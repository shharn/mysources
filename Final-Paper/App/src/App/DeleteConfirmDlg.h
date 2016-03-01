#pragma once


// DeleteConfirmDlg dialog

class DeleteConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteConfirmDlg)

public:
	DeleteConfirmDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DeleteConfirmDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DELCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
	bool GetDelConfirm();
	void SetDelConfirm(bool);

private:
	bool delConfirm;
};
