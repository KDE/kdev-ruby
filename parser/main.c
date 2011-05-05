/* This file is part of KDevelop
 *
 * Copyright (C) 2010  Miquel Sabaté <mikisabate@gmail.com>
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


#include <stdio.h>
#include <stdlib.h>


extern int yycompile_file(const char *);


/**
 * This is the main function for the parser's debugging utility. It's
 * used to perform all the tests. Please, take a look at the README file
 * for more info.
 */
int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: ruby-parser file\n\n");
        printf("KDevelop Ruby parser debugging utility\n");
        exit(0);
    }
    return yycompile_file(argv[argc - 1]);
}

