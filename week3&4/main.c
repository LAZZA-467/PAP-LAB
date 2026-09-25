#include <stdio.h>
#include <string.h>

int main(void)
{
    char employeeName[50];
    double basicSalary, allowances, deductions;
    double grossSalary, netSalary;

    const double HIGH_INCOME_THRESHOLD = 20000.00;

    printf("EMPLOYEE SALARY CALCULATOR\n");
    printf("==========================\n\n");

    printf("Enter employee name: ");
    fgets(employeeName, sizeof(employeeName), stdin);

    /* Remove the newline character left by fgets */
    employeeName[strcspn(employeeName, "\n")] = '\0';

    printf("Enter basic salary: ");
    scanf("%lf", &basicSalary);

    printf("Enter allowances: ");
    scanf("%lf", &allowances);

    printf("Enter deductions: ");
    scanf("%lf", &deductions);


    grossSalary = basicSalary + allowances;


    netSalary = grossSalary - deductions;

    printf("\n--- Salary Summary ---\n");
    printf("Employee: %s\n", employeeName);
    printf("Gross Salary: NAD %.2f\n", grossSalary);
    printf("Net Salary:   NAD %.2f\n", netSalary);

    if (netSalary >= HIGH_INCOME_THRESHOLD)
    {
        printf("High Income\n");
    }
    else
    {
        printf("Standard Income\n");
    }

    return 0;
}