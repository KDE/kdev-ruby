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


// Qt + KDevelop
#include <QtGui/QTextDocument>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/structuretype.h>
#include <language/duchain/duchainutils.h>

// Ruby
#include <duchain/helpers.h>
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

QString DeclarationNavigationContext::html(bool shorten)
{
    clear();
    m_shorten = shorten;
    modifyHtml()  += "<html><body><p>" + fontSizePrefix(shorten);
    addExternalHtml(m_prefix);

    if(!m_declaration.data()) {
        modifyHtml() += i18n("<br /> lost declaration <br />");
        return currentHtml();
    }
    if(m_previousContext) {
        QString link = createLink(m_previousContext->name(), m_previousContext->name(), NavigationAction(m_previousContext));
        modifyHtml() += navigationHighlight(i18n("Back to %1<br />", link));
    }

    if (!shorten) {
        const MethodDeclaration *mDecl = dynamic_cast<const MethodDeclaration *>(m_declaration.data());
        if (mDecl) {
            if (mDecl->qualifiedIdentifier().count() > 1 && mDecl->context() && mDecl->context()->owner()) {
                Declaration *d = m_declaration->context()->owner();
                makeLink(declarationName(DeclarationPointer(d)), DeclarationPointer(d), NavigationAction::NavigateDeclaration);
                modifyHtml() += (mDecl->isClassMethod()) ? "::" : "#";
            }
            htmlFunction();
        } else if (m_declaration->kind() == Declaration::Instance) {
            eventuallyMakeTypeLinks(m_declaration->abstractType());
            modifyHtml() += ' ' + nameHighlight(Qt::escape(declarationName(m_declaration))) + "<br>";
        } else if (m_declaration->kind() == Declaration::Type && m_declaration->abstractType().cast<StructureType>())
            htmlClass();
    } else if (m_declaration->abstractType()) {
        eventuallyMakeTypeLinks(m_declaration->abstractType());
        modifyHtml() += " ";
    }

    QString access = stringFromAccess(m_declaration);
    if (!access.isEmpty()) {
        modifyHtml() += labelHighlight(i18n("Access: %1 ", propertyHighlight(Qt::escape(access))));
        modifyHtml() += "<br />";
    }

    if (!shorten) {
        htmlAdditionalNavigation();
        modifyHtml() += "<br />";
        modifyHtml() += labelHighlight(i18n("Def.: "));
        makeLink(QString("%1 :%2").arg(KUrl(m_declaration->url().str()).fileName()).arg(m_declaration->rangeInCurrentRevision().textRange().start().line() + 1), m_declaration, NavigationAction::JumpToSource);
        modifyHtml() += " ";
        modifyHtml() += createLink(i18n("Show uses"), "show_uses", NavigationAction(m_declaration, NavigationAction::NavigateUses));
        if(!shorten && !m_declaration->comment().isEmpty()) {
            modifyHtml() += "<br />";
            QString comment = QString::fromUtf8(m_declaration->comment());
            if(!comment.isEmpty()) {
                comment.replace("<br />", "\n");
                comment.replace("<br/>", "\n");
                comment = Qt::escape(comment);
                comment.replace('\n', "<br />");
                modifyHtml() += commentHighlight(comment);
                modifyHtml() += "<br />";
            }
        }
    }

    addExternalHtml(m_suffix);
    modifyHtml() += fontSizeSuffix(shorten) + "</p></body></html>";
    return currentHtml();
}

void DeclarationNavigationContext::htmlFunction()
{
    const MethodDeclaration *mDecl = dynamic_cast<const MethodDeclaration *>(m_declaration.data());
    Q_ASSERT(mDecl);

    const FunctionType::Ptr type = m_declaration->abstractType().cast<FunctionType>();
    if (!type) {
        modifyHtml() += errorHighlight("Invalid type<br/>");
        return;
    }

    modifyHtml() += nameHighlight(Qt::escape(prettyIdentifier(m_declaration).toString()));
    if (type->arguments().size() > 0) {
        bool first = true;
        int nDef = 0;
        DUContext *ctx = DUChainUtils::getArgumentContext(m_declaration.data());

        if (ctx) {
            modifyHtml() += "( ";
            foreach (Declaration *d, ctx->localDeclarations(m_topContext.data())) {
                if (!first)
                    modifyHtml() += ", ";
                first = false;

                VariableDeclaration *vd = dynamic_cast<VariableDeclaration *>(d);
                if (vd->hasStar())
                    modifyHtml() += " *";
                else if (vd->isBlock())
                    modifyHtml() += " &";
                else
                    modifyHtml() += " ";
                modifyHtml() += nameHighlight(Qt::escape(vd->identifier().toString()));

                if (vd->isOpt()) {
                    modifyHtml() += " " + Qt::escape(mDecl->defaultParameters()[nDef].str());
                    nDef++;
                }
            }
            modifyHtml() += " )";
        }
    }
}

void DeclarationNavigationContext::htmlClass()
{
    StructureType::Ptr klass = m_declaration->abstractType().cast<StructureType>();
    Q_ASSERT(klass);
    ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(klass->declaration(m_topContext.data()));

    if (mDecl) {
        if (mDecl->isModule()) {
            modifyHtml() += "module ";
            eventuallyMakeTypeLinks(m_declaration->abstractType());
        } else {
            modifyHtml() += "class ";
            eventuallyMakeTypeLinks(m_declaration->abstractType());

            if (mDecl->baseClass()) {
                AbstractType::Ptr base = mDecl->baseClass().abstractType();
                modifyHtml() += " is a subclass of ";
                eventuallyMakeTypeLinks(base);
            }
        }
        modifyHtml() += " ";
        addModuleMixins(mDecl);
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
        modifyHtml() += "<br>";
    }
}

} // End of namespace Ruby

