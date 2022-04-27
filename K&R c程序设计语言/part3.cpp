//
// Created by 徐绍骞 on 2021/6/25.
//
// 练习3-1
int binsearch(int x,int v[],int n){
    int low,high,mid;
    low=0,high=n-1;
    while (low<=high){
        mid=(high+low)/2;
        if(v[mid]>x)high=mid-1;
        else if(v[mid]<x)low=mid+1;
        else return  mid;
    }
    return -1;
}
int binsearch_onejudge(int x,int v[],int n){
    int low,high,mid;
    low=0,high=n-1,mid=(low+high)/2;
    while(v[mid]!=x&&low<=high){
        if(v[mid]<x)low=mid+1;
        else high=mid-1;
        mid=(low+high)/2;
    }
    if(v[mid]==x)return mid;
    return -1;
}
int goldensearch(int x,int v[],int n){
    int low,high,mid;
    low=0,high=n-1;
    while (low<=high){
        mid=low+0.618*(high-low);
        if(v[mid]>x)high=mid-1;
        else if(v[mid]<x)low=mid+1;
        else return  mid;
    }
    return -1;
}
// 例 3.4
void countwsdo(){
    int c,n=0,nwhite,ndigit[10],nother;
    for(int i=0;i<10;i++)*(ndigit+i)=0;
    while((c=getchar())!=EOF&&n<20){
        n++;
        switch(c) {
            default:
                nother++;
                break;
            case '0':case '1':case '2':case '3':case '4':
            case '5':case '6':case '7':case '8':case '9':
                ndigit[c - '0']++;
                break;
                case '\n':case '\t':case ' ':
                nwhite++;
                break;
        }
    }
    for(int i=0;i<10;i++)cout<<"数字"<<i<<"出现次数："<<ndigit[i]<<endl;
    cout<<"空白字符出现次数："<<nwhite<<endl;
    cout<<"其他字符出现次数："<<nother<<endl;
}
// 练习3-2
void escape(char* s,char* t){
    int i,j,len=strlen(t);
    for(i=0;i< len;i++)s[i]=0;
    for(i=0,j=0;i<len;){
        switch (t[i]) {
            case '\n':
                s[j++]='\\',s[j++]='n',i++;
                break;
            case '\t':
                s[j++]='\\',s[j++]='t',i++;
                break;
            default:
                s[j++]=t[i++];
                break;
        }
    }
    s[j]='\0';
}
void reescape(char* s,char* t){
    int i,j,len=strlen(t);
    for(i=0;i< len;i++)s[i]=0;
    for(i=0,j=0;i< len;){
        if(t[i]=='\\'){
            switch (t[++i]) {
                case 'n':
                    s[j++]='\n',i++;
                    break;
                case 't':
                    s[j++]='\t',i++;
                    break;
            }
        } else s[j++]=t[i++];
    }
    s[j]='\0';
}

// 例3.5 Shell排序(递增)！
void shellsort(int*A,int n){
    int gap,i,j,tmp;
    for(gap=n/2;gap>0;gap/=2)        //最外层for循环控制两比较元素之间的距离，从n/2开始逐步对折，直到距离为0
        for(i=gap;i<n;i++)                  //中间层的for循环用于在与纳素笺移动位置
            for(j=i-gap;j>=0&&A[j]>A[j+gap];j-=gap){   //最内层的for语句用于比较各对相距gap个位置的元素
                tmp=A[j];                            //当两个元素逆序时将其互换
                A[j]=A[j+gap];
                A[j+gap]=tmp;
            }                                           //如果A[j]>A[j+gap],则交换两元素，并将A[j+gap]继续与A[j-gap]比较/
}                                                       //由于gap最终会递减为1，因此所有元素最终都会位于正确的排序位置上

//练习3-3
int judgeex(char*,char,char);
void copyex(char*,char,char,int*);
void expand(char*s1,char*s2) {
    int i, k = 0;
    for (i = 0; i < strlen(s1);) {
        if(judgeex(s1+i,'0','9')||judgeex(s1+i,'a','z')||judgeex(s1+i,'A','Z')){
            copyex(s2,s1[i],s1[i+2],&k);
            i+=2;
        }else s2[k++]=s1[i++];
    }
    s2[k]='\0';
}
int judgeex(char*s,char c1,char c2){
    if((*s>=c1&&*s<=c2)&&(*(s+1)=='-')&&(*(s+2)>=*s&&*(s+2)<=c2))
        return 1;
    else return 0;
}
void copyex(char*s,char c1,char c2,int* k){
    for(int i=0;i<c2-c1;)*(s+(*k)++)=(char)(c1+i++);
}
//例3.6
char store[MAXLINE];
char*itoa(int n,char*s){
    int i=0,sign;
    if((sign=n)<0)n=-n;
    do s[i++]=(char)(n%10+'0');
    while (n/=10);
    if(sign<0)s[i++]='-';
    s[i]='\0';
    return reverse(s);
}
//练习3-4,3-5,3-6
// 在二进制补码中，最大整数是0111…11，最大负数是1000…00
// '-'作为单目运算符时是将操作数的符号位取反，因此对最大负数而言其取负数的操作结果为0
char* itoa1(int n,char*s){
    int i=0,sign;
    if((sign=n)<0)n=-(n+1);
    do s[i++]=n%10+'0';
    while (n/=10);
    if(sign<0)s[0]+=1,s[i++]='-';
    s[i]='\0';
    return reverse(s);
}
char* itob(int n,char*s,int b){
    int i=0,bit,sign;
    if(b<=0||b>35)return nullptr;
    if((sign=n)<0)n=-(n+1);
    do s[i++]= n % b < 10 ?(n%b+'0'):(n%b-10+'a');
    while (n/=b);
    if(sign<0)s[0]+=1,s[i++]='-';
    s[i]='\0';
    return reverse(s);
}
char* itoa3(int n,char*s,int m){
    int i=0,j=0,sign;
    for(;j<m;j++)*(s+j)=' ';
    s[j]='\0';
    if((sign=n)<0)n=-(n+1);
    do s[i++]=(char)(n%10+'0');
    while (n/=10);
    if(sign<0)s[0]+=1,s[i]='-';
    return reverse(s);
}