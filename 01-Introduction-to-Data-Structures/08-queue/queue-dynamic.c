#include <stdio.h>
#include <stdlib.h>

// Global variables
int *queue;    // the queue is a dynamically allocated array of integers
int front = 0; // front is the index of the first element in the queue
int rear = 0;  // rear is the index of the next available position in the queue
int num_elements = 0;
int queue_size; // size of the queue

int isFull()
{
    if (num_elements == queue_size)
        return 1;
    else
        return 0;
}

int isEmpty()
{
    if (num_elements == 0)
        return 1;
    else
        return 0;
}

void enqueue(int val)
{
    if (isFull())
    {
        printf("Queue is full. Cannot enqueue %d\n", val);
        return;
    }

    queue[rear] = val;
    num_elements++;
    rear++;

    if (rear == queue_size)
        rear = 0;
}

int dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty. Cannot dequeue!\n");
        return 0; // Return an error value
    }

    int val;
    val = queue[front];
    num_elements--;

    front++;
    if (front == queue_size)
        front = 0;

    return val;
}

void printQueue()
{
    printf("Queue: ");
    if (rear <= front)
    { // print from front to end of array and then from start to rear
        for (int i = front; i < queue_size; i++)
            printf("%d ", queue[i]);

        for (int i = 0; i < rear; i++)
            printf("%d ", queue[i]);
    }
    else
    {
        for (int i = front; i < rear; i++)
            printf("%d ", queue[i]);
    }
    printf("\n");
}

int main()
{
    int choice, value;

    printf("Enter the size of the queue: ");
    scanf("%d", &queue_size);

    // Allocate memory for the queue
    queue = (int *)malloc(queue_size * sizeof(int));
    if (queue == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1)
    {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            value = dequeue();
            if (value != -1)
                printf("Dequeued value: %d\n", value);
            break;
        case 3:
            printQueue();
            break;
        case 4:
            free(queue); // Free the allocated memory
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}