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


#ifndef RUBY_REFACTORING_H
#define RUBY_REFACTORING_H


#include <interfaces/contextmenuextension.h>
#include <interfaces/context.h>


namespace Ruby
{

/**
 * @class RubyRefactoring
 *
 * The RubyRefactoring class packs all the refactoring functionalities
 * that this plugin provides.
 */
class RubyRefactoring : public QObject
{
    Q_OBJECT

public:
    /**
     * @return instance of this class.
     */
    static RubyRefactoring & self();

    /**
     * It extends the context menu by adding all the available refactoring
     * actions. In order to do this, it takes the context menu @p extension
     * and the given @param context.
     */
    void doContextMenu(KDevelop::ContextMenuExtension &extension, KDevelop::Context *context);

    /**
     * It makes the 'Create New Ruby Class' dialog to appear.
     *
     * @param item the KDevelop::ProjectBaseItem that the user may have
     * selected.
     */
    void createNewClass(KDevelop::ProjectBaseItem *item);

private slots:
    /**
     * Executed from the context menu when the user wants to
     * create a new class.
     */
    void executeNewClassAction();
};

}

#endif /* RUBY_REFACTORING_H */
