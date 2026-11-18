#ifndef LED_H
#define LED_H

#include <stdbool.h>

/* On-board LEDs on Port F: PF1 red, PF2 blue, PF3 green */
#define LED_RED_PIN   (1u << 1)
#define LED_BLUE_PIN  (1u << 2)
#define LED_GREEN_PIN (1u << 3)

#define LED_ALL_PINS \
  (LED_RED_PIN | LED_BLUE_PIN | LED_GREEN_PIN)

typedef enum {
  LED_RED,
  LED_BLUE,
  LED_GREEN
} led_color_t;

void led_init(void);
void led_set(led_color_t color, bool enabled);

#endif
