/* This file is part of KDevelop
 *
 * Copyright (C) 2011 Miquel Sabaté <mikisabate@gmail.com>
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


// Qt + KDE
#include <QtCore/QProcess>
#include <KStandardDirs>

// KDevelop
#include <language/duchain/identifier.h>
#include <language/duchain/duchain.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/types/unsuretype.h>
#include <language/duchain/types/integraltype.h>

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>
#include <duchain/declarations/methoddeclaration.h>


namespace Ruby
{
using namespace KDevelop;

const IndexedString & internalBuiltinsFile()
{
    static IndexedString doc_url(KStandardDirs::locate("data",
                                "kdevrubysupport/documentation/builtins.rb"));
    return doc_url;
}

const QString getName(RubyAst *ast)
{
    return QString(rb_name_node(ast->tree)->name);
}

const QByteArray getComment(RubyAst *ast)
{
    char *m_comment = ast->tree->comment;
    return (m_comment != NULL) ? QByteArray(m_comment) : QByteArray("");
}

Declaration * getDeclaration(const QualifiedIdentifier &id, const RangeInRevision &range, DUContextPointer context)
{
    QList<Declaration *> decls;

    {
        /*
         * Find the declarations at the topContext(). If no declaration was
         * found, we have to look for local declarations. If this fails, we
         * should find for global declarations.
         */
        DUChainReadLocker lock(DUChain::lock());
        if (context.data() == context->topContext())
            decls = context->topContext()->findDeclarations(id, range.end);
        else
            decls = context->topContext()->findDeclarations(id, CursorInRevision::invalid());
        if (!decls.length()) {
            decls = context->findLocalDeclarations(id.last(), range.end);
            if (!decls.length())
                decls = context->findDeclarations(id.last(), range.end);
        }
    }
    return (decls.length()) ? decls.last() : NULL;
}

KUrl getRequiredFile(Node *node, const EditorIntegrator *editor, bool local)
{
    QList<KUrl> searchPaths;
    QList<KUrl> gemPaths;
    QString name(""), base("");

    // TODO: by now take a look at the current directory if this is not a string
    // TODO: instead of the current directory, pick the project root directory
    if (node->kind != token_string) {
        searchPaths << editor->url().toUrl().directory();
    } else {
        name = editor->tokenToString(node);
        name.replace("'", ""); // remove surrounding '
        base = name;
        if (!name.endsWith(".rb"))
            name += ".rb";
        if (local)
            searchPaths << editor->url().toUrl().directory();
        else {
            const QPair<QList<KUrl>, QList<KUrl> > &p = getSearchPaths();
            searchPaths << p.first;
            gemPaths << p.second;
        }
    }

    QStringList filter;
    filter << base + "*";
    foreach (const KUrl &path, gemPaths) {
        QString basePath = path.path(KUrl::AddTrailingSlash) + "gems/";
        QDir dir(basePath);
        QStringList list = dir.entryList(filter, QDir::Dirs);
        foreach (const QString &inside, list) {
            // TODO: right now it assumes that the /lib directory exists. Even
            // though this is a pretty standard situation, it's not necessarily true.
            QString url = basePath + inside + "/lib/" + name;
            QFile script(url);
            QFileInfo info(url);
            if (script.exists() && !info.isDir()) {
                KUrl res(url);
                res.cleanPath();
                return res;
            }
        }
    }

    foreach (const KUrl &path, searchPaths) {
        QString url = path.path(KUrl::AddTrailingSlash) + name;
        QFile script(url);
        QFileInfo info(url);
        if (script.exists() && !info.isDir()) {
            KUrl res(url);
            res.cleanPath();
            return res;
        }
    }

    return KUrl();
}

QPair<QList<KUrl>, QList<KUrl> > getSearchPaths()
{
    // TODO: Cache, cache, cache !!!
    QList<KUrl> paths;
    QList<KUrl> gpaths;

    QStringList code;
    code << "ruby" << "-e" << "puts $:; STDERR.puts Gem.path";
    QProcess ruby;
    ruby.start("/usr/bin/env", code);
    ruby.waitForFinished();
    QList<QByteArray> rpaths = ruby.readAllStandardOutput().split('\n');
    QList<QByteArray> epaths = ruby.readAllStandardError().split('\n');
    rpaths.removeAll("");
    epaths.removeAll("");
    foreach (const QString &s, rpaths)
        paths << s;
    foreach (const QString &s, epaths)
        gpaths << s;

    return QPair<QList<KUrl>, QList<KUrl> >(paths, gpaths);
}

QList<MethodDeclaration *> getDeclaredMethods(Declaration *decl)
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

bool isUsefulType(AbstractType::Ptr type)
{
    if (!type)
        return false;
    if (type->whichType() != AbstractType::TypeIntegral)
        return true;
    QList<uint> skipTypes;
    skipTypes << IntegralType::TypeMixed << IntegralType::TypeNone << IntegralType::TypeNull;
    if (!skipTypes.contains(type.cast<IntegralType>()->dataType()))
        return true;
    return false;
}

AbstractType::Ptr mergeTypes(AbstractType::Ptr type, AbstractType::Ptr newType)
{
    UnsureType::Ptr unsure = UnsureType::Ptr::dynamicCast(type);
    UnsureType::Ptr newUnsure = UnsureType::Ptr::dynamicCast(newType);
    UnsureType::Ptr res;

    if (unsure && newUnsure) {
        int len = newUnsure->typesSize();
        for (int i = 0; i < len; i++)
            unsure->addType(newUnsure->types()[i]);
        res = unsure;
    } else if (unsure) {
        if (isUsefulType(newType))
            unsure->addType(newType->indexed());
        res = unsure;
    } else if (newUnsure) {
        UnsureType::Ptr cloned = UnsureType::Ptr(static_cast<UnsureType *>(newUnsure->clone()));
        if (isUsefulType(type))
            cloned->addType(type->indexed());
        res = cloned;
    } else {
        unsure = UnsureType::Ptr(new UnsureType());
        if (isUsefulType(type))
            unsure->addType(type->indexed());
        if (isUsefulType(newType))
            unsure->addType(newType->indexed());
        res = unsure;
    }

    if (res->typesSize() == 1)
        return res->types()[0].abstractType();
    return AbstractType::Ptr::staticCast(res);
}

int nodeListSize(Node *node)
{
    int i = 0;
    for (Node *n = node; n != NULL; n = n->next, i++);
    return i;
}

} // End of namespace Ruby

