#include "part1.cpp"
#include "part2.cpp"
#include "part3.cpp"
#include "part4.cpp"
#include "part5.cpp"
#include "part6.cpp"
#include "part7.cpp"
#include "part8.cpp"    
#include "test.cpp"
#include <ctime>
#include "shared.h"
int main(int argc,char*argv[]) {
    clock_t s,e;
    s=clock();
    e=clock();
    cout<<endl<<"运行时间："<<(double)(e-s)/CLOCKS_PER_SEC<<'s';
    exit(0);
}


