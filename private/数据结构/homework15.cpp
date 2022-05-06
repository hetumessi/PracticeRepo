/*    7-3 Self-printable B+ Tree (35 分)
    In this project, you are supposed to implement a B+ tree of order 3, with the following operations: 
    initialize, insert (with splitting) and search. The B+ tree should be able to print out itself.
    Input Specification:
    Each input file contains one test case. For each case, the first line contains a positive number N 
    (≤10^4), the number of integer keys to be inserted. Then a line of the N positive integer keys follows. All the numbers in a line are separated by spaces.
    Output Specification:
    For each test case, insert the keys into an initially empty B+ tree of order 3 according to the given order. 
    Print in a line Key X is duplicated where X already exists when being inserted. 
    After all the insertions, print out the B+ tree in a top-down lever-order format as shown by the samples.
    Sample Input 1:
    6
    7 8 9 10 7 4
    Sample Output 1:
    Key 7 is duplicated
    [9]
    [4,7,8][9,10]
    Sample Input 2:
    10
    3 1 4 5 9 2 6 8 7 0
    Sample Output 2:
    [6]
    [2,4][8]
    [0,1][2,3][4,5][6,7][8,9]
    Sample Input 3:
    3
    1 2 3
    Sample Output 3:
    [1,2,3]    
我的答案：
#include<cstdio>
#include<cstdlib>
#include<queue>
#define MAXINPUT 10050
#define INIFINITY 65535
using namespace std;
typedef struct Bplusnode*Bplusptr;
struct Bplusnode{
    int keys[4];
    bool flag;
    Bplusptr parent,sibling,childs[4];
};
enum flag{leaf,nonleaf};
int inputvalue[MAXINPUT];
queue<Bplusptr>printerqueque;
Bplusptr initializeBplustree(int),searchBplustree(Bplusptr,int),insertBplustree(Bplusptr,int);
void printBplustree(Bplusptr);
int main(){
    int inputnodes;
    scanf("%d",&inputnodes);
    for(int i=0;i<inputnodes;i++)scanf("%d",&inputvalue[i]);
    Bplusptr tree=nullptr;
    for(int i=0;i<inputnodes;i++)
        tree=insertBplustree(searchBplustree(tree,inputvalue[i]),inputvalue[i]);
    printBplustree(tree);
    return 0;
}
Bplusptr initializeBplustree(int flag){
    auto root=(Bplusptr)malloc(sizeof(struct Bplusnode));
    root->parent=root->sibling=nullptr;
    root->flag=flag;
    for(int i=0;i<4;i++)root->keys[i]=INIFINITY,root->childs[i]=nullptr;
    return root;
}
Bplusptr searchBplustree(Bplusptr root,int searchvalue){
    if(!root)return nullptr;
    if(root->flag){
        if(root->keys[0]>searchvalue)root=searchBplustree(root->childs[0],searchvalue);
        else if(root->keys[1]>searchvalue)root=searchBplustree(root->childs[1],searchvalue);
        else root=searchBplustree(root->childs[2],searchvalue);
    }
    return root;
}
Bplusptr insertBplustree(Bplusptr root,int insertvalue){
    if(!root)root=initializeBplustree(leaf);
    int insertpos=0;
    if(!root->flag){
        for(;insertvalue>=root->keys[insertpos];insertpos++)if(root->keys[insertpos]==insertvalue){
                printf("Key %d is duplicated\n",insertvalue);
                insertpos=-1;break;
            }
        if(insertpos>=0){
            for(int i=2;i>=insertpos;i--)root->keys[i+1]=root->keys[i];
            root->keys[insertpos]=insertvalue;
        }
        if(root->keys[3]<INIFINITY){
            Bplusptr nextleaf=initializeBplustree(leaf),parent=root->parent;
            nextleaf->sibling=root->sibling;
            root->sibling=nextleaf;
            for(int i=0;i<2;i++)nextleaf->keys[i]=root->keys[i+2],root->keys[i+2]=INIFINITY;
            if(parent){
                nextleaf->parent=parent;
                for(insertpos=0;root->keys[0]>=parent->keys[insertpos];insertpos++);
                for(int i=3;i>insertpos;i--)parent->childs[i]=parent->childs[i-1];
                parent->childs[insertpos+1]=nextleaf;
                for(int i=0;i<3;i++)if(parent->childs[i+1])parent->keys[i]=parent->childs[i+1]->keys[0];
            }else{
                root->parent=nextleaf->parent=initializeBplustree(nonleaf);
                root->parent->childs[0]=root,root->parent->childs[1]=root->sibling;
                root->parent->keys[0]=nextleaf->keys[0];
            }
        }
        if(root->parent)root=insertBplustree(root->parent,insertvalue);
    }else{
        if(root->keys[2]<INIFINITY){
            Bplusptr nextnonleaf=initializeBplustree(nonleaf),parent=root->parent;
            nextnonleaf->sibling=root->sibling;
            root->sibling=nextnonleaf;
            nextnonleaf->keys[0]=root->keys[2],root->keys[2]=INIFINITY;
            for(int i=0;i<2;i++){
                nextnonleaf->childs[i]=root->childs[i+2],root->childs[i+2]->parent=nextnonleaf;
                root->childs[i+2]=nullptr;
            }
            if(parent){
                nextnonleaf->parent=parent;
                for(;root->keys[1]>parent->keys[insertpos];insertpos++);
                for(int i=2;i>=insertpos;i--)parent->keys[i]=parent->keys[i-1];
                parent->keys[insertpos]=root->keys[1],root->keys[1]=INIFINITY;
                for(int i=3;i>insertpos;i--)parent->childs[i]=parent->childs[i-1];
                parent->childs[insertpos+1]=nextnonleaf;
            }else{
                root->parent=nextnonleaf->parent=initializeBplustree(nonleaf);
                root->parent->childs[0]=root,root->parent->childs[1]=nextnonleaf;
                root->parent->keys[0]=root->keys[1],root->keys[1]=INIFINITY;
            }
        }
        if(root->parent)root=insertBplustree(root->parent,insertvalue);
    }
    return root;
}
void printBplustree(Bplusptr root){
    printerqueque.push(root);
    while(!printerqueque.empty()){
        int flag=0;
        printf("[");
        for(int i=0;i<3;i++){
            int printnum=printerqueque.front()->keys[i];
            if(printnum<INIFINITY){
                if(!flag){
                    printf("%d",printnum);
                    flag=1;
                }else printf(",%d",printnum);
            }
        }
        printf("]");
        if(!printerqueque.front()->sibling)printf("\n");
        for(int i=0;i<3;i++){
            if(printerqueque.front()->childs[i])printerqueque.push(printerqueque.front()->childs[i]);
            else break;
        }
        printerqueque.pop();
    }
}  */