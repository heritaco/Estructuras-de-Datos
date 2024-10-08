#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    int item;
    struct tree_node *left;
    struct tree_node *right;
    int height;
} TreeNode;

TreeNode *newNode(int data);
void insert(TreeNode *node, TreeNode *new);
int readFromKeyBoard();
int getHight(TreeNode *parent); // new
// void showTree(TreeNode *parent); // new

int main()
{
    TreeNode *root = NULL;
    TreeNode *new = NULL;

    // FILE means a file pointer
    FILE *fp;

    // if file does not exist
    if ((fp = fopen("tree.txt", "r")) == NULL)
    {
        printf("Unable to open test file\n");
        exit(-1);
    }

    printf("File successfully open\n");

    int data;

    // while not end of file
    while (!feof(fp))
    { // read from file as int
        fscanf(fp, "%d", &data);
        // create a new node
        new = newNode(data);
        // if root is null
        if (root == NULL)
        {
            root = new;        // root is new
            root->height += 1; // increment height
        }
        else
            insert(root, new); // insert new node
    }
    // showTree(root); // show the tree
    fclose(fp); // close the file
}

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

void insert(TreeNode *parent, TreeNode *new)
{
    int lh = getHight(parent->left);  // get height of left child
    int rh = getHight(parent->right); // get height of right child

    // if left child is null
    if (lh == 0)
    {
        parent->left = new; // insert left child
        printf("\n ...%d inserted at left of %d.\n", new->item, parent->item);
    }
    // if right child is null
    else if (rh == 0)
    {
        parent->right = new; // insert right child
        printf("\n ...%d inserted at right of %d.\n", new->item, parent->item);
    }
    // else if left child is less than right child
    else if (rh < lh)
        insert(parent->right, new); // insert right child
    // else if right child is less than left child
    else
        insert(parent->left, new); // insert left child

    parent->height += 1;
}

int getHight(TreeNode *parent)
{
    // if parent is null return 0
    if (parent == NULL)
        return 0;

    int lbh = getHight(parent->left);  // get height of left child
    int rbh = getHight(parent->right); // get height of right child

    // if left child is greater than right child
    if (lbh > rbh)
        return lbh + 1; // return left child height + 1
    // if the right child is greater than left child
    else
        return rbh + 1; // return right child height + 1
}