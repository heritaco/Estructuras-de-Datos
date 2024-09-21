// The pointers are used to store the address of the memory location.
// Para generar estructuras de datos dinamicas, se utilizan punteros.

#include <stdio.h>  // Include standard input/output library
#include <stdlib.h> // Include standard library for exit functions

int main()
{
    int N;
    printf("Enter the number of elements: ");
    scanf("%d", &N);

    // Dynamic memory allocation
    int *arr = (int *)malloc(N * sizeof(int)); // malloc is a function that allocates memory in bytes
    // malloc returns a void pointer, so we need to cast it to the desired type
    // (int *) is a type cast, it converts the void pointer to an integer pointer
    // N * sizeof(int) is the number of bytes to allocate, N is the number of elements and sizeof(int) is the size of an integer in bytes
    // *arr is a pointer to the first element of the array

    if (arr == NULL) // Check if memory allocation was successful
    {
        perror("Error allocating memory"); // Print an error message if memory allocation fails
        exit(0);                           // Exit the program with a failure status
    }

    printf("Memory allocated successfully");

    printf("\nPlease, enter the %d elements of the array: ", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    int sum = 0;
    int min = arr[0];
    int max = arr[0];
    printf("Here your %d ints in reverse order: ", N);
    for (int i = N - 1; i >= 0; i--)
    {
        printf("%d ", arr[i]);
        sum += arr[i];
        if (arr[i] < min)
        {
            min = arr[i];
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("\nSum: %d\n", sum);
    printf("Min: %d\n", min);
    printf("Max: %d\n", max);

    free(arr); // Free the allocated memory

    return 0; // Exit the program with a success status
}
