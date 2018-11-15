#include "unp.h"

void str_echo(int sockfd){
    size_t n;
    char buf[MAXLINE];

    do{
        printf("5\n");
        while((n = read(sockfd, buf, MAXLINE)) > 0){
            printf("6\n");
            Writen(sockfd, buf, n);
        }
        printf("7\n");
    }while(n < 0 && errno == EINTR);
    if(n < 0){
        err_sys("str_echo: read error");
    }
}

void str_echo08(int sockfd){
    long arg1 = 0;
    long arg2 = 0;
    size_t n;
    char line[MAXLINE];

    for(;;){
        if((n = Readline(sockfd, line, MAXLINE)) < 0){
            return;
        }
        if(sscanf(line, "%ld%ld", &arg1, &arg2) == 2){
            snprintf(line, sizeof(line), "answer = %ld\n", (arg1>>1)+(arg2>>1)+(arg1&arg2&1));
        }else{
            snprintf(line, sizeof(line), "input error\n");
        }
        n = strlen(line);
        Writen(sockfd, line, n);
    }
}