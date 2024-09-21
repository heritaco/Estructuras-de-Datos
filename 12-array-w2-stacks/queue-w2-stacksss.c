#include <stdio.h>
#include <stdlib.h>

// define a structure for Stack
typedef struct Stack
{
    int *arr; // pointer to an integer array of the elements of the stack
    int top;  // top element
    int max;  // maximum size the stack
} Stack;

// initialize the stack
void initStack(Stack *stack, int size)
{
    stack->arr = (int *)malloc(size * sizeof(int));

    if (stack->arr == NULL)
    {
        printf("\nFailed to allocate memory for the stack!\n");
        exit(1);
    }

    stack->top = -1;   // initialize the top as -1 (indicating the stack is empty)
    stack->max = size; // set the maximum size of the stack.
}

// push an element onto the stack
void push(Stack *stack, int value)
{
    stack->arr[++stack->top] = value; // increment the top and store the value at the new top.
}

int pop(Stack *stack)
{
    return stack->arr[stack->top--]; // Return the topmost element and then decrease the top index.
}

int isEmpty(Stack *stack)
{
    // If top is -1, the stack is empty
    if (stack->top == -1)
        return 1;
    else
        return 0;
}

int isFull(Stack *stack)
{
    // If top is equal to max - 1, the stack is full
    if (stack->top == stack->max - 1)
        return 1;
    else
        return 0;
}

// Define a structure for Queue using two stacks
typedef struct Queue
{
    Stack pushStack; // Stack used for enqueue
    Stack popStack;  // Stack used for dequeue
    int size;        // Current size of the queue
    int max;         // Maximum size of the queue
} Queue;

// Function to initialize the queue
void initQueue(Queue *queue, int size)
{
    initStack(&queue->pushStack, size); // Initialize the stack for enqueuing elements
    initStack(&queue->popStack, size);  // Initialize the stack for dequeuing elements
    queue->size = 0;                    // Initialize the current size of the queue
    queue->max = size;                  // Set the maximum size of the queue
}

// Function to enqueue an element into the queue
void enqueue(Queue *queue, int value)
{
    if (queue->size == queue->max)
    {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }
    push(&queue->pushStack, value);          // Push the value onto the pushStack
    queue->size++;                           // Increment the current size of the queue
    printf("%d enqueued! hooray!\n", value); // Print the value
}

// Function to dequeue an element from the queue
int dequeue(Queue *queue)
{
    if (isEmpty(&queue->popStack))
    {
        while (!isEmpty(&queue->pushStack))
            push(&queue->popStack, pop(&queue->pushStack));
    }

    if (isEmpty(&queue->popStack))
    {
        printf("Queue is empty! Cannot dequeue!\n");
        return -1;
    }
    queue->size--;                // Decrement the current size of the queue
    return pop(&queue->popStack); // Pop the top element from popStack
}

// Function to print the queue
void printQueue(Queue *queue)
{
    if (!isEmpty(&queue->popStack))
    {
        printf("Queue: ");
        for (int i = queue->popStack.top; i >= 0; i--)
            printf("%d ", queue->popStack.arr[i]);
    }

    if (!isEmpty(&queue->pushStack))
        for (int i = 0; i <= queue->pushStack.top; i++)
            printf("%d ", queue->pushStack.arr[i]);

    if (isEmpty(&queue->popStack) && isEmpty(&queue->pushStack))
        printf("Queue is empty");

    printf("\n");
}

// Main function to demonstrate queue operations
int main()
{
    int size;    // Size of the queue
    int option;  // User's choice for the operation
    int value;   // Value to enqueue or dequeue
    Queue queue; // Declare a Queue structure

    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    // Initialize the queue
    initQueue(&queue, size);

    while (1)
    {
        printf("\n1) Enqueue\n2) Dequeue\n3) Print Queue\n0) Exit\nOption: ");
        scanf("%d", &option);

        switch (option)
        {

        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(&queue, value);
            break;

        case 2:
            value = dequeue(&queue);
            if (value != -1)
            {
                printf("Dequeued value: %d\n", value);
            }
            break;

        case 3:
            printQueue(&queue);
            break;

        case 0:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    // Free the allocated memory
    free(queue.pushStack.arr);
    free(queue.popStack.arr);

    return 0;
}