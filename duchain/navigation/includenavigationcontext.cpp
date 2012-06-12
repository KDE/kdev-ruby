/* This file is part of KDevelop
 *
 * Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>
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


#include <KLocale>
#include <duchain/navigation/includenavigationcontext.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/declarations/methoddeclaration.h>


namespace Ruby
{

IncludeNavigationContext::IncludeNavigationContext(const KDevelop::IncludeItem &item,
                                                   KDevelop::TopDUContextPointer topContext)
    : AbstractIncludeNavigationContext(item, topContext, KDevelop::RubyParsingEnvironment)
{
    /* There's nothing to do here! */
}

void IncludeNavigationContext::getFileInfo(KDevelop::TopDUContext* duchain)
{
    modifyHtml() += QString("%1: %2")
                      .arg(labelHighlight(i18nc("Count of files this header was included into", "Included by")))
                      .arg(duchain->importers().count());
    modifyHtml() += "<br />";
}

QString IncludeNavigationContext::declarationKind(KDevelop::DeclarationPointer decl)
{
    const MethodDeclaration *md = dynamic_cast<const MethodDeclaration *>(decl.data());
    if (md)
        return (md->isClassMethod()) ? "Class method" : "Instance method";

    const ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(decl.data());
    if (mDecl) {
        ClassDeclaration *cDecl = dynamic_cast<ClassDeclaration *>(decl.data());
        if (cDecl)
            return "Class";
        return "Module";
    }
    return KDevelop::AbstractNavigationContext::declarationKind(decl);
}

} // End of namespace Ruby

