/******************************************************************************
Implement an array representation of binary trees.
    A function to obtain the left child of a node.
    A function to obtain the right child of a node.
    A function to obtain the parent of a node.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// define the maximum size of the array
#define MAX_SIZE 100

// define the structure of the binary tree
typedef struct BinaryTree
{
    int array[MAX_SIZE];
    int size;
} BinaryTree;

// function to create a new binary tree
BinaryTree *newBinaryTree()
{
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->size = 0;
    return tree;
}

// function to obtain the left child of a node
int leftChild(BinaryTree *tree, int index)
{
    int leftIndex = 2 * index + 1;
    if (leftIndex < tree->size)
        return tree->array[leftIndex];
    return -1;
}

// function to obtain the right child of a node
int rightChild(BinaryTree *tree, int index)
{
    int rightIndex = 2 * index + 2;
    if (rightIndex < tree->size)
        return tree->array[rightIndex];
    return -1;
}

// function to obtain the parent of a node
int parent(BinaryTree *tree, int index)
{
    if (index == 0)
    {
        return -1; // Root node has no parent
    }

    int parentIndex = (index - 1) / 2;
    return tree->array[parentIndex];
}

int main()
{
    // create a new binary tree
    BinaryTree *tree = newBinaryTree();

    // insert elements into the binary tree
    tree->array[tree->size++] = 0;
    tree->array[tree->size++] = 1;
    tree->array[tree->size++] = 2;
    tree->array[tree->size++] = 3;
    tree->array[tree->size++] = 4;
    tree->array[tree->size++] = 5;
    tree->array[tree->size++] = 6;
    tree->array[tree->size++] = 7;
    tree->array[tree->size++] = 8;
    tree->array[tree->size++] = 9;

    // print all left children
    printf("Left children:\n");
    for (int i = 0; i < tree->size; i++)
    {
        int left = leftChild(tree, i);
        if (left != -1)
        {
            printf("Left child of %d: %d\n", tree->array[i], left);
        }
    }

    // print all right children
    printf("Right children:\n");
    for (int i = 0; i < tree->size; i++)
    {
        int right = rightChild(tree, i);
        if (right != -1)
        {
            printf("Right child of %d: %d\n", tree->array[i], right);
        }
    }

    // print all parent nodes
    printf("Parent nodes:\n");
    for (int i = 1; i < tree->size; i++) // start from 1 because root node has no parent
    {
        int parentNode = parent(tree, i);
        if (parentNode != -1)
        {
            printf("Parent of %d: %d\n", tree->array[i], parentNode);
        }
    }

    return 0;
}