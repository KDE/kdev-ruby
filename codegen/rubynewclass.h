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


#ifndef RUBY_NEWCLASS_H
#define RUBY_NEWCLASS_H

#include <KUrl>

#include <language/duchain/declaration.h>
#include <language/interfaces/icreateclasshelper.h>
#include <language/codegen/templateclassgenerator.h>


namespace Ruby
{

class RubyClassHelper: public KDevelop::ICreateClassHelper {
public:
    RubyClassHelper();
    virtual ~RubyClassHelper();

    virtual KDevelop::TemplateClassGenerator* createGenerator(const KUrl& baseUrl);
    virtual QList< KDevelop::DeclarationPointer > defaultMethods(const QString& name) const;
};

class RubyNewClass : public KDevelop::TemplateClassGenerator {
public:
    RubyNewClass(KUrl url);
    virtual KDevelop::DocumentChangeSet generate();

};

}


#endif /* RUBY_NEWCLASS_H */
