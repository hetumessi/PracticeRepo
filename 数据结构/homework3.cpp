/*
    03-树2 List Leaves (25 分)
    Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

    Input Specification:
    Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) 
    which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. 
    Then N lines follow, each corresponds to a node, 
    and gives the indices of the left and right children of the node. 
    If the child does not exist, a "-" will be put at the position. 
    Any pair of children are separated by a space.

    Output Specification:
    For each test case, print in one line all the leaves' indices in the order of top down, 
    and left to right. There must be exactly one space between any adjacent numbers,
    and no extra space at the end of the line.

    Sample Input:
    8
    1 -
    - -
    0 -
    2 7
    - -
    - -
    5 -
    4 6
    Sample Output:
    4 1 5
答案：
#include<iostream>
#include<queue>
#define MaxTree 10
#define Tree int
#define Null -1
using namespace std;
struct TreeNode
{
    Tree Left;
    Tree Right;
}T[MaxTree];
Tree BuildTree(struct TreeNode[]);
void leaves(Tree);
int main()
{
    Tree R;
    R=BuildTree(T);
    leaves(R);
}
Tree BuildTree(struct TreeNode T[])
{
    int i,N,check[MaxTree];
    char cl,cr;
    Tree Root;
    cin>>N;
    if(!N)return Null;
    for(i=0;i<N;i++)check[i]=0;
    for(i=0;i<N;i++) {
        cin>>cl>>cr;
        if (cl != '-') {
            T[i].Left = cl - '0';
            check[T[i].Left] = 1;
        } else T[i].Left = Null;
        if (cr != '-') {
            T[i].Right = cr - '0';
            check[T[i].Right] = 1;
        } else T[i].Right = Null;
    }
    for(i=0;i<N;i++)if(!check[i])break;
    Root=i;
    return Root;
}
void leaves(Tree R){
    queue<int> q;
    int flag=0;
    q.push(R);
    while(!q.empty()){
        if(T[q.front()].Left!=Null)q.push(T[q.front()].Left);
        if(T[q.front()].Right!=Null)q.push(T[q.front()].Right);
        if(T[q.front()].Left==Null&&T[q.front()].Right==Null){
            if(!flag){
                cout<<q.front();
                flag=1;
            }
            else cout<<' '<<q.front();
        }
        q.pop();
    }
}
*/
/*
    03-树3 Tree Traversals Again (25 分)
    An inorder binary tree traversal can be implemented in a non-recursive way with a stack. 
    For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed,
    the stack operations are: 
    push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). 
    Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. 
    Your task is to give the postorder traversal sequence of this tree.


    Figure 1
    Input Specification:
    Each input file contains one test case.
     For each case, the first line contains a positive integer N (≤30) 
     which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N).
      Then 2N lines follow, each describes a stack operation in the format: 
      "Push X" where X is the index of the node being pushed onto the stack; 
      or "Pop" meaning to pop one node from the stack.

    Output Specification:
    For each test case, print the postorder traversal sequence of the corresponding tree in one line. 
    A solution is guaranteed to exist. All the numbers must be separated by exactly one space, 
    and there must be no extra space at the end of the line.

    Sample Input:
    6
    Push 1
    Push 2
    Push 3
    Pop
    Pop
    Push 4
    Pop
    Pop
    Push 5
    Push 6
    Pop
    Pop
    Sample Output:
    3 4 2 6 5 1
    分析：
        实际上在输入格式中Push的过程是二叉树前序遍历的结果，Pop的过程是二叉树的中序遍历的结果
        如因此题目的意思变成已知二叉树的前序遍历和中序遍历求二叉树的后序遍历
    void solve(int prel,int postl,int inl,int n)
    { //只需要获得前序的第一个结点下标以及子树的结点数，然后在中序序列中操作即可
        if(!n)return;
        if(n==1)
        {
            post[postl]=pre[prel];
            return;
        }
        int root=pre[prel];
        post[postl+n-1]=root;
        for(int i=0;i<n;i++)if(in[inl+i]==root)break;
        int l=i,r=n-l-1;
        solve(prel+1,inl,postl,l);
        solve(prel+l+1,inl+l+1,postl+l,r);
    }
    
答案：
#include<iostream>
#include<stack>
#include<string>
#define MaxTree 30
using namespace std;
int inorder[MaxTree],preorder[MaxTree],postorder[MaxTree];
void getseries(int);
void post(int, int, int);
int main()
{
    int n;
    cin>>n;
    getseries(n);
    post(0,0,n-1);
}
void getseries(int n){
    stack<int> s;
    int i=0,j=0,nu;string str;
    while(i<n||j<n){
        cin>>str;
        if(str=="Push"){
            cin>>nu;
            s.push(nu);
            preorder[i++]=nu;
        }
        if(str=="Pop"){
            inorder[j++]=s.top();
            s.pop();
        }
    }
}
void post(int root, int start, int end) {  //root为根结点，start和end是中序序列的开始和结尾
    //用分而治之的策略，使用先序序列第一个元素(根结点)对中序序列的划分出的左右子树的两个中序序列递归进行划分，直到划分到只剩一个
    //如果给出后序和中序，求先序，也是一样的，只是变成用后序序列的最后一个元素划分中序序列
    //中序序列是必须知道的，因为没有中序序列，就没法把二叉树划分成根和左右子树
    if(start > end)return;
    int i = start;
    static int flag=0;
    while(i < end && inorder[i] != preorder[root]) i++;     //找到中序序列中的根结点下标
    post(root + 1, start, i - 1);                           //左子树求后序序列，root+1为左子树先序序列中的根结点
    post(root + 1 + i - start, i + 1, end);   //右子树求后序序列，i-start是左子树结点个数，root+1+i-start是右子树先序根结点
    if(!flag){
        cout<<preorder[root];
        flag=1;
    }else cout<<' '<<preorder[root];
}
*/