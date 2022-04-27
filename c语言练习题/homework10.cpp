/* 内存地址映像 */
#include <stdio.h>
#include <stdlib.h>
int varGlobal1 ;
int varGlobal2 ;
int varGlobal3 ;
int varGlobal4 = 1;
int varGlobal5 = 2;
int varGlobal6 = 3;
const int varGlobalCons1 = 4;
const int varGlobalCons2 = 5;
const int varGlobalCons3 = 6;
static int varGlobalStat1 = 7;
static int varGlobalStat2 = 8;
static int varGlobalStat3 = 9;
void funcTest(int param1, int param2, int param3)
{
    int varLocal1 = 10;
    int varLocal2 = 11;
    int varLocal3 = 12;
    const int varLocalCons1 = 0;
    const int varLocalCons2 = 0;
    const int varLocalCons3 = 0;
    static int varLocalStat1 = 0;
    static int varLocalStat2 = 0;
    static int varLocalStat3 = 0;
    printf("funcTest函数内常量地址\n");
    printf("varLocalCons1 = %p, varLocalCons2 = %p, varLocalCons3 = %p\n",&varLocalCons1,&varLocalCons2,&varLocalCons3);
    printf("funcTest函数内静态变量地址\n");
    printf("varLocalStat1 = %p, varLocalStat2 = %p, varLocalStat3 = %p\n",&varLocalStat1,&varLocalStat2,&varLocalStat3);
    printf("funcTest函数内变量地址\n");
    printf("varLocal1 = %p, varLocal2 = %p, varLocal3 = %p\n",&varLocal1,&varLocal2,&varLocal3);
    printf("funcTest函数参数地址\n");
    printf("param1 = %p, param2 = %p, param3 = %p\n",&param1,&param2,&param3);
}
int main()
{
    static int varLocalStat1 = 0;
    static int varLocalStat2 = 0;
    static int varLocalStat3 = 0;
    static int varLocalStat4 ;
    static int varLocalStat5 ;
    static int varLocalStat6 ;
    const int varLocalCons1 = 0;
    const int varLocalCons2 = 0;
    const int varLocalCons3 = 0;
    int varLocal1 = 0;
    int varLocal2 = 0;
    int varLocal3 = 0;
    char * pMalloc1, *pMalloc2, *pMalloc3;
    pMalloc1 = (char *)malloc(sizeof(char)*10);
    pMalloc2 = (char *)malloc(sizeof(char)*10);
    pMalloc3 = (char *)malloc(sizeof(char)*10);
    funcTest(varLocal1,varGlobal1,varGlobalCons1);
    printf("全局静态变量地址\n");
    printf("varGlobalStat1 = %p, varGlobalStat2 = %p, varGlobalStat3 = %p\n",&varGlobalStat1,&varGlobalStat2,&varGlobalStat3);
    printf("全局常量地址\n");
    printf("varGlobalCons1 = %p, varGlobalCons2 = %p, varGlobalCons3 = %p\n",&varGlobalCons1,&varGlobalCons2,&varGlobalCons3);
    printf("全局变量地址（未初始化）\n");
    printf("varGlobal1 = %p, varGlobal2 = %p, varGlobal3 = %p\n",&varGlobal1,&varGlobal2,&varGlobal3);
    printf("全局变量地址（初始化）\n");
    printf("varGlobal4 = %p, varGlobal5 = %p, varGlobal6 = %p\n",&varGlobal4,&varGlobal5,&varGlobal6);
    printf("main()本地常量地址\n");
    printf("varLocalCons1 = %p, varLocalCons2 = %p, varLocalCons3 = %p\n",&varLocalCons1,&varLocalCons2,&varLocalCons3);
    printf("main()本地静态变量地址(已初始化)\n");
    printf("varLocalStat1 = %p, varLocalStat2 = %p, varLocalStat3 = %p\n",&varLocalStat1,&varLocalStat2,&varLocalStat3);
    printf("main()本地静态变量地址(未初始化)\n");
    printf("varLocalStat4 = %p, varLocalStat5 = %p, varLocalStat6 = %p\n",&varLocalStat4,&varLocalStat5,&varLocalStat6);
    printf("在堆上分配的内存地址\n");
    printf("pMalloc1 = %p, pMalloc2 = %p, pMalloc3 = %p\n",pMalloc1,pMalloc2,pMalloc3);
    printf("main()本地变量地址\n");
    printf("varLocal1 = %p, varLocal2 = %p, varLocal3 = %p\n",&varLocal1,&varLocal2,&varLocal3);
    free(pMalloc1);
    free(pMalloc2);
    free(pMalloc3);
    return 0;
}
/* 运行结果：
    funcTest函数内常量地址
    varLocalCons1 = 0x7ff7ba312304, varLocalCons2 = 0x7ff7ba312300, varLocalCons3 = 0x7ff7ba3122fc
    funcTest函数内静态变量地址
    varLocalStat1 = 0x105bf5044, varLocalStat2 = 0x105bf5048, varLocalStat3 = 0x105bf504c
    funcTest函数内变量地址
    varLocal1 = 0x7ff7ba312310, varLocal2 = 0x7ff7ba31230c, varLocal3 = 0x7ff7ba312308
    funcTest函数参数地址
    param1 = 0x7ff7ba31231c, param2 = 0x7ff7ba312318, param3 = 0x7ff7ba312314
    全局静态变量地址
    varGlobalStat1 = 0x105bf502c, varGlobalStat2 = 0x105bf5030, varGlobalStat3 = 0x105bf5034
    全局常量地址
    varGlobalCons1 = 0x105bf0fac, varGlobalCons2 = 0x105bf0fb0, varGlobalCons3 = 0x105bf0fb4
    全局变量地址（未初始化）
    varGlobal1 = 0x105bf5038, varGlobal2 = 0x105bf503c, varGlobal3 = 0x105bf5040
    全局变量地址（初始化）
    varGlobal4 = 0x105bf5020, varGlobal5 = 0x105bf5024, varGlobal6 = 0x105bf5028
    main()本地常量地址
    varLocalCons1 = 0x7ff7ba312368, varLocalCons2 = 0x7ff7ba312364, varLocalCons3 = 0x7ff7ba312360
    main()本地静态变量地址(已初始化)
    varLocalStat1 = 0x105bf5050, varLocalStat2 = 0x105bf5054, varLocalStat3 = 0x105bf5058
    main()本地静态变量地址(未初始化)
    varLocalStat4 = 0x105bf505c, varLocalStat5 = 0x105bf5060, varLocalStat6 = 0x105bf5064
    在堆上分配的内存地址
    pMalloc1 = 0x60000322c030, pMalloc2 = 0x60000322c040, pMalloc3 = 0x60000322c050
    main()本地变量地址
    varLocal1 = 0x7ff7ba31235c, varLocal2 = 0x7ff7ba312358, varLocal3 = 0x7ff7ba312354   

    总结：
    1.const常量不是真正的常量，只是分配在栈中的只读量(在编译时刻直接在程序中替换，类似于宏)
    2.运行结果中所有变量地址的顺序依次为：
      全局常量 0x105bf0fac ～ 0x105bf0fb4
      全局静态变量 0x105bf502c ～ 0x105bf5034
      全局变量 0x105bf5038 ～ 0x105bf5040
      funcTest函数内静态变量 0x105bf5044 ～ 0x105bf504c
      main()本地静态变量 0x105bf5050 ～ 0x105bf5064
      (虽然看似地址顺序和是否初始化无关，但实际上未初始化的静态存储空间的变量存储在bss段，已初始化的存储在data段)
      (main()和funcTest()中静态变量地址的顺序应该也是和定义顺序有关)
      堆内存 0x60000322c030 ～ 0x60000322c050
      funcTest函数内常量地址 0x7ff7ba3122fc ～ 0x7ff7ba312304
      funcTest函数内变量 0x7ff7ba312308 ～ 0x7ff7ba312310
      main()本地变量 0x7ff7ba312354 ～ 0x7ff7ba31235c
      main()本地常量 0x7ff7ba312360 ～ 0x7ff7ba312368
      (栈上的内存分配上一定是main先入栈funcTest后入栈，因此main的地址先分配(栈地址从上往下分配，因此先分配的地址在高位))
      (综合来看(猜测)const常量的地址应该先于普通变量分配)
*/