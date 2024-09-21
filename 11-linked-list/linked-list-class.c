#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *head;
void ShowList();
void FreeList();

int main()
{
    head = NULL;
    int ans = 0;

    while (1)
    {
        printf("\n\033[0;33mPress 0 to add a new int to the list, any other key to quit: \033[0m");
        scanf("%d", &ans);

        if (ans == 0)
        {
            Node *newNode = (Node *)malloc(sizeof(Node));
            if (newNode != NULL)
            {
                int val;
                printf("\n\033[0;35mEnter the value: \033[0m");
                scanf("%d", &(newNode->data));
                newNode->next = NULL;
                if (head == NULL)
                {
                    head = newNode;
                }
                else
                {
                    Node *aux = head;
                    while (aux->next != NULL)
                        aux = aux->next;
                    aux->next = newNode;
                }
                ShowList();
            }
        }
        else
        {
            printf("\n\033[0;31mGoodbye!\033[0m\n");
            FreeList();
            return 0;
        }
    }
}

void ShowList()
{
    if (head == NULL)
    {
        printf("\nThe list is EMPTY");
    }
    else
    {
        printf("\nList:");
        Node *aux = head;
        while (aux != NULL)
        {
            printf("%d ", aux->data);
            aux = aux->next;
        }
        printf("\n");
    }
}   

void FreeList()
{
    Node *aux = head;
    while (aux != NULL)
    {
        Node *temp = aux;
        aux = aux->next;
        free(temp);
    }
    head = NULL;
}