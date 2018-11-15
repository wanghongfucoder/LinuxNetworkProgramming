#include "unp.h"

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
    // here set function for signal
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


