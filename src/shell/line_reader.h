#ifndef LINE_READER_H
#define LINE_READER_H

#define SHELL_LINE_SIZE 64

/* initializes internal state and prints the first prompt: tm4c> */
void line_reader_init(void);
void line_reader_process_char(char c);

#endif
