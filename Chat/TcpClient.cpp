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

//���ӷ�����
BOOL CTcpClient::Connet(DWORD ip, DWORD port){
	
	//�ж��Ƿ��Ѿ�����
	if (m_bConnected){
		return TRUE;
	}


	//����socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_socket){
		MessageBox(NULL,L"�����׽���ʧ��",L"����",MB_OK);
		m_bConnected = FALSE;
		return FALSE;
	}


	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//htonl(ip);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);

	//���ӷ�����
	int ret = connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == ret){
		closesocket(m_socket);
		MessageBox(NULL, L"���ӷ�����ʧ��", L"����", MB_OK);
		m_bConnected = FALSE;
		return FALSE;
	}

	m_hTcpCloseEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //�Զ����ã���ʼ���ź�  

	//�������ݽ����߳�
	//RECV_PROC_PARAM * param = new RECV_PROC_PARAM;
	//param->pTcpClient = this;
	//param->sock = m_h
	HANDLE hThread = CreateThread(NULL, 0, TcpRecvProc, (LPVOID)this, 0, NULL);
	CloseHandle(hThread);

	

	m_bConnected = TRUE;
	return TRUE;
}


//��������
BOOL CTcpClient::Send(char* data, int len){
	if (!m_bConnected){
		return FALSE;
	}

	int ret = send(m_socket, data, len, 0);
	if (SOCKET_ERROR == ret){
		MessageBox(NULL, L"���ݷ���ʧ��", L"����", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�˳�
BOOL CTcpClient::Close(){

	//�ر�socket
	if (m_bConnected){
		closesocket(m_socket);
	}

	//�����߳��˳�
	SetEvent(m_hTcpCloseEvent); //�������źţ����߳��˳�

	return TRUE;
}

//���ݽ����̻߳ص�����
DWORD WINAPI CTcpClient::TcpRecvProc(LPVOID lpParam){

	CTcpClient* pTcpClient = (CTcpClient*)lpParam;
	SOCKET sock = pTcpClient->m_socket;

	char recvbuf[1024];
	memset(recvbuf, 0, 1024);

	int ret;
	while (TRUE){

		//�ж��Ƿ�Ҫ�˳��߳�
		DWORD dwRet = WaitForSingleObject(pTcpClient->m_hTcpCloseEvent, 10); //�ȴ�10ms
		if (dwRet == WAIT_OBJECT_0){ //�˳��¼����ź�
			break;
		}

		ret = recv(sock, recvbuf, 1024, 0);
		if (SOCKET_ERROR == ret){
			MessageBox(NULL, L"�������ݴ���", L"����", MB_OK);
			break;
		}

		////////////////////////////////////////////////////////
		//�ж���������

		if (strcmp(recvbuf, "login ok!") == 0){
			SetEvent(hLoginOkEvent);   //�������ź�
		}
		else if (strcmp(recvbuf, "login failed!") == 0){
			SetEvent(hLoginFailEvent); //�������ź�
		}

	}

	return 0;
}