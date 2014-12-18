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


#ifndef RUBYCOMPLETIONHELPERS_H
#define RUBYCOMPLETIONHELPERS_H


#include <QtCore/QList>
#include <QtCore/QVariant>
#include <completion/completionexport.h>


namespace KTextEditor {
    class Document;
}

namespace KDevelop {
    class Declaration;
}

namespace ruby {

class NormalItem;

/**
 * Get a string representing an indentation.
 *
 * @param document The current document.
 * @returns a QString containing the indentation to be used.
 */
const QString KDEVRUBYCOMPLETION_EXPORT indentString(KTextEditor::Document *document);

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

}


#endif // RUBYCOMPLETIONHELPERS_H
