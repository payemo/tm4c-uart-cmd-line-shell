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

  uart_write("Hello from TM4C123!\r\n");

  while (1) {}
}
