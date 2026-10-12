#ifndef UTILITIES_H
#define UTILITIES_H

/*
 * utilities.h - reusable input / output helper functions.
 * These functions know nothing about employees, budgets or reports,
 * so every other module can use them safely.
 */

#include <stddef.h>

/* Throws away everything left on the current input line. */
void util_clear_input(void);

/* Reads a whole line of text into buffer (never returns an empty string). */
void util_read_string(const char *prompt, char *buffer, size_t size);

/* Reads an int in [min, max], re-prompting until the input is valid. */
int util_read_int(const char *prompt, int min, int max);

/* Reads a double in [min, max], re-prompting until the input is valid. */
double util_read_double(const char *prompt, double min, double max);

/* Asks a yes/no question; returns 1 for yes, 0 for no. */
int util_confirm(const char *prompt);

/* Display helpers */
void util_print_line(void);                  /* 60 dashes + newline */
void util_print_header(const char *title);   /* boxed title           */
void util_pause(void);                       /* "Press Enter..."      */

#endif /* UTILITIES_H */