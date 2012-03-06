/*
 * This file is part of KDevelop
 * Copyright 2012  Miquel Sabaté <mikisabate@gmail.com>
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


// Qt + KDE
#include <QApplication>
#include <QAction>
#include <KLocalizedString>

// Ruby
#include <codegen/rubyrefactoring.h>
#include <codegen/rubynewclass.h>


namespace Ruby
{

RubyRefactoring & RubyRefactoring::self()
{
    static RubyRefactoring rr;
    return rr;
}

void RubyRefactoring::doContextMenu(KDevelop::ContextMenuExtension &extension,
                                    KDevelop::Context *context)
{
    if (KDevelop::ProjectItemContext* projectContext = dynamic_cast<KDevelop::ProjectItemContext*>(context)) {
        if (projectContext->items().count() == 1) {
            KDevelop::ProjectBaseItem* item = projectContext->items().first();
            if (item->folder() || item->target()) {
                QAction *action = new QAction(i18n("Create New Ruby Class"), this);
                action->setData(QVariant::fromValue<KDevelop::ProjectBaseItem*>(item));
                connect(action, SIGNAL(triggered(bool)),
                        this, SLOT(executeNewClassAction()));
                extension.addAction(KDevelop::ContextMenuExtension::FileGroup, action);
            }
        }
    }
}

void RubyRefactoring::createNewClass(KDevelop::ProjectBaseItem *item)
{
    /*
     * TODO: the code below is not complete. It should detect if this is a Rails
     * application. If it's so, then it has to check if the user clicked
     * over a "relevant" directory (models, controllers,...). Otherwise we
     * have to retrieve the url just like the c++ plugin does.
     * TODO: move this code to the RubyNewClass class.
     */
    KUrl u = KUrl();
    if (item) {
        KDevelop::ProjectBaseItem *ff = item->folder();
        if(!ff && item->target())
            ff = static_cast<KDevelop::ProjectBaseItem*>(item->parent())->folder();
        if(ff)
            u = ff->url();
    } else {
        // TODO: get url from current selection
    }
    RubyNewClass newClass(item);
    RubyNewClassWizard newClassWizard(qApp->activeWindow(), &newClass, u);
    newClassWizard.exec();
}

void RubyRefactoring::executeNewClassAction()
{
    QAction* action = qobject_cast<QAction *>(sender());
    if (action) {
        KDevelop::ProjectBaseItem* item = action->data().value<KDevelop::ProjectBaseItem *>();
        createNewClass(item);
    }
}

}
