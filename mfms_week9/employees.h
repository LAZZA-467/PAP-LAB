#ifndef EMPLOYEES_H
#define EMPLOYEES_H

/*
 * employees.h - employee record type and the employee sub-menu.
 */

#include "config.h"

typedef struct {
    int    id;
    char   name[MAX_NAME_LEN];
    char   position[MAX_NAME_LEN];
    double salary;              /* monthly salary */
} Employee;

/* Life-cycle */
void employees_init(void);

/* Queries */
int             employees_count(void);
const Employee *employees_get(int index);      /* NULL if index invalid */
int             employees_find_index(int id);  /* -1 if not found      */
double          employees_total_salary(void);

/* Mutations */
int  employees_add(void);                      /* returns index or -1 */
int  employees_update(int id);                 /* returns 1 on success */
int  employees_remove(int id);                 /* returns 1 on success */

/* Presentation */
void employees_list(void);
void employees_menu(void);

#endif /* EMPLOYEES_H */