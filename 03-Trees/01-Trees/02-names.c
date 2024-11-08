#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    char name[100];
    struct tree_node *left;
    struct tree_node *right;
    int height;
} TreeNode;

TreeNode *newNode(char *name);
void insert(TreeNode *parent, TreeNode *new, int type);
char *readFromKeyBoard();
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

char *readFromKeyBoard()
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

    static char name[100];
    printf("Name: ");
    scanf("%s", name);
    return name;
}

TreeNode *newNode(char *name)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
        return NULL;
    else
    {
        // copy the string
        int i = 0;
        // while each character is not null and i is less than 99
        while (name[i] != '\0' && i < 99)
        { // copy the character to the new node
            new->name[i] = name[i];
            i++;
        }
        // add null character to the end of the string, if not it appears something strange
        new->name[i] = '\0';

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
            printf("\n%s inserted at left of %s.\n", new->name, parent->name);
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
            printf("\n%s inserted at right of %s.\n", new->name, parent->name);
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
        printf("%s ", root->name);
        inOrder(root->right);
    }
}

// Function to perform pre-order traversal
void preOrder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->name);
        preOrder(root->left);
        preOrder(root->right);
    }
}