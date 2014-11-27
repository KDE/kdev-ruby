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


#include <QtCore/QProcess>
#include <QtCore/QDirIterator>
#include <parser/node.h>
#include <duchain/loader.h>
#include <duchain/editorintegrator.h>


namespace ruby
{

QList<KDevelop::Path> Loader::m_rubyPath;
QList<KDevelop::Path> Loader::m_gemPath;

KDevelop::Path Loader::getRequiredFile(Node *node,
                                       const EditorIntegrator *editor,
                                       bool local)
{
    QList<KDevelop::Path> searchPaths;
    QString name("");

    /* Get the name of the file and update the cache of search paths. */
    name = editor->tokenToString(node);
    if (name.startsWith(QStringLiteral("'"))
            || name.startsWith(QStringLiteral("\""))) {
        name.replace(name[0], ""); // remove surrounding '
    }
    if (!name.endsWith(QStringLiteral(".rb"))) {
        name += ".rb";
    }
    searchPaths << KDevelop::Path(editor->url().toUrl()).parent();
    if (!local) {
        fillUrlCache();
        searchPaths << m_rubyPath;
    }

    /* Check first in the standard search path */
    int i = 0;
    foreach (const KDevelop::Path &path, searchPaths) {
        KDevelop::Path url(path, name);
        QFile script(url.path());
        QFileInfo info(url.path());
        if (script.exists() && !info.isDir()) {
            /* Sort the cache to break this loop sooner next time. */
            if (i > 1) {
                m_rubyPath.prepend(m_rubyPath.at(i - 1));
                m_rubyPath.removeAt(i);
            }
            return url;
        }
        i++;
    }
    if (local) {
        return KDevelop::Path();
    }

    /*
     * This is not a local search and we haven't found it yet, go for the gems.
     */
    name.chop(3); // .rb
    return getGem(name);
}

QList<KDevelop::IncludeItem> Loader::getFilesInSearchPath(const QString &url,
                                                          const QString &hint,
                                                          const KDevelop::Path &relative)
{
    int number = 0;
    QList<KDevelop::Path> paths;
    QList<KDevelop::IncludeItem> res;

    if (relative.isValid()) {
        paths << relative;
    } else {
        fillUrlCache();
        paths = m_rubyPath;

        /* Gem paths need some extra work :P */
        foreach (const KDevelop::Path &path, m_gemPath) {
            QDir dir(path.path() + "/");
            QStringList list = dir.entryList(QStringList() << hint + "*");
            foreach (const QString &inside, list) {
                paths << KDevelop::Path(path, inside + "lib");
            }
        }
    }

    foreach (const KDevelop::Path &path, paths) {
        KDevelop::Path aux(path, url);
        QDirIterator it(aux.path());

        while (it.hasNext()) {
            it.next();
            KDevelop::IncludeItem item;
            item.name = it.fileInfo().fileName();
            if (item.name.startsWith(QStringLiteral("."))
                    || item.name.endsWith(QStringLiteral("~"))
                    || item.name.endsWith(QStringLiteral(".so"))) {
                continue;
            }
            item.pathNumber = number;
            item.isDirectory = it.fileInfo().isDir();
            item.basePath = aux.toUrl();
            res << item;
        }
        number++;
    }
    return res;
}

KDevelop::Path Loader::getGem(const QString &name)
{
    const QString &real = name + QStringLiteral(".rb");
    QStringList filter;

    if (name.isEmpty()) {
      return KDevelop::Path();
    }

    filter = QStringList() << QString(name[0]) + "*";
    foreach (const KDevelop::Path &path, m_gemPath) {
        QDir dir(path.path());
        QStringList list = dir.entryList(filter, QDir::Dirs);
        int i = 0;
        foreach (const QString &inside, list) {
            KDevelop::Path url(path, inside + "/lib/" + real);
            QFile script(url.path());
            QFileInfo info(url.path());
            if (script.exists() && !info.isDir()) {
                /* Sort the cache to break this loop sooner next time. */
                if (i > 1) {
                    m_gemPath.prepend(m_gemPath.at(i - 1));
                    m_gemPath.removeAt(i);
                }
                return url;
            }
            i++;
        }
    }
    return KDevelop::Path();
}


void Loader::fillUrlCache()
{
    int it;
    QProcess ruby;
    QStringList code;
    QList<QByteArray> rpaths, epaths;

    if (urlsCached()) {
        return;
    }
    m_rubyPath = QList<KDevelop::Path>();
    m_gemPath = QList<KDevelop::Path>();

    code << "ruby" << "-e" << "puts $:; STDERR.puts Gem.path";
    ruby.start(QStringLiteral("/usr/bin/env"), code);
    ruby.waitForFinished();
    rpaths = ruby.readAllStandardOutput().split('\n');
    epaths = ruby.readAllStandardError().split('\n');

    /* For both rpaths and epaths, the last item is empty */
    for (it = 0; it < rpaths.size() - 1; it++) {
        m_rubyPath << KDevelop::Path(rpaths.at(it));
    }
    for (it = 0; it < epaths.size() - 1; it++) {
        KDevelop::Path aux(epaths.at(it));
        aux.addPath(QStringLiteral("gems"));
        m_rubyPath << aux;
    }
}

}
