#include "../lib/unp.h"
/**
 *  str_cli函数（再修订版）
 * 使用了select，只要服务器关闭它那一端的连接就会通知我们
 * 使用了shutdown，允许我们正确地处理批量输入
 */
void str_cli(FILE* fp, int sockfd){
    int maxfdp1;
    int stdineof = 0;
    char buf[MAXLINE];
    int n;

    fd_set rset;
    FD_ZERO(&rset);

    for(;;){
        // 如果标准输入没有完，就需要select标准输入的可读性
        if(stdineof == 0){
            FD_SET(fileno(fp), &rset);
        }
        // select连接到的套接字描述符的可读性
        FD_SET(sockfd, &rset);

        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);

        // 如果套接字可读
        if(FD_ISSET(sockfd, &rset)){
            // 如果在套接字上读到 EOF，当标准输入已经遇到EOF，则正常终止
            // 否则为服务器过早终止
            if((n=Read(sockfd, buf, MAXLINE)==0){
                if(stdineof == 1){
                    return;
                }else{
                    err_quit("str_cli: server terminated prematurely.");
                }
            }
            Write(fileno(stdout), buf, n);
        }

        // 如果标准输入可读
        if(FD_ISSET(fileno(fp), &rset)){
            // 如果在标准输入中读到EOF，那么就设置标志位
            // 用shutdown函数关闭套接字的写入，发送FIN
            if((n=Read(fileno(fp),buf, MAXLINE)) == 0){
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR);
                FD_CLR(sockfd, &rset);
                // 使用continue再执行一次循环，获取从服务器回射的文本
                continue;
            }
            Writen(sockfd, buf, n);j'k'l
        }
    }
}