/* This file is part of KDevelop
 *
 * Copyright (C) 2011-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


namespace ruby
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
    AbstractDeclarationNavigationContext::html(shorten);
    modifyHtml()  += "<html><body><p>";

    if(!declaration().data()) {
        modifyHtml() += i18n("<br /> lost declaration <br />");
        return currentHtml();
    }
    if(auto context = previousContext()) {
        QString link = createLink(context->name(), context->name(), NavigationAction(context));
        modifyHtml() += navigationHighlight(i18n("Back to %1<br />", link));
    }

    if (!shorten) {
        const MethodDeclaration *mDecl = dynamic_cast<const MethodDeclaration *>(declaration().data());
        if (mDecl) {
            if (mDecl->qualifiedIdentifier().count() > 1 && mDecl->context() && mDecl->context()->owner()) {
                Declaration *d = declaration()->context()->owner();
                makeLink(declarationName(DeclarationPointer(d)), DeclarationPointer(d), NavigationAction::NavigateDeclaration);
                modifyHtml() += (mDecl->isClassMethod()) ? "::" : "#";
            }
            htmlFunction();
        } else if (declaration()->kind() == Declaration::Instance) {
            eventuallyMakeTypeLinks(declaration()->abstractType());
            const QString &esc = declarationName(declaration()).toHtmlEscaped();
            modifyHtml() += ' ' + nameHighlight(esc) + "<br>";
        } else if (declaration()->kind() == Declaration::Type && declaration()->abstractType().dynamicCast<StructureType>()) {
            htmlClass();
        }
    } else if (declaration()->abstractType()) {
        eventuallyMakeTypeLinks(declaration()->abstractType());
        modifyHtml() += " ";
    }

    QString access = stringFromAccess(declaration());
    if (!access.isEmpty()) {
        access = propertyHighlight(access.toHtmlEscaped());
        modifyHtml() += labelHighlight(i18n("Access: %1 ", access));
        modifyHtml() += "<br />";
    }

    if (!shorten) {
        htmlAdditionalNavigation();
        modifyHtml() += "<br />";
        modifyHtml() += labelHighlight(i18n("Def.: "));
        makeLink(QString("%1 :%2").arg(QUrl(declaration()->url().str()).fileName()).arg(declaration()->rangeInCurrentRevision().start().line() + 1), declaration(), NavigationAction::JumpToSource);
        modifyHtml() += " ";
        modifyHtml() += createLink(i18n("Show uses"), "show_uses", NavigationAction(declaration(), NavigationAction::NavigateUses));
        if(!shorten && !declaration()->comment().isEmpty()) {
            modifyHtml() += "<br />";
            QString comment = QString::fromUtf8(declaration()->comment());
            if(!comment.isEmpty()) {
                comment.replace("<br />", "\n");
                comment.replace("<br/>", "\n");
                comment = comment.toHtmlEscaped();
                comment.replace('\n', "<br />");
                modifyHtml() += commentHighlight(comment);
                modifyHtml() += "<br />";
            }
        }
    }

    modifyHtml() += "</p></body></html>";
    return currentHtml();
}

void DeclarationNavigationContext::htmlFunction()
{
    const MethodDeclaration *mDecl = dynamic_cast<const MethodDeclaration *>(declaration().data());
    Q_ASSERT(mDecl);

    const auto type = declaration()->abstractType().dynamicCast<FunctionType>();
    if (!type) {
        modifyHtml() += errorHighlight("Invalid type<br/>");
        return;
    }

    const QString &name = prettyIdentifier(declaration()).toString();
    modifyHtml() += nameHighlight(name.toHtmlEscaped());
    if (type->arguments().size() > 0) {
        bool first = true;
        int nDef = 0;
        DUContext *ctx = DUChainUtils::argumentContext(declaration().data());

        if (ctx) {
            modifyHtml() += "( ";
            foreach (Declaration *d, ctx->localDeclarations(topContext().data())) {
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
                const QString &aux = vd->identifier().toString();
                modifyHtml() += nameHighlight(aux.toHtmlEscaped());

                if (vd->isOpt()) {
                    const QString &str = mDecl->defaultParameters()[nDef].str();
                    modifyHtml() += " " + str.toHtmlEscaped();
                    nDef++;
                }
            }
            modifyHtml() += " )";
        }
    }
}

void DeclarationNavigationContext::htmlClass()
{
    Q_ASSERT(declaration()->abstractType());
    auto klass = declaration()->abstractType().staticCast<StructureType>();
    ModuleDeclaration *mDecl = dynamic_cast<ModuleDeclaration *>(klass->declaration(topContext().data()));

    if (mDecl) {
        if (mDecl->isModule()) {
            modifyHtml() += "module ";
            eventuallyMakeTypeLinks(declaration()->abstractType());
        } else {
            modifyHtml() += "class ";
            eventuallyMakeTypeLinks(declaration()->abstractType());

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

void DeclarationNavigationContext::makeLink(const QString &name, const DeclarationPointer& declaration,
                                            NavigationAction::Type actionType)
{
    if (actionType == NavigationAction::JumpToSource
            && declaration->url() == builtinsFile()) {
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

}

