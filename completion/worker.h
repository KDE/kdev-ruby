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


#ifndef RUBY_COMPLETION_WORKER_H
#define RUBY_COMPLETION_WORKER_H


#include <language/codecompletion/codecompletionworker.h>
#include <completion/completionexport.h>


namespace ruby {

class CodeCompletionModel;
class CodeCompletionContext;

/**
 * @class CodeCompletionWorker
 * This is the worker for the code completion.
 */
class KDEVRUBYCOMPLETION_EXPORT CodeCompletionWorker : public KDevelop::CodeCompletionWorker
{
    Q_OBJECT

public:
    /// Constructor
    explicit CodeCompletionWorker(CodeCompletionModel *parent);

protected:
    /// Re-implemented from KDevelop::CodeCompletionWorker
    KDevelop::CodeCompletionContext *createCompletionContext(const KDevelop::DUContextPointer& context,
                                                             const QString &contextText,
                                                             const QString &followingText,
                                                             const KDevelop::CursorInRevision &position) const override;
};

}


#endif /* RUBY_COMPLETION_WORKER_H */
