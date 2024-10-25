#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
    int data;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the circular linked list
void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        newNode->next = *head;
    }
    else
    {
        struct Node *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Function to insert a node at a specific position
void insertAtPosition(struct Node **head, int data, int position)
{
    struct Node *newNode = createNode(data);
    if (position == 1)
    {
        if (*head == NULL)
        {
            *head = newNode;
            newNode->next = *head;
        }
        else
        {
            struct Node *temp = *head;
            while (temp->next != *head)
            {
                temp = temp->next;
            }
            newNode->next = *head;
            temp->next = newNode;
            *head = newNode;
        }
    }
    else
    {
        struct Node *temp = *head;
        for (int i = 1; i < position - 1 && temp->next != *head; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to delete a node at the beginning
void deleteAtBeginning(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = *head;
    if (temp->next == *head)
    {
        free(temp);
        *head = NULL;
    }
    else
    {
        struct Node *last = *head;
        while (last->next != *head)
        {
            last = last->next;
        }
        *head = (*head)->next;
        last->next = *head;
        free(temp);
    }
}

// Function to delete a node at the end
void deleteAtEnd(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = *head;
    if (temp->next == *head)
    {
        free(temp);
        *head = NULL;
    }
    else
    {
        struct Node *prev = NULL;
        while (temp->next != *head)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = *head;
        free(temp);
    }
}

// Function to delete a node at a specific position
void deleteAtPosition(struct Node **head, int position)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = *head;
    if (position == 1)
    {
        deleteAtBeginning(head);
    }
    else
    {
        struct Node *prev = NULL;
        for (int i = 1; i < position && temp->next != *head; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp->next == *head && position != 1)
        {
            printf("Position out of range.\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
    }
}

// Function to display the circular linked list
void displayList(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = head;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main()
{
    struct Node *head = NULL;
    int choice, data, position;

    while (1)
    {
        printf("\n1) Insert at end\n2) Insert at position\n3) Delete at beginning\n4) Delete at end\n5) Delete at position\n6) Display\n7) Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insertEnd(&head, data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &position);
            insertAtPosition(&head, data, position);
            break;
        case 3:
            deleteAtBeginning(&head);
            break;
        case 4:
            deleteAtEnd(&head);
            break;
        case 5:
            printf("Enter position: ");
            scanf("%d", &position);
            deleteAtPosition(&head, position);
            break;
        case 6:
            displayList(head);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}