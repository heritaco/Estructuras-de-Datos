// We have an ATM in which there are eight denominations of bills: 1, 2, 5,
// 10, 50, 100, 500 and 1000. If by keyboard an integer amount N of money to be
// withdrawn is entered, write a program to calculate the smallest number of bills
// that combined give the amount N

#include <stdio.h>

int main()
{
    int amount, bills[8] = {1000, 500, 100, 50, 10, 5, 2, 1}, i, count;
    int total_bills = 0; // Variable to keep track of the total number of bills

    printf("Enter the amount of money to be withdrawn: ");
    scanf("%d", &amount);

    for (i = 0; i < 8; i++)
    {
        count = amount / bills[i];
        amount = amount % bills[i];
        printf("Number of %d bills: %d\n", bills[i], count);
        total_bills += count; // Add the count to the total number of bills
    }

    // Print the total number of bills
    printf("Total number of bills: %d\n", total_bills);

    return 0;
}