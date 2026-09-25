#include <stdio.h>

int main(void)
{
    double totalRevenue, totalExpenses, balance;

    

    printf("MUNICIPAL BUDGET CALCULATOR\n");
    printf("============================\n\n");


    printf("Enter total revenue: ");
    scanf("%lf", &totalRevenue);

    printf("Enter total expenses: ");
    scanf("%lf", &totalExpenses);

    balance = totalRevenue - totalExpenses;

    printf("\n--- Budget Summary ---\n");
    printf("Revenue:  %.2f\n", totalRevenue);
    printf("Expenses: %.2f\n", totalExpenses);
    printf("Balance:  %.2f\n", balance);

    return 0;
}