/* This file is part of KDevelop
 *
 * Copyright 2006-2010 Alexander Dymo <adymo@kdevelop.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


//BEGIN Includes
// Qt + KDE
#include <QtCore/QTimer>
#include <QtCore/QProcess>
#include <QtWidgets/QAction>
#include <KActionCollection>

//KDevelop
#include <interfaces/icore.h>
#include <interfaces/iproject.h>
#include <interfaces/idocument.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/iprojectcontroller.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/iruncontroller.h>
#include <interfaces/ilauncher.h>
#include <interfaces/ilaunchmode.h>
#include <interfaces/ilaunchconfiguration.h>
#include <interfaces/launchconfigurationtype.h>
#include <execute/iexecuteplugin.h>
#include <project/projectmodel.h>
#include <language/interfaces/iquickopen.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchainutils.h>
#include <language/backgroundparser/backgroundparser.h>
#include <language/codecompletion/codecompletion.h>
#include <interfaces/contextmenuextension.h>
#include <language/interfaces/editorcontext.h>

//Ruby plugin
#include <languagesupport.h>
#include <parsejob.h>
#include <highlighting.h>
#include <rails/switchers.h>
#include <rails/dataprovider.h>
#include <rails/helpers.h>
#include <duchain/helpers.h>
#include <completion/model.h>
#include <codegen/refactoring.h>
#include <debug.h>
#include <version.h>
//END Includes


#define RUBY_FILE_LAUNCH_CONFIGURATION_NAME i18n("Current Ruby File")
#define RUBY_CURRENT_FUNCTION_LAUNCH_CONFIGURATION_NAME i18n("Current Ruby Test Function")

K_PLUGIN_FACTORY(KDevRubySupportFactory, registerPlugin<Ruby::LanguageSupport>();)

Q_LOGGING_CATEGORY(KDEV_RUBY, "kdev.ruby")

namespace Ruby
{

LanguageSupport::LanguageSupport(QObject *parent, const QVariantList &)
    : KDevelop::IPlugin(QStringLiteral("kdevrubysupport"), parent)
    , KDevelop::ILanguageSupport()
    , m_builtinsLoaded(false)
    , m_railsSwitchers(new Rails::Switchers(this))
    , m_viewsQuickOpenDataProvider(nullptr)
    , m_testsQuickOpenDataProvider(nullptr)
    , m_rubyFileLaunchConfiguration(nullptr)
    , m_rubyCurrentFunctionLaunchConfiguration(nullptr)
{
    // TODO: this should be removed once KDE knows how to handle categories.
    QLoggingCategory::setFilterRules(QStringLiteral("kdev.ruby.debug = true"));

    m_builtinsLock.lockForWrite();

    KDEV_USE_EXTENSION_INTERFACE(KDevelop::ILanguageSupport)
    setXMLFile("kdevrubysupport.rc");
    m_highlighting = new Ruby::Highlighting(this);
    m_refactoring = new Ruby::Refactoring(this);
    CodeCompletionModel *rModel = new CodeCompletionModel(this);
    new KDevelop::CodeCompletion(this, rModel, "Ruby");

    setupQuickOpen();

    QTimer::singleShot(0, this, SLOT(updateBuiltins()));

    /* Retrieving Ruby version */
    QProcess ruby;
    ruby.start("/usr/bin/env", QStringList() << "ruby" << "--version");
    ruby.waitForFinished();
    QString output = ruby.readAllStandardOutput().split(' ')[1];
    QStringList version = output.split('.');
    if (version.size() > 1) {
        if (version[0] == "1") {
            m_version = (version[1] == "8") ? ruby18 : ruby19;
        } else if (version[1] == "0") {
            m_version = ruby20;
        } else {
            m_version = ruby21;
        }
    }
}

LanguageSupport::~LanguageSupport()
{
    /* There's nothing to do here! */
}

QString LanguageSupport::name() const
{
    return QStringLiteral("Ruby");
}

KDevelop::ParseJob * LanguageSupport::createParseJob(const KDevelop::IndexedString &url)
{
    return new ParseJob(url, this);
}

KDevelop::ILanguage * LanguageSupport::language()
{
    return core()->languageController()->language(name());
}

KDevelop::ICodeHighlighting * LanguageSupport::codeHighlighting() const
{
    return m_highlighting;
}

KDevelop::ContextMenuExtension LanguageSupport::contextMenuExtension(KDevelop::Context *context)
{
    KDevelop::ContextMenuExtension cm;
    KDevelop::EditorContext *ed = dynamic_cast<KDevelop::EditorContext *>(context);

    if (ed && KDevelop::ICore::self()->languageController()->languagesForUrl(ed->url()).contains(language())) {
        // It's safe to add our own ContextMenuExtension.
        m_refactoring->fillContextMenu(cm, context);
    }
    return cm;
}

bool LanguageSupport::builtinsLoaded() const
{
    return m_builtinsLoaded;
}

QReadWriteLock * LanguageSupport::builtinsLock()
{
    return &m_builtinsLock;
}

enum ruby_version LanguageSupport::version() const
{
    return m_version;
}

void LanguageSupport::updateReady(KDevelop::IndexedString url, KDevelop::ReferencedTopDUContext topContext)
{
    Q_UNUSED(topContext)
    rDebug() << "builtins file is up to date " << url.str();
    m_builtinsLoaded = true;
    m_builtinsLock.unlock();
}

void LanguageSupport::updateBuiltins()
{
    rDebug() << "making sure that the builtins file is up to date";
    KDevelop::DUChain::self()->updateContextForUrl(internalBuiltinsFile(), KDevelop::TopDUContext::AllDeclarationsAndContexts, this, -10);
}

void LanguageSupport::runCurrentFile()
{
    KDevelop::IDocument *doc = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!doc)
        return;

    // Get out if this is not a Ruby file.
    if (!KDevelop::ICore::self()->languageController()->languagesForUrl(doc->url()).contains(language()))
        return;

    if (!m_rubyFileLaunchConfiguration)
        m_rubyFileLaunchConfiguration = findOrCreateLaunchConfiguration(RUBY_FILE_LAUNCH_CONFIGURATION_NAME);
    if (!m_rubyFileLaunchConfiguration)
        return;

    KConfigGroup cfg = m_rubyFileLaunchConfiguration->config();
    setUpLaunchConfigurationBeforeRun(cfg, doc);
    cfg.writeEntry("Arguments", QStringList() << doc->url().toLocalFile());
    cfg.sync();

    core()->runController()->execute(QStringLiteral("execute"),
                                     m_rubyFileLaunchConfiguration);
}

void LanguageSupport::runCurrentTestFunction()
{
    KDevelop::IDocument *doc = KDevelop::ICore::self()->documentController()->activeDocument();
    if (!doc)
        return;

    // Get out if this is not a Ruby file.
    if (!KDevelop::ICore::self()->languageController()->languagesForUrl(doc->url()).contains(language()))
        return;

    if (!m_rubyCurrentFunctionLaunchConfiguration)
        m_rubyCurrentFunctionLaunchConfiguration = findOrCreateLaunchConfiguration(RUBY_CURRENT_FUNCTION_LAUNCH_CONFIGURATION_NAME);
    if (!m_rubyCurrentFunctionLaunchConfiguration)
        return;

    // Find function under the cursor (if any)
    QString currentFunction = findFunctionUnderCursor(doc);
    rDebug() << "current function" << currentFunction;
    if (currentFunction.isEmpty())
        return;

    KConfigGroup cfg = m_rubyCurrentFunctionLaunchConfiguration->config();
    setUpLaunchConfigurationBeforeRun(cfg, doc);
    QStringList args;
    args << doc->url().toLocalFile() << "-n" << currentFunction;
    cfg.writeEntry("Arguments", args.join(" "));
    cfg.sync();

    core()->runController()->execute(QStringLiteral("execute"),
                                     m_rubyCurrentFunctionLaunchConfiguration);
}

QString LanguageSupport::findFunctionUnderCursor(KDevelop::IDocument *doc)
{
    QString function;
    KDevelop::DUChainReadLocker lock;

    KDevelop::TopDUContext *topContext = KDevelop::DUChainUtils::standardContextForUrl(doc->url());
    if (!topContext) {
        return "";
    }

    KDevelop::CursorInRevision cursor = KDevelop::CursorInRevision(doc->cursorPosition().line(), doc->cursorPosition().column());
    KDevelop::DUContext* context = topContext->findContextAt(cursor);
    if (!context)
        return "";

    rDebug() << "CONTEXT ID" << context->localScopeIdentifier();
    return context->localScopeIdentifier().toString();
}

void LanguageSupport::setUpLaunchConfigurationBeforeRun(KConfigGroup &cfg, KDevelop::IDocument *activeDocument)
{
    KDevelop::Path root = Rails::Helpers::findRailsRoot(activeDocument->url());
    if (root.isValid()) {
        cfg.writeEntry("Working Directory", root.toLocalFile());
    } else {
        cfg.writeEntry("Working Directory", root.parent().path());
    }
}

KDevelop::ILaunchConfiguration * LanguageSupport::findOrCreateLaunchConfiguration(const QString &name)
{
    foreach (KDevelop::ILaunchConfiguration *config, core()->runController()->launchConfigurations()) {
        if (config->name() == name) {
            return config;
        }
    }
    KDevelop::ILaunchConfiguration *config = nullptr;

    IExecutePlugin* executePlugin = core()->pluginController()->pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
    KDevelop::LaunchConfigurationType* type = core()->runController()->launchConfigurationTypeForId(executePlugin->nativeAppConfigTypeId());
    if (!type) {
        return nullptr;
    }

    KDevelop::ILaunchMode* mode = core()->runController()->launchModeForId("execute");
    if (!mode) {
        return nullptr;
    }

    KDevelop::ILauncher *launcher = nullptr;
    foreach (KDevelop::ILauncher *l, type->launchers()) {
        if (l->supportedModes().contains(QStringLiteral("execute"))) {
            launcher = l;
        }
    }
    if (!launcher) {
        return nullptr;
    }

    config = core()->runController()->createLaunchConfiguration(type, qMakePair(mode->id(), launcher->id()), nullptr, name);

    KConfigGroup cfg = config->config();
    cfg.writeEntry("isExecutable", true);
    cfg.writeEntry("Executable", "ruby");
    cfg.sync();

    return config;
}

void LanguageSupport::createActionsForMainWindow(Sublime::MainWindow * /*window*/,
                                                 QString &_xmlFile,
                                                 KActionCollection &actions)
{
    _xmlFile = xmlFile();

    QAction *action = actions.addAction("ruby_switch_to_controller");
    action->setText(i18n("Switch To Controller"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_1);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToController()));

    action = actions.addAction("ruby_switch_to_model");
    action->setText(i18n("Switch To Model"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_2);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToModel()));

    action = actions.addAction("ruby_switch_to_view");
    action->setText(i18n("Switch To View"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_3);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToView()));

    action = actions.addAction("ruby_switch_to_test");
    action->setText(i18n("Switch To Test"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_4);
    connect(action, SIGNAL(triggered(bool)), m_railsSwitchers, SLOT(switchToTest()));

    action = actions.addAction("ruby_run_current_file");
    action->setText(i18n("Run Current File"));
    action->setShortcut(Qt::META | Qt::Key_F9);
    connect(action, SIGNAL(triggered(bool)), this, SLOT(runCurrentFile()));

    action = actions.addAction("ruby_run_current_test_function");
    action->setText(i18n("Run Current Test Function"));
    action->setShortcut(Qt::META | Qt::SHIFT | Qt::Key_F9);
    connect(action, SIGNAL(triggered(bool)), this, SLOT(runCurrentTestFunction()));
}

void LanguageSupport::setupQuickOpen()
{
    KDevelop::IQuickOpen * quickOpen = core()->pluginController()->extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");
    if (quickOpen) {
        m_viewsQuickOpenDataProvider = new Rails::DataProvider(Rails::Kind::Views);
        quickOpen->registerProvider(Rails::DataProvider::scopes(), QStringList(i18n("Rails Views")), m_viewsQuickOpenDataProvider);

        m_testsQuickOpenDataProvider = new Rails::DataProvider(Rails::Kind::Tests);
        quickOpen->registerProvider(Rails::DataProvider::scopes(), QStringList(i18n("Rails Tests")), m_testsQuickOpenDataProvider);
    }
}

}

#include "languagesupport.moc"
