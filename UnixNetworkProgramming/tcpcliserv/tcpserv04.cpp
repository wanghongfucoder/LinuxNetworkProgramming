#include "unp.h"

/**
 * 信号处理实例：正确处理 accept() 函数返回的 EINTR，
 * 并建立一个给所有已终止子进程调用 waitpid 函数的信号处理函数
 */ 
int main(int argc, char const *argv[])
{
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, reinterpret_cast<SA*>(&servaddr), sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    void sig_chld(int);

    // 注册信号处理函数
    Signal(SIGCHLD, sig_chld);

    socklen_t clilen;
    struct sockaddr_in cliaddr;
    pid_t childpid;
    int connfd;
    for(;;){
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd, reinterpret_cast<SA*>(&cliaddr), &clilen)) < 0){
            if(errno == EINTR){
                continue;
            }else{
                err_sys("accept error");
            }
        }

        if((childpid = Fork()) == 0){
            Close(listenfd);
            str_echo08(connfd);
            exit(0);
        }
        Close(connfd);
    }
}


