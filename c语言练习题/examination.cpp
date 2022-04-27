/* 如果一个数正好是他的所有约数（除了它本身以外）的和，称为完备数，
如：6，它的约数有1，2，3，并且1+2+3=6,则6是一个完备数。
请输出n以内的所有完备数(完备数递增输出），每个完备数1行,每行按照下例输出：
比如某完备数是6，则该行输出：6=1+2+3
如果输入错误，则输出"error"。
例如：
输入：
40
输出：
6=1+2+3空格回车
28=1+2+4+7+14空格回车 
#include<iostream>
using namespace std;
int main()
{
    int n,i,j,sum,count;
    cin>>n;
    int divisor[n];
    if(!cin||n<=0)cout<<"error";
    else
    {
        for(i=2;i<=n;i++)
        {
            count=0,sum=0;
            for(j=0;j<n;j++)divisor[j]=0;
            for(j=1;j<=i/2;j++)
            {
                if(i%j==0)
                {
                    sum+=j;
                    divisor[count++]=j;
                }
            }
            if(sum==i)
            {
                cout<<i<<'=';
                for(j=0;j<count-1;j++)cout<<divisor[j]<<'+';
                cout<<divisor[count-1]<<' '<<endl;
            }
        }
    }
}*/

/* 实现逆序的Memcpy方法。
char * reversememcpy ( char * destination, const char * source, int num );
从source所指的内存地址的起始位置开始拷贝num个字节，逆序保存到目标destination所指的内存地址的
起始位置中。返回destination首地址。
注意为逆序拷贝。比如source指向的位置，依次保存了abcdef，当num=3时，则逆序拷贝后destination指向的
位置应该依次保存cba.
输入:abcdef
输出:cba
提交的程序包括main函数，具体内容如下:
#include<stdio.h>
#include<string.h>
char * reversememcpy ( char  * destination, const char * source, int num );
int main()
{
    char source[100],*destionation=new char[100],*t;
    int n; 
    gets(source);
    scanf("%d",&n);
	memset(destionation,'\0',sizeof(destionation));
    t=reversememcpy (destionation,source,n);
    if(t==NULL)
	{
		printf("error");
		delete(destionation);
		return 0;
	}
	if(strlen(destionation)>0)
   		printf("%s",destionation);
   	else
   		printf("no copy");
	    delete(destionation);
   return 0;
}
注意：目标地址不能为空，源和目标空间首地址差应该大于num。如果num>strlen(source)，应该输出error
如果不能拷贝，输出“no copy"。
#include<cstdio>
#include<cstring>
char * reversememcpy ( char  *destination, const char *source, int num);
int main()
{
    char source[100],*destionation=new char[100],*t;
    int n; 
    gets(source);
    scanf("%d",&n);
	memset(destionation,'\0',sizeof(destionation));
    t=reversememcpy (destionation,source,n);
    if(t==NULL)
	{
		printf("error");
		delete[](destionation);
		return 0;
	}
	if(strlen(destionation)>0)
   		printf("%s",destionation);
   	else
   		printf("no copy");
	    delete[](destionation);
   return 0;
}
char* reversememcpy (char *destination,const char *source,int num)
{
    char *c=destination;
    int i;
    for(i=0;i<num;i++)
    {
        *c=*(source+num-i-1);
        c++;
    }
    return destination;
} */

/* 题目内容：
输入n个整数，用冒泡排序对这n个数进行递增/非递减排序，输出排序后的结果.如果输入不符要求，则输出"error"
输入格式:第一行是待排序的数据个数n，第二排是逗号分隔的n个正整数
9
9,8,7,6,5,4,3,2,1
输出格式：输出排序后的用逗号分隔的n个数据，最后1个数据后面没有逗号
1,2,3,4,5,6,7,8,9 
#include<cstdio>
int main()
{
    int t,i,j,n,temp;
    scanf("%d",&n);
    int data[n];
    for(i=0;i<n;i++)t=scanf("%d,",&data[i]);
    if(t!=1)printf("error");
    else
    {
        for(i=0;i<n;i++)
        {
            for(j=1;j<n-i;j++)
            {
                if(data[j-1]>data[j])
                {
                    temp=data[j];
                    data[j]=data[j-1];
                    data[j-1]=temp;
                }
            }
        }
        for(i=0;i<n-1;i++)printf("%d,",data[i]);
        printf("%d",data[n-1]);
    }
} */

/* 实现一个三角形类 Ctriangle 
该类有一个GetPerimeter方法返回三角形的周长;
GetArea方法返回三角形的面积;
该类还提供一个display方法显示三角形的三边长度;
最终在main函数中生成该类对象，
输入三条边的长度（不用考虑三条边不能构成三角形的情况）;
展示三角形的三边长度以及周长和面积
Ctriangle类的使用如下，在你的代码中除了实现Ctriangle类还需引入一下代码。
int main() 
{
    double a, b, c;
    cin >> a >> b >> c;
    Ctriangle T(a, b, c);
    T.display();
    cout << "Perimeter:" <<setprecision(4)<< T.GetPerimeter() << endl;
    cout << "Area:" << setprecision(5) << T.GetArea() << endl;
    system("pause");
    return 0;
}
输出格式
输入：3 4 5
输出：
Ctriangle:a=3,b=4,c=5
Perimeter:12
Area:6 
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
class Ctriangle
{
    double a,b,c;
    public:
    Ctriangle(double v1,double v2,double v3):a(v1),b(v2),c(v3){}
    void display();
    double GetPerimeter();
    double GetArea();
};
void Ctriangle::display()
{
    cout<<"Ctriangle:a="<<a<<','<<"b="<<b<<','<<"c="<<c<<endl;
}
double Ctriangle::GetPerimeter()
{
    return a+b+c;
}
double Ctriangle::GetArea()
{
    double l=(a+b+c)/2;
    return sqrt(l*(l-a)*(l-b)*(l-c));
}
int main() 
{
    double a, b, c;
    cin >> a >> b >> c;
    Ctriangle T(a, b, c);
    T.display();
    cout << "Perimeter:" <<setprecision(4)<< T.GetPerimeter() << endl;
    cout << "Area:" << setprecision(5) << T.GetArea() << endl;
    system("pause");
    return 0;
}  */
/* 扩展String类，引入头文件CString.h,它的内容如下：
#include <iostream>
using namespace std;
class String{
protected:
	char *mystr;
	int len;
public:
	String(const char *p){
		len = strlen(p);
		mystr = new char[len+1];
		strcpy(mystr,p);
	}
	~String(){
		if (mystr !=NULL)
		{
			delete []mystr;
			mystr = NULL;
			len = 0;
		}
	}
	void showStr(){cout <<mystr;}
	char * GetStr(){return mystr;}
	virtual bool IsSubString(const char *str){
		int i,j;
		for (i =0;i<len;i++)
		{
			int k = i;
			for (j =0;str[j] !='\0';j++,k++)
			{
				if (str[j]!= mystr[k]) break;
			}
			if(str[j] =='\0') return true;
		}
		return false;
	}
};

class EditString:public String{
public:
	EditString(const char *p):String(p){}
	int IsSubString(int start, const char *str);
	void EditChar(char s, char d); 
	void EditSub(char * subs,char *subd); 
	void DeleteChar(char ch);  
	void DeleteSub(char * sub); 
};

实现int IsSubString(int start, const char *str);
从start处开始判断str是否为字符串的子串，是则返回子串第一次出现处的下标位置(下标从0开始计算)，否则返回-1；
例如：
EditString es("testtesttest");
es.IsSubString(3,"test");//4

实现EditChar(char s, char d)，用字符d代替所有字符s，例如：
EditString es("testtesttest");
es.EditChar('t','a');//"aesaaesaaesa"

实现void EditSub(char * subs,char *subd)，用字符串subd代替所有字符串subs，例如：
EditString es("testtesttest");
es.EditChar("test","str");//"strstrstr"

实现void DeleteChar(char ch)，将所有ch字符删除，例如：
EditString es("testtesttest");
es.DeleteChar('t');//"eseses"

实现void DeleteSub(char * sub)，将所有的字符串sub删除，例如：
EditString es("testtesttest");
es.DeleteSub("es");//"tttttt";
要求在main函数中输入一个字符串,然后依次将功能显示出来,代码如下:
int main()
{
    EditString mystring("testtesttest");
	//输入:testtesttest,3,test,t,a,aesa,str,t,rs
	//输出:4,aesaaesaaesa,strstrstr,eseses,tttttt
    cout<<mystring.IsSubString(3,"test")<<",";
	mystring.EditChar('t','a');
	mystring.showStr();
	cout<<",";
	mystring.EditSub("aesa","str");
	mystring.showStr();
	cout<<",";
	mystring.DeleteChar('t');
	mystring.showStr();
	cout<<",";
	mystring.DeleteSub("rs");
	mystring.showStr();
	return 0;
}
例如输入(空格或者回车分隔输入数据):
testtesttest 3 test t a aesa str t rs
输出(逗号分隔输出）:
4,aesaaesaaesa,strstrstr,srsrsr,sr  
#include <iostream>
#include <cstring>
using namespace std;
class String{
protected:
    char *mystr;
    int len;
public:
    String(const char *p){
        len = strlen(p);
        mystr = new char[len+1];
        strcpy(mystr,p);
    }
    ~String(){
        if (mystr !=NULL)
        {
            delete []mystr;
            mystr = NULL;
            len = 0;
        }
    }
    void showStr(){cout <<mystr;}
    char * GetStr(){return mystr;}
    virtual bool IsSubString(const char *str){
        int i,j;
        for (i =0;i<len;i++)
        {
            int k = i;
            for (j =0;str[j] !='\0';j++,k++)
            {
                if (str[j]!= mystr[k]) break;
            }
            if(str[j] =='\0') return true;
        }
        return false;
    }
};

class EditString:public String{
public:
    EditString(const char *p):String(p){}
    int IsSubString(int start, const char *str);
    void EditChar(char s, char d);
    void EditSub(char * subs,char *subd);

    void DeleteChar(char ch);
    void DeleteSub(char * sub);

};
int EditString::IsSubString(int start, const char *str)
{
    int i=start,j;
    for (i =start;i<len;i++)
    {
        int k = i;
        for (j =0;str[j] !='\0';j++,k++)
        {
            if (str[j]!= mystr[k]) break;
        }
        if(str[j] =='\0') return i;
    }
    return -1;
}
void EditString::EditChar(char s, char d)
{
    char *p = mystr;
    while(*p)
    {
        if(*p==s)
            *p = d;
        p++;
    }
}
void EditString::EditSub(char * subs,char *subd)
{
    int start=0;
    char *temp = new char[len+1];
    while(start<len)
    {
        start=IsSubString(start,subs);
        if(start!=-1){
            strncpy(temp,mystr,start);
            temp[start] = '\0';
            strcat(strcat(temp,subd),&mystr[start+strlen(subs)]);
            strcpy(mystr,temp);
            len = strlen(mystr);
        }
        else{
            break;
        }
    }
    delete []temp;
}
void EditString::DeleteChar(char ch)
{
    char *p = mystr,*q=mystr;
    while(*q)
    {
        if(*q!=ch){
            *p = *q;
            p++;
        }
        q++;
    }
    *p = '\0';
    len = strlen(mystr);
}
void EditString::DeleteSub(char * sub){
    int start=0;
    char *temp = new char[len+1];
    while(start<len)
    {
        start=IsSubString(start,sub);
        if(start!=-1){
            strncpy(temp,mystr,start);
            temp[start] = '\0';
            strcat(temp,&mystr[start+strlen(sub)]);
            strcpy(mystr,temp);
            len = strlen(mystr);
        }
        else{
            break;
        }
    }
    delete []temp;
}
void fun(char *s,char str[][256]){
    int index = 0;
    char *p = s,*q = s;
    while(*p)
    {
        if(*p==','){
            *p = '\0';
            strcpy(str[index++],q);
            q = p+1;
        }
        p++;
    }
    strcpy(str[index++],q);
    for(int i=0;i<9;++i){
        printf("%s\n",str[i]);
    } 
}
int main()
{
    EditString mystring("testtesttest");
	//输入:testtesttest,3,test,t,a,aesa,str,t,rs
	//输出:4,aesaaesaaesa,strstrstr,eseses,tttttt
    cout<<mystring.IsSubString(3,"test")<<",";
	mystring.EditChar('t','a');
	mystring.showStr();
	cout<<",";
	mystring.EditSub("aesa","str");
	mystring.showStr();
	cout<<",";
	mystring.DeleteChar('t');
	mystring.showStr();
	cout<<",";
	mystring.DeleteSub("rs");
	mystring.showStr();
	return 0;
}*/