#include <stdint.h>

#include "tm4c123gh6pm.h"

#include "led.h"

static uint32_t led_pin(led_color_t color)
{
  switch(color) {
  case LED_RED:
    return LED_RED_PIN;
  case LED_BLUE:
    return LED_BLUE_PIN;
  case LED_GREEN:
    return LED_GREEN_PIN;
  default:
    return 0u;
  }
}

void led_init(void)
{
  /* Enable GPIO Port F clock */
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

  /* Wait until GPIO is ready */
  while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0u) {
  }

  /* Disable analogue and alternate functions */
  GPIO_PORTF_AMSEL_R &= ~LED_ALL_PINS;
  GPIO_PORTF_AFSEL_R &= ~LED_ALL_PINS;
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0u;

  /* Initially turn off all RGB channels */
  GPIO_PORTF_DATA_R &= ~LED_ALL_PINS;

  /* Configure PF1 as a digital output */
  GPIO_PORTF_DIR_R |= LED_ALL_PINS;
  GPIO_PORTF_DEN_R |= LED_ALL_PINS;
}

void led_set(led_color_t color, bool enabled)
{
  const uint32_t pin = led_pin(color);

  if (pin == 0u) return;

  if (enabled) {
    GPIO_PORTF_DATA_R |= pin;
  } else {
    GPIO_PORTF_DATA_R &= ~pin;
  }
}
