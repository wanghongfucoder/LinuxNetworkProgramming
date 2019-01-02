/**
 * signal工具函数，直接抄过来
 * 函数作用为为某个信号（signo）注册信号处理函数
 */ 
/* include signal */
#include	"unp.h"

Sigfunc *
signal(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;

	// 设置注册函数
	act.sa_handler = func;
	// 设置处理函数的信号掩码，把sa_mask成员设置为空集，
	// 意味着在该信号处理函数期间，不阻塞额外的信号
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	// 对 SIGALRM 信号进行特殊处理的原因是：产生该信号的目的通常为I/O超时，
	// 此时我们希望受阻塞的系统调用被该信号中断掉
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		// 如果设置了SA_RESTART，那么由相应信号中断的系统调用将由内核重启
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	// 建立信号处理的posix方法就是调用sigaction函数
	// 需要填写对应的数据结构
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
/* end signal */

Sigfunc *
Signal(int signo, Sigfunc *func)	/* for our signal() function */
{
	Sigfunc	*sigfunc;

	if ( (sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return(sigfunc);
}
