#include "drivers/uart.h"
#include "drivers/led.h"
#include "drivers/button.h"
#include "drivers/systick.h"
#include "shell/shell.h"

#define SYSTEM_CLOCK_HZ 16000000UL

int main()
{
  if (!systick_init(SYSTEM_CLOCK_HZ)) {
    while(1) {
      /* Invalid SysTick configuration */
    }
  }
  
  uart_init();
  led_init();
  button_init();
  shell_init();

  while (1) {
    if (uart_available()) {
      char c = uart_getc();
      shell_process_char(c);
    }

    shell_process_line();
  }
}
