/*
 * This file is part of KDevelop
 * Copyright (C) 2014-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <QtTest/QtTest>
#include <rails/switchers.h>
#include <rails/helpers.h>
#include <rails/tests/rails.h>
#include <util/path.h>


QTEST_MAIN(ruby::rails::Test)

using namespace ruby::rails;

Test::Test()
{
    /* There's nothing to do here. */
}

void Test::TestFindRailsRoot()
{
    KDevelop::Path path;

    // Empty URL.
    path = Helpers::findRailsRoot(QUrl(""));
    Q_ASSERT(!path.isValid());

    // App.
    path = Helpers::findRailsRoot(QUrl("/rails/app/controllers/file.rb"));
    Q_ASSERT(path.isValid());
    QCOMPARE(path.toLocalFile(), QString("/rails"));
    path = Helpers::findRailsRoot(QUrl("/rails/app/models/file.rb"));
    Q_ASSERT(path.isValid());
    QCOMPARE(path.toLocalFile(), QString("/rails"));
    path = Helpers::findRailsRoot(QUrl("/rails/app/views/file.rb"));
    Q_ASSERT(path.isValid());
    QCOMPARE(path.toLocalFile(), QString("/rails"));

    // Tests.
    path = Helpers::findRailsRoot(QUrl("/rails/test/file.rb"));
    Q_ASSERT(path.isValid());
    QCOMPARE(path.toLocalFile(), QString("/rails"));
    path = Helpers::findRailsRoot(QUrl("/rails/dir/test/file.rb"));
    Q_ASSERT(path.isValid());
    QCOMPARE(path.toLocalFile(), QString("/rails/dir"));

    // Invalids
    path = Helpers::findRailsRoot(QUrl("/rails/app/test/file.rb"));
    Q_ASSERT(!path.isValid());
    path = Helpers::findRailsRoot(QUrl("/rails/app/controllers"));
    Q_ASSERT(!path.isValid());
}

