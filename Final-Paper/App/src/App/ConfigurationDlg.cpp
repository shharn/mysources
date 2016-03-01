// ConfigurationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "ConfigurationDlg.h"
#include "afxdialogex.h"

// CConfigurationDlg dialog
extern std::string tempPath;

IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialogEx)

CConfigurationDlg::CConfigurationDlg(CString targetPath,
									CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigurationDlg::IDD, pParent)
	, choiceLevel(SEARCH_LEVEL_MEDIUM)
{

}

CConfigurationDlg::~CConfigurationDlg()
{
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_MEDIUM, m_radioMedium);
}


BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO_LOW, &CConfigurationDlg::OnBnClickedRadioLow)
	ON_BN_CLICKED(IDC_RADIO_MEDIUM, &CConfigurationDlg::OnBnClickedRadioMedium)
	ON_BN_CLICKED(IDC_RADIO_HIGH, &CConfigurationDlg::OnBnClickedRadioHigh)
	ON_BN_CLICKED(CONF_BUTTON_OK, &CConfigurationDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(CONF_BUTTON_CANCEL, &CConfigurationDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

// CConfigurationDlg message handlers
BOOL CConfigurationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_radioMedium.SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*
void CConfigurationDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_BUTTON_TARGET, _T("Searching..."));
	((CButton*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(FALSE);
	
	wThread.PrePareWorker(GetSafeHwnd(), targetPath, destPath, choiceLevel);
}
*/

void CConfigurationDlg::OnBnClickedRadioLow()
{
	// TODO: Add your control notification handler code here
	choiceLevel = SEARCH_LEVEL_LOW;
}


void CConfigurationDlg::OnBnClickedRadioMedium()
{
	// TODO: Add your control notification handler code here
	choiceLevel = SEARCH_LEVEL_MEDIUM;
}


void CConfigurationDlg::OnBnClickedRadioHigh()
{
	// TODO: Add your control notification handler code here
	choiceLevel = SEARCH_LEVEL_HIGH;
}

double CConfigurationDlg::GetLevelOfDetection()
{
	return choiceLevel;
}

void CConfigurationDlg::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CConfigurationDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
