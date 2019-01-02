#include "../lib/unp.h"
#include <limits.h> // for OPEN_MAX

int main(int argc, char** argv){
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    Bind(listenfd, reinterpret_cast<SA*>(&server_addr), sizeof(server_addr));

    Listen(listenfd, LISTENQ);

    // 第一项用于监听套接字，第一项设置POLLRDNORM事件，当有新连接准备好时poll会通知我们
    struct pollfd client[OPEN_MAX];
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    // 不感兴趣的描述符设置负值
    for(int i = 1; i < OPEN_MAX; ++i){
        client[i].fd = -1;
    }
    int maxi = 0;

    struct sockaddr_in client_addr;
    socklen_t client_len;
    int connfd = -1;
    int sockfd = -1;
    int nready = -1;
    int client_idx = 0;
    for(;;){
        // maxi+1 制定了client中的元素个数
        // INFTIM 说明了要永远等待
        nready = Poll(client, maxi + 1, INFTIM);

        // 如果返回的当前事件中有普通数据，说明有一个连接，则接受这个连接
        if(client[0].revents & POLLRDNORM) {
            client_len = sizeof(client_addr);
            connfd = Accept(listenfd, reinterpret_cast<SA*>(&client_addr), &client_len);

            // 记录连接过来的描述符
            for(client_idx = 1; client_idx < OPEN_MAX; ++client_idx){
                if(client[client_idx] < 0){
                    client[client_idx].fd = connfd;
                    break;
                }
            }
            if(client_idx == OPEN_MAX){
                err_quit("too many clients");
            }

            // 设置当前描述符的事件为POLLRDNORM
            client[client_idx].events = POLLRDNORM;
            if(client_idx > maxi){
                maxi = client_idx;
            }

            // 如果已经就绪的描述符到 0 了，就不用再遍历了
            if(--nready <= 0){
                continue;
            }
        }

        // 依次处理就绪的描述符
        for(client_idx = 1; client_idx < maxi; ++client_idx){
            if((sockfd = client[client_idx].fd) < 0) {
                continue;
            }
            // 当该描述符可读或者出现了错误时
            if(client[i].revents & (POLLRDNORM | POLLERR)) {
                if((n = read(sockfd, buf, MAXLINE)) < 0){
                    // 客户端关闭了连接，收到 RST 信号（出现了错误的情况）
                    if(errno == ECONNRESET) {
                        Close(connfd);
                        client[i].fd = -1;
                    } else {
                        err_sys("read error");
                    }
                } else if(n == 0) {
                    // 读完了发过来的文本信息，服务端主动关闭连接
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    Writen(sockfd, buf, n);
                }
                if(--nready <= 0){
                    break;
                }
            }
        }
    }
}