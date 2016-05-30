
// PortalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Portal.h"
#include "PortalDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPortalDlg dialog



CPortalDlg::CPortalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPortalDlg::IDD, pParent)
	, m_ID(_T(""))
	, m_Password(_T(""))
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, 1007, m_ID);
	DDX_Text(pDX, 1008, m_Password);
	DDX_Control(pDX, 1003, m_ButtonLogin);
}

BEGIN_MESSAGE_MAP(CPortalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(1003, &CPortalDlg::OnBnClicked1003)
	ON_BN_CLICKED(1005, &CPortalDlg::OnBnClicked1005)
END_MESSAGE_MAP()


// CPortalDlg message handlers
// 100835 한승환
BOOL CPortalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPortalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPortalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPortalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortalDlg::OnBnClicked1003()
{
	// TODO: Add your control notification handler code here
	CSTUDENT_info<CSTUDENT_infoAccessor> info;
	UpdateData(TRUE);
	info.m_SID = atoi(m_ID);
	info.m_dwSIDLength = sizeof(LONG);
	info.m_dwSIDStatus = DBSTATUS_S_OK;
	if (info.OpenAll() == S_OK)
	{
		if (info.MoveNext() == S_OK)
		{
			if (info.m_PASSWORD == atoi(m_Password))
			{
				Student dlg;
				dlg.setID(atoi(m_ID));
				dlg.SetName(info.m_SNAME);
				CDialog::OnOK();
				if (dlg.DoModal() == S_OK)
				{
					OnOK();
				}
			}
			else
			{
				AfxMessageBox("비번 틀림");
			}
		}
		else
			AfxMessageBox("아이디 틀림");
	}
	else
		AfxMessageBox("접속 실패");

}


void CPortalDlg::OnBnClicked1005()
{
	// TODO: Add your control notification handler code here
	Register dlg;
	if (dlg.DoModal() == S_OK)
	{
		OnOK();
	}
}
// 100835 한승환