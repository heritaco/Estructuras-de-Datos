#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    int value;
    struct tree_node *left;
    struct tree_node *right;
    int height;
} TreeNode;

TreeNode *newNode(int value);
void insert(TreeNode *parent, TreeNode *new, int type);
int readFromKeyBoard();
void inOrder(TreeNode *root);
void preOrder(TreeNode *root);
int type;

int main()
{
    TreeNode *root = NULL;
    TreeNode *new = NULL;

    int ans;
    do
    { // insert in tree
        new = newNode(readFromKeyBoard());
        if (root == NULL)
        {
            root = new;
            root->height += 1;
        }
        else
            insert(root, new, type);

        // Print the tree in in-order and pre-order
        printf("\nIn-order traversal: ");
        inOrder(root);
        printf("\nPre-order traversal: ");
        preOrder(root);
        printf("\n");

    } while (ans != 0);
    return 0;
}

int readFromKeyBoard()
{
    printf("\n1) Insert to the left \n2) Insert to the right \n0) Exit\nInsert your choice: ");
    scanf("%d", &type);
    if (type == 0)
        exit(0);
    if (type != 1 && type != 2)
    {
        printf("Invalid input. Please try again.\n");
        readFromKeyBoard();
    }

    int value;
    printf("Value: ");
    scanf("%d", &value);
    return value;
}

TreeNode *newNode(int value)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
        return NULL;
    else
    {
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        return new;
    }
}

void insert(TreeNode *parent, TreeNode *new, int type)
{
    if (type == 1)
    {
        if (parent->left == NULL)
        {
            parent->left = new;
            printf("\n%d inserted at left of %d.\n", new->value, parent->value);
        }
        else
        {
            insert(parent->left, new, type);
        }
    }

    else if (type == 2)
    {
        if (parent->right == NULL)
        {
            parent->right = new;
            printf("\n%d inserted at right of %d.\n", new->value, parent->value);
        }

        else
        {
            insert(parent->right, new, type);
        }
    }
}

// Function to perform in-order traversal
void inOrder(TreeNode *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

// Function to perform pre-order traversal
void preOrder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}