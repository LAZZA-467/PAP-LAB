/*
 * main.c - menu controller for the MFMS.
 *
 * main.c only knows the *public interfaces* of the other modules
 * (the headers). It never touches their data directly.
 */
#include <stdio.h>

#include "config.h"
#include "utilities.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "reports.h"

static void show_about(void);

int main(void)
{
    int choice;

    /* 1. Initialise every module before use. */
    employees_init();
    budget_init();
    suppliers_init();

    /* 2. Menu loop. */
    do {
        util_print_header(APP_NAME "  v" APP_VERSION);
        printf("  1. Employee management\n");
        printf("  2. Budget management\n");
        printf("  3. Supplier management\n");
        printf("  4. Reports\n");
        printf("  5. About / help\n");
        printf("  0. Exit\n");

        choice = util_read_int("Choice: ", 0, 5);

        switch (choice) {
        case 1:
            employees_menu();
            break;
        case 2:
            budget_menu();
            break;
        case 3:
            suppliers_menu();
            break;
        case 4:
            reports_menu();
            break;
        case 5:
            show_about();
            break;
        case 0:
            printf("\nThank you for using the MFMS. Goodbye!\n");
            break;
        default:
            break;
        }
    } while (choice != 0);

    return 0;
}

static void show_about(void)
{
    util_print_header("ABOUT " APP_NAME);

    printf("Version %s\n\n", APP_VERSION);
    printf("A modular micro-finance management system built for the\n");
    printf("Week 9 multi-file programming lab.\n\n");
    printf("Modules:\n");
    printf("  main.c       - menu controller\n");
    printf("  employees.c  - employee records\n");
    printf("  budget.c     - income / expense records\n");
    printf("  suppliers.c  - supplier records (extension)\n");
    printf("  reports.c    - reports built on employees + budget\n");
    printf("  utilities.c  - reusable input / display helpers\n");
    printf("  config.h     - shared application constants\n");

    util_pause();
}