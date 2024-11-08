#include <stdio.h>  // studio.h is a header file that contains functions for input and output operations.
#include <stdlib.h> // stdlib.h is a header file that contains functions for memory allocation, process control functions, and other functions.

// Define a structure for a node, a structure is a user-defined data type available in C that allows to combine data items of different kinds.
typedef struct node
{ // The structure has two members: data and next.
    // data is an integer that stores the value of the node.
    // next is a pointer to the next node in the list.
    int data;
    struct node *next; // struct node *next is a pointer to a structure of type node.
                       // struct is a keyword used to define a structure.
                       // node is the name of the structure.
                       // *next is a pointer to a structure of type node.
} Node;                // The structure is named Node. The difference between 'node' and 'Node' is that 'Node' is a type, while 'node' is a variable.

// Declare a pointer to the first node in the list
// The pointer is initialized to NULL, which means the list is empty.

// A pointer is a variable that stores the memory address of another variable.
// The pointer is of type Node, which means it can store the memory address of a Node structure.
// The pointer is named head, which is a common name for the first node in a linked list.
Node *head = NULL;

// Function to insert a node at the beginning of the list

// The function takes an integer value as a parameter.
// 'void' is used as the return type because the function does not return any value.
void insert(int value)
{
    // Allocate memory for a new node
    // Structure *pointer = (Structure *)malloc(sizeof(Structure));
    Node *newNode = (Node *)malloc(sizeof(Node));

    // Check if memory allocation was successful
    // It is NULL if the memory allocation fails.
    // This could happen if there is not enough memory available on the system.
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return; // it is only 'return' because the function is of type void.
        // 'return' is used to exit the function and return control to the calling function.
        // there are many returns, such as 'return 0', 'return 1', 'return -1', etc.
        // 'return 0' is used to indicate successful execution of the program.
        // 'return 1' is used to indicate an error condition.
        // 'return -1' is used to indicate an error condition.
        // 'return' without a value is used to exit the function without returning a value.
    }

    // Initialize the new node with the given value and the current head
    newNode->data = value; // The '->' operator is used to access the members of a structure through a pointer.
                           // It is equivalent to (*pointer).member.
                           // In this case, it is used to access the data member of the newNode structure.
    // The data member of the newNode structure is assigned the value passed to the function.
    newNode->next = head;
    // The next member of the newNode structure is assigned the current value of the head pointer.
    head = newNode;
}

// Function to delete a node from the beginning of the list
void delete()
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    // Store the current head in a temporary variable
    // The temporary variable is used to keep a reference to the current head node.
    Node *temp = head;
    head = head->next;
    free(temp);
}

// Function to display the list
void showList()
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *current = head;
    printf("List: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free all nodes in the list
void freeList()
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int ans = 0;

    do
    {
        printf("1) Insert\n2) Delete\n3) Show\n0) Exit\n");
        scanf("%d", &ans);

        if (ans == 1)
        {
            int value;
            printf("Enter the value: ");
            scanf("%d", &value);
            insert(value);
        }
        else if (ans == 2)
        {
            delete ();
        }
        else if (ans == 3)
        {
            showList();
        }
    } while (ans != 0);

    // Free all allocated memory before exiting
    freeList();

    return 0;
}