// ClientSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[]){

	WORD wVersion;
	wVersion = MAKEWORD(2, 2);

	WSADATA wsaData;

	//初始化socket库
	int ret = WSAStartup(wVersion, &wsaData);
	if (ret != 0){
		printf("error\n");
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2){
		printf("error\n");
		WSACleanup();
		return -1;
	}


	//创建socket
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);

	//连接服务器
	connect(sockClient, (SOCKADDR*)&addr, sizeof(SOCKADDR));

	char recvbuf[128];
	memset(recvbuf, 0, 128);

	//recv
	recv(sockClient, recvbuf, 128, 0);
	printf("%s", recvbuf);

	//send
	send(sockClient, "Hello Server!", strlen("Hello Server!"), 0);

	//关闭socket
	closesocket(sockClient);

	WSACleanup();
	return 0;
}
