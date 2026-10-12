#ifndef REPORTS_H
#define REPORTS_H

/*
 * reports.h - reporting layer.
 * reports.c calls functions from employees.h and budget.h, so it never
 * touches their internal data directly.
 */

void reports_employee_report(void);
void reports_budget_report(void);
void reports_summary(void);
void reports_menu(void);

#endif /* REPORTS_H */