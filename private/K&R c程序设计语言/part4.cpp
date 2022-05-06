//
// Created by 徐绍骞 on 2021/7/3.
//
#include <stack>
#include "shared.h"
// 例 4.1 练习4-1 模式匹配(朴素)
int strindex(char s[],char t[]){
    int i,j,k;
    for(i=0;s[i]!='\0';i++){
        for(j=i,k=0;t[k]!='\0'&&s[j]==t[k];j++,k++);
        if(k>0&&t[k]=='\0')return i;
    }
    return -1;
}
int strrindex(char*s,char*t){
    int i,j,k;
    for(i= (int)strlen(s)-1;s[i]!='\0';i--){
        for(j=i,k=(int) strlen(t)-1;t[k]!='\0'&&s[j]==t[k];j--,k--);
        if(t[k]=='\0')return i;
    }
    return -1;
}
// 例 4.2
double atof(char* s){
    double var=0,power=1;
    int i,sign=1;
    for(i=0; isspace(s[i]);i++);
    if(s[i]=='+'||s[i]=='-')sign=(s[i++]=='-')?-1:1;
    for(; isdigit(s[i]);i++)var=10*var+s[i]-'0';
    if(s[i]=='.')i++;
    for(; isdigit(s[i]);i++){
        var=10*var+s[i]-'0';
        power*=10;
    }
    return sign*var/power;
}
double atoef(char s[])
{
    double val, power;
    int i, sign, n;
    n = 0;
    for(i = 0; isspace(s[i]); ++i);
    sign=(s[i] == '-') ? -1:1;
    if(s[i] == '+' || s[i] == '-')++i;
    for(val = 0.0; isdigit(s[i]); i++)val = 10.0*val + (s[i] - '0');
    if(s[i] == '.')i++;
    for(power = 1.0; isdigit(s[i]); i++){
        val = 10.0*val+(s[i]-'0');
        power *= 10.0;
    }
    val = sign * val/power;
    if(s[i] == 'e' || s[i] == 'E'){
        i++;
        sign=(s[i] == '-') ? -1:1;
        if(s[i] == '+' || s[i] == '-')i++;
        for( ; isdigit(s[i]); ++i)n = 10*n + (s[i]-'0');
        for( ; n>0; --n){
            if(sign > 0)val = val*10.0;
            else val = val*0.1;
        }
    }
    return val;
}
// 例4.3 逆波兰运算器 练习4-3，4-4，4-5，4-6，4-7，4-8，4-9，4-10，4-11
/* 程序中经常出现这样的情况：程序无法确定它已经读入的输入是否足够，除非超前地多读入一些输入，
 读入一些字符的以合成一个数字的情况便是一例：在看到第一个非数字字符之前，已经读入的数的完整性
 是不能确定的。由于程序要超前读入一个字符，这样就导致最后有一个字符不属于当前要读入的数
    因此，如果能"反渎"不需要的字符，该问题就可以得到解决。
    每当程序多读入一个字符时，就将其压回输入中，对代码其余部分而言就好像没有读入该字符一样 */
stack<double> st;
int buf[BUFSIZE],onebuf=0;         //缓冲区(也是类似于栈的结构)
int bufp=0,sp=0;                           //缓冲区下标变量(共享), 栈顶指针(下标)
// 缓冲区需要设置为int, 否则程序无法处理压回的EOF(char转int在不同机器无法确定是算术移位还是逻辑移位

// 数组模拟栈
double val[MAXVAL];
void push(double f){
    if(sp<MAXVAL)val[++sp]=f;
    else printf("error: stack full, can't push %g\n",f);
}
double pop(){           //返回栈顶的值
    if(sp>0)return val[sp--];
    else printf("error: stack empty\n");
    return 0;
}
double top(){
    return val[sp];
}
void copy(double *d){
    *d=top();
}
void exchange(){
    double tmp=val[sp];
    val[sp]=val[sp-1];
    val[sp-1]=tmp;
}
void clear(){
    for(double &i:val)i=0;
}
int getch(){                                               //getch函数用于读入下一个待处理的字符
    return (bufp>0)?buf[--bufp]:getchar();          //缓冲区下标大于0时读取缓冲区中的字符
}
void ungetch(int c){                                         //ungetch函数用于将字符放回到输入中
    if(bufp>=BUFSIZE)cout<<"ungetch:too many characters"<<endl;
    else buf[bufp++]=c;
}
int getch_one_neof(){
    if(onebuf){
        onebuf=0;
        return onebuf;
    }
    return getchar();
}
void ungetch_one_neof(int c){
    if(onebuf)cout<<"缓冲字符还未读取"<<endl;
    else onebuf=c;
}
void ungets(char*s){
    for(int i=(int)strlen(s)-1;i>0;i++)ungetch(s[i]);
}
int getop(char*s){                      //这个问题的特殊之处在需要将连续的多个数字字符作为一个操作数输出
    int i;
    static int c;
    while((s[0]=(char)(c=getch()))==' '||c=='\t');            //s[0]为输入流中第一个非空字符
    s[1]='\0';
    if(!isdigit(c)&&c!='.'&&c!='+'&&c!='-'){
        if(c=='s'&&getch()=='i'&&getch()=='n')return SIN;
        else if(c=='e'&&getch()=='x'&&getch()=='p')return EXP;
        else if(c=='p'&&getch()=='o'&&getch()=='w')return POW;
        else return c;
    }
    i=0;
    if(c=='-'||c=='+'){                                                     //剩下的从下标1开始输入
        s[++i]=c=getch();
        if(!isdigit(c))return s[0];
    }
    if(isdigit(c))while(isdigit(s[++i]=c=getch()));      // =是右结合
    if(c=='.')while(isdigit(s[++i]=c=getch()));
    s[i]='\0';
    return NUMBER;
}
void calculatormain(){
    int type;
    double num1,num2,op,recent,srecent,v[26];           //srecent 用于保存前一个字符
    for(double&i:v)i=0;
    char s[MAXOP];
    double f;
//    while((type=getop(s))!=EOF){
//    while((type=getop_ptr(s))!=EOF){
    while((type=getop_scanf(&f))!=EOF){
        switch(type){
            case NUMBER:
//                push(atof(s));
//                st.push(atof(s));                         //将s转为double类型
                st.push(f);
                break;
            case '+':
//                push(pop()+pop());
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();
                st.push(num1+num2);
                break;
            case '-':
//                op=pop();
//                push(pop()-op);
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();                  //如果直接使用pop()返回栈顶元素的话，需要注意将左右操作数交换
                st.push(num2-num1);                //使用先入栈的-后入栈的
                break;
            case '*':
//                push(pop()*pop());
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();
                st.push(num1*num2);
                break;
            case '/':
//                op=pop();
//                if(op)push(pop()/op);
//                else printf("error: zero divisor\n");
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();
                if(num1)st.push(num2/num1);        //除法与减法类似，需要注意左右操作数顺序
                else cout<<"除0错误"<<endl;
                break;
            case '%':
//                op=pop();
//                if(op)push((int)pop()%(int)op);
//                else printf("zero error")
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();
                if(num1)st.push((int)num2%(int)num1);
                else cout<<"模0错误"<<endl;
                break;
            case '=':
                if(islower(srecent)){
                    num1=st.top(),st.pop();
                    v[(int)srecent-'a']=num1;
                }else cout<<"没有变量可用于赋值"<<endl;
                break;
            case SIN:
                num1=st.top(),st.pop();
                if(num1>=0)st.push(sin(num1));
                else cout<<"负数没有正弦值"<<endl;
                break;
            case EXP:
                num1=st.top(),st.pop();
                st.push(exp(num1));
                break;
            case POW:
                num1=st.top(),st.pop();
                num2=st.top(),st.pop();
                st.push(pow(num2,num1));
                break;
            case '\n':
//                printf("结果是:%g\n",pop());
                recent=num1=st.top();
                st.pop();
                if(st.empty())cout<<"结果是:"<<num1<<endl;
                else cout<<"结果错误"<<endl;
                break;
            default:
                if(type>='a'&&type<='z'&&type!='v')st.push(v[type-'a']);
                else if(type=='v')st.push(recent);
                else cout<<"结果错误"<<endl;
                break;
        }
        srecent=type;
    }
}
int getline(int maxline,char*s){
    int i,c;
    for(i=0;(c=getchar())!=EOF&&c!='\n'&&i<maxline-1;)s[i++]=(char)c;
    s[i]='\0';
    return i;
}
void calculatormain_getline(){
    int i,k;
    double num1,num2;
    char s[MAXOP],tmp[MAXOP];
    while(getline(MAXOP,s)>0){
        for(i=0;i<strlen(s);i++){
            for(;s[i]==' '||s[i]=='\t';i++);
            if((isdigit(s[i]))||(isdigit(s[i+1])&&(s[i]=='+'||s[i]=='-'||s[i]=='.'))){
                for(k=0; isdigit(s[i]);i++)tmp[k++]=s[i];
                if(s[i]=='.')i++;
                for(; isdigit(s[i]);i++)tmp[k++]=s[i];
                tmp[k]='\0';
                st.push(atof(tmp));
            }
            else if(s[i]=='-'||s[i]=='+'||s[i]=='/'||s[i]=='*'||s[i]=='%'){
                switch (s[i]) {
                    case '+':
                        num1 = st.top(), st.pop();
                        num2 = st.top(), st.pop();
                        st.push(num1 + num2);
                        break;
                    case '-':
                        num1 = st.top(), st.pop();
                        num2 = st.top(), st.pop();
                        st.push(num2 - num1);
                        break;
                    case '*':
                        num1 = st.top(), st.pop();
                        num2 = st.top(), st.pop();
                        st.push(num1 * num2);
                        break;
                    case '/':
                        num1 = st.top(), st.pop();
                        num2 = st.top(), st.pop();
                        if (num1)st.push(num2 / num1);
                        else cout << "除0错误" << endl;
                        break;
                    case '%':
                        num1 = st.top(), st.pop();
                        num2 = st.top(), st.pop();
                        if (num1)st.push((int)num2%(int)num1);
                        else cout << "模0错误" << endl;
                        break;
                    default:
                        cout << "输入错误" << endl;
                        break;
                }
            }
        }
        num1=st.top(),st.pop();
        if(st.empty())cout<<"结果是："<<num1<<endl;
        else cout<<"结果错误"<<endl;
    }
}
// 例4.10 递归，快速排序！
void printd(int n){
    if(n<0){
        putchar('-');
        n=-n;
    }
    if(n/10)printd(n/10);                                   //递归和堆栈是一个道理
    putchar(n%10+'0');
}
int testarray[]={1,4,5,32,41,324,2,54,138,91};
int partition(int t[],int start,int end){                   //进行一趟排序
    int pivot=t[start];
    if(!t||start<0||start>end)return -1;
    while(start<end){
        while(t[end]>=pivot&&start<end)end--;
        t[start]=t[end];
        while(t[start]<pivot&&start<end)start++;
        t[end]=t[start];
    }
    t[start]=pivot;
    return start;
}
void quicksort(int t[],int start,int end){                      //递归
    if(end-start<1)return;
    int pivot=partition(t,start,end);
    if(pivot>start+1)quicksort(t,start,pivot-1);
    if(pivot<end-1)quicksort(t,pivot+1,end);
}
void swap(int t[],int a,int b){
    int tmp;
    tmp=t[a],t[a]=t[b],t[b]=tmp;
}
void qsort(int t[],int start,int end){                                       //KR书上的快速排序
    int pivot,i;
    if(end<=start)return;                                                       //若数组元素数小于2，不进行任何操作
    swap(t,start,(start+end)/2);                                       //划分子集的元素(枢轴)移动到v[0]
    pivot=start;
    for(i=start+1;i<=end;i++)if(t[i]<t[start])swap(t,++pivot,i);    //划分子集
    swap(t,start,pivot);                                                             //恢复枢轴元素
    qsort(t,start,pivot-1);
    qsort(t,pivot+1,end);
}
// 练习4-12
char* itoa_rec(int n,char s[]){
    static int i=0,sign;
    if((sign=n)<0){
        n=-n;
        s[i++]='-';
    }
    if(n/10)itoa_rec(n/10,s);
    s[i++]=n%10+'0';                    //递归调用之后再处理元素，元素顺序与输入的顺序相同(栈顶元素已出栈)
    return s;
}
void reverse_rec(char*s,char*t){
    static int i=0;
    t[i]=s[strlen(s)-1-i],i++;           //递归调用之前处理元素，元素顺序与输入顺序相反
    if(i==strlen(s))return;
    reverse_rec(s,t);
}
