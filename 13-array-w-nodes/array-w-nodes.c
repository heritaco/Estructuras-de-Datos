#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *front;
Node *rear;

void enqueue(int d);
int dequeue();
int isEmpty();

void showQueueList();

int main()
{
    front = NULL;
    rear = NULL;

    int ans = 0;
    int value;

    do
    {
        printf("1) Enqueue\n2) Dequeue\n3) Show\n0) Exit\n");
        scanf("%d", &ans);

        switch (ans)
        {
        case 1:
            printf("Enter the value to enqueue: ");
            scanf("%d", &value);
            enqueue(value);
            break;
        case 2:
            if (!isEmpty())
            {
                printf("Dequeued value: %d\n", dequeue());
            }
            else
            {
                printf("Queue is empty\n");
            }
            break;
        case 3:
            showQueueList();
            break;
        }
    } while (ans != 0);

    return 0;
}

void enqueue(int d)
{
    // Create a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // Check if memory is available
    if (newNode == NULL)
    {
        printf("Error: No memory available\n");
        return;
    }
    // Assign the value to the new node
    newNode->data = d;
    newNode->next = NULL;
    // Check if the queue is empty, if so, assign the new node to the front and rear
    if (front == NULL)
    {
        front = newNode;
        rear = newNode;
    }
    // If the queue is not empty, assign the new node to the rear and update the rear
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue()
{
    // Check if the queue is empty
    if (isEmpty())
    {
        return -1;
    }
    // Get the value from the front node
    int value = front->data;
    // Move the front to the next node
    Node *temp = front;
    front = front->next;
    // Free the memory of the node
    free(temp);
    // Return the value
    return value;
}

int isEmpty()
{
    return front == NULL;
}

void showQueueList()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }

    Node *current = front;
    printf("Queue: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}