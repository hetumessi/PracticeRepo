/* 7-17 汉诺塔的非递归实现 (25 分)
    借助堆栈以非递归（循环）方式求解汉诺塔的问题（n, a, b, c），即将N个盘子从起始柱（标记为“a”）通过借助柱（标记为“b”）移动到目标柱
    （标记为“c”），并保证每个移动符合汉诺塔问题的要求。
    输入格式:
    输入为一个正整数N，即起始柱上的盘数。
    输出格式:
    每个操作（移动）占一行，按柱1 -> 柱2的格式输出。
    输入样例:
    3
    输出样例:
    a -> c
    a -> b
    c -> b
    a -> c
    b -> a
    b -> c
    a -> c  */

/*  hanoi塔的递归实现  
#include<cstdio>
void hanoi(int,char,char,char)；
int main(){
    int n;
    scanf("%d",&n);
    hanoi(n,'a','c','b');
    return 0;
} 
void hanoi(int ranks,char origin,char aim,char tmp){
    if(ranks==1)printf("%c -> %c\n",origin,aim);
    else{
        hanoi(ranks-1,origin,tmp,aim);
        printf("%c -> %c\n",origin,aim);
        hanoi(ranks-1,tmp,aim,origin);
    }
} */
/*  使用栈模拟系统栈运行递归的解法  
#include<cstdio>
#define MAXINPUT 64
//定义两个宏以便于在push和hanoi_stimulation函数中批量创建同名变量拷贝栈顶活动的参数
#define PUSH_S(x) sysstack_stimulation[top].x=x  
#define SET(x) x=sysstack_stimulation[top].x
//定义一个结构体，储存模拟活动中的参数信息
typedef struct info{
    char origin,aim,tmp;
    int ranks,step;
}info;
//定义一个模拟栈用于模拟递归过程的活动记录
info sysstack_stimulation[MAXINPUT];
void push(int,char,char,char,int),hanoi_stimulation();
int top;   //栈顶指针
int main(){
    int n;
    scanf("%d",&n);
    push(n,'a','c','b',0);
    while(top>0)hanoi_stimulation(); //模拟栈不为空则循环执行hanoi模拟函数
}
void push(int ranks,char origin,char aim,char tmp,int step){
    top++;  //注意push时要先新开一个栈单元，再存储活动记录
    PUSH_S(ranks);
    PUSH_S(origin);
    PUSH_S(aim);
    PUSH_S(tmp);
    PUSH_S(step);
}
void hanoi_stimulation(){
    int SET(ranks),SET(step);
    char SET(origin),SET(aim),SET(tmp);
    switch(step){
        //根据hanoi的递归函数可知，当ranks不为1时每层的子问题需要进行三步处理
        case 0:     //case为0存在两种情况，ranks为1时打印语句，ranks不为1说明是刚压入栈的“递归”子活动
            if(ranks==1){
                printf("%c -> %c\n",origin,aim);
                break;
            }else{  
                sysstack_stimulation[top].step++;  
                push(ranks-1,origin,tmp,aim,0);    //继续向栈中压入ranks规模更小的子函数
                //相当于模拟hanoi(ranks-1,origin,tmp,aim);
                return;   //return而不是break，这样可以不执行后面的弹栈操作，使活动记录暂时“休眠”在栈中
            }
        case 1:     //case为1时说明第一步的子活动递归完成返回了，后栈顶活动完成了第一步处理
            sysstack_stimulation[top].step++;
            push(1,origin,aim,tmp,0);
            //将ranks为1的活动压入栈顶，实际上相当于模拟printf("%c -> %c\n",origin,aim);
            return;
        case 2:     //case为2的情况同理
            sysstack_stimulation[top].step++;
            push(ranks-1,tmp,aim,origin,0);
            //相当于模拟hanoi(ranks-1,tmp,aim,origin);
            return;
        default:break;
    }
    top--;     //正常结束的情况(即ranks规模为1，符合递归出口条件时)，将栈顶活动弹出
} */
/*  使用栈模拟系统栈运行递归的解法：改进
    实际上在使用栈模拟递归时并不需要使用专门的变量step来记录模拟进行的步骤，因为只要栈中活动顺序没有问题，那么与正常递归执行的顺序是
    一致的；但是需要注意的是，如果将递归函数的三步操作一次性压入栈中的话，需要逆序压入，这样栈顶的是第一步操作，然后对栈顶活动继续模拟
    即可(由于二三步操作之前就被压入栈中，因此后续只需要对栈顶活动进行处理即可)    
#include<cstdio>
#define MAXINPUT 64
#define PUSH_S(x) sysstack_stimulation[top].x=x  
#define SET(x) x=sysstack_stimulation[top].x
typedef struct info{
    char origin,aim,tmp;
    int ranks;
}info;
info sysstack_stimulation[MAXINPUT];
void push(int,char,char,char),hanoi_stimulation();
int top;
int main(){
    int n;
    scanf("%d",&n);
    push(n,'a','c','b');
    while(top>0)hanoi_stimulation(); 
}
void push(int ranks,char origin,char aim,char tmp){
    top++; 
    PUSH_S(ranks);
    PUSH_S(origin);
    PUSH_S(aim);
    PUSH_S(tmp);
}
void hanoi_stimulation(){
    int SET(ranks);
    char SET(origin),SET(aim),SET(tmp);
    top--;   //注意这种情况下只需将初始栈中的活动弹出，或替换为三个新的活动即可
    if(ranks==1)printf("%c -> %c\n",origin,aim);
    else{
        push(ranks-1,tmp,aim,origin);
        printf("%c -> %c\n",origin,aim);
        push(ranks-1,origin,tmp,aim);
    }
}    */