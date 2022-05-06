#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
enum BOOL{true,false};
/* 2.38 2.39 2.40* */
/* show_bytes 示例代码 */
typedef unsigned char*byte_pointer;
void show_bytes(byte_pointer start,int len){
    for(int i=0;i<len;i++)printf(" %.2x",*(start+i));
    printf("\n");
}
void show_int(int x){
    show_bytes((byte_pointer)&x,sizeof(int));
}
void show_float(float x){
    show_bytes((byte_pointer)&x,sizeof(float));
}
void show_pointer(void*x){
    show_bytes((byte_pointer)&x,sizeof(void*));
}
void show_short(short x){
    show_bytes((byte_pointer)&x,sizeof(short));
}
void show_long(long x){
    show_bytes((byte_pointer)&x,sizeof(long));
}
void show_double(double x){
    show_bytes((byte_pointer)&x,sizeof(double));
}
void test_show_bytes(int val){
    int ival=val;
    float fval=(float)val;
    int*pval=&val;
    short sval=(short)val;
    long lval=(long)val;
    double dval=(double)val;
    printf("\tint: %21d ",ival);
    show_int(ival);
    printf("\tfloat: %19.3f ",fval);
    //test_show_bytes中是将int转化为float，因此转化后的float都是整数(可能下溢)
    show_float(fval);   
    printf("\tvoid*: %19p ",pval);
    //主函数中只有test_show_bytes来回创建栈帧，因此pval的地址始终是同一个
    show_pointer(pval);
    printf("\tshort: %19hd ",sval);
    show_short(sval);
    printf("\tlong: %20ld ",lval);
    show_long(lval);
    printf("\tdouble: %18.6f ",dval);
    show_double(dval);
    printf("\n");
}
/*
int main(){
    test_show_bytes(0);   
    test_show_bytes(1);
    test_show_bytes(-1);
    test_show_bytes(10);
    test_show_bytes(rand()%SHRT_MAX);
    test_show_bytes(INT_MAX);
    test_show_bytes(INT_MIN);
    return 0;
}
//运行结果：
    int:                     0  00 00 00 00
    float:               0.000  00 00 00 00
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                   0  00 00
    long:                    0  00 00 00 00 00 00 00 00
    double:           0.000000  00 00 00 00 00 00 00 00

    int:                     1  01 00 00 00
    float:               1.000  00 00 80 3f
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                   1  01 00
    long:                    1  01 00 00 00 00 00 00 00
    double:           1.000000  00 00 00 00 00 00 f0 3f

    int:                    -1  ff ff ff ff
    float:              -1.000  00 00 80 bf
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                  -1  ff ff
    long:                   -1  ff ff ff ff ff ff ff ff
    double:          -1.000000  00 00 00 00 00 00 f0 bf

    int:                    10  0a 00 00 00
    float:              10.000  00 00 20 41
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                  10  0a 00
    long:                   10  0a 00 00 00 00 00 00 00
    double:          10.000000  00 00 00 00 00 00 24 40

    int:                 16807  a7 41 00 00
    float:           16807.000  00 4e 83 46
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:               16807  a7 41
    long:                16807  a7 41 00 00 00 00 00 00
    double:       16807.000000  00 00 00 00 c0 69 d0 40

    int:            2147483647  ff ff ff 7f
    float:      2147483648.000  00 00 00 4f
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                  -1  ff ff
    long:           2147483647  ff ff ff 7f 00 00 00 00
    double:  2147483647.000000  00 00 c0 ff ff ff df 41

    int:           -2147483648  00 00 00 80
    float:     -2147483648.000  00 00 00 cf
    void*:      0x7ff7bdcfd33c  3c d3 cf bd f7 7f 00 00
    short:                   0  00 00
    long:          -2147483648  00 00 00 80 ff ff ff ff
    double: -2147483648.000000  00 00 00 00 00 00 e0 c1
*/
/* 2.42 2.43** */
#define GETKEY(x,y) ((x)&255)|((y)&~255)
#define SETONE(x) ((x)|~0)
#define SETZERO(x) ((x)&0)
#define SETLOWONE(x) ((x)|255)
#define SETLOWZERO(x) ((x)&~255)
/*
int main(){
    int x=0x89ABCDEF,y=0x76543210;
    printf("0x%x\n",GETKEY(x,y));
    srand(time(NULL));
    x=rand();
    printf("The initial value of x is: 0x%x\n",x);
    printf("0x%x\n",SETONE(x));
    printf("0x%x\n",SETZERO(x));
    printf("0x%x\n",SETLOWONE(x));
    printf("0x%x\n",SETLOWZERO(x));
} */
/* 2.41 2.45** 2.44*** */
int is_little_endian(){
    int test=1;
    byte_pointer pbyte=(byte_pointer)&test;
    if(*pbyte)return true;
    else return false;
}
/* 2.45的一个错误示例
int bad_int_size_is_32(){
    int set_msb=1<<31;
    int beyond_msb=1<<32; 
    return set_msb&&!beyond_msb;
    //违反c标准：如果位级运算右操作数的值为负数或大于等于提升的左操作数的宽度，则其行为未定义。
    //shift count >= width of type [-Wshift-count-overflow]
}  */
int int_size_is_32(){  //保证在字长大于等于16的机器上可以运行
    int set_msb=1<<15<<15<<1;
    int beyond_msb=set_msb<<1;  
    return set_msb&&!beyond_msb;
}
int int_shifts_are_arithmetic(){
    int itest=~0;
    if((itest>>1&itest)==itest)return true;
    else return false;
}
int unsigned_shifts_are_arithmetic(){
    unsigned utest=~0;
    if((utest>>1&utest)==utest)return true;
    else return false;
}
/*
int main(){
    printf("The machine is ");
    if(is_little_endian())printf("little Endian!\n");
    else printf("large Endian.\n");
    printf("The size of Integar is ");
    if(int_size_is_32())printf("32!\n");
    else printf("not 32.\n");
    printf("Integer uses ");
    if(int_shifts_are_arithmetic())printf("arithmetic shift!\n");
    else printf("logical shift.\n");
    printf("Unsigned integer uses ");
    if(unsigned_shifts_are_arithmetic())printf("arithmetic shift.\n");
    else printf("logical shift!\n");
}     */
/* 2.46* */
typedef unsigned packed_t;
/* 错误代码： 
//这个函数的功能大概是先抽出bytenum<<3个位，然后只取最后一个字节的内容，最后转换为int
int xbyte(packed_t word,int bytenum){
    return (word>>(bytenum<<3))&0xFF;
} */
//错误代码的问题是在由于抽取出的字节是在低位，因此将unsigned转为int的过程中并不会将抽取出字节的高位进行符号转换
//举例：比如最后抽取出的字节为0xff，题意是想让其返回二进制补码0xffffffff表示的数 (-1)，但是错误代码返回的是0x000000ff (255)
//更正后的代码：
int xbyte(packed_t word,int bytenum){
    return (int)word>>(bytenum<<3)<<24>>24;
}
/* 2.47 2.48* */
/*         
            x                 ~x                incr(~x)  (表示反码+1，即-x的值)
     [01101]     13    [10010]     -14      [10011]     -13
     [01111]     15    [10000]     -16      [10001]     -15
     [11000]     -8    [00111]      7       [01000]      8
     [11111]     -1    [00000]      0       [00001]      1
     [10000]    -16    [01111]      15      [10000]     -16
     由表可知：
     -x等价于~x+1和~(x-1)
     一个数加1实际上就是找到数中第一个为0的位，将这个位置为1，之前的位置为0
     一个数减1相当于加-1，是将数中第一个为1的位置为0，之前的位置为1
     因此x先减1再取反等价于x先取反再+1
*/
/* 2.49*** */
unsigned unsigned_high_prod(unsigned,unsigned);
int int_high_prod(int x,int y){
    long long result=((long long)x*y)>>(8*sizeof(int));
    return result;
}
unsigned unsigned_high_prod(unsigned x,unsigned y){
    unsigned unsignedbits=8*sizeof(unsigned);
    int xsign=x>>(unsignedbits-1),ysign=y>>(unsignedbits-1);
    int x_without_sign=INT_MAX&x,y_without_sign=INT_MAX&y;
    unsigned result=int_high_prod(x_without_sign,y_without_sign)+
        xsign*y_without_sign+ysign*x_without_sign;    
        //注意这里实际上省略了2^64项，如果计算两个超过2^31的因子时结果会溢出，此时这种方法是不准确的
    return result;
}
/*
int main(){
    unsigned long long result=((unsigned long long)UINT_MAX*UINT_MAX)>>(8*sizeof(unsigned));
    printf("The high-order byte of UINT_MAX*UINT_MAX is %llu\n",result);
    printf("My answer is %u",unsigned_high_prod(UINT_MAX,UINT_MAX));
}  */
/* 2.50** */
#define PRODUCTFIVE(x) (((x)<<2)+(x))
#define PRODUCTNINE(x) (((x)<<3)+(x))
#define PRODUCTFOURTEEN(x) (((x)<<4)-((x)<<1))
#define PRODUCTNEGFIFTYSIX(x) (((x)<<3)-((x)<<6))
/*
int main(){
    srand(time(NULL));
    long long factor=rand();
    printf("factor=%lld\n",factor);
    printf("factor*5=%lld\n",PRODUCTFIVE(factor));
    printf("factor*9=%lld\n",PRODUCTNINE(factor));
    printf("factor*14=%lld\n",PRODUCTFOURTEEN(factor));
    printf("factor*(-56)=%lld\n",PRODUCTNEGFIFTYSIX(factor));
} */
/* 2.51** */
#define GETNONEMZERO(k) (~((1<<(k))-1))
#define GETNZEROMONELZERO(j,k) (~GETNONEMZERO(j+k)-~GETNONEMZERO(j))
/*
int main(){
    int j,k;
    srand(time(NULL));
    j=rand()%(sizeof(int)*4),k=rand()%(sizeof(int)*4);
    printf("j=%d,k=%d\n",j,k);
    printf("1(w-k)0(k)=%d\n",GETNONEMZERO(k));
    printf("0(w-j-k)1(k)0(j)=%d\n",GETNZEROMONELZERO(j,k));
} */
/* 2.52** */
unsigned replace_byte(unsigned x,int i,unsigned char b){
    byte_pointer pos=(byte_pointer)&x;
    if(is_little_endian())pos+=i;
    else pos+=sizeof(unsigned)-i-1;
    *pos=b;
    return x;
}
/*
int main(){
    unsigned itest=0x12345678;
    unsigned char ctest=0xAB;
    printf("0x12345678,2,0xAB --> 0x%x\n",replace_byte(itest,2,ctest));
    printf("0x12345678,0,0xAB --> 0x%x\n",replace_byte(itest,0,ctest));
}  */
/* 2.53*** */
//函数srl使用算术右移执行逻辑右移，函数sra使用逻辑右移执行算术右移
unsigned srl(unsigned x,int k){  
    //perform shift arithmetically
    unsigned xsra=(int)x>>k;
    xsra&=(1<<(8*sizeof(unsigned)-k))-1;
    return xsra;
}
int sra(int x,int k){
    //perform shift logically
    int xsrl=(unsigned)x>>k;
    if(xsrl>>(8*sizeof(unsigned)-k-1))xsrl|=~((1<<(8*sizeof(unsigned)-k))-1);
    return xsrl;
}
/*
int main(){
    srand(time(NULL));
    int itest=rand()*(rand()%2?-1:1);
    unsigned utest=rand();
    int shiftbits=rand()%(8*sizeof(int)-1);
    printf("INT_MAX shifiting right arithmetically by 1 bit is: ");
    printf("%d\n",sra(INT_MAX,1));
    printf("INT_MIN shifiting right arithmetically by 1 bit is: ");
    printf("%d\n",sra(INT_MIN,1));
    printf("UINT_MAX shifiting right logically by 1 bit is: ");
    printf("%d\n",srl(UINT_MAX,1));
    printf("The random data is itest=%d,utest=%u,shiftbits=%d\n",itest,utest,shiftbits);
    printf("itest shifiting right arithmetically by shiftbits bit is: ");
    printf("%d\n",sra(itest,shiftbits));
    printf("utest shifiting right logically by shiftbits bit is: ");
    printf("%d\n",sra(utest,shiftbits));
} */
/* 2.54* */
/*  Create some arbitrary values and convert to unsigned
    int x=random();
    int y=random();
    unsigned ux=(unsigned)x;
    unsigned uy=(unsigned)y;
    判断下列c表达式是否总是1:(说明原理或举出反例)
    a.(x<y)==(-x>-y)              反例：x=INT_MIN
    b.((x+y)<<4)+y-x==17*y+15*x   正确：Associative, commutative, distributes(结合律、交换律、分配律)
    c.~x+~y==~(x+y)               完全错误，~运算不满足分配律
    d.(int)(ux-uy)==-(y-x)        正确：同理(unsigned)x-(unsigned)y==(unsigned)(x-y)==-(unsigned)(y-x)
    e.((x>>1)<<1)<=x              正确：(x>>1)<<1会将最低位置0，得出的结果小于等于x
*/
/* 2.55** */
//考虑这样一些数字，它们的二进制表示是由形如0.yyyyyyy...的无穷串组成的，其中y是一个k位的序列
//例如：1/3的二进制表示是0.01010101...(y=01)，而1/5的二进制表示为0.001100110011...(y=0011)
#define ACCURACY 100
double Getapproresult(char*y){
    int len=strlen(y);
    double result=0;
    for(int i=1;i<=ACCURACY*len;i++)result+=pow(2,-i)*(*(y+(i-1)%len)-'0');
    return result;
}
//考虑y.yyyyyyy...=0.yyyyyyyy...+y，令V=0.yyyyyyyy，k=y的位数，Y=y
//此时有Y+V=V*2^k，由此可知：V=Y/(2^k-1）
//因此当y=001时，0.yyyyyy...=1/(8-1)=1/7
//     y=1001时，0.yyyyyy...=9/(16-1)=3/5
//     y=000111时，0.yyyyyy...=7/(64-1)=1/9
/*
int main(){
    char*test1="01",*test2="0011";
    char*str1="001",*str2="1001",*str3="000111";
    printf("The value corresponding to the string 01 is:%f\n",Getapproresult(test1));
    printf("The value corresponding to the string 0011 is:%f\n",Getapproresult(test2));
    printf("The value corresponding to the string 001 is:%f\n",Getapproresult(str1));
    printf("The value corresponding to the string 1001 is:%f\n",Getapproresult(str2));
    printf("The value corresponding to the string 000111 is:%f\n",Getapproresult(str3));
} 
    运行结果：
    The value 0.yyyyyy... to y=01 is:0.333333
    The value 0.yyyyyy... to y=0011 is:0.200000
    The value 0.yyyyyy... to y=001 is:0.142857
    The value 0.yyyyyy... to y=1001 is:0.600000
    The value 0.yyyyyy... to y=000111 is:0.111111
*/
/* 2.56* */
int float_ge(float x,float y){
    unsigned ux=(unsigned)x;
    unsigned uy=(unsigned)y;
    //Get the sign bits
    unsigned sx=ux>>31;
    unsigned sy=uy>>31;
    //Give an expression using only ux, uy, sx and sy
    //return sx==sy?((ux<<1>>24)==(uy<<1>>24)?(ux<<9)>(uy<<9):(ux<<1>>24)>(uy<<1>>24)):sx<sy;
    //注意：浮点数转化为整数并不是按位转换，所以无法通过转化为整数再移位的方法进行位级的比较
    //在c/c++中没有定义浮点数的值表示形式，浮点数在值表示层没有位，不能对其进行按位运算
    return (ux<<1==0&&uy<<1==0)||
           (!sx&&sy)||
           (!sx&&!sy&&ux>=uy)||
           (sx&&sy&&ux<=uy);
}
/*
int main(){
    float ftest1,ftest2;
    int ret;
    do{
        fflush(stdin);
        printf("Please input ftest1 and ftest2:");
        ret=scanf("%f %f",&ftest1,&ftest2);
    }while(ret!=2);
    printf("ftest1 is more than ftest2? ");
    if(float_ge(ftest1,ftest2))printf("YES.");
    else printf("NO.");
} */
/* 2.57* */
/* 给定一个浮点格式，有k位指数和n位小数，对于下列数，写出指数E，有效数M，小数f和值V的公式，另外，描述其位表示：
    a.数5.0:E=10000001(2)-127=2，M=1.01(2)=5/4，f=0.01(2)=1/4，V=(2^E)*M=5.0
            位表示：0x40a00000 (01000000101000000000000000000000)
    b.能够被准确描述的最大奇整数:由公式V=(2^E)*M=(2^E+(2^E)*f)=(2^E+(2^(E-23))*F) 
        (小数部分f可以表示为有效数域中的位表示的无符号数乘以有效数域的最高精度，对于float而言一般是23位，因此是2^(-23))
        由于要求为整数，因此E-23>=0；同时还要求为奇数，因此取E-23=0；要求为最大奇数，因此有效数取最大值
        由此可知：E=23=150-127，M=1.1111...11，f=0.1111...11，V=(2^E)*M=16777215
            位表示：0x4b7fffff (01001011011111111111111111111111)
    c.最小的正规格化数的倒数:正规格化数最小时E和M均取最小值，E=1-127=-126，M=1.0，f=0.0，V=2^(-126)
            其倒数为V=2^(126)，即E=253-127，M=1.0，f=0.0
            位表示：0x7e800000 (01111110100000000000000000000000)
*/
/* 2.58* */
/*
        描述                                扩展精度   (80位，1个符号位，15个指数位，1个单独的整数位，63个小数位)
                                值                      十进制
    最小的非规格化数     (2^(2-2^14))*(2^(-63))       3.64*10^(-4951)
    最小的规格化数           (2^(2-2^14))             3.64*10^(-4932)
    最大的规格化数      (2^(2^14-1)*(2-2^(-63)))      1.19*10^(4932)
*/
/* 2.59* */
//考虑一个基于IEEE浮点格式的16位浮点表示，它具有一个符号位、7个指数位、8个小数位，指数偏置量是63
/* (只考虑正数)
          描述             Hex        M       E       V
          -0             0x8000      0      -62      ——   (0是非规格化数)
       >1的最小值         0x3f01   257/256     0    257/256
          256            0x4700      1        8      2^8
      最大的非规格化数      0x00ff   255/256   -62  255*2^(-70)
           -∞            0x7f00      ——      ——      ——
    16进制表示为3AA0的数   0x3aa0     13/8     -5   13*2^(-11)
*/
/* 2.60* */
/* Create some arbitrary values and convert to double
    int x=random();
    int y=random();
    int z=random();
    double dx=(double)x;
    double dy=(double)y;
    double dz=(double)z;
    判断下列c表达式是否总是1:(说明原理或举出反例)
    (不能用IA32机器运行GCC测试答案(这种情况下使用的是扩展精度表示double)
    a.(double)(float)x==dx        反例：x大于16777217，x转化为float会损失精度，但直接转化为double时不会损失精度
    b.dx+dy==(double)(x+y)        反例：x+y转化为double也可能损失精度
    c.dx+dy+dz==dz+dy+dx          正确：对任意可能的整型取值均符合  (注意dx,dy,dz都是由整数转化而来的)
    d.dx*dy*dz==dz*dy*dx          反例：dx*dy可能大于9007199254740993，此时结果会损失精度
    e.dx/dx==dy/dy                反例：dx或dy=0
    //最小的float不能精确表示的正整数是16777217，最小的double不能精确表示的正整数是9007199254740993
*/
/* 2.61* */
//计算2^x的浮点表示，当x太小时返回0.0，当x太大时返回+∞，假设函数u2f返回的浮点值与它的无符号参数有相同的位表示
float u2f(unsigned);
float fpwr2(int x){
    //Result exponent and significand 
    unsigned exp,sig;
    unsigned u;
    if(x<-149)exp=0,sig=0;                   //Too small. Return 0.0
    else if(x<-126)exp=0,sig=1<<(x+149);     //Denormalized result
    else if(x<128)exp=x+127,sig=0;           //Normalized result
    else exp=255,sig=0;                      //Too big. Return +∞
    //Pack exp and sig into 32 bits
    u=exp<<23|sig;
    //Return as float
    return u2f(u);
}
float u2f(unsigned u){
    float result;
    byte_pointer upos=(byte_pointer)&u,fpos=(byte_pointer)&result;
    for(int i=0;i<sizeof(float);i++)*fpos++=*upos++;
    return result;
}
/*
int main(){
    for(int i=-159;i<135;i+=5)printf("2^%d=%.50f\n",i,fpwr2(i));
} */
/* 2.62* */
/*
    a.0x40490FDB的二进制表示为01000000010010010000111111011011，值为3.141593≈011.0010010000111111011011
    b.22/7的二进制表示为011.001001001...001
    c.两个π的近似值从相对于二进制小数点后第9位开始不同
*/