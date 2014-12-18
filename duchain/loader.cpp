/* This file is part of KDevelop
 *
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#include <duchain/loader.h>

#include <QtCore/QDirIterator>
#include <QtCore/QProcess>

#include <duchain/editorintegrator.h>
#include <parser/node.h>

namespace ruby {

QList<KDevelop::Path> Loader::s_rubyPath;
QList<KDevelop::Path> Loader::s_gemPath;

KDevelop::Path Loader::getRequiredFile(Node *node,
                                       const EditorIntegrator *editor,
                                       bool local)
{
    QList<KDevelop::Path> searchPaths;

    // Get the name of the file and update the cache of search paths.
    auto name = editor->tokenToString(node);
    if (name.startsWith(QStringLiteral("'")) ||
        name.startsWith(QStringLiteral("\""))) {

        // remove surrounding '
        name.replace(name[0], "");
    }
    if (!name.endsWith(QStringLiteral(".rb"))) {
        name += ".rb";
    }
    searchPaths << KDevelop::Path(editor->url().toUrl()).parent();
    if (!local) {
        fillUrlCache();
        searchPaths << s_rubyPath;
    }

    // Check first in the standard search path.
    int i = 0;
    for (const KDevelop::Path &path : searchPaths) {
        KDevelop::Path url(path, name);
        QFile script(url.path());
        QFileInfo info(url.path());
        if (script.exists() && !info.isDir()) {
            // Sort the cache to break this loop sooner next time.
            if (i > 1) {
                s_rubyPath.prepend(s_rubyPath.at(i - 1));
                s_rubyPath.removeAt(i);
            }
            return url;
        }
        i++;
    }
    if (local) {
        return KDevelop::Path();
    }

    // This is not a local search and we haven't found it yet, go for the gems.
    name.chop(3); // .rb
    return getGem(name);
}

QVector<KDevelop::IncludeItem>
Loader::getFilesInSearchPath(const QString &url,
                             const QString &hint,
                             const KDevelop::Path &relative)
{
    int number = 0;
    QList<KDevelop::Path> paths;
    QVector<KDevelop::IncludeItem> res;

    if (relative.isValid()) {
        paths << relative;
    } else {
        fillUrlCache();
        paths = s_rubyPath;

        /* Gem paths need some extra work :P */
        foreach (const KDevelop::Path &path, s_gemPath) {
            QDir dir(path.path() + "/");
            QStringList list = dir.entryList(QStringList() << hint + "*");
            foreach (const QString &inside, list) {
                paths << KDevelop::Path(path, inside + "lib");
            }
        }
    }

    for (const KDevelop::Path &path : paths) {
        KDevelop::Path aux(path, url);
        QDirIterator it(aux.path());

        while (it.hasNext()) {
            it.next();
            KDevelop::IncludeItem item;
            item.name = it.fileInfo().fileName();
            if (item.name.startsWith(QStringLiteral(".")) ||
                item.name.endsWith(QStringLiteral("~")) ||
                item.name.endsWith(QStringLiteral(".so"))) {

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
    if (name.isEmpty()) {
      return KDevelop::Path();
    }

    QStringList filter{ QString(name[0]) + "*" };
    const QString &real = name + QStringLiteral(".rb");

    for (const KDevelop::Path &path : s_gemPath) {
        QDir dir(path.path());
        QStringList list = dir.entryList(filter, QDir::Dirs);
        int i = 0;
        for (const QString &inside : list) {
            KDevelop::Path url(path, inside + "/lib/" + real);
            QFile script(url.path());
            QFileInfo info(url.path());
            if (script.exists() && !info.isDir()) {
                // Sort the cache to break this loop sooner next time.
                if (i > 1) {
                    s_gemPath.prepend(s_gemPath.at(i - 1));
                    s_gemPath.removeAt(i);
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
    QProcess ruby;
    QList<QByteArray> rpaths, epaths;

    if (urlsCached()) {
        return;
    }
    s_rubyPath = {};
    s_gemPath = {};

    QStringList code{ "ruby", "-e", "puts $:; STDERR.puts Gem.path" };
    ruby.start(QStringLiteral("/usr/bin/env"), code);
    ruby.waitForFinished();
    rpaths = ruby.readAllStandardOutput().split('\n');
    epaths = ruby.readAllStandardError().split('\n');

    /* For both rpaths and epaths, the last item is empty */
    for (int it = 0; it < rpaths.size() - 1; it++) {
        s_rubyPath << KDevelop::Path(rpaths.at(it));
    }
    for (int it = 0; it < epaths.size() - 1; it++) {
        KDevelop::Path aux(epaths.at(it));
        aux.addPath(QStringLiteral("gems"));
        s_rubyPath << aux;
    }
}

}
