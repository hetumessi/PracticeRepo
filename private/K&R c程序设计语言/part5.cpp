//
// Created by 徐绍骞 on 2021/7/11. 一塌糊涂
//
#include "shared.h"
// 例 5.2 该版本getint函数在到达文件末尾时返回EOF，当下一个输入不是数字时返回0
//              当输入中包含一个有意义的数字时返回一个正值(最后一个字符的ASCII码)
// 练习5-1，5-2
int getint(int*pn){
    int c,sign;
    while(isspace(c=getch()));
    if(!isdigit(c)&&c!=EOF&&c!='+'&&c!='-'){
        ungetch(c);
        return 0;
    }
    sign=(c=='-')?-1:1;
    if(c=='-'||c=='+')c=getch();
    if(!isdigit(c)){                      //不加这一段，如果+或-号后面跟的不是数字，getint函数将其视作0的有效表达方式
       ungetch(c);
        return 0;
    }
    for(*pn=0; isdigit(c);c=getch())*pn=*pn*10+(c-'0');
    *pn*=sign;
    if(c!=EOF)ungetch(c);
    return c;
}
int getfloat(float*pf){
    int c,sign,power=1;
    while(isspace(c=getch()));
    if(c!=EOF&&c!='+'&&c!='-'&&!isdigit(c)){
        ungetch(c);
        return 0;
    }
    sign=(c=='-')?-1:1;
    if(c=='+'||c=='-'||c=='.')c=getch();
    if(!isdigit(c)&&c!='.'){
        ungetch(c);
        return 0;
    }
    for(*pf=0; isdigit(c);c=getch())(*pf)=*pf*10+(float)(c-'0');
    if(c=='.')c=getch();
    for(; isdigit(c);c=getch()){
        *pf=*pf*10+(float)(c-'0');
        power*=10;
    }
    *pf/=(float)(sign*power);
    return c;
}
/*例5.4 一个不完善的存储分配程序
  第一个函数alloc(n)返回一个指向n个连续字符存储单元的指针，alloc函数的调用者可利用该指针存储字符序列
  第二个函数afree(p)释放已分配的存储空间，以便以后重用
  (不完善是指对afree的调用次序必须与其对应的alloc相反，第一个afree的是最后一个alloc的空间，
  即以栈的形式进行存储空间管理) (标准库中实现类似功能的malloc和free则没有上述限制)
  该程序最容易的实现方法是alloc函数对一个大字符数组allocbuf中空间进行分配 */
// 由于alloc和afree处理的对象是指针而不是数组下标，因此无需将数组给其他文件的函数使用
// 实际实现存储区数组时是不需要名字的，可以直接通过malloc向操作系统申请一个指向无名存储块的指针即可
static char allocbuf[ALLOCSIZE];                 //alloc使用的存储区，从下标0开始
static char* allocp=&allocbuf[0];                   //用于表示当前剩余空间的指针
char* alloc(int n){                                          //返回n个字符存储空间
    if(allocbuf+ALLOCSIZE-allocp>=n){        //如果空闲空间足够
        allocp+=n;                                            //存储区指针后移
        return allocp-n;                                     //返回申请分配空间的起始地址
    } else return nullptr;                                  //空间不足则分配空指针(也可以返回0)
}
void afree(char*p){                                                             //释放p所指向的申请分配空间
    if(p>=allocbuf&&p<allocbuf+ALLOCSIZE)allocp=p;     //如果指针p没有超过存储区边界，则将剩余空间的指针移回到p处
}
// 练习5-3，5-4，5-5
void mystrcat(char*s,char*t){
    if(s)while(*++s!='\0');
    while((*s++=*t++));
}
int mystrend(char*s,char*t){
    int len=(int)strlen(t)+1;
    if(!*s)return 0;
    while(*++s!='\0');
    while(*++t!='\0');
    while(*s--==*t--)len--;
    if(!len)return 1;
    else return 0;
}
char* mystrncpy(char*s,char*t,int n){
    char* tmp=s;
    if(n<1)return tmp;
    while(n>0&&(*s++=*t++))n--;
    if(!n)return tmp;
    else while(--n)*s++='\0';
    return tmp;
}
char* mystrncat(char*s,char*t,int n){
    char* tmp=s;
    if(*s)while(*++s);
    while(n>0&&(*s++=*t++))n--;
    *s='\0';
    return tmp;
}
int mystrncmp(char*s,char*t,int n){
    if(n<1)return -1;
    if(*s<*t)return *s-*t;
    else if(*s>*t)return 0;
    while(n>0&&*s&&*++s==++*t)n--;
    if(*s>*t||!n||!*s)return 0;
    else if(*s<*t)return *s-*t;
    return 0;
}
// 练习5-6
int getline_ptr(char*s,int lim){
    int c;
    char*tmp=s;
    while(lim--&&(c=getchar())!=EOF&&c!='\n')*s++=(char)c;
    if(c=='\n')*s++='\n';
    *s='\0';
    return (int)strlen(tmp);
}
char* reverse_ptr(char*s){
    int len=(int) strlen(s);
    char *tmp= new char[len+1],*ttmp=tmp;
    if(!*s)return s;
    while(*++s);
    while(len>0&&(*tmp++=*--s))len--;
    *tmp='\0';
    return ttmp;
}
char** reverse_ptr(char**s){
    int len=0;
    while(**++s)len++;
    char **tmp= new char*[len+1],**ttmp=tmp;
    while(len>=0&&(*tmp++=*--s))len--;
    return ttmp;
}
char* itoa_ptr(int n,char*s,int m){
    char* tmp=s;
    int sign=n>0?1:0;
    if(!sign)n=-(n+1);
    do *s++=(char)(n%10+'0');
    while(n/=10);
    if(!sign)*tmp+=1,*s='-';
    int len= (int)strlen(tmp);
    if(len<m)while(m>len&&(*++s=' '))m--;
    return reverse_ptr(tmp);
}
int atoi_ptr(char*s){
    int result=0,sign=*s=='-'?-1:1;
    if(*s=='+'||*s=='-')s++;
    while(isdigit(*s++))result=10*result+*(s-1)-'0';
    return result*sign;
}
int strindex_ptr(char*s,char*t){
    int i,j,lens=(int)strlen(s),lent= (int)strlen(t);
    for(i=0;i<lens;i++){
        for(j=0;*(t+j)==*(s+j+i);j++);
        if(j==lent)return i;
    }
    return -1;
}
int getop_ptr(char*s){
    static int c;
    char* tmp=s;
    while((*s=(char)(c=getch()))==' '||c=='\t');
    *(s+1)='\0';
    if(!isdigit(c)&&c!='.'&&c!='+'&&c!='-')return c;
    if((c=='+'||c=='-')){
        if(!isdigit(c=getch()))return *tmp;
        ungetch(c);
    }
    if(isdigit(c))while(isdigit(*s++=(char)c))c=getch();
    if(*s=='.')while(isdigit(*s++=(char)getch()))c=getch();
    *s='\0';
    s=tmp;
    return NUMBER;
}
// 例5.6，5.11 练习5-14，5-15，5-16，5-17，5-13
// UNIX程序sort的一个简化版本
/* 该程序按字母顺序对由文本行组成的集合进行排序处理长度不一的文本行，
 * 并且与整数不同的是它们不能在单个运算中完成比较或移动操作
 * 因此需要一个能够高效、方便地处理可变长度文本行的数据方法，引入指针数组处理此问题
 * 当交换次序颠倒的文本行时，实际交换的是指针数组中与这两个文本行相对应的指针，而不是文本行本身*/
// 首先考虑数据结构、以及输入输出函数
void onlyd_a_s(char*),writelines(char**,int),swaplines(char**,int,int);
void qsortlines(char**, int, int,int (*)(void*,void*));
int readlines(char**,int,int),numcmp(const char*,const char*),loweqhighcmp(const char*s1,const char*s2);
char *lineptr[MAXLINES];                                                //最多存储MAXLINES个文本行
int sortlinemain(int argc,char *argv[]){
    int numeric,reverse,loweqhigh,content;
    numeric=reverse=loweqhigh=content=0;
    while(argc-->0&&**++argv=='-')
        while(*++*argv)
            switch (**argv) {
                case 'n':
                    numeric=1;break;
                case 'r':
                    reverse=1;break;
                case 'f':
                    loweqhigh=1;break;
                case 'd':
                    content=1;break;
                default:
                    cout<<"sort:illegal option"<<" -"<<**argv;break;
            }
    int nlines=readlines(lineptr,MAXLINES,content);
    if(argc!=1)cout<<"Usge:find -r -n pattern"<<endl;
    if(nlines>=0){
        qsortlines(lineptr,0,nlines-1,\
                   (int (*)(void*,void*))(numeric?numcmp:((loweqhigh)?loweqhighcmp:strcmp)));
        if(reverse)writelines(reverse_ptr(lineptr),nlines);
        else writelines(lineptr,nlines);
        return 0;
    } else{     //readlines返回-1的情况
        cout<<"error:intput too big to sort"<<endl;
        return 1;
    }
}
void onlyd_a_s(char*s){
    if(!*s)return;
    char*tmp=s;
    while(*++s)if(isalnum(*s)||*s==' ')*++tmp=*s;
    *++tmp='\0';
}
int readlines(char**lineptr,int nlines,int content){
    int len,maxlines=0;
    char*p,nline[MAXLINE];                                              //每个文本行最长MAXLINE个字符
    while((len= getline_ptr(nline,MAXLINE))>0)
        if(maxlines>=nlines||(p=alloc(len))== nullptr)return -1;//超过最大行数或者空闲空间不足
        else {
            nline[len-1]='\0';                                                   //删除换行符
            if(content)onlyd_a_s(nline);
            strcpy(p,nline);                                                    //注意是strcpy不是strcat
            lineptr[maxlines++]=p;
        }
    return maxlines;
}
// 练习5-7
int readlines_s(char**lineptr,int nlines,char s[],int nline){
    int len,maxlines=0,maxline=0;
    char tline[MAXLINE];
    while((len= getline_ptr(tline,MAXLINE))>0)
        if(maxlines>=nlines||maxline>=nline)return -1;
        else{
            tline[len-1]='\0';
            strcpy(s,tline);
            *lineptr++=s;
        }
    return maxlines;
}
void writelines(char**lineptr,int nlines){
    while(nlines-->0)cout<<*lineptr++<<endl;
}
//将之前的快速排序算法操作的数据类型改为char*,并调用strcmp将数组元素和枢轴进行比较
void swaplines(char*t[],int a,int b){
    char* tmp;
    tmp=t[a],t[a]=t[b],t[b]=tmp;
}
typedef int (*comp)(void*,void*);
void qsortlines(char**lineptr, int left, int right,comp comp){ //此程序只要关注指针数组和函数指针用法
    int i,last;                                                                                       //不考虑输入无法转化成整型等错误情况
    if(left>=right)return;
    swaplines(lineptr,left,(left+right)/2);
    last=left;
    for(i=left+1;i<=right;i++)if(comp(lineptr[i],lineptr[left])<0)
        swaplines(lineptr,left,last);
    qsortlines(lineptr, left, last - 1,comp);
    qsortlines(lineptr, last + 1, right,comp);
}
/* 排序(交换类)算法通常可以分为三个不同的部分：
    判断任意两个对象之间次序的比较操作(比较)
    颠倒对象次序的交换操作(交换)
    比较和交换对象直到所有对象都按正确次序排列(遍历)
    将三个部分使用不同的方法组合可以实现不同的排序方式*/
int numcmp(const char*s1,const char*s2){
    double v1= atof(s1),v2=atof(s2);
    if(v1<v2)return -1;
    else if(v1>v2)return 1;
    else return 0;
}
int loweqhighcmp(const char*s1,const char*s2){
    for(; tolower(*s1)==tolower(*s2);s1++,s2++);
    if(*s1)return *s1-*s2;
    else return 0;
}
// 练习5-17是增加字段处理，应该可以在读入行的时候处理，具体不知道怎么实现
// 练习5-13
int tail(int argc,char*argv[]){
    char *s=new char[MAXLINE];
    int n=0,nlines= readlines_s(lineptr,MAXLINES,s,MAXLINE);
    char**t=lineptr;
    if(argc!=3)n=10;
    else if(!strcmp(*++argv,"-n"))if(**++argv=='-')while(isdigit(**++argv))n=10*n+**argv-'0';
    if(nlines>=0){
        while(*t++);
        while(n-->0)writelines(t-n,nlines);
        return 0;
    } else{
        cout<<"error:intput too big"<<endl;
        return 1;
    }
}
// 例5.7，练习5-8，5-9
char daytab[2][13]={     //定义为char类型是为了说明在char类型变量中存放较小非字符整数也是合法的
        {0,31,28,31,30,31,30,31,31,30,31,30,31},
        {0,31,29,31,30,31,30,31,31,30,31,30,31}
};
int day_of_year(int year,int month,int day){    //将某年某月某日转换成某年第几天
    if(year<0)return -1;
    int isleap=((!(year%4)&&year%100)||!(year%400));
    if(!(month>0&&month<13&&day>0&&day<=daytab[isleap][month]))return -1;
    for(int i=1;i<month;i++)day+=daytab[isleap][i];
    return day;
}
void month_day(int year,int days,int *pmonth,int *pday){ //将某年第几天转换成某月某日的形式
    if(days<0)return;
    int i,isleap=((!(year%4)&&year%100)||!(year%400));
    if((isleap&&days>366)||(!isleap&&days>365))return;
    for(i=1;days>daytab[isleap][i];i++)days-=daytab[isleap][i];
    *pmonth=i,*pday=days;
}
int day_of_year_ptr(int year,int month,int day){
    int isleap=((!(year%4)&&year%100)||!(year%400));
    while(month-->0)day+=*(*(daytab+isleap)+month);
    return day;
}
void month_day_ptr(int year,int days,int *pmonth,int *pday){
    *pmonth=1;
    int isleap=((!(year%4)&&year%100)||!(year%400));
    while(days>*(*(daytab+isleap)+*pmonth))days-=*(*(daytab+isleap)+(++*pmonth));
    *pday=days;
}
// 例5.10 echo程序和模式查找程序的命令行参数模拟
//UNIX程序通过命令行将argv字符串传给main函数的两个命令行参数
int echomain(int argc,char*argv[]){
    while(--argc>0)cout<<*++argv<<((argc>1)?" ":"");
    while(--argc>0)printf(argc>1?"%s ":"%s",*++argv);
    return 0;
}
int grepmain(int argc,char*argv[]){                   //不考虑可选参数情况argv中仅有两个字符串(一个程序名一个查找模式)
    char gline[MAXLINE];
    int found=0;
    if(argc!=2){                                                  //argv参数数量不为2的情况
        cout<<"Usge:find pattern"<<endl;            //提醒用户查找格式
        found=-1;                                                //标记为错误状态
    }
    else while(getline_ptr(gline,MAXLINE)>0)     //读取文件并存入gline
        if(strstr(line,argv[1])!= nullptr){           //strstr返回一个指针该指针指向字符串t在字符串s中第一次出现的位置
            cout<<gline;                                        //打印匹配的文本行
            found++;                                             //记录匹配文本行的个数
        }
    return found;                                               //返回匹配文本行个数
}
// 在main函数(grep程序)基础上在argv中加入可选参数字符串-n和-x
int grepmain_nx(int argc,char*argv[]){
    char gline[MAXLINE];
    long lineno=0;
    int except=0,number=0,found=0;
    while(--argc>0&&**++argv=='-')                   //跳过第一个字符串并检查argv字符串的第一个字符是否为'-'(可选参数)
        while(*++*argv)                                       //在可选参数字符串内进行遍历 (需要考虑到-nx，-xn，-xnn等情况)
            switch (**argv) {                                  //处理可选参数 (x或n)
                case 'x':
                    except=1;                                    //expect为真表示-x的情况：打印与模式不匹配的行
                    break;
                case 'n':
                    number=1;                                   //number为真表示-n的情况：在打印行的前面加上行号
                    break;
                default:                                            //处理无效参数的情况
                    cout<<"find:illegal option"<<" -"<<**argv;
                    argc=0,found=-1;
                    break;
            }
    if(argc!=1)cout<<"Usge:find -x -n pattern"<<endl;
    //按照正确的查找模式，在匹配完可选参数后argc应该还剩1，并且argv指向模式字符串
    else while(getline_ptr(gline,MAXLINE)>0){
        lineno++;                                                  //行号计数器
        if((strstr(gline,*argv)!= nullptr)!=except){
    //如果文本行匹配的话strstr(gline,*argv)!=nullptr为真，此时如果except为真，则if表达式为假，不进行打印输出
    //反之只要文本行匹配和except值不相等，则if表达式为真，进行打印
            if(number)cout<<lineno;                       //如果number为真输出行号
            cout<<gline;
            found++;
        }
    }
    return found;
}
// 练习5-10
int exprmain(int argc,char*argv[]){
    stack<int> stk;
    int number,opn1,opn2;
    while(--argc>0&&**++argv){
        number=opn1=opn2=0;
        if(isdigit(**argv)){
            while(isdigit(*(*argv)++))number=10*number+*((*argv)-1)-'0';
            stk.push(number);
        }
        else switch (**argv) {
                case '+':
                    opn1=stk.top(),stk.pop();
                    opn2=stk.top(),stk.pop();
                    stk.push(opn1+opn2);
                    break;
                case '-':
                    opn1=stk.top(),stk.pop();
                    opn2=stk.top(),stk.pop();
                    stk.push(opn2-opn1);
                    break;
                case '*':
                    opn1=stk.top(),stk.pop();
                    opn2=stk.top(),stk.pop();
                    stk.push(opn2*opn1);
                    break;
                case '/':
                    opn1=stk.top(),stk.pop();
                    opn2=stk.top(),stk.pop();
                    if(opn1)stk.push(opn2/opn1);
                    break;
                case '%':
                    opn1=stk.top(),stk.pop();
                    opn2=stk.top(),stk.pop();
                    if(opn1)stk.push(opn2%opn1);
                    break;
                default:
                    cout<<"操作数输入错误"<<endl;
            }
        }
    cout<<"结果是："<<stk.top()<<endl;
    return 0;
}
// 练习5-11，5-12
int detab_tabsize(int argc,char* argv[]){
    int c=getchar(),count=0,tabsize;
    if(argc<2)tabsize=TABSIZE;
    if(argc==2)while(*argv[1]++)tabsize=tabsize*10+*(argv[1]-1)-'0';
    while (c!=EOF){
        count++;
        if(c=='\t')for(int i=count;i<count+count%tabsize;i++)putchar(' ');
        putchar(c);
        c=getchar();
    }
    return 0;
}
void entab_tabsize(int argc,char*argv[]){
    int c,nbspLength, charLength,tabLength,tabsize;
    nbspLength= charLength=tabLength=0;
    if(argc<2)tabsize=TABSIZE;
    if(argc==2)while(*argv[1]++)tabsize=tabsize*10+*(argv[1]-1)-'0';
    while ((c=getchar()) != EOF ){
        if ( c==' ')nbspLength++;
        else if ( c == '\n' ) nbspLength =charLength = 0;
        else if(nbspLength>0){
            tabLength = (tabsize - charLength) % tabsize;
            if(tabLength>0&&nbspLength>=tabLength){
                putchar ( '\t' );
                nbspLength = nbspLength-tabLength;
            }
            if(nbspLength > tabsize){
                while(nbspLength > tabsize){
                    putchar ( '\t' );
                    nbspLength = nbspLength - tabsize;
                }
                charLength=nbspLength;
                while(--nbspLength>0)putchar ( ' ' );
            }else{
                charLength=nbspLength;
                while(--nbspLength>0)putchar ( ' ' );
            }
        }
        putchar ( c );
        charLength++;
        nbspLength = 0;
    }
}
// 例5.12 创建复杂声明：一个程序(dcl)用于将正确的c声明转换为文字描述，
//  另一个程序(dirdcl)完成相反的转换，文字描述从左向右阅读
// 练习5-18，5-19，5-20 不完整
void dcl(),dirdcl(),errmsg(const string&);
char token[MAXTOKEN],Name[MAXTOKEN],datatype[MAXTOKEN],out[MAXLINE];
//token:最后一个记号字符串 Name:标识符名 datatype:数据类型 out:输出串
int gettoken(),tokentype,prevtoken=NO,nexttoken=NO;
//gettoken:返回下一个标记
//tokentype:token的类型，定义了三种类型分别是NAME:标识符,PARENS:函数,BRACKETS:数组
void dclmain(){                                                         //将声明转换为文字描述
    while(gettoken()!=EOF){                                       //主函数中重复执行dcl程序直到文件末尾
        strcpy(datatype,token);                                    //该声明行的第一个记号是数据类型
        *out='\0';                                                          //更新out
        dcl();
        if(tokentype!='\n')errmsg("syntax error");   //认为声明结束后的字符是'\n'
        cout << Name << ":" << out << ' ' << datatype << endl;
    }
}
void dcl(){
    int ns=0;
    while(gettoken()=='*')ns++;                                  //获取标记字符串，统计'*'的个数
    dirdcl();                                                               //dcl中调用dirdcl
    while(ns-->0)strcat(out," pointer to");             //有几个'*'就有几个指针(point to)
}
void dirdcl(){
    int type;
    if(tokentype=='('){                                                 //只有'('表示形式为(dcl)的情况，需要递归处理(先输出括号内)
        dcl();                                                                //dirdcl调用dcl，dcl再调用dirdcl，间接形成了递归调用
        if(tokentype!=')')errmsg("error:missing ')'");
//dircl的调用结束说明tokentype属于gettoken所考虑的其他情况，此时一定是')'
//否则其他它字符要么非法，要么是'\n'就缺少了一个右括号
    } else if(tokentype==NAME)strcpy(Name, token);
//处理name的情况，name在声明中只出现一次
    else errmsg("error:expected Name or (dcl)");
    while((type=gettoken())==PARENS||type==BRACKETS)
//声明中必须先有括号或标识符名才有函数或数组的表示，所以在递归结束后处理函数或数组的情况
// 只需要按顺序输出即可
        if(type==PARENS)strcat(out," function returning");
        else{
            strcat(out," array");
            strcat(out,token);
            strcat(out," of");
        }
}
int gettoken(){                                                      //返回下一个标记
    int c;
    char *p=token;                                                 //定义一个内部变量的字符指针以更改token的内容
    while((c=getch())==' '||c=='\t');
    if(prevtoken||nexttoken){
        if(prevtoken)prevtoken=NO;
        else nexttoken=NO;
        return tokentype;
    }
    if(c=='('){                                                         //圆括号有两种情况，一是将dcl括起来以控制运算顺序
        if((c=getch())==')'){                                      //二是表示函数的情况
        strcpy(token,"()");
        return tokentype=PARENS;
        } else{
            ungetch(c);
            return tokentype='(';
        }
    } else if(c=='['){                                                   //方括号只有一种情况就是标识数组
        for(*p++=(char)c;(*p++=(char)getch())!=']';)     //将方括号内的内容也一并返回
            if(*(p-1)==' '|| !isdigit(*(p-1)))p--;
        *p='\0';                                                           //更新token
        return tokentype=BRACKETS;
    }else if(isalpha(c)){                                             //如果是字母开头的话就是标识符名或数据类型
        for(*p++=(char )c; isalnum(c=getch())||c=='_';)*p++=(char )c;
        ungetch(c);
        if(!strcmp("const",token)){
            while((c=getch())==' '||c=='\t');
            *p++=' ';
            for(*p++=(char )c; isalnum(c=getch())||c=='_';)*p++=(char )c;
        }
        *p='\0';
        return tokentype=NAME;
    }else return tokentype=c;                                   //如果不属于这三种情况则直接将c返回，
}                                                                            // 合法字符'*', ')'和'\n'都在这种情况下返回
void undclmain(){
    int type,braket;
    char temp[MAXTOKEN];
    while(gettoken()!=EOF){                                     //外层循环控制多次进行声明转换
        strcpy(out,token);                                           //每次转换前更新out
        while((type=gettoken())!='\n')                          //内层循环控制声明，输入到'\n'时一次转换结束
            if(type==PARENS||type==BRACKETS)strcat(out,token);//函数或数组放在out后面
            else if(type=='*'){                                         //*放在out前面
                nexttoken=YES;
                braket=gettoken();
                if(braket==PARENS||braket==BRACKETS)
                    sprintf(temp,"(*%s)",out);                    //(sprintf:将模式字符串存入第一个字符数组参数中)
                else if(braket!='\n')sprintf(temp,"*%s",out);
                else break;
                strcpy(out,temp);                                    //事实上只有当下一个记号是() 或[]，才有必要在输出中使用括号
            } else if(type==NAME){                               //数据类型或标识符名放在out前面
                sprintf(temp,"%s %s",token,out);
                strcpy(out,temp);
            } else cout<<"invalid input at "<<token<<endl;
        cout<<out<<endl;                                          //输出out，之前没做处理的单独的左右圆括号直接输出
    }
}
void errmsg(const string& err){
    prevtoken=YES;
    cout<<err<<endl;
}