#pragma once


// CheckPasswordDlg dialog

class CheckPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CheckPasswordDlg)

public:
	CheckPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CheckPasswordDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ANSPSWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_csInputPassword;
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonCancel();
	bool GetCorrectIncorrect();

private:
	bool isCorrect;

};
