#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 101

typedef struct Product
{
    int id;
    char name[50];
    int stock;
    float cost;
    char entry_date[11]; // Format: YYYY-MM-DD
    int priority;        // Lower value = higher priority
} Product;

typedef struct AVLNode
{
    Product product;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef struct HashNode
{
    Product product;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_TABLE_SIZE];

// Hash Function
int hashFunction(char *name)
{
    int hash = 0;
    while (*name)
        hash = (hash + *name++) % HASH_TABLE_SIZE;
    return hash;
}

// Hash Table Functions
void insertHash(Product product)
{
    int index = hashFunction(product.name);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    newNode->product = product;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void deleteHash(char *name)
{
    int index = hashFunction(name);
    HashNode *current = hashTable[index];
    HashNode *prev = NULL;

    while (current != NULL && strcmp(current->product.name, name) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return; // Not found
    if (prev == NULL)
        hashTable[index] = current->next;
    else
        prev->next = current->next;

    free(current);
}

Product *searchHash(char *name)
{
    int index = hashFunction(name);
    HashNode *current = hashTable[index];
    while (current)
    {
        if (strcmp(current->product.name, name) == 0)
            return &current->product;
        current = current->next;
    }
    return NULL;
}

// AVL Tree Functions
int max(int a, int b) { return (a > b) ? a : b; }
int height(AVLNode *node) { return node ? node->height : 0; }
int getBalance(AVLNode *node) { return node ? height(node->left) - height(node->right) : 0; }

AVLNode *createNode(Product product)
{
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->product = product;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *insertAVL(AVLNode *node, Product product)
{
    if (!node)
    {
        insertHash(product);
        return createNode(product);
    }

    if (product.priority < node->product.priority)
        node->left = insertAVL(node->left, product);
    else if (product.priority > node->product.priority)
        node->right = insertAVL(node->right, product);
    else
    {
        printf("Duplicate priority detected. Product '%s' not added.\n", product.name);
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && product.priority < node->left->product.priority)
        return rightRotate(node);

    if (balance < -1 && product.priority > node->right->product.priority)
        return leftRotate(node);

    if (balance > 1 && product.priority > node->left->product.priority)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && product.priority < node->right->product.priority)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrderTraversal(AVLNode *root)
{
    if (root)
    {
        inOrderTraversal(root->left);
        printf("ID: %d, Name: %s, Stock: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               root->product.id, root->product.name, root->product.stock,
               root->product.cost, root->product.entry_date, root->product.priority);
        inOrderTraversal(root->right);
    }
}

// Update Product
void updateProduct(AVLNode *root, char *name, int newStock, float newCost, char *newDate, int newPriority)
{
    Product *product = searchHash(name);
    if (product)
    {
        product->stock = newStock;
        product->cost = newCost;
        strcpy(product->entry_date, newDate);
        if (product->priority != newPriority)
        {
            root = insertAVL(root, *product); // Reinsert if priority changes
        }
    }
    else
    {
        printf("Product '%s' not found.\n", name);
    }
}

int main()
{
    AVLNode *root = NULL;

    // Menu
    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Add Product\n");
        printf("2. Delete Product by Name\n");
        printf("3. Display All Products (By Priority)\n");
        printf("4. Update Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            Product product;
            printf("Enter ID, Name, Stock, Cost, Entry Date (YYYY-MM-DD), Priority: ");
            scanf("%d %s %d %f %s %d", &product.id, product.name, &product.stock,
                  &product.cost, product.entry_date, &product.priority);
            root = insertAVL(root, product);
        }
        else if (choice == 2)
        {
            char name[50];
            printf("Enter product name to delete: ");
            scanf("%s", name);
            root = deleteAVL(root, name);
        }
        else if (choice == 3)
        {
            printf("\nAll Products (By Priority):\n");
            inOrderTraversal(root);
        }
        else if (choice == 4)
        {
            char name[50];
            int newStock, newPriority;
            float newCost;
            char newDate[11];
            printf("Enter product name to update: ");
            scanf("%s", name);
            printf("Enter new Stock, Cost, Entry Date (YYYY-MM-DD), Priority: ");
            scanf("%d %f %s %d", &newStock, &newCost, newDate, &newPriority);
            updateProduct(root, name, newStock, newCost, newDate, newPriority);
        }
    } while (choice != 5);

    return 0;
}
