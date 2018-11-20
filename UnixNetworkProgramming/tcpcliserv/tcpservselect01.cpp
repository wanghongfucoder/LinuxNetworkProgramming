#include "unp.h"

int main(){
    
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, reinterpret_cast<SA*>(servaddr), sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    int maxfd = listenfd;
    int maxi = -1;
    int client[FD_SETSIZE];
    for(int i = 0; i < FD_SETSIZE; ++i){
        client[i] = -1;
    }

    fd_set allset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for(;;){
        
    }
}