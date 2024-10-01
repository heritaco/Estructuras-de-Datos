#include <stdio.h>
#include <stdlib.h>

typedef struct node
{ // Define struct type
    int data;
    struct node *next;
} Node;

Node *last; // Head is not used anymore in a circular linked list

void showList(); // Funcion para imprimir lista

int main()
{

    last = NULL;
    int ans = 0;

    do
    {
        printf("\nPress '0' to add a new int to the list, any other key to quit: ");
        scanf("%d", &ans);

        if (ans == 0)
        { // Create the new Node
            Node *newNode = (Node *)malloc(sizeof(Node));

            if (newNode != NULL)
            { // Valid memory to allocate the in and the next pointer

                int val;
                printf("Enter the value: ");
                scanf("%d", &(newNode->data)); // Agregando el valor leido al primer nodo, a su atributo
                newNode->next = NULL;

                // 2.1 if the list is empty, this is the first
                if (last == NULL)
                { // Si last es igual a nulo, entonces no hay ningun nodo
                    newNode->next = newNode;
                    last = newNode;
                }
                else
                { // 2.2 Locate the last node in the list
                    newNode->next = last->next;
                    last->next = newNode;
                    last = newNode;
                }
                showList();
            }
        }
    } while (ans == 0);

    return 0;
} // main

void showList()
{
    if (last == NULL)
    {
        printf("\nThe list is EMPTY!!\n");
    }
    else
    {
        printf("\nList: ");
        Node *aux = last->next;

        do
        {
            printf("%d ", aux->data);
            aux = aux->next;
        } while (aux != last->next);

        printf("\n");
    }
}