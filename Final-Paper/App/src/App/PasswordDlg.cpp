// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "PasswordDlg.h"
#include "afxdialogex.h"


// PasswordDlg dialog

IMPLEMENT_DYNAMIC(PasswordDlg, CDialogEx)

PasswordDlg::PasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PasswordDlg::IDD, pParent)
	, m_csPassword(_T(""))
{

}

PasswordDlg::~PasswordDlg()
{
}

void PasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, PSWD_EDIT_PSWD, m_csPassword);
}


BEGIN_MESSAGE_MAP(PasswordDlg, CDialogEx)
	ON_BN_CLICKED(PSWD_BUTTON_OK, &PasswordDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(PSWD_BUTTON_CANCEL, &PasswordDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// PasswordDlg message handlers


void PasswordDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_csPassword.GetLength() < 4)
		AfxMessageBox(_T("At least 4 characters"));
	else
	{
		CString strMsgDigest;

		// get hashed value from the original password string
		GlobalFunction::GetHashedValueFromPassword(m_csPassword, strMsgDigest);

		// write hashed value to registry hive
		GlobalFunction::WriteToRigestrySZ(REGISTRY_PATH, PASSWORD_KEY, strMsgDigest);
		OnOK();
	}
}


void PasswordDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
