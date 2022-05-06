/*定义一个点类Point,并定义成员函数double Distance( Point p)实现 求该点到参数点的两点间的距离（欧几里得距离）。
编程实现: 输入两个点的坐标，创建两个点，调用Point类的Distance方法输出两个点的距离。在你的代码中除了实现Point类以外，还需一如下main函数：
int main(){
double a,b,c,d;
cin>>a>>b>>c>>d;
Point A(a,b),B(c,d);
cout<<setprecision(3)<<A.Distance(B)<<endl;
return 0;}
如输入：1 2 3 4回车
输出：2.83
提醒:用setprecision（3）函数设置输出精度为小数点后保持2位小数。该函数需要include<iomanip>文件。
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
class Point
{
    double x,y;
    public:
    Point(double a,double b):x(a),y(b){}
    double Distance(Point p);
    double Getx();
    double Gety();
};
double Point::Distance(Point p)
{
    double dx=x-p.Getx(),dy=y-p.Gety();
    return sqrt(dx*dx+dy*dy);
}
double Point::Getx()
{
    return x;
}
double Point::Gety()
{
    return y;
}
int main()
{
    double a,b,c,d;
    cin>>a>>b>>c>>d;
    Point A(a,b),B(c,d);
    cout<<setprecision(3)<<A.Distance(B)<<endl;
    return 0;
} */

/*实现User类的构造函数和AddUser方法添加新用户，实现int login(char *name,char * pass)方法，该方法接受用户名和密码，
判断用户名对应的密码是否正确，如果正确返回用户的编号，如果不正确返回-1。
User类的使用示意如下所示，在你的代码中除了实现User类以外，还需一如下main函数
int main()
{
    char name[10],name1[10],name2[10],pass[10],pass1[10],pass2[10];	
    cin>>name>>pass>>name1>>pass1>>name2>>pass2;	
    User user(name,pass);	
    user.AddUser(name1,pass1);	
    if (user.login(name2,pass2) >=0)	
    {	
        cout<<"Success Login!"<<endl;	
    }	
    else
    {	
        cout<<"Login failed!"<<endl;	
    }
    return 0;
}
例如输入：zhangsan 1234 test 1234567 test 123456回车
输出：Login failed!
例如输入：zhangsan 1234 test 1234567 test 1234567回车
输出：Success Login!   
#include<iostream>
#include<cstring>
using namespace std;
const int n=10;
class User
{
    char *name,*pass;
    char *namegroup[n],*passgroup[n];
    static int count;
    public:
    User(char *n,char *p)
    {
        AddUser(n,p);
    }
    void AddUser(char *name,char *pass);
    int login(char *name,char * pass);
};
int User::count=0;
void User::AddUser(char *name,char *pass)
{
    namegroup[count]=name,passgroup[count]=pass;
    count++;
}
int User::login(char *name,char *pass)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(strcmp(name,namegroup[i])==0&&strcmp(pass,passgroup[i])==0)
        return count;
    }
    return -1;
}
int main()
{
    char name[10],name1[10],name2[10],pass[10],pass1[10],pass2[10];	
    cin>>name>>pass>>name1>>pass1>>name2>>pass2;	
    User user(name,pass);	
    user.AddUser(name1,pass1);	
    if (user.login(name2,pass2) >=0)	
    {	
        cout<<"Success Login!"<<endl;	
    }	
    else
    {	
        cout<<"Login failed!"<<endl;	
    }
    return 0;
}*/
/*设计一个学生类Student，包含学生学号（最长10位）、姓名（不用支持中文,最长12字节）、三门课程成绩(成绩是单精度实数类型）等基本信息.
计算每门课程学生的平均成绩,成员函数 average1 ,average2 ,average3 ,分别返回三门课的平均成绩。
需实现Student的display成员函数，依次输出学号 姓名 和三门课的成绩，每个输出以空格隔开.
Student类的使用方法如下所示，在你的代码中除了实现Student类，还需引入以下代码：
int main(){
    Student *stu1,*stu2,*stu3;
    char name1[10],name2[10],name3[10];
    char num1[12],num2[12],num3[12];
    int grade1[3],grade2[3],grade3[3];
    cin>>num1>>name1>>grade1[0]>>grade1[1]>>grade1[2];
    cin>>num2>>name2>>grade2[0]>>grade2[1]>>grade2[2];
    cin>>num3>>name3>>grade3[0]>>grade3[1]>>grade3[2];
    stu1 = new Student(name1,num1,grade1[0],grade1[1],grade1[2]);
    stu2 = new Student(name2,num2,grade2[0],grade2[1],grade2[2]);
    stu3 = new Student(name3,num3,grade3[0],grade3[1],grade3[2]);
    stu1->display();
    stu2->display();
    stu3->display();
    cout<<"The average grade of course1:"<<setprecision(4)<<stu2->average1()<<endl;
    cout<<"The average grade of course2:"<<setprecision(4)<<stu2->average2()<<endl;
    cout<<"The average grade of course3:"<<setprecision(4)<<stu2->average3()<<endl;
    return 0;
}
上述代码执行时
输入：200906294 LiWeiwei 88 75 91 200902164 ChenHanfu 86 78 93 200908079 ZhanGaolin 94 69 97
输出：200906294 LiWeiwei 88 75 91回车
200902164 ChenHanfu 86 78 93回车
200908079 ZhanGaolin 94 69 97回车
The average grade of course1:89.33回车
The average grade of course2:67.33回车
The average grade of course3:93.67回车   
#include<iostream>
#include<iomanip>
using namespace std;
const int n=10;
class Student
{
    static double grades1,grades2,grades3;
    static int count;
    char *num,*name;
    float grade1,grade2,grade3;
    public:
    Student(char *names,char *number,double grade1,double grade2,double grade3);
    void display();
    double average1();
    double average2();
    double average3();
};
double Student::grades1=0;
double Student::grades2=0;
double Student::grades3=0;
int Student::count=0;
Student::Student(char *names,char *number,double grade1,double grade2,double grade3)
{
    num=number,name=names;
    this->grade1=grade1,this->grade2=grade2,this->grade3=grade3;
    grades1+=this->grade1,grades2+=this->grade2,grades3+=this->grade3;
    count++;
}
void Student::display()
{
    cout<<num<<' '<<name<<' '<<grade1<<' '<<grade2<<' '<<grade3<<endl;
}
double Student::average1()
{
    return grades1/count;
}
double Student::average2()
{
    return grades2/count;
}
double Student::average3()
{
    return grades3/count;
}
int main(){
    Student *stu1,*stu2,*stu3;
    char name1[10],name2[10],name3[10];
    char num1[12],num2[12],num3[12];
    int grade1[3],grade2[3],grade3[3];
    cin>>num1>>name1>>grade1[0]>>grade1[1]>>grade1[2];
    cin>>num2>>name2>>grade2[0]>>grade2[1]>>grade2[2];
    cin>>num3>>name3>>grade3[0]>>grade3[1]>>grade3[2];
    stu1 = new Student(name1,num1,grade1[0],grade1[1],grade1[2]);
    stu2 = new Student(name2,num2,grade2[0],grade2[1],grade2[2]);
    stu3 = new Student(name3,num3,grade3[0],grade3[1],grade3[2]);
    stu1->display();
    stu2->display();
    stu3->display();
    cout<<"The average grade of course1:"<<setprecision(4)<<stu2->average1()<<endl;
    cout<<"The average grade of course2:"<<setprecision(4)<<stu2->average2()<<endl;
    cout<<"The average grade of course3:"<<setprecision(4)<<stu2->average3()<<endl;
    return 0;
} */