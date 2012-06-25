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


#ifndef RUBYCOMPLETION_H
#define RUBYCOMPLETION_H


#include <duchain/tests/duchaintestbase.h>


namespace Ruby
{

class TestCompletion : public DUChainTestBase
{
    Q_OBJECT

public:
    /// Constructor.
    TestCompletion();

protected:
    /// Re-implemented from DUChainTestBase.
    virtual KDevelop::TopDUContext * parse(const QByteArray &code, const QString &id);

private slots:
    void baseClass();
};

} // End of namespace Ruby


#endif // RUBYCOMPLETION_H
