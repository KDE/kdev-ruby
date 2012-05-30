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


// KDE
#include <KLocalizedString>

// KDevelop
#include <language/duchain/types/abstracttype.h>
#include <language/duchain/types/indexedtype.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/navigation/declarationnavigationcontext.h>


namespace Ruby
{
using namespace KDevelop;

DeclarationNavigationContext::DeclarationNavigationContext( DeclarationPointer decl,
                                                            TopDUContextPointer topContext,
                                                            AbstractNavigationContext *prevContext)
    : AbstractDeclarationNavigationContext(decl, topContext, prevContext)
{
    /* There's nothing to do here! */
}

void DeclarationNavigationContext::htmlClass()
{
    StructureType::Ptr klass = m_declaration->abstractType().cast<StructureType>();
    Q_ASSERT(klass);
    ClassDeclaration *classDecl = dynamic_cast<ClassDeclaration *>(klass->declaration(m_topContext.data()));
    ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(klass->declaration(m_topContext.data()));

    if (classDecl) {
        /* Write class type */
        if (classDecl->classType() == ClassDeclarationData::Interface)
            modifyHtml() += "module ";
        else
            modifyHtml() += "class ";

        /* Write identifier */
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        /* Write inheritance */
        if (classDecl->baseClassesSize() > 0) {
            AbstractType::Ptr base = classDecl->baseClasses()->baseClass.abstractType();
            modifyHtml() += " is a subclass of ";
            eventuallyMakeTypeLinks(base);
        }
        modifyHtml() += " ";
    } else if (mDecl) {
        modifyHtml() += "module ";
        /* Write identifier */
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        /* Write inheritance */
        modifyHtml() += " ";
    }
}

void DeclarationNavigationContext::makeLink(const QString &name, DeclarationPointer declaration,
                                            NavigationAction::Type actionType)
{
    if (actionType == NavigationAction::JumpToSource
            && declaration->url() == internalBuiltinsFile()) {
        modifyHtml() += i18n("Ruby Kernel");
        return;
    }
    AbstractDeclarationNavigationContext::makeLink(name, declaration, actionType);
}

QString DeclarationNavigationContext::declarationKind(DeclarationPointer decl)
{
    const MethodDeclaration *md = dynamic_cast<const MethodDeclaration *>(decl.data());
    
    if (md)
        return (md->isClassMethod()) ? "Class method" : "Instance method";
    ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(decl.data());
    if (mDecl)
        return NULL;
    return KDevelop::AbstractNavigationContext::declarationKind(decl);
}

void DeclarationNavigationContext::htmlIdentifiedType(AbstractType::Ptr type,
                                                      const IdentifiedType *idType)
{
    // TODO
    KDevelop::AbstractDeclarationNavigationContext::htmlIdentifiedType(type, idType);
}

} // End of namespace Ruby

