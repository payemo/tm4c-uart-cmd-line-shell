#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

#include "shell.h"

#define SHELL_MAX_ARGS 8

int shell_tokenize(char *line, char *argv[], int max_args);

#endif
