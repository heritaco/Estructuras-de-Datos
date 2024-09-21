// Implement a program that creates a structure to store the details of the books in a library:

// title (char [15]),
// price (double)
// pages (int).

// Program must allow to register from the keyboard at least 3 books requesting the previous data title, price, etc...
// Implement a function to determine which of the registered books costs less and which costs more.
// Implement a function to identify if there are two or more books with the same number of pages. Send only one message

// INPUT:
// Book 1
//     Enter the book name: Introduction to C
//     Enter the price : 525.9
//     pages: 24
// Book 2
//     Enter the book name: Java Programming
//     Enter the price : 654.80
//     pages: 25
// Book 3
//     Enter the book name: Databases
//     Enter the price : 125.3
//     pages: 25

// OUTPUT:
// Bbook with the lowest price: Databases
// Book with the highest price: Java Programming
// "There are 2 books with the same number of pages: Java Programming, Databases

#include <stdio.h>

#define MAXBOOKS 3

// Structure to store the details of the books
struct Book
{
    char title[15];
    double price;
    int pages;
};

// Function to find the book with the maximum cost
void findMaxCost(struct Book books[])
{
    double max = books[0].price;
    int j = 0;
    for (int i = 1; i < MAXBOOKS; i++)
    {
        if (books[i].price > max)
        {
            max = books[i].price;
            j = i;
        }
    }
    printf("\nThe most expensive book is \"%s\", at a price of $%.2f\n", books[j].title, max);
}

// Function to find the book with the minimum cost
void findMinCost(struct Book books[])
{
    double min = books[0].price;
    int j = 0;
    for (int i = 1; i < MAXBOOKS; i++)
    {
        if (books[i].price < min)
        {
            min = books[i].price;
            j = i;
        }
    }
    printf("The cheapest book is \"%s\", at a price of $%.2f\n", books[j].title, min);
}

void samePages(struct Book books[])
{
    for (int i = 0; i < MAXBOOKS; i++)
    {
        for (int j = i + 1; j < MAXBOOKS; j++)
        {
            if (books[i].pages == books[j].pages)
                printf("\nThe book \"%s\" and  \"%s\" have the same pages, with: %d in total.\n", books[i].title, books[j].title, books[i].pages);
        }
    }
}

int main()
{
    struct Book books[MAXBOOKS]; // Array of structures to store the details of the books

    // Read the details of the books from the user
    for (int i = 0; i < MAXBOOKS; i++)
    {
        printf("\nBook %d\n", i + 1);
        printf("Enter the book name: ");
        scanf("%s", books[i].title);
        printf("Enter the price: ");
        scanf("%lf", &books[i].price);
        printf("Enter the number of pages: ");
        scanf("%d", &books[i].pages);
    }

    // Call the functions
    findMaxCost(books);
    findMinCost(books);
    samePages(books);

    return 0;
}