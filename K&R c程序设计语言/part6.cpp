//
// Created by 徐绍骞 on 2021/7/14.
//
#include "shared.h"
// 例6.3，6.4 统计c关键字出现的次数
// 练习6-1，6-2(未解之谜：从输入流里面读不到\n)，6-3，6-4
int getword(char*,int,int*);
struct key*binsearchkey(char *s, struct key *k);
void findkeymain(){
    struct key*p;
    char word[MAXWORD];
    while(getword(word,MAXWORD, nullptr)!=';')
        if(isalpha(word[0]))if((p=binsearchkey(word, keytab)))p->count++;
    for(p=keytab;p<keytab+NKEYS;p++)if(p->count>0)cout<<p->count<<' '<<p->word<<endl;
}
struct key* binsearchkey(char*s, struct key*k){   //binsearch_key函数：在tab[0]到tab[n-1]中查找单词，返回指针
    int cond;
    struct key*low=k,*high=k+NKEYS,*mid;
    while(high-low>0){
         mid=low+(high-low)/2;
        if((cond=strcmp(s,mid->word))>0)low=mid+1;
        else if(cond<0)high=mid;    //不使high=mid-1的原因：当mid=0时high为-1，此时的指针是非法的
        else return mid;                //而数组之后的一个元素的指针运算可以执行，所以low=mid+1是可以的
    }
    return nullptr;
}
int getword(char*word,int lim,int*level){   //getword函数：从输入中读取下一个字符或单词
    //单词分三种：字母开头的由字母和数组组成的串、一个非空白的非字母数字字符(比如,等)、EOF
    //扩展：单词中可以包含_，字符串常量，注释，define预处理控制命令
    int c;
    char*w=word;
    while(isspace(c=getch()));
    if(c!=EOF)*w++=(char)c;
    if(!isalpha(c)&&c!='"'&&c!='/'&&c!='#'){
        if(c=='\n')(*level)++;
        *w='\0';
        return c;
    }
    switch(c){
        case'"':
            for(;--lim>0;w++)if((*w=(char)getch())=='"') {w++;break;}
            break;
        case '/':
            if((c=getch())=='*'||c=='/'){
                if((*w++=(char)c)=='*'){
                    for(;--lim>0;w++)if((*w=(char)getch())=='*'){
                            if((*++w=(char)getch())=='/'){w++;break;}
                            else ungetch(*w--);
                    }
                }else for(;--lim>0;w++)if((*w=(char)getch())=='\n'){(*level)++;break;}
            } else return c;
            break;
        case '#':
            *w++=(char)getch();
            for(;--lim>0;w++)if((*w=(char)getch())=='\n'){(*level)++;break;}
        default:
            for(;--lim>0;w++)if(!isalnum(*w=(char)getch())&&*w!='_')break;
            break;
    }
    ungetch(*w);
    *w='\0';
    return word[0];
}
/* 例6.5 在6.3，6.4的基础上考虑更一般化的问题：统计所有单词的出现次数
 * 由于无法事先预知出现的单词列表，所以无法方便地排序并使用折半查找
 * 如果对将出现的单词依次存储再对每一次输入都进行一次线性查找看其是否已经出现的话，太浪费时间(O(N^2))
 * 因此，一种解决办法是在读取时就将其放入正确位置(使用二叉搜索树)  */
struct tnode{                       //树的结点
    char*word;                      //指向单词的指针
    int count,level;                        //单词出现的次数
    struct tnode*left,*right;    //左右子结点,前n个字符相同的分为一组，用链表存储
}tnodelist[MAXLINES];
struct tnode*addtree(struct tnode*,char*,int,int);
/* 函数addtree是递归的，主函数main以参数的方式传递给该函数一个单词作为树的根
 * 每一步中，将新单词与结点中存储的单词进行比较，随后通过递归调用addtree而转向左子树或右子树
 * 该单词最终将与树中的某结点匹配(计数值+1),或遇到一个空指针(表明需要创建一个结点加入到树中)
 * 若生成一个新结点则addtree返回一个指向新结点的指针，该指针保存在父结点中 */
int treeprint(struct tnode*);
struct tnode*talloc();
char*strdup(char*);
bool isonegroup(const char*,const char*,int);
int partitiontnode(struct tnode*,int,int);
void qsorttnode(struct tnode*,int,int);
void findkeymain_bintree(char*argv){
    struct tnode*root;
    int n,level=1;
    char word[MAXWORD];
    root=nullptr;
    while(getword(word,MAXWORD,&level)!=';')
        if(isalpha(word[0]))root=addtree(root,word,atoi_ptr(argv),level);
    n=treeprint(root);
    qsorttnode(tnodelist,0,n-1);
    for(int i=0;i<n;i++)cout<<"出现次数:"<<tnodelist[i].count<<"  单词:"<<tnodelist[i].word<<endl;
}
struct tnode*addtree(struct tnode*root,char*word,int length,int level){
    if(!root){
        root=talloc();
        root->word= strdup(word),root->count=1,root->level=level;
        root->left=root->right=nullptr;
    }else if(strcmp(root->word,word)>0)root->left=addtree(root->left,word,length,level);
    else if(strcmp(root->word,word)<0||(isonegroup(root->word,word,length)&&strcmp(root->word,word)!=0))
        root->right= addtree(root->right,word,length,level);
    else root->count++;
    return root;
}
// treeprint函数：按顺序打印树(中序遍历)
int treeprint(struct tnode*p){
    static int i=0;
    if(p){
        treeprint(p->left);
        tnodelist[i++]=*p;
        treeprint(p->right);
    }
    return i;
}
// talloc函数：新结点的初始化，返回一个指针指向一个能容纳树结点的空闲空间
struct tnode*talloc(){
    return (struct tnode*)malloc(sizeof(struct tnode));
}
// strdup函数：把通过其参数传入的字符串复制到某个安全的位置
char*strdup(char*s){
    char*p;
    p=(char*)malloc(strlen(s)+1);
    if(p)strcpy(p,s);
    return p;
}
bool isonegroup(const char*s1, const char*s2, int length){
    while(length--&&*s1++==*s2++);
    if(length<0||!*(s1-1)||!*(s2-1))return true;
    return false;
}
int partitiontnode(struct tnode* t,int start,int end){
    if(start<0||start>end||!t)return -1;
    struct tnode pivot=t[start];
    while(start<end){
        while(t[end].count<pivot.count&&start<end)end--;
        t[start]=t[end];
        while(t[start].count>=pivot.count&&start<end)start++;
        t[end]=t[start];
    }
    t[start]=pivot;
    return start;
}
void qsorttnode(struct tnode*t,int start,int end){
    int pivot=partitiontnode(t,start,end);
    if(end-start<=1)return;
    else if(pivot<end-1)qsorttnode(t,pivot+1,end);
    else if(pivot>start+1)qsorttnode(t,start,pivot-1);
}
/* 例6.6 表查找程序包的核心部分：这段代码很典型，可以在宏处理器或编译器的符号表管理例程中找到
 * install(s,t)函数将名字s和替换文本记录到某个表中，s和t仅仅是字符串
 * lookup(s)函数在表中查找s，若找到则返回该处的指针，若没找到则返回nullptr
 * 使用散列查找方法：
 * 将输入的名字转换为一个小的非负整数，该整数随后将作为一个指针数组的下标
 * 数组的每个元素指向某个链表的表头，链表中各个块用于描述具有该散列值的名字
 * 链表中每个块是一个结构，包含一个指向名字的指针，一个指向替换文本的指针以及一个指向链表后继的指针 */
struct nlist{
    struct nlist*next;
    char*name,*defn;
};
struct nlist *hashtab[HASHSIZE];
// 散列函数hash：在每次循环中将上次循环中的结果经过变换(乘以31)后得到的新值同字符串当前值相加
// 然后将该结果同数组长度执行取模运算，其结果是该函数的返回值
// 这并不是最好的散列函数，但比较简短有效
unsigned Hash(char*s){
    unsigned hashval;                           //unsigned保证散列值非负
    for(hashval=0;*s!='\0';s++)hashval=*s+31*hashval;
    return hashval%HASHSIZE;           //散列过程生成在数组hashtab中执行查找的下标
}
// lookup函数：在hashtab中查找s
// lookup函数中的for循环是遍历一个链表的标准方法 for(ptr=head;ptr;ptr=ptr->next);
struct nlist*lookup(char*s){
    struct nlist*np;
    for(np=hashtab[Hash(s)];np;np=np->next)if(!strcmp(np->name,s))return np;
    return nullptr;
}
// install函数借助lookup函数判断待加入的名字是否已经存在
// 如果已经存在，则用新的定义取而代之；否则创建一个新表项
// 如无足够空间创建新表项，则install函数返回NULL
struct nlist*install(char*name,char*defn){
    struct nlist*np;
    unsigned hashval;
    if(!(np= lookup(name))){                                       //如果没在散列表中找到
        np=new struct nlist;
        if(!(np->name= strdup(name)))return nullptr;    //将name赋给np->name，如果name为空返回空指针
        hashval=Hash(name);
        np->next=hashtab[hashval];                           //将散列表中存储的值换成np
        hashtab[hashval]=np;
    }else free((void*)np->defn);                                //如果通过lookup函数找到了name，就将前一个defn释放掉
    if(!(np->defn= strdup(defn)))return nullptr;          //将defn赋给np->defn，同时如果defn为空返回空指针
    return np;
}
void undef(char*name){
    struct nlist*np,*tmp;
    np=hashtab[Hash(name)];
    if(!strcmp(np->name,name)){
        tmp=np;
        np=np->next;
    }else for(;np->next;np=np->next)if(!strcmp(np->next->name,name)){
        tmp=np->next;
        np->next=tmp->next;
    }
    free(tmp->name),free(tmp->defn), free(tmp);
}
void getw(char*w,int lim){
    int c;
    while(isspace(c=getch()));
    *w++=(char)c;
    for(;--lim>0;w++)if(!isalnum(*w=(char)(c=getch())))break;
    ungetch(c), *w='\0';
}
int getdef(char*word,int lim){
    int c;
    char*w1,*w2;
    while(isspace(c=getch()));
    if(c=='#'){
        *word++=(char)c;
        getw(word,lim), w1=++word;
        getw(w1,lim), w2=++w1;
        getw(w2,lim);
        install(w1, w2);
    }else return c;
    return word[0];
}