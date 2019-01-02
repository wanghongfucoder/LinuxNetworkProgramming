#include "../lib/unp.h"

/**
 * TCP程序实例：复读机程序第一个版本，最简单的回射网络服务端
 * 等待连接的客户发射字符串过来，再复读回去
 */ 

int main(int argc, char** argv) {
    int listenfd;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        err_sys("socket error");
    }
    printf("0\n");
    struct sockaddr_in cliaddr;
    struct sockaddr_in seraddr;
    seraddr.sin_family      = AF_INET;
    seraddr.sin_port        = htons(23333);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, reinterpret_cast<SA*>(&seraddr), sizeof(seraddr));

    Listen(listenfd, LISTENQ);

    int       connfd;
    socklen_t clilen;
    pid_t     childpid;
    for (;;) {
        clilen = sizeof(cliaddr);
        printf("1\n");
        connfd =
            Accept(listenfd, reinterpret_cast<SA*>(&cliaddr), &clilen);
        printf("2\n");
        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            printf("3\n");
            str_echo(connfd);
            printf("4\n");
            exit(0);
        }
        Close(connfd);
    }
}