#ifndef BUDGET_H
#define BUDGET_H

/*
 * budget.h - income / expense records and the budget sub-menu.
 */

#include "config.h"

typedef enum {
    BUDGET_INCOME  = 0,
    BUDGET_EXPENSE = 1
} BudgetType;

typedef struct {
    int        id;
    char       category[MAX_CATEGORY_LEN];
    char       description[MAX_DESC_LEN];
    BudgetType type;
    double     amount;
} BudgetEntry;

/* Life-cycle */
void budget_init(void);

/* Queries */
int                budget_count(void);
const BudgetEntry *budget_get(int index);      /* NULL if index invalid */
double             budget_total_income(void);
double             budget_total_expense(void);
double             budget_balance(void);       /* income - expense       */

/* Mutations */
int budget_add(void);                          /* returns index or -1 */
int budget_remove(int id);                     /* returns 1 on success */

/* Presentation */
void budget_list(void);
void budget_menu(void);

#endif /* BUDGET_H */