/*
 * budget.c - income and expense tracking for the MFMS.
 */
#include <stdio.h>
#include <string.h>

#include "budget.h"
#include "utilities.h"

/* ---- module-private state ------------------------------------------- */
static BudgetEntry records[MAX_BUDGETS];
static int         record_count = 0;
static int         next_id      = 2001;
/* --------------------------------------------------------------------- */

static const char *budget_type_name(BudgetType type)
{
    return (type == BUDGET_INCOME) ? "income" : "expense";
}

void budget_init(void)
{
    record_count = 0;
    next_id      = 2001;
}

int budget_count(void)
{
    return record_count;
}

const BudgetEntry *budget_get(int index)
{
    if (index < 0 || index >= record_count) {
        return NULL;
    }
    return &records[index];
}

double budget_total_income(void)
{
    int    i;
    double total = 0.0;

    for (i = 0; i < record_count; i++) {
        if (records[i].type == BUDGET_INCOME) {
            total += records[i].amount;
        }
    }
    return total;
}

double budget_total_expense(void)
{
    int    i;
    double total = 0.0;

    for (i = 0; i < record_count; i++) {
        if (records[i].type == BUDGET_EXPENSE) {
            total += records[i].amount;
        }
    }
    return total;
}

double budget_balance(void)
{
    return budget_total_income() - budget_total_expense();
}

int budget_add(void)
{
    BudgetEntry *b;
    int          type;

    if (record_count >= MAX_BUDGETS) {
        printf("  ! Budget limit (%d) reached.\n", MAX_BUDGETS);
        return -1;
    }

    b = &records[record_count];
    memset(b, 0, sizeof *b);
    b->id = next_id++;

    printf("\n-- New budget entry (assigned ID %d) --\n", b->id);
    util_read_string("Category    : ", b->category, sizeof b->category);
    util_read_string("Description : ", b->description, sizeof b->description);

    type   = util_read_int("Type (1 = income, 2 = expense): ", 1, 2);
    b->type = (type == 1) ? BUDGET_INCOME : BUDGET_EXPENSE;

    b->amount = util_read_double("Amount      : ", 0.01, 100000000.0);

    record_count++;
    printf("  + %s entry \"%s\" of %.2f added.\n",
           budget_type_name(b->type), b->category, b->amount);
    return record_count - 1;
}

int budget_remove(int id)
{
    int i;
    int index = -1;

    for (i = 0; i < record_count; i++) {
        if (records[i].id == id) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        printf("  ! No budget entry with ID %d.\n", id);
        return 0;
    }

    for (i = index; i < record_count - 1; i++) {
        records[i] = records[i + 1];
    }
    record_count--;
    printf("  - Budget entry %d removed.\n", id);
    return 1;
}

void budget_list(void)
{
    int i;

    if (record_count == 0) {
        printf("  (no budget entries recorded yet)\n");
        return;
    }

    printf("\n%-6s %-16s %-9s %14s  %s\n",
           "ID", "Category", "Type", "Amount", "Description");
    util_print_line();

    for (i = 0; i < record_count; i++) {
        printf("%-6d %-16s %-9s %14.2f  %s\n",
               records[i].id,
               records[i].category,
               budget_type_name(records[i].type),
               records[i].amount,
               records[i].description);
    }

    util_print_line();
    printf("Entries: %d   Income: %.2f   Expenses: %.2f   Balance: %.2f\n",
           record_count,
           budget_total_income(),
           budget_total_expense(),
           budget_balance());
}

void budget_menu(void)
{
    int choice;

    do {
        util_print_header("BUDGET MANAGEMENT");
        printf("  1. Add budget entry\n");
        printf("  2. List budget entries\n");
        printf("  3. Remove budget entry\n");
        printf("  0. Back to main menu\n");

        choice = util_read_int("Choice: ", 0, 3);

        switch (choice) {
        case 1:
            budget_add();
            util_pause();
            break;

        case 2:
            budget_list();
            util_pause();
            break;

        case 3: {
            int id;
            if (budget_count() == 0) {
                printf("  (no budget entries to remove)\n");
            } else {
                budget_list();
                id = util_read_int("Budget entry ID to remove: ", 1, 999999);
                if (util_confirm("Delete this budget entry?")) {
                    budget_remove(id);
                } else {
                    printf("  (cancelled)\n");
                }
            }
            util_pause();
            break;
        }

        case 0:
        default:
            break;
        }
    } while (choice != 0);
}