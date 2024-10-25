#include <stdio.h>

int main()
{
    int arrayint[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Print the elements of the array
    printf("Elements of arrayint: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arrayint[i]);
    }
    printf("\n");

    int arrayint2[10] = {1, 2};
    // Print the elements of the array
    printf("Elements of arrayint: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arrayint2[i]);
    }
    printf("\n");

    return 0;
}
