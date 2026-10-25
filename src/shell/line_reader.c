#include "line_reader.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "../drivers/uart.h"

static char line[SHELL_LINE_SIZE];
static size_t line_pos;

static bool overflow_reported;
static bool ignore_next_lf;

static void line_reader_prompt(void)
{
  uart_write("tm4c> ");
}

static void line_reader_reset(void)
{
  line_pos = 0;
  line[line_pos] = '\0';
  overflow_reported = false;
}

static void line_reader_finish(void)
{
  uart_write("\r\n");

  if (line_pos > 0) {
    uart_write("received: ");
    uart_write(line);
    uart_write("\r\n");
  }

  line_reader_reset();
  line_reader_prompt();
}

void line_reader_init(void)
{
  ignore_next_lf = false;
  line_reader_reset();

  uart_write("\r\nTM4C123 Shell\r\n");
  line_reader_prompt();
}

void line_reader_process_char(char c)
{
  uint8_t ch = (uint8_t)c;

  // Handle CRLF as a single line ending.
  if (ch == '\n' && ignore_next_lf) {
    ignore_next_lf = false;
    return;
  }

  ignore_next_lf = (ch == '\r');

  // Enter: complete the current line.
  if (ch == '\r' || ch == '\n') {
    line_reader_finish();
    return;
  }

  // Backspace (BS) or Delete (DEL)
  if (ch == '\b' || ch == 0x7F) {
    if (line_pos > 0) {
      --line_pos;
      line[line_pos] = '\0';

      // Move cursor back, erase, move back
      uart_write("\b \b");
    }
    return;
  }

  // Accepr printable ASCII only.
  if (ch >= 0x20 && ch <= 0x7E) {
    if (line_pos < SHELL_LINE_SIZE - 1) {
      line[line_pos++] = (char)ch;
      line[line_pos] = '\0';

      // Echo accepted character.
      uart_putc((char)ch);
    } else if (!overflow_reported) {
      // Terminal bell (BEL): signal rejected input.
      uart_putc(0x07);
      overflow_reported = true;
    }
  }

  // Ignore other control characters.
}
