#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "button.h"

#define BUTTON_SW1_MASK (1u << 4)
#define BUTTON_SW2_MASK (1u << 0)

#define BUTTON_MASK (BUTTON_SW1_MASK | BUTTON_SW2_MASK)

void button_init(void)
{
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

  while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0u) {
  }

  /* Unlock GPIO Commit Port F for write access */
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R |= BUTTON_SW2_MASK;

  GPIO_PORTF_DIR_R &= ~BUTTON_MASK;
  GPIO_PORTF_AFSEL_R &= ~BUTTON_MASK;
  GPIO_PORTF_AMSEL_R &= ~BUTTON_MASK;

  GPIO_PORTF_PCTL_R &= 0x000F000Fu;

  GPIO_PORTF_PUR_R |= BUTTON_MASK;
  GPIO_PORTF_DEN_R |= BUTTON_MASK;

  GPIO_PORTF_LOCK_R = 0u;
}

bool button_pressed(button_id_t button)
{
  unsigned int mask;

  switch(button) {
  case BUTTON_SW1:
    mask = BUTTON_SW1_MASK;
    break;
  case BUTTON_SW2:
    mask = BUTTON_SW2_MASK;
    break;
  default:
    return false;
  }

  return (GPIO_PORTF_DATA_R & mask) == 0u;
}
