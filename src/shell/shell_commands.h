#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

#include <stddef.h>

typedef int (*shell_command_fn)(int argc, char **argv);

typedef struct {
  const char *name;
  const char *help;
  shell_command_fn handler;
} shell_command_t;

typedef enum {
  SHELL_OK = 0,
  SHELL_ERROR_ARGS,
  SHELL_ERROR_UNKNOWN,
} shell_result_t;

int shell_process_cmd(int argc, char **argv);

const shell_command_t *shell_commands_get(size_t *count);

#endif
