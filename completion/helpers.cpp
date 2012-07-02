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


#include <language/duchain/declaration.h>
#include <language/duchain/duchainutils.h>
#include <completion/helpers.h>


using namespace KDevelop;

namespace Ruby
{

QString getIndendation(const QString &line)
{
    return line.left(line.indexOf(QRegExp("\\S"), 0));
}

QString getArgumentList(Declaration *decl, QList<QVariant> *highlighting)
{
    QString ret = "(";
    QVector<Declaration *> params;

    if (DUContext *ctx = DUChainUtils::getArgumentContext(decl))
        params = ctx->localDeclarations();

    // TODO: this is just too simplistic

    bool first = true;
    foreach (Declaration *d, params) {
        if (first)
            first = false;
        else
            ret += ", ";
        ret += d->identifier().toString();
    }
    ret += ")";
    return ret;
}

} // End of namespace Ruby
