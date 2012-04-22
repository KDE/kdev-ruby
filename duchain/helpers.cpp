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

// Ruby
#include <duchain/helpers.h>
#include <duchain/editorintegrator.h>


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

Declaration *declarationForNode(const QualifiedIdentifier &id,
                                const RangeInRevision &range,
                                DUContextPointer context)
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
    QString name("");

    // TODO: by now take a look at the current directory if this is not a string
    // TODO: instead of the current directory, pick the project root directory
    if (node->kind != token_string) {
        searchPaths << editor->url().toUrl().directory();
    } else {
        name = editor->tokenToString(node);
        name.replace("'", ""); // remove surrounding '
        if (!name.endsWith(".rb"))
            name += ".rb";
        if (local)
            searchPaths << editor->url().toUrl().directory();
        else
            searchPaths << getSearchPaths();
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

QList<KUrl> getSearchPaths()
{
    // TODO: Cache, cache, cache !!!
    QList<KUrl> paths;

    QStringList code;
    code << "ruby" << "-e" << "puts $:";
    QProcess ruby;
    ruby.start("/usr/bin/env", code);
    ruby.waitForFinished();
    QList<QByteArray> rpaths = ruby.readAllStandardOutput().split('\n');
    rpaths.removeAll("");
    foreach (const QString &s, rpaths)
        paths << s;

    return paths;
}

} // End of namespace Ruby

