/**
 * 把网络端的 ip 地址转换成 xxx.xxx.xxx.xxx 类型的地址
 * 封装函数
 */ 
#include	"unp.h"

const char *
Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char	*ptr;

	if (strptr == NULL)		/* check for old code */
		err_quit("NULL 3rd argument to inet_ntop");
	if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_sys("inet_ntop error");		/* sets errno */
	return(ptr);
}

/**
 * 把xxx.xxx.xxx.xxx 类型的地址转换成网络端的 ip 地址
 */ 
void
Inet_pton(int family, const char *strptr, void *addrptr)
{
	int	n;

	if ( (n = inet_pton(family, strptr, addrptr)) < 0)
		err_sys("inet_pton error for %s", strptr);	/* errno set */
	else if (n == 0)
		err_quit("inet_pton error for %s", strptr);	/* errno not set */

	/* nothing to return */
}