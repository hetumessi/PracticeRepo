/* 已知基类ShapeFactory的声明如下：
const float pi=3.1416;
class ShapeFactory
{
    public:
    ShapeFactory(){};
    virtual ~ShapeFactory(){};
    virtual float Circumstance(){return 0;};
};
    ShapeFactory *Create(float a,float b,float c);
    ShapeFactory *Create(float a,float b,float c,float d);
    ShapeFactory *Create(float r);
请写出三角形(Triangle)、四边形(Quadrangle)、圆形(Circle)三个派生类，构造函数分别传入三边/四边/半径的长度
（不用检查是否符合三角形、矩形、圆的条件，没有异常输出），重写出求周长的函数（Circumstance函数）。
然后实现基类的Create函数，这里重载的三个Create函数，分别生成三角形、四边形、圆形的对象。
比如三角形类为Triangle：
ShapeFactory * ShapeFactory::Create(float a,float b,float c)
{
    ShapeFactory *p=new Triangle(a,b,c);
    return p;
}
如果三角形输入的三边长度是 3 4 5，四边形输入的四条边的长度是2 3 4 7，圆的半径是3，则要求程序运行能够得到如下的提示和输出：
输入三角形的三边长度：3 4 5
三角形的周长：12
输入四边形的四边长度：2 3 4 7
四边形的周长：16
输入圆的半径：3
圆的周长为：18.8496  
#include<iostream>
#define PAI 3.1415926
using namespace std;
class ShapeFactory
{
    public:
    ShapeFactory(){};
    virtual ~ShapeFactory(){};
    virtual float Circumstance(){return 0;};
    ShapeFactory *Create(float a,float b,float c);
    ShapeFactory *Create(float a,float b,float c,float d);
    ShapeFactory *Create(float r);
};
class Triangle:public ShapeFactory
{
    float t1,t2,t3;
    public:
    Triangle(float a,float b,float c):t1(a),t2(b),t3(c){}
    virtual float Circumstance()
    {
        return t1+t2+t3;
    }
};
class Quadrangle:public ShapeFactory
{
    float q1,q2,q3,q4;
    public:
    Quadrangle(float a,float b,float c,float d):q1(a),q2(b),q3(c),q4(d){}
    virtual float Circumstance()
    {
        return q1+q2+q3+q4;
    }
};
class Circle:public ShapeFactory
{
    float r;
    public:
    Circle(float a):r(a){}
    virtual float Circumstance()
    {
        return 2*PAI*r;
    }
};
ShapeFactory* ShapeFactory::Create(float a,float b,float c)
{
    ShapeFactory *p=new Triangle(a,b,c);
    return p;
}
ShapeFactory* ShapeFactory::Create(float a,float b,float c,float d)
{
    ShapeFactory *p=new Quadrangle(a,b,c,d);
    return p;
}
ShapeFactory* ShapeFactory::Create(float r)
{
    ShapeFactory *p=new Circle(r);
    return p;
}
int main()
{
    float ta,tb,tc,qa,qb,qc,qd,r;
    ShapeFactory shape,*s;
    cin>>ta>>tb>>tc>>qa>>qb>>qc>>qd>>r;
    cout<<"输入三角形的三边长度：";
    s=shape.Create(ta,tb,tc);
    cout<<ta<<' '<<tb<<' '<<tc<<endl;
    cout<<"三角形的周长："<<s->Circumstance()<<endl;
    cout<<"输入四边形的四边长度：";
    s=shape.Create(qa,qb,qc,qd);
    cout<<qa<<' '<<qb<<' '<<qc<<' '<<qd<<endl;
    cout<<"四边形的周长："<<s->Circumstance()<<endl;
    cout<<"输入圆的半径：";
    s=shape.Create(r);
    cout<<"圆的周长为："<<s->Circumstance()<<endl;
}  */

/* 实现带日期的时钟类，具体要求如下：已知时钟类的定义如下：
#include<iostream>
using namespace std;
bool leap(int year)
{
    if(year%400==0||(year%4==0 && year % 100!=0))return true;
    return false;
}
class Clock{public:Clock(int h,int m,int s){
        hour =(h>23? 0:h);
        minute = (m>59?0:m);
        second = (s>59?0:s);}
    virtual void run(){
        second = second+1;
        if (second>59){
            second =0;
            minute+=1;}
        if (minute>59){
            minute =0;
            hour+=1;}
        if (hour>23){
            hour =0;}
    }
    virtual void showTime(){
        cout<<"Now:"<<hour<<":"<<minute<<":"<<second<<endl;}
    int getHour(){return hour;}
    int getMinute(){return minute;}
    int getSecond(){return second;}
    protected:
    int hour;int minute;int second;
};
日期类定义如下：
class Date{
    public:
    Date(int y=1996,int m=1,int d=1){
    if (m>12||m<1){m=1;}
    if(d>days(y,m)){day = 1;}
    day =d;year =y;month =m;};
    int days(int year,int month);
    void NewDay();
    void showTime(){
    cout<<year<<"-"<<month<<"-"<<day<<endl;}
    protected:int year;int month;int day;
};
int main(){
    int h,m,s,day,month,year;
    cin>>h>>m>>s>>day>>month>>year;
    ClockWithDate cd1(h,m,s,day,month,year);
    cd1.showTime();
    cout<<"现在运行x秒:";
    int x;
    cin>>x;
    for(int i=0;i<x;++i)cd1.run();
    cd1.showTime();
    return 0;}
需要类外实现Date类的days方法，根据年和月，返回该年该月对应的天数，实现Date类的NewDay方法，该方法将Date代表的日期增加一天。
实现ClockWithDate类，它继承至Clock类和Date类，记录时间和日期，重新实现ClockWithDate类的showTime方法和run方法。
showTime方法输出当的时间和日期，先输出时间再输出日期。run方法每次将现在的时间增加一秒，并且当时间超过23：59：59时，更新日期。
比如某次程序运行输入当前时间是：1 1 1 7 10 2000（2000年10月7号1点1分1秒），然后输入运行时间x: 5,则程序运行的输入输出如下：
输入：1 1 1 7 10 2000
5
输出：
Now:1:1:1
2000-10-7
现在运行x秒:Now:1:1:6
2000-10-7 
int Date::days(int year,int month)
{
    int ymd[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(leap(year)!=0&&month==2)return ymd[month-1]+1;
    return ymd[month-1];
}
void Date::NewDay()
{
    day++;
    if(day>days(year,month))day=1,month++;
    if(month>12)month=1,year++;
}
class ClockWithDate:public Clock,public Date
{
    public:
    ClockWithDate(int h,int m,int s,int d,int mon,int y):Clock(h,m,s),Date(y,mon,d){}
    virtual void showTime();
    virtual void run();
};
void ClockWithDate::showTime()
{
    Clock::showTime();
    Date::showTime();
}
void ClockWithDate::run()
{
    second++;
    if(second==60)second=0,minute++;
    if(minute>=60)minute=0,hour++;
    if(hour>=24)hour=0,NewDay();
}
int main(){
    int h,m,s,day,month,year;
    cin>>h>>m>>s>>day>>month>>year;
    ClockWithDate cd1(h,m,s,day,month,year);
    cd1.showTime();
    cout<<"现在运行x秒:";
    int x;
    cin>>x;
    for(int i=0;i<x;++i)cd1.run();
    cd1.showTime();
}      */