#include <stdio.h>
#include <stdlib.h>

int *stack; // Puntero para el stack dinámico
int top;
int stackSize; // Tamaño actual del stack

// Función para inicializar el stack dinámico con un tamaño dado por el usuario
void initStack(int initialSize)
{
    stack = (int *)malloc(initialSize * sizeof(int)); // Inicializamos con el tamaño dado por el usuario
    top = 0;
    stackSize = initialSize;
}

int isEmpty()
{
    return top == 0;
}

// Función para redimensionar el stack cuando está lleno
void resizeStack()
{
    stackSize++; // hacemos el stack un lugar más grande
    stack = (int *)realloc(stack, stackSize * sizeof(int));
    // realloc() cambia el tamaño de la memoria asignada previamente
    // malloc() es para asignar memoria por primera vez
    printf("Stack resized to %d\n", stackSize);
}

void push(int value)
{
    if (top == stackSize)
    {
        resizeStack(); // Si el stack está lleno, lo redimensionamos
    }
    stack[top] = value;
    top++;
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack is empty. Cannot pop\n");
        return -1; // Valor de error
    }
    top--;
    return stack[top];
}

void printStack()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack:\n");
    for (int i = top - 1; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
}

int main()
{
    int initialSize;

    printf("Enter the initial size of the stack: ");
    scanf("%d", &initialSize);

    initStack(initialSize); // Inicializamos el stack con el tamaño dado por el usuario

    printf("1) Push\n2) Pop\n3) Print the stack\n0) to exit\n");

    int option;
    int value;

    do
    {
        printf("\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            value = pop();
            if (value != -1) // Asegurarse de que no hubo error en pop()
                printf("Popped value: %d\n", value);
            break;
        case 3:
            printStack();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option\n");
            break;
        }
    } while (option != 0);

    free(stack); // Liberamos la memoria antes de salir

    return 0;
}
