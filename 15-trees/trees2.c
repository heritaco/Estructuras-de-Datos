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
void insert(TreeNode *parent, TreeNode *new, int type, int currentHeight, int targetHeight);
char *readFromKeyBoard();
void showTree(TreeNode *root, int space);
int type, targetHeight;

int main()
{
    TreeNode *root = NULL;
    TreeNode *new = NULL;
    int ans;

    do
    {
        new = newNode(readFromKeyBoard());
        if (root == NULL)
        {
            root = new;
            root->height = 1; // Set the height of the root node to 1
        }
        else
        {
            printf("Enter the height at which you want to insert the node: ");
            scanf("%d", &targetHeight);
            insert(root, new, type, 1, targetHeight);
        }

        showTree(root, 0);

    } while (1); // Keep looping until user exits

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
        return readFromKeyBoard();
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
        int i = 0;
        while (name[i] != '\0' && i < 99)
        {
            new->name[i] = name[i];
            i++;
        }

        new->name[i] = '\0';
        new->left = NULL;
        new->right = NULL;
        new->height = 0;

        return new;
    }
}

void insert(TreeNode *parent, TreeNode *new, int type, int currentHeight, int targetHeight)
{
    if (currentHeight + 1 == targetHeight)
    {
        if (type == 1) // Insert to the left
        {
            if (parent->left == NULL)
            {
                parent->left = new;
                new->height = targetHeight;
                printf("\n%s inserted at left of %s at height %d.\n", new->name, parent->name, targetHeight);
            }
            else
            {
                printf("Left position at height %d is already occupied.\n", targetHeight);
            }
        }
        else if (type == 2) // Insert to the right
        {
            if (parent->right == NULL)
            {
                parent->right = new;
                new->height = targetHeight;
                printf("\n%s inserted at right of %s at height %d.\n", new->name, parent->name, targetHeight);
            }
            else
            {
                printf("Right position at height %d is already occupied.\n", targetHeight);
            }
        }
    }
    else
    {
        if (type == 1)
        {
            if (parent->left != NULL)
                insert(parent->left, new, type, currentHeight + 1, targetHeight);
            else
                printf("Cannot insert at height %d. No node at left at height %d.\n", targetHeight, currentHeight + 1);
        }
        else if (type == 2)
        {
            if (parent->right != NULL)
                insert(parent->right, new, type, currentHeight + 1, targetHeight);
            else
                printf("Cannot insert at height %d. No node at right at height %d.\n", targetHeight, currentHeight + 1);
        }
    }
}

void showTree(TreeNode *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    showTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->name);

    showTree(root->left, space);
}
