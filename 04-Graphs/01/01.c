// Graph specification based on adjacency matrix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNumV 10

char vertex[MaxNumV][20];    // Array of strings to store city names
int edges[MaxNumV][MaxNumV]; // Matrix of edges

int main()
{
    // Open the file in read mode
    FILE *fp = fopen("Vertices.txt", "r"); // the r is for read, w is for write, a is for append, r+ is for read and write
    if (fp == NULL)                        // Check if the file was opened successfully
    {
        perror("Error opening file"); // Print an error message if the file cannot be opened
        exit(-1);                     // Exit the program with a failure status
    }
    printf("File succesfully open");

    // Read the file line by line
    char city[20]; // Variable to store the city name
    int i = 0;     // Variable to store the inŊdex of the city

    // Read the file line by line
    while (!feof(fp))
    {
        fscanf(fp, "%s", city);  // Read the city name from the file
        strcpy(vertex[i], city); // Copy the city name to the vertex array
        i++;                     // Increment the index
    }
    printf("\nNumber of vertices: %d\n", i); // Print the number of vertices
    int numV = i;                            // Store the number of vertices in a variable

    // Close the file
    fclose(fp);

    // Initialize the edges matrix with zeros
    for (int i = 0; i < numV; i++)
    {
        for (int j = 0; j < numV; j++)
        {
            edges[i][j] = 0;
        }
    }

    // Open the file in read mode
    fp = fopen("Edges.txt", "r"); // the r is for read, w is for write, a is for append, r+ is for read and write

    if (fp == NULL) // Check if the file was opened successfully
    {
        perror("Error opening file"); // Print an error message if the file cannot be opened
        exit(-1);                     // Exit the program with a failure status
    }

    printf("File succesfully open");

    char cityFrom[20]; // Variable to store the first city name
    char cityTo[20];   // Variable to store the second city name
    int weight;        // Variable to store the weight of the edge

    // Read the file line by line
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d", cityFrom, cityTo, &weight); // Read the city names and weight from the file

        int k = 0; // Variable to store the index of the first city
        int j = 0; // Variable to store the index of the second city

        int foundcity1 = 0; // Variable to store if the first city is found
        int foundcity2 = 0; // Variable to store if the second city is found

        // Find the index of the first city
        for (int i = 0; i < numV; i++)
        {
            if (!foundcity1)
                if (strcmp(vertex[i], cityFrom) == 0)
                {
                    foundcity1 = 1;
                    k = i;
                    continue;
                }

            if (!foundcity2)
                if (strcmp(vertex[i], cityTo) == 0)
                {
                    foundcity2 = 1;
                    j = i;
                    continue;
                }
        }

        // Store the weight of the edge in the edges matrix
        edges[k][j] = weight;

        // Print the edge
        printf("\n%s - %s: %d", cityFrom, cityTo, weight);
    }

    // Close the file
    fclose(fp);

    return 0; // Exit the program with a success status
}