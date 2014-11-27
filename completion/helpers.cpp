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


#include <KTextEditor/Document>
#include <KTextEditor/ConfigInterface>
#include <language/duchain/ducontext.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainutils.h>
#include <completion/helpers.h>


using namespace KDevelop;

namespace ruby
{

const QString indentString(KTextEditor::Document *document)
{
    KTextEditor::ConfigInterface *iface = qobject_cast<KTextEditor::ConfigInterface *>(document);
    if (iface->configValue("replace-tabs").toBool()) {
        return QString(iface->configValue("indent-width").toUInt(), ' ');
    }
    return "\t";
}

QString getIndendation(const QString &line)
{
    return line.left(line.indexOf(QRegExp("\\S"), 0));
}

QString getArgumentList(Declaration *decl, QList<QVariant> *highlighting)
{
    Q_UNUSED(highlighting); // TODO
    QString ret("(");
    QVector<Declaration *> params;

    if (DUContext *ctx = DUChainUtils::getArgumentContext(decl))
        params = ctx->localDeclarations();

    // TODO: this is just too simplistic

    bool first = true;
    foreach (Declaration *d, params) {
        if (first) {
            first = false;
        } else {
            ret += ", ";
        }
        ret += d->identifier().toString();
    }
    ret += ")";
    return ret;
}

}
