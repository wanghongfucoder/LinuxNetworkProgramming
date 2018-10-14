#include "daytime_tcp.h"
#include <ws2tcpip.h>

int main(int argc, char *argv[])
{
#ifdef WIN32
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return 0;
    }
#endif
    // 创建套接字
    int socket_client = 0;
    socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client < 0)
    {
        err_sys("failed to create socket.\n");
    }

    // 添加ip地址和端口
    int ret = 0;
    struct sockaddr_in sa_client;
    std::memset(&sa_client, 0, sizeof(sa_client));
    // 地址族：AF_INET（又称PF_INET）是IPv4 网络协议的套接字类型
    sa_client.sin_family = AF_INET;
    // ip，inet_pton将ipv4或者ipv6的地址转换成二进制(windows中似乎没有实现inet_pton)
    // ret = inet_pton(AF_INET, argv[1], &sa_client.sin_addr);
    // if (ret <= 0)
    // {
    //     err_sys("inet_pton error for .\n");
    //     exit(1);
    // }
    sa_client.sin_addr.s_addr = inet_addr(argv[1]);
    // port
    sa_client.sin_port = htons(13); // 主机到网络短整数

    // 使用套接字连接指定地址
    ret = connect(socket_client, reinterpret_cast<sockaddr *>(&sa_client), sizeof(sa_client));
    if (ret < 0)
    {
        err_sys("connect error.\n");
    }

    // 读取数据
    char receive_line[MAXLINE + 1];
    int n = 0;
#ifdef WIN32
    while ((n = recv(socket_client, receive_line, MAXLINE, 0)) > 0)
    {
#elif __linux__

    while ((n = read(socket_client, receive_line, MAXLINE)) > 0)
    {
#endif
        receive_line[n] = '\0';
        if (fputs(receive_line, stdout) < 0)
        {
            err_sys("fputs error.\n");
        }
    }
    if (n < 0)
    {
        err_sys("recv error.\n");
    }
#ifdef WIN32
    WSACleanup();
#endif
}
