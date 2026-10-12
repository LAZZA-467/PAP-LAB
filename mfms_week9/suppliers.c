/*
 * suppliers.c - supplier records (challenge / extension module).
 */
#include <stdio.h>
#include <string.h>

#include "suppliers.h"
#include "utilities.h"

static Supplier records[MAX_SUPPLIERS];
static int      record_count = 0;
static int      next_id      = 5001;

static int suppliers_find_index(int id)
{
    int i;

    for (i = 0; i < record_count; i++) {
        if (records[i].id == id) {
            return i;
        }
    }
    return -1;
}

void suppliers_init(void)
{
    record_count = 0;
    next_id      = 5001;
}

int suppliers_count(void)
{
    return record_count;
}

const Supplier *suppliers_get(int index)
{
    if (index < 0 || index >= record_count) {
        return NULL;
    }
    return &records[index];
}

double suppliers_total_owed(void)
{
    int    i;
    double total = 0.0;

    for (i = 0; i < record_count; i++) {
        total += records[i].balance_owed;
    }
    return total;
}

static int suppliers_add(void)
{
    Supplier *s;

    if (record_count >= MAX_SUPPLIERS) {
        printf("  ! Supplier limit (%d) reached.\n", MAX_SUPPLIERS);
        return -1;
    }

    s = &records[record_count];
    memset(s, 0, sizeof *s);
    s->id = next_id++;

    printf("\n-- New supplier (assigned ID %d) --\n", s->id);
    util_read_string("Company        : ", s->company, sizeof s->company);
    util_read_string("Contact person : ", s->contact, sizeof s->contact);
    util_read_string("Phone          : ", s->phone, sizeof s->phone);
    s->balance_owed = util_read_double("Balance owed   : ", 0.0, 100000000.0);

    record_count++;
    printf("  + Supplier \"%s\" added.\n", s->company);
    return record_count - 1;
}

static void suppliers_list(void)
{
    int i;

    if (record_count == 0) {
        printf("  (no suppliers recorded yet)\n");
        return;
    }

    printf("\n%-6s %-20s %-18s %-14s %12s\n",
           "ID", "Company", "Contact", "Phone", "Owed");
    util_print_line();

    for (i = 0; i < record_count; i++) {
        printf("%-6d %-20s %-18s %-14s %12.2f\n",
               records[i].id,
               records[i].company,
               records[i].contact,
               records[i].phone,
               records[i].balance_owed);
    }

    util_print_line();
    printf("%d supplier(s), total owed %.2f\n",
           record_count, suppliers_total_owed());
}

static int suppliers_remove(int id)
{
    int index = suppliers_find_index(id);
    int i;

    if (index < 0) {
        printf("  ! No supplier with ID %d.\n", id);
        return 0;
    }

    for (i = index; i < record_count - 1; i++) {
        records[i] = records[i + 1];
    }
    record_count--;
    printf("  - Supplier %d removed.\n", id);
    return 1;
}

void suppliers_menu(void)
{
    int choice;

    do {
        util_print_header("SUPPLIER MANAGEMENT");
        printf("  1. Add supplier\n");
        printf("  2. List suppliers\n");
        printf("  3. Remove supplier\n");
        printf("  4. Total amount owed\n");
        printf("  0. Back to main menu\n");

        choice = util_read_int("Choice: ", 0, 4);

        switch (choice) {
        case 1:
            suppliers_add();
            util_pause();
            break;

        case 2:
            suppliers_list();
            util_pause();
            break;

        case 3: {
            int id;
            if (suppliers_count() == 0) {
                printf("  (no suppliers to remove)\n");
            } else {
                suppliers_list();
                id = util_read_int("Supplier ID to remove: ", 1, 999999);
                if (util_confirm("Delete this supplier?")) {
                    suppliers_remove(id);
                } else {
                    printf("  (cancelled)\n");
                }
            }
            util_pause();
            break;
        }

        case 4:
            printf("\n  Total owed to suppliers: %.2f\n",
                   suppliers_total_owed());
            util_pause();
            break;

        case 0:
        default:
            break;
        }
    } while (choice != 0);
}