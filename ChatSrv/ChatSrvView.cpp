
// ChatSrvView.cpp : CChatSrvView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CChatSrvView 构造/析构

CChatSrvView::CChatSrvView()
{
	// TODO:  在此处添加构造代码

}

CChatSrvView::~CChatSrvView()
{
}

BOOL CChatSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CChatSrvView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO:  调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
}


// CChatSrvView 诊断

#ifdef _DEBUG
void CChatSrvView::AssertValid() const
{
	CListView::AssertValid();
}

void CChatSrvView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CChatSrvDoc* CChatSrvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChatSrvDoc)));
	return (CChatSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CChatSrvView 消息处理程序
