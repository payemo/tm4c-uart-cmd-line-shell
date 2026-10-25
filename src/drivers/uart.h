#ifndef UART_H
#define UART_H

#include <stdbool.h>

void uart_init(void);
void uart_putc(char c);
void uart_write(const char *str);

bool uart_available(void);
char uart_getc(void);

#endif
