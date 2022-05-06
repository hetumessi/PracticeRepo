#include "common.h"

#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

int main()
{
    struct ShmEntry *entry;

    // 1. 申请共享内存
    /*  int shmget(key_t key, size_t size, int flag);
        1.key:key标识共享内存的键值
        当key的取值为IPC_PRIVATE(==0)，则函数shmget()将创建一块新的共享内存
        当key的取值为大于0的32位整数：视参数shmflg来确定操作。通常要求此值来源于ftok返回的IPC键值
        2.size:size以字节为单位指定需要共享的内存容量
        3.flag:读写的权限
        shmflg是权限标志，它的作用与open函数的mode参数一样，
        如果要想在key标识的共享内存不存在时，创建它的话，可以与IPC_CREAT做或操作。共享内存的权限标志与文件的读写权限一样，
        举例来说，0644,它表示允许一个进程创建的共享内存被内存创建者所拥有的进程向共享内存读取和写入数据，同时其他用户创建的进程只能读取共享内存。
        返回值：成功返回共享存储的id，失败返回-1
    */
    int shmid = shmget((key_t)1111, sizeof(struct ShmEntry), 0666|IPC_CREAT);//IPC_CREAT=01000
    if (shmid == -1){
        std::cout << "Create share memory error!" << std::endl;
        return -1;
    }

    // 2. 连接到当前进程空间/使用共享内存
    /*  void *shmat(int shm_id, const void *shm_addr, int shmflg);
        第一个参数，shm_id是由shmget()函数返回的共享内存标识。
        第二个参数，shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
        第三个参数，shm_flg是一组标志位，通常为0。
        调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1
    */
    entry = (ShmEntry*)shmat(shmid, 0, 0);
    entry->can_read = 0;
    char buffer[TEXT_LEN];
    while (true){
        if (entry->can_read == 0){
            std::cout << "Input message>>> ";
            fgets(buffer, TEXT_LEN, stdin);
            strncpy(entry->msg, buffer, TEXT_LEN);
            std::cout << "Send message: " << entry->msg << std::endl;
            entry->can_read = 1;
        }
    }
    // 3. 脱离进程空间
    /* int shmdt(const void *shmaddr);
        参数shmaddr是shmat()函数返回的地址指针，调用成功时返回0，失败时返回-1. 
        该函数用于将共享内存从当前进程中分离。注意，将共享内存分离并不是删除它，只是使该共享内存对当前进程不再可用。
    */
    shmdt(entry);

    // 4. 删除共享内存 
    /* int shmctl(int shm_id, int command, struct shmid_ds *buf);
       与信号量的semctl()函数一样，用来控制共享内存
       第一个参数，shm_id是shmget()函数返回的共享内存标识符。
       第二个参数，command是要采取的操作，它可以取下面的三个值：
        IPC_STAT：把shmid_ds结构中的数据设置为共享内存的当前关联值，即用共享内存的当前关联值覆盖shmid_ds的值
        IPC_SET： 如果进程有足够的权限，就把共享内存的当前关联值设置为shmid_ds结构中给出的值
        IPC_RMID：删除共享内存段
       第三个参数，buf是一个结构指针，它指向共享内存模式和访问权限的结构。
    */
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
