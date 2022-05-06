/*
    02-线性结构1 两个有序链表序列的合并 
    本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。

    函数接口定义：
    List Merge( List L1, List L2 );
    其中List结构定义如下：

    typedef struct Node *PtrToNode;
    struct Node {
        ElementType Data; // 存储结点数据 
        PtrToNode   Next; // 指向下一个结点的指针 
    };
    typedef PtrToNode List; // 定义单链表类型 
    L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。
    应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。 //本体关键：直接使用原序列中的结点！！！

    裁判测试程序样例：
    #include <stdio.h>
    #include <stdlib.h>

    typedef int ElementType;
    typedef struct Node *PtrToNode;
    struct Node {
        ElementType Data;
        PtrToNode   Next;
    };
    typedef PtrToNode List;

    List Read(); // 细节在此不表 
    void Print( List L ); // 细节在此不表；空链表将输出NULL 

    List Merge( List L1, List L2 );

    int main()
    {
        List L1, L2, L;
        L1 = Read();
        L2 = Read();
        L = Merge(L1, L2);
        Print(L);
        Print(L1);
        Print(L2);
        return 0;
    }

    // 你的代码将被嵌在这里 
    输入样例：
    3
    1 3 5
    5
    2 4 6 8 10
    输出样例：
    1 2 3 4 5 6 8 10 
    NULL        //输出NULL是因为L1和L2的结点都指向了L中的结点
    NULL    
答案：
List Merge(List L1, List L2)
{
	List pa, pb, pc;
	List L = (List)malloc(sizeof(struct Node));
	pa = L1->Next;
    pb = L2->Next;
    pc = L;
	while (pa && pb)
	{
		if (pa->Data <= pb->Data){
            pc->Next = pa;
            pc = pa;
            pa = pa->Next;
        }else{
            pc->Next = pb;
            pc = pb;
            pb = pb->Next;
        }
	}
	pc->Next = pa ? pa : pb;  //如果pa不为空，pc->Next = pa，否则pc->Next = pb
	L1->Next = NULL;
    L2->Next = NULL;
	return L;
}
*/
/* 
    02-线性结构3 Reversing Linked List (25 分)
    Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. 
    For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4;
     if K=4, you must output 4→3→2→1→5→6.

    Input Specification:
    Each input file contains one test case. For each case, 
    the first line contains the address of the first node, a positive N (≤10​^5) which is the total number of nodes, 
    and a positive K (≤N) which is the length of the sublist to be reversed. 
    The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

    Then N lines follow, each describes a node in the format:

    Address Data Next
    where Address is the position of the node, Data is an integer, and Next is the position of the next node.

    Output Specification:
    For each case, output the resulting ordered linked list. 
    Each node occupies a line, and is printed in the same format as in the input.

    Sample Input:
    00100 6 4
    00000 4 99999
    00100 1 12309
    68237 6 -1
    33218 3 00000
    99999 5 68237
    12309 2 33218
    Sample Output:
    00000 4 33218
    33218 3 12309
    12309 2 00100
    00100 1 99999
    99999 5 68237
    68237 6 -1
答案：
    自己构造一个memory数组来当做内存，然后基本操作就和链表的操作一样的。
    注意“有多余结点不在链表上”(即该结点是孤立的，并没有被其他结点指向)
#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAXSIZE 100000
using namespace std;
struct Lnode{
    int next;
    int data;
}node[MAXSIZE];
struct Snode{
    int add;
    int next;
    int data;
}snode[MAXSIZE];
void reverselink(){
    int i,j,a,n,k,Addr,Data,Next,nodeaddr;
    struct Snode tmp[MAXSIZE];
    cin>>a>>n>>k;
    for(i=0;i<n;i++){
        cin >> Addr >> Data >> Next;
        node[Addr].data=Data;
        node[Addr].next=Next;
    }
    nodeaddr=a;
    for(i=0,j=0;nodeaddr!=-1;i++,j++){
        tmp[i].data=node[nodeaddr].data;
        tmp[i].add=nodeaddr;
        nodeaddr=node[nodeaddr].next;
    }
    int tmpn=j;
    for(i=0;tmpn/k>0;tmpn-=k,i++)reverse(tmp+i*k,tmp+k*(i+1));
    for(i=0;i<j-1;i++)tmp[i].next=tmp[i+1].add;
    tmp[i].next=-1;
    for(i=0;i<j;i++){
        printf("%05d %d ",tmp[i].add,tmp[i].data);
        if(tmp[i].next!=-1)printf("%05d\n",tmp[i].next);
        else printf("-1");
    }
}
*/
/*
    02-线性结构4 Pop Sequence (25 分)
    Given a stack which can keep M numbers at most. Push N numbers in the order of 
    1, 2, 3, ..., N and pop randomly.
    You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. 
    For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, 
    but not 3, 2, 1, 7, 5, 6, 4.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains 3 numbers (all no more than 1000):
    M (the maximum capacity of the stack), N (the length of push sequence), 
    and K (the number of pop sequences to be checked). Then K lines follow, 
    each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

    Output Specification:
    For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

    Sample Input:
    5 7 5
    1 2 3 4 5 6 7
    3 2 1 7 5 6 4
    7 6 5 4 3 2 1
    5 6 4 3 7 2 1
    1 7 6 5 4 3 2
    Sample Output:
    YES
    NO
    NO
    YES
    NO
答案：
#include <iostream>
using namespace std;
void popsequence(){
    enum answer{NO,YES};
    int i,j,l,c,m,n,k,pos,count;
    cin>>m>>n>>k;
    int inputseq[k][n],countseq[n];
    for(i=0;i<k;i++)for(j=0;j<n;j++)cin>>inputseq[i][j];
    for(i=0;i<k;i++){
        pos=YES;
        for(j=0;j<n;j++){
            for(l=0;l<n;l++)countseq[l]=0;
            count=0;
            for(l=j+1;l<n;l++) {
                if (inputseq[i][j] > inputseq[i][l])countseq[count++]=inputseq[i][l];
                if (count >= m)pos = NO;
                for(c=0;c<count;c++)if(countseq[c+1]>countseq[c])pos = NO;
            }
        }
        if(pos==YES)cout<<"YES"<<endl;
        if(pos==NO)cout<<"NO"<<endl;
    }
}
*/
