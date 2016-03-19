// Student.cpp : implementation file
//

#include "stdafx.h"
#include "Portal.h"
#include "Student.h"
#include "afxdialogex.h"

#define COMPARE_OK 0
#define RESTRICT_CREDIT 
#define ALREADY_EXIST 0
// Student dialog

IMPLEMENT_DYNAMIC(Student, CDialogEx)

Student::Student(CWnd* pParent /*=NULL*/)
	: CDialogEx(Student::IDD, pParent)
	, m_Keyword(_T(""))
{

	EnableAutomation();

}

Student::~Student()
{
}

void Student::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void Student::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, 1000, m_TabStudent);
	DDX_Control(pDX, LCONTROL_SUBLISTS, m_SubjectList);
	DDX_Control(pDX, LCONTROL_REGISTEREDSUBJECT, m_RegisteredSubject);
	DDX_Control(pDX, LCONTROL_CURCREDIT, m_ListCurrentCourse);
	DDX_Control(pDX, LCONTROL_GRADE, m_ListGrade);
	DDX_Control(pDX, COMBO_MAJOR, m_ComboMajor);
	DDX_Text(pDX, EDIT_KEYWORD, m_Keyword);
	DDX_Control(pDX, COMBO_YEAR, m_ComboYear);
	DDX_Control(pDX, COMBO_SEME, m_ComboSeme);
	DDX_Control(pDX, LCONTROL_SCHE, m_listSche);
}


BEGIN_MESSAGE_MAP(Student, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, 1000, &Student::OnTcnSelchange1000)
	ON_CBN_SELCHANGE(COMBO_MAJOR, &Student::OnCbnSelchangeMajor)
	ON_BN_CLICKED(BUTTON_SEARCH, &Student::OnBnClickedSearch)
	ON_NOTIFY(LVN_ITEMCHANGED, LCONTROL_REGISTEREDSUBJECT, &Student::OnLvnItemchangedRegisteredsubject)
	ON_NOTIFY(LVN_ITEMCHANGED, LCONTROL_SUBLISTS, &Student::OnLvnItemchangedSublists)
	ON_BN_CLICKED(BUTTON_ADDSUB, &Student::OnBnClickedAddsub)
	ON_BN_CLICKED(BUTTON_DELETESUB, &Student::OnBnClickedDeletesub)
	ON_CBN_SELCHANGE(COMBO_YEAR, &Student::OnCbnSelchangeYear)
	ON_CBN_SELCHANGE(COMBO_SEME, &Student::OnCbnSelchangeSeme)
	ON_BN_CLICKED(BUTTON_EXIT, &Student::OnBnClickedExit)
	ON_BN_CLICKED(BUTTON_MODIFY, &Student::OnBnClickedModify)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Student, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IStudent to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {11C7ECBF-98E9-4FE8-9D49-20E0893F4D36}
static const IID IID_IStudent =
{ 0x11C7ECBF, 0x98E9, 0x4FE8, { 0x9D, 0x49, 0x20, 0xE0, 0x89, 0x3F, 0x4D, 0x36 } };

BEGIN_INTERFACE_MAP(Student, CDialogEx)
	INTERFACE_PART(Student, IID_IStudent, Dispatch)
END_INTERFACE_MAP()


// Student message handlers
// 100835 한승환
// Student Dialogue 초기 설정

BOOL Student::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  Add extra initialization here
	InitTab();	// 탭 컨트롤 설정
	InitLControl();	// 리스트 컨트롤 메뉴 설정
	InitComboMajor();	// 수강신청 메뉴 콤보박스(전공) 설정
	InitNeededCredit();	// 졸업소요학점 설정
	InitSchedule();		// 시간표 설정
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// 졸업 소요학점 설정
void Student::InitNeededCredit()
{
	m_ListCurrentCourse.DeleteAllItems();
	CSTUDENT_info<CSTUDENT_GETCOURSEYEAR> CourseYear;	// 학생에게 해당하는 교과과정 얻기
	UpdateData(TRUE);
	CourseYear.m_SID = m_ID;
	CourseYear.m_dwSIDLength = sizeof(LONG);
	CourseYear.m_dwSIDStatus = DBSTATUS_S_OK;
	int stuCourseYear;
	if (CourseYear.OpenAll() == S_OK)
	{
		if (CourseYear.MoveNext() == S_OK)
			stuCourseYear = CourseYear.m_Curri_Year;
	}
	else
		AfxMessageBox("접속 실패");

	int Limit_RequCul = 0, Limit_Cul = 0, Limit_RequMajor = 0, Limit_Major = 0, Limit_General = 0, Total = 0;
	int Max_Cultural = 0;
	CGET_COURSE<CGET_COURSEAccessor> GetCredit;
	UpdateData(TRUE);
	GetCredit.m_YEAR = stuCourseYear;


	if (GetCredit.OpenAll() == S_OK)
	{
		Limit_RequCul = GetCredit.m_Required_Cultural;
		Limit_Cul = GetCredit.m_Cultural_Course;
		Max_Cultural = GetCredit.m_Max_Cultural;
		Limit_RequMajor = GetCredit.m_Required_Major;
		Limit_Major = GetCredit.m_Major_Course;
		Limit_General = GetCredit.m_General_Course;
		Total = GetCredit.m_Total_Credits;
	}
	else
		AfxMessageBox("GetCredit 접속 실패");
	CString str_LiRequCul; str_LiRequCul.Format("%d", Limit_RequCul);
	CString str_LiCul; str_LiCul.Format("%d", Limit_Cul);
	CString str_LiRequMaj; str_LiRequMaj.Format("%d", Limit_RequMajor);
	CString str_LiMaj; str_LiMaj.Format("%d", Limit_Major);
	CString str_LiGene; str_LiGene.Format("%d", Limit_General);
	CString str_MaxCul; str_MaxCul.Format("%d", Max_Cultural);
	CString str_TotalCredit; str_TotalCredit.Format("%d", Total);

	int iIndex = m_ListCurrentCourse.InsertItem(0, str_MaxCul, 0);
	m_ListCurrentCourse.SetItemText(iIndex, 0, str_MaxCul/* 최대교양인정학점 */);
	m_ListCurrentCourse.SetItemText(iIndex, 1, str_LiRequCul/* 교필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 2, str_LiCul/* 교선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 3, str_LiRequMaj/* 전필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 4, str_LiMaj/* 전선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 5, str_LiGene/* 일선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 6, str_TotalCredit/* 총 학점 */);

	// 지금까지 수강한 각각의 학점 계산
	CLECTURE_info<CLECTURE_GETCREDIT> info;
	UpdateData(TRUE);

	info.m_SID = m_ID;
	info.m_dwSIDLength = sizeof(LONG);
	info.m_dwSIDStatus = DBSTATUS_S_OK;
	int Required_Cultural = 0, Cultural_Course = 0, Required_Major = 0, Major_Course = 0, General_Course = 0, Total_Credits = 0;

	if (info.OpenAll() == S_OK)
	{
		while (info.MoveNext() == S_OK)
		{
			if (strcmp(info.m_Course_Type, "교필") == COMPARE_OK)
			{
				if (Required_Cultural + info.m_CREDITS > Limit_RequCul)
				{
					General_Course += Required_Cultural + info.m_CREDITS - Limit_RequCul;	
					Required_Cultural = Limit_RequCul;
				}
				else
					Required_Cultural += info.m_CREDITS;
			}
			else if (strcmp(info.m_Course_Type, "교선") == COMPARE_OK)
			{
				if (Cultural_Course + info.m_CREDITS > Limit_Cul)
				{
					General_Course += Cultural_Course + info.m_CREDITS - Limit_Cul;	// 교양 학점 초과시 초과한 학점만큼 일선 학점에 추가
					Cultural_Course = Limit_Cul;
				}
				else
					Cultural_Course += info.m_CREDITS;
			}
			else if (strcmp(info.m_Course_Type, "전필") == COMPARE_OK)
			{
				if (Required_Major + info.m_CREDITS > Limit_RequMajor)			// 전공선택 학점 초과시 초과한 학점만큼 일선 학점에 추가
					Required_Major = Limit_RequMajor;
				else
					Required_Major += info.m_CREDITS;
			}
			else if (strcmp(info.m_Course_Type, "전선") == COMPARE_OK)
			{
				if (Major_Course + info.m_CREDITS > Limit_Major)
				{
					General_Course += Major_Course + info.m_CREDITS - Limit_Major;
					Major_Course = Limit_Major;
				}
				else
					Major_Course += info.m_CREDITS;
			}
			else if (strcmp(info.m_Course_Type, "일선") == COMPARE_OK)
			{
				if (General_Course + info.m_CREDITS > Limit_General)
					General_Course = Limit_General;
				else
					General_Course += info.m_CREDITS;
			}
		}
	}
	else
		AfxMessageBox("접속 실패");
	Total_Credits = Required_Cultural + Cultural_Course + Required_Major + Major_Course + General_Course;
	// 지금까지 수강한 학점 입력
	CUPDATE_STUCOURSE<CUPDATE_STUCOURSEAccessor> credit;
	credit.m_SID = m_ID;
	credit.m_Required_Curtural = Required_Cultural;
	credit.m_Cultural_Course = Cultural_Course;
	credit.m_Required_Major = Required_Major;
	credit.m_Major_Course = Major_Course;
	credit.m_General_Course = General_Course;
	credit.m_Total_Credits = Total_Credits;
	if (credit.OpenAll() != S_OK)
		AfxMessageBox("입력 실패");

	// 해당 학생이 들었던 총 학점 리스트 컨트롤에 출력
	CString strRequCul; strRequCul.Format("%d", Required_Cultural);
	CString strCul; strCul.Format("%d", Cultural_Course);
	CString strRequMaj; strRequMaj.Format("%d", Required_Major);
	CString strMaj; strMaj.Format("%d", Major_Course);
	CString strGene; strGene.Format("%d", General_Course);
	CString strTotal; strTotal.Format("%d", Total_Credits);

	iIndex = m_ListCurrentCourse.InsertItem(1, "", 0);
	m_ListCurrentCourse.SetItemText(iIndex, 1, strRequCul/* 교필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 2, strCul/* 교선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 3, strRequMaj/* 전필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 4, strMaj/* 전선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 5, strGene/* 일선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 6, strTotal/* 총 학점 */);

	strRequCul.Format("%d", Limit_RequCul - Required_Cultural);
	strCul.Format("%d", Limit_Cul - Cultural_Course);
	strRequMaj.Format("%d", Limit_RequMajor - Required_Major);
	strMaj.Format("%d", Limit_Major - Major_Course);
	strGene.Format("%d", Limit_General - General_Course);
	strTotal.Format("%d", Total - Total_Credits);

	// 잔여 학점 출력
	iIndex = m_ListCurrentCourse.InsertItem(2, "잔여학점", 0);
	m_ListCurrentCourse.SetItemText(iIndex, 1, strRequCul/* 교필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 2, strCul/* 교선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 3, strRequMaj/* 전필 */);
	m_ListCurrentCourse.SetItemText(iIndex, 4, strMaj/* 전선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 5, strGene/* 일선 */);
	m_ListCurrentCourse.SetItemText(iIndex, 6, strTotal/* 총 학점 */);


}



void Student::InitComboMajor()
{
	// 수강신청 메뉴에서 콤보박스에 전공 집어넣기

	SYSTEMTIME curTime;				// system 시간 구조체 선언
	GetSystemTime(&curTime);		// system 시간 구조체 초기화
	int semester = 0;
	if (curTime.wMonth > 2 && curTime.wMonth < 7)
		semester = 1;				// system 시간이 3~6월 사이이면 semester = 1
	else if (curTime.wMonth>7 && curTime.wMonth <= 12)
		semester = 2;				// system 시간이 8~12월 사이이면 semester = 2

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
	UpdateCurSubject();

	// 성적 조회
	// 콤보박스 설정
	// 년도
	CLECTURE_info<CLECTURE_GETYEAR> year;
	UpdateData(TRUE);
	year.m_SID = m_ID;
	year.m_dwSIDLength = sizeof(LONG);
	year.m_dwSIDStatus = DBSTATUS_S_OK;
	if (year.OpenAll() == S_OK)
	{
		while (year.MoveNext() == S_OK)
		{
			CString strYear;
			strYear.Format("%d", year.m_YEAR);
			m_ComboYear.AddString(strYear);
		}
		m_ComboYear.SetCurSel(0);
	}
}
void Student::InitTab()
{
	TC_ITEM tabItem;
	char *tabName[4] = { "수강신청", "시간표", "졸업소요학점", "성적조회" };			// 탭 메뉴 이름
	for (int i = 0; i < 4; i++)
	{
		tabItem.mask = TCIF_TEXT;
		tabItem.pszText = tabName[i];
		m_TabStudent.InsertItem(i, &tabItem);
	}

	// 초기화면 설정
	GetDlgItem(BUTTON_EXIT)->ShowWindow(TRUE);
	GetDlgItem(BUTTON_MODIFY)->ShowWindow(TRUE);

	// Window - 'Sign up the course'
	GetDlgItem(COMBO_MAJOR)->ShowWindow(TRUE);
	GetDlgItem(EDIT_KEYWORD)->ShowWindow(TRUE);
	GetDlgItem(BUTTON_SEARCH)->ShowWindow(TRUE);
	GetDlgItem(LCONTROL_SUBLISTS)->ShowWindow(TRUE);
	GetDlgItem(BUTTON_ADDSUB)->ShowWindow(TRUE);
	GetDlgItem(BUTTON_DELETESUB)->ShowWindow(TRUE);
	GetDlgItem(STATIC_REGISUB)->ShowWindow(TRUE);
	GetDlgItem(LCONTROL_REGISTEREDSUBJECT)->ShowWindow(TRUE);
	GetDlgItem(STATIC_SUBLIST)->ShowWindow(TRUE);

	// Window - 'Show Schedule'
	GetDlgItem(STATIC_SCHE)->ShowWindow(FALSE);
	GetDlgItem(LCONTROL_SCHE)->ShowWindow(FALSE);

	// Window - 'Show current & needed course'
	GetDlgItem(STATIC_CURCREDIT)->ShowWindow(FALSE);
	GetDlgItem(LCONTROL_CURCREDIT)->ShowWindow(FALSE);

	// Window - 'Show Grade'
	GetDlgItem(COMBO_YEAR)->ShowWindow(FALSE);
	GetDlgItem(COMBO_SEME)->ShowWindow(FALSE);
	GetDlgItem(STATIC_GRADE)->ShowWindow(FALSE);
	GetDlgItem(LCONTROL_GRADE)->ShowWindow(FALSE);
}

void Student::InitLControl()
{
	// 리스트 - 수강 신청
	m_SubjectList.InsertColumn(0, "과목코드", 0, 80);
	m_SubjectList.InsertColumn(1, "과목명", 0, 70);
	m_SubjectList.InsertColumn(2, "학점", 0, 50);
	m_SubjectList.InsertColumn(3, "담당교수", 0, 60);
	m_SubjectList.InsertColumn(4, "교과구분", 0, 60);


	m_listSche.InsertColumn(0, "교과목코드", 0, 80);
	m_listSche.InsertColumn(1, "교과목명", 0, 70);
	m_listSche.InsertColumn(2, "학점", 0, 40);
	m_listSche.InsertColumn(3, "담당교수", 0, 70);
	m_listSche.InsertColumn(4, "강의시간", 0, 70);
	m_listSche.InsertColumn(5, "강의실", 0, 55);

	// 리스트 - 신청된 과목
	m_RegisteredSubject.InsertColumn(0, "과목코드", 0, 80);
	m_RegisteredSubject.InsertColumn(1, "과목명", 0, 70);
	m_RegisteredSubject.InsertColumn(2, "학점", 0, 50);
	m_RegisteredSubject.InsertColumn(3, "담당교수", 0, 60);
	m_RegisteredSubject.InsertColumn(4, "교과구분", 0, 60);

	// 졸업소요 학점
	m_ListCurrentCourse.InsertColumn(0, "최대교양인정학점", 0, 110);
	m_ListCurrentCourse.InsertColumn(1, "교필", 0, 50);
	m_ListCurrentCourse.InsertColumn(2, "교선", 0, 50);
	m_ListCurrentCourse.InsertColumn(3, "전필", 0, 50);
	m_ListCurrentCourse.InsertColumn(4, "전선", 0, 50);
	m_ListCurrentCourse.InsertColumn(5, "일선", 0, 50);
	m_ListCurrentCourse.InsertColumn(6, "총계", 0, 50);


	// 리스트 - 성적조회
	m_ListGrade.InsertColumn(0, "교과목명", 0, 100);
	m_ListGrade.InsertColumn(1, "교과목번호", 0, 80);
	m_ListGrade.InsertColumn(2, "학점", 0, 50);
	m_ListGrade.InsertColumn(3, "등급", 0, 50);
	m_ListGrade.InsertColumn(4, "담당교수", 0, 60);
	m_ListGrade.InsertColumn(5, "년도", 0, 50);
	m_ListGrade.InsertColumn(6, "학기", 0, 50);
}

// 현재 신청된 과목 리스트 
void Student::UpdateCurSubject()
{
	SYSTEMTIME curTime;				// system 시간 구조체 선언
	GetSystemTime(&curTime);		// system 시간 구조체 초기화
	int semester = 0;
	if (curTime.wMonth > 2 && curTime.wMonth < 7)
		semester = 1;				// system 시간이 3~6월 사이이면 semester = 1
	else if (curTime.wMonth>7 && curTime.wMonth <= 12)
		semester = 2;				// system 시간이 8~12월 사이이면 semester = 2

	CLECTURE_info<CLECTURE_GETCURRENTSUBJECT> info2;
	UpdateData(TRUE);
	info2.m_SID = m_ID;
	info2.m_dwSIDLength = sizeof(LONG);
	info2.m_dwSIDStatus = DBSTATUS_S_OK;

	info2.m_YEAR = curTime.wYear;
	info2.m_dwYEARLength = sizeof(LONG);
	info2.m_dwYEARStatus = DBSTATUS_S_OK;

	info2.m_SEMESTER = semester;
	info2.m_dwSEMESTERLength = sizeof(LONG);
	info2.m_dwSEMESTERStatus = DBSTATUS_S_OK;

	if (info2.OpenAll() == S_OK)
	{
		m_RegisteredSubject.DeleteAllItems();
		int iCount = 0;
		while (info2.MoveNext() == S_OK)
		{
			CString strCredit;
			strCredit.Format("%d", info2.m_CREDITS);
			int iIndex = m_RegisteredSubject.InsertItem(iCount, info2.m_Subject_Number, 0);
			m_RegisteredSubject.SetItemText(iIndex, 0, info2.m_Subject_Number/* 교과목코드 */);
			m_RegisteredSubject.SetItemText(iIndex, 1, info2.m_Subject_Name/* 교과목명 */);
			m_RegisteredSubject.SetItemText(iIndex, 2, strCredit/* 해당 학점 */);
			m_RegisteredSubject.SetItemText(iIndex, 3, info2.m_PROFESSOR/* 담당교수 */);
			m_RegisteredSubject.SetItemText(iIndex, 4, info2.m_Course_Type/* 교과구분 */);
			++iCount;
		}
	}
	else
		AfxMessageBox("접속 실패");
}

void Student::OnTcnSelchange1000(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nSelection = m_TabStudent.GetCurSel();
	GetDlgItem(BUTTON_EXIT)->ShowWindow(TRUE);
	GetDlgItem(BUTTON_MODIFY)->ShowWindow(TRUE);
	switch (nSelection){
		// 수강신청 화면
	case 0:

		// Window - 'Sign up the course'
		GetDlgItem(COMBO_MAJOR)->ShowWindow(TRUE);
		GetDlgItem(EDIT_KEYWORD)->ShowWindow(TRUE);
		GetDlgItem(BUTTON_SEARCH)->ShowWindow(TRUE);
		GetDlgItem(LCONTROL_SUBLISTS)->ShowWindow(TRUE);
		GetDlgItem(BUTTON_ADDSUB)->ShowWindow(TRUE);
		GetDlgItem(BUTTON_DELETESUB)->ShowWindow(TRUE);
		GetDlgItem(STATIC_REGISUB)->ShowWindow(TRUE);
		GetDlgItem(LCONTROL_REGISTEREDSUBJECT)->ShowWindow(TRUE);
		GetDlgItem(STATIC_SUBLIST)->ShowWindow(TRUE);

		// Window - 'Show Schedule'
		GetDlgItem(STATIC_SCHE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SCHE)->ShowWindow(FALSE);

		// Window - 'Show current & needed course'
		GetDlgItem(STATIC_CURCREDIT)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_CURCREDIT)->ShowWindow(FALSE);

		// Window - 'Show Grade'
		GetDlgItem(COMBO_YEAR)->ShowWindow(FALSE);
		GetDlgItem(COMBO_SEME)->ShowWindow(FALSE);
		GetDlgItem(STATIC_GRADE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_GRADE)->ShowWindow(FALSE);

		break;
		// 시간표 화면
	case 1:
		// Window - 'Sign up the course'
		GetDlgItem(COMBO_MAJOR)->ShowWindow(FALSE);
		GetDlgItem(EDIT_KEYWORD)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_SEARCH)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SUBLISTS)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_ADDSUB)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_DELETESUB)->ShowWindow(FALSE);
		GetDlgItem(STATIC_REGISUB)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_REGISTEREDSUBJECT)->ShowWindow(FALSE);
		GetDlgItem(STATIC_SUBLIST)->ShowWindow(FALSE);

		// Window - 'Show Schedule'
		GetDlgItem(STATIC_SCHE)->ShowWindow(TRUE);
		GetDlgItem(LCONTROL_SCHE)->ShowWindow(TRUE);

		// Window - 'Show current & needed course'
		GetDlgItem(STATIC_CURCREDIT)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_CURCREDIT)->ShowWindow(FALSE);

		// Window - 'Show Grade'
		GetDlgItem(COMBO_YEAR)->ShowWindow(FALSE);
		GetDlgItem(COMBO_SEME)->ShowWindow(FALSE);
		GetDlgItem(STATIC_GRADE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_GRADE)->ShowWindow(FALSE);

		break;
		// 졸업소요학점 화면
	case 2:
		// Window - 'Sign up the course'
		GetDlgItem(COMBO_MAJOR)->ShowWindow(FALSE);
		GetDlgItem(EDIT_KEYWORD)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_SEARCH)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SUBLISTS)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_ADDSUB)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_DELETESUB)->ShowWindow(FALSE);
		GetDlgItem(STATIC_REGISUB)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_REGISTEREDSUBJECT)->ShowWindow(FALSE);
		GetDlgItem(STATIC_SUBLIST)->ShowWindow(FALSE);

		// Window - 'Show Schedule'
		GetDlgItem(STATIC_SCHE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SCHE)->ShowWindow(FALSE);

		// Window - 'Show current & needed course'
		GetDlgItem(STATIC_CURCREDIT)->ShowWindow(TRUE);
		GetDlgItem(LCONTROL_CURCREDIT)->ShowWindow(TRUE);

		// Window - 'Show Grade'
		GetDlgItem(COMBO_YEAR)->ShowWindow(FALSE);
		GetDlgItem(COMBO_SEME)->ShowWindow(FALSE);
		GetDlgItem(STATIC_GRADE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_GRADE)->ShowWindow(FALSE);



		break;

		// 성적조회 화면
	case 3:
		GetDlgItem(COMBO_MAJOR)->ShowWindow(FALSE);
		GetDlgItem(EDIT_KEYWORD)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_SEARCH)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SUBLISTS)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_ADDSUB)->ShowWindow(FALSE);
		GetDlgItem(BUTTON_DELETESUB)->ShowWindow(FALSE);
		GetDlgItem(STATIC_REGISUB)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_REGISTEREDSUBJECT)->ShowWindow(FALSE);
		GetDlgItem(STATIC_SUBLIST)->ShowWindow(FALSE);

		// Window - 'Show Schedule'
		GetDlgItem(STATIC_SCHE)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_SCHE)->ShowWindow(FALSE);

		// Window - 'Show current & needed course'
		GetDlgItem(STATIC_CURCREDIT)->ShowWindow(FALSE);
		GetDlgItem(LCONTROL_CURCREDIT)->ShowWindow(FALSE);

		// Window - 'Show Grade'
		GetDlgItem(COMBO_YEAR)->ShowWindow(TRUE);
		GetDlgItem(COMBO_SEME)->ShowWindow(TRUE);
		GetDlgItem(STATIC_GRADE)->ShowWindow(TRUE);
		GetDlgItem(LCONTROL_GRADE)->ShowWindow(TRUE);


		break;
	}
	*pResult = 0;
}

// 현재 년도, 학기에 해당하는 과목을 개설한 학과 콤보박스에 추가
void Student::OnCbnSelchangeMajor()
{
	// TODO: Add your control notification handler code here
	CSUBJECT_info<CSUBJECT_GETSUBJECTINFO> info;
	UpdateData(TRUE);
	m_ComboMajor.GetLBText(m_ComboMajor.GetCurSel(), major);	// Combo Box에서 선택된 텍스트 얻기
	SYSTEMTIME curTime;				// system 시간 구조체 선언
	GetSystemTime(&curTime);		// system 시간 구조체 초기화
	int semester = 0;
	if (curTime.wMonth > 2 && curTime.wMonth < 7)
		semester = 1;				// system 시간이 3~6월 사이이면 semester = 1
	else if (curTime.wMonth>7 && curTime.wMonth <= 12)
		semester = 2;				// system 시간이 8~12월 사이이면 semester = 2

	strcpy_s(info.m_MAJOR, major);
	info.m_dwMAJORLength = strlen(major);
	info.m_dwMAJORStatus = DBSTATUS_S_OK;

	info.m_YEAR = curTime.wYear;
	info.m_dwYEARLength = sizeof(LONG);
	info.m_dwYEARStatus = DBSTATUS_S_OK;

	info.m_SEMESTER = semester;
	info.m_dwSEMESTERLength = sizeof(LONG);
	info.m_dwSEMESTERStatus = DBSTATUS_S_OK;

	if (info.OpenAll() == S_OK)
	{
		m_SubjectList.DeleteAllItems();	// 리스트 초기화
		int iCount = 0;
		while (info.MoveNext() == S_OK)
		{
			CString strCredit;
			strCredit.Format("%d", info.m_CREDITS);
			int iIndex = m_SubjectList.InsertItem(iCount, info.m_Subject_Number, 0);
			m_SubjectList.SetItemText(iIndex, 0, info.m_Subject_Number/* 교과목코드 */);
			m_SubjectList.SetItemText(iIndex, 1, info.m_Subject_Name/* 교과목명 */);
			m_SubjectList.SetItemText(iIndex, 2, strCredit/* 해당 학점 */);
			m_SubjectList.SetItemText(iIndex, 3, info.m_PROFESSOR/* 담당교수 */);
			m_SubjectList.SetItemText(iIndex, 4, info.m_Course_Type/* 교과구분 */);
			++iCount;
		}
	}
	else
		AfxMessageBox("접속 실패");
}

void Student::setID(int SID)
{
	this->m_ID = SID;
}

void Student::SetName(TCHAR *SNAME)
{
	this->m_StudentName.Format(SNAME);
}

// 키워드 검색
void Student::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	CSUBJECT_info<CSUBJECT_SEARCHKEYWORD> info;
	UpdateData(TRUE);
	SYSTEMTIME curTime;				// system 시간 구조체 선언
	GetSystemTime(&curTime);		// system 시간 구조체 초기화
	int semester = 0;
	if (curTime.wMonth > 2 && curTime.wMonth < 7)
		semester = 1;				// system 시간이 3~6월 사이이면 semester = 1
	else if (curTime.wMonth>7 && curTime.wMonth <= 12)
		semester = 2;				// system 시간이 8~12월 사이이면 semester = 2

	info.m_YEAR = curTime.wYear;
	info.m_dwYEARLength = sizeof(LONG);
	info.m_dwYEARStatus = DBSTATUS_S_OK;

	info.m_SEMESTER = semester;
	info.m_dwSEMESTERLength = sizeof(LONG);
	info.m_dwSEMESTERStatus = DBSTATUS_S_OK;

	CString WholeKeyword;
	if (info.OpenAll() == S_OK)
	{
		m_SubjectList.DeleteAllItems();	// 리스트 초기화
		int iCount = 0;
		CString WholeCode;
		while (info.MoveNext() == S_OK)
		{
			
			WholeKeyword.Format(info.m_KEYWORD);
			int i = WholeKeyword.Find(m_Keyword);		// m_Keyword -> 사용자가 입력한 키워드, 검색결과 못찾았으면 -1
			if (i!=-1 && (WholeCode.Find(info.m_Subject_Number)==-1))
			{
				WholeCode.AppendFormat(info.m_Subject_Number);
				CString strCredit;
				strCredit.Format("%d", info.m_CREDITS);
				int iIndex = m_SubjectList.InsertItem(iCount, info.m_Subject_Number, 0);
				m_SubjectList.SetItemText(iIndex, 0, info.m_Subject_Number/* 교과목코드 */);
				m_SubjectList.SetItemText(iIndex, 1, info.m_Subject_Name/* 교과목명 */);
				m_SubjectList.SetItemText(iIndex, 2, strCredit/* 해당 학점 */);
				m_SubjectList.SetItemText(iIndex, 3, info.m_PROFESSOR/* 담당교수 */);
				m_SubjectList.SetItemText(iIndex, 4, info.m_Course_Type/* 교과구분 */);
				++iCount;
			}
		}
	}
	else
		AfxMessageBox("접속 실패");
}

// 리스트 컨트롤에서 아이템 선택시 선택한 열의 인덱스 추출(현재 신청된 과목)
void Student::OnLvnItemchangedRegisteredsubject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	SelectedRow_CurSub = m_RegisteredSubject.GetSelectionMark();
	*pResult = 0;
}

// 리스트 컨트롤에서 아이템 선택시 선택한 열의 인덱스 추출(신청하려는 과목)
void Student::OnLvnItemchangedSublists(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	SelectedRow_ListSub = m_SubjectList.GetSelectionMark();
	*pResult = 0;
}

// 수강 신청 버튼을 눌렀을 때
void Student::OnBnClickedAddsub()
{
	// TODO: Add your control notification handler code here
	//CLECTURE_info<CLECTURE_ADDSTUDENTTOLECTURE> info;
	CADD_Lecture<CADD_LectureAccessor> info;
	UpdateData(TRUE);
	CString Subject_Code = m_SubjectList.GetItemText(SelectedRow_ListSub, 0);
	info.m_SID = m_ID;
	strcpy_s(info.m_Subject_Number, Subject_Code);
	
	int iIndex = 0;
	bool flag = 1;
	CString temp;
	while (m_RegisteredSubject.GetItemText(iIndex, 0) != "")
	{
		temp = m_RegisteredSubject.GetItemText(iIndex, 0);
		if (Subject_Code == temp)
		{
			flag = ALREADY_EXIST;
			break;
		}
		iIndex++;
	}
	if (flag == ALREADY_EXIST)
		AfxMessageBox("이미 신청되어있습니다");
	else
	{
		if (info.OpenAll() == S_OK)
		{
			AfxMessageBox("신청 완료");
		
		}
		else
			AfxMessageBox("신청 실패");
		UpdateCurSubject();
		InitSchedule();
		InitNeededCredit();
	}
	
		
	UpdateData(TRUE);
}

// 과목 삭제 버튼을 눌렀을때
void Student::OnBnClickedDeletesub()
{
	// TODO: Add your control notification handler code here
	CDrop_Lecture<CDrop_LectureAccessor> info;
	UpdateData(TRUE);
	CString Subject_Code = m_RegisteredSubject.GetItemText(SelectedRow_CurSub, 0);
	info.m_SID = m_ID;
	strcpy_s(info.m_Subject_Number, Subject_Code);

	if (info.OpenAll() == S_OK)
	{
		AfxMessageBox("삭제 완료");
		
	}
	else
		AfxMessageBox("삭제 실패");
	UpdateCurSubject();
	InitSchedule();
	InitNeededCredit();
	UpdateData(TRUE);
}

// 성적 조회에서 년도 선택시 학기 콤보박스 설정
void Student::OnCbnSelchangeYear()
{
	// TODO: Add your control notification handler code here
	// 학기
	CLECTURE_info<CLECTURE_GETSEMESTER> seme;
	UpdateData(TRUE);
	CString strYear;
	m_ComboYear.GetLBText(m_ComboYear.GetCurSel(), strYear);	// 콤보박스에서 사용자가 선택한 텍스트 얻어오기
	Combo_SelYear = atoi(strYear);

	seme.m_SID = m_ID;
	seme.m_dwSIDLength = sizeof(LONG);
	seme.m_dwSIDStatus = DBSTATUS_S_OK;

	seme.m_YEAR = Combo_SelYear;
	seme.m_dwYEARLength = sizeof(LONG);
	seme.m_dwYEARStatus = DBSTATUS_S_OK;

	if (seme.OpenAll() == S_OK)
	{
		int count = m_ComboSeme.GetCount();
		for(int i=0;i<count;i++)
			m_ComboSeme.DeleteString(count-i-1);
		while (seme.MoveNext() == S_OK)
		{
			CString strSeme;
			strSeme.Format("%d", seme.m_SEMESTER);
			m_ComboSeme.AddString(strSeme);
		}
		m_ComboSeme.SetCurSel(0);
	}
	else
		AfxMessageBox("접속 실패");
}

// 콤보박스에서 학기 선택시 선택된 년도와 학기에 대한 성적 출력
void Student::OnCbnSelchangeSeme()
{
	// TODO: Add your control notification handler code here
	CLECTURE_info<CLECTURE_GETGRADE> info;
	UpdateData(TRUE);
	CString strSeme;
	m_ComboSeme.GetLBText(m_ComboSeme.GetCurSel(), strSeme);
	int SelSeme = atoi(strSeme);

	info.m_SID = m_ID;
	info.m_dwSIDLength = sizeof(LONG);
	info.m_dwSIDStatus = DBSTATUS_S_OK;

	info.m_YEAR = Combo_SelYear;
	info.m_dwYEARLength = sizeof(LONG);
	info.m_dwYEARStatus = DBSTATUS_S_OK;

	info.m_SEMESTER = SelSeme;
	info.m_dwSEMESTERLength = sizeof(LONG);
	info.m_dwSEMESTERStatus = DBSTATUS_S_OK;
	int totalCredit = 0;
	double totalGrade = 0;
	double AvgGrade = 0;
	if (info.OpenAll() == S_OK)
	{
		m_ListGrade.DeleteAllItems();	// 리스트 초기화
		int iCount = 0;
		while (info.MoveNext() == S_OK)
		{
			totalCredit += info.m_CREDITS;
			totalGrade += info.m_RESULT*info.m_CREDITS;
			CString strCredit;	strCredit.Format("%d", info.m_CREDITS);
			CString strGrade;	strGrade.Format("%2.1f", info.m_RESULT);
			CString strYear;	strYear.Format("%d", Combo_SelYear);
			CString strSeme;	strSeme.Format("%d", SelSeme);
			int iIndex = m_ListGrade.InsertItem(iCount, info.m_Subject_Number, 0);
			m_ListGrade.SetItemText(iIndex, 0, info.m_Subject_Name/* 교과목명 */);
			m_ListGrade.SetItemText(iIndex, 1, info.m_Subject_Number/* 교과목코드 */);
			m_ListGrade.SetItemText(iIndex, 2, strCredit/* 해당 학점 */);
			m_ListGrade.SetItemText(iIndex, 3, strGrade/* 해당 등급 */);
			m_ListGrade.SetItemText(iIndex, 4, info.m_PROFESSOR/* 담당교수 */);
			m_ListGrade.SetItemText(iIndex, 5, strYear/* 해당년도 */);
			m_ListGrade.SetItemText(iIndex, 6, strSeme/* 해당년도 */);
			++iCount;
		}
		AvgGrade = ((double)totalGrade / (double)totalCredit);
		CString strTotalCredit;	strTotalCredit.Format("%d", totalCredit);
		CString strAvgGrade;	strAvgGrade.Format("%4.2f", AvgGrade);
	
		int iIndex = m_ListGrade.InsertItem(iCount, "학기평점", 0);
		m_ListGrade.SetItemText(iIndex, 2, strTotalCredit/* 해당 학점 */);
		m_ListGrade.SetItemText(iIndex, 3, strAvgGrade/* 해당 등급 */);
	}
	else
		AfxMessageBox("접속 실패");

}



void Student::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void Student::OnBnClickedModify()
{
	// TODO: Add your control notification handler code here
	Stu_ModiInfo dlg;
	dlg.SetmID(m_ID);
	if (dlg.DoModal() == S_OK)
	{
		OnOK();
	}
}



// 시간표 출력
void Student::InitSchedule()
{
	// 신청된 과목 리스트 컨트롤에서 과목코드 추출
	int iiIndex = 0;
	CString temp;
	int iCount = 0;
	m_listSche.DeleteAllItems();
	while (m_RegisteredSubject.GetItemText(iiIndex, 0) != "")			// 신청된 과목 목록에서 과목코드 얻어내기
	{
		temp = m_RegisteredSubject.GetItemText(iiIndex, 0);
		CSUBJECT_info<CSUBJECT_Schedule> info;							// 얻어낸 과목코드로 데이터베이스 접속하여 시간 정보 얻어내기
		strcpy_s(info.m_Subject_Number, temp);
		info.m_dwSubject_NumberLength = strlen(temp);
		info.m_dwSubject_NumberStatus = DBSTATUS_S_OK;
	
		if (info.OpenAll() == S_OK)
		{
			if(info.MoveFirst() == S_OK)
			{
				CString Credits;	Credits.Format("%d", info.m_CREDITS);
				CString Class_Time;
				if (info.m_Class_Time / 10 == 1)
				{
					int time = info.m_Class_Time % 10;
					Class_Time.Format("월 수 금 %d", time);
				}
				else
				{
					int time = info.m_Class_Time % 10;
					Class_Time.Format("화 목 %d", time);
				}
				int iIndex = m_listSche.InsertItem(iCount, temp, 0);
				m_listSche.SetItemText(iIndex, 1, info.m_Subject_Name);
				m_listSche.SetItemText(iIndex, 2, Credits);
				m_listSche.SetItemText(iIndex, 3, info.m_PROFESSOR);
				m_listSche.SetItemText(iIndex, 4, Class_Time);
				m_listSche.SetItemText(iIndex, 5, info.m_CLASSROOM);
				++iCount;
			}
		}
		
		iiIndex++;
		info.CloseAll();
	}
}
// 100835 한승환