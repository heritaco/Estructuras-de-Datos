#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
   int item;
   struct tree_node* left;
   struct tree_node* right;
 }TreeNode;

TreeNode *newNode(int data);
void insert(TreeNode *node, TreeNode *new, int type);
int readFromKeyBoard();
int type;


int main()
{
    TreeNode *root = NULL;
    TreeNode *new = NULL;
    int ans;
  
    
    do{
        
        printf("\nPress '1' to add a new int to the TREE, any other key to quit: ");
        scanf("%d", &ans);
        
        if (ans == 1){ //insert in tree
                new = newNode(readFromKeyBoard());
                if (root == NULL){
                    root = new;
                    root->height += 1;
                }
                else{
                    
                    insert(root,new,type);
                  
                    
                }
                //showTree();              
         }
            
    }while(ans == 1);
}

int readFromKeyBoard(){
    printf("\n Insert to Left (0) and right (1) ");
  
    scanf("%d", &type);
    
    printf("\n Enter int: ");
    int data;
    scanf("%d", &data);
    return data;
}

TreeNode *newNode(int data){

    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    
    if (new == NULL)
       return NULL;
    else{
        new -> item = data;
        new -> left = NULL;
        new -> right = NULL;
        new -> height = 0;
        return new;
    }
    
}

void insert(TreeNode *parent, TreeNode *new,int type){
   
    
    if(type == 0){
        parent->left = new;
        printf("\n ...%d inserted at left of %d.\n",new->item,parent->item);
    }
    else if(type == 1){
        parent->right = new;
         printf("\n ...%d inserted at right of %d.\n",new->item,parent->item);
    }
      
    
}

