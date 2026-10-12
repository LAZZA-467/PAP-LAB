/*
 * employees.c - everything the MFMS knows about employees.
 */
#include <stdio.h>
#include <string.h>

#include "employees.h"
#include "utilities.h"

/* ---- module-private state ------------------------------------------- */
static Employee records[MAX_EMPLOYEES];
static int      record_count = 0;
static int      next_id      = 1001;
/* --------------------------------------------------------------------- */

void employees_init(void)
{
    record_count = 0;
    next_id      = 1001;
}

int employees_count(void)
{
    return record_count;
}

const Employee *employees_get(int index)
{
    if (index < 0 || index >= record_count) {
        return NULL;
    }
    return &records[index];
}

int employees_find_index(int id)
{
    int i;

    for (i = 0; i < record_count; i++) {
        if (records[i].id == id) {
            return i;
        }
    }
    return -1;
}

double employees_total_salary(void)
{
    int    i;
    double total = 0.0;

    for (i = 0; i < record_count; i++) {
        total += records[i].salary;
    }
    return total;
}

int employees_add(void)
{
    Employee *e;

    if (record_count >= MAX_EMPLOYEES) {
        printf("  ! Employee limit (%d) reached.\n", MAX_EMPLOYEES);
        return -1;
    }

    e = &records[record_count];
    memset(e, 0, sizeof *e);
    e->id = next_id++;

    printf("\n-- New employee (assigned ID %d) --\n", e->id);
    util_read_string("Name           : ", e->name, sizeof e->name);
    util_read_string("Position       : ", e->position, sizeof e->position);
    e->salary = util_read_double("Monthly salary : ", 0.0, 1000000.0);

    record_count++;
    printf("  + Employee \"%s\" added.\n", e->name);
    return record_count - 1;
}

void employees_list(void)
{
    int i;

    if (record_count == 0) {
        printf("  (no employees recorded yet)\n");
        return;
    }

    printf("\n%-6s %-20s %-20s %12s\n", "ID", "Name", "Position", "Salary");
    util_print_line();

    for (i = 0; i < record_count; i++) {
        printf("%-6d %-20s %-20s %12.2f\n",
               records[i].id,
               records[i].name,
               records[i].position,
               records[i].salary);
    }

    util_print_line();
    printf("%d employee(s), total payroll %.2f\n",
           record_count, employees_total_salary());
}

int employees_update(int id)
{
    int       index = employees_find_index(id);
    Employee *e;

    if (index < 0) {
        printf("  ! No employee with ID %d.\n", id);
        return 0;
    }

    e = &records[index];
    printf("\n-- Updating employee %d --\n", e->id);
    util_read_string("New name           : ", e->name, sizeof e->name);
    util_read_string("New position       : ", e->position, sizeof e->position);
    e->salary = util_read_double("New monthly salary : ", 0.0, 1000000.0);

    printf("  * Employee %d updated.\n", e->id);
    return 1;
}

int employees_remove(int id)
{
    int index = employees_find_index(id);
    int i;

    if (index < 0) {
        printf("  ! No employee with ID %d.\n", id);
        return 0;
    }

    printf("  - Removing %s (ID %d).\n", records[index].name, id);

    /* Close the gap so the array stays contiguous. */
    for (i = index; i < record_count - 1; i++) {
        records[i] = records[i + 1];
    }
    record_count--;
    return 1;
}

void employees_menu(void)
{
    int choice;

    do {
        util_print_header("EMPLOYEE MANAGEMENT");
        printf("  1. Add employee\n");
        printf("  2. List employees\n");
        printf("  3. Update employee\n");
        printf("  4. Remove employee\n");
        printf("  0. Back to main menu\n");

        choice = util_read_int("Choice: ", 0, 4);

        switch (choice) {
        case 1:
            employees_add();
            util_pause();
            break;

        case 2:
            employees_list();
            util_pause();
            break;

        case 3: {
            int id;
            if (employees_count() == 0) {
                printf("  (no employees to update)\n");
            } else {
                employees_list();
                id = util_read_int("Employee ID to update: ", 1, 999999);
                employees_update(id);
            }
            util_pause();
            break;
        }

        case 4: {
            int id;
            if (employees_count() == 0) {
                printf("  (no employees to remove)\n");
            } else {
                employees_list();
                id = util_read_int("Employee ID to remove: ", 1, 999999);
                if (util_confirm("Delete this employee?")) {
                    employees_remove(id);
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