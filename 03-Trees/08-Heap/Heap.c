/******************************************************************************
Implement an array representation of binary trees.
    A function to obtain the left child of a node.
    A function to obtain the right child of a node.
    A function to obtain the parent of a node.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

void insert(int item);
void reHeapUp(int index);

int removeTop();
void reHeapDown(int i);

void showHeap();

int treeNodes[MAXSIZE];
int last;

int main(){
    
    last = 0;
    
    for (int i = 0; i <  MAXSIZE; i++)
        treeNodes[i] = -1;
        
    FILE *fp = fopen("treeTest.txt","r");
    
    if (fp == NULL) {
        printf("Unable to open test filen");
        exit(-1);
    }

    printf("File successfully open");

    int data;

    while(!feof(fp)){
       
        fscanf(fp,"%d", &data);
         printf("\nReading %d", data);
        insert(data);
        showHeap();
    }
    
    fclose(fp);
    
    int top = removeTop();
    printf("\n\n This is the current top: %d", top);
    showHeap();
    top = removeTop();
    printf("\n\n This is the current top: %d", top);
    showHeap();
    
    return 0;
}

void insert(int item){
   treeNodes[last] = item;
   reHeapUp(last); //put the new element in the correct place
   last ++;
}

void reHeapUp(int index){
   int i = index;
   int iPrnt = (i-1)/2;
   
   if(iPrnt < 0)
     return;

   if(treeNodes[iPrnt] < treeNodes[i]){
        printf("\n\n... reheap UP");
        int aux = treeNodes[iPrnt];
        treeNodes[iPrnt] = treeNodes[i];
        treeNodes[i] = aux;        
        
        reHeapUp(iPrnt);
   }
}

int removeTop(){
    if(last == 0) //heap empty
      return -1;

    int val = treeNodes[0]; //the root
    
    treeNodes[0] = treeNodes[last-1]; //the last is the root
    treeNodes[last-1] = -1;           //mark this node as invalid
    last --;                          
  
    reHeapDown(0);                    //test to put the new root in the correct place
    
    return val;
}

void reHeapDown(int i){
     int index = i;
     
         //exchange parent with the greater of its children
         int ln = 2*index + 1; //the left one
         int rn = 2*index + 2; //the right one
     
         if (treeNodes[ln] == -1) //we reached a leaf
            return;

         //this parent has at least one child. Decide if
         //exchange is required and the child to exchange

         if (treeNodes[ln] > treeNodes[index]){ //left greater than parent
            if (treeNodes[rn] == -1){ //exchange parent with left node is no right child
                printf("\n\n... reheap DOWN left");
                 int temp = treeNodes[index];
                 treeNodes[index] = treeNodes[ln];
                 treeNodes[ln] = temp;
                 reHeapDown(ln);
             }
             else{//exchange with right node only if it is greater than left one
                 if (treeNodes[rn] > treeNodes[ln]){ //exchange parent with right node
                    printf("\n\n... reheap DOWN right");
                    int temp = treeNodes[index];
                    treeNodes[index] = treeNodes[rn];
                    treeNodes[rn] = temp;
                    reHeapDown(rn);
                 }
                 else{
                     printf("\n\n... reheap DOWN left");
                    int temp = treeNodes[index];
                    treeNodes[index] = treeNodes[ln];
                    treeNodes[ln] = temp;
                    reHeapDown(ln);
                 }
            }
         }
         else { //exchange wih right node only if it is greater than parent
               if (treeNodes[rn] > treeNodes[index]){ //exchange parent with right node
                    printf("\n\n... reheap DOWN right");
                    int temp = treeNodes[index];
                    treeNodes[index] = treeNodes[rn];
                    treeNodes[rn] = temp;
                    reHeapDown(rn);
                 }
         }
}


void showHeap(){
    if (last == 0){
       printf("\n  .. heap is empty");
       return;
    }
    
   printf("\n\n  .. ... heap .. ..");
   for(int i = 0; i <= last - 1; i++){
      printf("\nNode %d", treeNodes[i]);
      int li = 2*i + 1;
      int ri = 2*i + 2;
      if(treeNodes[li] != -1)
        printf("\n\t Left Node %d", treeNodes[li]);
        
      if(treeNodes[ri] != -1)
        printf("\n\t Right Node %d", treeNodes[ri]);
   }
   
   printf("\n  .. ... ... .. ..");
}
