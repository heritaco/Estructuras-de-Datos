#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE *fp;
    int i;

    if ((fp = fopen("Sales.txt", "r")) == NULL)
    {
        printf("Unable to open Sales.txt\n");
        exit(-1);
    }

    printf("File successfully open\n");

    // 2. Now count the total rows in the file, to know the arrays size
    char c;
    int N = 0;

    // mientras c es igual a un caracter que no sea el final del archivo
    // fgetc lee un caracter del archivo
    // EOF es un macro que indica el final del archivo
    // si c es igual a un salto de linea, incrementamos N
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            N++;
        }
    }

    N++; // Incrementamos N para contar la ultima fila

    rewind(fp); // rewind es para volver al inicio del archivo

    printf("Number of rows: %d\n", N);

    // 3. Now we can allocate memory for the arrays

    // Dynamic memory allocation
    // *Sales is a pointer to the first element of the array
    // N * sizeof(float) is the number of bytes to allocate, N is the number of elements and sizeof(float) is the size of a float in bytes
    // malloc is a function that allocates memory in bytes
    float *Sales = (float *)malloc(N * sizeof(float));

    if (Sales == NULL)
    {
        printf("Memory allocation failed\n");
        exit(0);
    }

    printf("Memory allocated successfully\n\n");

    // 4. Now we can read the data from the file into the array

    for (i = 1; i < N + 1; i++)
        fscanf(fp, "%f", &Sales[i]);
    // fscanf reads formatted input from a file
    // fp is the file pointer
    // %f is the format specifier for a float
    // &Sales[i] is the address of the i-th element of the array
    // & before a variable name is the address-of operator, it returns the memory address of the variable

    for (i = 1; i < N + 1; i++)
        printf("Sales of employee[%d] = %f\n", i, Sales[i]);
    // printf is a function that prints formatted output to the console
    // %d is the format specifier for an integer
    // %f is the format specifier for a float
    // Sales[i] is the i-th element of the array

    // 5. Do computations with functions

    // Acc sale
    void accSale(float Sales[], int N)
    {
        printf("\nAccumulated sales\n");
        float total = 0;
        for (i = 1; i < N + 1; i++)
        {
            total += Sales[i];
            printf("Total at employee [%d] = %f\n", i, total);
        }
    }

    accSale(Sales, N);

    // Max sale
    void findMaxSale(float Sales[], int N)
    {
        float max = Sales[1];
        int j = 1;
        for (int i = 2; i < N + 1; i++)
        {
            if (Sales[i] > max)
            {
                max = Sales[i];
                j = i;
            }
        }
        printf("\nMax sale at employee [%d] = %f\n", j, max);
    }

    findMaxSale(Sales, N);

    // 6. Free the allocated memory

    free(Sales);
    // free is a function that deallocates memory
    // Sales is the pointer to the memory block to deallocate

    // 7. Close the file

    fclose(fp);
    // fclose is a function that closes a file
    // fp is the file pointer

    return 0;
}