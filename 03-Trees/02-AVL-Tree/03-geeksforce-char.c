#include <stdio.h>
#include <stdlib.h>

// Definir la estructura del nodo del árbol AVL
typedef struct TreeNode
{
    char *key;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
} TreeNode;

// Declaración de funciones
TreeNode *newNode(char *key);
TreeNode *preOrderInsert(TreeNode *root, FILE *fp);
void preOrder(TreeNode *root);
void inOrder(TreeNode *root);

// Función para crear un nuevo nodo
TreeNode *newNode(char *key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->key = (char *)malloc(50 * sizeof(char));

    // Copiar el contenido de key a node->key manualmente
    int i = 0;
    while (key[i] != '\0' && i < 49)
    {
        node->key[i] = key[i];
        i++;
    }
    node->key[i] = '\0'; // Asegurarse de que la cadena esté terminada en nulo

    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Función para insertar nodos en preorden
TreeNode *preOrderInsert(TreeNode *root, FILE *fp)
{
    char data[50];
    if (fscanf(fp, "%s", data) != EOF)
    {
        root = newNode(data);
        root->left = preOrderInsert(root->left, fp);
        root->right = preOrderInsert(root->right, fp);
    }
    return root;
}

// Función para realizar el recorrido preorden
void preOrder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Función para realizar el recorrido inorden
void inOrder(TreeNode *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%s ", root->key);
        inOrder(root->right);
    }
}

// Función principal
int main()
{
    TreeNode *root = NULL;
    FILE *fp = fopen("names.txt", "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    root = preOrderInsert(root, fp);
    fclose(fp);

    printf("Recorrido Preorden: ");
    preOrder(root);
    printf("\n");

    printf("Recorrido Inorden: ");
    inOrder(root);
    printf("\n");

    return 0;
}