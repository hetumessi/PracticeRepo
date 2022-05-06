/* 回文测试：输入一30个字符以内的字符串，判断是否为回文；如果是，则打印"true"；否则打印"false"。像"aba"这样的从左往右读与从右往左读一致就是回文。
输入样例1：
ayzya
输出样例1：
true
输入样例2：
ayzy
输出样例2：
false
#include<stdio.h>
#include<string.h>

int main()
{
    char string[31];
    int i,iscycle=1;
    scanf("%s",string);
    int len=strlen(string);
    if(len<=30)
    {
        for(i=0;i<=len/2;i++)
        {
            if(string[i]!=string[len-i-1])
            {
                printf("false");
                iscycle=0;
                break;
            }
        }
        if(iscycle==1)printf("true");
    }
}*/

/*书有书名(字符串长度不超过50字节)，价格（单精度实数），分类（正整数）。
书的结构定义如下:
struct book
{
	char name[50];
	float price;
	int classification;	
}; 
输入n本书（n<=100)，及每本书的书名，价格和分类(空格分隔输入数据)， 
请分别根据价格递增顺序排序，如果价格相同，则按照书名(ASCII码）递增排序。
最后输出排序后的结果，每行一本书详细信息，按照：书名，价格(保留2位小数），分类由逗号分隔。
例子: 
输入：
3
program 35  1
history   35  2
cloudy-computing 57 1 
输出 
history,35.00,2
program,35.00,1
cloudy-computing,57.00,1

#include<stdio.h>
#include<stdio.h>
#include<string.h>

int main()
{
    typedef struct book
	{
        char name[50];
	    float price;
	    int classification;	
    }book;
    int n,i,j,max;
    scanf("%d",&n);
    book bk[n],tmp;
    if(n<=100)
    {
        for(i=0;i<n;i++)
    {
        scanf("%s %f %d",bk[i].name,&bk[i].price,&bk[i].classification);
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(bk[i].price>bk[j].price||(bk[i].price==bk[j].price&&strcmp(bk[i].name,bk[j].name)>0))
            {
                tmp=bk[i];
                bk[i]=bk[j];
                bk[j]=tmp;
            }
        }
    }
    for(i=0;i<n;i++)printf("%s,%.2f,%d\n",bk[i].name,bk[i].price,bk[i].classification);
    }
}*/

/*接受若干非负整数（数据不重复），当个数超过10个或者遇到负数时停止接受，将这几个整数按升序排列输出，并且奇数在前，偶数在后。
输出要求，每个数字后输出空格与其他数字隔开，最后一个数字后也有空格
输入样例1：
10 9 8 7 6 5 4 3 2 1
输出样例1：
1 3 5 7 9 2 4 6 8 10 回车
输入样例2：
2 3 4 5 -1
输出样例2：
3 5 2 4 回车

#include<stdio.h>
#include<string.h>

int main()
{
    int a[10];
    int i,j,k,len,x;
    len=0;
    k=0;
    for(i=0;i<10;i++)
    {
        x=scanf("%d",&a[i]);
        if(a[i]<0||x==0) break;
        len++;
    }
    for(i=0;i<len-1;i++){
	    for(j=0;j<len-i-1;j++){
		    if(a[j]%2==0){
			    k=a[j+1];
			    a[j+1]=a[j];
			    a[j]=k;
		    }
	    }
    }
    for(i=0;i<len-1;i++){
	    for(j=0;j<len-i-1;j++){
		    if(a[j]>a[j+1]&&a[j]%2&&a[j+1]%2){
			    k=a[j+1];
			    a[j+1]=a[j];
			    a[j]=k;
		    }
		    if(a[j]>a[j+1]&&a[j]%2==0&&a[j+1]%2==0){
			    k=a[j+1];
			    a[j+1]=a[j];
			    a[j]=k;
		    }
	    }
    }
    for(i=0;i<len-1;i++)
    {
    printf("%d ",a[i]);
    }
    return 0;
}*/
