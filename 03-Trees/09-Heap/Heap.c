/******************************************************************************
Given this code change the least possible to make it work as expected.
Implement an application in C to perform the operations of
insertion, deletion, deployment and ordering of nodes from
a Heap binary tree.
Use an options menu to show the correct functioning of the
above mentioned operations.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 // define el tamano maximo del heap

// prototipos de funciones
void insert(int item);
void reHeapUp(int index);
int removeTop();
void reHeapDown(int i);
void showHeap();
void sortHeap();

// variables globales
int treeNodes[MAXSIZE]; // arreglo que almacena los nodos del heap
int last = 0;           // indice que representa el tamano actual del heap

int main()
{
    int choice, item, result;

    // inicializa el heap con valores invalidos (-1) indicando espacios vacios
    for (int i = 0; i < MAXSIZE; i++)
        treeNodes[i] = -1;

    // ciclo infinito para mostrar el menu de opciones al usuario
    while (1)
    {
        printf("\nHeap Operations Menu:");
        printf("\n1. Insert node");     // opcion para insertar un nodo
        printf("\n2. Delete top node"); // opcion para eliminar el nodo raiz
        printf("\n3. Display heap");    // opcion para mostrar el heap
        printf("\n4. Sort heap");       // opcion para ordenar el heap
        printf("\n5. Exit");            // opcion para salir del programa
        printf("\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // insertar un nodo
            printf("Enter the value to insert: ");
            scanf("%d", &item);
            insert(item);
            printf("Node inserted successfully.\n");
            break;

        case 2: // eliminar el nodo raiz (tope del heap)
            result = removeTop();
            if (result != -1)
            {
                printf("Deleted top node: %d\n", result);
            }
            else
            {
                printf("Heap is empty, nothing to delete.\n");
            }
            break;

        case 3: // mostrar el contenido del heap
            printf("Displaying the heap:\n");
            showHeap();
            break;

        case 4: // ordenar el heap
            printf("Sorting the heap:\n");
            sortHeap();
            break;

        case 5: // salir del programa
            printf("Exiting...\n");
            exit(0);
            break;

        default: // manejar entrada invalida
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

// inserta un nodo en el heap
void insert(int item)
{
    treeNodes[last] = item;
    reHeapUp(last); // put the new element in the correct place
    last++;
}
// ajusta el heap hacia arriba para mantener la propiedad del max-heap
void reHeapUp(int index)
{
    int i = index;
    int iPrnt = (i - 1) / 2;

    if (iPrnt < 0)
        return;

    if (treeNodes[iPrnt] < treeNodes[i])
    {
        printf("\n\n... reheap UP");
        int aux = treeNodes[iPrnt];
        treeNodes[iPrnt] = treeNodes[i];
        treeNodes[i] = aux;

        reHeapUp(iPrnt);
    }
}

// elimina el nodo raiz
int removeTop()
{
    if (last == 0) // heap empty
        return -1;

    int val = treeNodes[0]; // the root

    treeNodes[0] = treeNodes[last - 1]; // the last is the root
    treeNodes[last - 1] = -1;           // mark this node as invalid
    last--;

    reHeapDown(0); // test to put the new root in the correct place

    return val;
}

// ajusta el heap hacia abajo para mantener la propiedad del max-heap
void reHeapDown(int i)
{
    int index = i;

    // exchange parent with the greater of its children
    int ln = 2 * index + 1; // the left one
    int rn = 2 * index + 2; // the right one

    if (treeNodes[ln] == -1) // we reached a leaf
        return;

    // this parent has at least one child. Decide if
    // exchange is required and the child to exchange

    if (treeNodes[ln] > treeNodes[index])
    { // left greater than parent
        if (treeNodes[rn] == -1)
        { // exchange parent with left node is no right child
            printf("\n\n... reheap DOWN left");
            int temp = treeNodes[index];
            treeNodes[index] = treeNodes[ln];
            treeNodes[ln] = temp;
            reHeapDown(ln);
        }
        else
        { // exchange with right node only if it is greater than left one
            if (treeNodes[rn] > treeNodes[ln])
            { // exchange parent with right node
                printf("\n\n... reheap DOWN right");
                int temp = treeNodes[index];
                treeNodes[index] = treeNodes[rn];
                treeNodes[rn] = temp;
                reHeapDown(rn);
            }
            else
            {
                printf("\n\n... reheap DOWN left");
                int temp = treeNodes[index];
                treeNodes[index] = treeNodes[ln];
                treeNodes[ln] = temp;
                reHeapDown(ln);
            }
        }
    }
    else
    { // exchange wih right node only if it is greater than parent
        if (treeNodes[rn] > treeNodes[index])
        { // exchange parent with right node
            printf("\n\n... reheap DOWN right");
            int temp = treeNodes[index];
            treeNodes[index] = treeNodes[rn];
            treeNodes[rn] = temp;
            reHeapDown(rn);
        }
    }
}

// muestra la estructura del heap en orden de niveles
void showHeap()
{
    if (last == 0)
    {
        printf("\n  .. heap is empty");
        return;
    }

    printf("\n\n  .. ... heap .. ..");
    for (int i = 0; i <= last - 1; i++)
    {
        printf("\nNode %d", treeNodes[i]);
        int li = 2 * i + 1;
        int ri = 2 * i + 2;
        if (treeNodes[li] != -1)
            printf("\n\t Left Node %d", treeNodes[li]);

        if (treeNodes[ri] != -1)
            printf("\n\t Right Node %d", treeNodes[ri]);
    }

    printf("\n  .. ... ... .. ..");
}

// ordena los elementos del heap usando heap sort
void sortHeap()
{
    int originalSize = last; // guarda el tamano original del heap
    while (last > 1)
    {
        // intercambia el nodo raiz con el ultimo nodo
        int temp = treeNodes[0];
        treeNodes[0] = treeNodes[last - 1];
        treeNodes[last - 1] = temp;
        last--;        // reduce el tamano del heap para "eliminar" el ultimo nodo
        reHeapDown(0); // ajusta el nuevo nodo raiz
    }
    last = originalSize; // restaura el tamano original del heap

    printf("Sorted elements:\n");
    for (int i = 0; i < originalSize; i++)
    { // imprime los elementos ordenados
        printf("%d ", treeNodes[i]);
    }
    printf("\n");
}