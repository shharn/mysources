// DeleteConfirmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "DeleteConfirmDlg.h"
#include "afxdialogex.h"


// DeleteConfirmDlg dialog

IMPLEMENT_DYNAMIC(DeleteConfirmDlg, CDialogEx)

DeleteConfirmDlg::DeleteConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DeleteConfirmDlg::IDD, pParent)
	, delConfirm(false)
{

}

DeleteConfirmDlg::~DeleteConfirmDlg()
{
}

void DeleteConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DeleteConfirmDlg, CDialogEx)
	ON_BN_CLICKED(DELCON_BUTTON_CANCEL, &DeleteConfirmDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(DELCON_BUTTON_OK, &DeleteConfirmDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// DeleteConfirmDlg message handlers


void DeleteConfirmDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	SetDelConfirm(false);
	OnOK();
}


void DeleteConfirmDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	SetDelConfirm(true);
	OnOK();
}

bool DeleteConfirmDlg::GetDelConfirm()
{
	return delConfirm;
}

void DeleteConfirmDlg::SetDelConfirm(bool delConfirm)
{
	this->delConfirm = delConfirm;
}
