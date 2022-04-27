/* 鲁智深吃馒头。
    据说，鲁智深一天中午匆匆来到开封府大相国寺，想蹭顿饭吃，当时大相国寺有99个和尚，只做了99个馒头
    智清长老不愿得罪鲁智深，便把他安排在一个特定位置，之后对所有人说：
    从我开始报数（围成一圈），第5个人可以吃到馒头（并退下）
    按此方法，所有和尚都吃到了馒头，唯独鲁智深没有吃上，请问他在那个位置？ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int solve(int,int);
int main(){
    printf("%d",solve(100,5));
    return 0;
}
int solve(int monksnum,int step){
    int monk[monksnum],count=0,num=0,luzhishen;
    memset(monk,0,sizeof(monk));
    for(;count<monksnum-1;count++){
        for(int i=0;i<step;i++,num++)while(monk[num%monksnum]<0)num++;
        monk[(num-1)%monksnum]=-1;
    }
    for(int i=0;i<monksnum;i++)if(monk[i]==0)luzhishen=i+1;
    return luzhishen;
}    */
/* 计算50!的值 
    原理：使用一个足够大的数组存放结果的各个位上的数字
         在进行乘法计算时用乘数乘每位上的数字，从最后一位开始计算
         当一位上的数字除以10不为0的话，将除以10的结果进位到前一位，原本一位只保留除以10的余数
         例：450*50
            ｜4｜5｜0｜ -> ｜200｜250｜0｜ -> ｜225｜0｜0｜ -> ｜22｜5｜0｜0｜ -> ｜2｜2｜5｜0｜0｜
#include<cstdio>
#include<cstring>
void fact(int);
int main(){
    fact(50);
    return 0;
}
void fact(int n){
    int sumdigits[100],sumbits=1,tmp;
    memset(sumdigits,-1,sizeof(sumdigits));
    sumdigits[sumbits-1]=1;
    for(int multiplier=2;multiplier<=n;multiplier++){
        for(int i=0;i<sumbits;i++)sumdigits[i]*=multiplier;
        for(int i=sumbits-1;i>0;i--)sumdigits[i-1]+=sumdigits[i]/10,sumdigits[i]%=10;
        while(sumdigits[0]/10){
            for(int i=sumbits;i>0;i--)sumdigits[i+1]=sumdigits[i];
            tmp=sumdigits[0]/10;
            sumdigits[1]=sumdigits[0]%10;
            sumdigits[0]=tmp;
            sumbits++;
        }
    }
    for(int i=0;i<sumbits;i++)printf("%d",sumdigits[i]);
}  */