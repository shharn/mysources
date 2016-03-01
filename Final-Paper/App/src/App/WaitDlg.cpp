// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "WaitDlg.h"
#include "afxdialogex.h"


// CWaitDlg dialog

IMPLEMENT_DYNAMIC(CWaitDlg, CDialogEx)

CWaitDlg::CWaitDlg(CString path, ImageProcessNotificationWorkerThread *pNot, CWnd* pParent/*=NULL*/)
	: CDialogEx(CWaitDlg::IDD, pParent)
	, m_cstrPath(path)
	, m_pWnd(pParent)
	, pNot(pNot)
{

}

CWaitDlg::~CWaitDlg()
{
}

void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaitDlg message handlers

BOOL CWaitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	SetDlgItemText(WAITDLG_PATH, m_cstrPath);
	EnableWindow(FALSE);
	CreateThread();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HRESULT CWaitDlg::CreateThread()
{
	if ((m_hThread = (HANDLE)_beginthreadex(NULL, 0, WaitThreadProc, static_cast<LPVOID>(this), 0, NULL)) == NULL)
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}

void CWaitDlg::IsBeingCopied(CStringW pszPath)
{
	HANDLE fHandle = INVALID_HANDLE_VALUE;
	while ((fHandle = ::CreateFile(
		pszPath,					// pointer to the file name
		GENERIC_READ,		             // access (read/write) mode
		FILE_SHARE_READ						// share mode
		| FILE_SHARE_WRITE
		| FILE_SHARE_DELETE,
		NULL,                               // security descriptor
		OPEN_EXISTING,                      // how to create
		0,
		NULL)) == INVALID_HANDLE_VALUE)
		Sleep(100);                              // file with attributes to copy
	CloseHandle(fHandle);
}

void CWaitDlg::TerminateRequest()
{
	isTerminate = true;
}

void CWaitDlg::TerminateDlg()
{
	CDialogEx::OnCancel();
}

static UINT WINAPI WaitThreadProc(LPVOID lpContext)
{
	CWaitDlg* pwThread = reinterpret_cast<CWaitDlg*>(lpContext);
	pwThread->IsBeingCopied(pwThread->m_cstrPath);
	// ::PostMessage(pwThread->GetSafeHwnd(), WM_CLOSE, 0, 0);
	pwThread->TerminateDlg();
	return 0;
}

void CWaitDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CWaitDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnCancel();
}
