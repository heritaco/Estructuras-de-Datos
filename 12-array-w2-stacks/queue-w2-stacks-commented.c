#include <stdio.h>
#include <stdlib.h>

// Definimos una estructura para la Pila (Stack)
typedef struct Stack
{
    int *arr; // Puntero a un arreglo de enteros, que serán los elementos de la pila
    int top;  // Índice del elemento en la cima (top) de la pila
    int max;  // Tamaño máximo de la pila
} Stack;

// Inicializa la pila
void initStack(Stack *stack, int size)
{
    stack->arr = (int *)malloc(size * sizeof(int)); // Asigna memoria dinámica para el arreglo de la pila

    // Si no se puede asignar memoria, muestra un error y sale del programa
    if (stack->arr == NULL)
    {
        printf("\n¡Error al asignar memoria para la pila!\n");
        exit(1); // Sale del programa con un código de error
    }

    stack->top = -1;   // Inicializa la cima de la pila como -1, indicando que está vacía
    stack->max = size; // Define el tamaño máximo de la pila
}

// Inserta un elemento en la pila
void push(Stack *stack, int value)
{
    stack->arr[++stack->top] = value; // Incrementa el índice 'top' y almacena el valor en la nueva posición de 'top'
}

// Elimina y devuelve el elemento en la cima de la pila
int pop(Stack *stack)
{
    return stack->arr[stack->top--]; // Devuelve el valor del 'top' y luego lo decrementa
}

// Verifica si la pila está vacía
int isEmpty(Stack *stack)
{
    // Si 'top' es -1, significa que la pila está vacía
    if (stack->top == -1)
        return 1;
    else
        return 0;
}

// Verifica si la pila está llena
int isFull(Stack *stack)
{
    // Si 'top' es igual a 'max - 1', la pila está llena
    if (stack->top == stack->max - 1)
        return 1;
    else
        return 0;
}

// Definimos una estructura para la Cola (Queue) usando dos pilas
typedef struct Queue
{
    Stack pushStack; // Pila usada para encolar (agregar) elementos
    Stack popStack;  // Pila usada para desencolar (quitar) elementos
    int size;        // Tamaño actual de la cola
    int max;         // Tamaño máximo de la cola
} Queue;

// Inicializa la cola
void initQueue(Queue *queue, int size)
{
    // Inicializamos las dos pilas dentro de la cola
    initStack(&queue->pushStack, size); // Pila para agregar elementos
    initStack(&queue->popStack, size);  // Pila para quitar elementos
    queue->size = 0;                    // Inicializamos el tamaño actual de la cola en 0
    queue->max = size;                  // Definimos el tamaño máximo de la cola
}

// Inserta un elemento en la cola
void enqueue(Queue *queue, int value)
{
    // Si la cola está llena, no se puede agregar más elementos
    if (queue->size == queue->max)
    {
        printf("La cola está llena. No se puede agregar %d\n", value);
        return;
    }
    // Se agrega el valor en la pila 'pushStack'
    push(&queue->pushStack, value);          
    queue->size++;                           // Aumentamos el tamaño de la cola
    printf("%d agregado a la cola!\n", value); // Mostramos el valor agregado
}

// Quita un elemento de la cola
int dequeue(Queue *queue)
{
    // Si la pila 'popStack' está vacía, movemos todos los elementos de 'pushStack' a 'popStack'
    if (isEmpty(&queue->popStack))
    {
        // Pasamos todos los elementos de 'pushStack' a 'popStack' invirtiendo su orden
        while (!isEmpty(&queue->pushStack))
            push(&queue->popStack, pop(&queue->pushStack));
    }

    // Si la pila 'popStack' aún está vacía después de mover los elementos, la cola está vacía
    if (isEmpty(&queue->popStack))
    {
        printf("La cola está vacía! No se puede quitar elementos!\n");
        return -1; // Devuelve -1 si no se puede desencolar
    }

    queue->size--;                // Decrementamos el tamaño de la cola
    return pop(&queue->popStack); // Quitamos el elemento del 'popStack' (el que salió primero)
}

// Imprime los elementos de la cola
void printQueue(Queue *queue)
{
    // Primero imprimimos los elementos de 'popStack' (los más antiguos)
    if (!isEmpty(&queue->popStack))
    {
        printf("Cola: ");
        for (int i = queue->popStack.top; i >= 0; i--) // Recorrimos la pila 'popStack' desde el top
            printf("%d ", queue->popStack.arr[i]);
    }

    // Luego imprimimos los elementos de 'pushStack' (los más recientes)
    if (!isEmpty(&queue->pushStack))
        for (int i = 0; i <= queue->pushStack.top; i++)
            printf("%d ", queue->pushStack.arr[i]);

    // Si ambas pilas están vacías, la cola está vacía
    if (isEmpty(&queue->popStack) && isEmpty(&queue->pushStack))
        printf("La cola está vacía");

    printf("\n");
}

// Función principal para demostrar las operaciones de la cola
int main()
{
    int size;    // Tamaño de la cola
    int option;  // Opción del usuario para elegir la operación
    int value;   // Valor a encolar o desencolar
    Queue queue; // Declaramos una estructura de cola

    // Pedimos al usuario el tamaño de la cola
    printf("Ingresa el tamaño de la cola: ");
    scanf("%d", &size);

    // Inicializamos la cola con el tamaño dado
    initQueue(&queue, size);

    // Bucle infinito para interactuar con el usuario
    while (1)
    {
        printf("\n1) Encolar (enqueue)\n2) Desencolar (dequeue)\n3) Imprimir cola\n0) Salir\nOpción: ");
        scanf("%d", &option);

        switch (option)
        {

        case 1:
            // Encolar un valor
            printf("Ingresa un valor para encolar: ");
            scanf("%d", &value);
            enqueue(&queue, value);
            break;

        case 2:
            // Desencolar un valor
            value = dequeue(&queue);
            if (value != -1)
            {
                printf("Valor desencolado: %d\n", value);
            }
            break;

        case 3:
            // Imprimir la cola
            printQueue(&queue);
            break;

        case 0:
            // Salir del programa
            printf("Saliendo...\n");
            return 0;

        default:
            // Opción inválida
            printf("Opción no válida. Inténtalo de nuevo.\n");
            break;
        }
    }

    // Liberamos la memoria asignada para las pilas
    free(queue.pushStack.arr);
    free(queue.popStack.arr);

    return 0;
}
