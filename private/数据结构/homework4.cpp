/*
    04-树6 Complete Binary Search Tree (30 分)
    A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
    Both the left and right subtrees must also be binary search trees.
    A Complete Binary Tree (CBT) is a tree that is completely filled, 
    with the possible exception of the bottom level, which is filled from left to right.

    Now given a sequence of distinct non-negative integer keys, 
    a unique BST can be constructed if it is required that the tree must also be a CBT.
     You are supposed to output the level order traversal sequence of this BST.

    Input Specification:
    Each input file contains one test case. For each case, the first line contains a positive integer N (≤1000). 
    Then N distinct non-negative integer keys are given in the next line. 
    All the numbers in a line are separated by a space and are no greater than 2000.

    Output Specification:
    For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

    Sample Input:
    10
    1 2 3 4 5 6 7 8 9 0
    Sample Output:
    6 3 8 1 5 7 9 0 2 4

    题意理解：完全二叉搜索树
            将给定的序列通过某种组织方式使其既是一棵完全二叉树又是一棵二叉搜索树
    
    树的表示法：链表vs数组
        *需要的操作
            *填写数字(某种遍历) —— 完全二叉树，不浪费空间
            *层序遍历 —— 直接顺序输出
        *数组完胜

    核心算法：
    void solve(int Aleft,int Aright,TRoot)     
    {//排序后的输入序列A，从A中选出正确的根结点填入T[TRoot]中
     //初始调用为solve(0,n-1,0);
        n=Aright-Aleft+1;       //计算出输入序列的结点数
        if(!n)return;           //n为0时结束递归调用
        L=GetLeftLength(n);     //计算出n个结点的树其左子树有多少个结点
        T[TRoot]=A[Aleft+L];    //ALeft+左子树结点个数就是序列中根结点的下标
        LeftTRoot=TRoot*2+1;    //左子树的根结点下标为TRoot*2+1(整个树的根结点下标为0)
        RightTRoot=LeftTRoot+1; //右子树根结点下标为TRoot*2+1
        solve[Aleft,Aleft+L-1,LeftTRoot];    //在左右子树递归调用此过程
        solve[Aleft+L+1,Aright,RightTRoot];
    }
    计算左子树的规模GetLeftLength()：
    完全二叉树前h-1层的总结点个数：(2^h-1)-1 (h从1开始)
    因此左子树的结点数 n=2^(h-2)-1+x，x为最下面一层的结点个数(0<=x<=2^(h-2))，此时h=⌊lg(n+1)⌋
    不过到这里x的值不一定等于x(最下一层结点数)，此时有两种情况：x超过左子树的叶子结点数，x不超过左子树的叶子结点数
    x=min(x,2^(h-2))

答案：
#include<iostream>
#include<queue>
#include<cmath>
#define MAXLINE 1000
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
typedef struct TreeNode *BinTree;
typedef int ElementType;
struct TreeNode {
    ElementType val;
    BinTree left,right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
int pre[MAXLINE],in[MAXLINE],lev[MAXLINE];
void CBST(int*,int,int,int);
int partiation(int*,int,int);
void qksort(int*,int,int);
BinTree create(int*,int*,int,int,int,int);
void levelorder(BinTree);
int main() {
    int i,n,v[MAXLINE];
    cin>>n;
    for(i=0;i<n;i++)cin>>v[i];
    qksort(v,0,n-1);
    CBST(v,n,0,n-1);
    BinTree BT= create(pre,in,0,n-1,0,n-1);
    levelorder(BT);
    for(i=0;i<n-1;i++)cout<<lev[i]<<' ';
    cout<<lev[n-1];
}
int partiation(int* v,int start,int end){
    if(v==NULL||start<0||start>end)return -1;
    int pivot=v[start];
    while(start<end){
        for(;v[end]>=pivot&&start<end;end--);
        v[start]=v[end];
        for(;v[start]<pivot&&start<end;start++);
        v[end]=v[start];
    }
    v[start]=pivot;
    return start;
}
void qksort(int*v,int start,int end){
    if(end-start<1)return;
    int pivot= partiation(v,start,end);
    if(pivot>start+1)qksort(v,start,pivot-1);
    if(pivot<end-1)qksort(v,pivot+1,end);
}
void CBST(int*v,int n,int start,int end){
    int h,pivot;
    static int i=0,j=0;
    if(end-start<1){
        pre[i++]=in[j++]=v[start];
        return;
    }
    for(h=0;(int)pow(2,h)<n+1;h++);
    pivot=start+(min(pow(2,h-2),(int)pow(2,h-1)-(int)pow(2,h)+1+n))+(int)pow(2,h-2)-1;
    pre[i++]=v[pivot];
    if(pivot-start>0)CBST(v,pivot-start,start,pivot-1);
    in[j++]=v[pivot];
    if(end-pivot>0)CBST(v,end-pivot,pivot+1,end);
}
BinTree create(int*pre,int*in,int ps,int pe,int is,int ie){
    if(ps>pe)return nullptr;
    TreeNode* node = new TreeNode(pre[ps]);
    int pos;
    for(int i=is;i<=ie;i++)
        if(in[i]==node->val){
            pos=i;
            break;
    }
    node->left=create(pre,in,ps+1,ps+pos-is,is,pos-1);
    node->right=create(pre,in,pe-ie+pos+1,pe,pos+1,ie);
    return node;
}
void levelorder(BinTree BT){
    queue<BinTree> q;
    int i=0;
    BinTree T=BT;
    q.push(T);
    while(!q.empty()){
        T=q.front();
        q.pop();
        lev[i++]=T->val;
        if(T->left)q.push(T->left);
        if(T->right)q.push(T->right);
    }
}
*/