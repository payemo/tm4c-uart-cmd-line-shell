#include <stdint.h>

#include "drivers/uart.h"

/* static void delay(volatile uint32_t count) { */
/*   while (count > 0u) { */
/*     --count; */
/*     __asm volatile ("nop"); */
/*   } */
/* } */

int main()
{
  //led_init();
  uart_init();

  uart_write("UART echo ready\r\n");

  while (1) {
    if (uart_available()) {
      char c = uart_getc();
      uart_putc(c);
    }
  }
}
