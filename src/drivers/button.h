#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

typedef enum {
  BUTTON_SW1,
  BUTTON_SW2
} button_id_t;

void button_init(void);
bool button_pressed(button_id_t button);

#endif
