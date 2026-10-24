#include <stdint.h>

#include "drivers/uart.h"

#define REG32(addr) (*(volatile uint32_t *)(addr))

/* System Control registers */
#define SYSCTL_RCGCGPIO REG32(0x400FE608u)
#define SYSCTL_PRGPIO   REG32(0x400FEA08u)

/* GPIO Port F registers */
#define GPIO_PORTF_DATA REG32(0x400253FCu)
#define GPIO_PORTF_DIR  REG32(0x40025400u)
#define GPIO_PORTF_DEN  REG32(0x4002551Cu)

#define GPIO_PORTF_AFSEL REG32(0x40025420u)
#define GPIO_PORTF_AMSEL REG32(0x40025528u)
#define GPIO_PORTF_PCTL  REG32(0x4002552Cu)

#define PORTF_CLOCK (1u << 5)
#define LED_RED     (1u << 1)

static void led_init(void)
{
  /* Enable GPIO Port F clock */
  SYSCTL_RCGCGPIO |= PORTF_CLOCK;

  /* Wait until GPIO is ready */
  while ((SYSCTL_PRGPIO & PORTF_CLOCK) == 0u) {
  }

  /* Disable analogue and alternate functions */
  GPIO_PORTF_AMSEL &= ~LED_RED;
  GPIO_PORTF_AFSEL &= ~LED_RED;
  GPIO_PORTF_PCTL &= ~(0xFu << 4);

  /* Configure PF1 as a digital output */
  GPIO_PORTF_DIR |= LED_RED;
  GPIO_PORTF_DEN |= LED_RED;

  /* Initially turn off the LED */
  GPIO_PORTF_DATA &= ~LED_RED;
}

static void delay(volatile uint32_t count) {
  while (count > 0u) {
    --count;
    __asm volatile ("nop");
  }
}

int main()
{
  //led_init();
  uart_init();

  uart_write("Hello from TM4C123!\r\n");

  while (1) {
    /* GPIO_PORTF_DATA |= LED_RED; */
    /* delay(1000000u); */

    /* GPIO_PORTF_DATA &= ~(LED_RED); */
    /* delay(1000000u); */
  }
}
