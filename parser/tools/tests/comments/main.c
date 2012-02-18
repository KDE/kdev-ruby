

#include <stdio.h>
#include <stdlib.h>
#include "../../../node.h"


/*
 * This is a recursive function that steps over the AST to fetch
 * all the comments that the parser has stored. All the comments
 * are printed to the stdout.
 */
void fetch_comments(struct node *tree)
{
  struct node *ptr;

  if (!tree)
    return;
  if (tree->comment != NULL)
    printf("%s", tree->comment);

  fetch_comments(tree->l);
  fetch_comments(tree->r);
  fetch_comments(tree->next);
}


int main(int argc, char *argv[])
{
    RAst *ast;

  if (argc != 2) {
    printf("Usage: comments-test file\n\n");
    printf("KDevelop Ruby parser debugging utility\n");
    exit(1);
  }

  ast = rb_compile_file(argv[1], NULL);
  if (ast->errors[0].valid) {
    printf("This is unexpected...\n");
    exit(1);
  }

  fetch_comments(ast->tree);
  rb_free(ast);
  return 0;
}
 
