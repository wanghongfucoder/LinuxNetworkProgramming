#include "../lib/unp.h"

/**
 * 信号处理函数，signal.cpp中 Signal 函数的 func
 * 用于处理僵死进程
 * Signal(SIGCHLD, sig_chld);
 */ 
void sig_chld(int signo){
    pid_t pid;
    int stat;
    // waitpid 返回已终止进程的 pid，以及通过stat返回子进程的终止状态
    // 使用循环调用waitpid，以获取所有的子进程的状态，我们必须指定WNOHANG选项，
    // 它告知waitpid在有尚未终止的子进程在运行时不要阻塞（无法告知 wait函数不阻塞）
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0){
        printf("child %d terminated\n", pid);
    }
    return;
}