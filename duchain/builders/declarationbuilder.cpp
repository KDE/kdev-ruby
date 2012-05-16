/* This file is part of KDevelop
 *
 * Copyright 2010 Niko Sams <niko.sams@gmail.com>
 * Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
 * Copyright 2011 Miquel Sabaté <mikisabate@gmail.com>
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


#include <duchain/builders/declarationbuilder.h>
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <duchain/declarations/variabledeclaration.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/editorintegrator.h>
#include <rubydefs.h>
#include <duchain/types/objecttype.h>
#include <duchain/types/variablelengthcontainer.h>
#include <language/duchain/types/unsuretype.h>
#include <KLocale>
#include <duchain/helpers.h>
#include <duchain/expressionvisitor.h>
#include <language/duchain/aliasdeclaration.h>
#include <language/duchain/duchainutils.h>


namespace Ruby
{

DeclarationBuilder::DeclarationBuilder()
    : DeclarationBuilderBase()
{
    /* There's nothing to do here! */
}

DeclarationBuilder::DeclarationBuilder(EditorIntegrator *editor)
    : DeclarationBuilderBase(), m_editor(editor)
{
    setEditor(editor);
}

DeclarationBuilder::~DeclarationBuilder()
{
    /* There's nothing to do here! */
}

ReferencedTopDUContext DeclarationBuilder::build(const IndexedString &url, RubyAst *node, ReferencedTopDUContext updateContext)
{
    return DeclarationBuilderBase::build(url, node, updateContext);
}

void DeclarationBuilder::startVisiting(RubyAst *node)
{
    m_unresolvedImports.clear();
    DeclarationBuilderBase::startVisiting(node);
}

void DeclarationBuilder::visitClassStatement(RubyAst *node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);

    /* First of all, open the declaration and set the comment */
    setComment(getComment(node));
    ClassDeclaration *decl = openDeclaration<ClassDeclaration>(id, range);
    decl->setKind(KDevelop::Declaration::Type);
    decl->clearBaseClasses();
    decl->setClassType(ClassDeclarationData::Class);
    lastClassModule = decl;
    insideClassModule = true;

    /*
     * Now let's check for the base class. Ruby does not support multiple
     * inheritance, and the access is always public.
     */
    Node *aux = node->tree;
    node->tree = node->tree->cond;
    if (node->tree) {
        QualifiedIdentifier baseId = getIdentifier(node);
        KDevelop::Declaration *baseDecl = declarationForNode(baseId, range, DUContextPointer(currentContext()));
        if (!baseDecl) {
            appendProblem(node->tree, i18n("NameError: undefined local variable or method `%1'", baseId.toString()));
        } else {
            ClassDeclaration *realClass = dynamic_cast<ClassDeclaration *>(baseDecl);
            if (!realClass || realClass->classType() == ClassDeclarationData::Interface) {
                appendProblem(node->tree, i18n("TypeError: wrong argument type (expected Class)"));
            } else {
                BaseClassInstance base;
                StructureType::Ptr baseType = baseDecl->type<StructureType>();
                base.baseClass = baseType->indexed();
                base.access = KDevelop::Declaration::Public;
                decl->addBaseClass(base);
            }
        }
    }
    node->tree = aux;

    /*  Setup types and go for the class body */
    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
    lock.unlock();
    DeclarationBuilderBase::visitClassStatement(node);
    lock.lock();
    closeContext();

    closeType();
    closeDeclaration();
    insideClassModule = false;
}

void DeclarationBuilder::visitModuleStatement(RubyAst* node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);

    setComment(getComment(node));
    /* TODO: should this get a ModuleDeclaration or so? */
    ClassDeclaration *decl = openDeclaration<ClassDeclaration>(id, range);
    decl->setKind(KDevelop::Declaration::Type);
    decl->clearBaseClasses();
    decl->setClassType(ClassDeclarationData::Interface);
    lastClassModule = decl;
    insideClassModule = true;

    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
    lock.unlock();
    DeclarationBuilderBase::visitModuleStatement(node);
    lock.lock();
    closeContext();

    closeType();
    closeDeclaration();
    insideClassModule = false;
}

void DeclarationBuilder::visitMethodStatement(RubyAst *node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);

    setComment(getComment(node));
    MethodDeclaration *decl = openDeclaration<MethodDeclaration>(id, range);
    decl->setClassMethod(is_class_method(node->tree));
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());

    openType(type);
    decl->setInSymbolTable(false);
    lock.unlock();
    DeclarationBuilderBase::visitMethodStatement(node);
    lock.lock();
    closeType();
    closeDeclaration();

    if (!type->returnType()) {
        /* TODO: return the type of the last statement instead */
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    }
    decl->setType(type);
}

void DeclarationBuilder::visitParameter(RubyAst *node)
{
    AbstractFunctionDeclaration *funcDecl = dynamic_cast<AbstractFunctionDeclaration*>(currentDeclaration());
    AbstractType::Ptr type(new ObjectType());

    /* TODO: handle default, star and block parameters */
    {
      // create variable declaration for argument
      DUChainWriteLocker lock(DUChain::lock());
      RangeInRevision range = m_editor->findRange(node->tree);
      openDefinition<VariableDeclaration>(getIdentifier(node), range);
      currentDeclaration()->setKind(Declaration::Instance);
      currentDeclaration()->setType(type);
    }
    DeclarationBuilderBase::visitParameter(node);
    closeDeclaration();
}

void DeclarationBuilder::visitBlockVariable(RubyAst *node)
{
    /* TODO Type should be inferred from the yield calls from the caller method */
    AbstractType::Ptr type(new ObjectType());

    // create variable declaration for argument
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = m_editor->findRange(node->tree);
    openDefinition<VariableDeclaration>(getIdentifier(node), range);
    currentDeclaration()->setKind(Declaration::Instance);
    currentDeclaration()->setType(type);
    DeclarationBuilderBase::visitBlockVariable(node);
    closeDeclaration();
}

void DeclarationBuilder::visitVariable(RubyAst *node)
{
    QualifiedIdentifier id = getIdentifier(node);
    AbstractType::Ptr type(new ObjectType());
    declareVariable(currentContext(), type, id, node);
}

void DeclarationBuilder::visitReturnStatement(RubyAst *node)
{
    RubyAstVisitor::visitReturnStatement(node);
    if (node->tree->l != NULL) {
        if (!hasCurrentType()) {
            appendProblem(node->tree->l, "Return statement not within"
                                         " function declaration");
            return;
        }
        TypePtr<FunctionType> t = currentType<FunctionType>();
        AbstractType::Ptr encountered(new ObjectType()); // TODO: Should be the last type
        t->setReturnType(encountered);
    }
    setLastType(AbstractType::Ptr(0));
}

void DeclarationBuilder::visitAssignmentStatement(RubyAst *node)
{
    /*
     * TODO: this method is under construction. Some ideas:
     *  - I'm sure that the loops can be merged.
     *  - The NilClass declaration has to be cached somehow.
     */

    QList<AbstractType::Ptr> values;
    QList<DeclarationPointer> declarations;
    QList<bool> alias;

    debug() << "==== Starting with the assignment statement !!!!";
    DUChainReadLocker lock(DUChain::lock());
    RubyAst *aux = new RubyAst(node->tree->r, node->context);
    for (Node *n = aux->tree; n != NULL; n = n->next) {
        ExpressionVisitor v(currentContext(), m_editor);
        aux->tree = n;
        v.visitNode(aux);
        values << v.lastType();
        alias << v.lastAlias();
        declarations << v.lastDeclaration();
    }
    lock.unlock();

    aux->tree = node->tree->l;
    int i = 0;
    int rsize = values.length();
    AbstractType::Ptr type;
    for (Node *n = aux->tree; n != NULL; n = n->next, i++) {
        aux->tree = n;
        if (i < rsize) {
            if (alias.at(i)) {
                DUChainWriteLocker wlock(DUChain::lock());
                RangeInRevision range = getNameRange(aux);
                QualifiedIdentifier id = getIdentifier(aux);
                AliasDeclaration *d = openDeclaration<AliasDeclaration>(id, range);
                d->setAliasedDeclaration(declarations.at(i).data());
                closeDeclaration();
            } else {
                DUChainWriteLocker wlock(DUChain::lock());
                type = values.at(i);
                if (!type) // HACK: provisional fix, should be removed in the future
                    type = new ObjectType();
                debug() << "We have to set the following type: " << type->toString();
                QualifiedIdentifier id = getIdentifier(aux);
                declareVariable(currentContext(), type, id, aux);
            }
        } else {
            DUChainWriteLocker wlock(DUChain::lock());
            // TODO: the following shows that we need some caching system at the ExpressionVisitor
            type = topContext()->findDeclarations(QualifiedIdentifier("NilClass")).first()->abstractType();
            QualifiedIdentifier id = getIdentifier(aux);
            declareVariable(currentContext(), type, id, aux);
        }
    }
    delete aux;
}

void DeclarationBuilder::visitAliasStatement(RubyAst *node)
{
    RubyAst *right = new RubyAst(node->tree->r, node->context);
    QualifiedIdentifier id = QualifiedIdentifier(QString(right->tree->name));
    DUChainReadLocker lock(DUChain::lock());
    const RangeInRevision &range = editorFindRange(right, right);
    KDevelop::Declaration *decl = declarationForNode(id, range, DUContextPointer(currentContext()));
    lock.unlock();

    if (is_global_var(node->tree->l) && is_global_var(right->tree)) {
        DUChainWriteLocker wlock(DUChain::lock());
        // If the global variable on the right is not declared, declare it as nil
        if (!decl) {
            // TODO: NilClass should be cached, since it's already heavily used in other parts of the builder
            AbstractType::Ptr type = topContext()->findDeclarations(QualifiedIdentifier("NilClass")).first()->abstractType();
            decl = openDefinition<VariableDeclaration>(id, range);
            decl->setKind(Declaration::Instance);
            decl->setType(type);
            eventuallyAssignInternalContext();
            DeclarationBuilderBase::closeDeclaration();
        }
        node->tree = node->tree->l;
        QualifiedIdentifier aid = getIdentifier(node);
        AbstractType::Ptr type = decl->abstractType();
        declareVariable(currentContext(), type, aid, node);
    } else if (decl && decl->isFunctionDeclaration()) {
        DUChainWriteLocker wlock(DUChain::lock());
        node->tree = node->tree->l;
        const RangeInRevision & arange = editorFindRange(node, node);
        QualifiedIdentifier aid = getIdentifier(node);
        aliasMethodDeclaration(aid, arange, decl);
    } else
        appendProblem(node->tree, QString("undefined method `" + id.toString() + "'"));
}

void DeclarationBuilder::visitMethodCall(RubyAst *node)
{
    DUChainReadLocker lock(DUChain::lock());
    ExpressionVisitor v(currentContext(), m_editor);
    v.visitNode(node);

    /* And now let's take a look at the method arguments */
    DeclarationPointer lastMethod = v.lastDeclaration();
    if (lastMethod) {
        DUContext *argCtx = DUChainUtils::getArgumentContext(lastMethod.data());
        FunctionType::Ptr mtype = lastMethod->type<FunctionType>();
        if (argCtx && mtype) {
            RubyAst *aux = new RubyAst(node->tree->r, node->context);
            QVector<Declaration *> args = argCtx->localDeclarations();
            int i = 0;
            lock.unlock();
            DUChainWriteLocker wlock(DUChain::lock());
            for (Node *n = aux->tree; n != NULL; n = n->next, i++) {
                aux->tree = n;
                ExpressionVisitor av(currentContext(), m_editor);
                av.visitNode(aux);
                args.at(i)->setType(av.lastType());
                /* TODO: mix types */
            }
            wlock.unlock();
        }
    }
}

void DeclarationBuilder::visitInclude(RubyAst *node)
{
    RubyAst *module = new RubyAst(node->tree->r, node->context);
    Declaration *decl = getModuleDeclaration(module);

    if (decl) {
        QList<MethodDeclaration *> iMethods = getDeclaredMethods(decl);
        foreach (MethodDeclaration *md, iMethods) {
            if (!md->isClassMethod()) {
                Declaration *raw = dynamic_cast<Declaration *>(md);
                {
                    DUChainWriteLocker wlock(DUChain::lock());
                    // TODO: instead of aliasing, register the include
                    aliasMethodDeclaration(md->qualifiedIdentifier(), md->range(), raw);
                }
            }
        }
    }
    delete module;
}

void DeclarationBuilder::visitExtend(RubyAst *node)
{
    RubyAst *module = new RubyAst(node->tree->r, node->context);
    Declaration *decl = getModuleDeclaration(module);

    if (decl) {
        QList<MethodDeclaration *> iMethods = getDeclaredMethods(decl);
        foreach (MethodDeclaration *md, iMethods) {
            if (md->isClassMethod()) {
                Declaration *raw = dynamic_cast<Declaration *>(md);
                {
                    DUChainWriteLocker wlock(DUChain::lock());
                    // TODO: instead of aliasing, register the exclude
                    aliasMethodDeclaration(md->qualifiedIdentifier(), md->range(), raw);
                }
            }
        }
    }
    delete module;
}

void DeclarationBuilder::declareVariable(DUContext *ctx, AbstractType::Ptr type,
                                         const QualifiedIdentifier &id, RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    const RangeInRevision range = editorFindRange(node, node);

    /* Let's check if this variable is already declared */
    QList<Declaration *> decs = ctx->findDeclarations(id.first(), startPos(node), 0, DUContext::DontSearchInParent);

    // TODO: Not sure if this is properly working...
    if (!decs.isEmpty()) {
        QList<Declaration *>::const_iterator it = decs.constEnd() - 1;
        for (;; --it) {
            if (dynamic_cast<VariableDeclaration *>(*it)) {
                if (!wasEncountered(*it)) {
                    setEncountered(*it);
                    (*it)->setRange(range);
                }
                if ((*it)->abstractType() && !(*it)->abstractType()->equals(type.unsafeData())) {
                    if ( IntegralType::Ptr integral = IntegralType::Ptr::dynamicCast((*it)->abstractType()) ) {
                        if ( integral->dataType() == IntegralType::TypeMixed ) {
                            // mixed to @p type
                            (*it)->setType(type);
                            return;
                        }
                    }
                    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast((*it)->abstractType());
                    if ( !unsure ) {
                        unsure = UnsureType::Ptr(new UnsureType());
                        unsure->addType((*it)->indexedType());
                    }
                    unsure->addType(type->indexed());
                    (*it)->setType(unsure);
                }
                return;
            }
            if (it == decs.constBegin())
                break;
        }
    }

    VariableDeclaration *dec = openDefinition<VariableDeclaration>(id, range);
    dec->setKind(Declaration::Instance);
    dec->setType(type);
    debug() << "Set type " << type->toString();
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::aliasMethodDeclaration(const QualifiedIdentifier &id,
                                                const RangeInRevision &range,
                                                Declaration *decl)
{
    MethodDeclaration *d = dynamic_cast<MethodDeclaration *>(decl);
    setComment(d->comment());
    MethodDeclaration *alias = openDeclaration<MethodDeclaration>(id, range);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
    openType(type);
    alias->setInSymbolTable(false);
    closeType();
    closeDeclaration();

    if (!type->returnType()) {
        /* TODO: return the type of the last statement instead */
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeVoid)));
    }
    alias->setType(type);
}

void DeclarationBuilder::appendProblem(Node *node, const QString &msg)
{
    KDevelop::Problem *p = new KDevelop::Problem();
    p->setFinalLocation(getDocumentRange(node));
    p->setSource(KDevelop::ProblemData::SemanticAnalysis);
    p->setDescription(msg);
    p->setSeverity(KDevelop::ProblemData::Error);
    {
        DUChainWriteLocker lock(DUChain::lock());
        topContext()->addProblem(ProblemPointer(p));
    }
}

KDevelop::RangeInRevision DeclarationBuilder::getNameRange(const RubyAst *node)
{
    return m_editor->findRange(rb_name_node(node->tree));
}

Declaration * DeclarationBuilder::getModuleDeclaration(const RubyAst *module)
{
    /*
     * NOTE: this is a convenient method that allows us to retrieve the declaration of
     * a module from an include/extend expression. This is just because the implementation
     * of the ExpressionVisitor::visitMethodCall is still a bit clunky. Therefore,
     * this method will eventually be gone.
     */
    DUChainReadLocker rlock(DUChain::lock());
    RubyAst *aux = new RubyAst(module->tree, module->context);
    DUContext *lastCtx = module->context;
    Declaration *lastDecl = NULL;

    if (aux->tree->kind == token_method_call)
        aux->tree = aux->tree->l;
    for (Node *n = aux->tree; n != NULL; n = n->next) {
        QualifiedIdentifier id = getIdentifier(aux);
        QList<Declaration *> list = lastCtx->findDeclarations(id.last());
        if (!list.empty()) {
            ClassDeclaration *d = dynamic_cast<ClassDeclaration *>(list.last());
            if (!d || d->classType() != ClassDeclarationData::Interface) {
                appendProblem(n, i18n("TypeError: wrong argument type (expected Module)"));
                return NULL;
            } else {
                lastCtx = d->internalContext();
                lastDecl = d;
            }
        }
        aux->tree = n->next;
    }
    delete aux;
    return lastDecl;
}

KDevelop::QualifiedIdentifier DeclarationBuilder::identifierForNode(NameAst *node)
{
    if (!node)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(node->value);
}

void DeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration() && lastType()) {
        DUChainWriteLocker wlock(DUChain::lock());
        currentDeclaration()->setType(lastType());
    }
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::updateCurrentType()
{
    DUChainWriteLocker lock(DUChain::lock());
    currentDeclaration()->setAbstractType(currentAbstractType());
}

}
