/* 
    07-图5 Saving James Bond - Hard Version (30 分)
    This time let us consider the situation in the movie "Live and Let Die" in which James Bond, 
    the world's most famous spy, was captured by a group of drug dealers. 
    He was sent to a small piece of land at the center of a lake filled with crocodiles. 
    There he performed the most daring action to escape -- he jumped onto the head of the nearest crocodile! 
    Before the animal realized what was happening, James jumped again onto the next big head... 
    Finally he reached the bank before the last crocodile could bite him 
    (actually the stunt man was caught by the big mouth and barely escaped with his extra thick boot).

    Assume that the lake is a 100 by 100 square one. 
    Assume that the center of the lake is at (0,0) and the northeast corner at (50,50). 
    The central island is a disk centered at (0,0) with the diameter of 15. 
    A number of crocodiles are in the lake at various positions. 
    Given the coordinates of each crocodile and the distance that James could jump, 
    you must tell him a shortest path to reach one of the banks. 
    The length of a path is the number of jumps that James has to make.

    Input Specification:
    Each input file contains one test case. 
    Each case starts with a line containing two positive integers N (≤100), 
    the number of crocodiles, and D, the maximum distance that James could jump. 
    Then N lines follow, each containing the (x,y) location of a crocodile. 
    Note that no two crocodiles are staying at the same position.

    Output Specification:
    For each test case, if James can escape, output in one line the minimum number of jumps he must make. 
    Then starting from the next line, output the position (x,y) of each crocodile on the path, 
    each pair in one line, from the island to the bank. 
    If it is impossible for James to escape that way, simply give him 0 as the number of jumps. 
    If there are many shortest paths, just output the one with the minimum first jump, 
    which is guaranteed to be unique.

    Sample Input 1:             Sample Input 2:
    17 15                       4 13
    10 -21                      -12 12
    10 21                       12 12
    -40 10                      -12 -12
    30 -50                      12 -12
    20 40                       Sample Output 2:
    35 10                       0
    0 -10
    -25 22
    40 -40
    -30 30
    -10 22
    0 11
    25 21
    25 10
    10 10
    10 35
    -30 10
    Sample Output 1:
    4
    0 11
    10 21
    10 35
答案：(对题意理解有误，需要重做)
#include<iostream>
#include<cmath>
#include<stack>
#define MaxVertexNum 101
using namespace std;
typedef struct Point{
    int x,y;
}point;
double G[MaxVertexNum][MaxVertexNum];
point P[MaxVertexNum];
void Dijikstra(int,int,int),BuildGraph(int,int),Save007(int,int);
double canjump(point,point,int),dist[MaxVertexNum]={0};
int FindMindist(int),path[MaxVertexNum][MaxVertexNum];
bool canescape(point,int),firstjump(point,int),collected[MaxVertexNum]={false};
int main(int argc,char*argv[]) {
    int n,jump;
    cin>>n>>jump;
    BuildGraph(n,jump);
    Save007(n,jump);
}
void BuildGraph(int n,int jump){
    int i,j;
    for(i=1;i<=n;i++)cin>>P[i].x>>P[i].y;
    for(i=0;i<=n;i++)for(j=0;j<=n;j++)if(i!=j)G[i][j]=INFINITY;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)if(i!=j&&canjump(P[i],P[j],jump)!=0)
                G[i][j]=G[j][i]=canjump(P[i],P[j],jump);
}
void Save007(int n,int jump){
    int i,j,mini=1,minj;
    stack<int> s;
    double mind=INFINITY;
    for(i=1;i<=n;i++)if(!collected[i]&&firstjump(P[i],jump)){
            for(j=1;j<=n;j++)dist[j]=INFINITY;
            Dijikstra(i,n,jump);
            for(j=1;j<=n;j++)if(canescape(P[j],jump)&&mind>dist[j])mind=dist[j],mini=i,minj=j;
    }
    if(mind<INFINITY){
        for(i=minj;i!=mini;i=path[mini][i])s.push(i);
        s.push(mini);
        cout<<s.size()+1<<endl;
        while(!s.empty()){
            cout<<P[s.top()].x<<' '<<P[s.top()].y<<endl;
            s.pop();
        }
    }else cout<<0<<endl;
}
bool firstjump(point p,int jump){
    return sqrt(pow(p.x,2)+pow(p.y,2))<=jump;
}
bool canescape(point p,int jump){
    return (p.x+jump>=50||p.x-jump<=-50||p.y+jump>=50||p.y-jump<=-50);
}
double canjump(point p1,point p2,int jump){
    double d;
    if((d=(sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2))))<=jump)return d;
    return 0;
}
int FindMindist(int n){
    double mindist=INFINITY;
    int mini=1;
    for(int i=1;i<=n;i++)if(!collected[i]&&dist[i]<mindist)
        mindist=dist[i],mini=i;
    if(mindist<INFINITY)return mini;
    else return -1;
}
void Dijikstra(int s,int n,int jump){
    int count=2;
    for(int i=1;i<=n;i++){
        dist[i]=G[s][i];
        if(dist[i]<INFINITY)path[s][i]=s;
        else path[s][i]=-1;
    }
    dist[s]=0,collected[s]=true;
    while(true){
        int v = FindMindist(n);
        collected[v]=true,count++;
        if (v < 0)break;
        for (int i = 1; i <= n; i++)
            if (!collected[i] && G[v][i] < INFINITY)
                if (dist[i] > dist[v] + G[v][i]) {
                    dist[i] = dist[v] + G[v][i];
                    path[s][i] = v;
                }
    }
}  */
/*
    07-图6 旅游规划 (25 分)
    有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。
    现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。
    如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

    输入格式:
    输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；
    M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。
    随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。
    输入保证解的存在。

    输出格式:
    在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

    输入样例:           输出样例:
    4 5 0 3            3 40
    0 1 1 20
    1 3 2 30
    0 3 4 10
    0 2 2 20
    2 3 1 20

    题意理解：
    *城市为结点
    *公路为边
        *权重1：距离
        *权重2：收费
    *单源最短路
        *Dijkstra——距离
        *等距离时按收费更新
    核心算法伪代码描述：
    void Dijkstra(Vertex S)
    {
        while(1)
        {
            v=未收录顶点中dist最小者;
            if(这样的v不存在)
                break;
            collected[w]==true;
            for(v的每个邻接点w)
                if(collected[w]==false)
                    if(dist[v]+E(v,w)<dist[w])
                    {
                        dist[w]=dist[v]+E(v,w);
                        path[w]=v;
                        cost[w]=cast[v]+C(v,w);
                    }
                    else if((dist[v]+E(v,w)==dist[w])
                            &&(cost[v]+C(v,w)<cost[w]))
                    {
                        cost[w]=cost[v]+C(v,w);
                    }
        }
    }
    其他类似问题
    *要求数最短路径有多少条
        *count[s]=1;
        *如果找到更短路：count[w]=count[v];
        *如果找到等长路：count[w]+=count[v];
    *要求边数最少得最短路(本质上等价于dist，只不过每新增一条边的权重均为1)
        *count[s]=0;
        *如果找到更短路：count[w]=count[v]+1;
        *如果找到等长路：count[w]=count[v]+1;
答案：
#include<iostream>
#define MaxCities 500
#define INFINITY 65535
using namespace std;
typedef struct{
    int length,price;
}highway;
highway G[MaxCities][MaxCities];
bool collected[MaxCities]={false};
int dist[MaxCities],price[MaxCities];
void Buildgraph(int,int);
int FindMindistprice(int);
void Dijkstra(int,int);
void selectpath(int,int,int);
int main(int argc,char*argv[]) {
    int N,M,S,D;
    cin>>N>>M>>S>>D;
    Buildgraph(M,N);
    selectpath(N,S,D);
}
void Buildgraph(int m,int n){
    int c1,c2;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        G[i][j].length=G[i][j].price=INFINITY;
        G[j][i]=G[i][j];
    }
    for(int i=0;i<m;i++){
        cin>>c1>>c2>>G[c1][c2].length>>G[c1][c2].price;
        G[c2][c1]=G[c1][c2];
    }
}
void selectpath(int n,int s,int d){
    for(int i=0;i<n;i++)dist[i]=price[i]=INFINITY;
    Dijkstra(s,n);
    cout<<dist[d]<<' '<<price[d]<<endl;
}
int FindMindistprice(int n){
    int mind=INFINITY,minp=INFINITY,mini=0;
    for(int i=0;i<n;i++)if(!collected[i]&&(mind>=dist[i]||(mind==dist[i]&&minp>price[i])))
        mind=dist[i],mini=i,minp=price[i];
    if(mind<(int)INFINITY)return mini;
    return -1;
}
void Dijkstra(int s,int n){
    for(int i=0;i<n;i++)dist[i]=G[s][i].length,price[i]=G[s][i].price;
    collected[s]=true,dist[s]=price[s]=0;
    while(true){
        int v=FindMindistprice(n);
        collected[v]=true;
        if(v<0)break;
        for(int i=0;i<n;i++)if(!collected[i]&&G[v][i].length<(int)INFINITY)
            if (dist[i]>dist[v]+G[v][i].length||(dist[i]==dist[v]+G[v][i].length&&price[i]>price[v]+G[v][i].price))
                dist[i]=dist[v]+G[v][i].length,price[i]=price[v]+G[v][i].price;
    }
}
*/
/* 
    1072 Gas Station (30 分)
    A gas station has to be built at such a location that the minimum distance between the station 
    and any of the residential housing is as far away as possible. 
    However it must guarantee that all the houses are in its service range.

    Now given the map of the city and several candidate locations for the gas station, 
    you are supposed to give the best recommendation. 
    If there are more than one solution, output the one with the smallest average distance to all the houses. 
    If such a solution is still not unique, output the one with the smallest index number.

    Input Specification:
    Each input file contains one test case. For each case, the first line contains 4 positive integers: 
    N (≤10^​3), the total number of houses; 
    M (≤10), the total number of the candidate locations for the gas stations; 
    K (≤10^​4), the number of roads connecting the houses and the gas stations; 
    and D​S, the maximum service range of the gas station. 
    It is hence assumed that all the houses are numbered from 1 to N, 
    and all the candidate locations are numbered from G1 to GM.

    Then K lines follow, each describes a road in the format

    P1 P2 Dist
    where P1 and P2 are the two ends of a road which can be either house numbers or gas station numbers, 
    and Dist is the integer length of the road.

    Output Specification:
    For each test case, print in the first line the index number of the best location. 
    In the next line, print the minimum and the average distances between the solution and all the houses. 
    The numbers in a line must be separated by a space and be accurate up to 1 decimal place. 
    If the solution does not exist, simply output No Solution.

    Sample Input 1:         Sample Output 1:           Sample Input 2:          Sample Output 2:
    4 3 11 5                G1                         2 1 2 10                 No Solution
    1 2 2                   2.0 3.3                    1 G1 9
    1 4 2                                              2 G1 20
    1 G1 4
    1 G2 3
    2 3 2
    2 G2 1
    3 4 2
    3 G3 2
    4 G1 3
    G2 G1 1
    G3 G2 2
    题意分析：
    本题输出的是Gas Station与全部居民楼中的最短距离中距离最长的候选点，Gas Station与居民楼的距离最长不能超过ds，否则直接淘汰该候选点
    如果该距离相等的话找到其中距离居民楼的平均距离最短的候选点输出，两种距离都相等的话输出序号最小的那一个候选点
    在计算Gas Station与居民楼距离的时候需要将m个候选Gas Station全部纳入图中，因为输入中给出了居民楼和候选地址之间的边
    但是计算平局距离和最短距离时只能在Gas Station与居民楼的距离中计算
    输入中存在字符'G'，因此存储输入的变量类型为char[]，因为n<=1000，所以数组长度至少为4
答案：
#include<iostream>
#include<cstdlib>
#define MaxHouses 1000
#define MaxStation 10
#define INFINITY 65535
using namespace std;
int G[MaxHouses+MaxStation+1][MaxHouses+MaxStation+1],dist[MaxHouses+MaxStation+1];
bool collected[MaxHouses+MaxStation+1];
void Buildgraph(int,int,int,int);
void GasStation(int,int,int);
bool Dijkstra(int,int,int,int);
int FindMindist(int,int,int);
int main(int argc,char*argv[]) {
    int n,m,k,ds;
    cin>>n>>m>>k>>ds;
    Buildgraph(n,k,m,ds);
    GasStation(n,ds,m);
}
void Buildgraph(int n,int k,int m,int ds){
    int g1,g2,l;char s1[5],s2[5];
    for(int i=1;i<=n+m;i++)for(int j=1;j<=n+m;j++)if(i!=j)G[i][j]=INFINITY;
    for(int i=1;i<=k;i++){
        cin>>s1>>s2>>l;
        g1=(s1[0]=='G'?atoi(s1+1)+n:atoi(s1));
        g2=(s2[0]=='G'?atoi(s2+1)+n:atoi(s2));
        G[g1][g2]=G[g2][g1]=l;
    }
}
void GasStation(int n,int ds,int m){
    double mina=INFINITY;int mini=0,mind=0;
    for(int i=n+1;i<=n+m;i++){
        for(int j=1;j<=n+m;j++)collected[j]=false;
        if(Dijkstra(n,m,i,ds)){
            int min=INFINITY;double ave=0;
            for(int j=1;j<=n;j++){
                ave+=dist[j];
                if(min>dist[j]&&i!=j)min=dist[j];
            }
            ave=ave/n;
            if(mind<min||(mind==min&&mina>ave))mina=ave,mind=min,mini=i;
        }
    }
    if(mina<INFINITY){
        cout<<'G'<<mini-n<<endl;
        printf("%.1f %.1f\n",(double)mind,mina);
    }else cout<<"No Solution"<<endl;
}
bool Dijkstra(int n,int m,int s,int ds){
    for(int i=1;i<=n+m;i++)dist[i]=G[s][i];
    collected[s]=true,dist[s]=0;
    while(true){
        int v=FindMindist(n,m,ds);
        if(v<0)break;
        collected[v]=true;
        for(int i=1;i<=n+m;i++)if(!collected[i]&&G[v][i]<INFINITY)
            if(dist[i]>dist[v]+G[v][i])dist[i]=dist[v]+G[v][i];
    }
    for(int i=1;i<=n;i++)if(dist[i]>ds)return false;
    return true;
}
int FindMindist(int n,int m,int ds){
    int mind=INFINITY,mini=-1;
    for(int i=1;i<=n+m;i++)if(!collected[i]&&mind>dist[i])
        mind=dist[i],mini=i;
    if(mind<INFINITY)return mini;
    return -1;
}   */
/* 
    1087 All Roads Lead to Rome (30 分)
    Indeed there are many different tourist routes from our city to Rome. 
    You are supposed to find your clients the route with the least cost while gaining the most happiness.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains 2 positive integers N (2≤N≤200), the number of cities, 
    and K, the total number of routes between pairs of cities; followed by the name of the starting city. 
    The next N−1 lines each gives the name of a city and an integer that 
    represents the happiness one can gain from that city, except the starting city. 
    Then K lines follow, each describes a route between two cities in the format City1 City2 Cost. 
    Here the name of a city is a string of 3 capital English letters, 
    and the destination is always ROM which represents Rome.

    Output Specification:
    For each test case, we are supposed to find the route with the least cost. 
    If such a route is not unique, the one with the maximum happiness will be recommanded. 
    If such a route is still not unique, then we output the one with the maximum average happiness -- 
    it is guaranteed by the judge that such a solution exists and is unique.

    Hence in the first line of output, you must print 4 numbers: 
    the number of different routes with the least cost, the cost, the happiness, and the average happiness 
    (take the integer part only) of the recommanded route. 
    Then in the next line, you are supposed to print the route in the format City1->City2->...->ROM.

    Sample Input:           Sample Output:
    6 7 HZH                 3 3 195 97
    ROM 100                 HZH->PRS->ROM
    PKN 40
    GDN 55
    PRS 95
    BLN 80
    ROM GDN 1
    BLN ROM 1
    HZH PKN 1
    PRS ROM 2
    BLN HZH 2
    PKN GDN 1
    HZH PRS 1
    题意分析：
    在Dijkstra算法，上增加了相等时的两次特判及不同最短路径条数的计算
答案：(只通过两个测试点)
#include<iostream>
#include<stack>
#define INFINITY 65535
#define MaxCities 205
using namespace std;
typedef struct City{
    string name;
    int happiness;
}city;
city cities[MaxCities];
int G[MaxCities][MaxCities],cost[MaxCities],paths[MaxCities],
    num[MaxCities],happiness[MaxCities],path[MaxCities];
bool collected[MaxCities]={false};
void BuildGraph(int,int);
void LeadtoRome(int);
void Dijkstra(int,int);
int FindMindist(int);
int main(int argc,char*argv[]) {
    int n,k;
    string start;
    cin>>n>>k>>start;
    cities[n-1].name=start;
    BuildGraph(n,k);
    LeadtoRome(n);
}
void BuildGraph(int n,int k){
    string c1,c2;int d,i1,i2;
    for(int i=0;i<n-1;i++)cin>>cities[i].name>>cities[i].happiness;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(i!=j)G[i][j]=INFINITY;
    for(int i=0;i<k;i++){
        cin>>c1>>c2>>d;
        for(int j=0;j<n;j++)
            if(c1==cities[j].name)i1=j;
            else if(c2==cities[j].name)i2=j;
        G[i1][i2]=G[i2][i1]=d;
    }
}
void LeadtoRome(int n){
    stack<int> s;int ave=0,count=1,rom;
    Dijkstra(n,n-1);
    for(int i=0;i<n-1;i++)if(cities[i].name=="ROM")rom=i;
    for(int i=path[rom];i!=n-1;i=path[i],count++){
        s.push(i);
        ave+=happiness[i];
    }
    printf("%d %d %d %d\n",num[rom],cost[rom],happiness[rom],(ave+cities[rom].happiness)/count);
    cout<<cities[n-1].name<<"->";
    while(!s.empty()){
        cout<<cities[s.top()].name<<"->";
        s.pop();
    }
    cout<<"ROM"<<endl;
}
void Dijkstra(int n,int s){
    for(int i=0;i<n;i++){
        cost[i]=G[s][i],num[i]=1,happiness[i]=cities[i].happiness;
        if(cost[i]<INFINITY)path[i]=s,paths[i]=1;
        else path[i]=-1;
    }
    collected[s]=true,cost[s]=0,paths[s]=0;
    while(true){
        int v=FindMindist(n);
        collected[v]=true;
        if(v<0)break;
        for(int i=0;i<n;i++)if(!collected[i]&&G[v][i]<INFINITY){
                if(cost[i]>cost[v]+G[v][i])
                    cost[i]=cost[v]+G[v][i],num[i]=num[v],path[i]=v,
                    paths[i]=paths[v]+1,happiness[i]=happiness[v]+cities[i].happiness;
                else if(cost[i]==cost[v]+G[v][i]){
                    num[i]+=num[v];
                    if(happiness[i]<happiness[v]+cities[i].happiness)
                        happiness[i]=happiness[v]+cities[i].happiness,path[i]=v,paths[i]=paths[v]+1;
                    else if(happiness[i]==happiness[v]+cities[i].happiness&&
                    happiness[i]/paths[i]<(happiness[v]+cities[i].happiness)/(paths[v]+1))path[i]=v,paths[i]=paths[v]+1;
                }
        }
    }
}
int FindMindist(int n){
    int minc=INFINITY,mini=-1;
    for(int i=0;i<n;i++)if(!collected[i]&&minc>cost[i])
        minc=cost[i],mini=i;
    if(minc<INFINITY)return mini;
    else return -1;
}  */
/* 
    1131 Subway Map (30 分)
    In the big cities, the subway systems always look so complex to the visitors. 
    To give you some sense, the following figure shows the map of Beijing subway. 
    Now you are supposed to help people with your computer skills! 
    Given the starting position of your user, your task is to find the quickest way to his/her destination.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains a positive integer N (≤ 100), the number of subway lines. 
    Then N lines follow, with the i-th (i=1,⋯,N) line describes the i-th subway line in the format:

    M S[1] S[2] ... S[M]

    where M (≤ 100) is the number of stops, and S[i]'s (i=1,⋯,M) are the indices of the stations 
    (the indices are 4-digit numbers from 0000 to 9999) along the line. 
    It is guaranteed that the stations are given in the correct order -- that is, 
    the train travels between S[i] and S[i+1] (i=1,⋯,M−1) without any stop.

    Note: It is possible to have loops, 
    but not self-loop (no train starts from S and stops at S without passing through another station). 
    Each station interval belongs to a unique subway line. 
    Although the lines may cross each other at some stations (so called "transfer stations"), 
    no station can be the conjunction of more than 5 lines.

    After the description of the subway, another positive integer K (≤ 10) is given. 
    Then K lines follow, each gives a query from your user: 
    the two indices as the starting station and the destination, respectively.

    The following figure shows the sample map.

    Note: It is guaranteed that all the stations are reachable, 
    and all the queries consist of legal station numbers.

    Output Specification:
    For each query, first print in a line the minimum number of stops. 
    Then you are supposed to show the optimal path in a friendly format as the following:

    Take Line#X1 from S1 to S2.
    Take Line#X2 from S2 to S3.
    ......
    where Xi's are the line numbers and Si's are the station indices. 
    Note: Besides the starting and ending stations, only the transfer stations shall be printed.

    If the quickest path is not unique, output the one with the minimum number of transfers, 
    which is guaranteed to be unique.

    Sample Input:
    4
    7 1001 3212 1003 1204 1005 1306 7797
    9 9988 2333 1204 2006 2005 2004 2003 2302 2001
    13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011
    4 6666 8432 4011 1306
    3
    3011 3013
    6666 2001
    2004 3001
    Sample Output:
    2
    Take Line#3 from 3011 to 3013.
    10
    Take Line#4 from 6666 to 1306.
    Take Line#3 from 1306 to 2302.
    Take Line#2 from 2302 to 2001.
    6
    Take Line#2 from 2004 to 1204.
    Take Line#1 from 1204 to 1306.
    Take Line#3 from 1306 to 3001.
答案：
#include<iostream>
#include<unordered_map>
#include<vector>
#define INFINITY 65535
using namespace std;
unordered_map<int,int>lines;           //路线map
bool visited[10100];                   //记录站点是否访问过
vector<int>path,tempath;               //最终路径和每次dfs的备选路径
vector<vector<int>>v(10100);           //图
int mincnt,mintransfer,Start,End,n;    //最少途径站点数、最少换乘次数、起点、终点、路线条数
void buildgraph();
int transfercnt(vector<int>);          //该函数用于求解换乘次数，参数传入的值为备选路径tempath
void SubwayMap();
void dfs(int,int);
// DFS是一个递归函数，考虑递归边界和递归式，
// 递归边界就是到达起点，而递归式更新mincnt和mintransfer以及选择最优路径
// 用tempPath来存放最短的路径，在访问v顶点时就可以把该顶点加入到tempPath中，执行递归式
// 注意之前需要将起点也加入到tempPath中
int main(){
    cin>>n;
    buildgraph();
    SubwayMap();
    return 0;
}
void buildgraph(){
    int m,pre,temp;
    for(int i=0;i<n;i++){              //建图
        cin>>m>>pre;                   //输入每条路线的站点数m和第一个站点pre
        for(int j=1;j<m;j++){          //输入剩下的m-1个站点temp
            cin>>temp;
            v[pre].push_back(temp);    //将pre和temp之间相互增加一条边
            v[temp].push_back(pre);
            lines[pre*10000+temp]=lines[temp*10000+pre]=i+1;
            //记录路线，map第一个关键字前四位为第一个站点，后四位为第二个站点，第二个关键字代表第几条路线
            pre=temp;                  //将temp换为pre，从而将路线上的每两个站点之间增加一条边
        }
    }
}
void SubwayMap(){
    int k;
    cin>>k;                            //输入query个数
    for(int i=0;i<k;i++){
        cin>>Start>>End;               //输入每个query中的起点和终点
        mincnt=mintransfer=INFINITY;   //初始化mincnt和mintransfer
        tempath.clear();               //清空
        tempath.push_back(Start);      //先将起点压入tempath
        visited[Start]=true;           //将起点标记为已访问
        dfs(Start,0);                  //dfs求解最优路径
        visited[Start]=false;          //将起点重新标记为false，准备求解下一个query
        cout<<mincnt<<endl;            //输出最少途经站点
        int preline=0,pretransfer=Start;//定义两个变量用于输出当前路线和站点
        for(int j=1;j<path.size();j++)if(lines[path[j-1]*10000+path[j]]!=preline){
        //如果上一组路线与当前路线不同，按要求的格式输出
                if(preline)printf("Take Line#%d from %04d to %04d.\n",preline,pretransfer,path[j-1]);
                preline=lines[path[j-1]*10000+path[j]],pretransfer=path[j-1];
            }
        printf("Take Line#%d from %04d to %04d.\n",preline,pretransfer,End);//最后输出到终点的那一条边
    }
}
void dfs(int node,int cnt){
    if(node==End){
        if(cnt<mincnt||(cnt==mincnt&&transfercnt(tempath)<mintransfer))
            mincnt=cnt,mintransfer=transfercnt(tempath),path=tempath;
        return;
        //递归出口为node等于终点，同时更新mincnt和mintransfer，选出途径路径和换成次数最少的路径
    }
    for(int i:v[node])if(!visited[i]){//遍历图中未访问站点i，注意这里遍历的是图v的第一个下标
            visited[i]=true;          
            tempath.push_back(i);     //将i压入tempath
            dfs(i,cnt+1);             //递归，途经站点数cnt+1
            visited[i]=false;
            tempath.pop_back();       //递归结束后将站点重新设置为未访问，并弹出tempath，准备求解下一个query
    }
}
int transfercnt(vector<int>a){
//该函数用于求解换乘次数，a传入的值为备选路径tempath
    int cnt=-1,preline=0;             //换乘次数初始化为-1
    for(int i=1;i<a.size();i++){
        if(lines[a[i-1]*10000+a[i]]!=preline)cnt++;//每当tempath中相邻两个站点之间的路线与preline不等时换乘次数+1
        preline=lines[a[i-1]*10000+a[i]];//preline更新为上一组站点的路线
    }
    return cnt;                      //返回换乘次数
} */
/*
    1018 Public Bike Management
    There is a public bike service in Hangzhou City which provides great convenience to the tourists 
    from all over the world. 
    One may rent a bike at any station and return it to any other stations in the city.

    The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. 
    A station is said to be in perfect condition if it is exactly half-full. 
    If a station is full or empty, 
    PBMC will collect or send bikes to adjust the condition of that station to perfect. 
    And more, all the stations on the way will be adjusted as well.

    When a problem station is reported, PBMC will always choose the shortest path to reach that station. 
    If there are more than one shortest path, 
    the one that requires the least number of bikes sent from PBMC will be chosen.

    The above figure illustrates an example. 
    The stations are represented by vertices and the roads correspond to the edges. 
    The number on an edge is the time taken to reach one end station from another. 
    The number written inside a vertex S is the current number of bikes stored at S. 
    Given that the maximum capacity of each station is 10. To solve the problem at S3, 
    we have 2 different shortest paths:

    PBMC -> S1-> S3. 
    In this case, 4 bikes must be sent from PBMC, 
    because we can collect 1 bike from S1and then take 5 bikes to S3, 
    so that both stations will be in perfect conditions.

    PBMC -> S2-> S3. 
    This path requires the same time as path 1, 
    but only 3 bikes sent from PBMC and hence is the one that will be chosen.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains 4 numbers: Cmax(≤100), always an even number, 
    is the maximum capacity of each station; N (≤500), the total number of stations; 
    Sp, the index of the problem station 
    (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); 
    and M, the number of roads. 
    The second line contains N non-negative numbers Ci(i=1,⋯,N) 
    where each Ci is the current number of bikes at Si respectively. 
    Then M lines follow, each contains 3 numbers: 
    Si, Sj, and Tij
    ​
    which describe the time Tij taken to move betwen stations Si and Sj. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, print your results in one line. 
    First output the number of bikes that PBMC must send. 
    Then after one space, output the path in the format: 0−>S1−>⋯−>Sp. 
    Finally after another space, 
    output the number of bikes that we must take back to PBMC after the condition of Sp is adjusted to perfect.

    Note that if such a path is not unique, 
    output the one that requires minimum number of bikes that we must take back to PBMC. 
    The judge's data guarantee that such a path is unique.

    Sample Input:       Sample Output:
    10 3 3 5            3 0->2->3 0
    6 7 0
    0 1 1
    0 2 1
    0 3 3
    1 3 1
    2 3 1
    题意分析：求给定源点和终点之间的最短距离
            坑点1：三个标尺，标尺一为dist(源点和终点之间的时间花销最短)，标尺二和三分别为从pbmc发出和回收的自行车数量最少
            坑点2：发出和回收是按沿途站点依次进行的，因此路径上回收到的自行车只能补充后面的站点，不能补充前面的站点
            坑点3：最少发出和回收数量minsend和minback不符合最优子结构，不可以用dijkstra直接求解
                (即后一个结点的状态不可能由前面的结点推出，不是简单的线性相加关系)
                    因此本题考虑用dijkstra+dfs的方法求解，djkstra计算dist最短的路径，dfs选择minsend和minback
答案：
#include<iostream>
#include<stack>
#include<vector>
#include<cmath>
#define MaxVertexNum 550
#define INFINITY 65535
using namespace std;
int capacity,stations,pstation,roads,minsend,minback,
    G[MaxVertexNum][MaxVertexNum],dist[MaxVertexNum];
vector<int>pre[MaxVertexNum],path,tempath;
double station[MaxVertexNum];
bool collected[MaxVertexNum]={false};
void buildgraph();
void pbm();
void dijkstra(int);
void dfs(int);
int findmindist();
int main(int argc,char*argv[]){
    cin>>capacity>>stations>>pstation>>roads;
    buildgraph();
    pbm();
}
void buildgraph(){
    int s,e,t;
    for(int i=0;i<=stations;i++)for(int j=0;j<=stations;j++)if(i!=j)G[i][j]=INFINITY;
    for(int i=1;i<=stations;i++){
        cin>>station[i];
        station[i]-=capacity/2.0;
    }
    for(int i=0;i<roads;i++){
        cin>>s>>e>>t;
        G[s][e]=G[e][s]=t;
    }
}
void pbm(){
    minsend=minback=INFINITY;
    stack<int>stk;
    dijkstra(0);
    dfs(pstation);
    cout<<minsend<<' ';
    for(int i:path)stk.push(i);
    while(stk.size()>1){
        cout<<stk.top()<<"->";
        stk.pop();
    }
    cout<<pstation<<' '<<minback<<endl;
}
void dijkstra(int s){
    for(int i=0;i<=stations;i++){
        dist[i]=G[s][i];
        if((double)G[s][i]<INFINITY)pre[i].push_back(s);
    }
    dist[s]=0,collected[s]=true;
    while(true){
        int v=findmindist();
        if(v<0)break;
        collected[v]=true;
        for(int i=0;i<=stations;i++)if(!collected[i]&&(double)G[v][i]<INFINITY){
            if(dist[i]>dist[v]+G[v][i]){
                dist[i]=dist[v]+G[v][i];
                pre[i].clear(),pre[i].push_back(v);
            }else if(dist[i]==dist[v]+G[v][i])pre[i].push_back(v);
        }
    }
}
int findmindist(){
    int mind=INFINITY,mini=-1;
    for(int i=0;i<=pstation;i++)if(!collected[i]&&mind>dist[i])
        mind=dist[i],mini=i;
    if((double)mind<INFINITY)return mini;
    return -1;
}
void dfs(int node){
    tempath.push_back(node);
    if(node==0){
        int thisend=0,thisback=0;
        for(int i=(int)tempath.size()-1;i>=0;i--){
            int id=tempath[i];
            if(station[id]>0)thisback+=(int)station[id];
            else{
                if(thisback+station[id]>=0)thisback+=(int)station[id];
                else thisend-=(int)(thisback+station[id]),thisback=0;
            }
        }
        if(minsend>thisend||(minsend==thisend&&minback>thisback))
            minsend=thisend,minback=thisback,path=tempath;
        tempath.pop_back();
        return;
    }
    for(int i:pre[node])dfs(i);
    tempath.pop_back();
} */
