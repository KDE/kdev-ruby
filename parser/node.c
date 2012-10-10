/* This file is part of KDevelop
 *
 * Copyright (C) 2010 Miquel Sabaté <mikisabate@gmail.com>
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"


/*
 * alloc functions.
 */

struct node * alloc_node(int kind, struct node *l, struct node *r)
{
    struct node *n = (struct node *) malloc(sizeof(struct node));

    if (!n) {
        printf("Out of space!");
        exit(0);
    }
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

struct node * alloc_cond(int kind, struct node *cond, struct node *l, struct node *r)
{
    struct node *n = alloc_node(kind, l, r);
    n->cond = cond;
    return n;
}

struct node * alloc_ensure(int kind, struct node *l, struct node *r,
                           struct node *els, struct node *ensure)
{
    struct node *n = alloc_cond(kind, els, l, r);
    n->ensure = ensure;
    return n;
}


/*
 * List manipulation functions
 */

struct node * create_list(struct node *head, struct node *tail)
{
    head->next = tail;
    head->last = tail->last;
    return head;
}

struct node * update_list(struct node *head, struct node *tail)
{
    if (!tail)
        return head;
    (head->last == NULL) ? (head->next = tail) : (head->last->next = tail);
    tail->next = NULL;
    head->last = tail;
    return head;
}

struct node * concat_list(struct node *head, struct node *tail)
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

void raw_print(struct node *n)
{
    printf("%i", n->kind);
    if (n->name != NULL)
        printf("(%s)", n->name);
    printf("[%i,%i:%i,%i] ", n->pos.start_line, n->pos.start_col,
           n->pos.end_line, n->pos.end_col);
}

void print_list(struct node *n)
{
    struct node * p;

    printf("\nNext statements: ");
    for (p = n; p != NULL; p = p->next)
        raw_print(p);
    printf("\nRoot: ");
}

void print_node(struct node *n)
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

void free_ast(struct node *n)
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
    if (n->comment)
        free(n->comment);
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

struct node * rb_name_node(struct node *n)
{
    struct node *name;
    const char isMethod = (n->kind == token_function);

    if (isMethod)
        name = (n->cond->r != NULL) ? n->cond->r : n->cond;
    else
        name = (n->r->last != NULL) ? n->r->last : n->r;
    return name;
}
