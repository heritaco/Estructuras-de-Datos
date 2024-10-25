/******************************************************************************

Develop a C program that demonstrates the application or use of a dynamic ADT
(queue, stack or linkedlist) with the assumption of being taken to a real scenario.

The basic operations to be considered by the programme are:
    Insert elements into the ADT.
    Delete element from the end or start of the ADT.
    Inserting elements to the ADT at a certain position.
    Delete element from the ADT at a given position.
    Update an element in a given position.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// node structure
struct Node
{
    int ticket;
    struct Node *next;
};

// function to create a new node
struct Node *createNode(int ticket)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->ticket = ticket;
    newNode->next = NULL;
    return newNode;
}

// function to insert a node at the end of the circular linked list
void insertEnd(struct Node **head, int ticket)
{
    struct Node *newNode = createNode(ticket);
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

// function to insert a node at a specific position
void insertAtPosition(struct Node **head, int ticket, int position)
{
    struct Node *newNode = createNode(ticket);
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

// function to delete a node at the beginning
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

// function to delete a node at the end
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

// function to delete a node at a specific position
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

// function to display the circular linked list
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
        printf("%d ", temp->ticket);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// function to update a node at a specific position
void updateAtPosition(struct Node **head, int position, int newTicket)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = *head;
    for (int i = 1; i < position && temp->next != *head; i++)
    {
        temp = temp->next;
    }
    if (temp->next == *head && position != 1)
    {
        printf("Position out of range.\n");
        return;
    }
    temp->ticket = newTicket;
}

int main()
{

    printf("Welcome to the Bank Queue Management System!\n");
    printf("Clients are waiting in a queue, each holding a ticket with their turn number.\n");
    printf("You can manage the queue using the following operations:\n");

    struct Node *head = NULL;
    int choice, ticket, position, newTicket;

    while (1)
    {
        printf("\n1) Insert a client at the end of the queue\n");
        printf("2) Insert a client at a specific position\n");
        printf("3) Remove the first client\n");
        printf("4) Remove the last client\n");
        printf("5) Remove a client from a specific position\n");
        printf("6) Update a client's ticket number at a specific position\n");
        printf("7) Display the queue\n");
        printf("0) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter ticket number: ");
            scanf("%d", &ticket);
            insertEnd(&head, ticket);
            displayList(head);
            break;
        case 2:
            printf("Enter ticket number: ");
            scanf("%d", &ticket);
            printf("Enter position: ");
            scanf("%d", &position);
            insertAtPosition(&head, ticket, position);
            displayList(head);
            break;
        case 3:
            deleteAtBeginning(&head);
            displayList(head);
            break;
        case 4:
            deleteAtEnd(&head);
            displayList(head);
            break;
        case 5:
            printf("Enter position: ");
            scanf("%d", &position);
            deleteAtPosition(&head, position);
            displayList(head);
            break;
        case 7:
            displayList(head);
            break;
        case 6:
            printf("Enter position: ");
            scanf("%d", &position);
            printf("Enter new ticket number: ");
            scanf("%d", &newTicket);
            updateAtPosition(&head, position, newTicket);
            displayList(head);
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
