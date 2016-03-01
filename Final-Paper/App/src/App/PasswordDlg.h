#pragma once
// PasswordDlg dialog

class PasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PasswordDlg)

public:
	PasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PasswordDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	// User-defined password
	CString m_csPassword;
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
