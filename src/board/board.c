#include "tm4c123gh6pm.h"
#include "board.h"

__attribute__((noreturn))
void board_reset(void)
{
  __asm volatile ("dsb 0xF" ::: "memory");
  
  NVIC_APINT_R = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

  /* Ensure the reset request write completes */
  __asm volatile ("dsb 0xF" ::: "memory");

  while (1) {
  }
}
