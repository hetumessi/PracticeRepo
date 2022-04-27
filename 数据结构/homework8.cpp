/*
    08-图7 公路村村通 (30 分)
    现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。

    输入格式:
    输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；
    随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。
    为简单起见，城镇从1到N编号。

    输出格式:
    输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。

    输入样例:   输出样例:
    6 15       12
    1 2 5
    1 3 3
    1 4 7
    1 5 4
    1 6 2
    2 3 4
    2 4 6
    2 5 2
    2 6 6
    3 4 6
    3 5 1
    3 6 1
    4 5 10
    4 6 8
    5 6 3
答案：
(prim版本)
#include<iostream>
#define INFINITY 65535
#define MaxVertexNum 1005
using namespace std;
int G[MaxVertexNum][MaxVertexNum],dist[MaxVertexNum],nv,ne,findmindist();
void buildgraph(),prim();
int main(){
    cin>>nv>>ne;
    buildgraph();
    prim();
}
void buildgraph(){
    int v1,v2;
    for(int i=1;i<=nv;i++)for(int j=1;j<=nv;j++)G[i][j]=INFINITY;
    for(int i=0;i<ne;i++){
        cin>>v1>>v2>>G[v1][v2];
        G[v2][v1]=G[v1][v2];
    }
}
int findmindist(){
    int mindist=INFINITY,mini=-1;
    for(int i=1;i<=nv;i++)if(dist[i]&&dist[i]<mindist)mindist=dist[i],mini=i;
    if(mindist<INFINITY)return mini;
    return -1;
}
void prim(){
    int totalweight=0,count=0;
    for(int i=1;i<=nv;i++)dist[i]=G[1][i];
    dist[1]=0,count++;
    while(true){
        int v=findmindist();
        if(v<0)break;
        totalweight+=dist[v],count++;
        dist[v]=0;
        for(int i=1;i<=nv;i++)if(dist[i]&&G[v][i]<INFINITY)
            if(dist[i]>G[v][i])dist[i]=G[v][i];
    }
    if(count<nv)cout<<-1;
    else cout<<totalweight;
}   
(kruskal版本)
#include<iostream>
#define MaxVertexNum 1005
using namespace std;
typedef struct{
    int v1,v2,price;
}road;
road roads[MaxVertexNum*3];
int nv,ne,set[MaxVertexNum],findset(int*,int),cmp(const void*,const void*);
void initedge(),kruskal(),unionset(int,int);
int main(){
    cin>>nv>>ne;
    initedge();
    kruskal();
}
void initedge(){
    for(int i=0;i<ne;i++)cin>>roads[i].v1>>roads[i].v2>>roads[i].price;
}
int cmp(const void*a,const void*b){
    return((road*)a)->price-((road*)b)->price;
}
int findset(int*set,int x){
    if(set[x]<0)return x;
    return set[x]=findset(set,set[x]);
}
void unionset(int root1,int root2){
    if(set[root1]>set[root2]){
        set[root2]+=set[root1];
        set[root1]=root2;
    }else{
        set[root1]+=set[root2];
        set[root2]=root1;
    }
}
void kruskal(){
    int count=0,totalweight=0;
    for(int i=1;i<=nv;i++)set[i]=-1;
    qsort(roads,ne,sizeof(road),cmp);
    for(int i=0;i<ne&&count<nv-1;i++){
        int root1=findset(set,roads[i].v1),root2=findset(set,roads[i].v2);
        if(root1!=root2){
            unionset(root1,root2);
            count++,totalweight+=roads[i].price;
        }
    }
    if(count<nv-1)cout<<-1;
    else cout<<totalweight;
} */
/*
    08-图8 How Long Does It Take (25 分)
    Given the relations of all the activities of a project, 
    you are supposed to find the earliest completion time of the project.

    Input Specification:
    Each input file contains one test case. 
    Each case starts with a line containing two positive integers N (≤100), 
    the number of activity check points (hence it is assumed that the check points are numbered from 0 to N−1), 
    and M, the number of activities. Then M lines follow, each gives the description of an activity. 
    For the i-th activity, three non-negative numbers are given: S[i], E[i], and L[i], 
    where S[i] is the index of the starting check point, E[i] of the ending check point, 
    and L[i] the lasting time of the activity. 
    The numbers in a line are separated by a space.

    Output Specification:
    For each test case, if the scheduling is possible, 
    print in a line its earliest completion time; or simply output "Impossible".

    Sample Input 1:     Sample Output 1:    Sample Input 2:     Sample Output 2: 
    9 12                18                  4 5                 Impossible
    0 1 6                                   0 1 1
    0 2 4                                   0 2 2
    0 3 5                                   2 1 3
    1 4 1                                   1 3 4
    2 4 1                                   3 2 5
    3 5 2
    5 4 0
    4 6 9
    4 7 7
    5 7 4
    6 8 2
    7 8 4
答案：
#include<iostream>
#include<queue>
#define INFINITY 65535
#define MaxVertexNum 105
using namespace std;
int G[MaxVertexNum][MaxVertexNum],ve[MaxVertexNum],indegree[MaxVertexNum],nv,ne;
void buildgraph(),topsort();
int main(){
    cin>>nv>>ne;
    buildgraph();
    topsort();
}
void buildgraph(){
    int v1,v2;
    for(int i=0;i<nv;i++)for(int j=0;j<nv;j++)G[i][j]=INFINITY;
    for(int i=0;i<ne;i++)cin>>v1>>v2>>G[v1][v2];
}
void topsort(){
    int count=0,comptime=0;
    queue<int>q;
    for(int i=0;i<nv;i++)for(int j=0;j<nv;j++)if(G[i][j]<INFINITY)indegree[j]++;
    for(int i=0;i<nv;i++)if(!indegree[i])q.push(i);
    while(!q.empty()){
        int v=q.front();
        q.pop(),count++;
        for(int i=0;i<nv;i++)if(G[v][i]<INFINITY){
            if(!--indegree[i])q.push(i);
            if(ve[i]<ve[v]+G[v][i])ve[i]=ve[v]+G[v][i];
        }
    }
    if(count<nv-1)cout<<"Impossible";
    else{
        for(int i=0;i<nv;i++)if(ve[i]>comptime)comptime=ve[i];
        cout<<comptime;
    }
}   */
/*
    08-图9 关键活动 (30 分)
    假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。
    “任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

    比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。
    有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；
    有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

    但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。
    比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，
    那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

    任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。
    在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；
    但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

    请编写程序判定一个给定的工程项目的任务调度是否可行；
    如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

    输入格式:
    输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，
    例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。
    随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

    输出格式:
    如果任务调度不可行，则输出0；
    否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，
    每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。
    关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

    输入样例:       输出样例:
    7 8            17
    1 2 4          1->2
    1 3 3          2->4
    2 4 5          4->6
    3 4 3          6->7
    4 5 1
    4 6 6
    5 7 5
    6 7 2
答案：
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#define MaxVertexNum 105
#define INFINITY 65535
using namespace std;
int nv,ne,maxve,G[MaxVertexNum][MaxVertexNum],indegree[MaxVertexNum],ve[MaxVertexNum],vl[MaxVertexNum];
typedef struct{
    int start,end,ee,el;
}activity;
vector<activity>project;
void buildgraph(),crticlepath();
bool toposort();
int main(){
    cin>>nv>>ne;
    buildgraph();
    crticlepath();
}
void buildgraph(){
    int start,end;
    for(int i=1;i<=nv;i++)for(int j=1;j<=nv;j++)G[i][j]=INFINITY;
    for(int i=0;i<ne;i++){
        cin>>start>>end>>G[start][end];
        activity act;
        act.start=start,act.end=end;
        project.push_back(act);
    }
}
bool toposort(){
    for(int i=1;i<=nv;i++)for(int j=1;j<=nv;j++)if(G[i][j]<INFINITY)indegree[j]++;
    queue<int>q;
    stack<int>s;
    int count=0;
    for(int i=1;i<=nv;i++)if(!indegree[i])q.push(i);
    while(!q.empty()){
        int v=q.front();
        s.push(v),q.pop(),count++;
        for(int i=1;i<=nv;i++)if(G[v][i]<INFINITY){
            if(!--indegree[i])q.push(i);
            if(ve[i]<ve[v]+G[v][i])ve[i]=ve[v]+G[v][i];
        }
    }
    for(int i=1;i<=nv;i++)if(ve[i]>maxve)maxve=ve[i];
    for(int i=1;i<=nv;i++)vl[i]=maxve;
    while(!s.empty()){
        int v=s.top();
        s.pop();
        for(int i=1;i<=nv;i++)if(G[v][i]<INFINITY)
            if(vl[v]>vl[i]-G[v][i])vl[v]=vl[i]-G[v][i];
    }
    if(count<nv-1)return false;
    return true;
}
void crticlepath(){
    if(toposort()){
        activity tmp;
        cout<<maxve<<endl;
        for(auto &i:project)i.ee=ve[i.start],i.el=vl[i.end]-G[i.start][i.end];
        for(int i=1;i<project.size();i++)for(int j=0;j<project.size()-i;j++)
            if(project[j].start>project[j+1].start)tmp=project[j],project[j]=project[j+1],project[j+1]=tmp;
        for(int i=1;i<project.size();i++)if(project[i].start==project[i+1].start)
            tmp=project[i],project[i]=project[i+1],project[i+1]=tmp;
        for(auto i:project)if(i.ee==i.el)cout<<i.start<<"->"<<i.end<<endl;
    }else cout<<0;
}  */