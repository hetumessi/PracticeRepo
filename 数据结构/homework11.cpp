/*
    7-14 电话聊天狂人 (25 point(s))
    给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

    输入格式:
    输入首先给出正整数N(≤10^5)，为通话记录条数。随后N行，每行给出一条通话记录。
    简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

    输出格式:
    在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。
    如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

    输入样例:                   输出样例:
    4                          13588625832 3
    13005711862 13588625832
    13505711862 13088625832
    13588625832 18087925832
    15005713862 13588625832
    分析：
    解法1-排序
        *第1步：读入最多2*10^5个电话号码，每个号码存为长度为11的字符串
        *第2步：按字符串非递减顺序排序
        *第3步：扫描有序数组，累计同号码出现的次数，并且更新最大次数
        *此方法编程快捷简单，但无法扩展解决动态插入的问题
    解法2-直接映射
        *第1步：创建有2*10^10个单元的整数数组，保证每个电话号码对应唯一的单元下标：数组初始化为0
        *第2步：对读入的每个电话号码，找到以之为下标的单元，数值累计1次
        *第3步：顺序扫描数组，找出累计次数最多的单元
        *此方法编程简单快捷，动态插入快
        *但下标范围已经超过了unsigned long，需要2*10^10*2bytes≈37GB，为了2*10^5个号码扫描2*10^10个单元
    解法3-带“智商“的散列
        *分离链接法
        *将最后5位用于散列

    程序框架
    int main(){
        创建散列表;
        读入号码插入表中;
        扫描表输出狂人;
        return 0;
    }
    HashTable的定义 ——> NextPrime ——> CreateTable 
    Hash,Find ——> Insert
    扫描整个散列表：更新最大通话次数、更新最小号码+统计人数

    int main(){
        int N,i;
        ElementType key;
        HashTable H;
        scanf("%d",&N);
        H=CreateTable(N*2);     //创建一个散列表
        for(i=0;i<N;i++){
            scanf("%s",key);Insert(H,Key);
            scanf("%s",key);Insert(H,Key);
        }
        ScanAndOutput(H);
        DestroyTable(H);
        return 0;
    }

    输出狂人
    void ScanAndOutput(HashTable H){
        int i,MaxCnt=PCnt=0;
        ElementType MinPhone;
        List Ptr;
        MinPhone[0]='\0';
        for(i=0;i<H->TableSizel;i++){                //扫描链表
            Ptr=H->Heads[i].Next;
            while(Ptr){
                if(Ptr->Count>MaxCnt){               //更新最大通话次数
                    MaxCnt=Ptr->Count;
                    strcpy(MinPhone,Ptr->Data);
                    PCnt=1;
                }
                else if(Ptr->Count==MaxCnt){
                    PCnt++;                          //狂人计数
                    if(strcmp(MinPhone,Ptr->Data)>0)
                        strcpy(MinPhone,Ptr->Data);  //更新狂人的最小手机号码
                }
                Ptr=Ptr->Next;
            }
        }
        printf("%s %d",MinPhone,MaxCnt);
        if(PCnt>1)printf(" %d",PCnt);
        printf("\n");
    }

    HashTable的定义(引用6.3.1和6.3.2示例程序，对模块进行裁剪和加工)
    typedef struct LNode *PtrToLNode;
    struct LNode {
        ElementType Data;
        PtrToLNode Next;
        int Count;(新增)
    };
    typedef PtrToLNode Position;
    typedef PtrToLNode List;
    
    #define MAXTABLESIZE 1000000
    int Hash(int Key,int P){            //除留余数法散列函数
        return Key%P;
    }
    int NextPrime( int N )
    { // 返回大于N且不超过MAXTABLESIZE的最小素数 
        int i, p = (N%2)? N+2 : N+1; //从大于N的下一个奇数开始 

        while( p <= MAXTABLESIZE ) {
            for( i=(int)sqrt(p); i>2; i-- )
                if ( !(p%i) ) break; // p不是素数 
            if ( i==2 ) break; // for正常结束，说明p是素数 
            else  p += 2; // 否则试探下一个奇数 
        }
        return p;
    }
    HashTable CreateTable( int TableSize )
    {
        HashTable H;
        int i;
        H = (HashTable)malloc(sizeof(struct TblNode));
        H->TableSize = NextPrime(TableSize);
        H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
        for( i=0; i<H->TableSize; i++ ) {
            H->Heads[i].Data[0] = '\0';
            H->Heads[i].Next = NULL;
            H->Heads[i].Count=0;(新增)
        }
        return H;
    }
    Position Find( HashTable H, ElementType Key )
    {
        Position P;
        Index Pos;
        
        Pos = Hash( atoi(Key+KEYLENGTH-MAXD), H->TableSize );(修改)
        P = H->Heads[Pos].Next; // 从该链表的第1个结点开始 
        // 当未到表尾，并且Key未找到时 
        while( P && strcmp(P->Data, Key) )
            P = P->Next;

        return P; // 此时P或者指向找到的结点，或者为NULL 
    }
    bool Insert( HashTable H, ElementType Key )
    {
        Position P, NewCell;
        Index Pos;
        
        P = Find( H, Key );
        if ( !P ) { // 关键词未找到，可以插入 
            NewCell = (Position)malloc(sizeof(struct LNode));
            strcpy(NewCell->Data, Key);
            NewCell->Count=1;(新增)
            Pos=Hash(atoi(Key+KEYLENGTH-MAXD),H->TableSize);(修改)
            // 将NewCell插入为H->Heads[Pos]链表的第1个结点 
            NewCell->Next = H->Heads[Pos].Next;
            H->Heads[Pos].Next = NewCell; 
            return true;
        }
        else { // 关键词已存在 
            printf("键值已存在");
            return false;
        }
    }

答案：(map的应用！)
#include<iostream>
#include<map>
#include<string>
using namespace std;
map<string,int>id;
string num1,num2,minphn;
int n,maxc,countc;
void crazyman();
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>num1>>num2;
        id[num1]++,id[num2]++;
    }
    crazyman();
}
void crazyman(){
    for(auto i:id){
        if(i.second>maxc)maxc=i.second,minphn=i.first,countc=1;
        else if(i.second==maxc)countc++;
    }
    cout<<minphn<<' '<<maxc;
    if(countc>1)cout<<' '<<countc;
    cout<<endl;
} */
/*
    1078 Hashing (25 point(s))
    The task of this problem is simple: 
    insert a sequence of distinct positive integers into a hash table, 
    and output the positions of the input numbers. 
    The hash function is defined to be H(key)=key%TSize where TSize is the maximum size of the hash table. 
    Quadratic probing (with positive increments only) is used to solve the collisions.

    Note that the table size is better to be prime. If the maximum size given by the user is not prime, 
    you must re-define the table size to be the smallest prime number 
    which is larger than the size given by the user.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains two positive numbers: MSize (≤10^4) and N (≤MSize) 
    which are the user-defined table size and the number of input numbers, respectively. 
    Then N distinct positive integers are given in the next line. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line. 
    All the numbers in a line are separated by a space, 
    and there must be no extra space at the end of the line. 
    In case it is impossible to insert the number, print "-" instead.
答案：(完全不懂这题为啥这样做)
#include<iostream>
#include<cmath>
#define MSIZE 10050
using namespace std;
int msize,n,num,htable[MSIZE];
void insert(int);
bool isprime(int);
int main(){
    cin>>msize>>n;
    while(!isprime(msize))msize++;
    for(int i=0;i<n;i++){
        cin>>num;
        insert(num);
        if(i<n-1)cout<<' ';
    }
    cout<<endl;
}
bool isprime(int m){
    int i;
    if(m==1)return false;
    for(i=sqrt(m);i>1;i--)if(!(m%i))return false;
    return true;
}
void insert(int key){
    for(int d=0;d<msize;d++){
        int pos=(key+d*d)%msize;
        if(!htable[pos]){
            htable[pos]=key;
            cout<<pos;
            return;
        }
    }
    cout<<'-';
} */
/*
    QQ帐户的申请与登陆 (25 point(s))
    实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。

    输入格式:
    输入首先给出一个正整数N（≤10^5），随后给出N行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。
    其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表Login）时表示是老帐户登陆，
    后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。
    密码为不小于6位、不超过16位、且不包含空格的字符串。

    输出格式:
    针对每条指令，给出相应的信息：

    1）若新申请帐户成功，则输出“New: OK”；
    2）若新申请的号码已经存在，则输出“ERROR: Exist”；
    3）若老帐户登陆成功，则输出“Login: OK”；
    4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
    5）若老帐户密码错误，则输出“ERROR: Wrong PW”。

    输入样例:                       输出样例:
    5                              ERROR: Not Exist
    L 1234567890 myQQ@qq.com       New: OK
    N 1234567890 myQQ@qq.com       ERROR: Exist
    N 1234567890 myQQ@qq.com       ERROR: Wrong PW
    L 1234567890 myQQ@qq           Login: OK
    L 1234567890 myQQ@qq.com
答案：(还是map)
#include<iostream>
#include<map>
#include<string>
#define digitn 100500
using namespace std;
int n;
char command;
string id,pw;
map<string,string>qq;
void judgeqq(char,const string&,const string&),insert(string,string);
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>command>>id>>pw;
        judgeqq(command,id,pw);
    }
}
void judgeqq(char cd,const string&idstr,const string&pwstr){
    if(cd=='N'){
        if(qq.find(idstr)!=qq.end())cout<<"ERROR: Exist"<<endl;
        else{
            qq[idstr]=pwstr;
            cout<<"New: OK"<<endl;
        }
    }else if(cd=='L'){
        if(qq.find(idstr)==qq.end())cout<<"ERROR: Not Exist"<<endl;
        else if(qq[idstr]!=pwstr)cout<<"ERROR: Wrong PW"<<endl;
        else cout<<"Login: OK"<<endl;
    }
} */
/*
    Hashing - Hard Version (30 point(s))
    Given a hash table of size N, we can define a hash function H(x)=x%N. 
    Suppose that the linear probing is used to solve collisions, 
    we can easily obtain the status of the hash table with a given sequence of input numbers.

    However, now you are asked to solve the reversed problem: 
    reconstruct the input sequence from the given status of the hash table. 
    Whenever there are multiple choices, the smallest number is always taken.

    Input Specification:
    Each input file contains one test case. For each test case,
    the first line contains a positive integer N (≤1000), 
    which is the size of the hash table. The next line contains N integers, 
    separated by a space. A negative integer represents an empty cell in the hash table. 
    It is guaranteed that all the non-negative integers are distinct in the table.

    Output Specification:
    For each test case, print a line that contains the input sequence, 
    with the numbers separated by a space. Notice that there must be no extra space at the end of each line.

    Sample Input:                       Sample Output:
    11                                  1 13 12 21 33 34 38 27 22 32
    33 1 13 12 34 38 27 22 32 -1 21

    分析：
        *已知H(x)=x%N以及用线性探测解决冲突问题
        *先给出散列映射的结果，反求输入顺序
            *当元素x被映射到H(x)位置，发现这个位置已经有y了，则y一定是在x之前被输入的
            *————————>拓扑排序!!!
            
答案：
#include<iostream>
#include<cstdlib>
#include<stack>
#define range 1050
using namespace std;
int n,num,htable[range],temp[range],output[range],myhash(int),cmp(const void*,const void*);
stack<int>s1,s2;
void insert(int),hashing();
bool find(int);
int main(){
    cin>>n;
    int i,j;
    for(i=0,j=0;i<n;i++){
        cin>>num;
        htable[i]=num;
        if(num>0)output[j++]=num;
    }
    qsort(output,j,sizeof(int),cmp);
    for(i=j-1;i>=0;i--)s1.push(output[i]);
    hashing();
}
int cmp(const void*num1,const void*num2){
    return *(int*)num1-*(int*)num2;
}
int myhash(int key){
    return key%n;
}
bool find(int key){
    int pos=myhash(key);
    while(temp[pos]&&temp[pos]!=key)++pos%=n;
    if(key==htable[pos]){
        temp[pos]=key;
        return true;
    }
    return false;
}
void hashing(){
    int i=0;
    while(!s1.empty()){
        while(!find(s1.top()))s2.push(s1.top()),s1.pop();
        output[i++]=s1.top(),s1.pop();
        while(!s2.empty())s1.push(s2.top()),s2.pop();
    }
    for(int j=0;j<i-1;j++)cout<<output[j]<<' ';
    cout<<output[i-1]<<endl;
}  */
        
        
        
        