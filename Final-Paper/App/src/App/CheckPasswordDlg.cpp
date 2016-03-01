// CheckPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "CheckPasswordDlg.h"
#include "afxdialogex.h"


// CheckPasswordDlg dialog

IMPLEMENT_DYNAMIC(CheckPasswordDlg, CDialogEx)

CheckPasswordDlg::CheckPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CheckPasswordDlg::IDD, pParent)
	, m_csInputPassword(_T(""))
	, isCorrect(false)
{

}

CheckPasswordDlg::~CheckPasswordDlg()
{
}

void CheckPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ANSPSWD_EDIT_PSWD, m_csInputPassword);
}


BEGIN_MESSAGE_MAP(CheckPasswordDlg, CDialogEx)
	ON_BN_CLICKED(ANSPSWD_BUTTON_ENTER, &CheckPasswordDlg::OnBnClickedButtonEnter)
	ON_BN_CLICKED(ANSPSWD_BUTTON_CANCEL, &CheckPasswordDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CheckPasswordDlg message handlers


void CheckPasswordDlg::OnBnClickedButtonEnter()
{
	// TODO: Add your control notification handler code here
	// Obtain the set password from registry
	// and compare
	UpdateData(TRUE);
	CString gotPassword;
	GlobalFunction::GetConfigurationPassword(gotPassword);

	CString hashedPassword;
	GlobalFunction::GetHashedValueFromPassword(m_csInputPassword, hashedPassword);
	if (hashedPassword.Compare(gotPassword) == 0)
	{
		isCorrect = true;
		AfxMessageBox(_T("Correct paswd"));
		OnOK();
	}
	else{
		isCorrect = false;
		AfxMessageBox(_T("Incorrect paswd"));
	}
}


void CheckPasswordDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	isCorrect = false;
	OnOK();
}

bool CheckPasswordDlg::GetCorrectIncorrect()
{
	return isCorrect;
}