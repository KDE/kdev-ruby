/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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
    QString name("");

    /* Get the name of the file and update the cache of search paths. */
    name = editor->tokenToString(node);
    if (name.startsWith("'") || name.startsWith("\""))
        name.replace(name[0], ""); // remove surrounding '
    if (!name.endsWith(".rb"))
        name += ".rb";
    searchPaths << editor->url().toUrl().directory();
    if (!local) {
        fillUrlCache();
        searchPaths << m_urlCache.first;
    }

    /* Check first in the standard search path */
    int i = 0;
    foreach (const KUrl &path, searchPaths) {
        QString url = path.path(KUrl::AddTrailingSlash) + name;
        QFile script(url);
        QFileInfo info(url);
        if (script.exists() && !info.isDir()) {
            /* Sort the cache to break this loop sooner next time. */
            if (i > 1) {
                m_urlCache.first.prepend(m_urlCache.first.at(i - 1));
                m_urlCache.first.removeAt(i);
            }
            KUrl res(url);
            res.cleanPath();
            return res;
        }
        i++;
    }
    if (local)
        return KUrl();

    /*
     * This is not a local search and we haven't found it yet, go for the gems.
     */
    name.chop(3); // .rb
    return getGem(name);
}

KUrl Loader::getGem(const QString &name)
{
    const QString &real = name + ".rb";
    QStringList filter;

    if (name.isEmpty())
      return KUrl();

    filter = QStringList() << QString(name[0]) + "*";
    foreach (const KUrl &path, m_urlCache.second) {
        QString basePath = path.path(KUrl::AddTrailingSlash);
        QDir dir(basePath);
        QStringList list = dir.entryList(filter, QDir::Dirs);
        foreach (const QString &inside, list) {
            QString url = basePath + inside + "/lib/" + real;
            QFile script(url);
            QFileInfo info(url);
            if (script.exists() && !info.isDir()) {
                KUrl res(url);
                res.cleanPath();
                return res;
            }
        }
    }
    return KUrl();
}

QList<IncludeItem> Loader::getFilesInSearchPath(const QString &url, const QString &hint, const KUrl &relative)
{
    int number = 0;
    QList<IncludeItem> res;
    QList<KUrl> paths;

    if (relative.isEmpty()) {
        fillUrlCache();
        paths = m_urlCache.first;

        /* Gem paths need some extra work :P */
        foreach (const KUrl &path, m_urlCache.second) {
            QString basePath = path.path(KUrl::AddTrailingSlash);
            QDir dir(basePath);
            QStringList list = dir.entryList(QStringList() << hint + "*");
            foreach (const QString &inside, list)
                paths << basePath + inside + "/lib/";
        }
    } else
        paths << relative;

    foreach (const KUrl &path, paths) {
        QString p = path.path(KUrl::AddTrailingSlash) + url;
        QDirIterator it(p);
        while (it.hasNext()) {
            it.next();
            IncludeItem item;
            item.name = it.fileInfo().fileName();
            if (item.name.startsWith(".") || item.name.endsWith("~")
                || item.name.endsWith(".so")) {
                continue;
            }
            item.pathNumber = number;
            item.isDirectory = it.fileInfo().isDir();
            item.basePath = p;
            res << item;
        }
        number++;
    }
    return res;
}

void Loader::fillUrlCache()
{
    int it;
    QProcess ruby;
    QStringList code;
    QList<QByteArray> rpaths, epaths;

    if (urlsCached())
        return;
    m_urlCache.first = QList<KUrl>();
    m_urlCache.second = QList<KUrl>();

    code << "ruby" << "-e" << "puts $:; STDERR.puts Gem.path";
    ruby.start("/usr/bin/env", code);
    ruby.waitForFinished();
    rpaths = ruby.readAllStandardOutput().split('\n');
    epaths = ruby.readAllStandardError().split('\n');

    /* For both rpaths and epaths, the last item is empty */
    for (it = 0; it < rpaths.size() - 1; it++)
        m_urlCache.first << KUrl(rpaths.at(it));
    for (it = 0; it < epaths.size() - 1; it++)
        m_urlCache.second << KUrl(epaths.at(it) + "/gems");
}

} // End of namespace Ruby
