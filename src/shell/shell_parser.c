#include "shell_parser.h"

#include <stddef.h>

static int is_blank(char c)
{
  return c == ' ' || c == '\t';
}
  
int shell_tokenize(char *line, char *argv[], int max_args)
{
  if (line == NULL || argv == NULL || max_args <= 0) {
    return -1;
  }

  int argc = 0;
  char *cursor = line;

  while (*cursor != '\0') {
    // Skip leading or repeated separators
    while (is_blank(*cursor)) {
      ++cursor;
    }

    if (argc >= max_args) {
      return -2;
    }

    if ((*cursor >= 'A' && *cursor <= 'Z') ||
	(*cursor >= 'a' && *cursor <= 'z')) {
      argv[argc] = cursor;
      ++argc;
    }

    while (*cursor != '\0' && !is_blank(*cursor)) {
      ++cursor;
    }

    if (*cursor != '\0') {
      *cursor = '\0';
      ++cursor;
    }
  }

  return argc;
}
