#include "daytime_tcp.h"

int main(int argc, char* argv[]) {
    // 创建套接字
    int socket_client = 0;
    socket_client     = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client < 0) {
        err_sys("failed to create socket.\n");
    }

    // 添加ip地址和端口
    int                ret = 0;
    struct sockaddr_in sa_client;
    std::memset(&sa_client, 0, sizeof(sa_client));
    // 地址族：AF_INET（又称PF_INET）是IPv4 网络协议的套接字类型
    sa_client.sin_family = AF_INET;
    // ip，inet_pton将ipv4或者ipv6的地址转换成二进制(windows中似乎没有实现inet_pton)
    if (argc == 2) {
        ret = inet_pton(AF_INET, argv[1], &sa_client.sin_addr);
    } else {
        ret = inet_pton(AF_INET, "222.20.79.231", &sa_client.sin_addr);
    }
    if (ret <= 0) {
        err_sys("inet_pton error");
        exit(1);
    }
    // port
    sa_client.sin_port = htons(10003);  // 主机到网络短整数

    // 使用套接字连接指定地址
    ret = connect(socket_client, reinterpret_cast<sockaddr*>(&sa_client),
                  sizeof(sa_client));
    if (ret < 0) {
        err_sys("connect error");
    }

    // 读取数据
    char receive_line[MAXLINE + 1];
    int  n = 0;

    while ((n = read(socket_client, receive_line, MAXLINE)) > 0) {
        receive_line[n] = '\0';
        if (fputs(receive_line, stdout) < 0) {
            err_sys("fputs error");
        }
    }
    if (n < 0) {
        err_sys("recv error");
    }
    close(socket_client);
}
