#include "shell.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "../drivers/uart.h"

static char line[SHELL_LINE_SIZE];
static size_t line_pos;

static bool line_ready;
static bool last_was_cr;
static uint8_t hidden_overflow_symbols;

static void shell_print_prompt(void)
{
  uart_write("tm4c> ");
}

static void shell_reset_line(void)
{
  line_pos = 0;
  line[line_pos] = '\0';
  
  hidden_overflow_symbols = 0;
  line_ready = false;
}

void shell_init(void)
{
  last_was_cr = false;
  shell_reset_line();

  uart_write("\r\nTM4C123 Shell\r\n");
  shell_print_prompt();
}

void shell_process_char(char c) {

  if (c >= 0x20 && c <= 0x7E) {
    if (line_pos < SHELL_LINE_SIZE - 1) {
      line[line_pos++] = c;
      line[line_pos] = '\0';
      uart_putc(c);
    } else {
      ++hidden_overflow_symbols;
      uart_putc('\a');
    }
  } else if (c == '\r' || c == '\n') {
    if (c == '\n' && last_was_cr) {
      last_was_cr = false;
    } else {
      last_was_cr = (c == '\r');
      line_ready = true;
      line[line_pos] = '\0';
      uart_write("\r\n");
    }
  } else if (c == '\b' || c == 0x7F) {
    if (hidden_overflow_symbols > 0) {
	--hidden_overflow_symbols;
    } else if (line_pos > 0) {
      --line_pos;
      line[line_pos] = '\0';
      uart_write("\b \b");
    }
  }
}

void shell_process_line(void)
{
  if (!line_ready) {
    return;
  }

  if (hidden_overflow_symbols > 0) {
    uart_write("Error: command too long\r\n");
  } else if (line_pos > 0U) {
    uart_write("received: ");
    uart_write(line);
    uart_write("\r\n");
  }

  shell_reset_line();
  shell_print_prompt();
}
