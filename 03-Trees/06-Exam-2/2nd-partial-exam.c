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

// definicion del nodo del arbol binario
typedef struct TreeNode
{
    int item;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
} TreeNode;

TreeNode *newNode(int item);
void swapTree(TreeNode *root);
int countNodes(TreeNode *root);
int sumItems(TreeNode *root);
void findMinMax(TreeNode *root, int *min, int *max);
void getMinMax(TreeNode *root, int *min, int *max);
void inOrder(TreeNode *root);
void preorder(TreeNode *parent);

int main()
{
    // crear el arbol
    TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(3);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->right = newNode(4);
    root->right->right->left = newNode(8);

    // imprimir el arbol original
    printf("In order original tree: ");
    inOrder(root);

    printf("\nPreorder original tree: ");
    preorder(root);

    // intercambiar el arbol para obtener el arbol B
    swapTree(root);

    // imprimir el arbol intercambiado
    printf("\nIn order swapped tree: ");
    inOrder(root);

    printf("\nPreorder swapped tree: ");
    preorder(root);

    // contar el numero de nodos
    int count = countNodes(root);
    printf("\nNumber of nodes: %d\n", count);

    // suma de todos los elementos
    int sum = sumItems(root);
    printf("Sum of all items: %d\n", sum);

    // encontrar los valores minimo y maximo
    int min, max;
    getMinMax(root, &min, &max);
    printf("Minimum item: %d\n", min);
    printf("Maximum item: %d\n", max);

    return 0;
}

// funcion para crear un nuevo nodo
TreeNode *newNode(int item)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
        return NULL;
    else
    {
        new->item = item;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        return new;
    }
}

// funcion para intercambiar los hijos izquierdo y derecho de un arbol binario
void swapTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    // intercambiar los hijos izquierdo y derecho
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    // intercambiar recursivamente los subarboles izquierdo y derecho
    swapTree(root->left);
    swapTree(root->right);
}

// funcion para contar el numero de elementos en un arbol binario
int countNodes(TreeNode *root)
{
    // si el nodo actual es NULL, retornar 0
    if (root == NULL)
    {
        return 0;
    }

    // contar el nodo actual (1) mas el numero de nodos en el subarbol izquierdo
    // y el numero de nodos en el subarbol derecho
    int leftCount = countNodes(root->left);   // contar nodos en el subarbol izquierdo
    int rightCount = countNodes(root->right); // contar nodos en el subarbol derecho

    // retornar el conteo total: 1 (nodo actual) + conteo del subarbol izquierdo + conteo del subarbol derecho
    return 1 + leftCount + rightCount;
}

// funcion para retornar la suma de todos los elementos en un arbol binario
int sumItems(TreeNode *root)
{
    // caso base: si el nodo actual es NULL, retornar 0
    if (root == NULL)
    {
        return 0;
    }

    // sumar el elemento del nodo actual con la suma de elementos en el subarbol izquierdo
    // y la suma de elementos en el subarbol derecho
    int leftSum = sumItems(root->left);   // suma de elementos en el subarbol izquierdo
    int rightSum = sumItems(root->right); // suma de elementos en el subarbol derecho

    // retornar la suma total: elemento del nodo actual + suma del subarbol izquierdo + suma del subarbol derecho
    return root->item + leftSum + rightSum;
}

// funcion para encontrar los valores minimo y maximo en un arbol binario
void findMinMax(TreeNode *root, int *min, int *max)
{
    if (root == NULL)
        return;

    if (root->item < *min)
        *min = root->item;

    if (root->item > *max)
        *max = root->item;

    findMinMax(root->left, min, max);
    findMinMax(root->right, min, max);
}

// funcion auxiliar para inicializar los valores minimo y maximo y llamar a findMinMax
void getMinMax(TreeNode *root, int *min, int *max)
{
    if (root == NULL)
        return;

    *min = root->item;
    *max = root->item;

    findMinMax(root, min, max);
}

// funcion para realizar el recorrido in-order
void inOrder(TreeNode *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->item);
        inOrder(root->right);
    }
}

// funcion para mostrar el arbol en preorder
void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->item);
    preorder(root->left);
    preorder(root->right);
}