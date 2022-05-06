#include "queue.h"

#include <iostream>

int ThreadSafeQueue::size(){
    return this->queue_size;
}

void ThreadSafeQueue::put(Task* item){
    pthread_mutex_lock(&mutex);
    this->queue->push_back(item);
    this->queue_size += 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&condition);
}

void ThreadSafeQueue::batch_put(std::vector<Task*> items){
    int size = items.size();
    for(int i = 0; i < size; i ++){
        Task* item = items[i];
        this->put(item);
    } 
}

Task* ThreadSafeQueue::pop(){
    pthread_mutex_lock(&mutex);
    while (this->queue_size == 0){
    /* 用while不用if的原因
       pthread_cond_signal在多处理器上可能同时唤醒多个线程，而当你只想让一个线程处理某个任务时，其它被唤醒的线程就需要继续wait
       此时while循环的意义就体现在这里了，而且标准只要求pthread_cond_signal至少唤醒一个pthread_cond_wait上的线程
       因此有些实现为了简单在单处理器上也会唤醒多个线程.
       在线程池中，pthread_cond_broadcast唤醒全部线程，但我们通常只需要一部分线程去做执行任务，所以其它的线程需要继续wait，所以强烈推荐此处使用while循环
    */
        pthread_cond_wait(&condition, &mutex);
    }
    Task* item = this->queue->front();
    this->queue->pop_front();
    this->queue_size -= 1;
    pthread_mutex_unlock(&mutex);
    return item;
}
