//
// Created by 徐绍骞 on 2021/6/19.
//
#include <iostream>
#include <cmath>
#include <climits>
#include <cstring>
#include "shared.h"
using namespace std;
// 练习2-1
void signedrange(){
    cout<<"signed char取值范围："<<-pow(2,8*sizeof(char)-1)
    <<'~'<<pow(2,8*sizeof(char)-1)-1<<endl;
    cout<<"signed short取值范围："<<-pow(2,8*sizeof(short)-1)
        <<'~'<<pow(2,8*sizeof(short)-1)-1<<endl;
    cout<<"signed int取值范围："<<-pow(2,8*sizeof(int)-1)
        <<'~'<<pow(2,8*sizeof(int)-1)-1<<endl;
    cout<<"signed long取值范围："<<-pow(2,8*sizeof(long)-1)
        <<'~'<<pow(2,8*sizeof(long)-1)-1<<endl;
}
void unsignedrange(){
    cout<<"unsigned char取值范围："<<0
        <<'~'<<pow(2,8*sizeof(char))-1<<endl;
    cout<<"unsigned short取值范围："<<0
        <<'~'<<pow(2,8*sizeof(short))-1<<endl;
    cout<<"unsigned int取值范围："<<0
        <<'~'<<pow(2,8*sizeof(int))-1<<endl;
    cout<<"unsigned long取值范围："<<0
        <<'~'<<pow(2,8*sizeof(long))-1<<endl;
}
void printimpulse(){
    cout<<"signed char最大值："<<SCHAR_MAX<<"   "<<"最小值："<<SCHAR_MIN<<endl;
    cout<<"signed short最大值："<<SHRT_MAX<<"   "<<"最小值："<<SHRT_MIN<<endl;
    cout<<"signed int最大值："<<INT_MAX<<"   "<<"最小值："<<INT_MIN<<endl;
    cout<<"signed long最大值："<<LONG_MAX<<"   "<<"最小值："<<LONG_MIN<<endl;
    cout<<"unsigned long最大值："<<UCHAR_MAX<<"   "<<"最小值："<<0<<endl;
    cout<<"unsigned long最大值："<<USHRT_MAX<<"   "<<"最小值："<<0<<endl;
    cout<<"unsigned long最大值："<<UINT_MAX<<"   "<<"最小值："<<0<<endl;
    cout<<"unsigned long最大值："<<ULONG_MAX<<"   "<<"最小值："<<0<<endl;
}
// 练习2-2
int get_withoutandor(char* s,int lim){
    int i=0,c=getchar(),ijudge=YES;
    while(ijudge==YES){
        if(i>lim-1)ijudge=NO;
        s[i++] = c;
        c = getchar();
        if(c=='\n')ijudge=NO;
        if(c==EOF)ijudge=NO;
    }
    return i;
}
// 例2.7 输出字符串中的整数,输出小写字母对应ASCII字符集的整数
int aoti(char* s){
    int n=0,i;
    for(i=0;i< strlen(s);i++)if(s[i]>='0'&&s[i]<='9')n=10*n+(s[i]-'0');
    return n;
}
int lower(int c){
    if(c>='A'&&c<='Z')return c-'A'+'a';
    if(c>='a'&&c<='z')return c;
    return -1;
}
// 练习2-3
int judgestring(char *s){
    int i=2;
    if((s[0]=='0'&&s[1]=='x')||(s[0]=='0'&&s[1]=='X'))
        while((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f')||(s[i]>='A'&&s[i]<='F'))i++;
    if(i== strlen(s))return i;
    return -1;
}
int htoi(char* s){
    int len= judgestring(s),n=0,i=2;
    if(judgestring(s)==-1)return -1;
    else{
        for(;i<len;i++){
            if(s[i]>='0'&&s[i]<='9')n+=(s[i]-'0')*(int)pow(16,len-i-1);
            if(s[i]>='a'&&s[i]<='f')n+=(s[i]-'a'+10)*(int)pow(16,len-i-1);
            if(s[i]>='A'&&s[i]<='F')n+=(s[i]-'A'+10)*(int)pow(16,len-i-1);
        }
    }
    return n;
}
// 练习2-4
char* squeeze1(char*s1,char* s2){       //删除s1与s2对应位置相同的字符
    int i,j=0,len= (strlen(s1)>strlen(s2)?strlen(s2):strlen(s1));
    if(strlen(s1)>strlen(s2)){
        for(i=0;i<len;i++)if(s1[i]!=s2[i])s1[j++]=s1[i];
        for(int k=0;k<strlen(s1)-len;k++)s1[j++]=s1[i++];
    } else for(i=0;i<len;i++)if(s1[i]!=s2[i])s1[j++]=s1[i];
    s1[j]='\0';
    return s1;
}
char* squeeze2(char*s1,char* s2){       //删除s1中与s2的任何字符相同的字符
    int i,j,k;
    for(i=0;i< strlen(s2);i++){
        for(j=0,k=0;j< strlen(s1);j++)if(s1[j]!=s2[i])s1[k++]=s1[j];
        s1[k]='\0';
    }
    return s1;
}
// 练习2-5
int any(char* s1,char* s2){
    int i,j;
    for(i=0;i<strlen(s2);i++){
        for(j=0;j< strlen(s1);j++)if(s1[j]==s2[i])return j+1;
        if(i== strlen(s2))return -1;
    }
    return  0;
}
// 例2.9 返回从右边第p位开始向右n位的字段，假定最右边的一位是第0位，这台机器是逻辑移位
unsigned getbits(unsigned x,int p,int n){   //返回的字段是从右边第p+1-n位开始向左扫描到第p位结束
    return (x>>(p+1-n))&~(~0<<n);           //x右移p+1-n位使第p+1-n变为最低位
}                                                            //~(~0<<n)表示低n位全为1，其他位为屏蔽码
// 练习2-6
int ubinarydecimal(int a,int n);
unsigned setbits(unsigned x,int p,int n,unsigned y){
    y=((y>>n)<<n)|(x>>(p+1-n))&~(~0<<n);
    return y;
}
unsigned invert(unsigned x,int p,int n){
    unsigned tmp=~(~0<<(p+1))&(~0<<(p+1-n));
    x^=tmp;
    return x;
}
unsigned rightrot(unsigned x,int n){        //只考虑8位以内循环
    int rot=n%8;
    return (x<<(8-rot))|(x>>rot);
}
int ubinarydecimal(int a,int n){
    int b=0;
    for(int i=0;i<n;i++){
        b=10*b+((a>>(n-i-1))&1);
//        cout<<((a>>(n-i-1))&1);
    }
    return b;
}
// 练习2-9
int bitcount1(unsigned x){         // 最坏情况：所有位都为1时与bitcount2需要进行的移位次数相同
    int a;
    for(a=0;x!=0;x&=(x-1),a++);     // x-1将x最右边值为1的一位置为0，低于此位的置为1
    return a;                                  // x&=(x-1)删除x中最右边值为1的一个二进制位
}
//int bitcount2(unsigned x){
//    int a;
//    for(a=0;x!=0;x>>=1)if(x&01)a++;
//    return a;
//}
// 练习2-10
int lower_withoutifelse(int c){
    return ((c>='a'&&c<='z')||(c>='A'&&c<='Z'))?((c>='a'&&c<='z')?c:c-'A'+'a'):-1;
}