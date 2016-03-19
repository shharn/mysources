#pragma once
#include "afxwin.h"


// Register dialog

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // standard constructor
	virtual ~Register();

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClicked1026();
	afx_msg void OnBnClicked1027();
	CString m_ID;
	CString m_Password;
	CComboBox m_ComboMajor;
	int m_EnterYear;
	CString m_Phone;
	CString m_Address;
	CString m_Name;
	CComboBox m_ComboGender;
};
