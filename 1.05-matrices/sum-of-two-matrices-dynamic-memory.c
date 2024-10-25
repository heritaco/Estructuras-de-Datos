#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Sum of two matrices\n\n");

    // Declare variables
    int col;
    int row;

    // Ask the user for the number of rows and columns
    printf("Enter the number of rows: ");
    scanf("%d", &row);

    printf("Enter the number of columns: ");
    scanf("%d", &col);

    // Allocate memory for the matrices
    int *matrix1 = (int *)malloc(row * col * sizeof(int));
    int *matrix2 = (int *)malloc(row * col * sizeof(int));
    int *result = (int *)malloc(row * col * sizeof(int));

    // Check if memory allocation was successful
    if (matrix1 == NULL || matrix2 == NULL || result == NULL)
    {
        perror("Error allocating memory");
        exit(0);
    }

    printf("\nMemory allocated successfully\n");

    // Ask the user for the elements of the matrices
    printf("\nPlease, enter the %d elements of the first matrix separated by a space, example:", row * col);

    // Print the example
    for (int i = 1; i < row * col + 1; i++)
    {
        printf(" %d", i);
    }
    printf("\n");

    // Read the elements of the first matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &matrix1[i * col + j]);
        }
        // i didnt know how to do the input in different lines
    }

    // Read the elements of the second matrix
    printf("\nPlease, enter the %d elements of the second martix separated by a space:\n", row * col);
    for (int i = 0; i < row * col; i++)
        scanf("%d", &matrix2[i]);

    // Print the sum of the matrices
    printf("\nThe sum of the matrices is:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // It sums position by position
            result[i * col + j] = matrix1[i * col + j] + matrix2[i * col + j];
            printf("%d \t", result[i * col + j]);
        }
        // Print a new line after each row
        printf("\n");
    }

    // Free the allocated memory
    free(matrix1);
    free(matrix2);
    free(result);

    // Exit the program
    return 0;
}