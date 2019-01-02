#include "unp.h"

void str_cli(FILE* fp, int sockfd) {
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));
        if (Readline(sockfd, recvline, MAXLINE) == 0) {
            err_quit("str_cli: server terminated prematurely");
        }
        Fputs(recvline, stdout);
    }
}

void str_cli_SIGPIPE(FILE* fp, int sockfd){
        char sendline[MAXLINE];
    char recvline[MAXLINE];
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        // 引发一个RST
        // TCP处理程序会在自己认为的异常时刻发送RST包。例如，A向B发起连接，但B之上并未监听相应的端口，这时B操作系统上的TCP处理程序会发RST包。
        Writen(sockfd, sendline, 1);
        // 睡眠 1 秒
        sleep(1);
        // 不理会RST，写入更多的数据到服务器上，引发SIGPIPE信号，该信号会导致客户端死亡
        Writen(sockfd, sendline, strlen(sendline) - 1);
        if (Readline(sockfd, recvline, MAXLINE) == 0) {
            err_quit("str_cli: server terminated prematurely");
        }
        Fputs(recvline, stdout);
    }
}