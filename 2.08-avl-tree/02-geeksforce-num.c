#include <stdio.h>  // incluir la biblioteca estandar de entrada y salida
#include <stdlib.h> // incluir la biblioteca estandar de funciones de utilidad

// definir la estructura para el nodo del arbol AVL
typedef struct TreeNode
{
    int item;               // valor del nodo
    struct TreeNode *left;  // puntero al hijo izquierdo
    struct TreeNode *right; // puntero al hijo derecho
    int height;             // altura del nodo
} TreeNode;

TreeNode *newNode(int data);                // declaracion de la funcion para crear un nuevo nodo
TreeNode *insert(TreeNode *node, int item); // declaracion de la funcion para insertar un nodo
int getHeight(TreeNode *n);                 // declaracion de la funcion para obtener la altura de un nodo

int max(int a, int b);              // declaracion de la funcion para obtener el maximo de dos enteros
TreeNode *rightRotate(TreeNode *y); // declaracion de la funcion para rotar a la derecha
TreeNode *leftRotate(TreeNode *x);  // declaracion de la funcion para rotar a la izquierda
int getBalance(TreeNode *n);        // declaracion de la funcion para obtener el factor de balance

void inOrder(TreeNode *root);             // declaracion de la funcion para el recorrido en orden
void preOrder(TreeNode *root);            // declaracion de la funcion para el recorrido en preorden
void showTree(TreeNode *root, int space); // declaracion de la funcion para mostrar el arbol

int main()
{
    TreeNode *root = NULL; // inicializar el arbol como vacio
    TreeNode *new = NULL;  // inicializar el nuevo nodo como vacio

    FILE *fp; // declarar un puntero a archivo

    if ((fp = fopen("test-num.txt", "r")) == NULL) // intentar abrir el archivo en modo lectura
    {
        printf("Unable to open test file\n"); // imprimir mensaje de error si no se puede abrir el archivo
        exit(-1);                             // salir del programa con codigo de error
    }
    printf("File successfully opened\n"); // imprimir mensaje de exito si se abre el archivo

    int data; // declarar una variable para almacenar los datos leidos

    while (fscanf(fp, "%d", &data) != EOF) // leer datos del archivo hasta el final del archivo
        root = insert(root, data);         // insertar los datos en el arbol

    fclose(fp); // cerrar el archivo

    // imprimir el recorrido en preorden del arbol AVL
    printf("Preorder traversal of AVL tree: ");
    preOrder(root);
    printf("\n");

    // imprimir el recorrido en orden del arbol AVL
    printf("Inorder traversal of AVL tree: ");
    inOrder(root);
    printf("\n");

    return 0; // terminar el programa
}

// funcion para crear un nuevo nodo
TreeNode *newNode(int item)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode)); // asignar memoria para el nuevo nodo

    if (new == NULL) // verificar si la asignacion de memoria fallo
        return NULL; // retornar NULL si fallo
    else
    {
        new->item = item;  // asignar el valor al nodo
        new->left = NULL;  // inicializar el hijo izquierdo como NULL
        new->right = NULL; // inicializar el hijo derecho como NULL
        new->height = 0;   // inicializar la altura como 0
        return new;        // retornar el nuevo nodo
    }
}

// funcion para obtener la altura del nodo
int getHeight(TreeNode *n)
{
    if (n == NULL)    // verificar si el nodo es NULL
        return 0;     // retornar 0 si el nodo es NULL
    return n->height; // retornar la altura del nodo
}

// funcion utilitaria para obtener el maximo de dos enteros
int max(int a, int b)
{
    return (a > b) ? a : b; // retornar el mayor de los dos enteros
}

// funcion para rotar a la derecha el subarbol enraizado con y
TreeNode *rightRotate(TreeNode *y)
{
    TreeNode *x = y->left;   // asignar el hijo izquierdo de y a x
    TreeNode *T2 = x->right; // asignar el hijo derecho de x a T2

    // realizar la rotacion
    x->right = y;
    y->left = T2;

    // actualizar las alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // retornar el nuevo nodo raiz
}

// funcion para rotar a la izquierda el subarbol enraizado con x
TreeNode *leftRotate(TreeNode *x)
{
    TreeNode *y = x->right; // asignar el hijo derecho de x a y
    TreeNode *T2 = y->left; // asignar el hijo izquierdo de y a T2

    // realizar la rotacion
    y->left = x;
    x->right = T2;

    // actualizar las alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // retornar el nuevo nodo raiz
}

// obtener el factor de balance del nodo n
int getBalance(TreeNode *n)
{
    if (n == NULL)                                   // verificar si el nodo es NULL
        return 0;                                    // retornar 0 si el nodo es NULL
    return getHeight(n->left) - getHeight(n->right); // retornar el factor de balance
}

// funcion recursiva para insertar un item en el subarbol enraizado con node y retorna la nueva raiz del subarbol
TreeNode *insert(TreeNode *node, int item)
{
    // 1. realizar la insercion normal en el arbol binario de busqueda
    if (node == NULL)         // verificar si el nodo es NULL
        return newNode(item); // crear un nuevo nodo si es NULL

    if (item < node->item)                       // si el item es menor que el valor del nodo
        node->left = insert(node->left, item);   // insertar en el subarbol izquierdo
    else if (item > node->item)                  // si el item es mayor que el valor del nodo
        node->right = insert(node->right, item); // insertar en el subarbol derecho
    else                                         // los items iguales no estan permitidos en el arbol binario de busqueda
        return node;                             // retornar el nodo sin cambios

    // 2. actualizar la altura de este nodo ancestro
    node->height = 1 + max(getHeight(node->left), getHeight(node->right)); // actualizar la altura

    // 3. obtener el factor de balance de este nodo ancestro para verificar si este nodo se volvio desequilibrado
    int balance = getBalance(node); // obtener el factor de balance

    // si este nodo se vuelve desequilibrado, entonces hay 4 casos

    // caso izquierda izquierda
    if (balance > 1 && item < node->left->item)
        return rightRotate(node); // realizar rotacion a la derecha

    // caso derecha derecha
    if (balance < -1 && item > node->right->item)
        return leftRotate(node); // realizar rotacion a la izquierda

    // caso izquierda derecha
    if (balance > 1 && item > node->left->item)
    {
        node->left = leftRotate(node->left); // realizar rotacion a la izquierda en el hijo izquierdo
        return rightRotate(node);            // realizar rotacion a la derecha
    }

    // caso derecha izquierda
    if (balance < -1 && item < node->right->item)
    {
        node->right = rightRotate(node->right); // realizar rotacion a la derecha en el hijo derecho
        return leftRotate(node);                // realizar rotacion a la izquierda
    }

    // retornar el puntero del nodo (sin cambios)
    return node;
}

// funcion para realizar el recorrido en preorden del arbol AVL
void preOrder(TreeNode *root)
{
    if (root != NULL) // verificar si el nodo raiz no es NULL
    {
        printf("%d ", root->item); // imprimir el valor del nodo
        preOrder(root->left);      // recorrer el subarbol izquierdo
        preOrder(root->right);     // recorrer el subarbol derecho
    }
}

// funcion para realizar el recorrido en orden del arbol
void inOrder(TreeNode *root)
{
    if (root != NULL) // verificar si el nodo raiz no es NULL
    {
        inOrder(root->left);       // recorrer el subarbol izquierdo
        printf("%d ", root->item); // imprimir el valor del nodo
        inOrder(root->right);      // recorrer el subarbol derecho
    }
}