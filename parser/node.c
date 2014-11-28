/* This file is part of KDevelop
 *
 * Copyright (C) 2010-2014 Miquel Sabaté Solà <mikisabate@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifdef BUILD_TESTS
#include <stdio.h>
#endif
#include <stdlib.h>

#include "node.h"


/*
 * alloc functions.
 */

struct Node * alloc_node(int kind, struct Node *l, struct Node *r)
{
    struct Node *n = (struct Node *) malloc(sizeof(struct Node));

    if (!n)
        exit(0);
    n->kind = kind;
    n->flags = 0;
    n->name = NULL;
    n->context = NULL;
    n->comment = NULL;
    n->next = NULL;
    n->last = NULL;
    n->cond = NULL;
    n->ensure = NULL;
    n->l = l;
    n->r = r;
    n->pos.offset = 0;
    n->pos.start_line = n->pos.end_line = -1;
    n->pos.start_col = n->pos.end_col = -1;
    return n;
}

struct Node * alloc_cond(int kind, struct Node *cond, struct Node *l, struct Node *r)
{
    struct Node *n = alloc_node(kind, l, r);
    n->cond = cond;
    return n;
}

struct Node * alloc_ensure(int kind, struct Node *l, struct Node *r,
                           struct Node *els, struct Node *ensure)
{
    struct Node *n = alloc_cond(kind, els, l, r);
    n->ensure = ensure;
    return n;
}


/*
 * List manipulation functions
 */

struct Node * create_list(struct Node *head, struct Node *tail)
{
    head->next = tail;
    head->last = tail->last;
    return head;
}

struct Node * update_list(struct Node *head, struct Node *tail)
{
    if (!tail)
        return head;
    (head->last == NULL) ? (head->next = tail) : (head->last->next = tail);
    tail->next = NULL;
    head->last = tail;
    return head;
}

struct Node * concat_list(struct Node *head, struct Node *tail)
{
    if (!tail)
        return head;
    (head->last == NULL) ? (head->next = tail) : (head->last->next = tail);
    head->last = (tail->last) ? tail->last : tail;
    return head;
}

/*
 * Auxiliar functions
 */

#ifdef BUILD_TESTS

void raw_print(struct Node *n)
{
    printf("%i", n->kind);
    if (n->name != NULL)
        printf("(%s)", n->name);
    if (n->pos.start_line != -1 && n->pos.start_col != -1 &&
        n->pos.end_line != -1 && n->pos.end_col != -1) {
        printf("[%i,%i:%i,%i] ", n->pos.start_line, n->pos.start_col,
                                    n->pos.end_line, n->pos.end_col);
    } else
        printf(" ");
}

void print_list(struct Node *n)
{
    struct Node * p;

    printf("\nNext statements: ");
    for (p = n; p != NULL; p = p->next)
        raw_print(p);
    printf("\nRoot: ");
}

void print_node(struct Node *n)
{
    if (n != NULL) {
        print_node(n->l);
        raw_print(n);
        print_node(n->r);
        if (n->next != NULL)
            print_list(n->next);
    }
}

void print_errors(struct error_t *e)
{
    struct error_t *aux;

    for (aux = e; aux; aux = aux->next)
        printf("Line: %i, Column: %i; %s\n", aux->line, aux->column, aux->msg);
}

#endif

void free_ast(struct Node *n)
{
    if (!n)
        return;

    free_ast(n->next);
    free_ast(n->l);
    free_ast(n->r);
    free_ast(n->cond);
    free_ast(n->ensure);
    if (n->name)
        free(n->name);
    if (n->comment) {
        free(n->comment);
        n->comment = NULL;
    }
    free(n);
}

void free_errors(struct ast_t *ra)
{
    struct error_t *aux;

    for (aux = ra->errors; aux; aux = aux->next)
        free(aux->msg);
}

/*
 * Interface to the parser
 */

void rb_free(struct ast_t *ra)
{
    free_ast(ra->tree);
    free_errors(ra);
    free(ra);
}

struct Node * rb_name_node(struct Node *n)
{
    struct Node *name;
    const char isMethod = (n->kind == token_function);

    if (isMethod)
        name = (n->cond->r != NULL) ? n->cond->r : n->cond;
    else
        name = (n->r->last != NULL) ? n->r->last : n->r;
    return name;
}
