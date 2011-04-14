/* This file is part of KDevelop
   Copyright (C) 2010  Miquel Sabaté <mikisabate@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"


/*
 * alloc functions.
 */

struct node * alloc_node(int kind, struct node * l, struct node * r)
{
  struct node * n = (struct node *) malloc (sizeof(struct node));

  if (!n) {
    printf("Out of space!");
    exit(0);
  }
  n->kind = kind;
  n->name = NULL;
  n->next = NULL;
  n->last = NULL;
  n->cond = NULL;
  n->ensure = NULL;
  n->l = l;
  n->r = r;
  return n;
}

struct node * alloc_cond(int kind, struct node * cond, struct node * l, struct node * r)
{
  struct node * n = alloc_node(kind, l, r);
  n->cond = cond;
  return n;
}

struct node * alloc_ensure(int kind, struct node * l, struct node * r,
                            struct node * els, struct node * ensure)
{
  struct node * n = alloc_cond(kind, els, l, r);
  n->ensure = ensure;
  return n;
}


/*
 * List manipulation functions
 */

struct node * create_list(struct node * head, struct node * tail)
{
  head->next = tail;
  head->last = tail->last;
  return head;
}

struct node * update_list(struct node * head, struct node * tail)
{
  if (tail == NULL)
    return head;

  (head->last == NULL) ? (head->next = tail) : (head->last->next = tail);
  tail->next = NULL;
  head->last = tail;
  return head;
}

struct node * concat_list(struct node * head, struct node * tail)
{
  (head->last == NULL) ? (head->next = tail) : (head->last->next = tail);
  head->last = tail->last;
  return head;
}


/*
 * Interface to the parser
 */

void rb_free(RubyAst * ra)
{
  free_ast(ra->tree);
  free_errors(ra->errors);
  free(ra);
}


/*
 * Auxiliar functions
 */

void print_list(struct node * n)
{
  struct node * p;

  printf("\nNext statements: ");
  for (p = n; p != NULL; p = p->next) {
    if (p->name != NULL)
      printf("%i(%s) ", p->kind, p->name);
    else
      printf("%i ", p->kind);
  }
  printf("\nRoot: ");
}

void print_node(struct node * n)
{
  if (n != NULL) {
    print_node(n->l);
    if (n->name != NULL)
      printf("%i(%s) ", n->kind, n->name);
    else
      printf("%i ", n->kind);
    print_node(n->r);
    if (n->next != NULL)
      print_list(n->next);
  }
}

void print_errors(char ** errors)
{
  char ** p;

  for (p = errors; *p != NULL; ++p)
    printf("%s\n", *p);
}

void free_ast(struct node * n)
{
  if (n == NULL)
    return;
  free_ast(n->next);
  free_ast(n->l);
  free_ast(n->r);
  free_ast(n->cond);
  free_ast(n->ensure);
  if (n->name != NULL)
    free(n->name);
  free(n);
}

void free_errors(char ** errors)
{
  char ** p;

  for (p = errors; *p != NULL; p++)
    free(*p);
  free(errors);
}

