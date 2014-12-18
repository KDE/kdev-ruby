/* This file is part of KDevelop
 *
 * Copyright (C) 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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

#ifndef RUBY_REFACTORING_H
#define RUBY_REFACTORING_H

#include <language/codegen/basicrefactoring.h>

namespace ruby {

struct Refactoring : public KDevelop::BasicRefactoring
{
    explicit Refactoring(QObject *parent = nullptr);
};

}

#endif // REFACTORING_H

