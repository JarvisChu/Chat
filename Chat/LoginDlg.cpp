// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "TcpClient.h"

// CLoginDlg dialog


extern CTcpClient g_TcpClient;
extern HANDLE hLoginOkEvent;
extern HANDLE hLoginFailEvent;
extern HANDLE hTcpDisconnectedEvent;


IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_COMBO_ID, m_ctrlID);
	DDX_Control(pDX, IDC_EDIT_PSWD, m_ctrlPSWD);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CLoginDlg::OnBnClickedBtnClose)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg message handlers


//�رմ���
void CLoginDlg::OnBnClickedBtnClose()
{
	CDialog::OnCancel();
}


//
BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!m_btnClose.LoadBitmaps(IDB_CLOSE_NORM, IDB_CLOSE_DOWN,IDB_CLOSE_HIGHLIGHT, IDB_CLOSE_NORM)){
		MessageBox(L"����λͼ��ťʧ��");
	}

	m_btnClose.SubclassDlgItem(IDC_BTN_CLOSE,this);
	m_btnClose.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



//ʹ���ڿ��ƶ�
void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	::UpdateWindow(m_hWnd);
	ReleaseCapture();

	::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}



//��ͼ
BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//����ͷ��
	CStatic* picCtrl = (CStatic*)GetDlgItem(IDC_PIC_PROFILE);
	CRect rectProfile;
	picCtrl->GetWindowRect(&rectProfile);

	Graphics graph(picCtrl->GetWindowDC()->GetSafeHdc());
	m_pimgProfile = Image::FromFile(L"res/profile.jpg");
	graph.DrawImage(m_pimgProfile, 0, 0, rectProfile.Width(), rectProfile.Height());


	//////////////////////////////////////////////////////////////////
	//���ر���


	//λͼ
	CBitmap bmUp;     //�Ի����Ϸ�����
	CBitmap bmBase;   //�Ի����·�����

	bmUp.LoadBitmapW(IDB_LOGIN_BK_UP);
	bmBase.LoadBitmapW(IDB_LOGIN_BK_BASE);

	BITMAP bmpBase;
	bmBase.GetBitmap(&bmpBase);


	//��������DC
	CDC dcCompatibleDC_Up;
	CDC dcCompatibleDC_Base;

	dcCompatibleDC_Up.CreateCompatibleDC(pDC);
	dcCompatibleDC_Base.CreateCompatibleDC(pDC);

	//��λͼѡ������DC
	dcCompatibleDC_Up.SelectObject(bmUp);
	dcCompatibleDC_Base.SelectObject(bmBase);

	///////////////////////////////////////////
	//��ȡ��ͼ�����С

	//��ȡ �ָ��� ��rect
	CRect rectSeperator;
	GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rectSeperator);

	//���ڵ� rect
	CRect rectWnd;
	GetWindowRect(&rectWnd);

	//ClientToScreen(&rectSeperator);
	//ClientToScreen(&rectWnd);

	ScreenToClient(&rectSeperator);
	ScreenToClient(&rectWnd);

	//���沿��
	CRect rectUp;
	rectUp.left = rectWnd.left;
	rectUp.top = rectWnd.top;
	rectUp.right = rectSeperator.right;
	rectUp.bottom = rectSeperator.bottom;

	//���沿��
	CRect rectBase;
	rectBase.left = rectSeperator.left;
	rectBase.top = rectSeperator.top;
	rectBase.right = rectWnd.right;
	rectBase.bottom = rectWnd.bottom;



	//��ͼ
	pDC->BitBlt(rectUp.left, rectUp.top, rectUp.Width(), rectUp.Height(), &dcCompatibleDC_Up, 0, 0, SRCCOPY);
	//pDC->BitBlt(rectBase.left, rectBase.top, rectBase.Width(),rectBase.Height(), &dcCompatibleDC_Base, 0, 0, SRCCOPY);
	pDC->StretchBlt(rectBase.left, rectBase.top, rectBase.Width(), rectBase.Height(), &dcCompatibleDC_Base, 0, 0, bmpBase.bmWidth, bmpBase.bmHeight, SRCCOPY);

	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CLoginDlg::LoadProfile()
{
	return TRUE;
}


//��½ ��ť
void CLoginDlg::OnBnClickedOk()
{
	UpdateData();

	DWORD ip = inet_addr("127.0.0.1");
	DWORD port = 8000;
	if (!g_TcpClient.Connet(ip, port)){
		return;
	}

	//��ȡ�˺�����
	CString szId;
	m_ctrlID.GetWindowTextW(szId);

	CString szPswd;
	m_ctrlPSWD.GetWindowTextW(szPswd);


	g_TcpClient.Send("hello world", strlen("hello world"));

	HANDLE h[2];
	h[0] = hLoginOkEvent;
	h[1] = hLoginFailEvent;

	DWORD dwRet = WaitForMultipleObjects(2, h, FALSE, 20000);

	if (WAIT_OBJECT_0 == dwRet){
		MessageBox(L"��½�ɹ�");
	}
	else if ((WAIT_OBJECT_0 + 1) == dwRet){
		MessageBox(L"��½ʧ��");
		return;
	}
	else if (WAIT_TIMEOUT == dwRet){
		MessageBox(L"��½��ʱ");
		return;
	}


	CDialogEx::OnOK();
}
