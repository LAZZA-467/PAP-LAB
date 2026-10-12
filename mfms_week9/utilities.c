/*
 * utilities.c - implementation of the reusable helper functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "utilities.h"

void util_clear_input(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard the rest of the line */
    }
}

void util_read_string(const char *prompt, char *buffer, size_t size)
{
    if (buffer == NULL || size == 0) {
        return;
    }

    for (;;) {
        printf("%s", prompt);

        if (fgets(buffer, (int)size, stdin) == NULL) {
            buffer[0] = '\0';          /* EOF - fail safe */
            return;
        }

        /* If there was no newline, the user typed more than we can hold. */
        if (strchr(buffer, '\n') == NULL) {
            util_clear_input();
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            printf("  ! Input cannot be empty, please try again.\n");
            continue;
        }
        return;
    }
}

int util_read_int(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long value;

    for (;;) {
        printf("%s", prompt);

        if (fgets(line, sizeof line, stdin) == NULL) {
            return min;                /* EOF - fail safe */
        }

        if (strchr(line, '\n') == NULL) {
            util_clear_input();
        }
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0') {
            printf("  ! Input cannot be empty, please try again.\n");
            continue;
        }

        errno = 0;
        value = strtol(line, &end, 10);

        while (*end == ' ' || *end == '\t') {   /* allow trailing blanks */
            end++;
        }

        if (end == line || *end != '\0' || errno == ERANGE) {
            printf("  ! \"%s\" is not a whole number.\n", line);
            continue;
        }
        if (value < min || value > max) {
            printf("  ! Please enter a value between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

double util_read_double(const char *prompt, double min, double max)
{
    char line[64];
    char *end;
    double value;

    for (;;) {
        printf("%s", prompt);

        if (fgets(line, sizeof line, stdin) == NULL) {
            return min;                /* EOF - fail safe */
        }

        if (strchr(line, '\n') == NULL) {
            util_clear_input();
        }
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0') {
            printf("  ! Input cannot be empty, please try again.\n");
            continue;
        }

        errno = 0;
        value = strtod(line, &end);

        while (*end == ' ' || *end == '\t') {
            end++;
        }

        if (end == line || *end != '\0' || errno == ERANGE) {
            printf("  ! \"%s\" is not a valid amount.\n", line);
            continue;
        }
        if (value < min || value > max) {
            printf("  ! Please enter an amount between %.2f and %.2f.\n",
                   min, max);
            continue;
        }
        return value;
    }
}

int util_confirm(const char *prompt)
{
    char line[16];

    for (;;) {
        printf("%s [y/n]: ", prompt);

        if (fgets(line, sizeof line, stdin) == NULL) {
            return 0;
        }
        if (strchr(line, '\n') == NULL) {
            util_clear_input();
        }

        if (line[0] == 'y' || line[0] == 'Y') {
            return 1;
        }
        if (line[0] == 'n' || line[0] == 'N') {
            return 0;
        }
        printf("  ! Please answer y or n.\n");
    }
}

void util_print_line(void)
{
    int i;

    for (i = 0; i < 60; i++) {
        putchar('-');
    }
    putchar('\n');
}

void util_print_header(const char *title)
{
    size_t i;
    size_t width;

    width = strlen(title) + 4;
    putchar('\n');

    for (i = 0; i < width; i++) {
        putchar('=');
    }
    putchar('\n');
    printf("  %s\n", title);

    for (i = 0; i < width; i++) {
        putchar('=');
    }
    putchar('\n');
}

void util_pause(void)
{
    char line[8];

    printf("\nPress Enter to continue...");
    if (fgets(line, sizeof line, stdin) == NULL) {
        return;
    }
}