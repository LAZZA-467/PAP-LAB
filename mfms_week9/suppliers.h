#ifndef SUPPLIERS_H
#define SUPPLIERS_H

/*
 * suppliers.h - optional extension module.
 * Adding this module required no changes to employees.c, budget.c,
 * utilities.c or reports.c - only main.c gained two lines.
 */

#include "config.h"

typedef struct {
    int    id;
    char   company[MAX_NAME_LEN];
    char   contact[MAX_NAME_LEN];
    char   phone[MAX_NAME_LEN];
    double balance_owed;        /* what the MFMS still owes the supplier */
} Supplier;

void            suppliers_init(void);
int             suppliers_count(void);
const Supplier *suppliers_get(int index);   /* NULL if index invalid */
double          suppliers_total_owed(void);
void            suppliers_menu(void);

#endif /* SUPPLIERS_H */