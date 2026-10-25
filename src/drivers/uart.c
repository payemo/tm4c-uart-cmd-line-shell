#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "uart.h"

void uart_init(void)
{
  // 1. Enable UART0 and GPIO Port A clocks.
  SYSCTL_RCGCUART_R |= (1U << 0);
  SYSCTL_RCGCGPIO_R |= (1U << 0);

  // Wait until both peripherals are ready
  while ((SYSCTL_RCGCUART_R & 1U) == 0U) {}
  while ((SYSCTL_RCGCGPIO_R & 1U) == 0U) {}

  // 2. Configure PA0 and PA1 for UART0
  GPIO_PORTA_AFSEL_R |= 0x03U;
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFFU) | 0x11U;

  GPIO_PORTA_AMSEL_R &= ~0x03U;
  GPIO_PORTA_DEN_R |= 0x03U;

  // 3. Disable UART before configuration
  UART0_CTL_R = 0U;

  // 4. Configure 115200 baud at 16MHz
  UART0_IBRD_R = 8U;
  UART0_FBRD_R = 44U;
  UART0_CC_R = 0U;

  // 5. Configure 8N1, FIFOs disabled.
  UART0_LCRH_R = (3U << 5);

  // 6. Enable UART0 and Tx/Rx
  UART0_CTL_R = (1U << 0) | (1U << 8) | (1U << 9);
}

void uart_putc(char c)
{
  // Wait until a transmit holding register is available.
  while ((UART0_FR_R & (1U << 5)) != 0U) {}

  UART0_DR_R = (uint8_t)c;
}

void uart_write(const char *str)
{
  while (*str != '\0') {
    uart_putc(*str++);
  }
}

bool uart_available(void)
{
  return ((UART0_FR_R & (1U << 4)) == 0);
}

char uart_getc(void)
{
  return UART0_DR_R & 0xFF;
}
