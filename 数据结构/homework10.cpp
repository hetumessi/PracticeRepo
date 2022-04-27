/*
    7-13 统计工龄 (20 point(s))
    给定公司N名员工的工龄，要求按工龄增序输出每个工龄段有多少员工。

    输入格式:
    输入首先给出正整数N（≤10^5），即员工总人数；随后给出N个整数，即每个员工的工龄，范围在[0, 50]。

    输出格式:
    按工龄的递增顺序输出每个工龄的员工个数，格式为：“工龄:人数”。每项占一行。如果人数为0则不输出该项。

    输入样例:            输出样例:
    8                   0:1
    10 2 0 5 7 2 5 2    2:3
                        5:2
                        7:1
                        10:1
答案：
#include<iostream>
#define maxages 55
using namespace std;
int n,age,ages[maxages];
void count();
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>age;
        ages[age]++;
    }
    for(int i=0;i<maxages;i++)if(ages[i])cout<<i<<':'<<ages[i]<<endl;
}   */
/*
    1075 PAT Judge (25 point(s))
    The ranklist of PAT is generated from the status list, 
    which shows the scores of the submissions. 
    This time you are supposed to generate the ranklist for PAT.

    Input Specification:
    Each input file contains one test case. 
    For each case, the first line contains 3 positive integers, N (≤10^4), 
    the total number of users, K (≤5), the total number of problems, and M (≤10^5), 
    the total number of submissions. 
    It is then assumed that the user id's are 5-digit numbers from 00001 to N, 
    and the problem id's are from 1 to K. 
    The next line contains K positive integers p[i] (i=1, ..., K), 
    where p[i] corresponds to the full mark of the i-th problem. 
    Then M lines follow, each gives the information of a submission in the following format:

    user_id problem_id partial_score_obtained
    where partial_score_obtained is either −1 if the submission cannot even pass the compiler, 
    or is an integer in the range [0, p[problem_id]]. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, you are supposed to output the ranklist in the following format:

    rank user_id total_score s[1] ... s[K]
    where rank is calculated according to the total_score, 
    and all the users with the same total_score obtain the same rank; 
    and s[i] is the partial score obtained for the i-th problem. 
    If a user has never submitted a solution for a problem, 
    then "-" must be printed at the corresponding position. 
    If a user has submitted several solutions to solve one problem, 
    then the highest score will be counted.

    The ranklist must be printed in non-decreasing order of the ranks. 
    For those who have the same rank, 
    users must be sorted in nonincreasing order according to the number of perfectly solved problems. 
    And if there is still a tie, then they must be printed in increasing order of their id's. 
    For those who has never submitted any solution that can pass the compiler, 
    or has never submitted any solution, they must NOT be shown on the ranklist. 
    It is guaranteed that at least one user can be shown on the ranklist.

    Sample Input:       Sample Output:
    7 4 20              1 00002 63 20 25 - 18
    20 25 25 30         2 00005 42 20 0 22 -
    00002 2 12          2 00007 42 - 25 - 17
    00007 4 17          2 00001 42 18 18 4 2
    00005 1 19          5 00004 40 15 0 25 -
    00007 2 25
    00005 1 20
    00002 2 2
    00005 1 15
    00001 1 18
    00004 3 25
    00002 2 25
    00005 3 22
    00006 4 -1
    00001 2 18
    00002 1 20
    00004 1 15
    00002 4 18
    00001 3 4
    00001 4 2
    00005 2 -1
    00004 2 0
    此题坑点：
    1.提交不通过编译的得分是-1，但最后输出时显示是0分，只有完全没做过的题显示'-'
    2.一个人只有提交过通过了编译的答案(最低分0分)才能在榜单上显示
    3.如果一个人对同一题多次提交过满分，该题满分次数只算一次
    4.榜单排序规则是
        *第一关键字是总得分，总得分相同的排名相同
        *相同总得分虽然排名相同，但仍然存在先后顺序
            *第二关键字是题目满分个数
            *第三关键字是id顺序
答案：(误，最后两个测试点段错误)
#include<iostream>
#include<cstdlib>
#define marks 5
#define users 1050
#define missioins 10050
using namespace std;
typedef struct input{
    int id,prob,mark;
}input;
typedef struct output{
    int id,tol,perf;
}output;
input inputs[missioins];
output outputs[users];
int n,m,k,fullmark[marks],compare(const void*,const void*),ranks[users][marks+4];
void patjudge();
int main(){
    cin>>n>>k>>m;
    for(int i=0;i<k;i++)cin>>fullmark[i];
    for(int i=0;i<m;i++)cin>>inputs[i].id>>inputs[i].prob>>inputs[i].mark;
    patjudge();
}
int compare(const void*node1,const void*node2){
    int comp=-1;
    if(((output*)node1)->tol<((output*)node2)->tol)comp=1;
    else if(((output*)node1)->tol==((output*)node2)->tol){
        if(((output*)node1)->perf<((output*)node2)->perf)comp=1;
        else if(((output*)node1)->perf==((output*)node2)->perf)
            if(((output*)node1)->id>((output*)node2)->id)comp=1;
    }
    return comp;
}
void patjudge(){
    for(int i=0;i<n;i++)for(int j=1;j<k+1;j++)ranks[i][j]=-2;
    for(int i=0,l=0,j;i<m;i++){
        int flag=0;
        for(j=0;j<=l;j++)if(ranks[j][0]==inputs[i].id){
            if(inputs[i].mark>ranks[j][inputs[i].prob]){
                if(inputs[i].mark>=0)ranks[j][k+3]=1;
                if(inputs[i].mark==fullmark[inputs[i].prob-1])ranks[j][k+1]++;
                ranks[j][inputs[i].prob]=inputs[i].mark;
            }
            flag=1;
        }
        if(!flag){
            ranks[l][0]=inputs[i].id;
            if(inputs[i].mark>=0)ranks[l][k+3]=1;
            if(inputs[i].mark==fullmark[inputs[i].prob-1])ranks[l][k+1]++;
            ranks[l++][inputs[i].prob]=inputs[i].mark;
        }
    }
    for(int i=0;i<n;i++)for(int j=1;j<=k;j++){
        if(ranks[i][j]>0)ranks[i][k+2]+=ranks[i][j];
        else if(ranks[i][j]==-1)ranks[i][j]=0;
    }
    for(int i=0;i<n;i++)outputs[i].id=ranks[i][0],outputs[i].tol=ranks[i][k+2],outputs[i].perf=ranks[i][k+1];
    qsort(outputs,n,sizeof(output),compare);
    int nums=0;
    for(int i=0;i<n;i++)if(ranks[i][k+3]==1)nums++;
    for(int i=0,num=1;i<nums;i++){
        if(i>0&&outputs[i].tol<outputs[i-1].tol)num=i+1;
        cout<<num<<' ';
        printf("%05d ",outputs[i].id);
        cout<<outputs[i].tol<<' ';
        for(int j=0;j<n;j++)if(ranks[j][0]==outputs[i].id){
            for(int l=1;l<k;l++){
                if(ranks[j][l]>=0)cout<<ranks[j][l]<<' ';
                else cout<<"- ";
            }
            if(ranks[j][k]>=0)cout<<ranks[j][k]<<endl;
            else cout<<'-'<<endl;
        }
    }
} */
/*
    1067 Sort with Swap(0, i) (25 point(s))
    Given any permutation of the numbers {0, 1, 2,..., N−1}, 
    it is easy to sort them in increasing order. But what if Swap(0, *) is the ONLY operation 
    that is allowed to use? 
    For example, to sort {4, 0, 2, 1, 3} we may apply the swap operations in the following way:

    Swap(0, 1) => {4, 1, 2, 0, 3}
    Swap(0, 3) => {4, 1, 2, 3, 0}
    Swap(0, 4) => {0, 1, 2, 3, 4}
    Now you are asked to find the minimum number of swaps need to sort 
    the given permutation of the first N nonnegative integers.

    Input Specification:
    Each input file contains one test case, which gives a positive N (≤10^5) 
    followed by a permutation sequence of {0, 1, ..., N−1}. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each case, simply print in a line the minimum number of swaps need to sort the given permutation.

    Sample Input:           Sample Output:
    10                      9
    3 5 7 2 6 4 9 0 8 1
    分析：
    表排序的物理排序(将序列分为环，根据环数计算交换次数)
    1.在计算环时，要将已经纳入某个环中的数记录下来。如果每次都重复计算的话可能会超时
    2.环的分类
        *序列中只有单元环(没有多元环，此时每个数都已经在自己的位置上，不需要交换)
        *序列中只有一个多元环(0一定在这个多元环中，此时只需计算环内的交换次数即可，不需要与别的环进行交换)
            *此时总交换次数=多元环内交换次数=多元环元素个数-1
                *多元环元素个数=n-单元环元素个数，因此总交换次数=n-single-1
        *序列中存在多个多元环，此时要先将0与其他多元环元素进行一次交换，相当于把多个多元环组合为一个大的多元环
            *多元环间交换次数=多元环个数-1
            *此时总交换次数=多元环间交换次数+大多元环元素交换次数=多元环个数-1+多元环元素个数-1
                *总交换次数=n-single-multiple-2
    3.0在第0个位置的时候，由于本题只能换0，所以必须将0换到其他的多元环中，此时0本身实际相当于一个多元环(multiple++)
        *存在一种特殊情况：序列没有其他多元环，此时不需要交换，0也不需要看作多元环
答案：
#include<iostream>
#define maxcount 105000
using namespace std;
int n,table[maxcount],flag[maxcount],swap0andi();
void swap(int*,int*);
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>table[i];
    cout<<swap0andi()<<endl;
}
void swap(int*num1,int*num2){
    int tmp=*num1;
    *num1=*num2,*num2=tmp;
}
int swap0andi(){
    int right=0,tmp,circle=0;
    for(int i=1;i<n;i++)if(table[i]==i)flag[i]=1,right++;
    if(!table[0]&&right<n-1){
        for(tmp=1;tmp<n&&flag[tmp];tmp++);
        swap(table[0],table[tmp]);
        circle++;
    }
    for(int i=0;i<n;i++)if(!flag[i]){
        tmp=i,flag[tmp]=1;
        for(int j=table[tmp];j!=tmp;j=table[j])flag[j]=1;
        circle++;
    }
    if(circle==0)return 0;
    else if(circle==1)return n-right-1;
    else return n-right+circle-2;
}   
*/