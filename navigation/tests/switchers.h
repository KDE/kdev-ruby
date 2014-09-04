/*
 * This file is part of KDevelop
 * Copyright (C) 2014 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#ifndef RAILS_SWITCHERS_TEST_H
#define RAILS_SWITCHERS_TEST_H


#include <QtCore/QObject>


namespace Rails
{

class SwitchersTest : public QObject
{
    Q_OBJECT

public:
    SwitchersTest();

private slots:
    void TestFindRailsRoot();
};

} // End of namespace Rails


#endif /* RAILS_SWITCHERS_TEST */
