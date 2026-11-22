#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>

bool systick_init(uint32_t system_clock_hz);
uint32_t uptime_ms(void);

#endif
