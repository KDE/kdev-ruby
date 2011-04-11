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

#include "node.h"
#include "interface.h"

extern int yycompile_file(const char *);

/* Configurable */
#define LIB 0


#if LIB
void lib_test(struct node * n)
{
  struct node * it;

  if (is_function(n)) {
    printf("This is a function definition\n");
    printf("The name of the function is: %s\n", function_name(n));
    printf("It has the following arguments: ");
    for (it = function_args(n); it != NULL; it = arg_next(it))
      printf("%s ", arg_name(it));
    printf("\n");
  } else if (is_class(n)) {
    printf("This is a class definition\n");
    printf("The name of the class is: %s\n", class_name(n));
    if (has_superclass(n))
      printf("The superclass' name is: %s\n", superclass(n));
  } else if (is_variable(n)) {
    printf("This is a variable, or a constant, or similar ;)\n");
    printf("The variable name is: %s\n", var_name(n));
  } else
    printf("There's no test for this kind of token: %i\n", token_kind(n));
}
#endif

void usage()
{
  printf("Usage: ruby-parser file\n\n");
  printf("KDevelop Ruby parser debugging utility\n");
  exit(0);
}

int main(int argc, char * argv[])
{
  if (argc != 2)
    usage();
#if LIB
  RubyAst * ast = rb_compile_file(argv[argc - 1]);
  print_node(ast->tree);
  printf("\n");
  lib_test(ast->tree);
  printf("\n\nIs there any error?\n");
  print_errors(ast->errors);
  printf("\n\nFree!\n");
  rb_free(ast);
  return 0;
#else
  return yycompile_file(argv[argc - 1]);
#endif
}

