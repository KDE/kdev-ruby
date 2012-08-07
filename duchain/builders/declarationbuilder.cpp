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


// KDE
#include <KLocale>

// KDevelop
#include <language/duchain/types/functiontype.h>
#include <language/duchain/types/integraltype.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/aliasdeclaration.h>
#include <language/duchain/duchainutils.h>

// Ruby
#include <rubydefs.h>
#include <duchain/helpers.h>
#include <duchain/expressionvisitor.h>
#include <duchain/editorintegrator.h>
#include <duchain/builders/declarationbuilder.h>
#include <duchain/declarations/variabledeclaration.h>
#include <duchain/declarations/methoddeclaration.h>
#include <duchain/declarations/classdeclaration.h>
#include <duchain/declarations/moduledeclaration.h>
#include <duchain/types/objecttype.h>


namespace Ruby
{

DeclarationBuilder::DeclarationBuilder() : DeclarationBuilderBase()
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

void DeclarationBuilder::startVisiting(RubyAst *node)
{
    m_unresolvedImports.clear();
    m_injected = false;
    lastClassModule = NULL;
    DeclarationBuilderBase::startVisiting(node);
}

template<typename T>
T * DeclarationBuilder::reopenDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range)
{
    DUChainReadLocker rlock(DUChain::lock());
    Declaration *res = NULL;
    QList<Declaration *> decls = currentContext()->findDeclarations(id);

    foreach (Declaration *d, decls) {
        Declaration *fitting = dynamic_cast<T*>(d);
        if (fitting && (d->topContext() == currentContext()->topContext())) {
            debug() << "Reopening the following declaration: " << d->toString();
            openDeclarationInternal(d);
            d->setRange(range);
            setEncountered(d);
            // TODO: register the re-opening
            res = d;
            break;
        } else
            debug() << "Do not reopen since it's not in the same top context";
    }

    if (!res)
        res = openDeclaration<T>(id, range);
    return static_cast<T*>(res);
}

void DeclarationBuilder::visitClassStatement(RubyAst *node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);
    const QByteArray &comment = getComment(node);
    ClassDeclaration *baseClass = NULL;

    if (!validReDeclaration(id, range)) {
        node->foundProblems = true;
        return;
    }

    /* First of all, open the declaration and set the comment */
    ClassDeclaration *decl = reopenDeclaration<ClassDeclaration>(id, range);
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->clearBaseClass();
    decl->clearModuleMixins();
    decl->setKind(KDevelop::Declaration::Type);
    m_accessPolicy.push(Declaration::Public);
    lastClassModule = decl;
    insideClassModule = true;
    m_classDeclarations.push(DeclarationPointer(decl));

    /*
     * Now let's check for the base class. Ruby does not support multiple
     * inheritance, and the access is always public.
     */
    Node *aux = node->tree;
    node->tree = node->tree->cond;
    if (node->tree) {
        QualifiedIdentifier baseId = getIdentifier(node);
        KDevelop::Declaration *baseDecl = getDeclaration(baseId, range, DUContextPointer(currentContext()));
        if (!baseDecl)
            appendProblem(node->tree, i18n("NameError: undefined local variable or method `%1'", baseId.toString()));
        else {
            baseClass = dynamic_cast<ClassDeclaration *>(baseDecl);
            if (!baseClass)
                appendProblem(node->tree, i18n("TypeError: wrong argument type (expected Class)"));
            else if (baseClass->internalContext())
                decl->setBaseClass(baseClass->indexedType());
            else
                debug() << "Error: found a valid base class but with no internal context";
        }
    }
    node->tree = aux;

    /*  Setup types and go for the class body */
    ClassType::Ptr type = ClassType::Ptr(new ClassType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    openContextForClassDefinition(node);
    if (baseClass && baseClass->internalContext())
        currentContext()->addImportedParentContext(baseClass->internalContext());
    decl->setInternalContext(currentContext());
    DeclarationBuilderBase::visitClassStatement(node);
    closeContext();

    closeType();
    closeDeclaration();
    m_classDeclarations.pop();
    insideClassModule = false;
    m_accessPolicy.pop();
}

void DeclarationBuilder::visitSingletonClass(RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    ExpressionVisitor ev(currentContext(), m_editor);
    Node *aux = node->tree;

    node->tree = node->tree->r;
    ev.visitNode(node);
    if (ev.lastType()) {
        Declaration *d = ev.lastDeclaration().data();
        if (d) {
            if (!d->internalContext()) {
                d = StructureType::Ptr::dynamicCast(ev.lastType())->declaration(topContext());
                m_instance = true;
            } else
                m_instance = false;
            if (d) {
                lastClassModule = d;
                insideClassModule = true;
                m_classDeclarations.push(DeclarationPointer(d));
                m_injected = true;
                injectContext(d->internalContext());
            }
        }
    }

    node->tree = aux;
    RubyAstVisitor::visitSingletonClass(node);
    if (m_injected) {
        closeInjectedContext();
        m_injected = false;
        m_classDeclarations.pop();
        insideClassModule = false;
    }
}

void DeclarationBuilder::visitModuleStatement(RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);
    const QByteArray &comment = getComment(node);

    if (!validReDeclaration(id, range, false)) {
        node->foundProblems = true;
        return;
    }

    ModuleDeclaration *decl = reopenDeclaration<ModuleDeclaration>(id, range);
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->clearModuleMixins();
    decl->clearMixers();
    decl->setKind(KDevelop::Declaration::Type);
    m_accessPolicy.push(Declaration::Public);
    lastClassModule = decl;
    insideClassModule = true;

    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
    DeclarationBuilderBase::visitModuleStatement(node);
    closeContext();

    closeType();
    closeDeclaration();
    insideClassModule = false;
    m_accessPolicy.pop();
}

void DeclarationBuilder::visitMethodStatement(RubyAst *node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);
    const QByteArray &comment = getComment(node);
    bool injectedContext = false;
    bool instance = true;
    Node *aux = node->tree;

    /*
     * Check if this is a singleton method. If it is so, we have to determine
     * what's the context to be injected in order to get everything straight.
     */
    node->tree = aux->cond;
    if (valid_children(node->tree)) {
        node->tree = node->tree->l;
        ExpressionVisitor ev(currentContext(), m_editor);
        ev.visitNode(node);
        if (ev.lastType()) {
            Declaration *d = ev.lastDeclaration().data();
            if (d) {
                if (!d->internalContext()) {
                    StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());
                    d = (sType) ? sType->declaration(topContext()) : NULL;
                    instance = true;
                } else
                    instance = false;
                if (d) {
                    injectedContext = true;
                    injectContext(d->internalContext());
                    node->tree = aux->cond->r;
                    id = getIdentifier(node);
                    range = editorFindRange(node, node);
                }
            }
        }
    }
    node->tree = aux;

    MethodDeclaration *decl = reopenDeclaration<MethodDeclaration>(id, range);
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->clearYieldTypes();
    if (m_injected)
        decl->setClassMethod(!m_instance);
    else
        decl->setClassMethod(!instance);
    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
    if (currentContext()->type() == DUContext::Class)
        decl->setAccessPolicy(currentAccessPolicy());

    openType(type);
    decl->setInSymbolTable(false);
    decl->setType(type);
    decl->clearDefaultParameters();
    DeclarationBuilderBase::visitMethodStatement(node);
    closeDeclaration();
    eventuallyAssignInternalContext();
    closeType();

    /*
     * In Ruby, a method returns the last expression if no return expression
     * has been fired. Thus, the type of the last expression has to be mixed
     * into the return type of this method.
     */
    node->tree = aux->l;
    if (node->tree && node->tree->l) {
        node->tree = get_last_expr(node->tree->l);
        if (node->tree->kind != token_return) {
            ExpressionVisitor ev(node->context, m_editor);
            ev.visitNode(node);
            if (ev.lastType())
                type->setReturnType(mergeTypes(ev.lastType(), type->returnType()));
        }
    }
    node->tree = aux;

    if (!type->returnType())
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeNull)));
    decl->setType(type);
    decl->setInSymbolTable(true);

    if (injectedContext)
        closeInjectedContext();
}

void DeclarationBuilder::visitParameter(RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    MethodDeclaration *mDecl = dynamic_cast<MethodDeclaration *>(currentDeclaration());
    ExpressionVisitor ev(currentContext(), m_editor);
    ev.visitParameter(node);
    AbstractType::Ptr type = ev.lastType();

    /* Just grab the left side if this is an optional parameter */
    if (node->tree->l) {
        Node *aux = node->tree->l;
        node->tree = node->tree->r;
        mDecl->addDefaultParameter(IndexedString(m_editor->tokenToString(node->tree)));
        node->tree = aux;
    }

    /* Finally, declare the parameter */
    FunctionType::Ptr mType = currentType<FunctionType>();
    if (mType) {
        mType->addArgument(type);
        declareVariable(getIdentifier(node), type, node);
    }
}

void DeclarationBuilder::visitBlockVariables(RubyAst *node)
{
    MethodDeclaration *last = dynamic_cast<MethodDeclaration *>(m_lastMethodCall);
    Node *n = node->tree;
    if (!last || !n)
        return;

    uint i = 0;
    uint max = last->yieldTypesSize();
    AbstractType::Ptr type;
    const YieldType *yieldList = last->yieldTypes();
    for (Node *aux = n; aux != NULL; aux = aux->next, i++) {
        node->tree = aux;
        if (yieldList && i < max)
            type = yieldList[i].type.abstractType();
        else
            type = AbstractType::Ptr(new IntegralType(IntegralType::TypeMixed));
        declareVariable(getIdentifier(node), type, node);
    }
}

void DeclarationBuilder::visitVariable(RubyAst *node)
{
    QualifiedIdentifier id = getIdentifier(node);
    AbstractType::Ptr type(new ObjectType());
    declareVariable(id, type, node);
}

void DeclarationBuilder::visitBlock(RubyAst *node)
{
    m_accessPolicy.push(Declaration::Public);
    RubyAstVisitor::visitBlock(node);
    m_accessPolicy.pop();
}

void DeclarationBuilder::visitReturnStatement(RubyAst *node)
{
    RubyAstVisitor::visitReturnStatement(node);
    if (node->tree->l != NULL) {
        node->tree = node->tree->l;
        if (!hasCurrentType()) {
            appendProblem(node->tree, i18n("Return statement not within function declaration"));
            return;
        }
        TypePtr<FunctionType> t = currentType<FunctionType>();
        if (!t) // the case of: a = -> { return 1 }
            return;
        ExpressionVisitor ev(currentContext(), m_editor);
        ev.visitNode(node);
        AbstractType::Ptr rType = t->returnType();
        t->setReturnType(mergeTypes(ev.lastType(), rType));
    }
}

void DeclarationBuilder::visitAssignmentStatement(RubyAst *node)
{
    QList<AbstractType::Ptr> values;
    QList<DeclarationPointer> declarations;
    QList<bool> alias;

    debug() << "==== Starting with the assignment statement !!!!";
    DUChainReadLocker lock(DUChain::lock());

    /* First of all, fetch the types and declaration on the right side */
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

    /*
     * Check if we can unpack. If it's possible, do it and get out! We can
     * unpack if the following conditions are satisfied:
     *  - More than 1 expressions on the left side.
     *  - Just one expression on the right side, which has Array as its type.
     */
    int rsize = values.length();
    if (rsize == 1) {
        int rest = nodeListSize(node->tree->l);
        ClassType::Ptr ct = values.first().cast<ClassType>();
        if (rest > 1 && ct && ct->contentType()) {
            lock.lock();
            QualifiedIdentifier qi = ct.unsafeData()->declaration(topContext())->qualifiedIdentifier();
            lock.unlock();
            if (qi == QualifiedIdentifier("Array")) {
                for (Node *n = node->tree->l; n != NULL; n = n->next) {
                    aux->tree = n;
                    QualifiedIdentifier id = getIdentifier(aux);
                    declareVariable(id, ct->contentType().abstractType(), aux);
                }
                delete aux;
                return;
            }
        }
    }

    /*
     * We cannot unpack, so iterate over the left side expressions
     * and assign types.
     */
    int i = 0;
    AbstractType::Ptr type;
    for (Node *n = node->tree->l; n != NULL; n = n->next, i++) {
        if (n->kind == token_method_call)
            continue;
        aux->tree = n;
        if (has_star(n)) {
            int rest = nodeListSize(n) - 1;
            int pack = rsize - i - rest;
            ClassType::Ptr newType = getBuiltinsType("Array", currentContext()).cast<ClassType>();
            DUChainWriteLocker wlock(DUChain::lock());
            for (int j = pack; j > 0; j--, i++)
                newType->addContentType(values.at(i));
            wlock.unlock();
            i--;
            if (!is_just_a_star(n)) {
                QualifiedIdentifier id = getIdentifier(aux);
                declareVariable(id, newType.cast<AbstractType>(), aux);
            }
        } else if (i < rsize) {
            if (alias.at(i)) {
                DUChainWriteLocker wlock(DUChain::lock());
                RangeInRevision range = getNameRange(aux);
                QualifiedIdentifier id = getIdentifier(aux);
                AliasDeclaration *d = openDeclaration<AliasDeclaration>(id, range);
                d->setAliasedDeclaration(declarations.at(i).data());
                closeDeclaration();
            } else {
                type = values.at(i);
                if (!type) // HACK: provisional fix, should be removed in the future
                    type = new ObjectType();
                debug() << "We have to set the following type: " << type->toString();
                QualifiedIdentifier id = getIdentifier(aux);
                declareVariable(id, type, aux);
            }
        } else {
            // TODO: the following shows that we need some caching system at the ExpressionVisitor
            lock.lock();
            type = topContext()->findDeclarations(QualifiedIdentifier("NilClass")).first()->abstractType();
            lock.unlock();
            QualifiedIdentifier id = getIdentifier(aux);
            declareVariable(id, type, aux);
        }
    }
    delete aux;
}

void DeclarationBuilder::visitAliasStatement(RubyAst *node)
{
    RubyAst *right = new RubyAst(node->tree->r, node->context);
    QualifiedIdentifier id = QualifiedIdentifier(QString(right->tree->name));
    const RangeInRevision &range = editorFindRange(right, right);
    KDevelop::Declaration *decl = getDeclaration(id, range, DUContextPointer(currentContext()));

    if (is_global_var(node->tree->l) && is_global_var(right->tree)) {
        DUChainWriteLocker wlock(DUChain::lock());
        // If the global variable on the right is not declared, declare it as nil
        if (!decl) {
            // TODO: NilClass should be cached, since it's already heavily used in other parts of the builder
            AbstractType::Ptr type = topContext()->findDeclarations(QualifiedIdentifier("NilClass")).first()->abstractType();
            VariableDeclaration *vDecl = openDefinition<VariableDeclaration>(id, range);
            vDecl->setVariableKind(right->tree);
            vDecl->setKind(Declaration::Instance);
            vDecl->setType(type);
            eventuallyAssignInternalContext();
            DeclarationBuilderBase::closeDeclaration();
            decl = vDecl;
        }
        node->tree = node->tree->l;
        QualifiedIdentifier aid = getIdentifier(node);
        AbstractType::Ptr type = decl->abstractType();
        declareVariable(aid, type, node);
    } else if (decl && decl->isFunctionDeclaration()) {
        DUChainWriteLocker wlock(DUChain::lock());
        node->tree = node->tree->l;
        const RangeInRevision & arange = editorFindRange(node, node);
        QualifiedIdentifier aid = getIdentifier(node);
        aliasMethodDeclaration(aid, arange, decl);
    } else
        appendProblem(node->tree, i18n("undefined method `%1'", id.toString()));
}

void DeclarationBuilder::visitMethodCall(RubyAst *node)
{
    DUChainReadLocker lock(DUChain::lock());
    Node *aux = node->tree;
    ExpressionVisitor v(currentContext(), m_editor);
    v.visitNode(node);

    /* Let's take a look at the method arguments */
    DeclarationPointer lastMethod = v.lastDeclaration();
    if (lastMethod) {
        DUContext *argCtx = DUChainUtils::getArgumentContext(lastMethod.data());
        FunctionType::Ptr mtype = lastMethod->type<FunctionType>();
        if (argCtx && mtype) {
            QVector<Declaration *> args = argCtx->localDeclarations();
            lock.unlock();
            visitMethodCallArgs(node, args);
        }
    }

    /* And last but not least, go for the block */
    node->tree = aux->cond;
    m_lastMethodCall = lastMethod.data();
    lock.unlock();
    visitBlock(node);
    lock.lock();
    m_lastMethodCall = NULL;
    node->tree = aux;
}

void DeclarationBuilder::visitInclude(RubyAst *node)
{
    Node *aux = node->tree;
    node->tree = node->tree->r;
    registerModuleMixin(node, true);
    node->tree = aux;
}

void DeclarationBuilder::visitExtend(RubyAst *node)
{
    Node *aux = node->tree;
    node->tree = node->tree->r;
    registerModuleMixin(node, false);
    node->tree = aux;
}

void DeclarationBuilder::visitLambda(RubyAst *node)
{
    // TODO
    Ruby::RubyAstVisitor::visitLambda(node);
}

void DeclarationBuilder::visitForStatement(RubyAst *node)
{
    Node *aux = node->tree;
    node->tree = node->tree->cond;
    ExpressionVisitor ev(currentContext(), m_editor);

    ev.visitNode(node);
    AbstractType::Ptr type = ev.lastType();
    if (type) {
        ClassType::Ptr ctype = type.cast<ClassType>();
        if (ctype && ctype->contentType())
            type = ctype->contentType().abstractType();
        else
            type = AbstractType::Ptr(new ObjectType);
    } else
        type = AbstractType::Ptr(new ObjectType);

    node->tree = aux->r;
    for (Node *n = node->tree; n != NULL; n = n->next) {
        node->tree = n;
        QualifiedIdentifier id = getIdentifier(node);
        declareVariable(id, type, node);
    }
    node->tree = aux;
}

void DeclarationBuilder::visitAccessSpecifier(short int policy)
{
    switch (policy) {
        case 0:
            setAccessPolicy(KDevelop::Declaration::Public);
            break;
        case 1:
            setAccessPolicy(KDevelop::Declaration::Protected);
            break;
        case 2:
            setAccessPolicy(KDevelop::Declaration::Private);
    }
}

void DeclarationBuilder::visitYieldStatement(RubyAst *node)
{
    MethodDeclaration *mDecl = currentDeclaration<MethodDeclaration>();
    Node *n = node->tree;
    if (mDecl && n->l) {
        ExpressionVisitor ev(currentContext(), m_editor);
        uint i = 0;
        for (Node *aux = n->l; aux != NULL; aux = aux->next, i++) {
            node->tree = aux;
            ev.visitNode(node);
            YieldType yt = { ev.lastType()->indexed() };
            mDecl->replaceYieldTypes(yt, i);
        }
    }
    node->tree = n;
}

void DeclarationBuilder::declareVariable(const QualifiedIdentifier &id, AbstractType::Ptr type, RubyAst *node)
{
    DUChainWriteLocker wlock(DUChain::lock());
    RangeInRevision range;
    Node *aux = node->tree;
    QualifiedIdentifier rId(id);
    VariableDeclaration *dec = NULL;
    bool hintContainer = false;

    /* Take care of the special a[...] case */
    if (aux->kind == token_array_value) {
        node->tree = aux->l;
        rId = getIdentifier(node);
        hintContainer = true;
    }
    range = editorFindRange(node, node);

    if ((is_ivar(node->tree) || is_cvar(node->tree)) && !m_classDeclarations.isEmpty()) {
        DUContext *internal = m_classDeclarations.last()->internalContext();
        DUContext *previousCtx = currentContext();
        injectContext(internal);
        VariableDeclaration *var = reopenDeclaration<VariableDeclaration>(rId, range);
        var->setRange(RangeInRevision(internal->range().start, internal->range().start));
        var->setAutoDeclaration(true);
        previousCtx->createUse(var->ownIndex(), range);
        var->setVariableKind(node->tree);
        var->setKind(Declaration::Instance);
        var->setType(mergeTypes(var->abstractType(), type));
        DeclarationBuilderBase::closeDeclaration();
        closeInjectedContext();
        node->tree = aux;
        return;
    }

    /* Let's check if this variable is already declared */
    QList<Declaration *> decs = currentContext()->findDeclarations(rId.first(), startPos(node), 0, DUContext::DontSearchInParent);
    if (!decs.isEmpty()) {
        dec = dynamic_cast<VariableDeclaration *>(decs.last());
        if (dec) {
            ClassType::Ptr ct = dec->type<ClassType>();
            if (ct && hintContainer) {
                ct->addContentType(type);
                dec->setType(AbstractType::Ptr::dynamicCast(ct));
            } else
                dec->setType(mergeTypes(dec->abstractType(), type));
            node->tree = aux;
            return;
        }
    }

    dec = openDefinition<VariableDeclaration>(rId, range);
    dec->setVariableKind(node->tree);
    dec->setKind(Declaration::Instance);
    dec->setType(type);
    DeclarationBuilderBase::closeDeclaration();
    node->tree = aux;
}

void DeclarationBuilder::aliasMethodDeclaration(const QualifiedIdentifier &id,
                                                const RangeInRevision &range,
                                                Declaration *decl)
{
    MethodDeclaration *d = dynamic_cast<MethodDeclaration *>(decl);
    setComment(d->comment());
    MethodDeclaration *alias = openDeclaration<MethodDeclaration>(id, range);
    alias->setType(decl->type<FunctionType>());
    closeDeclaration();
}

KDevelop::RangeInRevision DeclarationBuilder::getNameRange(const RubyAst *node)
{
    return m_editor->findRange(rb_name_node(node->tree));
}

void DeclarationBuilder::registerModuleMixin(RubyAst *module, bool include)
{
    ModuleDeclaration *decl = getModuleDeclaration(module);
    if (decl) {
        // Register the Module mixin
        if (lastClassModule) {
            ModuleDeclaration *current = dynamic_cast<ModuleDeclaration *>(lastClassModule);
            if (current) {
                DUChainWriteLocker lock(DUChain::lock());
                ModuleMixin mixin;
                mixin.included = include;
                mixin.module = decl->indexedType();
                current->addModuleMixin(mixin);
                mixin.module = current->indexedType();
                decl->addMixer(mixin);
            }
        }

        // Add all the available methods from the mixed in module
        QList<MethodDeclaration *> eMethods = getDeclaredMethods(decl);
        foreach (MethodDeclaration *md, eMethods) {
            if (md->isClassMethod() ^ include) {
                DUChainWriteLocker wlock(DUChain::lock());
                Declaration *raw = dynamic_cast<Declaration *>(md);
                aliasMethodDeclaration(md->qualifiedIdentifier(), md->range(), raw);
            }
        }
    }
}

ModuleDeclaration * DeclarationBuilder::getModuleDeclaration(RubyAst *module)
{
    ExpressionVisitor ev(currentContext(), m_editor);
    Declaration *d;

    ev.visitNode(module);
    d = ev.lastDeclaration().data();
    if (d) {
        ClassDeclaration *cDecl = dynamic_cast<ClassDeclaration *>(d);
        ModuleDeclaration *found = dynamic_cast<ModuleDeclaration *>(d);
        if (!cDecl && found)
            return found;
        appendProblem(module->tree, i18n("TypeError: wrong argument type (expected Module)"));
    }
    return NULL;
}

QList<MethodDeclaration *> DeclarationBuilder::getDeclaredMethods(Declaration *decl)
{
    DUChainReadLocker rlock(DUChain::lock());
    QList<MethodDeclaration *> res;
    DUContext *internal = decl->internalContext();
    if (!internal)
        return res;

    QList<QPair<Declaration *, int> > list = internal->allDeclarations(internal->range().end, decl->topContext(), false);
    for (int i = 0; i < list.size(); i++) {
        MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(list.at(i).first);
        if (md)
            res << md;
    }
    return res;
}

bool DeclarationBuilder::validReDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range, bool isClass)
{
    DUChainReadLocker rlock(DUChain::lock());
    QList<Declaration *> decls = currentContext()->findDeclarations(id, range.end, AbstractType::Ptr(NULL),
                                                                    NULL, DUContext::DontSearchInParent);

    foreach (Declaration *d, decls) {
        ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(d);
        ClassDeclaration *cd = dynamic_cast<ClassDeclaration *>(d);
        if ((cd && !isClass) || (md && !cd && isClass)) {
            const QString msg = i18n("TypeError: %1 is not a %2", id.toString(), (isClass) ? "class" : "module");
            rlock.unlock();
            appendProblem(range, msg);
            return false;
        }
    }
    return true;
}

void DeclarationBuilder::visitMethodCallArgs(RubyAst *mc, const QVector<Declaration *> &args)
{
    RubyAst *node = new RubyAst(mc->tree->r, mc->context);
    VariableDeclaration *vd;
    int total, left = 0, right = 0;
    bool mark = false, starSeen = false;

    if (args.isEmpty())
        total = 0;
    else {
        vd = dynamic_cast<VariableDeclaration *>(args.last());
        total = args.size() - vd->isBlock();
    }

    /*
     * Normal arguments can appear before and/or after a list of opt_args
     * and a rest_arg. Therefore, these kind of arguments will mark the left
     * side and the right side. This is important to know because of the
     * flexibility that Ruby gives to the programmer.
     */
    for (int i = 0; i < total; i++) {
        vd = dynamic_cast<VariableDeclaration *>(args.at(i));
        if (!vd->hasStar() && !vd->isOpt()) {
            (mark) ? right++ : left++;
        } else if (vd->hasStar()) {
            starSeen = true;
            mark = true;
        } else
            mark = true;
    }

    /* We have enough info to know if we have to raise an ArgumentError */
    int nCaller = nodeListSize(node->tree);
    if (nCaller < (left + right)) {
        appendProblem(mc->tree, i18n("wrong number of arguments (%1 for %2)"
                                       " (ArgumentError)", nCaller, left + right));
        delete node;
        return;
    } else if (!starSeen && (total < nCaller)) {
        appendProblem(mc->tree, i18n("wrong number of arguments (%1 for %2)"
                                       " (ArgumentError)", nCaller, total));
        delete node;
        return;
    }

    /*
     * Everything is fine, do the iteration. Note that opt_args and rest_args
     * will be fed depending on the left and right counters.
     */
    int i = 0;
    int rest = nCaller - left - right;
    DUChainWriteLocker wlock(DUChain::lock());
    for (Node *n = node->tree; n; i++) {
        vd = dynamic_cast<VariableDeclaration *>(args.at(i));
        node->tree = n;
        if (vd->isOpt()) {
            if (rest > 0)
                rest--;
            else
                continue;
        } else if (vd->hasStar()) {
            ClassType::Ptr ct = vd->type<ClassType>();
            for (int j = rest; j > 0; j--) {
                ExpressionVisitor av(currentContext(), m_editor);
                av.visitNode(node);
                if (av.lastType())
                    ct->addContentType(av.lastType());
                node->tree = node->tree->next;
            }
            vd->setType(ct);
            n = node->tree;
            continue;
        }
        ExpressionVisitor av(currentContext(), m_editor);
        av.visitNode(node);
        AbstractType::Ptr last = av.lastType().cast<AbstractType>();
        AbstractType::Ptr original = args.at(i)->abstractType();
        args.at(i)->setType(mergeTypes(original, last));
        n = n->next;
    }
    delete node;
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

} // End of namespace Ruby
