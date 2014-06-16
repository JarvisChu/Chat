#pragma once

class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	//BOOL Open(DWORD,)
	BOOL Connet(DWORD ip, DWORD port);
	BOOL Send(char* data, int len);
	BOOL Close();

	static DWORD WINAPI TcpRecvProc(LPVOID lpParam);

public:
	SOCKET m_socket;
private:
	BOOL m_bConnected;
public:
	HANDLE m_hTcpCloseEvent;
};

