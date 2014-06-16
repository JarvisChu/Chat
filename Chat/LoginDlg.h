#pragma once
#include "afxext.h"
#include "atlimage.h"
#include "afxwin.h"


// CLoginDlg dialog

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_btnClose;
	afx_msg void OnBnClickedBtnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	Image* m_pimgProfile;
	BOOL LoadProfile();
	CComboBox m_ctrlID;
	CEdit m_ctrlPSWD;
	afx_msg void OnBnClickedOk();
};
