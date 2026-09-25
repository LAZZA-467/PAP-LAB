#include <stdio.h>
#include <string.h>

int main(void)
{
    float salaries[50], budgets[10];
    char  registrations[20][20];
    int i, j;
    float sum, avg, highest, lowest, target, temp;
    char  regTarget[20];
    int   found;

    printf("Enter 50 employee salaries:\n");
    for (i = 0; i < 50; i++)
        scanf("%f", &salaries[i]);

    printf("\nAll Salaries:\n");
    for (i = 0; i < 50; i++)
        printf("%.2f\n", salaries[i]);

    sum = 0;
    highest = lowest = salaries[0];
    for (i = 0; i < 50; i++) {
        sum += salaries[i];
        if (salaries[i] > highest) highest = salaries[i];
        if (salaries[i] < lowest)  lowest  = salaries[i];
    }
    avg = sum / 50;
    printf("\nAverage: %.2f\nHighest: %.2f\nLowest: %.2f\n", avg, highest, lowest);

    printf("Enter salary to search: ");
    scanf("%f", &target);
    found = 0;
    for (i = 0; i < 50; i++)
        if (salaries[i] == target) {
            printf("Found at position %d\n", i + 1);
            found = 1;
            break;
        }
    if (!found) printf("Salary not found\n");

    printf("\nEnter 10 department budgets:\n");
    for (i = 0; i < 10; i++)
        scanf("%f", &budgets[i]);

    printf("\nBudgets:\n");
    for (i = 0; i < 10; i++)
        printf("%.2f\n", budgets[i]);

    sum = 0;
    for (i = 0; i < 10; i++)
        sum += budgets[i];
    printf("\nTotal Budget: %.2f\nAverage Budget: %.2f\n", sum, sum / 10);

    for (i = 0; i < 9; i++)
        for (j = 0; j < 9 - i; j++)
            if (budgets[j] > budgets[j + 1]) {
                temp = budgets[j];
                budgets[j] = budgets[j + 1];
                budgets[j + 1] = temp;
            }

    printf("\nBudgets Sorted (Lowest to Highest):\n");
    for (i = 0; i < 10; i++)
        printf("%.2f\n", budgets[i]);

    printf("\nEnter 20 registration numbers:\n");
    for (i = 0; i < 20; i++)
        scanf(" %19s", registrations[i]);

    printf("\nAll Registrations:\n");
    for (i = 0; i < 20; i++)
        printf("%s\n", registrations[i]);

    printf("\nEnter registration to search: ");
    scanf(" %19s", regTarget);

    found = 0;
    for (i = 0; i < 20; i++)
        if (strcmp(registrations[i], regTarget) == 0) {
            printf("Found at position %d\n", i + 1);
            found = 1;
            break;
        }
    if (!found) printf("Registration not found\n");

    return 0;
}