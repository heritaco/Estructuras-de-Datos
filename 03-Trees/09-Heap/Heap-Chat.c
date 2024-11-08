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

        case 4: // ordenar el heap utilizando heap sort
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
    if (last >= MAXSIZE)
    { // verifica si hay espacio en el heap
        printf("Heap is full, cannot insert.\n");
        return;
    }
    treeNodes[last] = item; // inserta el elemento en la ultima posicion
    reHeapUp(last);         // reajusta hacia arriba para mantener la propiedad del max-heap
    last++;                 // incrementa el tamano del heap
}

// ajusta el heap hacia arriba para mantener la propiedad del max-heap
void reHeapUp(int index)
{
    int parent = (index - 1) / 2; // calcula el indice del nodo padre
    if (index > 0 && treeNodes[parent] < treeNodes[index])
    { // si el padre es menor que el nodo actual
        int temp = treeNodes[parent];
        treeNodes[parent] = treeNodes[index];
        treeNodes[index] = temp;
        reHeapUp(parent); // llamada recursiva para ajustar el nodo padre
    }
}

// elimina el nodo raiz (el maximo) del heap
int removeTop()
{
    if (last == 0)
    {
        return -1; // el heap esta vacio
    }
    int top = treeNodes[0];             // almacena el valor de la raiz
    treeNodes[0] = treeNodes[last - 1]; // reemplaza la raiz con el ultimo elemento
    treeNodes[last - 1] = -1;           // marca la ultima posicion como vacia
    last--;                             // reduce el tamano del heap
    reHeapDown(0);                      // reajusta hacia abajo para restaurar la propiedad del heap
    return top;                         // retorna el valor de la raiz eliminada
}

// ajusta el heap hacia abajo para mantener la propiedad del max-heap
void reHeapDown(int index)
{
    int largest = index;       // inicializa el indice del nodo mayor como el nodo actual
    int left = 2 * index + 1;  // calcula el indice del hijo izquierdo
    int right = 2 * index + 2; // calcula el indice del hijo derecho

    // verifica si el hijo izquierdo es mayor que el nodo actual
    if (left < last && treeNodes[left] > treeNodes[largest])
    {
        largest = left;
    }
    // verifica si el hijo derecho es mayor que el nodo mayor actual
    if (right < last && treeNodes[right] > treeNodes[largest])
    {
        largest = right;
    }
    // si el nodo mayor no es el nodo actual, realiza un intercambio
    if (largest != index)
    {
        int temp = treeNodes[index];
        treeNodes[index] = treeNodes[largest];
        treeNodes[largest] = temp;
        reHeapDown(largest); // llamada recursiva para ajustar el nodo intercambiado
    }
}

// muestra la estructura del heap en orden de niveles
void showHeap()
{
    if (last == 0)
    { // verifica si el heap esta vacio
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap structure:\n");
    for (int i = 0; i < last; i++)
    {                                // recorre los elementos del heap
        printf("%d ", treeNodes[i]); // imprime cada nodo en una sola linea
    }
    printf("\n");
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
