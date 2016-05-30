#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Student dialog

class Student : public CDialogEx
{
	DECLARE_DYNAMIC(Student)

public:
	Student(CWnd* pParent = NULL);   // standard constructor
	virtual ~Student();

	virtual void OnFinalRelease();

	// Dialog Data
	enum { IDD = IDD_STUDENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_TabStudent;

	CListCtrl m_SubjectList;
	CListCtrl m_RegisteredSubject;
	CListCtrl m_ListCurrentCourse;
	CListCtrl m_ListGrade;
	afx_msg void OnTcnSelchange1000(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_ComboMajor;
	afx_msg void OnCbnSelchangeMajor();
	void setID(int SID);
	void SetName(TCHAR *SNAME);
	CString major;
	void UpdateCurSubject(void);
	void InitTab();
	void InitLControl();
private:
	int m_ID;
	CString m_StudentName;
	int Combo_SelYear;
public:
	afx_msg void OnBnClickedSearch();
	CString m_Keyword;
	
	afx_msg void OnLvnItemchangedRegisteredsubject(NMHDR *pNMHDR, LRESULT *pResult);
	int SelectedRow_CurSub;
	int SelectedRow_ListSub;
	afx_msg void OnLvnItemchangedSublists(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddsub();
	afx_msg void OnBnClickedDeletesub();
	CComboBox m_ComboYear;
	CComboBox m_ComboSeme;
	afx_msg void OnCbnSelchangeYear();
	afx_msg void OnCbnSelchangeSeme();
	void InitComboMajor();
	void InitNeededCredit();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedModify();
	CListCtrl m_listSche;
	void InitSchedule();
};
