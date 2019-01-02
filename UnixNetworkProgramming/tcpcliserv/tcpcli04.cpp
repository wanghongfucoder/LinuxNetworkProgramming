#include "unp.h"

/**
 * 信号处理实例：与服务器建立了5个连接的TCP客户端程序
 * 当客户终止时，所有打开的描述符由内核自动关闭，且所有5个连接基本在同一时刻终止。
 * 这就引发了5个FIN，每个连接一个，它们反过来使服务器的5个子进程基本在同一时刻终止。
 * 这又导致差不多在同一时刻有5个SIGCHLD信号递交给父进程。
 */ 

/**
 * 当服务器端进程终止时（服务器向客户端发送了FIN，客户端回了一个ACK，然而客户端还阻塞在Fgets()函数），
 * 在客户端键入另一行文本，这时服务器端因为异常连接返回一个RST。
 * 但是客户端收不到 RST，因为它调用 written之后立刻调用了 readline，由于FIN，readline立刻返回 0(EOF) ，
 * 但是客户端并未预期收到EOF，于是显示“服务器过早终止”的错误信息
 */ 

/**
 * 客户端程序的问题是：
 * 当客户端收到FIN时，客户端正阻塞在fgets函数上。客户实际在应对两个描述符：套接字和用户输入，
 * 它不能单纯阻塞在这两个源中某个特定源的输入，应该阻塞在其中任何一个源的输入上，这就是select和poll函数的目的之一。
 */ 
int main(int argc, char const *argv[])
{
    if(argc != 2){
        err_quit("usage: tcpcli <IP Address>");
    }

    const int process_num = 5;
    struct sockaddr_in  servaddr;
    int sockfd[process_num];
    for(int i = 0; i < 5; ++i){
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        Connect(sockfd[i], reinterpret_cast<SA*>(&servaddr), sizeof(servaddr));
    }
    str_cli(stdin, sockfd[0]);
    
    exit(0);
}
