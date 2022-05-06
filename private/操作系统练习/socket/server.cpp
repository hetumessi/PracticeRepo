#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

// 域套接字
#define SOCKET_PATH "./domainsocket"
#define MSG_SIZE 2048

int main()
{
    int socket_fd, accept_fd;
	int ret = 0;
	socklen_t addr_len;
	char msg[MSG_SIZE];
	struct sockaddr_un server_addr;

    // 1. 创建域套接字
	socket_fd = socket(PF_UNIX,SOCK_STREAM,0);
	if(-1 == socket_fd){
		std::cout << "Socket create failed!" << std::endl;
		return -1;
	}
    // 移除已有域套接字路径
	// int remove(const char *filename) 删除给定的文件名filename对应的文件(包括文件数据和inode等)，以便它不再被访问。
	remove(SOCKET_PATH);
    // 内存区域置0
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sun_family = PF_UNIX;
	strcpy(server_addr.sun_path, SOCKET_PATH);

    // 2. 绑定域套接字
	/* bind()函数：对socket定位(绑定指定的ip、port等)
	   int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
	   bind()用来设置给sockfd对应的socket一个名称，此名称由my_addr指向一sockaddr结构
	   bind()做的事情主要是：
		1.先通过fd找到对应的struct socket结构体；
		2.然后把address和socket绑定对应起来（调用sock->ops->bind函数）；
	   其实客户端也是可以用bind这个函数但没必要
	   理解下bind函数的作用：给这个socketfd绑定地址（IP:Port）。
	   客户端不需要是因为：如果没设置，内核在建连的时候会自动选一个临时的端口号作为本次TCP连接的地址。
	   一般客户端也不在意端口号，只要能和服务端正常通信就好，所以客户端一般没有bind调用。
	   服务端必须要用这个是因为服务端必须提前明确指定监听的IP和Port。
	*/
    std::cout << "Binding socket..." << std::endl;
	ret = bind(socket_fd,(sockaddr *)&server_addr,sizeof(server_addr));

	if(0 > ret){
		std::cout << "Bind socket failed." << std::endl;
		return -1;
	}
	
    // 3. 监听套接字
	/* 监听套接字
		对于监听套接字，不走数据流，只管理连接的建立。
		accept将从全连接队列获取一个创建好的socket（3次握手完成），对于监听套接字的可读事件就是全连接队列非空。
		对于监听套接字，只在乎可读事件。
		监听套接字的可读事件是：icsk_accept_queue 队列非空。
	   普通套接字
		普通套接字是走数据流的，也就是网络IO，针对普通套接字关注可读可写事件。
		在说socket的可读可写事件之前，先捋顺套接字的读写。
		套接字层是内核提供给程序员用来网络编程的，读写都是针对套接字而言：
		write数据到socketfd，大部分情况下数据写到socket的内存buffer就结束了，并没有发送到对端网络（异步发送）；
		read socketfd的数据，也只是从socket的内存buffer里读数据而已，而不是从网卡读（虽然数据是从网卡一层层递上来的）；
		也就是说，程序员是跟socket打交道，内核屏蔽了底层的细节。
		因此socket 的可读可写事件就很容易理解了：
		socketfd可读：socket buffer内有数据（阈值SO_RCLOWAT）；
		socketfd可写：socket buffer还有空间写（阈值SO_SNDLOWAT）；
	*/
	std::cout << "Listening socket..." << std::endl;
	/* listen()函数：等待连接
		int listen(int s, int backlog);
		listen()用来等待s的socket连线，backlog指定同时能处理的最大连接要求，如果连接数目达此上限则client端将收到ECONNREFUSED的错误
		Listen()并未开始接收连线，只是设置socket为listen模式，真正接收client端连线的是accept()
		其实socket()创建出来的套接字并无客户端和服务端之分，是listen函数让socket有了不一样的属性，成为监听套接字。
		listen()主要做两件事：
		1.通过fd找到struct socket结构体；
		2.调用sock->ops->listen函数（对应inet_listen）：
		  检查socket状态，类型，必须为流式套接字才能转化成监听套接字；
		  调用inet_csk_listen_start：
			初始化请求队列icsk->icsk_accept_queue
			套接字状态设置成TCP_LISTEN
			获取到之前bind的端口，如果没有设置就会用临时的端口
			把监听套接字加入到全局hash表中
	*/
	ret = listen(socket_fd, 10);
	if(-1 == ret){
		std::cout << "Listen failed" << std::endl;
		return -1;
	}
    std::cout << "Waiting for new requests." << std::endl;
	/* accept()函数：接受socket连线
		int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
		accept()用来接受s的socket连线，s的socket必需先经bind()、listen()函数处理过，当有连线进来时accept()会返回一个新的socket_fd，
		往后的数据传送与读取就是经由新的socket处理，而s的socket能继续使用accept()来接受新的连线要求
		提取出的是所监听套接字的等待连接队列中第一个连接请求
		连线成功时，addr所指的结构会被系统填入远程主机的地址数据，参数addrlen为scokaddr的结构长度
		新建立的套接字准备发送send()和接收数据recv()。
	    accept()主要是从队列icsk->icsk_accept_queue中取请求：
		如果队列为空，就看socket是否设置了非阻塞标识，非阻塞的就直接报错EAGAIN，否则阻塞线程等待。
	*/
    accept_fd = accept(socket_fd, NULL, NULL);
    
    bzero(msg,MSG_SIZE);

    while(true){
        // 4. 接收&处理信息
		/* recv()函数：经socket接收数据
			int recv(int s, void *buf, int len, unsigned int flags);
			recv()用来接收远端主机经指定的socket传来的数据，并把数据存到由buf指向的内存空间，len为可接收数据的最大长度
			flags指定接收模式，一般设0
		*/
        recv(accept_fd, msg, MSG_SIZE, 0);
        std::cout << "Received message from remote: " << msg <<std::endl;
    }

    close(accept_fd);
	close(socket_fd);
	return 0;
}
