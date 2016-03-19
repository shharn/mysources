// Register.cpp : implementation file
//

#include "stdafx.h"
#include "Portal.h"
#include "Register.h"
#include "afxdialogex.h"


// Register dialog

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(Register::IDD, pParent)
	, m_ID(_T(""))
	, m_Password(_T(""))
	, m_EnterYear(0)
	, m_Phone(_T(""))
	, m_Address(_T(""))
	, m_Name(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();

}

Register::~Register()
{
}

void Register::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, 1007, m_ID);
	DDX_Text(pDX, 1009, m_Password);
	DDX_Control(pDX, 1025, m_ComboMajor);
	DDX_Text(pDX, 1013, m_EnterYear);
	DDX_Text(pDX, 1015, m_Phone);
	DDX_Text(pDX, 1012, m_Address);
	DDX_Text(pDX, 1008, m_Name);
	DDX_Control(pDX, IDC_COMBO1, m_ComboGender);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(1026, &Register::OnBnClicked1026)
	ON_BN_CLICKED(1027, &Register::OnBnClicked1027)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Register, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IRegister to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {26007234-3268-44D1-AEA7-4EB880885DB9}
static const IID IID_IRegister =
{ 0x26007234, 0x3268, 0x44D1, { 0xAE, 0xA7, 0x4E, 0xB8, 0x80, 0x88, 0x5D, 0xB9 } };

BEGIN_INTERFACE_MAP(Register, CDialogEx)
	INTERFACE_PART(Register, IID_IRegister, Dispatch)
END_INTERFACE_MAP()


// Register message handlers
// 100835 한승환

BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SYSTEMTIME curTime;				// system 시간 구조체 선언
	GetSystemTime(&curTime);		// system 시간 구조체 초기화
	int semester = 0;
	if (curTime.wMonth > 2 && curTime.wMonth < 7)
		semester = 1;				// system 시간이 3~6월 사이이면 semester = 1
	else if (curTime.wMonth>7 && curTime.wMonth <= 12)
		semester = 2;				// system 시간이 8~12월 사이이면 semester = 2
	m_EnterYear = curTime.wYear;
	UpdateData(FALSE);
	CSUBJECT_info<CSUBJECT_GETMAJOR> info;
	UpdateData(TRUE);
	info.m_YEAR = curTime.wYear;
	info.m_dwYEARLength = sizeof(LONG);
	info.m_dwYEARStatus = DBSTATUS_S_OK;

	info.m_SEMESTER = semester;
	info.m_dwSEMESTERLength = sizeof(LONG);
	info.m_dwSEMESTERStatus = DBSTATUS_S_OK;
	if (info.OpenAll() == S_OK)
	{
		while (info.MoveNext() == S_OK)
			m_ComboMajor.AddString(info.m_MAJOR);
		m_ComboMajor.SetCurSel(0);	// 초기 커서 0으로 설정
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// 확인 버튼을 눌렀을 때
void Register::OnBnClicked1026()
{
	// TODO: Add your control notification handler code here
	CRegister_Student<CRegister_StudentAccessor> info;
	UpdateData(TRUE);
	
	info.m_SID = atoi(m_ID);
	info.m_PASSWORD = atoi(m_Password);
	info.m_Curri_Year = m_EnterYear;
	CString major;
	m_ComboMajor.GetLBText(m_ComboMajor.GetCurSel(), major);
	CString Gender;
	m_ComboGender.GetLBText(m_ComboGender.GetCurSel(), Gender);
	strcpy_s(info.m_MAJOR, major);
	strcpy_s(info.m_Phone_Number, m_Phone);
	strcpy_s(info.m_SNAME, m_Name);
	strcpy_s(info.m_ADDERSS, m_Address);
	strcpy_s(info.m_GENDER, Gender);
	if (info.OpenAll() == S_OK)		// 데이터베이스 접속 성공
		AfxMessageBox("회원 등록 완료");
	else
		AfxMessageBox("등록 실패");
	OnOK();
}

// 취소 버튼을 눌렀을 때
void Register::OnBnClicked1027()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

// 100835 한승환