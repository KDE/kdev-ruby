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


#ifndef RUBY_COMPLETION_MODEL_H
#define RUBY_COMPLETION_MODEL_H


#include <language/codecompletion/codecompletionmodel.h>
#include <completion/completionexport.h>


namespace ruby {

/**
 * @class CodeCompletionModel
 * This is the code completion model for the Ruby language support.
 */
class KDEVRUBYCOMPLETION_EXPORT CodeCompletionModel : public KDevelop::CodeCompletionModel
{
    Q_OBJECT

public:
    /// Constructor.
    explicit CodeCompletionModel(QObject *parent);

    /// Destructor.
    ~CodeCompletionModel() override;

protected:
    /// Re-implemented from KDevelop::CodeCompletionModel.
    KDevelop::CodeCompletionWorker *createCompletionWorker() override;
};

}


#endif /* RUBY_COMPLETION_MODEL_H */
