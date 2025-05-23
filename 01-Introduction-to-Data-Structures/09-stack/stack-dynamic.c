#include <stdio.h>
#include <stdlib.h>

int *stack; // the stack is a dynamically allocated array of integers
int top;
int stack_size; // size of the stack

int isEmpty()
{
    if (top == 0)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (top == stack_size)
        return 1;
    else
        return 0;
}

void push(int value)
{
    stack[top] = value;
    top++;
}

int pop()
{
    int val;
    top--;
    val = stack[top];

    return val;
}

void printStack()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }
    // print from top to the beginning of the array
    printf("Stack:\n");

    int last = top - 1; // top - 1 because top is the next available position

    for (int i = last; i >= 0; i--)
        printf("%d\n", stack[i]);
}

int main()
{
    top = 0;

    printf("Enter the size of the stack: ");
    scanf("%d", &stack_size);

    // Allocate memory for the stack
    stack = (int *)malloc(stack_size * sizeof(int));
    if (stack == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int option;
    int value;

    do
    {
        printf("1) Push\n2) Pop\n3) Print the stack\n0) to exit\n");
        printf("\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            if (isFull())
                printf("Stack is full. Cannot push\n");
            else
            {
                printf("Value to push: ");
                scanf("%d", &value);
                push(value);
            }
            break;
        case 2:
            if (isEmpty())
                printf("Stack is empty. Cannot pop\n");
            else
                printf("Popped value: %d\n", pop());
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

    free(stack); // Free the allocated memory
    return 0;
}