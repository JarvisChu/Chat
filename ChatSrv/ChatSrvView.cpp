
// ChatSrvView.cpp : CChatSrvView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ChatSrv.h"
#endif

#include "ChatSrvDoc.h"
#include "ChatSrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatSrvView

IMPLEMENT_DYNCREATE(CChatSrvView, CListView)

BEGIN_MESSAGE_MAP(CChatSrvView, CListView)
END_MESSAGE_MAP()

// CChatSrvView ����/����

CChatSrvView::CChatSrvView()
{
	// TODO:  �ڴ˴���ӹ������

}

CChatSrvView::~CChatSrvView()
{
}

BOOL CChatSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CChatSrvView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO:  ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}


// CChatSrvView ���

#ifdef _DEBUG
void CChatSrvView::AssertValid() const
{
	CListView::AssertValid();
}

void CChatSrvView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CChatSrvDoc* CChatSrvView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChatSrvDoc)));
	return (CChatSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CChatSrvView ��Ϣ�������
