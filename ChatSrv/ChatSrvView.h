
// ChatSrvView.h : CChatSrvView ��Ľӿ�
//

#pragma once


class CChatSrvView : public CListView
{
protected: // �������л�����
	CChatSrvView();
	DECLARE_DYNCREATE(CChatSrvView)

// ����
public:
	CChatSrvDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CChatSrvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ChatSrvView.cpp �еĵ��԰汾
inline CChatSrvDoc* CChatSrvView::GetDocument() const
   { return reinterpret_cast<CChatSrvDoc*>(m_pDocument); }
#endif

