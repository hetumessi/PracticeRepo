/*  螺旋矩阵
    按螺旋方式为二维数组赋值
    以五阶方阵为例：
    1  2  3  4  5
    16 17 18 19 6 
    15 24 25 20 7 
    14 23 22 21 8 
    13 12 11 10 9 
//c语言可以运行，c++无法通过编译？？？
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#define MAXINPUT 1000
void iterspiralset(int[][MAXINPUT],int,int,char);
void recspiralset(int[][MAXINPUT],int,int,int,int,char);
int main(){
    int a[MAXINPUT][MAXINPUT],num=1;
    unsigned rows,lines,n;
    char ret1,ret2;
    while(1){
        memset(a,0,sizeof(a));
        printf("输入矩阵阶数(n*n)：");
        if(!(ret1=scanf("%d",&n))){
            while(getchar()!='\n');
            printf("重新输入...\n");
            continue;
        }
        printf("输入初始化的行、列数：");
        if((ret1=scanf(" %d %d",&rows,&lines)<2)){
            while(getchar()!='\n');
            printf("重新输入...\n");
            continue;
        }
        if(rows>n||lines>n)printf("提示：你初始化的行/列无法完全显示\n");
        printf("使用迭代方法还是递归方法(迭代：i/递归：r)：");
        scanf(" %c",&ret1);
        printf("顺时针还是逆时针(1：顺时针/2：逆时针)：");
        scanf(" %c",&ret2);
        if((n>0&&n<MAXINPUT)&&(ret1=='i'||ret1=='r')&&(ret2<'3'&&ret2>'0')){
            if(ret1=='i')iterspiralset(a,rows,lines,ret2);
            else recspiralset(a,rows-1,lines-1,0,1,ret2);
        }else{
            while(getchar()!='\n');
            printf("重新输入...\n");
            continue;
        }
        for(int i=0;i<n;i++){
            printf("第%d行数据：\n",i+1);
            for(int j=0;j<n;j++)printf("%d\t",a[i][j]);
            printf("\n");
        }
        printf("是否继续测试？y/n ");
        scanf(" %c",&ret1);
        if(ret1!='y')break;
    }
}
void iterspiralset(int a[][MAXINPUT],int rows,int lines,char ret){
    int start=0,rowborder=rows-1,lineborder=lines-1,num=1,steps;
    while(start<=rowborder&&start<=lineborder){
        if(start==rowborder&&start==lineborder)a[start][start]=num;
        else if(start==rowborder&&start<lineborder)
            for(steps=start;steps<=lineborder;steps++)a[start][steps]=num++;
        else if(start==lineborder&&start<rowborder)
            for(steps=start;steps<=rowborder;steps++)a[steps][start]=num++;
        else{
            for(steps=start;steps<lineborder;steps++)a[start][steps]=num++;
            for(steps=start;steps<rowborder;steps++)a[steps][lineborder]=num++;
            for(steps=lineborder;steps>start;steps--)a[rowborder][steps]=num++;
            for(steps=rowborder;steps>start;steps--)a[steps][start]=num++;
        }
        start++,rowborder--,lineborder--;
    }
    if(ret=='2'){
        int*tmp=(int*)malloc(sizeof(int)),*pa,*pb;
        for(int i=0;i<rows;i++){
            pa=*a+i*MAXINPUT;
            pb=pa+lines-1;
            for(int j=0;j<lines/2;j++)*tmp=*pa,*pa++=*pb,*pb--=*tmp;
        }
        free(tmp);
    }
}
void recspiralset(int a[][MAXINPUT],int rowborder,int lineborder,int start,int num,char ret){
    int steps;
    if(start>rowborder||start>lineborder)return;
    else if(start==rowborder&&start==lineborder)a[start][start]=num;
    else if(start==rowborder&&start<lineborder)
        for(steps=start;steps<=lineborder;steps++)a[start][steps]=num++;
    else if(start==lineborder&&start<rowborder)
        for(steps=start;steps<=rowborder;steps++)a[steps][start]=num++;
    else{
        for(steps=start;steps<lineborder;steps++)a[start][steps]=num++;
        for(steps=start;steps<rowborder;steps++)a[steps][lineborder]=num++;
        for(steps=lineborder;steps>start;steps--)a[rowborder][steps]=num++;
        for(steps=rowborder;steps>start;steps--)a[steps][start]=num++;
    }
    if(ret=='2'){
        int*tmp=(int*)malloc(sizeof(int)),*pa=*a+start*(MAXINPUT+1),*pb=*a+start*MAXINPUT+lineborder;
        for(int i=start;i<(lineborder+start+1)/2;i++)*tmp=*pa,*pa++=*pb,*pb--=*tmp;
        for(int i=start+1;i<rowborder;i++){
            pa=*a+i*MAXINPUT+start,pb=*a+i*MAXINPUT+lineborder;
            *tmp=*pa,*pa=*pb,*pb=*tmp;
        }
        if(start!=rowborder){
            pa+=MAXINPUT,pb+=MAXINPUT;
            for(int i=start;i<(lineborder+start+1)/2;i++)*tmp=*pa,*pa++=*pb,*pb--=*tmp;
        }
        free(tmp);
    }
    recspiralset(a,rowborder-1,lineborder-1,start+1,num,ret);
}  */