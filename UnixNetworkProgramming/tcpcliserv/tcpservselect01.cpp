#include "unp.h"

int main() {

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr   = htonl(INADDR_ANY);
    servaddr.sin_port   = htons(SERV_PORT);

    Bind(listenfd, reinterpret_cast<SA*>(servaddr), sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    int maxfd = listenfd;
    int maxi  = -1;
    int client[FD_SETSIZE];
    for (int i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }

    fd_set allset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    fd_set             rset;
    int                nready;
    socklen_t          clilen;
    struct sockaddr_in cliaddr;
    int                connfd, sockfd;
    char               buf[MAXLINE];
    ssize_t            n;
    for (;;) {
        rset   = allset;
        nready = Select(maxfd + 1, &rset, nullptr, nullptr, nullptr);

        int i = 0;
        if (FD_ISSET(listenfd, &rset)) {
            // get new client connection
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, reinterpret_cast<SA*>(&cliaddr), &clilen);

            // save descriptor
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                }
            }
            if (i == FD_SETSIZE) {
                err_quit("too many clients.");
            }

            // add new descriptor to set
            FD_SET(connfd, &allset);
            // for select
            if (connfd > maxfd) {
                maxfd = connfd;
            }
            // max index in client[]
            if (i > maxi) {
                maxi = i;
            }
            // no more readable descriptors
            if (--nready <= 0) {
                continue;
            }
        }

        // check all clients for data
        for (i = 0; i < maxi; ++i) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET(sockfd, &rset)) {
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
                    // connection closed by client
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else {
                    Writen(sockfd, buf, n);
                }
            }

            if (--nready <= 0) {
                break;
            }
        }
    }
}