/*
    09-排序1 排序 (25 分)
    给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。
    本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：
    数据1：只有1个元素；
    数据2：11个不相同的整数，测试基本正确性；
    数据3：103个随机整数；
    数据4：104个随机整数；
    数据5：105个随机整数；
    数据6：105个顺序整数；
    数据7：105个逆序整数；
    数据8：105个基本有序的整数；
    数据9：105个随机正整数，每个数字不超过1000。
    输入格式:
    输入第一行给出正整数N（≤10^5），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。
    输出格式:
    在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。
    输入样例:                           输出样例:
    11                                 -20 -17 -5 0 4 8 10 29 43 50 981
    4 981 10 -17 0 -20 29 50 8 43 -5

答案：
#include<iostream>
#define maxnum 10050
using namespace std;
int n;
long a[maxnum];
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    mysort(0,n-1);
    for(int i=0;i<n-1;i++)cout<<a[i]<<' ';
    cout<<a[n-1];
}
//冒泡排序
void mysort(int start,int end){                 
    for(int i=end-start;i>0;i--){
        int flag=0;
        for(int j=0;j<i;j++){
            long tmp=a[j];
            if(a[j]>a[j+1]){
                a[j]=a[j+1],a[j+1]=tmp;
                flag=1;
            }
        }
        if(!flag)break;
    }
}
//插入排序
void mysort(int start,int end){
    for(int i=1;i<=end-start;i++){
        int j;
        long tmp=a[i];
        for(j=i;j>0&&a[j-1]>tmp;j--)a[j]=a[j-1];
        a[j]=tmp;
    }
}
//希尔排序
void mysort(int start,int end){      //希尔排序：基于原始增量序列版本
    for(int length=(end+start)/2;length>0;length/=2){
        for(int i=1;i<n;i++){
            int j;
            long tmp=a[i];
            for(j=i;j>=length&&a[j-length]>tmp;j-=length)a[j]=a[j-length];
            a[j]=tmp;
        }
    }
}
void mysort(int start,int end){      //希尔排序：基于Sedgewick增量序列版本
    int Sedgewick[]={929,505,209,109,41,19,5,1,0};
    for(int l=0;Sedgewick[l]>end-start;length=Sedgewick[l++]);
    for(int length=Sedgewick[l];length>0;l++){
        for(int i=1;i<n;i++){
            int j;
            long tmp=a[i];
            for(j=i;j>=length&&a[j-length]>tmp;j-=length)a[j]=a[j-length];
            a[j]=tmp;
        }
    }
}
//堆排序
void percdown(int root,int size){
    long tmp=a[root];
    int parent,child;
    for(parent=root;parent*2+1<size;parent=child){
        child=parent*2+1;
        if(child<size-1&&a[child]<a[child+1])child++;
        if(tmp>=a[child])break;
        else a[parent]=a[child];
    }
    a[parent]=tmp;
}
void mysort(int start,int end){
    for(int i=(end-start+1)/2;i>=0;i--)percdown(i,end-start+1);
    for(int i=end-start;i>0;i--){
        long tmp=a[0];
        a[0]=a[i],a[i]=tmp;
        percdown(0,i);
    }
}
//归并排序
long tmpa[maxnum];
void merge(long*a,long*tmpa,int start,int end,int center){ //归并子列
    int start1=start,end1=center,start2=center+1,end2=end,tmp=start;
    while(start1<=end1&&start2<=end2){
        if(a[start1]<=a[start2])tmpa[tmp++]=a[start1++];
        else tmpa[tmp++]=a[start2++];
    }
    while(start1<=end1)tmpa[tmp++]=a[start1++];
    while(start2<=end2)tmpa[tmp++]=a[start2++];
    for(int i=start;i<=end;i++)a[i]=tmpa[i];
}
void mysort(int start,int end){     //归并排序：递归版本
    if(start>=end)return;
    int center=(start+end)/2;
    mysort(start,center);
    mysort(center+1,end);
    merge(a,tmpa,start,end,center);
}
void mysort(int start,int end){     //归并排序：非递归版本
    int length=1;
    while(length<=end-start){
        int i;
        for(i=0;i<=n-length*2;i+=length*2)merge(a,tmpa,i,i+length*2-1,i+length-1);
        if(i+length<=n)merge(a,tmpa,i,n-1,i+length-1);
        else for(int j=i;j<n;j++)tmpa[j]=a[j];
        length*=2;
        for(i=0;i<=n-length*2;i+=length*2)merge(tmpa,a,i,i+length*2-1,i+length-1);
        if(i+length<=n)merge(tmpa,a,i,n-1,i+length-1);
        else for(int j=i;j<n;j++)a[j]=tmpa[j];
        length*=2;
    }
} 
//快速排序
int compare(const void*num1,const void*num2){
    return (*(int*)num1-*(int*)num2);
}
void mysort(int start,int end){                 //快速排序：库函数版本
    qsort(a,end-start+1,sizeof(long),compare);
}
int cutoff;
void swap(long*element1,long*element2){
    long tmp=*element1;
    *element1=*element2,*element2=tmp;
}
long median(int start,int end){
    int center=(start+end)/2;
    if(a[start]>a[center])swap(&a[start],&a[center]);
    if(a[start]>a[end])swap(&a[start],&a[end]);
    if(a[center]>a[end])swap(&a[center],&a[end]);
    swap(&a[center],&a[end-1]);
    return a[end-1];
}
void mysort(int start,int end){                 //快速排序：手写版本
    if(start>=end)return;
    if(cutoff<=end-start+1){
        long pivot=median(start,end);
        int low=start,high=end-1;
        while(low<high){
            while(a[++low]<pivot);
            while(a[--high]>pivot);
            swap(&a[low],&a[high]);
        }
        swap(&a[low],&a[end-1]);
        mysort(start,low-1);
        mysort(low+1,end);
    }else sort(a,a+end-start+1);
}
//基数排序
#define maxdigit 4
#define radix 10
typedef struct node*pnode;
struct node{
    long key;pnode next;
};
struct headnode{
    pnode head,tail;
};
typedef struct headnode bucket[radix];
long factor;
int getdigit(long num,int bits){
    int bitnum;
    for(int i=0;i<bits;i++){
        bitnum=(int)num%radix;
        num/=radix;
    }
    return bitnum;
}
void mysort(int start,int end){                 //基数排序：LSD(次位优先)版本
    for(int i=0;i<n;i++)if(factor+a[i]<0)factor=-a[i];
    for(int i=0;i<n;i++)a[i]+=factor;
    bucket buk;
    pnode list=nullptr,p,tmp;
    for(auto&i:buk)i.head=i.tail=nullptr;
    for(int i=end-start;i>=0;i--){
        tmp=new struct node;
        tmp->key=a[i];
        tmp->next=list,list=tmp;
    }
    for(int i=1;i<=maxdigit;i++){
        p=list;
        while(p){
            int di=getdigit(p->key,i);
            tmp=p,p=p->next,tmp->next=nullptr;
            if(!buk[di].head)buk[di].head=buk[di].tail=tmp;
            else buk[di].tail->next=tmp,buk[di].tail=tmp;
        }
        list=nullptr;
        for(int j=radix-1;j>=0;j++){
            if(buk[j].head){
                buk[j].tail->next=list;
                list=buk[j].head;
                buk[j].head=buk[j].tail=nullptr;
            }
        }
    }
    for(int i=0;i<end-start+1;i++){
        tmp=list;
        list=list->next;
        a[i]=tmp->key-factor;
        free(tmp);
    }
}
void mysort_pass(int start,int end,int bits){
    bucket buk;
    pnode list=nullptr,p,tmp;
    if(bits<=0)return;
    for(auto&i:buk)i.head=i.tail=nullptr;
    for(int i=start;i<=end;i++){
        tmp=new struct node;
        tmp->key=a[i];
        tmp->next=list,list=tmp;
    }
    p=list;
    while(p){
        int di=getdigit(p->key,bits);
        tmp=p,p=p->next;
        if(!buk[di].head)buk[di].tail=tmp;
        tmp->next=buk[di].head,buk[di].head=tmp;
    }
    int left=start,right=start;
    for(auto i:buk){
        if(i.head){
            p=i.head;
            while(p){
                tmp=p,p=p->next;
                a[right++]=tmp->key;
                free(tmp);
            }
            mysort_pass(left,right-1,bits-1);
            left=right;
        }
    }
}
void mysort(int start,int end){                 //基数排序：MSD(主位优先)版本
    for(int i=0;i<end-start+1;i++)if(factor+a[i]<0)factor=-a[i];
    for(int i=0;i<end-start+1;i++)a[i]+=factor;
    mysort_pass(start,end,maxdigit);
    for(int i=0;i<end-start+1;i++)a[i]-=factor;
}    
int counts[radix];
long tmpa[maxcount];
void mysort(int start,int end){                 //基数排序：无链表版本
    int bits=1;
    for(int i=0;i<n;i++)if(a[i]+factor<0)factor=-a[i];
    for(int i=0;i<n;i++)a[i]+=factor;
    for(int i=0;i<maxdigit;i++){
        for(int&j:counts)j=0;
        for(int j=0;j<end-start+1;j++){
            int k=(int)(a[j]/bits)%radix;
            counts[k]++;
        }
        for(int j=1;j<radix;j++)counts[j]+=counts[j-1];
        for(int j=0;j<end-start+1;j++){
            int k=(int)(a[j]/bits)%radix;
            tmpa[counts[k]-1]=a[j];
            counts[k]--;
        }
        for(int j=0;j<end-start+1;j++)a[j]=tmpa[j];
        bits*=10;
    }
    for(int i=0;i<n;i++)a[i]-=factor;
}
*/
/*
    1089 Insert or Merge (25 分)
    According to Wikipedia:
    Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
    Each iteration, insertion sort removes one element from the input data, 
    finds the location it belongs within the sorted list, and inserts it there. 
    It repeats until no input elements remain.

    Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element 
    (a list of 1 element is considered sorted). 
    Then repeatedly merge two adjacent sublists to produce new sorted sublists until 
    there is only 1 sublist remaining.

    Now given the initial sequence of integers, 
    together with a sequence which is a result of several iterations of some sorting method, 
    can you tell which sorting method we are using?

    Input Specification:
    Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). 
    Then in the next line, N integers are given as the initial sequence. 
    The last line contains the partially sorted sequence of the N numbers. 
    It is assumed that the target sequence is always ascending. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, print in the first line either "Insertion Sort" or "Merge Sort" 
    to indicate the method used to obtain the partial result. 
    Then run this method for one more iteration and output in the second line the resuling sequence. 
    It is guaranteed that the answer is unique for each test case. 
    All the numbers in a line must be separated by a space, 
    and there must be no extra space at the end of the line.

    Sample Input 1:         Sample Output 1:
    10                      Insertion Sort
    3 1 2 8 7 5 9 4 6 0     1 2 3 5 7 8 9 4 6 0
    1 2 3 7 8 5 9 4 6 0

    Sample Input 2:         Sample Output 2:
    10                      Merge Sort
    3 1 2 8 7 5 9 4 0 6     1 2 3 8 4 5 7 9 0 6
    1 3 2 8 5 7 4 9 0 6
分析：本题关键在于对插入排序和归并排序的理解
     并不一定定需要对依次对整个排序过程完全模拟
     插入排序特点：已经排好序的部分呈现为递增，并且从头开始直到非递增的部分以后就是未排序的，未排序的部分与原始序列相同
                 (实际上是向一个空序列中每次添加一个元素，然后对这个序列进行排序)
     归并排序特点：以length=1开始进行分组(实际上length为2才涉及到排序的问题)，然后将排好序的组合并后再两两归并
                 直到最终合并为一个单一的序列(length=n)
                (题干声明本题有唯一解，所以在归并过程中一定会出现与partial result相同的序列)
     其中sort()为c++ stl中的排序函数
     sort(first,last)对容器或普通数组中[first, last)范围内的元素进行排序，默认进行升序排序。
 
    如何区分简单插入排序和非递归的归并排序
        *插入排序：前面有序，后面没变化
        *归并排序：分段有序(每个固定长度的归并段内均有序)
    
    捏软柿子算法
        *判断是否插入排序
            *从左向右扫描，直到发现顺序不对，跳出循环
            *从跳出地点继续向右扫描，与原序列比对，发现不同则判断为“非”
            *循环自然结束，则判断为“是”，返回跳出地点
        *如果是插入排序的话，则从跳出地点开始进行一趟插入

    判断归并段的长度
        *从头开始连续有序的子列长度
            *反例： 2 1 8 9 6 5 3 4
                   1 2 8 9 5 6 3 4
            *如果从开始扫描的话得出的归并段长度为4(1,2,8,9)，但是明显后面以4为归并长度的子列不是有序的
        *所有连续有序子列的最短长度？
            *反例： 4 2 1 3 13 14 12 11 8 9 7 6 10 5
                   1 2 3 4 11 12 13 14 6 7 8 9 5 10
            *这种情况续有序子列的最短长度为2(5,10)，但从一个子段来看归并长度明显应该是4，之所以因为最后的子列元素没满
            *另外，即使不算最后一个子列，这种情况依然错误，因为这个算法是找最短长度，所以几乎一定会是2或1
        *从原始序列出发，模拟归并排序并跟原始序列相比较，直到与原序列相等后再做一次归并
            *for(l=2;l<=N;*=2);
            *由于题目中给出的是排序过程中的结果，因此对于归并排序来说一般第一趟归并长度是2，所以每两个一组的数据一定是有序的
            *继续判断归并段长度，判断在每两个一组的情况下组间是否有序，以1 2 3 4 11 12 13 14 6 7 8 9 5 10为例
             判断(2,3)，(12,13)，(7,8)之间是否有序，如果有序说明归并段长度为4也满足
            *同理，继续往下判断归并段长度为8,……的情况
    
    测试数据
        *最小N的情况
            *由于题目中明确了数据可以区分插入排序和归并排序，因此N最小为4
            *插入排序的第1步，此时什么都没改变，与原序列相同
            *归并排序的第1步，所有都变了
        *尾部子列没有变化，但是前面变了的情况
            *这种属于归并排序的情况，因此本题无法使用从后往前扫描发现顺序没变就认为是插入排序的算法(这种算法本来就完全错误)
            *最大N的情况
            
答案：(网上抄的...)
#include<iostream>
#include<algorithm>
#define maxcount 105
using namespace std;
int n,initial[maxcount],partial[maxcount];
void IorM();
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>initial[i];
    for(int i=0;i<n;i++)cin>>partial[i];
    IorM();
    for(int i=0;i<n-1;i++)cout<<initial[i]<<' ';
    cout<<initial[n-1];
}
void IorM(){
    int i,j;        
    for(i=1;i<n&&partial[i-1]<=partial[i];i++);     //注意i的取值，这种情况下i取到的是正好是递增结束元素的下标
    for(j=i;j<n&&partial[j]==initial[j];j++);       //检查非递增部分partial是否和intial相同，如果相同说明是插入排序
    if(j==n){
        cout<<"Insertion Sort"<<endl;
        sort(initial,initial+i+1);                  //对0到i+1的initial排序，即相当于在i的基础上再进行一次插入
    }else{
        cout<<"Merge Sort"<<endl;
        int length=1,flag=1;                        //设置flag信号，当flag=1时说明结果还不相等，继续进行迭代
        while(flag){
            flag=0;
            for(i=0;i<n;i++)if(initial[i]!=partial[i])flag=1;
            length*=2;                              //对length进行处理，每次循环乘2
            for(i=0;i<n/length;i++)sort(initial+i*length,initial+(i+1)*length); //对每个相邻的length长度的子列进行归并
            sort(initial+n/length*length,initial+n); //对最后一个剩余的元素数量不满的组进行归并
        }
    }
}  */
/*
    1098 Insertion or Heap Sort (25 分)
    According to Wikipedia:
    Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
    Each iteration, insertion sort removes one element from the input data, 
    finds the location it belongs within the sorted list, and inserts it there. 
    It repeats until no input elements remain.

    Heap sort divides its input into a sorted and an unsorted region, 
    and it iteratively shrinks the unsorted region by extracting the largest element 
    and moving that to the sorted region. 
    it involves the use of a heap data structure rather than a linear-time search to find the maximum.

    Now given the initial sequence of integers, 
    together with a sequence which is a result of several iterations of some sorting method, 
    can you tell which sorting method we are using?

    Input Specification:
    Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). 
    Then in the next line, N integers are given as the initial sequence. 
    The last line contains the partially sorted sequence of the N numbers. 
    It is assumed that the target sequence is always ascending. 
    All the numbers in a line are separated by a space.

    Output Specification:
    For each test case, print in the first line either "Insertion Sort" or "Heap Sort" 
    to indicate the method used to obtain the partial result. 
    Then run this method for one more iteration and output in the second line the resulting sequence. 
    It is guaranteed that the answer is unique for each test case. 
    All the numbers in a line must be separated by a space, 
    and there must be no extra space at the end of the line.

    Sample Input 1:         Sample Output 1:
    10                      Insertion Sort
    3 1 2 8 7 5 9 4 6 0     1 2 3 5 7 8 9 4 6 0
    1 2 3 7 8 5 9 4 6 0
    
    Sample Input 2:         Sample Output 2:
    10                      Heap Sort
    3 1 2 8 7 5 9 4 6 0     5 4 3 1 0 2 6 7 8 9
    6 4 5 1 0 3 2 7 8 9
答案：
#include<iostream>
#include<algorithm>
#define Maxcount 105
using namespace std;
int n,init[Maxcount],partial[Maxcount],insort[Maxcount],hesort[Maxcount];
void IorH(),percdown(int,int);
bool insertion(),heap();
int main(int argc,char*argv[]){
    cin>>n;
    for(int i=0;i<n;i++)cin>>init[i];
    for(int i=0;i<n;i++)insort[i]=hesort[i]=init[i];
    for(int i=0;i<n;i++)cin>>partial[i];
    IorH();
}
void IorH(){
    if(insertion()){
        cout<<"Insertion Sort"<<endl;
        for(int i=0;i<n-1;i++)cout<<insort[i]<<' ';
        cout<<insort[n-1]<<endl;
    }else if(heap()){
        cout<<"Heap Sort"<<endl;
        for(int i=0;i<n-1;i++)cout<<hesort[i]<<' ';
        cout<<hesort[n-1]<<endl;
    }
}
bool insertion(){
    int i,j;
    for(i=1;i<n&&partial[i-1]<=partial[i];i++);
    for(j=i;j<n&&partial[j]==init[j];j++);
    if(j==n){
        sort(insort,insort+i+1);
        return true;
    }
    return false;
}
bool heap(){
    for(int i=n/2-1;i>=0;i--)percdown(i,n);
    for(int i=n-1;i>0;i--){
        int j,tmp=hesort[0];
        hesort[0]=hesort[i],hesort[i]=tmp;
        percdown(0,i);
        for(j=0;j<n&&hesort[j]==partial[j];j++);
        if(j==n){
            tmp=hesort[0];
            hesort[0]=hesort[i-1],hesort[i-1]=tmp;
            percdown(0,i-1);
            return true;
        }
    }
    return false;
}
void percdown(int root,int size){
    int parent,child,tmp=hesort[root];
    for(parent=root;parent*2+1<size;parent=child){
        child=parent*2+1;
        if(hesort[child+1]>hesort[child]&&child<size-1)child++;
        if(tmp>=hesort[child])break;
        else hesort[parent]=hesort[child];
    }
    hesort[parent]=tmp;
} */