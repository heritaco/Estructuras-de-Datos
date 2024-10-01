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
void showTree(TreeNode *root, int space);
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

        showTree(root, 0);

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

        // return the new node
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

void showTree(TreeNode *root, int space)
{
    // if the root is NULL, return
    if (root == NULL)
        return;

    // space is the distance between the nodes
    space += 10;

    // process right child first
    showTree(root->right, space);

    // print current node after space count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");            // print space
    printf("%s\n", root->name); // print node

    // process left child
    showTree(root->left, space);
}