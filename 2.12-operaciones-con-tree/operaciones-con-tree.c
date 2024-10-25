#include <stdio.h>
#include <stdlib.h>

// definicion de la estructura del nodo del arbol
typedef struct tree_node
{
    int item;
    struct tree_node *left;
    struct tree_node *right;
    int height;
} TreeNode;

// prototipos de funciones
TreeNode *newNode(int data);
void insert(TreeNode *parent, TreeNode *new);
char *readFromKeyBoard();
void showTree(TreeNode *root, int espacioV);
void preorder(TreeNode *parent);
void inOrder(TreeNode *root);
int getHeight(TreeNode *parent);

int performOperation(int a, int b, int operation);
int getUserOperation();

int main()
{
    TreeNode *root = NULL;
    TreeNode *new = NULL;

    int data;

    // solicitar el primer numero (root)
    printf("Ingrese el valor de la root: ");
    scanf("%d", &data);
    root = newNode(data);

    // solicitar el segundo numero (hijo izquierdo)
    printf("Ingrese el valor del hijo izquierdo: ");
    scanf("%d", &data);
    new = newNode(data);
    insert(root, new);

    // solicitar el tercer numero (hijo derecho)
    printf("Ingrese el valor del hijo derecho: ");
    scanf("%d", &data);
    new = newNode(data);
    insert(root, new);

    // mostrar el arbol en preorder
    printf("\nArbol preorder:\n");
    preorder(root);

    // mostrar el arbol en inOrder
    printf("\n\nArbol inOrder:\n");
    inOrder(root);
    printf("\n");

    // seleccion de operacion
    int operation = getUserOperation();

    // obtener los dos numeros
    if (root && root->left && root->right)
    {
        int result = performOperation(root->left->item, root->right->item, operation);
        printf("\nResultado de la operacion: %d\n", result);
    }
    else
    {
        printf("No se pueden realizar operaciones. Se requieren dos nodos hijos.\n");
    }

    return 0;
}

// funcion para crear un nuevo nodo
TreeNode *newNode(int data)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
        return NULL;
    else
    {
        new->item = data;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        return new;
    }
}

// funcion para insertar un nuevo nodo en el arbol
void insert(TreeNode *parent, TreeNode *new)
{
    int lh = getHeight(parent->left);
    int rh = getHeight(parent->right);

    if (lh == 0)
    {
        parent->left = new;
        printf("%d inserted at left of %d\n", new->item, parent->item);
    }
    else if (rh == 0)
    {
        parent->right = new;
        printf("%d inserted at right of %d\n", new->item, parent->item);
    }
    else if (rh < lh)
        insert(parent->right, new);
    else
        insert(parent->left, new);

    parent->height += 1;
}

// funcion para obtener la altura de un nodo
int getHeight(TreeNode *parent)
{
    if (parent == NULL)
        return 0;

    int lbh = getHeight(parent->left);
    int rbh = getHeight(parent->right);

    if (lbh > rbh)
        return 1 + lbh;
    else
        return 1 + rbh;
}

// funcion para mostrar el arbol en preorder
void preorder(TreeNode *parent)
{
    if (parent == NULL)
        return;
    printf(" %d", parent->item);
    preorder(parent->left);
    preorder(parent->right);
}

// funcion para mostrar el arbol en inOrder
void inOrder(TreeNode *parent)
{
    if (parent != NULL)
    {
        inOrder(parent->left);
        printf("%d ", parent->item);
        inOrder(parent->right);
    }
}

// funcion para obtener la operacion del usuario
int getUserOperation()
{
    int operation;
    printf("\nSeleccione una operacion: \n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicacion\n");
    printf("4. Division\n");
    printf("Ingrese su opcion: ");
    scanf("%d", &operation);
    return operation;
}

// funcion para realizar la operacion seleccionada
int performOperation(int a, int b, int operation)
{
    switch (operation)
    {
    case 1:
        return a + b;
    case 2:
        return a - b;
    case 3:
        return a * b;
    case 4:
        return a / b;
    default:
        printf("Operacion no valida.\n");
        return 0;
    }
}