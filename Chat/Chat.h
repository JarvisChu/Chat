
// Chat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#pragma comment(lib,"gdiplus.lib")

// CChatApp: 
// �йش����ʵ�֣������ Chat.cpp
//


class CChatApp : public CWinApp
{
public:
	CChatApp();

public:
	GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR m_GdiplusToken;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CChatApp theApp;