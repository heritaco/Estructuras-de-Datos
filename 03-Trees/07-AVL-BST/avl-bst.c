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

TreeNode *newNode(int data);
TreeNode *insertNode(TreeNode *node, int item);
int getHeight(TreeNode *parent);
void preorderTraversal(TreeNode *parent);
void inorderTraversal(TreeNode *parent);
void postorderTraversal(TreeNode *parent);
int getBalanceFactor(TreeNode *parent);
void showTree(TreeNode *parent, int order);
TreeNode *rotateLeft(TreeNode *x);
TreeNode *rotateRight(TreeNode *y);

int main()
{
    TreeNode *root = NULL;

    FILE *fp;
    // abre el archivo treeTest.txt para lectura
    if ((fp = fopen("treeTest.txt", "r")) == NULL)
    {
        printf("Unable to open test file\n");
        exit(-1);
    }

    printf("File successfully opened\n");

    int data;
    // lee los datos del archivo y los inserta en el arbol
    while (!feof(fp))
    {
        fscanf(fp, "%d", &data);
        printf("\nReading: %d", data);
        root = insertNode(root, data);
    }

    // muestra el arbol en diferentes ordenes
    printf("\n\nMostrando el arbol en preorden:");
    showTree(root, 1); // preorden

    printf("\n\nMostrando el arbol en orden:");
    showTree(root, 2); // en orden

    printf("\n\nMostrando el arbol en postorden:");
    showTree(root, 3); // postorden
    fclose(fp);
}

// crea un nuevo nodo con el dato proporcionado
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

// inserta un nodo en el arbol
TreeNode *insertNode(TreeNode *parent, int item)
{
    // si el nodo padre es nulo, crea un nuevo nodo con el item y lo retorna
    if (parent == NULL)
    {
        printf("\ninserting %d", item);
        return newNode(item);
    }
    // si el item es mayor que el item del nodo padre, inserta en el subarbol derecho
    else if (item > parent->item)
    {
        printf("\ninserting %d to the right of %d", item, parent->item);
        parent->right = insertNode(parent->right, item);
    }
    // si el item es menor que el item del nodo padre, inserta en el subarbol izquierdo
    else if (item < parent->item)
    {
        printf("\ninserting %d to the left of %d", item, parent->item);
        parent->left = insertNode(parent->left, item);
    }
    // si el item es igual al item del nodo padre, retorna el nodo padre
    else
        return parent;

    // actualiza la altura del nodo padre
    parent->height = getHeight(parent);

    // obtiene el factor de balance del nodo padre
    int balance = getBalanceFactor(parent);

    // si el nodo esta desbalanceado hacia la derecha
    if (balance < -1)
    {
        // si el item es mayor que el item del hijo derecho, realiza una rotacion a la izquierda
        if (item > parent->right->item)
            return rotateLeft(parent);
        // si el item es menor que el item del hijo derecho, realiza una rotacion derecha-izquierda
        if (item < parent->right->item)
        {
            parent->right = rotateRight(parent->right);
            return rotateLeft(parent);
        }
    }
    // si el nodo esta desbalanceado hacia la izquierda
    else if (balance > 1)
    {
        // si el item es menor que el item del hijo izquierdo, realiza una rotacion a la derecha
        if (item < parent->left->item)
            return rotateRight(parent);
        // si el item es mayor que el item del hijo izquierdo, realiza una rotacion izquierda-derecha
        if (item > parent->left->item)
        {
            parent->left = rotateLeft(parent->left);
            return rotateRight(parent);
        }
    }

    // imprime el fin de la insercion y retorna el nodo padre
    printf("\nend of insertion: %d", item);
    return parent;
}

// obtiene la altura del nodo
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

// obtiene el balance del nodo
int getBalanceFactor(TreeNode *parent)
{
    int lh = 0; // inicializa la altura del subarbol izquierdo en 0
    int rh = 0; // inicializa la altura del subarbol derecho en 0

    // si el hijo izquierdo no es nulo, obtiene su altura
    if (parent->left != NULL)
        lh = parent->left->height;
    // si el hijo derecho no es nulo, obtiene su altura
    if (parent->right != NULL)
        rh = parent->right->height;

    // retorna la diferencia entre la altura del subarbol izquierdo y derecho
    return (lh - rh);
}

// realiza una rotacion a la izquierda
TreeNode *rotateLeft(TreeNode *x)
{
    TreeNode *y = x->right; // guarda el hijo derecho de x en y
    TreeNode *B = y->left;  // guarda el hijo izquierdo de y en B

    y->left = x;  // convierte a x en el hijo izquierdo de y
    x->right = B; // asigna B como el hijo derecho de x

    // actualiza las alturas de x e y
    x->height = getHeight(x);
    y->height = getHeight(y);

    return y; // retorna y como la nueva raiz del subarbol
}

// realiza una rotacion a la derecha
TreeNode *rotateRight(TreeNode *y)
{
    TreeNode *x = y->left;  // guarda el hijo izquierdo de y en x
    TreeNode *B = x->right; // guarda el hijo derecho de x en B

    x->right = y; // convierte a y en el hijo derecho de x
    y->left = B;  // asigna B como el hijo izquierdo de y

    // actualiza las alturas de y y x
    y->height = getHeight(y);
    x->height = getHeight(x);

    return x; // retorna x como la nueva raiz del subarbol
}

// recorrido en preorden
void preorderTraversal(TreeNode *parent)
{
    if (parent == NULL)
        return;

    printf(" %d,", parent->item);
    preorderTraversal(parent->left);
    preorderTraversal(parent->right);
}

// recorrido en orden
void inorderTraversal(TreeNode *parent)
{
    if (parent == NULL)
        return;

    inorderTraversal(parent->left);
    printf(" %d,", parent->item);
    inorderTraversal(parent->right);
}

// recorrido en postorden
void postorderTraversal(TreeNode *parent)
{
    if (parent == NULL)
        return;

    postorderTraversal(parent->left);
    postorderTraversal(parent->right);
    printf(" %d,", parent->item);
}

// muestra el arbol en el orden especificado
void showTree(TreeNode *parent, int order)
{
    if (parent == NULL)
    {
        printf("\nThe TREE is empty!!");
        return;
    }

    printf("\nTREE:");

    switch (order)
    {
    case 1:
        preorderTraversal(parent);
        break;
    case 2:
        inorderTraversal(parent);
        break;
    case 3:
        postorderTraversal(parent);
        break;
    }
}