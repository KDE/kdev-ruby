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
#include <duchain/types/classtype.h>


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
    decl->clearBaseClass();
    m_accessPolicyStack.push(Declaration::Public);
    lastClassModule = decl;
    insideClassModule = true;
    openContextForClassDefinition(node);

    /*
     * Now let's check for the base class. Ruby does not support multiple
     * inheritance, and the access is always public.
     */
    Node *aux = node->tree;
    node->tree = node->tree->cond;
    if (node->tree) {
        QualifiedIdentifier baseId = getIdentifier(node);
        KDevelop::Declaration *baseDecl = declarationForNode(baseId, range, DUContextPointer(currentContext()));
        if (!baseDecl)
            appendProblem(node->tree, i18n("NameError: undefined local variable or method `%1'", baseId.toString()));
        else {
            ClassDeclaration *realClass = dynamic_cast<ClassDeclaration *>(baseDecl);
            if (!realClass)
                appendProblem(node->tree, i18n("TypeError: wrong argument type (expected Class)"));
            else {
                currentContext()->addImportedParentContext(realClass->internalContext());
                decl->setBaseClass(realClass->indexedType());
            }
        }
    }
    node->tree = aux;

    /*  Setup types and go for the class body */
    ClassType::Ptr type = ClassType::Ptr(new ClassType());
    type->setDeclaration(decl);
    decl->setType(type);
    openType(type);

    decl->setInternalContext(currentContext());
    DeclarationBuilderBase::visitClassStatement(node);
    closeContext();

    closeType();
    closeDeclaration();
    insideClassModule = false;
    m_accessPolicyStack.pop();
}

void DeclarationBuilder::visitModuleStatement(RubyAst* node)
{
    DUChainWriteLocker lock(DUChain::lock());
    RangeInRevision range = getNameRange(node);
    QualifiedIdentifier id = getIdentifier(node);

    setComment(getComment(node));
    ModuleDeclaration *decl = openDeclaration<ModuleDeclaration>(id, range);
    decl->clearModuleMixins();
    decl->setKind(KDevelop::Declaration::Type);
    m_accessPolicyStack.push(Declaration::Public);
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
    m_accessPolicyStack.pop();
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
    if (currentContext()->type() == DUContext::Class)
        decl->setAccessPolicy(currentAccessPolicy());

    openType(type);
    decl->setInSymbolTable(false);
    DeclarationBuilderBase::visitMethodStatement(node);
    closeDeclaration();
    closeType();

    /*
     * In Ruby, a method returns the last expression if no return expression
     * has been fired. Thus, the type of the last expression has to be mixed
     * into the return type of this method.
     */
    if (node->tree->l) {
        node->tree = get_last_expr(node->tree->l);
        if (node->tree->kind != token_return) {
            ExpressionVisitor ev(currentContext(), m_editor);
            ev.visitNode(node);
            if (ev.lastType())
                type->setReturnType(mergeTypes(ev.lastType(), type->returnType()));
        }
    }
    if (!type->returnType())
        type->setReturnType(AbstractType::Ptr(new IntegralType(IntegralType::TypeNull)));
    decl->setType(type);
}

void DeclarationBuilder::visitParameter(RubyAst *node)
{
    MethodDeclaration *mDecl = dynamic_cast<MethodDeclaration *>(currentDeclaration());
    ExpressionVisitor ev(currentContext(), m_editor);
    ev.visitParameter(node);
    AbstractType::Ptr type = ev.lastType();

    /* Just grab the left side if this is an optional parameter */
    if (node->tree->l) {
        Node *aux = node->tree->l;
        node->tree = node->tree->r;
        // TODO: for some reason, it assumes that *all* the parameters have this same default value :S
        mDecl->addDefaultParameter(IndexedString(m_editor->tokenToString(node->tree)));
        node->tree = aux;
    }

    /* Finally, declare the parameter */
    FunctionType::Ptr mType = currentType<FunctionType>();
    if (mType) {
        mType->addArgument(type);
        declareVariable(currentContext(), type, getIdentifier(node), node);
    }
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
        node->tree = node->tree->l;
        if (!hasCurrentType()) {
            appendProblem(node->tree, "Return statement not within function declaration");
            return;
        }
        TypePtr<FunctionType> t = currentType<FunctionType>();
        ExpressionVisitor ev(currentContext(), m_editor);
        ev.visitNode(node);
        AbstractType::Ptr type = mergeTypes(ev.lastType(), t->returnType());
        t->setReturnType(type);
    }
    setLastType(AbstractType::Ptr(0));
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
            QualifiedIdentifier qi = ct.unsafeData()->declaration(m_topContext)->qualifiedIdentifier();
            lock.unlock();
            if (qi == QualifiedIdentifier("Array")) {
                for (Node *n = node->tree->l; n != NULL; n = n->next) {
                    aux->tree = n;
                    QualifiedIdentifier id = getIdentifier(aux);
                    declareVariable(currentContext(), ct->contentType().abstractType(), id, aux);
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
        aux->tree = n;
        if (has_star(n)) {
            int rest = nodeListSize(n) - 1;
            int pack = rsize - i - rest;
            ClassType::Ptr newType = getArray().cast<ClassType>();
            for (int j = pack; j > 0; j--, i++)
                newType->addContentType(values.at(i));
            i--;
            if (!is_just_a_star(n)) {
                QualifiedIdentifier id = getIdentifier(aux);
                declareVariable(currentContext(), newType.cast<AbstractType>(), id, aux);
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
            for (Node *n = aux->tree; n != NULL && i < args.size(); n = n->next, i++) {
                aux->tree = n;
                ExpressionVisitor av(currentContext(), m_editor);
                av.visitNode(aux);
                AbstractType::Ptr merged = mergeTypes(args.at(i)->abstractType(),
                                                      av.lastType().cast<AbstractType>());
                args.at(i)->setType(merged);
            }
            wlock.unlock();
        }
    }
}

void DeclarationBuilder::visitInclude(RubyAst *node)
{
    RubyAst *module = new RubyAst(node->tree->r, node->context);
    ModuleDeclaration *decl = getModuleDeclaration(module);

    // Register module mix-in
    registerModuleMixin(decl->indexedType(), true);

    // Include the instance methods
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
    ModuleDeclaration *decl = getModuleDeclaration(module);

    // Register module mix-in
    registerModuleMixin(decl->indexedType(), false);

    // Include the class methods
    if (decl) {
        QList<MethodDeclaration *> eMethods = getDeclaredMethods(decl);
        foreach (MethodDeclaration *md, eMethods) {
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

void DeclarationBuilder::visitLambda(RubyAst *node)
{
    Ruby::RubyAstVisitor::visitLambda(node);
}

void DeclarationBuilder::visitForStatement(RubyAst *node)
{
    RubyAstVisitor::visitForStatement(node);
    RubyAst *aux = new RubyAst(node->tree->l, node->context);
    ExpressionVisitor ev(currentContext(), m_editor);
    ev.visitNode(aux);
    AbstractType::Ptr type = ev.lastType();
    if (type) {
        ClassType::Ptr ctype = type.cast<ClassType>();
        if (ctype && ctype->contentType())
            type = ctype->contentType().abstractType();
        else
            type = AbstractType::Ptr(new ObjectType);
    } else
        type = AbstractType::Ptr(new ObjectType);

    for (Node *n = node->tree->r; n != NULL; n = n->next) {
        aux->tree = n;
        QualifiedIdentifier id = getIdentifier(aux);
        declareVariable(currentContext(), type, id, aux);
    }
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
    alias->setType(decl->type<FunctionType>());
    closeDeclaration();
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

ModuleDeclaration * DeclarationBuilder::getModuleDeclaration(const RubyAst *module)
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
    ModuleDeclaration *lastDecl = NULL;

    if (aux->tree->kind == token_method_call)
        aux->tree = aux->tree->l;
    for (Node *n = aux->tree; n != NULL; n = n->next) {
        QualifiedIdentifier id = getIdentifier(aux);
        QList<Declaration *> list = lastCtx->findDeclarations(id.last());
        if (!list.empty()) {
            ModuleDeclaration *d = dynamic_cast<ModuleDeclaration *>(list.last());
            if (!d) {
                rlock.unlock();
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

void DeclarationBuilder::registerModuleMixin(IndexedType type, bool include)
{
    if (lastClassModule) {
        ModuleDeclaration *current = dynamic_cast<ModuleDeclaration *>(lastClassModule);
        if (current) {
            ModuleMixin mixin;
            mixin.included = include;
            mixin.module = type;
            current->addModuleMixin(mixin);
        }
    } else {
        // TODO: register to the Kernel module
    }
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

} // End of namespace Ruby
