#pragma once
class CTcpServer
{
public:
	CTcpServer();
	~CTcpServer();

	BOOL Startup(DWORD ip, DWORD port);

	static DWORD WINAPI RecvProc(LPVOID lpParam);
	static DWORD WINAPI SocketProc(LPVOID lpParam);

private:
	SOCKET sockm_socket;
};

