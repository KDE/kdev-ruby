/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <completion/worker.h>
#include <completion/context.h>
#include <completion/model.h>

#include <language/util/includeitem.h>


namespace ruby
{

CodeCompletionWorker::CodeCompletionWorker(CodeCompletionModel *parent)
    : KDevelop::CodeCompletionWorker(parent)
{
    /* There's nothing to do here */
}

KDevelop::CodeCompletionContext* CodeCompletionWorker::createCompletionContext(const KDevelop::DUContextPointer& context, const QString &contextText,
                                                                               const QString &followingText, const KDevelop::CursorInRevision &position) const
{
    return new ruby::CodeCompletionContext(context, contextText, followingText, position);
}

}
