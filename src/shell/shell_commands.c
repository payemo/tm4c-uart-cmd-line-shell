#include "../drivers/uart.h"
#include "shell_commands.h"

#define FIRMWARE_VERSION "0.1"
#define UART_BAUD_RATE "115200"

static int cmd_help(int argc, char **argv);
static int cmd_info(int argc, char **argv);

static const shell_command_t commands[] = {
  { "help", "Show available commands", cmd_help },
  { "info", "Show board information", cmd_info }
};

static int str_eq(const char *lhs, const char *rhs)
{
  while (*lhs != '\0' && (*lhs == *rhs)) {
    ++lhs;
    ++rhs;
  }

  return (int)(unsigned char)*lhs - (int)(unsigned char)*rhs;
}

static int cmd_help(int argc, char **argv)
{
  size_t count = 0;
  const shell_command_t *commands = shell_commands_get(&count);

  if (argc > 2) {
    uart_write("Usage: help [command]\r\n");
    return SHELL_ERROR_ARGS;
  }

  if (argc == 2) {
    for (size_t i = 0; i < count; ++i) {
      if (str_eq(argv[1], commands[i].name) == 0) {
	uart_write(commands[i].name);
	uart_write(" - ");
	uart_write(commands[i].help);
	uart_write("\r\n");
	return SHELL_OK;
      }
    }

    uart_write("Error: no help for '");
    uart_write(argv[1]);
    uart_write("'\r\n");

    return SHELL_ERROR_UNKNOWN;
  }

  for (size_t i = 0; i < count; ++i) {
    uart_write(commands[i].name);
    uart_write(" - ");
    uart_write(commands[i].help);
    uart_write("\r\n");
  }

  return SHELL_OK;
}

static int cmd_info(int argc, char **argv)
{
  (void)argv;

  if (argc != 1) {
    uart_write("Usage: info\r\n");
    return SHELL_ERROR_ARGS;
  }

  uart_write("Board: EK-TM4C123GXL\r\n");
  uart_write("MCU: TM4C123GH6PM\r\n");
  uart_write("UART: UART0\r\n");
  uart_write("Baud: " UART_BAUD_RATE "\r\n");
  uart_write("Firmware: " FIRMWARE_VERSION "\r\n");

  return SHELL_OK;
}

int shell_process_cmd(int argc, char **argv)
{
  if (argc == 0 || argv == NULL || argv[0] == NULL) {
    return SHELL_OK;
  }

  size_t count = 0;
  const shell_command_t *commands = shell_commands_get(&count);

  for (size_t i = 0; i < count; ++i) {
    if (str_eq(argv[0], commands[i].name) == 0) {
      return commands[i].handler(argc, argv);
    }
  }

  uart_write("Error: unknown command '");
  uart_write(argv[0]);
  uart_write("'\r\n");

  return SHELL_ERROR_UNKNOWN;
}

const shell_command_t *shell_commands_get(size_t *count)
{
  *count = sizeof(commands) / sizeof(commands[0]);
  return commands;
}
