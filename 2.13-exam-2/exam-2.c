/******************************************************************************

Develop a function to obtain the swapped version of a binary tree. The following figure
shows an example of the swapped version (B tree) of an A tree (show the resulting
tree)

Original tree (A tree)
          1
        /   \
       2     5
      /     / \
     3     6   7
      \       /
       4     8

Swapped tree (B tree)
           1
         /   \
        5     2
       / \      \
      7   6      3
       \        /
        8      4

a) Write a function that counts the number of items in a binary tree.
b) Write a function that returns the sum of all the keys in a binary tree.
c) Write a function that returns the minimum and maximum values of all the keys
in a binary.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Definition of the binary tree node
typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node *newNode(int key);
void swapTree(Node *root);
int countNodes(Node *root);
int sumKeys(Node *root);
void findMinMax(Node *root, int *min, int *max);
void getMinMax(Node *root, int *min, int *max);
void inOrder(Node *root);
void preorder(Node *parent);

int main()
{
    // Create the original tree (A tree)
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(3);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->right = newNode(4);
    root->right->right->left = newNode(8);

    // Print the original tree
    printf("In order original tree: ");
    inOrder(root);

    printf("\nPreorder original tree: ");
    preorder(root);

    // Swap the tree to get the B tree
    swapTree(root);

    // Print the swapped tree
    printf("\nIn order swapped tree: ");
    inOrder(root);

    printf("\nPreorder swapped tree: ");
    preorder(root);

    // Count the number of nodes
    int count = countNodes(root);
    printf("\nNumber of nodes: %d\n", count);

    // Sum of all keys
    int sum = sumKeys(root);
    printf("Sum of all keys: %d\n", sum);

    // Find the minimum and maximum values
    int min, max;
    getMinMax(root, &min, &max);
    printf("Minimum key: %d\n", min);
    printf("Maximum key: %d\n", max);

    return 0;
}

Node *newNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Function to swap the left and right children of a binary tree
void swapTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Swap the left and right children
    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively swap the left and right subtrees
    swapTree(root->left);
    swapTree(root->right);
}

// Function to count the number of items in a binary tree
int countNodes(Node *root)
{
    // Base case: if the current node is NULL, return 0
    if (root == NULL)
    {
        return 0;
    }

    // Recursive case: count the current node (1) plus the number of nodes in the left subtree
    // and the number of nodes in the right subtree
    int leftCount = countNodes(root->left);   // Count nodes in the left subtree
    int rightCount = countNodes(root->right); // Count nodes in the right subtree

    // Return the total count: 1 (current node) + left subtree count + right subtree count
    return 1 + leftCount + rightCount;
}

// Function to return the sum of all the keys in a binary tree
int sumKeys(Node *root)
{
    // Base case: if the current node is NULL, return 0
    if (root == NULL)
    {
        return 0;
    }

    // Recursive case: sum the key of the current node with the sum of keys in the left subtree
    // and the sum of keys in the right subtree
    int leftSum = sumKeys(root->left);   // Sum of keys in the left subtree
    int rightSum = sumKeys(root->right); // Sum of keys in the right subtree

    // Return the total sum: key of the current node + left subtree sum + right subtree sum
    return root->key + leftSum + rightSum;
}

// Function to find the minimum and maximum values in a binary tree
void findMinMax(Node *root, int *min, int *max)
{
    if (root == NULL)
        return;

    if (root->key < *min)
        *min = root->key;

    if (root->key > *max)
        *max = root->key;

    findMinMax(root->left, min, max);
    findMinMax(root->right, min, max);
}

// Helper function to initialize min and max values and call findMinMax
void getMinMax(Node *root, int *min, int *max)
{
    if (root == NULL)
        return;

    *min = root->key;
    *max = root->key;

    findMinMax(root, min, max);
}

// Function to perform in-order traversal
void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// funcion para mostrar el arbol en preorder
void preorder(Node *parent)
{
    if (parent == NULL)
        return;
    printf("%d ", parent->key);
    preorder(parent->left);
    preorder(parent->right);
}