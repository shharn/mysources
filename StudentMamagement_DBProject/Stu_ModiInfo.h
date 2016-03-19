#pragma once


// Stu_ModiInfo dialog

class Stu_ModiInfo : public CDialogEx
{
	DECLARE_DYNAMIC(Stu_ModiInfo)

public:
	Stu_ModiInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~Stu_ModiInfo();

// Dialog Data
	enum { IDD = IDD_MODIINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_ID;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void SetmID(int m_SID);
	
	int m_Password;
	CString m_Phone;
	CString m_Address;
};
