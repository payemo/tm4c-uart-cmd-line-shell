#include <stdint.h>

#include "tm4c123gh6pm.h"

#include "led.h"

void led_init(void)
{
  /* Enable GPIO Port F clock */
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

  /* Wait until GPIO is ready */
  while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0u) {
  }

  /* Disable analogue and alternate functions */
  GPIO_PORTF_AMSEL_R &= ~LED_RED;
  GPIO_PORTF_AFSEL_R &= ~LED_RED;
  GPIO_PORTF_PCTL_R &= ~(0xFu << 4);

  /* Configure PF1 as a digital output */
  GPIO_PORTF_DIR_R |= LED_RED;
  GPIO_PORTF_DEN_R |= LED_RED;

  /* Initially turn off the LED */
  GPIO_PORTF_DATA_R &= ~LED_RED;
}
