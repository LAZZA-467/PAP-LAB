/*
 * reports.c - builds reports by calling the employees and budget modules.
 */
#include <stdio.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "utilities.h"

void reports_employee_report(void)
{
    int             i;
    int             count = employees_count();
    double          total = employees_total_salary();
    const Employee *top   = employees_get(0);

    util_print_header("EMPLOYEE REPORT");

    if (count == 0) {
        printf("  (no employees recorded yet)\n");
        return;
    }

    printf("Employees on record  : %d\n", count);
    printf("Total monthly salary : %.2f\n", total);
    printf("Average salary       : %.2f\n", total / count);

    for (i = 1; i < count; i++) {
        const Employee *e = employees_get(i);
        if (e != NULL && top != NULL && e->salary > top->salary) {
            top = e;
        }
    }

    if (top != NULL) {
        printf("Highest paid         : %s (%s) at %.2f\n",
               top->name, top->position, top->salary);
    }
}

void reports_budget_report(void)
{
    int i;
    int count = budget_count();

    util_print_header("BUDGET REPORT");

    if (count == 0) {
        printf("  (no budget entries recorded yet)\n");
        return;
    }

    printf("%-6s %-16s %-9s %14s\n", "ID", "Category", "Type", "Amount");
    util_print_line();

    for (i = 0; i < count; i++) {
        const BudgetEntry *b = budget_get(i);
        if (b == NULL) {
            continue;
        }
        printf("%-6d %-16s %-9s %14.2f\n",
               b->id,
               b->category,
               (b->type == BUDGET_INCOME) ? "income" : "expense",
               b->amount);
    }

    util_print_line();
    printf("Total income   : %.2f\n", budget_total_income());
    printf("Total expenses : %.2f\n", budget_total_expense());
    printf("Balance        : %.2f\n", budget_balance());
}

void reports_summary(void)
{
    double income  = budget_total_income();
    double expense = budget_total_expense();
    double payroll = employees_total_salary();
    double net     = income - expense - payroll;

    util_print_header("MFMS FINANCIAL SUMMARY");

    printf("Employees on record   : %d\n", employees_count());
    printf("Monthly payroll       : %.2f\n", payroll);
    printf("Budget entries        : %d\n", budget_count());
    printf("Total income          : %.2f\n", income);
    printf("Total expenses        : %.2f\n", expense);
    util_print_line();
    printf("Balance before payroll: %.2f\n", income - expense);
    printf("Surplus / (deficit)   : %.2f\n", net);
    util_print_line();

    if (net >= 0.0) {
        printf("Status: SURPLUS - the MFMS is operating within its budget.\n");
    } else {
        printf("Status: DEFICIT - payroll exceeds the available funds.\n");
    }
}

void reports_menu(void)
{
    int choice;

    do {
        util_print_header("REPORTS");
        printf("  1. Employee report\n");
        printf("  2. Budget report\n");
        printf("  3. Financial summary (employees + budget)\n");
        printf("  0. Back to main menu\n");

        choice = util_read_int("Choice: ", 0, 3);

        switch (choice) {
        case 1:
            reports_employee_report();
            util_pause();
            break;

        case 2:
            reports_budget_report();
            util_pause();
            break;

        case 3:
            reports_summary();
            util_pause();
            break;

        case 0:
        default:
            break;
        }
    } while (choice != 0);
}