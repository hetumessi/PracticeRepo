#include "task.h"

#include <thread>
#include <chrono>

void Task::set_result(int result){
    pthread_mutex_lock(&mutex);
    this->result = result;
    this->done = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&condition);
}

int Task::get_result(){
    pthread_mutex_lock(&mutex);
    int r = 0;
    if ( this->done ){
        r = this->result;
    } else{
        pthread_cond_wait(&condition, &mutex);
        r = this->result;
    }
    pthread_mutex_unlock(&mutex);
    return r;
}

int Task::callable(){
    /* chrono是一个time library, 源于boost，现在已经是C++标准
        要使用chrono库，需要#include<chrono>，其所有实现均在std::chrono namespace下
        chrono库主要包含了三种类型：时间间隔Duration、时钟Clocks和时间点Time point。
        1.duration表示一段时间间隔，用来记录时间长度，可以表示几秒钟、几分钟或者几个小时的时间间隔，duration的原型是：
            template<class Rep, class Period = std::ratio<1>> class duration;
        其中第一个模板参数Rep是一个数值类型，表示时钟个数；
        第二个模板参数是一个默认模板参数std::ratio，它的原型是：
            template<std::intmax_t Num, std::intmax_t Denom = 1> class ratio;
            其中第一个模板参数Num代表分子，Denom代表分母，分母默认为1，ratio代表的是一个分子除以分母的分数值
        标准库为了方便使用，就定义了一些常用的时间间隔，如时、分、秒、毫秒、微秒和纳秒，在chrono命名空间下，它们的定义如下：
        typedef duration <Rep, ratio<3600,1>> hours;
        typedef duration <Rep, ratio<60,1>> minutes;
        typedef duration <Rep, ratio<1,1>> seconds;
        typedef duration <Rep, ratio<1,1000>> milliseconds;
        typedef duration <Rep, ratio<1,1000000>> microseconds;
        typedef duration <Rep, ratio<1,1000000000>> nanoseconds;
        通过定义这些常用的时间间隔类型，我们能方便的使用它们，比如线程的休眠：
        std::this_thread::sleep_for(std::chrono::seconds(3)); //休眠三秒
        std::this_thread::sleep_for(std::chrono:: milliseconds (100)); //休眠100毫秒

        2.Time point表示一个时间点，用来获取1970.1.1以来的秒数和当前的时间
          time_point必须要clock来计时，time_point有一个函数time_from_eproch()用来获得1970年1月1日到time_point时间经过的duration

        3.Clocks表示当前的系统时钟，内部有time_point, duration, Rep, Period等信息，它主要用来获取当前时间，以及实现time_t和time_point的相互转换
          Clocks包含三种时钟： 
        　system_clock：从系统获取的时钟；
        　steady_clock：不能被修改的时钟；
        　high_resolution_clock：高精度时钟，实际上是system_clock或者steady_clock的别名。
          可以通过now()来获取当前时间点
          通过时钟获取两个时间点之相差多少个时钟周期，我们可以通过duration_cast将其转换为其它时钟周期的duration
    */
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    return ms.count()/1000;
}
