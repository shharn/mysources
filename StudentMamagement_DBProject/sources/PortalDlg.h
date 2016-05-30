
// PortalDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "STUDENT_info.h"
#include "Student.h"
#include "LECTURE_info.h"
#include "SUBJECT_info.h"
#include "Drop_Lecture.h"
#include "ADD_Lecture.h"
#include "UPDATE_STUCOURSE.h"
#include "GET_COURSE.h"
#include "GET_STUINFO.h"
#include "Stu_ModiInfo.h"
#include "FIX_STUINFO.h"
#include "Register.h"
#include "Register_Student.h"

// CPortalDlg dialog
class CPortalDlg : public CDialogEx
{
// Construction
public:
	CPortalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PORTAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ID;
	CString m_Password;
	afx_msg void OnBnClicked1003();
	afx_msg void OnBnClicked1005();
	CButton m_ButtonLogin;
};
