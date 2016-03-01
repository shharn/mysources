#pragma once
#include "afxcmn.h"
#include "DeleteConfirmDlg.h"
#include "PasswordDlg.h"
#include "CheckPasswordDlg.h"
#include "ImageProcessThread.h"
#include "afxwin.h"

#define CORRECT_PASSWORD true
#define INCORRECT_PASSWORD false

// CConfigurationDlg dialog

class CConfigurationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigurationDlg)

public:
	CConfigurationDlg(CString targetPath, CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurationDlg();

// Dialog Data
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	double choiceLevel;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCalcel();
	afx_msg void OnBnClickedRadioLow();
	afx_msg void OnBnClickedRadioMedium();
	afx_msg void OnBnClickedRadioHigh();
	double GetLevelOfDetection();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	CButton m_radioMedium;
};
