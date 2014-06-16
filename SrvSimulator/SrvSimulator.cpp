// SrvSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersion;
	WSADATA wsaData;
	int ret;

	wVersion = MAKEWORD(1, 1);

	//请求2.2版本的WinSock
	ret = WSAStartup(wVersion, &wsaData);
	if (ret != 0){
		printf("Initialize WinSock Error\n");
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1){
		printf("Version not correct\n");
		WSACleanup();
		return -1;
	}

	//创建socket
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	//绑定
	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);

	bind(sockSrv, (SOCKADDR*)&addr, sizeof(SOCKADDR));

	//监听
	listen(sockSrv, 10);

	SOCKADDR_IN addrClient;  //用于接收客户端的地址信息
	int len = sizeof(SOCKADDR);
	while (1){
		SOCKET sockClient = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

		char buf[128];
		sprintf_s(buf, 128, "Welcome %s !\n", inet_ntoa(addrClient.sin_addr));
		printf("%s\n", buf);

		while (1){

			char recvbuf[128];
			memset(recvbuf, 0, 128);
			recv(sockClient, recvbuf, 128, 0);
			printf("%s\n", recvbuf);
	
			send(sockClient, "login failed!", strlen("login failed!") + 1, 0);
			
		}
		closesocket(sockClient);

	}

	return 0;
}