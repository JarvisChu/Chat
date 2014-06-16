
// ChatSrvView.h : CChatSrvView 类的接口
//

#pragma once


class CChatSrvView : public CListView
{
protected: // 仅从序列化创建
	CChatSrvView();
	DECLARE_DYNCREATE(CChatSrvView)

// 特性
public:
	CChatSrvDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CChatSrvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ChatSrvView.cpp 中的调试版本
inline CChatSrvDoc* CChatSrvView::GetDocument() const
   { return reinterpret_cast<CChatSrvDoc*>(m_pDocument); }
#endif

