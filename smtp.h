#include "StdAfx.h"

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#include <WinSock.h>
#else
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#pragma comment(lib,"Ws2_32.lib")

struct data6
{
	unsigned int d4:6;
	unsigned int d3:6;
	unsigned int d2:6;
	unsigned int d1:6;
};
// 协议中加密部分使用的是base64方法
char con628(char c6);
void base64(char *dbuf,char *buf128,int len);
void sendemail(char *email,char *body);
int open_socket(struct sockaddr *addr);
bool send();