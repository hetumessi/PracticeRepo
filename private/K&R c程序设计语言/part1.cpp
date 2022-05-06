//
// Created by 徐绍骞 on 2021/6/15.
//
#include <string>
#include "shared.h"
int Max=0;
char line[MAXLINE],longest[MAXLINE],tmpca[MAXLINE],pattern[]="oulf";;
// 练习1-3，1-4，1-15
void Fahr(){
    float fahr,celsius;
    printf("titile:华氏温度转换\n华氏度\t摄氏度\n");
    for (fahr = LOWER; fahr <= UPPER; fahr+=step){
        celsius = (5.0 / 9.0)*(fahr - 32);
        printf("%3.0f \t%6.2f\n", fahr, celsius);
    }
}
void Celsius(){
    float fahr,celsius;
    printf("titile:摄氏温度转换\n摄氏度\t华氏度\n");
    for(celsius=LOWER; celsius <= UPPER; celsius+=step){
        fahr=32+(9.0/5.0)*celsius;
        printf("%3.0f \t%6.2f\n",celsius,fahr);
    }
}
// 练习1-5
void reversefahr(){
    float fahr,celsius;
    printf("titile:逆序输出华氏温度转换\n华氏度\t摄氏度\n");
    for (fahr = UPPER; fahr >= LOWER; fahr-=step){
        celsius = (5.0 / 9.0)*(fahr - 32);
        printf("%3.0f \t%6.2f\n", fahr, celsius);
    }
}
// 练习1-6，1-7，1-8
void putfile(){
    int count=0,voidcount=0;
    printf("EOF的值为：%d",EOF);
    for(;int c=getchar(); count++) {
        printf("输入第%d字符是%d，",count,c);
        if(c=='\n'||c==' '||c=='\t')voidcount++;
        printf("空白字符%d个 \n",voidcount);
    }
    printf("共输入%d个字符",count);
}
// 练习1-9，1-10
void instead(){
    int c=getchar(),insteadcount=0;
    for(;c;){
        if(c==' '||c=='\t'||c=='\b'||c=='\\')insteadcount++;
        else insteadcount=0;
        if(insteadcount > 1)c=getchar();
        else{
            switch (c) {
                case ' ':putchar('\\'); putchar('s');
                case '\t':putchar('\\'); putchar('t');
                case '\b':putchar('\\'); putchar('b');
                case '\\':putchar('\\');
                default:putchar(c);
            }
            c=getchar();
        }
    }
}
// 练习1-12,1-13
void vertical(int* array,int len)    //clion环境运行失败
{
    int maxValue;
    int i,j;
    for(i=0;i<len;i++)if(array[i]>maxValue)maxValue=array[i];
    printf("\n  y/num↑\n");
    for(i = maxValue + 1; i > 0; i--){
        printf("%8d|_  ", i);
        for(j = 0; j < len; j++){
            if(array[j] == i)printf(" ___    ");
            else if(array[j] >= i)printf("|   |   ");
            else if(array[j] == i-1)printf(" (%d)    ",array[j]);
            else printf("        ");}
    }
    printf("\n");
    printf("       0");
    for(i = 0; i < len + 1; i++)printf("|___|___");
    printf("|___→\n");
    for(i = 0; i< (2 * len); i++)printf("\t");
    printf("\tx/word\n\t ");
    for(i = 0; i < len; i++)printf("   word%d",i+1);
    printf("\n\n");
}
void horizontal(int* array,int max,int len){
    int i,j;
    for(i=0;i<len;i++){
        printf("word%6d|",i+1);
        for(j=0;j<=array[i];j++)printf("___");
        printf("|");
        putchar('\n');
    }
    printf("\t\t");
    for(i=0;i<len;i++)printf(" %d ",i);
}
void onerowoneword(){
    int i,j,k,state=Out,c=getchar(),words=0,maxvalue;
    int wordarray[10];
    for(i=0;i<10;i++)wordarray[i]=0;
    for(;c;){
        if(c=='\n'||c==' '||c=='\t'){
            state=Out;
            putchar(',');
            c=getchar();
        }else{
            if(words==10&&state==Out)break;
            if(state==Out) {
                state = In;
                words++;
            }
            putchar(c);
            wordarray[words-1]++;
            c=getchar();
        }
    }
    printf("\n共输入%d个单词\n",words);
    printf("单词长度分别为:\n");
    for(i=0;i<words;i++)if(wordarray[i]>maxvalue)maxvalue=wordarray[i];
    for(i=0;i<24;i++)printf("——");
    putchar('\n');
    for(i=0;i<words;i++)printf("|word%2d|\t",i+1);
    putchar('\n');
    for(i=0;i<words;i++)printf("|%5d    |\t",wordarray[i]);
    putchar('\n');
    for(i=0;i<24;i++)printf("——");
    putchar('\n');
    for(i=0;i<words;i++)if(wordarray[i]>maxvalue)maxvalue=wordarray[i];
//    vertical(wordarray,words);
    horizontal(wordarray,maxvalue,words);
}
// 例1.6
void digitappear(){
    int c=getchar(),i,count=0;
    int digit[10];
    for(i=0;i<10;i++)digit[i]=0;
    for(;c;){
        if(c>='0'&&c<='9') {
            digit[c - '0']++, count++;
        }
        c=getchar();
        if(count==10)break;
    }
    printf("digits=");
    for(i=0;i<9;i++)printf("%d,",digit[i]);
    printf("%d",digit[9]);
}// 例1.9，练习1-17,1-18,1-19
int getline_delspace_fold(int maxline);
void copy(char* to,char* from);
char* reverse(char* s);
void charmain(){
    int len;
    extern int max;
    extern char line[MAXLINE],longest[MAXLINE];
//    while ((len= getline_delspace_fold(MAXLINE)) > 0){
    while ((len= getline_ptr(line,MAXLINE)) > 0){
        if(len>10){
            for(int i=0;i<len&&line[i]!='\n';i++)putchar(line[i]);
            for(int i=0;i< strlen(line);i++)putchar(reverse(line)[i]);
        }
//    while((len= get_withoutandor(line,MAXLINE))>0){
//        if(len>10&&strindex(line,pattern)!=-1)for(int i=0;i<len;i++)putchar(line[i]);
//        if(len > Max){
//            Max=len;
//            copy(longest,line);
//        }
    }
}
int getline_delspace_fold(int maxline){    //读取文件流中第一行
    int c,i,j=0,k,l=0,nsp=0;
    extern char line[MAXLINE];
    for(i=0;((c=getchar())!=EOF&&c!='\n')&&i<maxline-2;i++){
        line[j++]=c;
        l++;
        if(l==FOLDCOMP){
            for(k=j;line[k]==' '&&line[k]=='\t'&&k>=0;k--){
                nsp++;
                if(k==0)return i-nsp;
            }
            j-=nsp;
            line[j++]='\n';
            l=0;
        }
    }
    line[j]='\0';
    return i;    //返回读取行长度
}
void copy(char* to,char* from){
    int i=0;
    while((to[i]=from[i])!='\0')i++;
}
char* reverse(char *s){
    int len= strlen(s);
    extern char tmp[MAXLINE];
    for(int i=0;i<MAXLINE;i++)tmpca[i]=0;
    for(int i=0;i<len;i++){
        tmpca[len - i - 1]=s[i];
    }
    return tmpca;
}
// 练习1-20,1-21
void detab(int argc,char* argv[]){
    int c=getchar(),count=0,tabsize;
    while (c!=EOF){
        count++;
        if(c=='\t')for(int i=count;i<count+count%8;i++)putchar(' ');
        putchar(c);
        c=getchar();
    }
}
void entab(){
    int c;
    int nbspLength = 0;
    int charLength = 0;
    int tabLength = 0;
    while ((c=getchar()) != EOF ){
        if ( c==' ')nbspLength++;
        else if ( c == '\n' ){
            nbspLength = 0;
            charLength = 0;
        }
        else if(nbspLength>0){
            tabLength = (TABSIZE - charLength) % TABSIZE;
            if(tabLength>0&&nbspLength>=tabLength){
                putchar ( '\t' );
                nbspLength = nbspLength-tabLength;
            }
            if(nbspLength > TABSIZE){
                while(nbspLength > TABSIZE){
                    putchar ( '\t' );
                    nbspLength = nbspLength - TABSIZE;
                }
                charLength=nbspLength;
                while(nbspLength>0){
                    putchar ( ' ' );
                    nbspLength--;
                }
            }else{
                charLength=nbspLength;
                while(nbspLength>0){
                    putchar ( ' ' );
                    nbspLength--;
                }
            }
        }
        putchar ( c );
        charLength++;
        nbspLength = 0;
    }
}
// 练习1-23,1-24
void delcomment(){
    int c,d;
    while((c=getchar())!=EOF) {
        if (c == '/'){
            if((d=getchar())=='*'){
                while(getchar()!='*'&&getchar()!='/')getchar();
                c=getchar();
            }else if(d=='/'){
                while((c=getchar())!='\n') getchar();
                c=getchar();
            }
        }
        putchar(c);
    }
}
int judgestate(int,int*,char,char);
void bracketerror(){
    int c,circle,big,square;
    circle=big=square=Out;
    while((c=getchar())!=EOF){
        if(judgestate(c,&circle,'(',')')==-1||judgestate(c,&big,'{','}')==-1||judgestate(c,&square,'[',']')==-1){
            printf("\nerror\n");
            break;
        }
        putchar(c);
    }
}
int judgestate(int i,int* state,char s1,char s2){
    if(i==s1)*state=In;
    if(i==s2){
        if(*state==Out)return -1;
        else if(*state==In)*state=Out;
    }
    return 0;
}