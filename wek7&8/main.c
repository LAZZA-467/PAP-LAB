#include <stdio.h>
#include <string.h>

int main(void)
{
    char supplierName[100] = "";   /* stored supplier name */
    char supplierCode[30]  = "";   /* stored supplier code */
    char tempName[100];
    int  choice;

    do
    {
        printf("\n================================\n");
        printf("MUNICIPAL FINANCIAL MANAGEMENT\n");
        printf("================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Supplier\n");
        printf("3. Search Supplier\n");
        printf("4. Show Name Length\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            /* ---------- 1. ADD SUPPLIER ---------- */
            case 1:
                printf("Enter supplier name: ");
                scanf(" %[^\n]", tempName);       /* read full line with spaces */
                strcpy(supplierName, tempName);   /* copy into stored array   */

                printf("Enter supplier code: ");
                scanf(" %[^\n]", tempName);
                strcpy(supplierCode, tempName);

                printf("Supplier added successfully.\n");
                break;

            /* ---------- 2. DISPLAY SUPPLIER ---------- */
            case 2:
                if (strlen(supplierName) == 0)
                    printf("No supplier stored yet.\n");
                else
                {
                    printf("\n--- Supplier Details ---\n");
                    printf("Name : %s\n", supplierName);
                    printf("Code : %s\n", supplierCode);
                }
                break;

            /* ---------- 3. SEARCH SUPPLIER ---------- */
            case 3:
                if (strlen(supplierName) == 0)
                    printf("No supplier stored yet.\n");
                else
                {
                    printf("Enter name to search: ");
                    scanf(" %[^\n]", tempName);

                    if (strcmp(supplierName, tempName) == 0)
                        printf("Supplier FOUND: %s (%s)\n",
                               supplierName, supplierCode);
                    else
                        printf("Supplier NOT found.\n");
                }
                break;

            /* ---------- 4. SHOW NAME LENGTH ---------- */
            case 4:
                if (strlen(supplierName) == 0)
                    printf("No supplier stored yet.\n");
                else
                {
                    printf("Supplier name length: %lu characters\n",
                           (unsigned long) strlen(supplierName));
                }
                break;

            /* ---------- 5. EXIT ---------- */
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    return 0;
}