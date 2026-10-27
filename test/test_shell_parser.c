#include <stdio.h>

#include "shell_parser.h"

static void test_line(char *line)
{
  char *argv[SHELL_MAX_ARGS];

  int argc = shell_tokenize(line, argv, SHELL_MAX_ARGS);

  if (argc == -1) {
    printf("Error: invalid tokenizer arguments\n");
    return;
  }

  if (argc == -2) {
    printf("Error: too many arguments\n");
    return;
  }

  printf("argc: %d\n", argc);

  for (int i = 0; i < argc; ++i) {
    printf("argv[%d]: \"%s\"\n", i, argv[i]);
  }
}

int main(void)
{
  char line1[] = "led green on";
  char line2[] = "   help   ";
  char line3[] = "led     red     off";
  char line4[] = "";
  char line5[] = "a b c d e f g h i";

  test_line(line1);
  puts("-------");

  test_line(line2);
  puts("-------");

  test_line(line3);
  puts("-------");

  test_line(line4);
  puts("-------");

  test_line(line5);

  return 0;
}
