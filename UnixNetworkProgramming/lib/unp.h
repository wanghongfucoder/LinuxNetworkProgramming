#ifndef UNP_H_
#define UNP_H_

#include <cstdlib> // exit()

#define MAXLINE 1024
#define LISTENQ 128
void err_sys(const char* msg) {
    perror(msg);
    exit(1);
}

#endif // !UNP_H_

