/**
 * 使用了自带的缓冲区的readline
 */ 

/* include readline */
#include "unp.h"

static int   read_cnt;
static char* read_ptr;
static char  read_buf[MAXLINE];

static ssize_t my_read(int fd, char* ptr) {
    // 缓冲区读完，再读取 MAXLINE个字符
    if (read_cnt <= 0) {
    again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return (-1);
        } else if (read_cnt == 0)
            return (0);
        read_ptr = read_buf;
    }
    // 返回一个字符
    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

ssize_t readline(int fd, void* vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *ptr;

    ptr = (char*)vptr;
    for (n = 1; n < maxlen; n++) {
        // 读取一个字符，赋值给缓存区
        if ((rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break; /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1); /* EOF, n - 1 bytes were read */
        } else
            return (-1); /* error, errno set by read() */
    }

    *ptr = 0; /* null terminate like fgets() */
    return (n);
}

// 读取read_ptr指向的缓存区中剩余的字符
ssize_t readlinebuf(void** vptrptr) {
    if (read_cnt)
        *vptrptr = read_ptr;
    return (read_cnt);
}
/* end readline */

// 供用户使用的 Readline接口
ssize_t Readline(int fd, void* ptr, size_t maxlen) {
    ssize_t n;

    if ((n = readline(fd, ptr, maxlen)) < 0)
        err_sys("readline error");
    return (n);
}
