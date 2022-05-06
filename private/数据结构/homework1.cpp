/* 二分查找 伪代码与实现
    伪代码：
    int binarysearch(int i,int array[],int up,int bottom){
    int Mid = (up + bottom) / 2;
    if      下界超过上界时，说明没有找到，返回错误状态-1
    else if x比中间位置的数字大，则以M为新bottom值重新查找，递归调用 binarysearch(i,array,mid-1,bottom)
    else if x比中间位置的数字小，则以M为新up重新查找，递归调用 binarysearch(i,array,up,mid+1)
    else if x与中间位置的数字相等，则返回数字位置 Mid+1
}

int binarysearch(int i,int array[],int up,int bottom)
{
    int mid;
    mid=(up+bottom)/2;
    if(up<bottom)return -1;
    else if(i==array[mid])return mid+1;
    if(i<array[mid])return binarysearch(i,array,mid-1,bottom);
    else if(i>array[mid])return binarysearch(i,array,up,mid+1);
    return 0;
}
*/
/*
    01-复杂度3 二分查找     
    本题要求实现二分查找算法。
    函数接口定义：
    Position BinarySearch( List L, ElementType X );
    其中List结构定义如下：
    typedef int Position;
    typedef struct LNode *List;
    struct LNode {
        ElementType Data[MAXSIZE];
        Position Last; // 保存线性表中最后一个元素的位置 
    };
    L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。
    函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。
    找到则返回下标，否则返回一个特殊的失败标记NotFound。

    裁判测试程序样例：
    #include <stdio.h>
    #include <stdlib.h>

    #define MAXSIZE 10
    #define NotFound 0
    typedef int ElementType;

    typedef int Position;
    typedef struct LNode *List;
    struct LNode {
        ElementType Data[MAXSIZE];
        Position Last; // 保存线性表中最后一个元素的位置 
    };

    List ReadInput(); // 裁判实现，细节不表。元素从下标1开始存储 
    Position BinarySearch( List L, ElementType X );

    int main()
    {
        List L;
        ElementType X;
        Position P;

        L = ReadInput();
        scanf("%d", &X);
        P = BinarySearch( L, X );
        printf("%d\n", P);

        return 0;
    }
    // 你的代码将被嵌在这里 
    输入样例1：
    5
    12 31 55 89 101
    31
    输出样例1：
    2
    输入样例2：
    3
    26 78 233
    31
    输出样例2：
    0
答案：
    Position BinarySearch( List L, ElementType X ){
        Position mid,start=1,end=L->Last;
        while(start<=end){
            mid=(start+end)/2;
            if(X>L->Data[mid])start=mid+1;
            if(X<L->Data[mid])end=mid-1;
            if(X==L->Data[mid])return mid;
        }
        return NotFound;
    }
*/
/*  
    01-复杂度2 Maximum Subsequence Sum 
    Given a sequence of K integers { N1, N2, ..., NK}. A continuous subsequence is defined to be 
    { Ni, Ni+1, ..., Nj} where 1≤i≤j≤K. 
    The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. 
    For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } 
    with the largest sum being 20.
    Now you are supposed to find the largest sum, 
    together with the first and the last numbers of the maximum subsequence.

    Input Specification:
    Each input file contains one test case. Each case occupies two lines. 
    The first line contains a positive integer K (≤10000). 
    The second line contains K numbers, separated by a space.

    Output Specification:
    For each test case, output in one line the largest sum, 
    together with the first and the last numbers of the maximum subsequence. 
    The numbers must be separated by one space, but there must be no extra space at the end of a line. 
    In case that the maximum subsequence is not unique, 
    output the one with the smallest indices i and j (as shown by the sample case). 
    If all the K numbers are negative, then its maximum sum is defined to be 0, 
    and you are supposed to output the first and the last numbers of the whole sequence.

    Sample Input:
    10
    -10 1 2 3 4 -5 -23 3 7 -21
    Sample Output:
    10 1 4
答案：(别人的)
    #include<bits/stdc++.h>
    using namespace std;
    int main()
    {
        int k,x,maxSum=-1,sum=0,s=0,st=0,e;
        cin>>k;
        for(int i=0;i<k;i++)
        {
            cin>>x;
            if(!i)s=x;
            if(sum<0||!i)
            {
                sum=0;
                st=x;
            }
            sum+=x;
            if(sum>maxSum)
            {
                maxSum=sum;
                s=st;
                e=x;
            }
        }
        if(maxSum<0)
        {
            maxSum=0;
            e=x;
        }
        cout<<maxSum<<' '<<s<<' '<<e;
        return 0;
    }
*/