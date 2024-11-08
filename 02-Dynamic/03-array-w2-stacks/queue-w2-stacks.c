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
    // allocate memory for the stack array
    stack->arr = (int *)malloc(size * sizeof(int));

    // if memory cannot be allocated, print an error and exit the program
    if (stack->arr == NULL)
    {
        printf("\nFailed to allocate memory for the stack!\n");
        exit(1);
    }

    stack->top = -1;   // initialize the top as -1, indicating an empty stack
    stack->max = size; // set the maximum size of the stack.
}

// push an element onto the stack
void push(Stack *stack, int value)
{
    // increment the top index of the stack
    stack->top++;

    // store the value at the new top index
    stack->arr[stack->top] = value;
}

int pop(Stack *stack)
{
    // get the value at the top of the stack
    int value = stack->arr[stack->top];
    // decrease the top index
    stack->top--;
    // return the value
    return value;
}

int isEmpty(Stack *stack)
{
    // if top is -1, the stack is empty
    if (stack->top == -1)
        return 1;
    else
        return 0;
}

int isFull(Stack *stack)
{
    // if top is equal to max - 1, the stack is full
    if (stack->top == stack->max - 1)
        return 1;
    else
        return 0;
}

// structure for queue using two stacks
typedef struct Queue
{
    Stack pushStack; // stack used for enqueue
    Stack popStack;  // stack used for dequeue
    int size;        // current size of the queue
    int max;         // maximum size of the queue
} Queue;

// initialize the queue
void initQueue(Queue *queue, int size)
{
    initStack(&queue->pushStack, size); // initialize the stack for enqueuing
    initStack(&queue->popStack, size);  // initialize the stack for dequeuing
    queue->size = 0;                    // initialize the current size
    queue->max = size;                  // set the maximum size of the queue
}

// function to enqueue an element
void enqueue(Queue *queue, int value)
{
    // if the queue is full, we cannot enqueue more elements
    if (queue->size == queue->max)
    {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }

    // push the value onto the pushStack
    push(&queue->pushStack, value);          // push the value onto the pushStack
    queue->size++;                           // increment the current size of the queue
    printf("%d enqueued! hooray!\n", value); // print the value
}

// dequeue an element
int dequeue(Queue *queue)
{
    // if popStack is empty, move all elements from pushStack to popStack
    if (isEmpty(&queue->popStack))
        while (!isEmpty(&queue->pushStack))
            push(&queue->popStack, pop(&queue->pushStack));

    // if popStack is empty, the queue is empty
    if (isEmpty(&queue->popStack))
    {
        printf("Queue is empty! Cannot dequeue!\n");
        return -1;
    }

    queue->size--;                // decrement the size of the queue
    return pop(&queue->popStack); // pop the top from popStack
}
// print the queue
void printQueue(Queue *queue)
{
    // if popStack is not empty, print the elements in it
    if (!isEmpty(&queue->popStack))
    {
        printf("Queue: ");
        for (int i = queue->popStack.top; i >= 0; i--)
            printf("%d ", queue->popStack.arr[i]);
    }

    // if pushStack is not empty, print the elements in it
    if (!isEmpty(&queue->pushStack))
        for (int i = 0; i <= queue->pushStack.top; i++)
            printf("%d ", queue->pushStack.arr[i]);

    // if both stacks are empty, the queue is empty
    if (isEmpty(&queue->popStack) && isEmpty(&queue->pushStack))
        printf("Queue is empty");

    printf("\n");
}

// display the menu for the user
void displayMenu(Queue *queue)
{
    int option; // user's choice
    int value;  // value to enqueue

    while (1)
    {
        printf("\n1) Enqueue\n2) Dequeue\n3) Print Queue\n0) Exit\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(queue, value);
            break;

        case 2:
            value = dequeue(queue);
            if (value != -1)
            {
                printf("Dequeued value: %d\n", value);
            }
            break;

        case 3:
            printQueue(queue);
            break;

        case 0:
            printf("Exiting...\n");
            return;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}

int main()
{
    int size;    // size of the queue
    Queue queue; // queue structure

    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    initQueue(&queue, size);

    displayMenu(&queue);

    // free the allocated memory
    free(queue.pushStack.arr);
    free(queue.popStack.arr);

    return 0;
}