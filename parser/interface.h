/* This file is part of KDevelop
   Copyright (C) 2011  Miquel Sabaté <mikisabate@gmail.com>

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


#ifndef INTERFACE_H_
#define INTERFACE_H_


/*
 * This file defines a set of macros that make things easier
 * to the programmer that's going to use this parser.
 * WARNING: is still under development.
 */

/* Variables, Constants,... */
#define is_variable(n) (is_object(n) && n->name != NULL)
#define var_name(n) n->name

/* Function */
#define is_function(n) (n->kind == token_function)
#define function_name(n) n->cond->name
#define function_body(n) n->l
#define function_args(n) n->r
#define arg_name(n) n->name
#define arg_next(n) n->next
#define number_arguments(n)

/* Class */
#define is_class(n) (n->kind == token_class)
#define class_name(n) n->r->name
#define has_superclass(n) (n->cond != NULL)
#define superclass(n) n->cond->name
#define class_body(n) n->l

/* Others */
#define is_object(n) (n->kind == token_object)
#define token_kind(n) n->kind


#endif /* INTERFACE_H_ */

