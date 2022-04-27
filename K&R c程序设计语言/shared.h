//
// Created by 徐绍骞 on 2021/7/6.
//
// 这个文件暂时只放宏定义，结构体定义和部分需要共享的外部变量和函数
// 由于share.h在main和各个源文件中都会包含，所以要进行条件预处理
#ifndef C_SHARED_H   //等价于#if !defined(C_SHARED_H)
#define C_SHARED_H
#define LOWER 0
#define TEST LOWER  //测试:宏定义可以使用之前定义的宏
#define UPPER 300
#define step 20
#define In 0
#define Out 1
#define MAXLINES 5000
#define MAXLINE 1000
#define TABSIZE 8
#define FOLDCOMP 10
#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define SIN '1'
#define EXP '2'
#define POW '3'
#define BUFSIZE 100
#define ALLOCSIZE 10000
#define MAXTOKEN 100
#define MAXWORD 100
#define NKEYS (sizeof keytab/sizeof(struct key))
#define MaxSize 10000
#define MaxVertexNum 1005
#define HASHSIZE 101
#define FMTLEN  88
#define PERMS 0666
#define MAX_PATH 1024
#ifndef DIRSIZ
#define DIRSIZ 1024
#endif
#define NALLOC 1024
#define Maxcount 105
#define INFINITY 65535
#define FOREVER for(;;)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define Dprint(e) printf(#e)
#define SWAP(t,x,y) {t tmp;tmp=(t)x,x=(t)y,y=tmp;}
typedef struct TreeNode*BinTree;
typedef struct BSTreeNode*BST;
typedef struct AVLreeNode*AVL;
typedef struct HeapStruct_Huff*MinHeap;
typedef struct HuffmanNode*HuffmanTree;
typedef struct ENode*PtrToENode;
typedef struct MGNode*PtrToMGNode;
typedef struct AdjVNode*PtrToAdjVNode;
typedef struct LGNode*PtrToLGNode;
typedef struct Vnode AdjList[MaxVertexNum];
typedef long Align;
typedef union header Header;
typedef int ElementType;
typedef int SetName;
typedef int WeightType;
typedef char DataType;
typedef int Vertex;
typedef ElementType SetType[MaxSize];
typedef BinTree Position;
typedef PtrToENode Edge;
typedef PtrToMGNode MGraph;
typedef PtrToLGNode LGraph;
typedef struct Point{
    int x,y;
}point;
struct key{
    const char *word;
    int count;
}keytab[]={{"auto",0},{"break",0},{"case",0},
{"char",0},{"const",0},{"continue",0},
{"default",0},{"unsigned",0},{"void",0},
{"volatile",0},{"while",0}};
struct TreeNode {
    ElementType val;
    TreeNode *left,*right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct BSTreeNode
{
    ElementType Data;
    BST Left, Right;
    int flag;
};
struct AVLreeNode
{
    ElementType Data;
    AVL Left, Right;
    int height;
};
struct HeapStruct_Huff{
    HuffmanTree *Elements;
    int Size,Capicity;
};
struct HuffmanNode{
    ElementType weight;
    HuffmanTree Left,Right;
};
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
struct MGNode{
    int Nv,Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};
struct AdjVNode{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};
struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType Data;
};
struct LGNode{
    int Nv,Ne;
    AdjList G;
};
enum judge{NO,YES};
enum {NAME,PARENS,BRACKETS};
enum month{Jan,Feb,Mar,Apr,May,Jun,July,Aug,Sep,Oct,Nov,Dec};
extern int testarray[];
extern char line[],longest[],tmpca[],pattern[],store[],daytab[2][13];
extern int tpreorder[],tinorder[],tpostorder[];
extern int bufp,buf[BUFSIZE];
int tpreorder[]={'A','B','D','E','C','F','G'},
    tinorder[]={'D','B','E','A','F','C','G'},
    tpostorder[]={'D','E','B','F','G','C','A'};
int getline_ptr(char*,int);
int strindex(char*,char*);
int get_withoutandor(char*,int);
int getch();
int getop_ptr(char*);
int getop_scanf(double*f);
double atof(char*);
void ungetch(int);
template <typename T>void Swap(T t[],int t1,int t2){
    T tmp;
    tmp=t[t1],t[t1]=t[t2],t[t2]=tmp;
}
#endif //C_SHARED_H
