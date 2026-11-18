#include "drivers/uart.h"
#include "drivers/led.h"
#include "shell/shell.h"

int main()
{
  uart_init();
  led_init();
  shell_init();

  while (1) {
    if (uart_available()) {
      char c = uart_getc();
      shell_process_char(c);
    }

    shell_process_line();
  }
}
