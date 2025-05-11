#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNumV 10
int dfs();
int top = 0;
int STACK_SIZE = 20;
int NumV = 0;
char stack[20][20];

void push(char *value);
char *pop(char stack[]);

char vertex[MaxNumV][20];    // array of strings, each a city of 20 chars max
int edges[MaxNumV][MaxNumV]; // matrix for edges

int main()
{

    // First read vertex

    FILE *fp = fopen("Vertices.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open test file...");
        exit(-1);
    }

    printf("File successfully open...");
    char city[20];
    int i = 0;

    while (!feof(fp))
    {
        fscanf(fp, "%s", vertex[i]);
        printf("\nCity %d: %s", i, vertex[i]);
        i++;
    }

    printf("\n\nNum of vertex in file: %d\n\n", i);
    NumV = i;

    fclose(fp);

    // Now read edges, and fill out the adjacency matriz

    fp = fopen("Edges.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open test filen");
        exit(-1);
    }

    printf("File successfully open...");

    int cost;
    char cityFrom[20];
    char cityTo[20];

    while (!feof(fp))
    {
        fscanf(fp, "%s", cityFrom);
        fscanf(fp, "%s", cityTo);
        fscanf(fp, "%d", &cost);

        // find cityies in array, then fill out the adjacency matrix
        int k = 0;
        int j = 0;
        int foundCity1 = 0;
        int foundCity2 = 0;

        for (i = 0; i < NumV; i++)
        {
            if (!foundCity1)
                if (strcmp(vertex[i], cityFrom) == 0)
                {
                    foundCity1 = 1;
                    k = i;
                    continue;
                }
            if (!foundCity2)
                if (strcmp(vertex[i], cityTo) == 0)
                {
                    foundCity2 = 1;
                    j = i;
                }

            if (foundCity1 && foundCity2)
            {
                break;
            }
        }

        edges[k][j] = cost; // here should be the 'cost'

        printf("\n<From '%s'(%d) to '%s'(%d): %d>", cityFrom, k, cityTo, j, cost);
    }

    printf("\n\nAdjacency matrix (cost in matrix): \n");
    // print the adjacency matrixz
    printf("\n    ");
    for (int k = 0; k < NumV; k++)
        printf("%d\t", k);
    printf("\n    ");
    for (int k = 0; k < NumV; k++)
        printf("-------");

    for (int k = 0; k < NumV; k++)
    {
        printf("\n %d| ", k);
        for (int j = 0; j < NumV; j++)
            printf("%d\t", edges[k][j]);
    }
    printf("\n\n");

    fclose(fp);
    dfs("a", "d");

    return 0;
}
int dfs(char *cityFrom, char *cityTo)
{
    printf("Seaching if path exists from %s to %s...", cityFrom, cityTo);
    char val[20];
    int found = 0;
    push(cityFrom);
    printf("\n\n");
    pop(val);
    printf("->   %s", val);
    if (strcmp(val, cityTo) == 0)
    {
        found = 1;
    }
    else
    {
        while (!isEmpty() && !found)
        {
            int k = 0;
            for (int i = 0; i < NumV; i++)
            {
                if (strcmp(vertex[i], val) == 0)
                {
                    k = i; // regresa el índice del nodo en el arreglo
                    break;
                }
            }
            for (int j = 0; j < NumV; j++)
            {
                if (edges[k][j] != 0)
                {
                    push(vertex[j]);
                }
            }
        }
        if (!found)
        {
            printf("\nPath does not exist");
        }
    }
}
int isEmpty()
{
    if (top == 0)
        return 1;
    else
        return 0;
}

int isFull(int STACK_SIZE)
{
    if (top == STACK_SIZE)
        return 1;
    else
        return 0;
}

void push(char *value)
{
    if (isFull(STACK_SIZE))
    {
        printf("Stack is full! Cannot push '%s'.\n", value);
        return;
    }
    strcpy(stack[top], value);
    top++;
}

char *pop(char *value)
{
    if (isEmpty())
    {
        printf("Stack is empty! Cannot pop.\n");
        return NULL;
    }
    top--;
    strcpy(value, stack[top]);
    return value;
}
