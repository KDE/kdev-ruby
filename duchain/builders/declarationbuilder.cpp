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
#include <duchain/declarations/moduledeclaration.h>


namespace Ruby
{

DeclarationBuilder::DeclarationBuilder() : DeclarationBuilderBase()
{
    /* There's nothing to do here. */
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

void DeclarationBuilder::closeDeclaration()
{
    if (currentDeclaration() && lastType()) {
        DUChainWriteLocker wlock;
        currentDeclaration()->setType(lastType());
    }
    eventuallyAssignInternalContext();
    DeclarationBuilderBase::closeDeclaration();
}

void DeclarationBuilder::closeContext()
{
    if (currentContext()->type() == DUContext::Function) {
        Q_ASSERT(currentDeclaration<AbstractFunctionDeclaration>());
        currentDeclaration<AbstractFunctionDeclaration>()->setInternalFunctionContext(currentContext());
    }

    DeclarationBuilderBase::closeContext();
}

void DeclarationBuilder::startVisiting(RubyAst *node)
{
    m_unresolvedImports.clear();
    m_injected = false;
    m_lastMethodCall = nullptr;

    DeclarationBuilderBase::startVisiting(node);
}

void DeclarationBuilder::visitClassStatement(RubyAst *node)
{
    ModuleDeclaration *baseClass = nullptr;
    RangeInRevision range = getNameRange(node);
    const QByteArray comment = getComment(node);
    QualifiedIdentifier id = getIdentifier(node);
    DUContext *ctx = getContainedNameContext(node);

    /* First of all, open the declaration. */
    ModuleDeclaration *decl = reopenDeclaration<ModuleDeclaration>(id, range, ctx, Class);
    if (!decl) {
        node->foundProblems = true;
        return;
    }

    // Initialize the declaration.
    DUChainWriteLocker lock;
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->setIsModule(false);
    decl->clearBaseClass();
    decl->clearModuleMixins();
    decl->setKind(KDevelop::Declaration::Type);
    m_accessPolicy.push(Declaration::Public);
    m_classDeclarations.push(DeclarationPointer(decl));

    /*
     * Now let's check for the base class. Ruby does not support multiple
     * inheritance, and the access is always public.
     */
    Node *aux = node->tree;
    node->tree = node->tree->cond;
    if (node->tree) {
        ExpressionVisitor ev(ctx, m_editor);
        lock.unlock();
        ev.visitNode(node);
        DeclarationPointer baseDecl = ev.lastDeclaration();
        lock.lock();
        if (baseDecl) {
            baseClass = dynamic_cast<ModuleDeclaration *>(baseDecl.data());
            if (!baseClass || baseClass->isModule())
                appendProblem(node->tree, i18n("TypeError: wrong argument type (expected Class)"));
            else if (baseClass->internalContext())
                decl->setBaseClass(baseClass->indexedType());
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
    lock.unlock();
    DeclarationBuilderBase::visitClassStatement(node);
    lock.lock();
    closeContext();

    closeType();
    closeDeclaration();
    m_classDeclarations.pop();
    m_accessPolicy.pop();
}

void DeclarationBuilder::visitSingletonClass(RubyAst *node)
{
    ExpressionVisitor ev(currentContext(), m_editor);
    Node *aux = node->tree;

    node->tree = node->tree->r;
    ev.visitNode(node);
    if (ev.lastType()) {
        DeclarationPointer d = ev.lastDeclaration();
        if (d) {
            m_instance = false;
            if (!d->internalContext()) {
                StructureType::Ptr sType;
                UnsureType::Ptr ut = ev.lastType().cast<UnsureType>();
                if (ut && ut->typesSize() > 0)
                    sType = ut->types()[0].type<StructureType>();
                else
                    sType = StructureType::Ptr::dynamicCast(ev.lastType());
                if (sType) {
                    DUChainWriteLocker lock;
                    d = sType->declaration(topContext());
                    m_instance = true;
                } else
                    d = DeclarationPointer();
            }
            if (d) {
                m_classDeclarations.push(d);
                m_injected = true;
                injectContext(d->internalContext());
            }
        }
    }

    node->tree = aux;
    m_accessPolicy.push(Declaration::Public);
    RubyAstVisitor::visitSingletonClass(node);
    m_accessPolicy.pop();
    if (m_injected) {
        closeInjectedContext();
        m_injected = false;
        m_classDeclarations.pop();
    }
}

void DeclarationBuilder::visitModuleStatement(RubyAst *node)
{
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);
    const QByteArray comment = getComment(node);
    DUContext *ctx = getContainedNameContext(node);

    /* First of all, open the declaration. */
    ModuleDeclaration *decl = reopenDeclaration<ModuleDeclaration>(id, range, ctx, Module);
    if (!decl) {
        node->foundProblems = true;
        return;
    }

    // Initialize the declaration.
    DUChainWriteLocker wlock;
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->setIsModule(true);
    decl->clearModuleMixins();
    decl->clearMixers();
    decl->setKind(KDevelop::Declaration::Type);
    m_accessPolicy.push(Declaration::Public);
    m_classDeclarations.push(DeclarationPointer(decl));

    StructureType::Ptr type = StructureType::Ptr(new StructureType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    openContextForClassDefinition(node);
    decl->setInternalContext(currentContext());
    wlock.unlock();
    DeclarationBuilderBase::visitModuleStatement(node);
    wlock.lock();
    closeContext();

    closeType();
    closeDeclaration();
    m_accessPolicy.pop();
    m_classDeclarations.pop();
}

void DeclarationBuilder::visitMethodStatement(RubyAst *node)
{
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);
    const QByteArray comment = getComment(node);
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
            DeclarationPointer d = ev.lastDeclaration();
            if (d) {
                if (!d->internalContext()) {
                    DUChainWriteLocker lock;
                    StructureType::Ptr sType = StructureType::Ptr::dynamicCast(ev.lastType());
                    d = (sType) ? sType->declaration(topContext()) : nullptr;
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

    // Re-open the declaration.
    bool isClassMethod = (m_injected) ? !m_instance : !instance;
    MethodDeclaration *decl = reopenDeclaration(id, range, isClassMethod);

    DUChainWriteLocker lock;
    if (!comment.isEmpty())
        decl->setComment(comment);
    decl->clearYieldTypes();
    decl->setClassMethod(isClassMethod);

    FunctionType::Ptr type = FunctionType::Ptr(new FunctionType());
    if (currentContext()->type() == DUContext::Class)
        decl->setAccessPolicy(currentAccessPolicy());

    openType(type);
    decl->setInSymbolTable(false);
    decl->setType(type);
    decl->clearDefaultParameters();
    lock.unlock();
    DeclarationBuilderBase::visitMethodStatement(node);
    lock.lock();
    closeDeclaration();
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
            lock.unlock();
            ExpressionVisitor ev(node->context, m_editor);
            ev.visitNode(node);
            if (ev.lastType())
                type->setReturnType(mergeTypes(ev.lastType(), type->returnType()));
            lock.lock();
        }
    }
    node->tree = aux;

    if (!type->returnType())
        type->setReturnType(getBuiltinsType("NilClass", currentContext()));
    decl->setType(type);
    decl->setInSymbolTable(true);

    if (injectedContext)
        closeInjectedContext();
}

void DeclarationBuilder::visitParameter(RubyAst *node)
{
    MethodDeclaration *mDecl = dynamic_cast<MethodDeclaration *>(currentDeclaration());
    ExpressionVisitor ev(currentContext(), m_editor);
    ev.visitParameter(node);
    AbstractType::Ptr type = ev.lastType();

    /* Just grab the left side if this is an optional parameter */
    if (node->tree->l) {
        DUChainWriteLocker wlock;
        Node *aux = node->tree->l;
        node->tree = node->tree->r;
        mDecl->addDefaultParameter(IndexedString(m_editor->tokenToString(node->tree)));
        node->tree = aux;
    }

    /* Finally, declare the parameter */
    FunctionType::Ptr mType = currentType<FunctionType>();
    if (mType) {
        DUChainWriteLocker wlock;
        mType->addArgument(type);
        declareVariable(getIdentifier(node), type, node, DUContext::DontSearchInParent);
    }
}

void DeclarationBuilder::visitBlock(RubyAst *node)
{
    m_accessPolicy.push(Declaration::Public);
    DeclarationBuilderBase::visitBlock(node);
    m_accessPolicy.pop();
}

void DeclarationBuilder::visitBlockVariables(RubyAst *node)
{
    DUChainReadLocker rlock;
    MethodDeclaration *last = dynamic_cast<MethodDeclaration *>(m_lastMethodCall);
    Node *n = node->tree;
    if (!n)
        return;

    uint max = 0, i = 0;
    const YieldType *yieldList = nullptr;
    if (last) {
        yieldList = last->yieldTypes();
        max = last->yieldTypesSize();
    }

    AbstractType::Ptr type;
    for (Node *aux = n; aux != nullptr; aux = aux->next, i++) {
        node->tree = aux;
        if (yieldList && i < max)
            type = yieldList[i].type.abstractType();
        else
            type = getBuiltinsType("Object", currentContext());
        rlock.unlock();
        declareVariable(getIdentifier(node), type, node, DUContext::DontSearchInParent);
        rlock.lock();
    }
}

void DeclarationBuilder::visitReturnStatement(RubyAst *node)
{
    RubyAstVisitor::visitReturnStatement(node);

    if (node->tree->l != nullptr) {
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
        DUChainWriteLocker wlock;
        t->setReturnType(mergeTypes(ev.lastType(), rType));
    }
}

void DeclarationBuilder::visitAssignmentStatement(RubyAst *node)
{
    QList<AbstractType::Ptr> values;
    QList<DeclarationPointer> declarations;
    QList<bool> alias;
    DUChainReadLocker lock;

    /* First of all, fetch the types and declaration on the right side */
    RubyAst *aux = new RubyAst(node->tree->r, node->context);
    for (Node *n = aux->tree; n != nullptr; n = n->next) {
        ExpressionVisitor v(currentContext(), m_editor);
        aux->tree = n;
        lock.unlock();
        // TODO: improve this
        DeclarationBuilderBase::visitNode(aux);
        v.visitNode(aux);
        lock.lock();
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
                for (Node *n = node->tree->l; n != nullptr; n = n->next) {
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
    for (Node *n = node->tree->l; n != nullptr; n = n->next, i++) {
        if (n->kind == token_method_call)
            continue;
        aux->tree = n;
        if (has_star(n)) {
            int rest = nodeListSize(n) - 1;
            int pack = rsize - i - rest;
            ClassType::Ptr newType = getBuiltinsType("Array", currentContext()).cast<ClassType>();
            DUChainWriteLocker wlock;
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
                DUChainWriteLocker wlock;
                RangeInRevision range = getNameRange(aux);
                QualifiedIdentifier id = getIdentifier(aux);
                AliasDeclaration *d = openDeclaration<AliasDeclaration>(id, range);
                d->setAliasedDeclaration(declarations.at(i).data());
                closeDeclaration();
            } else {
                type = values.at(i);
                if (!type) // HACK: provisional fix, should be removed in the future
                    type = getBuiltinsType("Object", currentContext());
                QualifiedIdentifier id = getIdentifier(aux);
                declareVariable(id, type, aux);
            }
        } else {
            lock.lock();
            type = getBuiltinsType("NilClass", currentContext());
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
    DeclarationPointer decl = getDeclaration(id, range, DUContextPointer(currentContext()));

    if (is_global_var(node->tree->l) && is_global_var(right->tree)) {
        DUChainWriteLocker wlock;
        // If the global variable on the right is not declared, declare it as nil
        if (!decl) {
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
        DUChainWriteLocker wlock;
        MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(decl.data());
        node->tree = node->tree->l;
        const RangeInRevision & arange = editorFindRange(node, node);
        QualifiedIdentifier aid = getIdentifier(node);
        aliasMethodDeclaration(aid, arange, md);
    } else
        appendProblem(node->tree, i18n("undefined method `%1'", id.toString()));
}

void DeclarationBuilder::visitMethodCall(RubyAst *node)
{
    Node *aux = node->tree;

    /*
     * Handle chained method calls. Take a look at the implementation of
     * RubyAstVisitor::visitMethodCall() for more details.
     */
    node->tree = aux->l;
    if (node->tree->kind == token_method_call)
        visitMethodCall(node);
    node->tree = aux;

    ExpressionVisitor v(currentContext(), m_editor);
    v.visitNode(node);
    DeclarationPointer lastMethod = v.lastDeclaration();

    /* Let's take a look at the method arguments */
    visitMethodCallArgs(node, lastMethod);

    /* And last but not least, go for the block */
    node->tree = aux->cond;
    m_lastMethodCall = lastMethod.data();
    visitBlock(node);
    m_lastMethodCall = nullptr;
    node->tree = aux;
}

void DeclarationBuilder::visitMixin(RubyAst *node, bool include)
{
    RubyAst *module = new RubyAst(node->tree->r, node->context);
    ModuleDeclaration *decl = getModuleDeclaration(module);

    if (decl) {
        // Report an error if we're completely sure that this is not a module.
        if (!decl->isModule()) {
            appendProblem(node->tree->r, i18n("TypeError: wrong argument type (expected Module)"));
            return;
        }

        // Register the Module mixin
        if (insideClassModule()) {
            ModuleDeclaration *current = dynamic_cast<ModuleDeclaration *>(lastClassModule());
            if (current) {
                DUChainWriteLocker lock;
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
                DUChainWriteLocker wlock;
                aliasMethodDeclaration(md->qualifiedIdentifier(), md->range(), md);
            }
        }
    }
    delete module;
}

void DeclarationBuilder::visitForStatement(RubyAst *node)
{
    Node *aux = node->tree;
    node->tree = node->tree->cond;

    ExpressionVisitor ev(currentContext(), m_editor);
    ev.visitNode(node);
    AbstractType::Ptr type = ev.lastType();

    DUChainReadLocker rlock;
    if (type) {
        ClassType::Ptr ctype = type.cast<ClassType>();
        if (ctype && ctype->contentType())
            type = ctype->contentType().abstractType();
        else
            type = getBuiltinsType("Object", currentContext());
    } else
        type = getBuiltinsType("Object", currentContext());

    node->tree = aux->r;
    for (Node *n = node->tree; n != nullptr; n = n->next) {
        node->tree = n;
        QualifiedIdentifier id = getIdentifier(node);
        rlock.unlock();
        declareVariable(id, type, node);
        rlock.lock();
    }
    node->tree = aux;
}

void DeclarationBuilder::visitAccessSpecifier(const short int policy)
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
        for (Node *aux = n->l; aux != nullptr; aux = aux->next, i++) {
            node->tree = aux;
            ev.visitNode(node);

            DUChainWriteLocker wlock;
            YieldType yt = { ev.lastType()->indexed() };
            mDecl->replaceYieldTypes(yt, i);
            wlock.unlock();
        }
    }
    node->tree = n;
}

void DeclarationBuilder::visitRescueArg(RubyAst *node)
{
    AbstractType::Ptr type(nullptr);
    ModuleDeclaration *mDecl = nullptr;
    Node *n = node->tree;
    node->tree = n->l;

    /* If there's no rescue variable, don't even care. */
    if (!n->r)
        return;

    /* Get the type of the exception list. */
    for (node->tree = n->l; node->tree; node->tree = node->tree->next) {
        ExpressionVisitor ev(currentContext(), m_editor);
        ev.visitNode(node);
        mDecl = dynamic_cast<ModuleDeclaration *>(ev.lastDeclaration().data());
        if (mDecl)
            type = mergeTypes(type, mDecl->indexedType().abstractType());
    }

    node->tree = n->r;
    const QualifiedIdentifier &id = getIdentifier(node);
    declareVariable(id, type, node);
}

const KDevelop::RangeInRevision DeclarationBuilder::getNameRange(const RubyAst *node) const
{
    return m_editor->findRange(rb_name_node(node->tree));
}

void DeclarationBuilder::openContextForClassDefinition(RubyAst *node)
{
    RangeInRevision range = editorFindRange(node, node);
    KDevelop::QualifiedIdentifier className(getName(node));

    DUChainWriteLocker wlock;
    openContext(node, range, DUContext::Class, className);
    currentContext()->setLocalScopeIdentifier(className);
}

template<typename T>
T * DeclarationBuilder::reopenDeclaration(const QualifiedIdentifier &id,
                                          const RangeInRevision &range,
                                          DUContext *context,
                                          DeclarationKind kind)
{
    Declaration *res = nullptr;
    DUChainReadLocker rlock;
    QList<Declaration *> decls = context->findDeclarations(id);
    rlock.unlock();

    foreach (Declaration *d, decls) {
        Declaration *fitting = dynamic_cast<T*>(d);
        if (fitting) {
            const bool valid = validReDeclaration(d, id, range, kind);
            if (!valid)
                return nullptr;

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

    if (!res) {
        DUChainWriteLocker lock;
        injectContext(context);
        res = openDeclaration<T>(id, range);
        closeInjectedContext();
    }
    return static_cast<T*>(res);
}

MethodDeclaration * DeclarationBuilder::reopenDeclaration(const QualifiedIdentifier &id,
                                                          const RangeInRevision &range,
                                                          bool classMethod)
{
    DUChainReadLocker rlock;
    Declaration *res = nullptr;

    /**
     * Just get declarations from the current context. Moreover, we don't
     * want declarations from imported contexts either (base classes).
     */
    QList<Declaration *> decls = currentContext()->findLocalDeclarations(id.first(), range.start);
    rlock.unlock();
    foreach (Declaration *d, decls) {
        MethodDeclaration *method = dynamic_cast<MethodDeclaration *>(d);
        if (method && (method->isClassMethod() == classMethod)) {
            debug() << "Reopening the following method: " << d->toString();
            openDeclarationInternal(method);
            method->setRange(range);
            setEncountered(method);
            res = d;
            break;
        }
    }

    if (!res) {
        DUChainWriteLocker lock;
        res = openDeclaration<MethodDeclaration>(id, range);
    }
    return static_cast<MethodDeclaration *>(res);
}

void DeclarationBuilder::declareVariable(const QualifiedIdentifier &id,
                                         const AbstractType::Ptr &type,
                                         RubyAst *node,
                                         DUContext::SearchFlag flags)
{
    RangeInRevision range;
    Node *aux = node->tree;
    QualifiedIdentifier rId(id);
    VariableDeclaration *dec = nullptr;
    bool hintContainer = false;

    /* Take care of the special a[...] case */
    if (aux->kind == token_array_value) {
        node->tree = aux->l;
        rId = getIdentifier(node);
        hintContainer = true;
    }
    range = editorFindRange(node, node);

    if ((is_ivar(node->tree) || is_cvar(node->tree)) && !m_classDeclarations.isEmpty()) {
        DUChainWriteLocker wlock;
        DUContext *internal = m_classDeclarations.last()->internalContext();
        DUContext *previousCtx = currentContext();
        injectContext(internal);
        VariableDeclaration *var = reopenDeclaration<VariableDeclaration>(rId, range, currentContext());
        var->setRange(RangeInRevision(internal->range().start, internal->range().start));
        var->setAutoDeclaration(true);
        previousCtx->createUse(var->ownIndex(), range);
        var->setVariableKind(node->tree);
        var->setKind(Declaration::Instance);
        AbstractType::Ptr atype = mergeTypes(var->abstractType(), type);
        UnsureType::Ptr utype = atype.cast<UnsureType>();
        if (!utype || utype->typesSize() > 0)
            var->setType(atype);
        else
            var->setType(getBuiltinsType("Object", currentContext()));
        wlock.unlock();
        DeclarationBuilderBase::closeDeclaration();
        wlock.lock();
        closeInjectedContext();
        node->tree = aux;
        return;
    }

    /* Let's check if this variable is already declared */
    DUChainWriteLocker wlock;
    QList<Declaration *> decs = currentContext()->findDeclarations(rId.first(), startPos(node), nullptr, flags);
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

    if (is_global_var(node->tree))
        injectContext(topContext());
    dec = openDefinition<VariableDeclaration>(rId, range);
    dec->setVariableKind(node->tree);
    dec->setKind(Declaration::Instance);
    dec->setType(type);
    wlock.unlock();
    DeclarationBuilderBase::closeDeclaration();
    wlock.lock();
    if (is_global_var(node->tree))
        closeInjectedContext();

    node->tree = aux;
}

void DeclarationBuilder::aliasMethodDeclaration(const QualifiedIdentifier &id,
                                                const RangeInRevision &range,
                                                const MethodDeclaration *decl)
{
    setComment(decl->comment());
    MethodDeclaration *alias = openDeclaration<MethodDeclaration>(id, range);
    alias->setType(decl->type<FunctionType>());
    closeDeclaration();
}

ModuleDeclaration * DeclarationBuilder::getModuleDeclaration(RubyAst *module) const
{
    ExpressionVisitor ev(currentContext(), m_editor);
    Declaration *d;

    ev.visitNode(module);
    d = ev.lastDeclaration().data();
    ModuleDeclaration *found = dynamic_cast<ModuleDeclaration *>(d);
    return found;
}

QList<MethodDeclaration *> DeclarationBuilder::getDeclaredMethods(const Declaration *decl)
{
    DUChainReadLocker rlock;
    QList<MethodDeclaration *> res;
    DUContext *internal = decl->internalContext();
    if (!internal)
        return res;

    QVector<Declaration *> decls = internal->localDeclarations();
    foreach (Declaration *d, decls) {
        MethodDeclaration *md = dynamic_cast<MethodDeclaration *>(d);
        if (md)
            res << md;
    }
    return res;
}

bool DeclarationBuilder::validReDeclaration(Declaration *decl, const QualifiedIdentifier &id,
                                            const RangeInRevision &range, DeclarationKind kind)
{
    // Check that we'll deal just with a class or a module.
    if (kind != Class && kind != Module)
        return true;
    ModuleDeclaration *md = dynamic_cast<ModuleDeclaration *>(decl);
    if (!md)
        return true;

    // Now let's check that we're not trying to redeclare a class as
    // a module and viceversa.
    const bool mod = md->isModule();
    if ((mod && kind == Class) || (!mod && kind == Module)) {
        const QString str = (kind == Class) ? "class" : "module";
        const QString msg = i18n("TypeError: %1 is not a %2", id.toString(), str);

        appendProblem(range, msg);
        return false;
    }
    return true;
}

DUContext * DeclarationBuilder::getContainedNameContext(RubyAst *node)
{
    Node *aux = node->tree;
    Node *last = aux->r->last;
    DUContext *ctx = currentContext();
    ExpressionVisitor ev(currentContext(), m_editor);

    if (!last)
        return ctx;
    for (Node *n = aux->r; n != last; n = n->next) {
        node->tree = n;
        ev.visitNode(node);
        const DeclarationPointer d = ev.lastDeclaration();
        if (d) {
            ctx = d->internalContext();
            ev.setContext(ctx);
        } else
            break;
    }
    node->tree = aux;
    return ctx;
}

void DeclarationBuilder::visitMethodCallArgs(const RubyAst *mc, const DeclarationPointer &lastMethod)
{
    DUChainReadLocker rlock;
    RubyAst *node = new RubyAst(mc->tree->r, mc->context);
    VariableDeclaration *vd;
    int total, left = 0, right = 0;
    bool mark = false, starSeen = false;

    DUContext *argCtx = nullptr;
    if (lastMethod.data())
        argCtx = DUChainUtils::getArgumentContext(lastMethod.data());
    if (!argCtx || !lastMethod->type<FunctionType>()) {
        /*
         * We couldn't get enough info, visit the list of parameters as a
         * regular list and get out.
         */
        for (Node *n = node->tree; n; n = n->next) {
            node->tree = n;
            rlock.unlock();
            DeclarationBuilderBase::visitNode(node);
            rlock.lock();
        }
        delete node;
        return;
    }

    QVector<Declaration *> args = argCtx->localDeclarations();
    rlock.unlock();
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
    DUChainWriteLocker wlock;
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
            if (!ct) {// TODO: shouldn't happen but it does :(
                n = n->next;
                continue;
            }
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
        wlock.unlock();
        DeclarationBuilderBase::visitNode(node);
        wlock.lock();
        av.visitNode(node);
        AbstractType::Ptr last = av.lastType().cast<AbstractType>();
        AbstractType::Ptr original = args.at(i)->abstractType();
        args.at(i)->setType(mergeTypes(original, last));
        n = n->next;
    }
    delete node;
}

} // End of namespace Ruby
