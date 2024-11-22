#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Product structure
typedef struct {
    int id;
    char name[50];
    int quantity;
    float cost;
    char entryDate[11]; // Format: YYYY-MM-DD
    int priority;
} Product;

// AVL Tree node
typedef struct AVLNode {
    Product product;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function to get the height of the node
int getHeight(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new AVL node
AVLNode* createNode(Product product) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->product = product;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = 1 + (getHeight(y->left) > getHeight(y->right)? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right)? getHeight(x->left) : getHeight(x->right));
    
    return x;
}

// Left rotate
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = 1 + (getHeight(x->left) > getHeight(x->right)? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right)? getHeight(y->left) : getHeight(y->right));
    
    return y;
}

// Get balance factor
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Insert a product into AVL Tree
AVLNode* insertAVL(AVLNode* node, Product product) {
    if (node == NULL)
        return createNode(product);
    
    if (product.id < node->product.id)
        node->left = insertAVL(node->left, product);
    else if (product.id > node->product.id)
        node->right = insertAVL(node->right, product);
    else
        return node;
    
    node->height = 1 + (getHeight(node->left) > getHeight(node->right)? getHeight(node->left) : getHeight(node->right));
    
    int balance = getBalance(node);
    
    // Left Left
    if (balance > 1 && product.id < node->left->product.id)
        return rightRotate(node);
    
    // Right Right
    if (balance < -1 && product.id > node->right->product.id)
        return leftRotate(node);
    
    // Left Right
    if (balance > 1 && product.id > node->left->product.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left
    if (balance < -1 && product.id < node->right->product.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Hash Table node
typedef struct HashNode {
    Product product;
    struct HashNode* next;
} HashNode;

// Hash Table
typedef struct {
    HashNode* buckets[TABLE_SIZE];
} HashTable;

// Hash function using djb2 algorithm
unsigned int hashFunction(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % TABLE_SIZE;
}

// Initialize Hash Table
HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for(int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    return table;
}

// Insert into Hash Table
int insertHashTable(HashTable* table, Product product) {
    unsigned int index = hashFunction(product.name);
    HashNode* current = table->buckets[index];
    while(current != NULL) {
        if(strcmp(current->product.name, product.name) == 0)
            return 0; // Duplicate name
        current = current->next;
    }
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->product = product;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    return 1;
}

// Search in Hash Table by name
Product* searchHashTable(HashTable* table, const char* name) {
    unsigned int index = hashFunction(name);
    HashNode* current = table->buckets[index];
    while(current != NULL) {
        if(strcmp(current->product.name, name) == 0)
            return &current->product;
        current = current->next;
    }
    return NULL;
}

// Delete from Hash Table by name
int deleteHashTable(HashTable* table, const char* name) {
    unsigned int index = hashFunction(name);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;
    while(current != NULL) {
        if(strcmp(current->product.name, name) == 0) {
            if(prev == NULL)
                table->buckets[index] = current->next;
            else
                prev->next = current->next;
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}