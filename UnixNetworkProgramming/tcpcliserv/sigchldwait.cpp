#include "../lib/unp.h"

/**
 * 不该使用的信号处理函数，因为信号处理函数只执行一次
 * 因此 wait 只执行一次，面对多个信号的情况会留下僵死进程
 */

void sig_chld_NO_USE(int signo){
    pid_t pid;
    int stat;
     
    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;    
}
