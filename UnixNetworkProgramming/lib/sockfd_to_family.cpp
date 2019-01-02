#include "unp.h"

/**
 * 获取某个套接字的本地协议的版本
 */ 
int sockfd_to_family(int sockfd){
    struct sockaddr_storage ss;
    socklen_t len;

    len = sizeof(ss);
    if(getsockname(sockfd, (struct sockaddr*)&ss, &len) < 0){
        return -1;
    }
    return ss.ss_family;
}