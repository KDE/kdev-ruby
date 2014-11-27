/* This file is part of KDevelop
 *
 * Copyright (C) 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <rails/support.h>

#include <QtWidgets/QAction>

#include <interfaces/icore.h>
#include <interfaces/iplugincontroller.h>
#include <language/interfaces/iquickopen.h>

#include <rails/dataprovider.h>
#include <rails/switchers.h>

using namespace Rails;

Support::Support(Ruby::LanguageSupport *support)
    : QObject(nullptr)
    , m_support(support)
    , m_views(nullptr)
    , m_tests(nullptr)
{
    m_switchers = new Switchers(support);
    setupQuickOpen();
}

Support::~Support()
{
    delete m_switchers;
    delete m_views;
    delete m_tests;
}

void Support::setupQuickOpen()
{
    auto qo = m_support->core()->pluginController()->
        extensionForPlugin<KDevelop::IQuickOpen>("org.kdevelop.IQuickOpen");

    Q_ASSERT(qo);

    m_views = new DataProvider(Kind::Views);
    auto name = QStringList(i18n("Rails Views"));
    qo->registerProvider(DataProvider::scopes(), name, m_views);

    m_tests = new DataProvider(Kind::Tests);
    name = QStringList(i18n("Rails Tests"));
    qo->registerProvider(DataProvider::scopes(), name, m_tests);
}

void Support::setupActions(KActionCollection &actions)
{
    QAction *action = actions.addAction("ruby_switch_to_controller");
    action->setText(i18n("Switch To Controller"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_1);
    connect(action, &QAction::triggered,
            m_switchers, &Switchers::switchToController);

    action = actions.addAction("ruby_switch_to_model");
    action->setText(i18n("Switch To Model"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_2);
    connect(action, &QAction::triggered,
            m_switchers, &Switchers::switchToModel);

    action = actions.addAction("ruby_switch_to_view");
    action->setText(i18n("Switch To View"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_3);
    connect(action, &QAction::triggered,
            m_switchers, &Switchers::switchToView);

    action = actions.addAction("ruby_switch_to_test");
    action->setText(i18n("Switch To Test"));
    action->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_4);
    connect(action, &QAction::triggered,
            m_switchers, &Switchers::switchToTest);
}

