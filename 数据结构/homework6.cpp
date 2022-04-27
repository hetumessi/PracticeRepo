/*
    06-图1 列出连通集
    给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。
    进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

    输入格式:
    输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。
    输出格式:
    按照"{ v1 v​2 ... vk}"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。
    输入样例:           输出样例:
    8 6                { 0 1 4 2 7 }
    0 7                { 3 5 }
    0 1                { 6 }
    2 0                { 0 1 2 7 4 }
    4 1                { 3 5 }
    2 4                { 6 }
    3 5
答案：
#include<iostream>
#include<queue>
#define maxinte 10
using namespace std;
void BuildMGraph();
void printdb();
void DFS(int);
void BFS(int);
int MGraph[maxinte][maxinte],Ne,Nv;
bool visited[maxinte];
int main(){
    BuildMGraph();
    printdb();
}
void BuildMGraph(){
    cin>>Nv>>Ne;
    int v1,v2;
    for(int i=0;i<Nv;i++)for(int j=0;j<Nv;j++)MGraph[i][j]=0;
    for(int i=0;i<Ne;i++){
        cin>>v1>>v2;
        MGraph[v1][v2]=MGraph[v2][v1]=1;
    }
}
void printdb(){
    for(int j=0;j<Nv;j++)visited[j]=false;
    for(int i=0;i<Nv;i++)
        if(!visited[i]){
            cout<<"{ ";
            DFS(i);
            cout<<"}"<<endl;
        }
    for(int j=0;j<Nv;j++)visited[j]=false;
    for(int i=0;i<Nv;i++)
        if(!visited[i]){
            cout<<"{ ";
            BFS(i);
            cout<<"}"<<endl;
        }
}
void DFS(int v){
    visited[v]=true;
    cout<<v<<' ';
    for(int i=0;i<Nv;i++)
        if(MGraph[v][i]!=0&&!visited[i])DFS(i);
}
void BFS(int v){
    queue<int> q;
    int w;
    q.push(v);
    visited[v]=true;
    while(!q.empty()){
        v=q.front(),q.pop();
        cout<<v<<' ';
        for(int i=0;i<Nv;i++)
            if(MGraph[v][i]!=0&&!visited[i]){
                visited[i]=true;
                q.push(i);
            }
    }
}*/
/*
    1076 Forwards on Weibo (30 分)
    Weibo is known as the Chinese version of Twitter.
    One user on Weibo may have many followers, and may follow many other users as well. 
    Hence a social network is formed with followers relations. When a user makes a post on Weibo, 
    all his/her followers can view and forward his/her post, which can then be forwarded again by their followers. 
    Now given a social network, 
    you are supposed to calculate the maximum potential amount of forwards for any specific user, 
    assuming that only L levels of indirect followers are counted.

    Input Specification:
    Each input file contains one test case. For each case, 
    the first line contains 2 positive integers: N (≤1000), 
    the number of users; and L (≤6), the number of levels of indirect followers that are counted. 
    Hence it is assumed that all the users are numbered from 1 to N. 
    Then N lines follow, each in the format:

    M[i] user_list[i]
    where M[i] (≤100) is the total number of people that user[i] follows; 
    and user_list[i] is a list of the M[i] users that followed by user[i]. 
    It is guaranteed that no one can follow oneself. 
    All the numbers are separated by a space.

    Then finally a positive K is given, followed by K UserID's for query.

    Output Specification:
    For each UserID, 
    you are supposed to print in one line the maximum potential amount of forwards this user can trigger, 
    assuming that everyone who can view the initial post will forward it once, 
    and that only L levels of indirect followers are counted.

    Sample Input:       Sample Output:
    7 3                 4
    3 2 3 4             5
    0
    2 5 6
    2 3 1
    2 3 4
    1 4
    1 5
    2 2 6
题意分析：本题输入给出的是关注的人，注意转发微博是关注的人转发被关注的人，所以边的方向应该是关注指向被关注
        (可以理解为关注的人本身是不知道有什么人关注了他自己的)
        输出是是在给定层数l限制下最多能有多少人转发(即与给定顶点之间路径长度不超过l的结点个数)
#include<iostream>
#include<queue>
#define MaxUsers 1000
using namespace std;
typedef int Vertex;
typedef struct AdjVNode *PtrToAdjVNode;
typedef struct LGNode *PtrToLGNode;
typedef struct Vnode AdjList[MaxUsers+1];
typedef PtrToLGNode LGraph;
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};
struct Vnode{
    PtrToAdjVNode FirstEdge;
};
struct LGNode{
    int Nv,Ne;
    AdjList G;
};
LGraph CreatelGraph(int);
void InsertEdge(LGraph,int,int);
LGraph BuildLGraph(int);
void ForwardsonWeibo(LGraph,int,bool*);
int BFS(LGraph,int,int,bool*);
int main(int argc,char*argv[]) {
    int l,n;
    cin>>n>>l;
    bool visited[n+1];
    LGraph L=BuildLGraph(n);
    ForwardsonWeibo(L,l,visited);
}
LGraph BuildLGraph(int n){
    int user,userl;
    LGraph L=CreatelGraph(n);
    for(int i=1;i<=n;i++){
        cin >> user;
        for(int j=1; j <=user; j++){
            cin>>userl;
            InsertEdge(L,i,userl);
        }
    }
    return L;
}
LGraph CreatelGraph(int n){
    auto L=new struct LGNode;
    for(int i=0;i<=n;i++)L->G[i].FirstEdge= nullptr;
    L->Nv=n,L->Ne=0;
    return L;
}
void InsertEdge(LGraph L,int user,int userl){
    auto newnode=new struct AdjVNode;
    newnode->AdjV=user;
    newnode->Next=L->G[userl].FirstEdge;
    L->G[userl].FirstEdge=newnode;
    L->Ne++;
}
void ForwardsonWeibo(LGraph L,int l,bool*visited){
    int n,v;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>v;
        for(int j=1;j<=L->Nv;j++)visited[j]= false;
        cout<<BFS(L,v,l,visited)<<endl;
    }
}
int BFS(LGraph L,int v,int l,bool*visited){
    int last=v,tail,level=0,count=0;
    PtrToAdjVNode w;
    queue<int> q;
    q.push(v);
    visited[v]=true;
    while(!q.empty()){
        v=q.front(),q.pop();
        w=L->G[v].FirstEdge;
        while(w) {
            if (!visited[w->AdjV]) {
                q.push(w->AdjV);
                visited[w->AdjV] = true, count++, tail = w->AdjV;
            }
            w = w->Next;
        }
        if(v==last)level++,last=tail;
        if(level==l)break;
    }
    return count;
}
*/
    
    
    