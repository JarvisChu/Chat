
// Chat.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "LoginDlg.h"
#include "TcpClient.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatApp

BEGIN_MESSAGE_MAP(CChatApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChatApp ����

CChatApp::CChatApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CChatApp ����

CChatApp theApp;


//ȫ�ֵ�TCP������
CTcpClient g_TcpClient;

//ȫ�ֵ��¼�����
HANDLE hLoginOkEvent;
HANDLE hLoginFailEvent;
HANDLE hTcpDisconnectedEvent;



// CChatApp ��ʼ��

BOOL CChatApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Failed to Initialize Sockets"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	
	//��½�ɹ��¼�
	hLoginOkEvent = CreateEvent(NULL, FALSE/*�Զ�����*/, FALSE/*��ʼ���ź�*/, NULL);
	hLoginFailEvent = CreateEvent(NULL, FALSE/*�Զ�����*/, FALSE/*��ʼ���ź�*/, NULL);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	
	//GDI+ ��ʼ��
	GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

	//������½�Ի���
	CLoginDlg logindlg;
	if (IDOK == logindlg.DoModal()){

	}
	else{
		exit(0);
	}



	CChatDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�


	return FALSE;
}



int CChatApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	//�ر�GDI+ͼ���[������ExitInstance��ʵ��]
	GdiplusShutdown(m_GdiplusToken);

	return CWinApp::ExitInstance();
}
