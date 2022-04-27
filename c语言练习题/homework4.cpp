/*功能：实现删除字符串中连续的重复字符（除字母和数字）。 输入为字符串，将字符串中连续重复的，非字母和数字的字符删去，然后输出处理后的字符串。
要求用指针指向输入的字符串进行操作。
输入格式:
输入字符串最长50个字符，之后截断，只输出处理后的字符串。 
输出格式：
输入样例：
1+++2==3
输出样例：
1+2=3
注意：尽量不用string库的函数处理，否则可能会出现错误扣分的情况（可能和网站编译系统有关）
标准答案：
#include<stdio.h>
int main(){
	char a[100];
	char b[100]={0};
	int i,j=1;
	char *q=a,*p=b;
	scanf("%50s",a);
	b[0]=a[0];
	for(i=1;a[i]!='\0';i++){
		if(a[i]<'0'||a[i]>'z'||(a[i]>'9'&&a[i]<'A')||(a[i])>'Z'&&a[i]<'a')
		if(a[i]==b[j-1])continue;
		*(p+j)=*(q+i);
		j++;

	}
    printf("%s",b);
    return 0;
}*/

/* 题目内容：编写程序，输入一个字符串(字符串长度不超过50），分别统计输出该字符串中的字母个数和数字个数。要求用指针指向这个字符串进行处理。
输入格式:
字符串
输出格式：
英文逗号分隔的2个整数，第一个整数是字母个数，第二个整数的数字个数。
输入样例：
the day the month the year 123
输出样例：
21,3
标准答案：
#include <stdio.h>
#define N 50
int main()
{
    char str[N] = "";
    char *p = str;
    int letters = 0, digits = 0;
    gets(str);

    while(*p){
        if(*p>='0'&&*p<='9')
            digits++;
        if(*p>='a'&&*p<='z'||*p>='A'&&*p<='Z')
            letters++;
        p++;
    }
    printf("%d,%d\n",letters,digits);

    return 0;
}*/

/* 题目内容：
编写程序，输入两个字符串，通过2个指针p和q分别指向这2个字符串，比较字符串是否相等。 要求不使用strcmp函数。
输入格式:string1回车string2回车 
说明:string1和string2最长为256，可能包含空格 
输出格式：
相等输出: equal
不等输出: unequal
输入样例：
string1
string2
输出样例：
unequal 

#include<stdio.h>

int main()
{
    const int n=256;
    char string1[n],string2[n];
    char *pstr1=string1,*pstr2=string2;
    int i,len1,equal=0;
    gets(string1);
    gets(string2);
    while(*pstr1&&*pstr2)
    {
        if(*pstr1!=*pstr2)
        {
            printf("unequal");
            equal=1;
            break;
        }
        pstr1++;
        pstr2++;
        i++;
    }
    if(equal==0)printf("equal");
}
*/