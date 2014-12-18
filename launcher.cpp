/* This file is part of KDevelop
 *
 * Copyright 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <launcher.h>

#include <QtWidgets/QAction>

#include <klocalizedstring.h>

#include <execute/iexecuteplugin.h>
#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/ilaunchconfiguration.h>
#include <interfaces/ilauncher.h>
#include <interfaces/ilaunchmode.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/launchconfigurationtype.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/duchainutils.h>
#include <language/duchain/topducontext.h>

#include <debug.h>
#include <languagesupport.h>
#include <rails/helpers.h>

using namespace ruby;
using namespace KDevelop;

namespace {

/**
 * @internal Set up the launch configuration before the run occurs.
 * @param cfg the KConfigGroup for this launch.
 * @param document the currently active document.
 */
void setupBeforeRun(KConfigGroup &cfg, IDocument *document)
{
    Path root = rails::Helpers::findRailsRoot(document->url());

    if (root.isValid()) {
        cfg.writeEntry("Working Directory", root.toLocalFile());
    } else {
        cfg.writeEntry("Working Directory", root.parent().path());
    }
}

/**
 * @internal Find the method under the cursor in the given \p doc. It's
 * used by the runCurrentTestFunction() slot.
 */
QString findFunctionUnderCursor(KDevelop::IDocument *doc)
{
    DUChainReadLocker lock;

    const auto top = DUChainUtils::standardContextForUrl(doc->url());
    if (!top) {
        return "";
    }

    const auto &cursor = doc->cursorPosition();
    auto context = top->findContextAt(CursorInRevision(
        cursor.line(), cursor.column()
    ));
    if (!context) {
        return "";
    }

    rDebug() << "CONTEXT ID" << context->localScopeIdentifier();
    return context->localScopeIdentifier().toString();
}

}

Launcher::Launcher(LanguageSupport *support)
    : QObject(support)
    , m_file(nullptr)
    , m_function(nullptr)
{
    m_support = support;
}

void Launcher::setupActions(KActionCollection &actions)
{
    QAction *action = actions.addAction("ruby_run_current_file");
    action->setText(i18n("Run Current File"));
    action->setShortcut(Qt::META | Qt::Key_F9);
    connect(action, &QAction::triggered, this, &Launcher::runCurrentFile);

    action = actions.addAction("ruby_run_current_test_function");
    action->setText(i18n("Run Current Test Function"));
    action->setShortcut(Qt::META | Qt::SHIFT | Qt::Key_F9);
    connect(action, &QAction::triggered, this, &Launcher::runCurrentTest);
}

ILaunchConfiguration * Launcher::launchConfiguration(const QString &name)
{
    for (auto config : m_support->core()->runController()->launchConfigurations()) {
        if (config->name() == name) {
            return config;
        }
    }

    auto executePlugin = m_support->core()->pluginController()->
        pluginForExtension("org.kdevelop.IExecutePlugin")->extension<IExecutePlugin>();
    auto type = m_support->core()->runController()->launchConfigurationTypeForId(
        executePlugin->nativeAppConfigTypeId());

    if (!type) {
        return nullptr;
    }

    auto mode = m_support->core()->runController()->launchModeForId("execute");
    if (!mode) {
        return nullptr;
    }

    KDevelop::ILauncher *launcher = nullptr;
    for (auto l : type->launchers()) {
        if (l->supportedModes().contains(QStringLiteral("execute"))) {
            launcher = l;
            break;
        }
    }
    if (!launcher) {
        return nullptr;
    }

    auto config = m_support->core()->runController()->createLaunchConfiguration(
        type, qMakePair(mode->id(), launcher->id()), nullptr, name);

    KConfigGroup cfg = config->config();
    cfg.writeEntry("isExecutable", true);
    cfg.writeEntry("Executable", "ruby");
    cfg.sync();

    return config;
}

void Launcher::runCurrentFile()
{
    auto doc = ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return;
    }

    // Get out if this is not a Ruby file.
    if (!ICore::self()->languageController()->languagesForUrl(doc->url()).
            contains(m_support->language())) {
        return;
    }

    if (!m_file) {
        m_file = launchConfiguration(i18n("Current Ruby File"));
        if (!m_file) {
            return;
        }
    }

    KConfigGroup cfg = m_file->config();
    setupBeforeRun(cfg, doc);
    cfg.writeEntry("Arguments", QStringList() << doc->url().toLocalFile());
    cfg.sync();

    m_support->core()->runController()->
        execute(QStringLiteral("execute"), m_file);
}

void Launcher::runCurrentTest()
{
    auto doc = ICore::self()->documentController()->activeDocument();
    if (!doc) {
        return;
    }

    // Get out if this is not a Ruby file.
    if (!ICore::self()->languageController()->languagesForUrl(doc->url()).
            contains(m_support->language())) {
        return;
    }

    if (!m_function) {
        m_function = launchConfiguration(i18n("Current Ruby Test Function"));
        if (!m_function) {
            return;
        }
    }

    // Find function under the cursor (if any).
    const QString &&currentFunction = findFunctionUnderCursor(doc);
    if (currentFunction.isEmpty()) {
        return;
    }

    KConfigGroup cfg = m_function->config();
    setupBeforeRun(cfg, doc);
    QStringList args{
        doc->url().toLocalFile(),
        "-n",
        currentFunction
    };
    cfg.writeEntry("Arguments", args.join(" "));
    cfg.sync();

    m_support->core()->runController()->execute(
        QStringLiteral("execute"), m_function);
}

