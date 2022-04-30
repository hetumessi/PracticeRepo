#include <stdio.h>
#include <sys/types.h>
/* Unix域协议
   Unix域协议并不是一个实际的协议族，它只是在同一台主机上进行客户-服务器通信时，使用与在不同主机上的客户和服务器间通信时相同的API(套接口或XTI)的一种方法。
   当客户和服务器在同一台主机上时，Unix域协议是IPC通信方式的一种替代品。
   Unix域提供了两种类型的套接口：字节流套接口(与TCP类似)和数据报套接口(与UDP类似)。
*/
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
/* socket
	套接字，是内核对复杂的网络协议栈的API封装
	如果要进行网络编程，落到实处对程序员来讲就是socket编程。Linux网络编程甚至可以叫做套接字编程。
	Linux内核版本4.19为了方便，如果没特意说明协议，默认TCP协议
	一个基于Tcp的C/S的网络程序的基本构成：
	1.客户端和服务端都用socket调用创建套接字；
	2.服务端用bind绑定监听地址，用listen把套接字转化为监听套接字，用accept捞取一个客户端来的连接；
	3.客户端用connect进行建连，用write/read进行网络IO；
*/
#define SOCKET_PATH "./domainsocket"
#define MSG_SIZE 2048

int main()
{
    // fd：文件描述符。后面socket()返回的就是这个描述符
	int socket_fd;
	int ret = 0;
	char msg[MSG_SIZE];
/* 通用的套接字地址结构
struct sockaddr {
	__uint8_t       sa_len;         // total length 
	sa_family_t     sa_family;      // [XSI] address family 
	char            sa_data[14];    // [XSI] addr value (actually larger) (同时包括目标地址和端口信息)
};  
*/
/* internet形式的通用套接字地址结构
struct sockaddr_in {                //与sockaddr一样是16个字节并且信息排列顺序相同，可以互相转化且不会丢失任何信息
	__uint8_t       sin_len;
	sa_family_t     sin_family;
	in_port_t       sin_port;
	struct  in_addr sin_addr;
	char            sin_zero[8];
};
struct in_addr {  
	in_addr_t s_addr;  //internet地址
};
*/
/* Unix域套接字地址结构
sun_family只能是AF_LOCAL或AF_UNIX，而sun_path是本地文件的路径，通常将文件放在/tmp目录下
struct  sockaddr_un {
	unsigned char   sun_len;        // sockaddr len including null 
	sa_family_t     sun_family;     // [XSI] AF_UNIX 
	char            sun_path[104];  // [XSI] path name (gag) 
};
*/
	struct sockaddr_un server_addr;

    // 1. 创建域套接字
	/* socket 函数
		int socket(int family, int type, int protocol)
		family为地址族，也就是IP地址类型，常用的有AF_INET和AF_INET6。AF是“Address Family”的简写，INET是“Inetnet”的简写
		AF_INET表示IPv4地址，例如127.0.0.1；AF_INET6表示IPv6地址，例如1030::C9B4:FF12:48AA:1A2B
		(AF_和PF_协议簇表达的意思相同或在某些系统中差别很小，一般可以互相替换)
		PF_UNIX (也称作PF_LOCAL) 套接字族用来在同一机器上的提供有效的进程间通讯，即unix域套接字
		type为数据传输方式/套接字类型，常用的有SOCK_STREAM（流格式套接字/面向连接的套接字）和SOCK_DGRAM（数据报套接字/无连接的套接字）
		protocol表示传输协议，常用的有IPPROTO_TCP和IPPTOTO_UDP，分别表示TCP传输协议和UDP传输协议，传入0则表示使用默认协议

		这个函数(系统api)主要做两件事情：
		第一件事：调用socket_create函数创建好socket相关的结构体，主要是struct socket，还有与之关联的socket sock结构，具体网络协议对应的结构体
		第二件事：调用sock_map_fd函数创建好struct file这个结构体，并与第一步创建出的struct socket关联起来；
		socket()只负责创建出适配具体网络协议的资源（内存、结构体、队列等），并没有和具体地址绑定；
		返回的是非负整数的fd，与struct file对应，而struct file则与具体的struct socket关联，从而实现一切皆文件的封装的一部分
		（另一部分inode的创建处理在sock_alloc的函数里体现）；
	*/
	socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(-1 == socket_fd){
		std::cout << "Socket create failed!" << std::endl;
		return -1;
	}
    
    // 内存区域置0
	// bzero(void*s,size_t n)将内存块（字符串）的前n个字节清零，等价于memset(s,0,n)
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sun_family = PF_UNIX;
	strcpy(server_addr.sun_path, SOCKET_PATH);

    // 2. 连接域套接字
	/* connect()函数：建立socket连线
		int connect(int sockfd, struct sockaddr * serv_addr, int addrlen);
		connect()用来将sockfd的socket连至serv_addr指定的网络地址. 
		serv_addr指定服务器网络地址
		addrlen为sockaddr的结构长度.
	*/
	ret = connect(socket_fd, (sockaddr *)&server_addr, sizeof(server_addr));

	if(-1 == ret){
		std::cout << "Connect socket failed" << std::endl;
		return -1;
	}

	while(true){
        std::cout << "Input message>>> ";
        fgets(msg, MSG_SIZE, stdin);
		// 3. 发送信息
		/* send()函数：经socket传送数据
			int send(int s, const void * msg, int len, unsigned int falgs);
			send()用来将数据由指定的socket传给对方主机. 
			s为已建立好连接的socket_fd.
			msg指向欲连线的数据内容
			len则为数据长度
			flags一般设0，表示数据传送模式
		*/
		ret = send(socket_fd, msg, MSG_SIZE, 0);
	}
	// 关闭socket文件
	close(socket_fd);
	return 0;
}
