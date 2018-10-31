#ifndef UNP_H_
#define UNP_H_

#include <cstdio>
#include <cstdlib> // exit()

#include <unistd.h>

#include <netinet/in.h>

#define MAXLINE 1024
#define LISTENQ 128
#define SERV_PORT 23333

void err_sys(const char* msg) {
    perror(msg);
    exit(1);
}

int Socket(int __domain, int __type, int __protocol){
    int fd = socket(__domain, __type, __protocol);
    if(fd < 0){
        err_sys("Socket error");
    }
    return fd;
}

void Bind(int __fd, const sockaddr* __addr, socklen_t __len){
    int ret = bind(__fd, __addr, __len);
    if(ret < 0){
        err_sys("Bind error");
    }
}

void Listen(int __fd, int __len) {
    int ret = listen(__fd, __len);
    if(ret < 0){
        err_sys("Listen error");
    }
}

int Accept(int __fd, sockaddr* __addr, socklen_t* __len){
    int ret_fd =  accept(__fd, __addr, __len);
    if(ret_fd < 0){
        err_sys("accept error");
    }
    return ret_fd;
}

void Close(int __fd){
    close(__fd);
}

pid_t Fork(){
    return fork();
}

#endif // !UNP_H_

