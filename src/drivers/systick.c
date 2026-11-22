#include "tm4c123gh6pm.h"

#include "systick.h"

#define SYSTICK_TICK_HZ 1000UL

#define SYSTICK_MAX_RELOAD 0x00FFFFFUL

#define SYSTICK_CTRL_ENABLE  (1UL << 0)
#define SYSTICK_CTRL_INTEN   (1UL << 1)
#define SYSTICK_CTRL_CLK_SRC (1UL << 2)

static volatile uint32_t g_uptime_ms = 0;

bool systick_init(uint32_t system_clock_hz)
{
  if (system_clock_hz < SYSTICK_TICK_HZ) {
    return false;
  }

  if ((system_clock_hz % 1000) != 0) {
    return false;
  }

  uint32_t ticks = system_clock_hz / SYSTICK_TICK_HZ;

  if (ticks > (SYSTICK_MAX_RELOAD + 1UL)) {
    return false;
  }

  /* Stop SysTick and disable it's interrupt */
  NVIC_ST_CTRL_R = 0U;

  /* Configure reload value */
  NVIC_ST_RELOAD_R = ticks - 1U;

  /* Clear current counter and COUNT flag */
  NVIC_ST_CURRENT_R = 0U;

  /* Reset software uptime counter */
  g_uptime_ms = 0U;

  /* Enable SysTick:
   * - Processor clock source
   * - SysTick interrupt
   * - Counter
   */
  NVIC_ST_CTRL_R = (SYSTICK_CTRL_ENABLE |
		    SYSTICK_CTRL_INTEN  |
		    SYSTICK_CTRL_CLK_SRC);

  return true;
}

uint32_t uptime_ms(void)
{
  return g_uptime_ms;
}

/*
 * SysTick exception handler
 *
 * This function must be referenced by the
 * startup vector table
 */
void SysTick_Handler(void)
{
  ++g_uptime_ms;
}
