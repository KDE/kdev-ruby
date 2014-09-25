/*
 * This file is part of KDevelop
 * Copyright (C) 2012-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <completion/worker.h>
#include <completion/context.h>
#include <completion/model.h>

#include <language/util/includeitem.h>


namespace Ruby
{

CodeCompletionWorker::CodeCompletionWorker(CodeCompletionModel *parent)
    : KDevelop::CodeCompletionWorker(parent)
{
    /* There's nothing to do here */
}

KDevelop::CodeCompletionContext* CodeCompletionWorker::createCompletionContext(KDevelop::DUContextPointer context, const QString &contextText,
                                                                               const QString &followingText, const KDevelop::CursorInRevision &position) const
{
    return new Ruby::CodeCompletionContext(context, contextText, followingText, position);
}

} // End of namespace Ruby
