//
// Created by 徐绍骞 on 2021/8/5. 基本都是"借鉴"来的
//
// 例8.2 将输入复制到输出，getchar的实现
#include<unistd.h>
#include<fcntl.h>
char bufs[BUFSIZ];
int copy(){
    int n;
    while((n=(int)read(0,buf,BUFSIZ))>0)write(1,buf,n);
    return 0;
}
int getchar1(){     //每次读入一个字符
    char c;
    return (read(0,&c,1)==1)?(unsigned char)c:EOF;
}
int getchar2(){     //一次读入一组字符，但每次只输出一个字符
    static char buf[BUFSIZ];    //注意缓冲区，缓冲区指针和访问缓冲区的下标都定义为了局部静态变量
    static char*bufp=buf;
    static int n=0;                     //第一次调用时n=0
    if(n==0){                              //第一次调用将一组字符全部读入
        n=(int)read(0,buf,sizeof buf);
        bufp=buf;
    }
    return (--n>=0)?(unsigned char)*bufp++:EOF;   //每调用一次将缓冲区指针向后移一位，直到末尾
}
// 例8.3 简化的UNIX程序cp
void error(const char*,...);
int cpmain(int argc,char*argv[]){
    int f1,f2,n;
    if(argc!=3)error("Usage:cp from to");           //提醒调用参数格式错误
    if((f1=open(argv[1],O_RDONLY,0))==-1)error("cp:can't open %s",argv[1]); //打开文件失败
    if((f2=creat(argv[2],PERMS))==-1)error("cp:can't create %s, mode %03o",argv[2],PERMS);//创建文件失败
    while((n=(int)read(f1,buf,BUFSIZ))>0)if(write(f2,buf,n)!=n)error("cp:write error on file %s",argv[2]);
    //如果从f1读到的字符数n大于0，则将n个字符写入f2，如果写入字符数量不足n的话，报告写入时发生错误
    return 0;
}
void error(const char*fmt,...){
    va_list args;                      //声明一个代表无名参数指针类型va_list的变量args
    va_start(args,fmt);           //va_start将va_list指针初始化为fmt之后的第一个无名参数
    fprintf(stderr,"error:");
    vfprintf(stderr,fmt,args); //vprintf原型：int vprintf(const char *format, va_list arg)，以printf的格式将所有参数输出
    fprintf(stderr,"\n");
    va_end(args);                //va_end释放args并做一些善后工作
    exit(1);
}
// 练习 8-1
void filecopy_by_sys(int,int);
int catmain_by_sys(int argc,char*argv[]){
    int f;
    if(argc==1)filecopy_by_sys(0,1);
    else while(--argc)if((f=open(*++argv,O_RDONLY))==-1){
            cout<<"cat: can't open "<<*argv;
            return 1;
        }else{
            filecopy_by_sys(f,1);
            close(f);
        }
    return 0;
}
void filecopy_by_sys(int f1,int f2){
    int n=(int)read(f1,buf,BUFSIZ);
    write(f2,buf,n);
}
// 例8.5  fopen()和getc()的实现
// 由于系统和编译器的库函数实现问题(文件结构只是简单模拟)，书中的程序无法使用，在此仅作为伪代码展示
// 下列宏和函数原型为<stdio.h>的部分典型片段，其中包含宏getc的实现
/* #define NULL 0
 * #define EOF (-1)
 * #define BUFSIZ 1024
 * #OPEN_MAX 20             //一次最多可打开的文件数
 * #define stdin (&_iob[0])
 * #define stdout (&_iob[1])
 * #define stderr (&_iob[2])
 * int fillbuf(FILE*);
 * int flushbuf(int,FILE*);
 * #define feof(p) (((p)->flag&_EOF)!=0)  //p一般为传入的FILE*，当p->flag的第二个位字段为0时(p)->flag&_EOF)=0
 * #define ferror(p) (((p)->flag&_ERR)!=0)
 * #define getc(p) (--(p)->cnt>=0?(unsigned char)*(p)->ptr++:fillbuf(p))
 * //先将文件内容读入缓冲区，宏getc再读缓冲区内容，如果缓冲区为空(读完)后，调用fillbuf()将缓冲区填满
 * #define putc(x,p) (--(p)->cnt>=0?*(p)->ptr++=(x):flushbuf((x),p)
 * //宏putc先通过文件指针将缓冲区满(写完)后，调用flushbuf()将缓冲区内容刷新到文件中
 * #define getchar() getc(stdin)
 * #define putchar(x) putc((x),stdout)
 */
typedef struct iobuf{
    int cnt;                         //剩余的字符数
    char*ptr;                      //下一个字符的位置
    char*base;                   //缓冲区的位置
    int flag;                       //文件访问模式
    int fd;                         //文件描述符
}myFILE;
enum flags{
    READ=01,                    //以读写方式打开文件
    WRITE=02,                  //以写方式打开文件
    UNBUF=04,                 //不对文件进行缓冲
    myEOF=010,               //已到文件的末尾
    ERR=020,                  //该文件发生错误
};
// 首先需要初始化数组iob(已经打开的文件)中的stdin、stdout和stderr值
myFILE iob[OPEN_MAX]={
        {0,(char*)nullptr,(char*)nullptr,READ,0},                    //stdin:读
        {0,(char*)nullptr,(char*)nullptr,WRITE,0},                  //stdout:写
        {0,(char*)nullptr,(char*)nullptr,READ|UNBUF,0}         //stderr:读且不缓冲
};
/* fopen()的简单实现：
 *  fopen()主要功能为打开文件，定位到合适位置，设置标志位以指示相应的状态
 *  不分配任何缓冲区空间，缓冲区的分配是在第一次读文件时由fillbuf()完成的
 *  该版本的fopen()不能识别表示二进制访问方式的b标志，也不能识别允许同时进行读和写的+标志 */
myFILE*fopen(char*name,const char*mode){
    int fd=0;
    myFILE*fp;
    if(*mode!='r'&&*mode!='w'&&*mode!='a')return nullptr;       //如果mode取值不正确，返回空指针
    for(fp=iob;fp<iob+OPEN_MAX;fp++)if((fp->flag&(READ|WRITE))==0)break;
    //_READ、_WRITE分别为枚举常量01、02(八进制转为二进制为001、010，_READ|_WRITE=011)
    //如果文件空闲的话flag值为0
    if(fp>=iob+OPEN_MAX)return nullptr;       //如果打开的文件数超过OPEN_MAX，返回空指针
    if(*mode=='w')fd=creat(name,PERMS);
    //写模式打开文件，如果文件不存在创建一个新的，如果存在则将内容清空，最后返回文件标识符
    else if(*mode=='a'){
        if((fd=open(name,O_WRONLY,0))==-1)fd=creat(name,PERMS);
        lseek(fd,0L,2);
    //读模式打开文件，打开文件并返回文件标识符，如果文件打开失败则创建一个新的并文件标识符
    //将访问位置设为文件末尾
    }else fd=open(name,O_RDWR,0);           //读写模式打开文件
    if(fd==-1)return nullptr;                        //不能访问名字(打开文件过程发生错误)
    fp->fd=fd;
    fp->cnt=0;
    fp->base=nullptr;
    fp->flag=(*mode=='r')?READ:WRITE;    //flag值置为READ或WRITE
    return fp;
}
/* fillbuf()实现：
 * 对于某一特定文件，第一次调用getc()时计数值为0，这样就必须调用一次fillbuf()
 * 如果函数fillbuf()发现文件不是以读模式打开的话，将立即返回EOF；
 * 否则将试图分配一个缓冲区（如果读操作是以缓冲模式进行)
 * 建立缓冲区后，fillbuf()调用read填充此缓冲区，设置计数值和指针，并返回缓冲区中第一个字符
 * 随后进行的fillbuf()调用会发现缓冲区已经分配 */
int fillbuf(myFILE*fp){
    int bufsize;                                            //缓冲区大小
    if((fp->flag&(READ|myEOF|ERR))!=READ)return EOF;
    //myEOF、ERR的二进制表示为1000,10000，READ|myEOF|ERR=11001
    //如果flag状态不是读的话返回EOF(并且只能是READ，READ|myEOF、READ|ERR、READ|myEOF|ERR都不可以)
    bufsize=(fp->flag&UNBUF)?1:BUFSIZ;
    //UNBUF表示读取文件为不缓冲形式，此时缓冲区大小设为1
    if(fp->base==nullptr)if((fp->base=(char*)malloc(bufsize))==nullptr)return EOF;
    //如果缓冲区指针为空，则新建一个，并检查如果创建失败则返回EOF
    fp->ptr=fp->base;
    fp->cnt=(int)read(fp->fd,fp->ptr,bufsize);
    //如果缓冲区不为空，调用read读取文件存入缓冲区，并将当前访问的字符指针指向缓冲区
    //并将文件剩余字符数cnt更新
    if(--fp->cnt<0){                                         //先将--cnt表示向下读一个字符，如果此时cnt<0
        if(fp->cnt==-1)fp->flag|=myEOF;             //cnt=-1说明读到文件末尾(read返回的是0)
        else fp->flag|=ERR;                                //否则说明发生错误(read返回负数)
        fp->cnt=0;
        return EOF;
    }
    //注意：到达文件结尾和出错都是返回EOF，区别是前者会将flag的myEOF位置1，后者会将flag的ERR位置1
    //上游可以通过feof和ferror函数进行判断
    return (unsigned char)*fp->ptr++;               //返回当前指向的缓冲区的字符
}
// 练习8-2
typedef struct{
    int cnt,fd;char*ptr,*base;
    struct{
        unsigned int read:1,write:1,unbuf:1,eof:1,err:1;
    }flag;
}myfile;
myfile iobb[OPEN_MAX];
myfile*fopen_bits(char*name,const char*mode){
    int fd;
    myfile*fp;
    if(*mode!='r'&&*mode!='w'&&*mode!='a')return nullptr;
    for(fp=iobb;fp<iobb+OPEN_MAX;fp++)if(!fp->flag.read&&!fp->flag.write)break;
    if(fp>iobb+OPEN_MAX)return nullptr;
    if(*mode=='w')fd=creat(name,PERMS);
    else if(*mode=='a'){
        if((fd=open(name,O_WRONLY,0))==-1)fd=creat(name,PERMS);
        lseek(fd,0L,2);
    }else fd=open(name,O_RDWR,0);
    if(fd==-1)return nullptr;
    fp->fd=fd;
    fp->cnt=0;
    fp->base=nullptr;
    if(*mode=='r')fp->flag.read=1,fp->flag.write=0;
    else if(*mode=='w')fp->flag.read=0,fp->flag.write=1;
    else fp->flag.read=fp->flag.write=1;
    return fp;
}
int fillbuf_bits(myfile*fp){
    int bufsize;
    if(!fp->flag.read||fp->flag.eof||fp->flag.err)return EOF;
    bufsize=(fp->flag.unbuf)?1:BUFSIZ;
    if(!fp->base)if(!(fp->base=(char*)malloc(bufsize)))return EOF;
    fp->ptr=fp->base;
    fp->cnt=(int)read(fp->fd,fp->ptr,bufsize);
    if(--fp->cnt<0){
        if(fp->cnt==-1)fp->flag.eof=1;
        else fp->flag.err=1;
        fp->cnt=0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}
// 练习8-3
int flushbuf(int x,myfile*fp){
    int bufsize,n;
    if(!fp->flag.write||fp->flag.eof||fp->flag.err)return EOF;
    if(!fp->base&&!fp->flag.unbuf){
        //如果还未分配缓冲区且写文件为缓冲形式
        //如果这时写文件本身就是不缓冲模式的话则不要需要操作直接返回字符即可
        if(!(fp->base=(char*)malloc(BUFSIZ)))fp->flag.unbuf=1;
        //如果分配失败，不能直接返回EOF，而是应该以不缓冲模式写文件
        else fp->ptr=fp->base,fp->cnt=BUFSIZ-1;
        //分配成功，将写指针指向缓冲区，剩余字符数为BUFSIZ-1(实际上就是缓冲区大小)
    }
    if(fp->flag.unbuf){
        //如果已分配缓冲区且写文件为不缓冲模式
        bufsize=1;
        n=(int)write(fp->fd,&x,bufsize);
        fp->ptr=fp->base=nullptr,fp->cnt=0;
        if(x==EOF)return x;
    }else{
        //如果已分配缓冲区且写文件为缓冲模式
        bufsize=(int)(fp->ptr-fp->base);
        n=(int)write(fp->fd,fp->ptr,bufsize);
        fp->ptr=fp->base,fp->cnt=BUFSIZ-1;
    }
    if(n!=bufsize){     //传输字符数不等于缓冲区大小，说明发生错误
        fp->flag.err=1;
        return EOF;
    }
    return x;           //返回当前字符x
}
int fflush(myfile*fp){
    int res=0;
    if(!fp){
        for(auto&i:iobb)if(!fflush(&i))res=EOF;
    }else{
        if(fp->flag.write&&!fp->flag.err)flushbuf(EOF,fp);
        else res=EOF;
    }
    return res;
}
int fclose(myfile*fp){
    int ret;
    if((ret=fflush(fp))!=EOF){
        free(fp->base);
        fp->base=fp->ptr =nullptr;
        fp->fd=fp->cnt=0;
        fp->flag={0};
    }
    return 0;
}
// 练习8-4
int fseek(myfile*fp,long offset,int origin){
    int res=0;
    if(fp->flag.read){
        offset-=fp->cnt;
        res=(int)lseek(fp->fd,offset,origin);
        fp->cnt=0;
    }else if(fp->flag.write){
        res=fflush(fp);
        if(res!=EOF)res=(int)lseek(fp->fd,offset,origin);
    }
    return res<0?EOF:0;
}
/* 例 8.6 fsize()：ls命令的一种特殊形式
 * 同例8.5，此程序也是伪代码展示，
 * 并且还对<sys/types.h>、<sys/stat.h>、<dirent.h>等文件中已定义了的结构进行了模拟*/
/* fsize()功能为打印命令行参数表中指定的所有文件的长度，如果其中文件是目录则对此目录递归调用自身
 * 如果，命令行中没有参数，则fsize()处理当前目录
 * 由于在不同版本的系统中目录格式不一，为分离出不可移植的部分，将此任务分为两部分
 * 外层定义一个称为Direct的结构和3个函数opendir()、readdir()、closedir()用以提供与系统无关的对目录项中
 * 名字和i结点编号的访问，并以此接口编写fsize()，然后再讨论如何在与Version 7和System V UNIX系统目录结构
 * 相同的系统中实现这三个函数 */
// 结构体Dirent包含i结点编号和文件名，最大长度由系统设定(NAME_MAX)
 typedef struct Dirent{                         //可移植的目录项结构
     long ino{};                                     //i结点编号
     char name[NAME_MAX+1]{};            //文件名加字符串结束符
 }Dirent;
 typedef struct DIR{                           //最小的DIR：无缓冲等特性
     int fd{};                                       //目录的文件描述符
     Dirent d;                                      //目录项
 }DIR;
 DIR*opendir(char*dirname);
 Dirent*readdir(DIR*dfd);
 void closedir(DIR*dfd);
struct stat{                                //由stat返回的i结点信息
    dev_t st_dev;                         //i结点设备
    ino_t st_ino;                          //i结点编号
    short st_mode;                      //模式位
    short st_nlink;                       //文件的总链接数
    short st_uid;                         //所有者的用户id
    short st_gid;                         //所有者的组id
    dev_t st_rdev;                       //用于特殊的文件
    off_t st_size;                        //用字符数表示的文件长度
    time_t st_atime;                   //上一次访问的时间
    time_t st_mtime;                  //上一次修改的时间
    time_t st_ctime;                   //上一次改变i结点的时间
};
//stat将文件的i结点信息填充到结构体stbuf中，fstat类似于stat，后者以文件标识符作为参数
int stat(char*,struct stat*);
int fstat(int,struct stat*);
 void fsize(const char*),dirwalk(char*,void(*fcn)(char*));
 int fsizemain(int argc,char**argv){
     if(argc==1)fsize(".");
     else while(--argc>0)fsize(*++argv);
     return 0;
 }
 /*st_mode项包含了描述文件的一系列标志，在<sys/stat.h>定义，如:
    #define S_IFMT 016000   //文件的类型
    #define S_IFDIR 004000  //目录
    #define S_IFCHR 002000  //特殊字符
    #define S_IFBLK 006000  //特殊块
    #define S_IFREG 010000  //普通
  */
/* 由于fsize()对每个目录都调用dirwalk()，而dirwalk()调用fsize()
 * 因此这两个函数实际是相互递归调用的 */
void fsize(char*name){
     struct stat stbuf{};
     if(stat(name,&stbuf)==-1){
         fprintf(stderr,"fisze: can't access %s\n",name);
         return;
     }
     if((stbuf.st_mode&S_IFMT)==S_IFDIR)dirwalk(name,fsize);    //如果类型是目录，则递归调用dirwalk()
     printf("%8lld %s",stbuf.st_size,name);                               //不是目录的话直接输出文件长度
 }
/* 函数dirwalk()是一个通用的函数，它对目录中每个文件都调用函数fcn一次
 * 首先打开目录，循环遍历其中每个文件，并对每个文件调用该函数，然后关闭目录返回
 * 其中每次调用readdir将返回一个指针，指向下一个文件的信息，如果目录中已没有待处理文件则返回nullptr
 * 每个目录都包含自身"."和父目录".."的项目，在处理时必须跳过，否则将导致无限循环   */
void dirwalk(char*dir,void(*fcn)(char*)){
    char name[MAX_PATH];
    Dirent*dp;
    DIR*dfd;
    if(!(dfd=opendir(dir))){                                                    //打开目录失败
        fprintf(stderr,"dirwalk: can't open %s\n",dir);
        return;
    }
    while((dp=readdir(dfd))){
        if(!strcmp(dp->name,".")||!strcmp(dp->name,".."))continue;      //跳过目录本身的目录项和父目录
        if(strlen(dir)+strlen(dp->name)+2>sizeof(name))                     //目录名超过最大名字长度
            fprintf(stderr,"dirwalk: name %s/%s too long\n",dir,dp->name);
        else{
            sprintf(name,"%s/%s",dir,dp->name);                              //将目录中的文件名存入name
            (*fcn)(name);                                                                  //对文件名调用fsize()
        }
    }
    closedir(dfd);
}
/* 上述程序与目录的格式无关，下面要在具体的某个系统上提供一个opendir、readdir和closedir的最简单版本
 *  据说以下函数适用于Version 7和System V UNIX系统，模拟使用了<sys/dir.h>中的目录信息 */
// 这个direct适用于Version 7和System V UNIX系统，与前面的Dirent都代表目录项结构，注意两者区别
struct direct{                              //目录项
    ino_t d_ino{};                          //i结点编号
    char d_name[DIRSIZ/4]{};        //长文件名不包含'\0'
    //由于系统中的DIRSIZ值过大超过strncpy最多复制字符数的范围，所以取DIRSIZ/4
};
// opendir打开目录供readdir使用
// 首先打开目录，验证此文件是一个目录(调用系统调用fstat)，然后分配一个目录结构并保存信息

DIR*opendir(char*dirname){
    int fd;
    struct stat stbuf{};
    DIR*dp;
    if((fd=open(dirname,O_RDONLY,0))==-1||fstat(fd,&stbuf)==-1||(stbuf.st_mode&S_IFMT)!=S_IFDIR
       ||!(dp=(DIR*)malloc(sizeof(DIR))))return nullptr;
    //以只读模式打开dirname目录，文件标识符赋给fd
    // 如果打开失败、获取i结点信息失败、打卡的不是目录、目录结构DIR申请失败，返回空指针
    dp->fd=fd;      //将文件标识符为fd的目录结构dp返回
    return dp;
}
// closedir关闭由opendir打开的目录并释放内存空间
void closedir(DIR*dfd){
    if(dfd){
        close(dfd->fd);
        free(dfd);
    }
}
/* readdir使用read系统调用按顺序读取每个目录项
 * 如果某个目录位置当前没有使用(可能是因为删除了文件)，则结点编号为0并跳过该位置
 * 否则将i结点编号和目录名放在一个static类型结构中，并给用户返回一个指向此结构的指针
 * 每次调用readdir函数将覆盖前一次调用获得的信息 */
Dirent*readdir(DIR*dfd){
    struct direct dirbuf;
    static Dirent d;
    while(read(dfd->fd,(char*)&dirbuf,sizeof dirbuf)==sizeof dirbuf){    //每次读一个目录项，直到读不了为止
        if(!dirbuf.d_ino)continue;                                             //注意中间碰到i结点为空是continue不是break
        d.ino=(long)dirbuf.d_ino;                                                        //将direct转化为可移植的Dirent
        strncpy(d.name,dirbuf.d_name,DIRSIZ/4);
        d.name[DIRSIZ/4-1]='\0';
        return&d;
    }
    return nullptr;
}
// 练习8-5
void fsize_extend(char*name){
    struct stat stbuf{};
    char fname[MAX_PATH];
    Dirent*dp;
    DIR*dfd;
    if(stat(name,&stbuf)==-1){
        fprintf(stderr,"fisze: can't access %s\n",name);
        return;
    }
    if((stbuf.st_mode&S_IFMT)==S_IFDIR){
        if(!(dfd=opendir(name))){
            fprintf(stderr,"dirwalk: can't open %s\n",name);
            return;
        }
        while((dp=readdir(dfd))){
            if(!strcmp(dp->name,".")||!strcmp(dp->name,".."))continue;
            if(strlen(name)+strlen(dp->name)+2>sizeof(name))
                fprintf(stderr,"dirwalk: name %s/%s too long\n",name,dp->name);
            else{
                sprintf(fname,"%s/%s",name,dp->name);
                fsize(fname);
            }
        }
        closedir(dfd);
    }
    printf("%d\n%llu\n%d\n%d\n%d\n%d\n%d\n%lld\n%ld\n%ld\n%ld\n%s",
           stbuf.st_dev,stbuf.st_ino,stbuf.st_mode,stbuf.st_nlink,stbuf.st_uid,stbuf.st_gid,
           stbuf.st_rdev,stbuf.st_size,stbuf.st_atime,stbuf.st_ctime,stbuf.st_mtime,name);
}
// 例 8.7 存储分配程序：相对于part5的程序，本例的版本可以以任意次序调用malloc()和free()
/* 空闲块包含位于空闲块开始处的控制信息称为“头部”，为了简化块的对齐，
 * 所有块的大小都必须是头部大小的整数倍，且头部已正确地对齐。通过联合实现*/
typedef long Align;
typedef union header Header;
union header{                     //按long类型的边界对齐(假定long为最受限的类型)
    struct{
        union header*ptr;       //空闲块链表中的下一块
        unsigned size;            //本块的长度(相对于头结点长度的倍数)
    }s;
    Align x;                          //Align(long)仅仅用于强制每个头部在最坏情况下满足对其要求
};
/* malloc()申请的长度外还要额外算上一个记录申请块信息的Header，因此实际申请的空间长度要加一个Header长度
 * 同时申请空间的长度不是Header长度整数倍时，最后不足的部分按1个单元算(保证空间足够并且对齐)；
 * 变量base表示空闲块链表的头部，首次调用malloc()时，freep为NULL，系统将创建一个退化的空闲块链表
 * 这个链表只包含一个大小为0的块，且该块指向自己。
 * 任何情况下当请求空闲空间时都将搜索空闲块链表，搜索从上一次找到空闲块的地方(freep)开始
 * 该策略可以保证链表是均匀的，如果找到的块太大，则将其尾部返回给用户，这样大块的头部只需要修改size
 * 字段即可。任何情况下，返回给用户的指针都指向块内的空闲存储空间，即比指向头部的指针大一个单元 */
static Header base;      //空闲链表头
static Header*freep;    //空闲链表的当前指针(上一次被申请空间的前一个空闲块)
static Header*morecore(unsigned);
void myfree(void*);
void*mymalloc(unsigned nbytes){
    Header*p,*prevp;    //p用于搜索符合申请条件的空闲块并返回，prevp用于保存p前一个空闲块并保存到freep
    // nuits考虑到长度的倍数不能取整的情况因此在结果后面+1，但这样的话如果正好能取整的情况下会多加1
    // 因此在实际申请长度的基础上-1再除以sizeof(Header)后+1
    unsigned nunits=(nbytes+sizeof(Header)-1)/sizeof(Header)+1;
    // 将freep赋给prevp，如果此时的freep为空说明还没有找过空闲块
    if(!(prevp=freep)){
        base.s.ptr=freep=prevp=&base;                       //初始化base，base为一个退化的空闲块链表
        base.s.size=0;
    }
    for(p=prevp->s.ptr;;prevp=p,p=p->s.ptr){             //遍历空闲链表，将prep和p分别沿链表移动
        if(p->s.size>=nunits){                                    //如果找到满足申请长度的块
            //如果长度正好合适则将prevp的下一个块指向p下一个块
            //表示从空闲块链表删除当前块(被malloc()分配的块)
            if(p->s.size==nunits)prevp->s.ptr=p->s.ptr;
            else{                                                       //如果空间块较长
                p->s.size-=nunits;
                //将空闲块指针移动到原本大小-nunits个单元的位置
                //并将p的大小置为nunits，表示原来空间末尾长度为nunits的空间被分配
                p+=p->s.size;
                p->s.size=nunits;
            }
            freep=prevp;                                            //将freep指向prevp
            return(void*)(p+1);                                     //将被分配的块返回(Header之后的首地址)
        }
        //如果p遍历到了开始的位置仍然没有找到合适的空间，调用morecore()并将空闲空间指针赋给p，继续遍历
        //如果p为空说明申请失败，返回空指针
        if(p==freep)if(!(p=morecore(nunits)))return nullptr;
    }
}
/* 函数morecore()用于向操作系统请求存储空间，其实现细节因系统的不同而不同
 * 由于向操作系统请求存储空间是一个开销很大的操作，因此不希望每次调用malloc()函数时都执行该操作
 * 基于这个考虑，morecore()每次请求至少NALLOC个单元，这个较大的块将根据需要分成较小的块
 * 在设置完size字段后，morecore()调用free()将多余的存储空间插入到空闲空间中*/
static Header*morecore(unsigned nu){
    char*cp;
    Header*up;
    if(nu<NALLOC)nu=NALLOC;                                  //一次分配不足NALLOC个单元的默认按NALLOC分配
    cp=(char*)sbrk((int)(nu*sizeof(Header)));                 //通过系统调用sbrk返回申请到的空间的char*指针
    if(cp==(char*)-1)return nullptr;                               //分配失败返回空指针
    up=(Header*)cp;                                                   //将char*转为Header*然后赋给up
    up->s.size=nu;
    myfree((void*)(up+1));                                         //调用free()将申请到的空间插入空闲空间，注意+1
    return freep;
}
/* free()从freep指向的地址开始，逐个扫描空闲块链表，寻找可以插入空闲块的地方
 * 该位置可能在两个空闲块之间，也可能在链表的末尾，在任何一种情况下，如果被释放的块与另一空闲块相邻
 * 则将这两个块合并起来，合并两个块的操作只要设置指针指向正确的位置并设置正确大小即可 */
void myfree(void*ap){
    Header*bp,*p;
    //考虑到在正常的接口中free()的参数是malloc申请空间中第一个空闲单元(不算块头)，因此bp指向传入指针-1位置
    bp=(Header*)ap-1;
    //从freep位置开始遍历空闲块链表，当bp的位置在两个相邻空闲块之间、链表末尾后面或开头前面时跳出循环
    //(p>=p->s.ptr说明p是最后一个空闲块，p所指向的下一个块是第一个块)
    for(p=freep;!(bp>p&&bp<p->s.ptr);p=p->s.ptr)if(p>=p->s.ptr&&(bp>p||bp<p->s.ptr))break;
    if(bp+bp->s.size==p->s.ptr){                //如果bp加上其长度正好等于p下一个块开始位置
        bp->s.size+=p->s.ptr->s.size;           //直接将bp和原来p指向的下一个块合并
        bp->s.ptr=p->s.ptr->s.ptr;
    }else bp->s.ptr=p->s.ptr;                      //否则的话，将bp的下一个块指向原来p指向的下一个块
    if(p+p->s.size==bp){                            //如果p加上其长度正好等于bp
        p->s.size+=bp->s.size;                     //直接将p和bp合并
        p->s.ptr=bp->s.ptr;
    }else p->s.ptr=bp;                                //否则的话，将p的下一个块指向bp
    freep=p;                                              //将freep指向p(bp的前一个空闲块)
}
// 练习8-6，8-7，8-8
void*mycalloc(int n,unsigned bytes){
    char*p=(char*)mymalloc(n*bytes),*ip=p;
    if(!p)return nullptr;
    else for(int i=0;i<((Header*)p-1)->s.size;i++)*p++=0;
    return ip;
}
void mallocerror(unsigned nbytes){
    if(nbytes<=0){
        fprintf(stderr,"invalid size");
        exit(1);
    }
}
void mybfree(void*p,int n){
    p=mymalloc(n);
    free(p);
}