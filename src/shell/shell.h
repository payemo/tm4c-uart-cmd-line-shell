#ifndef SHELL_H
#define SHELL_H

#define SHELL_LINE_SIZE 64

/* initializes internal state and prints the first prompt: tm4c> */
void shell_init(void);

void shell_process_char(char c);

/* handles a completed line outside the character-input function */
void shell_process_line(void);

#endif
