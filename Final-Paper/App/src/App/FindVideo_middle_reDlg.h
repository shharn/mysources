
// FindVideo_middle_reDlg.h : header file
//

#pragma once
#include <SetupAPI.h>
#include <Dbt.h>
#include "ConfigurationDlg.h"
#include "FileLockThread.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ioctl.h"

#define DIRECTORY_SEARCH	10000
#define NOTIFICATION_SEARCH	10001

#define TERMINATE_PROCESS		0x00000001
#define JUST_STOP_MONITORING	0x00000002
#define RESTART_PROCESS			0x00000004

#define PROGRAM_NAME			L"avs"
#define CMDLINE_RESTART_PROCESS L"--Restart"

// CFindVideo_middle_reDlg dialog
class CFindVideo_middle_reDlg : public CDialogEx
{
// Construction
public:
	CFindVideo_middle_reDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FINDVIDEO_MIDDLE_RE_DIALOG };

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
	// Path to start searching
	CString m_strTargetPath;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonTarget();
	afx_msg void OnBnClickedLock();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSearch();
	
	
private:
	BOOL isLocked;
	BOOL isSearching;
	double levelOfDetection;
	double choiceLevel;
	CString password;

	CProgressCtrl m_pgctrlNumOfFiles;
	CStatic m_staticStatus;
	CListCtrl m_listCtrlPaths;

	PasswordDlg pswdDlg;
	CheckPasswordDlg checkDlg;
	ImageProcessThread wThread; // wait
	FileLockThread fThread; // wait
	
	std::vector<HANDLE> fileHandles;
	std::vector<CString> filePaths;
	
	SP_CLASSIMAGELIST_DATA m_imgList;
	HDEVNOTIFY hDevNotify;
	char FirstDriveFromMask(ULONG unitMask);

	void InitializeSettings();
	BOOL InitializeDetectDevice();
	void InitializeFileHandles();
	LRESULT OnUpdateUI(WPARAM, LPARAM lParam);
	LRESULT OnThreadCompleted(WPARAM, LPARAM);
	LRESULT OnOneFileCompleted(WPARAM, LPARAM);
	LRESULT OnNotificationOccured(WPARAM, LPARAM);
	LRESULT OnDeviceChangeHandler(WPARAM wParam, LPARAM lParam);
	LRESULT OnInitSlideControl(WPARAM wParam, LPARAM);
	LRESULT OnReceiveNumOfFiles(WPARAM wParam, LPARAM);
	BOOL CheckPassword();
	void GoToTrayIcon();
	void RestartProcess();
	void TerminateProcess(UINT flag = TERMINATE_PROCESS);
	void UpdateUIAndDataAfterDeviceRemoved();
public:
	afx_msg void OnClose();
protected:
	afx_msg LRESULT OnUserTrayNotification(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMenuExit();
	afx_msg void OnMenuLock();
	virtual void OnCancel();
	virtual void OnOK();
};

// Copy from HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
static const GUID GUID_DEVINTERFACE_LIST[] =
{
	// GUID_DEVINTERFACE_USB_DEVICE
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

	// GUID_DEVINTERFACE_DISK
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },

	// GUID_DEVINTERFACE_HID, 
	{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },

	// GUID_NDIS_LAN_CLASS
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

	//// GUID_DEVINTERFACE_COMPORT
	//{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },

	//// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
	//{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },

	//// GUID_DEVINTERFACE_PARALLEL
	//{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },

	//// GUID_DEVINTERFACE_PARCLASS
	//{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};
