#include <stdio.h>

#define QUEUE_SIZE 5 // we use define to create a constant

// Global variables
int queue[QUEUE_SIZE]; // the queue is an array of integers
int front = 0;         // front is the index of the first element in the queue
int rear = 0;          // rear is the index of the next available position in the queue
int num_elements = 0;

int isFull()
{
    if (num_elements == QUEUE_SIZE)
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

    if (rear == QUEUE_SIZE)
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
    if (front == QUEUE_SIZE)
        front = 0;

    return val;
}

void printQueue()
{
    printf("Queue: ");
    if (rear <= front)
    { // print from front to end of array and then from start to rear
        for (int i = front; i < QUEUE_SIZE; i++)
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
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}