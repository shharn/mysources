// Stu_ModiInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Portal.h"
#include "Stu_ModiInfo.h"
#include "afxdialogex.h"

// Stu_ModiInfo dialog

IMPLEMENT_DYNAMIC(Stu_ModiInfo, CDialogEx)

Stu_ModiInfo::Stu_ModiInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(Stu_ModiInfo::IDD, pParent)
	, m_Password(0)
{

}

Stu_ModiInfo::~Stu_ModiInfo()
{
}

void Stu_ModiInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, EDIT_PHONE, m_Phone);
	DDX_Text(pDX, EDIT_ADDR, m_Address);
}


BEGIN_MESSAGE_MAP(Stu_ModiInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &Stu_ModiInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// Stu_ModiInfo message handlers
// 100835 한승환

BOOL Stu_ModiInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CGET_STUINFO<CGET_STUINFOAccessor> info;
	info.m_SID = m_ID;
	if (info.OpenAll() == S_OK)
	{
		m_Password = info.m_PASSWORD;
		m_Phone.Format(info.m_Phone_Number);
		m_Address.Format(info.m_ADDRESS);
	}
	UpdateData(FALSE);


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void Stu_ModiInfo::SetmID(int m_SID)
{
	this->m_ID = m_SID;
}

// 확인 버튼 눌렀을 때
void Stu_ModiInfo::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CFIX_STUINFO<CFIX_STUINFOAccessor> info;
	UpdateData(TRUE);
	info.m_SID = m_ID;
	info.m_PASSWORD = m_Password;
	strcpy_s(info.m_Phone_Number, m_Phone);
	strcpy_s(info.m_ADDRESS, m_Address);
	if (info.OpenAll() == S_OK)
		AfxMessageBox("수정 완료");
	else
		AfxMessageBox("수정 실패");
	CDialogEx::OnOK();
}

// 100835 한승환