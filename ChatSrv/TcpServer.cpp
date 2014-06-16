#include "stdafx.h"
#include "TcpServer.h"


struct SOCK_PROC_PARAM{
	SOCKET sock;
};

CTcpServer::CTcpServer()
{
}


CTcpServer::~CTcpServer()
{
}

//����������
BOOL CTcpServer::Startup(DWORD ip, DWORD port){
	
	//����socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_socket){
		MessageBox(NULL,L"����socketʧ��",L"����",MB_OK);
		return FALSE;
	}

	//��IP�Ͷ˿�
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);

	int ret = bind(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == ret){
		MessageBox(NULL, L"��ʧ��", L"����", MB_OK);
		return FALSE;
	}

	//����
	ret = listen(m_socket, 1000);
	if (SOCKET_ERROR == ret){
		MessageBox(NULL, L"��������ʧ��", L"����", MB_OK);
		return FALSE;
	}

	//�����߳�
	SOCK_PROC_PARAM *param = new SOCK_PROC_PARAM;
	param->sock = m_socket;
	HANDLE hThread = CreateThread(NULL, 0, SocketProc, (LPVOID)param, 0, NULL);
	CloseHandle(hThread);

	return TRUE;

}

//�����߳�
DWORD WINAPI CTcpServer::SocketProc(LPVOID lpParam){

	SOCK_PROC_PARAM* param = (SOCK_PROC_PARAM*)lpParam;
	SOCKET sock = param->sock;


	//����
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1){
		SOCKET client = accept(sock, (SOCKADDR*)&addrClient, &len);

		char buf[128];
		sprintf_s(buf, 128, "Welcome %s !\n", inet_ntoa(addrClient.sin_addr));
		//printf("%s\n", buf);
		MessageBoxA(NULL, buf, "��ӭ", MB_OK);

		HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)&client, 0, NULL);
		CloseHandle(hThread);

	}

	return 0;
}

//���ݽ����߳�
DWORD WINAPI CTcpServer::RecvProc(LPVOID lpParam){
	SOCKET* pSock = (SOCKET*)lpParam;

	while (1){
		char recvbuf[128];
		memset(recvbuf, 0, 128);
		recv(*pSock, recvbuf, 128, 0);
		//printf("%s\n", recvbuf);
		MessageBoxA(NULL, recvbuf, "�յ�����", MB_OK);


	}
	

	return 0;
}