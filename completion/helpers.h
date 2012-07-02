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


#ifndef RUBYCOMPLETIONHELPERS_H
#define RUBYCOMPLETIONHELPERS_H


#include <QtCore/QList>
#include <QtCore/QVariant>
#include <completion/completionexport.h>


namespace KDevelop {
    class Declaration;
}

namespace Ruby
{

class NormalItem;

/// Get the indentation of a given @p line.
QString KDEVRUBYCOMPLETION_EXPORT getIndendation(const QString &line);

/**
 * Get the representation of the arguments list of a method declaration.
 * @param decl The declaration of the method.
 * @param highlighting A list of the highlighted items of the text. You
 * usually want this list empty before calling this method.
 * @note the DUChain must be locked.
 * @returns a QString representing the argument list of the given method.
 */
QString KDEVRUBYCOMPLETION_EXPORT getArgumentList(KDevelop::Declaration *decl, QList<QVariant> *highlighting);

} // End of namespace Ruby


#endif // RUBYCOMPLETIONHELPERS_H
