// leer un archivo de texto se lee cada linea, vemos si la info quedo en nuestro arreglo de tipo ventas

#include <stdio.h>  // Include standard input/output library
#include <stdlib.h> // Include standard library for exit functions

#define MAXEMP 10 // Define a constant for the maximum number of employees

int main()
{
    // File path
    const char *filePath = "C:\\Users\\herie\\OneDrive\\Documentos\\GitHub\\Estructuras_de_Datos\\Clase_03\\Sales.txt";
    // it has a * because it is a pointer
    // a pointer is a variable that stores the memory address of another variable

    // Open the file in read mode
    FILE *fp = fopen(filePath, "r"); // the r is for read, w is for write, a is for append, r+ is for read and write
    if (fp == NULL)                  // Check if the file was opened successfully
    {
        perror("Error opening file"); // Print an error message if the file cannot be opened
        return EXIT_FAILURE;          // Exit the program with a failure status
    }

    // Array to store sales data
    float Sales[MAXEMP];

    // Read data from the file into the array
    for (int i = 0; i < MAXEMP; i++)
    {
        // Read a float value from the file and store it in the array
        if (fscanf(fp, "%f", &(Sales[i])) != 1)
        {
            // Print an error message if reading fails
            fprintf(stderr, "Error reading data for Sales[%d]\n", i);
            fclose(fp);          // Close the file
            return EXIT_FAILURE; // Exit the program with a failure status
        }
    }

    // Verify the data was correctly loaded by printing it
    for (int i = 0; i < MAXEMP; i++)
        printf("Sales[%d] = %f\n", i, Sales[i]);

    // Close the file
    fclose(fp);

    return 0; // Exit the program with a success status
}