#include "drivers/uart.h"
#include "shell/line_reader.h"

int main()
{
  uart_init();

  line_reader_init();

  while (1) {
    if (uart_available()) {
      char c = uart_getc();
      line_reader_process_char(c);
    }
  }
}
