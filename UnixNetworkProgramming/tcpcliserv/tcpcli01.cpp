#include "unp.h"

int main(int argc, char** argv) {
    // int sockfd;
    // struct sockaddr_in server_addr;

    if (argc != 2) {
        err_quit("usage: tcpcli <IPaddress>");
    }

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(23333);
    Inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    Connect(sockfd, reinterpret_cast<SA*>(&server_addr), sizeof(server_addr));

    str_cli(stdin, sockfd);
    exit(0);
}