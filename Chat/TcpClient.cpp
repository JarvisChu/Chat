#include "stdafx.h"
#include "TcpClient.h"


struct RECV_PROC_PARAM{
	CTcpClient * pTcpClient;
	SOCKET sock;
};




extern HANDLE hLoginOkEvent;
extern HANDLE hLoginFailEvent;
extern HANDLE hTcpDisconnectedEvent;


CTcpClient::CTcpClient() :m_bConnected(FALSE)
{
}


CTcpClient::~CTcpClient()
{
}

//连接服务器
BOOL CTcpClient::Connet(DWORD ip, DWORD port){
	
	//判断是否已经连接
	if (m_bConnected){
		return TRUE;
	}


	//创建socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_socket){
		MessageBox(NULL,L"创建套接字失败",L"错误",MB_OK);
		m_bConnected = FALSE;
		return FALSE;
	}


	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//htonl(ip);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);

	//连接服务器
	int ret = connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == ret){
		closesocket(m_socket);
		MessageBox(NULL, L"连接服务器失败", L"错误", MB_OK);
		m_bConnected = FALSE;
		return FALSE;
	}

	m_hTcpCloseEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //自动重置，初始无信号  

	//创建数据接收线程
	//RECV_PROC_PARAM * param = new RECV_PROC_PARAM;
	//param->pTcpClient = this;
	//param->sock = m_h
	HANDLE hThread = CreateThread(NULL, 0, TcpRecvProc, (LPVOID)this, 0, NULL);
	CloseHandle(hThread);

	

	m_bConnected = TRUE;
	return TRUE;
}


//发送数据
BOOL CTcpClient::Send(char* data, int len){
	if (!m_bConnected){
		return FALSE;
	}

	int ret = send(m_socket, data, len, 0);
	if (SOCKET_ERROR == ret){
		MessageBox(NULL, L"数据发送失败", L"错误", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//退出
BOOL CTcpClient::Close(){

	//关闭socket
	if (m_bConnected){
		closesocket(m_socket);
	}

	//接收线程退出
	SetEvent(m_hTcpCloseEvent); //设置有信号，让线程退出

	return TRUE;
}

//数据接收线程回调函数
DWORD WINAPI CTcpClient::TcpRecvProc(LPVOID lpParam){

	CTcpClient* pTcpClient = (CTcpClient*)lpParam;
	SOCKET sock = pTcpClient->m_socket;

	char recvbuf[1024];
	memset(recvbuf, 0, 1024);

	int ret;
	while (TRUE){

		//判断是否要退出线程
		DWORD dwRet = WaitForSingleObject(pTcpClient->m_hTcpCloseEvent, 10); //等待10ms
		if (dwRet == WAIT_OBJECT_0){ //退出事件有信号
			break;
		}

		ret = recv(sock, recvbuf, 1024, 0);
		if (SOCKET_ERROR == ret){
			MessageBox(NULL, L"接收数据错误", L"错误", MB_OK);
			break;
		}

		////////////////////////////////////////////////////////
		//判断数据类型

		if (strcmp(recvbuf, "login ok!") == 0){
			SetEvent(hLoginOkEvent);   //设置有信号
		}
		else if (strcmp(recvbuf, "login failed!") == 0){
			SetEvent(hLoginFailEvent); //设置有信号
		}

	}

	return 0;
}