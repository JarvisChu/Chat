
// ChatSrv.h : ChatSrv Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChatSrvApp:
// �йش����ʵ�֣������ ChatSrv.cpp
//

class CChatSrvApp : public CWinApp
{
public:
	CChatSrvApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChatSrvApp theApp;
