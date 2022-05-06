/* 设有一个3位数，它的百位数、十位数、个位数的立方和正好等于这个3位数，如153=1+125+27。
编写函数，返回小于等于传入参数n且满足该条件的三位数（称为水仙花数）的个数。
（指定函数原型：int find(int n)）
 返回值要求：如果传入参数n不是三位数或者在该范围内没有找到，则find返回0，
否则返回找到的水仙花数的个数。
 注意：不要在find函数中打印（如调用printf或puts等函数）任何数据，否则视为错误。
提交的程序需要包含需要的头文件及如下的main函数：
#include<stdio.h>
#include<stdlib.h>
int find(int n);
int main()
{
    int n,r;
    r=scanf("%d",&n);
    if(r!=1){printf("error");return -1;}
    r=find(n);
    printf("%d",r);
    return 0;
}
输入1：400
输出1：3
输入2：59
输出2：0 
int find(int n)
{
    int a,b,c;
    int i,count=0;
    if(n<=999&&n>=100)
    {
        for(i=100;i<=n;i++)
        {
            a=(int)(i/100);
            b=(int)(i/10)-10*a;
            c=i-100*a-10*b;
            if(a*a*a+b*b*b+c*c*c==i)count++;
        }
    }
    else return 0;
    if(count!=0)return count;
    else return 0;
}*/
/*编写程序，从键盘输入5个正整数，然后求出它们的最小公倍数，并显示输出。
（通过调用对两个正整数求最小公倍数的函数实现）（参考函数原型：int LCM(int x, int y))
输入输出格式要求：
int LCM(int x, int y);返回值为x和y的最小公倍数。
要求在main函数接收5个正整数，然后通过调用LCM函数最终得到这5个数的最小公倍数，最后输出最小公倍数。
如果输入数据错误，输出"error"。
例如：
输入：2 3 6 9 10
输出：90 
#include<stdio.h>
int LCM(int x, int y);                  非递归方法
int main() 
{
    int a,b,c,d,e;
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    if(a>0&&b>0&&c>0&&d>0&&e>0)
    {
        printf("%d",LCM(LCM(LCM(a,b),LCM(c,d)),e));     另一种思路是用递归方法求出最大公约数
    }                                                   最小公倍数=两数之积/最大公约数
    else printf("error");
}
int LCM(int x, int y)
{
    int i;
    for(i=x?y:(x>=y);i<=x*y;i++)
    {
        if(i%x==0&&i%y==0)break;
    }
    return i;
}*/
/* 编程实现函数：void my_strcpy(char * destination,char * source);
函数功能：将source指向的字符串拷贝到destination指向的位置。
注意：使用空格字符来表示字符串的结束。例如source指向空间，依次保存了字符'a'，字符'b'，字符空格' '，字符'c'，则source指向的字符串为"ab"。
destionation原来存储的字符串是"xyz tdk"，则拷贝后，destionation存储的应该是“ab  tdk”。
遇到异常情况，输出"error"；否则不要随意输出，会视为错误.
您的main函数需要读入2个长度不超过80字节的字符串(按行依次读入source和destionation字符串），然后调用my_strcpy函数，
最后用puts函数输出destionation里面存储的字符串。
例如：
输入1：xyz abc
a kp
输出1:xyz
输入2：xyz abc
a kppp
输出2：xyz pp   
#include<stdio.h>
#include<string.h>
#define N 80

void my_strcpy(char *destination,char *source);
int main()
{
    char destination[N],source[N];
    gets(source);
    gets(destination);
    my_strcpy(destination,source);
    puts(destination);
}
void my_strcpy(char *destination,char *source)
{
    int i,len;
    char *pd=destination,*ps=source;
    for(i=1;*ps!=' ';i++,ps++)len=i+1;
    ps=source;
    for(i=0;i<len;i++)
    {
        *pd++=*ps++;
    }
    return;
}*/