/* This file is part of KDevelop
 *
 * Copyright (C) 2010-2015 Miquel Sabaté Solà <mikisabate@gmail.com>
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


#include <stdio.h>
#include <stdlib.h>
#include "node.h"


extern int rb_debug_file(struct options_t *opts);

/*
 * This is a recursive function that steps over the AST to fetch
 * all the comments that the parser has stored. All the comments
 * are printed to the stdout.
 */
void fetch_comments(struct Node *tree)
{
    if (!tree)
        return;
    if (tree->comment != NULL)
        printf("%s", tree->comment);

    fetch_comments(tree->l);
    fetch_comments(tree->r);
    fetch_comments(tree->next);
}


/**
 * This is the main function for the parser's debugging utility. It's
 * used to perform all the tests. Please, take a look at the README file
 * for more info.
 */
int main(int argc, char *argv[])
{
    struct ast_t *ast;
    struct options_t opts;

    switch (argc) {
        case 2:
            opts.path = argv[argc - 1];
            opts.version = ruby21;
            return rb_debug_file(&opts);
        case 3:
            opts.path = argv[argc - 2];
            opts.contents = NULL;
            opts.version = atoi(argv[argc - 1]);
            ast = rb_compile_file(&opts);
            if (ast->errors) {
                print_errors(ast->errors);
                exit(1);
            }
            fetch_comments(ast->tree);
            rb_free(ast);
            break;
        default:
            printf("Usage: ruby-parser file [ruby-version]\n\n");
            printf("KDevelop Ruby parser debugging utility\n");
    }
    return 0;
}
