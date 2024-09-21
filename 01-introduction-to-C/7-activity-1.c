// We have an ATM in which there are eight denominations of bills: 1, 2, 5,
// 10, 50, 100, 500 and 1000. If by keyboard an integer amount N of money to be
// withdrawn is entered, write a program to calculate the smallest number of bills
// that combined give the amount N

#include <stdio.h> // Include the input/output library

int main()
{
    int amount;                // Declare the variable amount
    int number_of_tickets = 0; // Declare and initialize the variable number_of_tickets

    printf("Enter the amount you wish to withdraw: ");
    scanf("%d", &amount); // %d because it is an integer, &amount because it is a pointer

    // If the amount is greater than or equal to 1000
    if (amount >= 1000)
    {
        int tickets = amount / 1000;    // Calculate the number of $1000 bills
        printf("$1000: %d\n", tickets); // Print the number of $1000 bills
        number_of_tickets += tickets;   // Add to the total number of tickets
        amount = amount % 1000;         // Now the amount is the remainder of the division by 1000
    }

    // The same as before for all the other bills
    if (amount >= 500)
    {
        int tickets = amount / 500;
        printf("$500: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 500;
    }

    if (amount >= 100)
    {
        int tickets = amount / 100;
        printf("$100: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 100;
    }

    if (amount >= 50)
    {
        int tickets = amount / 50;
        printf("$50: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 50;
    }

    if (amount >= 10)
    {
        int tickets = amount / 10;
        printf("$10: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 10;
    }

    if (amount >= 5)
    {
        int tickets = amount / 5;
        printf("$5: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 5;
    }

    if (amount >= 2)
    {
        int tickets = amount / 2;
        printf("$2: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 2;
    }

    if (amount >= 1)
    {
        int tickets = amount / 1;
        printf("$1: %d\n", tickets);
        number_of_tickets += tickets;
        amount = amount % 1;
    }

    // Print the total number of tickets
    printf("Number of tickets: %d\n", number_of_tickets);

    return 0;
}