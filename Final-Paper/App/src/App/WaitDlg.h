#pragma once
#include "resource.h"
#include "ImageProcessNotificationWorkerThread.h"
// CWaitDlg dialog

class CWaitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWaitDlg)

public:
	CWaitDlg(CString path, ImageProcessNotificationWorkerThread *pNot, CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitDlg();

	virtual BOOL OnInitDialog();
	HRESULT CreateThread();
	CString m_cstrPath;
	void TerminateDlg();
	void Run();
	virtual void OnOK();
	virtual void OnCancel();
	void IsBeingCopied(CStringW pszPath); // ok
	ImageProcessNotificationWorkerThread *pNot;

// Dialog Data
	enum { IDD = IDD_DIALOG_WAITING };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
	HANDLE m_hThread;
	CWnd *m_pWnd;

private:
	void TerminateRequest();
	bool isTerminate;
	
};

static UINT WINAPI WaitThreadProc(LPVOID lpContext);