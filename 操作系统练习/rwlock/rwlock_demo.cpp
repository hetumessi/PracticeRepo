#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

int num = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void*){
    int times = 10000;
    while(times --){
        pthread_rwlock_rdlock(&rwlock);
        pthread_mutex_lock(&mutex);
	    if (times % 1000 == 0){
            printf("print num in reader: num = %d\n", num);
            // sleep(1);
            // usleep(10);
	        }
        pthread_mutex_unlock(&mutex);
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}

void *writer(void*){
    int times = 1000;
    while(times --){
        pthread_rwlock_wrlock(&rwlock);
        pthread_mutex_lock(&mutex);
	    num += 1;
        pthread_mutex_unlock(&mutex);
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}


int main(){
    printf("Start in main function.\n");
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, &reader, NULL);
    pthread_create(&thread2, NULL, &reader, NULL);
    pthread_create(&thread3, NULL, &writer, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("Print in main function: num = %d\n", num);
    return 0;
}
/* 不加读写锁运行结果：
    Start in main function.
    Print in main function: num = 1000
    加上读写锁运行结果：
    Start in main function.
    print num in reader: num = 820
    print num in reader: num = 990
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    print num in reader: num = 1000
    Print in main function: num = 1000
*/
