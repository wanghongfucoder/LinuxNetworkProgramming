#include "../lib/unp.h"

/**
 * 拒绝服务型攻击：如果有一个恶意的客户端程序连接了该服务器，发送了1个字节之后进入睡眠，
 * 那么服务器会阻塞于下一个read调用，以等待来自于该客户端的数据，服务器端被这么一个客户端阻塞，
 * 不能再为其他客户提供服务。
 * 因此，服务器绝对不能阻塞鱼单个客户的相关的函数调用。
 */ 

int main() {

    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr   = htonl(INADDR_ANY);
    servaddr.sin_port   = htons(SERV_PORT);

    Bind(listenfd, reinterpret_cast<SA*>(servaddr), sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    // 对client[]初始化
    int maxfd = listenfd;
    int maxi  = -1;
    int client[FD_SETSIZE];
    for (int i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }

    // 初始化allset，默认select监听套接字
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
        // 获得已经就绪的描述符的数量
        nready = Select(maxfd + 1, &rset, nullptr, nullptr, nullptr);

        int i = 0;
        // 如果监听套接字可读
        if (FD_ISSET(listenfd, &rset)) {
            // 得到新连接的描述符
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, reinterpret_cast<SA*>(&cliaddr), &clilen);

            // 保存描述符
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                }
            }
            if (i == FD_SETSIZE) {
                err_quit("too many clients.");
            }

            // 把新的描述符添加到描述符集
            FD_SET(connfd, &allset);
            // for select，更新最大的描述符索引
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

        // 依次处理每个select的描述符
        // check all clients for data
        for (i = 0; i < maxi; ++i) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET(sockfd, &rset)) {
                if ((n = Read(sockfd, buf, MAXLINE)) == 0) {
                    // connection closed by client
                    // 连接被客户端关闭，这边也关闭
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