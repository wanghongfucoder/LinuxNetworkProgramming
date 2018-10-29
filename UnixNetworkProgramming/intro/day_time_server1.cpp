#include "daytime_tcp.h"
#include <ctime>

int main(int argc, char* argv[])
{
    //  创建套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        err_sys("socket() error");
    }
    // 指定地址，作为服务端允许任意地址连接
    sockaddr_in sa_server;
    std::memset(&sa_server, 0, sizeof(sa_server));

    sa_server.sin_family = AF_INET;
    // 作为服务器，你要绑定【bind】到本地的IP地址上进行监听【listen】，
    // 但是你的机器上可能有多块网卡，也就有多个IP地址，这时候你要选择绑定在哪
    // 个IP上面，如果指定为INADDR_ANY，那么系统将绑定默认的网卡【即IP地址】。
    // s_addr是ip地址
    sa_server.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_server.sin_port        = htons(10003);

    // 绑定
    int ret = bind(listen_fd, reinterpret_cast<sockaddr*>(&sa_server),
                   sizeof(sa_server));
    if (ret < 0)
    {
        err_sys("bind() error");
    }

    // 监听
    ret = listen(listen_fd, LISTENQ);
    if (ret < 0)
    {
        err_sys("listen() error");
    }

    int    connect_fd = 0;
    time_t now;
    char   buff[MAXLINE];
    sockaddr_in cliaddr;
    socklen_t len;
    for (;;)
    {
        len = sizeof(cliaddr);
        // 接收到一个连接
        connect_fd = accept(listen_fd, reinterpret_cast<sockaddr*>(&cliaddr), &len);
        printf("connection from %s, port %d.\n", inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));

        now = time(NULL);
        snprintf(buff, sizeof(buff), "time is %.24s.\r\n", ctime(&now));
        ret = write(connect_fd, buff, strlen(buff));
        close(connect_fd);
    }
    close(listen_fd);
}