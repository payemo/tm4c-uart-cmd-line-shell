#ifndef LED_H
#define LED_H

/* On-board LEDs on Port F: PF1 red, PF2 blue, PF3 green */
#define LED_RED (1u << 1)

void led_init(void);

#endif
