/* 7-2 Color the Tree (35 分)
    There is a kind of balanced binary search tree named red-black tree in the data structure. 
    It has the following 5 properties:
    (1) Every node is either red or black.
    (2) The root is black.
    (3) Every leaf (NULL) is black.
    (4) If a node is red, then both its children are black.
    (5) For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
    For example, the tree in Figure 1 is a red-black tree, while the ones in Figure 2 and 3 are not.

    For each given binary search tree, you are supposed to tell if it is possible to color the nodes and turn it 
    into a legal red-black tree.
    Input Specification:
    Each input file contains several test cases. The first line gives a positive integer K (≤10) which is the 
    total number of cases. 
    For each case, the first line gives a positive integer N (≤30), 
    the total number of nodes in the binary search tree. 
    The second line gives the postorder traversal sequence of the tree. 
    All the numbers in a line are separated by a space.
    Output Specification:
    For each test case, print in a line Yes if the given tree can be turned into a legal red-black tree, 
    or No if not.
    Sample Input:             Sample Output:
    3                         Yes
    9                         No
    1 4 5 2 8 15 14 11 7      Yes
    9
    1 4 5 8 7 2 15 14 11
    8
    6 5 8 7 11 17 15 10
*/
/* ac题解(网上资源) 
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn=111;
struct node
{
    int l,r,tol;
}stu[maxn];
int n,a[maxn],root,tot;
void handle(int l,int r,int pre)
{
    if(l==r) return ;
    int pos=r;
    for(int i=r-1;i>=l;--i) if(a[i]>a[r]) pos=i;
    if(pos==r){
        int cnt=++tot;
        stu[cnt].l=0;
        stu[cnt].r=0;
        handle(l,pos-1,cnt);
        stu[pre].l=cnt;
    }
    else if(pos==l){
        int cnt=++tot;
        stu[cnt].l=0;
        stu[cnt].r=0;
        handle(pos,r-1,cnt);
        stu[pre].r=cnt;
    }
    else{
        int cnt=++tot;
        stu[cnt].l=0;
        stu[cnt].r=0;
        handle(l,pos-1,cnt);
        stu[pre].l=cnt;
        cnt=++tot;
        stu[cnt].l=0;
        stu[cnt].r=0;
        handle(pos,r-1,cnt);
        stu[pre].r=cnt;
    }
}
vector<int> solve(vector<int> p,vector<int> q)
{
    vector<int> res;
    res.clear();
    for(int i=0;i<(int)p.size();++i){
        int u=p[i];
        for(int j=0;j<(int)q.size();++j){
            if(u==q[j]){
                res.push_back(u);
                break;
            }
        }
    }
    return res;
}
int tol;
vector<int> red[maxn],black[maxn];
bool flag;
void dfs(int cur)
{
    if(flag==false) return ;
    if(stu[cur].l>0 && stu[cur].r>0){
        dfs(stu[cur].l);
        if(flag==false) return ;
        dfs(stu[cur].r);
        if(flag==false) return ;
        vector<int> x=solve(black[stu[stu[cur].l].tol],black[stu[stu[cur].r].tol]);
        int cnt=++tol;
        stu[cur].tol=cnt;
        red[cnt]=x;
        black[cnt].clear();
        vector<int> y=solve(black[stu[stu[cur].l].tol],red[stu[stu[cur].r].tol]);
        vector<int> z=solve(red[stu[stu[cur].l].tol],black[stu[stu[cur].r].tol]);
        vector<int> w=solve(red[stu[stu[cur].l].tol],red[stu[stu[cur].r].tol]);
        set<int> se;
        se.clear();
        for(int i=0;i<(int)x.size();++i) se.insert(x[i]);
        for(int i=0;i<(int)y.size();++i) se.insert(y[i]);
        for(int i=0;i<(int)z.size();++i) se.insert(z[i]);
        for(int i=0;i<(int)w.size();++i) se.insert(w[i]);
        set<int>::iterator it;
        for(it=se.begin();it!=se.end();++it){
            black[cnt].push_back((*it)+1);
        }
        if((int)red[cnt].size()==0 && (int)black[cnt].size()==0){
            flag=false;
            return ;
        }
    }
    else if(stu[cur].l>0){
        dfs(stu[cur].l);
        if(flag==false) return ;
        int id=stu[stu[cur].l].tol;
        bool have0=false;
        for(int i=0;i<(int)red[id].size();++i){
            if(red[id][i]==0){
                have0=true;
                break;
            }
        }
        if(have0==false){
            flag=false;
            return ;
        }
        int cnt=++tol;
        stu[cur].tol=cnt;
        red[cnt].clear();
        black[cnt].clear();
        black[cnt].push_back(1);
    }
    else if(stu[cur].r>0){
        dfs(stu[cur].r);
        if(flag==false) return ;
        int id=stu[stu[cur].r].tol;
        bool have0=false;
        for(int i=0;i<(int)red[id].size();++i){
            if(red[id][i]==0){
                have0=true;
                break;
            }
        }
        if(have0==false){
            flag=false;
            return ;
        }
        int cnt=++tol;
        stu[cur].tol=cnt;
        red[cnt].clear();
        black[cnt].clear();
        black[cnt].push_back(1);
    }
    else{
        int cnt=++tol;
        stu[cur].tol=cnt;
        red[cnt].clear();
        red[cnt].push_back(0);
        black[cnt].clear();
        black[cnt].push_back(1);
    }
}
int main()
{
    int t;
    for(scanf("%d",&t);t;--t){
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        tot=0;
        root=++tot;
        stu[root].l=0;
        stu[root].r=0;
        handle(1,n,1);
        flag=true;
        tol=0;
        dfs(root);
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
我的答案，两个测试点不通过  
#include<queue>
#include<cstdlib>
#include<cstdio>
#define MAXNODES 35
using namespace std;
typedef struct RBnode*nodeptr;
struct RBnode{
    nodeptr parent,leftchild,rightchild;
    int value,color;
};
enum color{black,red};
void posttolevel(int,int),solve(int);
bool judgeRB(nodeptr);
queue<int>levelorder;
int postorder[MAXNODES];
nodeptr buildRB(nodeptr),insertRB(nodeptr,int);
int main(){
    int totalcases,nodes,nodevalue;
    scanf("%d",&totalcases);
    for(int i=0;i<totalcases;i++){
        scanf("%d",&nodes);
        for(int j=0;j<nodes;j++)scanf("%d",&postorder[j]);
        solve(nodes);
    }
}
void solve(int nodes){
    levelorder.push(postorder[nodes-1]);
    posttolevel(0,nodes-1);
    nodeptr btree=nullptr;
    btree=buildRB(btree);
    if(judgeRB(btree))printf("Yes\n");
    else printf("No\n");
}
bool judgeRB(nodeptr root){
    if(root->value>0){
        if(root->color==red&&root->parent->color==red)return false;
        return judgeRB(root->leftchild)&&judgeRB(root->rightchild);
    }
    return true;
}
void posttolevel(int start,int end){
    if(start>end)return;
    int i=start,pivot=0;
    for(;postorder[i]<postorder[end];i++);
    pivot=i;
    if(pivot>start)levelorder.push(postorder[pivot-1]);
    if(pivot<end)levelorder.push(postorder[end-1]);
    posttolevel(start,pivot-1);
    posttolevel(pivot,end-1);
}
nodeptr buildRB(nodeptr root){
    while(!levelorder.empty()){
        root=insertRB(root,levelorder.front());
        levelorder.pop();
    }
    return root;
}
nodeptr insertRB(nodeptr root,int insertvalue){
    if(!root){
        root=(nodeptr)malloc(sizeof(struct RBnode));
        root->leftchild=(nodeptr)malloc(sizeof(struct RBnode));
        root->rightchild=(nodeptr)malloc(sizeof(struct RBnode));
        root->parent=nullptr,root->leftchild->parent=root->rightchild->parent=root;
        root->value=insertvalue,root->leftchild->value=root->rightchild->value=-1;
        root->color=root->leftchild->color=root->rightchild->color=black;
    }
    if(root->value<0){
        root->leftchild=(nodeptr)malloc(sizeof(struct RBnode));
        root->rightchild=(nodeptr)malloc(sizeof(struct RBnode));
        root->leftchild->parent=root->rightchild->parent=root;
        root->value=insertvalue,root->leftchild->value=root->rightchild->value=-1;
        root->color=red,root->leftchild->color=root->rightchild->color=black;
        if(root->parent->color==red){
            nodeptr grandparent=root->parent->parent,
                    leftancle=grandparent->leftchild,rightancle=grandparent->rightchild;
            if(root->parent->value<grandparent->value&&rightancle->color==red){
                root->parent->color=rightancle->color=black;
                if(grandparent->parent)grandparent->color=red;
            }else if(root->parent->value>grandparent->value&&leftancle->color==red){
                root->parent->color=leftancle->color=black;
                if(grandparent->parent)root->parent->parent->color=red;
            }
        }
    }else if(root->value>insertvalue)root->leftchild=insertRB(root->leftchild,insertvalue);
    else if(root->value<insertvalue)root->rightchild=insertRB(root->rightchild,insertvalue);
    return root;
}  */

   
    
   