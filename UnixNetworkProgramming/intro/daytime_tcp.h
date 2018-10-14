#ifndef DAYTIME_TCP_H_
#define DAYTIME_TCP_H_

#include "../lib/unp.h"

#include <cstdio>
#include <cstring>


#include <winsock2.h>
// 提供inet_pton函数
// WS2tcpip.h 必须是显式包含 Winsock2.h 后才能在此级别使用套接字选项


/*
  和在工程设置里写上链入Ws2_32.lib的效果一样，不过这种方法写的  
  程序别人在使用你的代码的时候就不用再设置工程settings了。

  告诉连接器连接的时候要找ws2_32.lib，这样你就不用在linker的lib
  设置里指定这个lib了。

  ws2_32.lib是winsock2的库文件

  WinSock2就相当于连接系统和你使用的软件之间交流的一个接口,可能
  这个功能就是修复软件与系统正确的通讯的作用。
*/
#ifdef _MSC_VER
//#pragma comment(lib,"ws2_32.lib")
#endif

#endif // !DAYTIME_TCP_H_
