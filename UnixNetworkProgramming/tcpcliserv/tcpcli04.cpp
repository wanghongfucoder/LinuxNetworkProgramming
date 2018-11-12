#include "unp.h"

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