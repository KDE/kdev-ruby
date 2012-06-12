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
#include <duchain/declarations/variabledeclaration.h>
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
        modifyHtml() += "class ";

        /* Write identifier */
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        /* Write inheritance */
        if (classDecl->baseClass()) {
            AbstractType::Ptr base = classDecl->baseClass().abstractType();
            modifyHtml() += " is a subclass of ";
            eventuallyMakeTypeLinks(base);
        }
        modifyHtml() += " ";
    } else if (mDecl) {
        modifyHtml() += "module ";
        /* Write identifier */
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        modifyHtml() += " ";
        // Add the modules/classes that include/extend this module.
        addMixers(mDecl);
    }

    // Both classes and modules can have a valid module mix-in list.
    if (mDecl)
        addModuleMixins(mDecl);
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

    const ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(decl.data());
    if (mDecl)
        return NULL;

    VariableDeclaration *var = dynamic_cast<VariableDeclaration *>(decl.data());
    if (var) {
        switch (var->variableKind()) {
            case 3: return "Global variable";
            case 4: return "Instance variable";
            case 5: return "Class variable";
            case 6: return "Constant";
            default: return "Variable";
        }
    }
    return KDevelop::AbstractNavigationContext::declarationKind(decl);
}

void DeclarationNavigationContext::addModuleMixins(ModuleDeclaration *decl)
{
    uint nMixins = decl->moduleMixinsSize();
    QList<AbstractType::Ptr> includes, extends;
    ModuleMixin aux;

    if (nMixins > 0) {
        for (uint i = 0; i < nMixins; i++) {
            aux = decl->moduleMixins()[i];
            if (aux.included)
                includes << aux.module.abstractType();
            else
                extends << aux.module.abstractType();
        }
        if (!includes.isEmpty()) {
            modifyHtml() += "<br>Includes: ";
            foreach (const AbstractType::Ptr d, includes)
                eventuallyMakeTypeLinks(d);
        }
        if (!extends.isEmpty()) {
            modifyHtml() += "<br>Extends: ";
            foreach (const AbstractType::Ptr d, extends)
                eventuallyMakeTypeLinks(d);
        }
    }
}

void DeclarationNavigationContext::addMixers(ModuleDeclaration *decl)
{
    uint nMixers = decl->mixersSize();
    const ModuleMixin *aux;

    if (nMixers > 0) {
        aux = decl->mixers();
        modifyHtml() += "<br>Mixed in: ";
        for (uint i = 0; i < nMixers; i++) {
            eventuallyMakeTypeLinks(aux[i].module.abstractType());
            if (i != nMixers - 1)
                modifyHtml() += ", ";
        }
    }
}

} // End of namespace Ruby

