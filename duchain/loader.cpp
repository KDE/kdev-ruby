/* This file is part of KDevelop
 *
 * Copyright (C) 2012  Miquel Sabaté <mikisabate@gmail.com>
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


// Qt
#include <QtCore/QProcess>
#include <QtCore/QDirIterator>

// Ruby
#include <duchain/loader.h>
#include <duchain/editorintegrator.h>


namespace Ruby
{

QPair<QList<KUrl>, QList<KUrl> > Loader::m_urlCache;

KUrl Loader::getRequiredFile(Node *node, const EditorIntegrator *editor, bool local)
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

QList<IncludeItem> Loader::getFilesInSearchPath(const QString &url, bool relative)
{
    QList<IncludeItem> res;
    QList<KUrl> paths = getSearchPaths().first;
    int number = 0;

    foreach (const KUrl &path, paths) {
        QString p = path.path(KUrl::AddTrailingSlash) + url;
        QDirIterator it(p);
        while (it.hasNext()) {
            it.next();
            IncludeItem item;
            item.name = it.fileInfo().fileName();
            if (item.name.startsWith(".") || item.name.endsWith("~"))
                continue;
            item.pathNumber = number;
            item.isDirectory = it.fileInfo().isDir();
            item.basePath = p;
            res << item;
        }
        number++;
    }
    return res;
}

QPair<QList<KUrl>, QList<KUrl> > Loader::getSearchPaths()
{
    if (urlsCached())
        return m_urlCache;

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

    m_urlCache.first = paths;
    m_urlCache.second = gpaths;
    return QPair<QList<KUrl>, QList<KUrl> >(paths, gpaths);
}

} // End of namespace Ruby
