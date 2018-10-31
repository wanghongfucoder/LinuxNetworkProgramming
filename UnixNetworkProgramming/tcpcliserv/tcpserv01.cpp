#include "../lib/unp.h"


int main(int argc, char** argv){
    int listenfd;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        err_sys("socket error");
    }
    
    struct sockaddr_in cliaddr;
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(23333);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, reinterpret_cast<sockaddr*>(seraddr), sizeof(seraddr));

    Listen(listenfd, LISTENQ);

    int connfd;
    socklen_t clilen;
    pid_t childpid;
    for(;;){
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, reinterpret_cast<sockaddr*>(cliaddr), &clilen);
        if((childpid = Fork()) == 0){
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        Close(connfd);
    }
}