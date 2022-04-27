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
    /* int shmget(key_t key, size_t size, int flag);
        1.key:标识符的规则
          key标识共享内存的键值：0/IPC_PRIVATE，当key的取值为IPC_PRIVATE，则函数shmget()将创建一块新的共享内存，
                              如果key的取值为0，而参数shmflg中设置了IPC_PRIVATE这个标志，则同样将创建一块新的共享内存。
        2.size:共享存储段的字节数
          size是要建立共享内存的长度。所有的内存分配操作都是以页为单位的。
          所以如果一段进程只申请一块只有一个字节的内存，内存也会分配整整一页(在i386机器中一页的缺省大小PACE_SIZE=4096字节)这样，
          新创建的共享内存的大小实际上是从size这个参数调整而来的页面大小。
        3.flag:读写的权限
          shmflg主要和一些标志有关。其中有效的包括IPC_CREAT和IPC_EXCL，它们的功能与open()的O_CREAT和O_EXCL相当。
          IPC_CREAT   如果共享内存不存在，则创建一个共享内存，否则打开操作。
          IPC_EXCL    只有在共享内存不存在的时候，新的共享内存才建立，否则就产生错误。
        返回值：成功返回共享存储的id，失败返回-1
    */
    int shmid = shmget((key_t)1111, sizeof(struct ShmEntry), 0666|IPC_CREAT);
    if (shmid == -1){
        std::cout << "Create share memory error!" << std::endl;
        return -1;
    }

    // 2. 连接到当前进程空间/使用共享内存
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
    shmdt(entry);

    // 4. 删除共享内存 
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
