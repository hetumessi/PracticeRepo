//
// Created by 徐绍骞 on 2021/7/22.
//
// 练习7-1
#include<cstdlib>
#include<cstdarg>
void tohighorlow(char*choice){
    int c;
    while((c=getchar())!=EOF){
            if(!strcmp(choice,"high"))putchar(toupper(c));
            else if(!strcmp(choice,"low"))putchar(tolower(c));
            else putchar(c);
    }
}
// 练习7-2
void print(){
    int count=0,c;
    while((c=getchar())!=EOF){
        if(c=='\n'||count==10){
            if(count==10)putchar('\n');
            count=0;
        }
        if(!isprint(c)){
            printf("(0%o)",c);
            count++;
        }else{
            putchar(c);
            count++;
        }
    }
}
/* 例7.3 以可移植的方式编写可处理变长参数表的函数minprintf
 * 由于重点在于参数的处理，所以函数minprintf只处理格式字符串和参数，格式转换由printf完成
 * 编写minprintf的关键在于如何处理一个甚至连名字都没有的参数表
 * <stdarg.h>中规定的宏对如何遍历参数表进行了定义，使用这些宏可以帮助实现简化的printf函数minprintf*/
//minprintf函数：带有可变参数表的简化的printf函数
// 练习7-3
char*format(char*,char);
void minprintf(char*fmt,...){
    va_list ap;                                  //定义va_list类型的参数指针ap，依次指向每个无名参数
    char*p,*sval;int ival;double dval;void*vval;//指针p用于遍历模式字符串，ival,dval,sval用于接受输入流中的字符
    char pfmt[FMTLEN];
    va_start(ap,fmt);                        //带参宏va_start将ap指向最后一个有名参数fmt的后一个参数，即第一个无名参数
    for(p=fmt;*p;p++) {                     //遍历模式字符串
        if(*p!='%'){                              //如果没有遇到字符'%'则直接输出其中的内容并跳过switch
            putchar(*p);
            continue;
        }
        switch (*++p){                        //默认转换说明的'%'后面只有一个字符
            case'd':case'i':case'o':case'x':case'X':case'u':case'c':
                ival=va_arg(ap,int);
                printf(format(pfmt,*p),ival);
                break;
            case'f':case'e':case'E':case'g':case'G':
                dval=va_arg(ap,double);
                printf(format(pfmt,*p),dval);
                break;
            case's':
                for(sval=va_arg(ap,char*);*sval;sval++)putchar(*sval); //移动ap，返回char*遍历字符串后输出
                break;
            case'p':
                vval=va_arg(ap,void*);
                printf(format(pfmt,*p),vval);
            default:
                putchar(*p);                    //其他情况则直接输出
                break;
        }
    }
    va_end(ap);                                //结束时的清理工作
}
char*format(char*fmt,char c){
    char*p=fmt;
    *p='%',*++p=c,*++p='\0';
    return fmt;
}
//练习7-4
void minscanf(char*fmt,...){
    va_list ap;
    char*p;int*ival;float*dval;char*cval;
    char pfmt[FMTLEN];
    va_start(ap,fmt);
    for(p=fmt;*p;p++){
        if(*p!='%'){
            getchar();
            continue;
        }
        switch (*++p){
            case'd':case'i':case'o':case'x':case'u':
                ival=va_arg(ap,int*);
                scanf(format(pfmt,*p),ival);
                break;
            case'e':case'f':case'g':
                dval=va_arg(ap,float*);
                scanf(format(pfmt,*p),dval);
                break;
            case'c':case's':case'%':
                cval=va_arg(ap,char*);
                scanf(format(pfmt,*p),cval);
                break;
            default:
                getchar();
                break;
        }
    }
    va_end(ap);
}
//练习7-5(不对)
int getop_scanf(double*f){
    double opf;char ops[MAXWORD],opc;
    if(scanf(" %lf",&opf)){
            *f=opf;
            return NUMBER;
        }
    else if(scanf(" %s",ops)){
        if(!strcmp(ops,"sin"))return SIN;
        else if(!strcmp(ops,"exp"))return EXP;
        else if(!strcmp(ops,"pow"))return POW;
        else if(!strcmp(ops,"+"))return'+';
        else if(!strcmp(ops,"-"))return'-';
        else if(!strcmp(ops,"*"))return'*';
        else if(!strcmp(ops,"/"))return'/';
    }
    cout<<"error"<<endl;
    return -1;
}
/* 例7.5 编写将多个文件连接起来的cat程序
 * 如果有命令行参数，参数将被解释为文件名，并按顺序逐个处理
 * 如果没有参数，则处理标准输入 */
void filecopy(FILE*,FILE*);
int catmain(int argc,char*argv[]){
    FILE*fp;
    char*prog=argv[0];                                                     //记下程序名，供错误处理用
    if(argc==1)filecopy(stdin,stdout);                                //如果没有命令行参数，则复制标准输入
    else while(--argc)if(!(fp=fopen(*++argv,"r"))){   //如果fp为空输出错误信息
                fprintf(stderr,"%s: can't open %s\n",prog,*argv);
                exit(1);                                                          //发生错误直接终止程序，并在stderr文件报告错误信息
        }else{
            filecopy(fp,stdout);
            fclose(fp);
        }
    if(ferror(stdout)){                                                       //同理如果stdout流中出现错误，终止程序并报错
        fprintf(stderr,"%s: error writing stdout\n",prog);
        exit(2);
    }
    exit(0);                                                                    //正常终止
}
//filecopy函数:将文件ifp复制到文件ofp
void filecopy(FILE*ifp,FILE*ofp){
    int c;
    while((c=getc(ifp))!=EOF)putc(c,ofp);
}
//例7.7 标准库中的fgets和fputs函数，使用fgets实现getline
char*fgets(char*s,int n,FILE*iop){
    int c;
    char*cs=s;
    while((c=getc(iop))!=EOF)if((*cs++=(char)c)=='\n')break;
    *cs='\0';
    return (cs==s&&c==EOF)?nullptr:s;
}
int fputs(char*s,FILE*iop){
    char c;
    while((c=*s++))putc(c,iop);
    return ferror(iop)?EOF:1;
}
int getline_gets(char*lines,int max){
    if(fgets(lines,max,stdin))return 0;
    else return (int)strlen(lines);
}
// 练习7-6
void cmpfiles(char*name1,char*name2){
    FILE*fp1,*fp2;
    fp1=fopen(name1,"r"),fp2=fopen(name2,"r");
    if(!fp1||!fp2){
        cout<<"文件打开失败"<<endl;
        exit(1);
    }
    char lines1[MAXWORD+1],lines2[MAXWORD+1];
    do{
        fgets(lines1,MAXWORD,fp1);
        fgets(lines2,MAXWORD,fp2);
    }while(!strcmp(lines1,lines2));
    if(ferror(stdout)){
        fprintf(stderr,"标准输出流错误");
        exit(2);
    }
    cout<<lines1<<lines2;
    fclose(fp1), fclose(fp2);
}
//练习7-7
void grepmain_fin(int argc,char*argv[]){
    char gline[MAXLINE];
    long lineno=0;
    FILE*fp;
    int number=0;
    if(--argc>2&&**++argv=='-'){
        if(*++*argv=='n')number=1;
        else{
            cout<<"find:illegal option"<<" -"<<**argv;
            argc=0;
        }
        --argc,++argv;
    }
    if(argc-->1)fp=fopen(*argv++,"r");
    else fp=stdin;
    if(--argc!=1)fprintf(stderr,"Usge:find -x -n filename pattern");
    else while(fgets(gline,MAXLINE,fp)){
            lineno++;
            if(strstr(gline,*argv)!=nullptr){
                if(number)cout<<lineno<<' '<<*(argv-1)<<' ';
                cout<<gline;
            }
        }
}
// 练习7-8
void fileprintpages(char*names[]){
    FILE*fp;
    int c;
    while(*names){
        fp=fopen(*names++,"r");
        if(!fp){
            fprintf(stderr,"文件:%s打开失败",*names);
            continue;
        }
        do{
            c=fgetc(fp);
            if(c!=EOF)putchar(c);
            else putchar('\f');
            if(ferror(stdout)){
                fprintf(stderr,"输出流错误");
                exit(1);
            }
        }while(c!=EOF);
    }
}
// 练习7-9
#define Isupper(c) (((c)>='A'&&(c)<='Z')?1:0)