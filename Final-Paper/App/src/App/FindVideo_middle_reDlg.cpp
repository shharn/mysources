
// FindVideo_middle_reDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindVideo_middle_re.h"
#include "FindVideo_middle_reDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClose();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFindVideo_middle_reDlg dialog



CFindVideo_middle_reDlg::CFindVideo_middle_reDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindVideo_middle_reDlg::IDD, pParent)
	, m_strTargetPath(_T(""))
	, levelOfDetection(SEARCH_LEVEL_MEDIUM)
	, isSearching(false)
	, fThread(&wThread, fileHandles)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFindVideo_middle_reDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_strTargetPath);
	DDX_Control(pDX, LIST_PATHS, m_listCtrlPaths);
	DDX_Control(pDX, PROGBAR_NUMOFFILES, m_pgctrlNumOfFiles);
	DDX_Control(pDX, STATIC_LIGHTPIC, m_staticStatus);
}

BEGIN_MESSAGE_MAP(CFindVideo_middle_reDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_EXIT, &CFindVideo_middle_reDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(BUTTON_CONFIG, &CFindVideo_middle_reDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(BUTTON_TARGET, &CFindVideo_middle_reDlg::OnBnClickedButtonTarget)
	ON_BN_CLICKED(BUTTON_LOCK, &CFindVideo_middle_reDlg::OnBnClickedLock)
	ON_BN_CLICKED(BUTTON_DELETE, &CFindVideo_middle_reDlg::OnBnClickedDelete)
	ON_BN_CLICKED(BUTTON_SEARCH, &CFindVideo_middle_reDlg::OnBnClickedSearch)

	// for thread communicatons
	ON_MESSAGE(WM_USER_UPDATE, &CFindVideo_middle_reDlg::OnUpdateUI)
	ON_MESSAGE(WM_USER_DIRECTORY_SEARCH_COMPLETED, &CFindVideo_middle_reDlg::OnThreadCompleted)
	ON_MESSAGE(WM_USER_ONE_FILE_COMPLETED, &CFindVideo_middle_reDlg::OnOneFileCompleted)
	ON_MESSAGE(WM_USER_NOTIFICATION_OCCUR, &CFindVideo_middle_reDlg::OnNotificationOccured)
	ON_MESSAGE(WM_DEVICECHANGE, &CFindVideo_middle_reDlg::OnDeviceChangeHandler)
	ON_MESSAGE(WM_USER_TRAY_NOTIFICATION, &CFindVideo_middle_reDlg::OnUserTrayNotification)
	ON_COMMAND(ID_MENU_EXIT, &CFindVideo_middle_reDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_LOCK, &CFindVideo_middle_reDlg::OnMenuLock)
	ON_MESSAGE(WM_USER_RECEIVE_NUM_OF_FILES, &CFindVideo_middle_reDlg::OnReceiveNumOfFiles)
END_MESSAGE_MAP()


// CFindVideo_middle_reDlg message handlers

BOOL CFindVideo_middle_reDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_listCtrlPaths.InsertColumn(0, _T("Path"), LVCFMT_LEFT, 350);
	m_pgctrlNumOfFiles.SetStep(1);

	// Some kind of initilizing
	// if locked, get file names from registry
	// and button names & status icon setting(lock<->Unlock, On monitoring <-> Not monitoring)
	// Set value to see if locked
	
	fThread.Initialize(wThread.GetSafeThreadHandle());
	wThread.PrePareWorker(GetSafeHwnd(), this);
	InitializeSettings();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFindVideo_middle_reDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	// if the esc key is pressed, minimize & go to tray icon
	else if ((nID & 0xFFF0) == SC_CLOSE)
	{
		GoToTrayIcon();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFindVideo_middle_reDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFindVideo_middle_reDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFindVideo_middle_reDlg::InitializeSettings()
{
	// Get the configuration information from the registry hive
	GlobalFunction::GetConfigurationInfo(isLocked, filePaths, password);
	if (isLocked == true)
	{
		// Change button text to "Unlock"
		SetDlgItemText(BUTTON_LOCK, _T("Unlock"));

		// Create a thread for file lock
		fThread.CreateThread();

		// Initialize the settings for Device Notification
		InitializeDetectDevice();

		// Get handle and lock the file & add the paths to ListCtrl
		HANDLE handle = INVALID_HANDLE_VALUE;
		for (CString member : filePaths)
		{
			handle = ::CreateFile(member, GENERIC_READ, NULL, NULL,
				OPEN_EXISTING, 0, NULL);
			if (handle == INVALID_HANDLE_VALUE)
				continue;
			m_listCtrlPaths.InsertItem(LVIF_TEXT, member);
			fThread.MyFileLock(handle);
		}
	}
}

void CFindVideo_middle_reDlg::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	if (isLocked == true)
	{
		if (checkDlg.DoModal())
		{
			if (checkDlg.GetCorrectIncorrect())
			{
				TcRemoveProtection();
				TcUninstallDriver();
				fThread.TerminateEvent();
				wThread.ShutdownThread();
				TerminateProcess();
			}
		}
	}
	else
	{
		fThread.TerminateEvent();
		wThread.ShutdownThread();
		TerminateProcess();
	}
}

// Complete
void CFindVideo_middle_reDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	if (m_strTargetPath != "")
	{
		CConfigurationDlg dlg(m_strTargetPath);
		if (dlg.DoModal() == IDOK)
			levelOfDetection = dlg.GetLevelOfDetection();
	}
	else
		AfxMessageBox(_T("Specify target path"));
}

// Complete
void CFindVideo_middle_reDlg::OnBnClickedButtonTarget()
{
	// TODO: Add your control notification handler code here
	CFolderPickerDialog dlgFolder;
	if (dlgFolder.DoModal() == IDOK)
	{
		m_strTargetPath = dlgFolder.GetFolderPath();
	}
	UpdateData(FALSE);
}

BOOL CFindVideo_middle_reDlg::InitializeDetectDevice()
{
	ZeroMemory(&m_imgList, sizeof(SP_CLASSIMAGELIST_DATA));
	m_imgList.cbSize = sizeof(SP_CLASSIMAGELIST_DATA);
	BOOL b = ::SetupDiGetClassImageList(&m_imgList);
	ASSERT(b);

	
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	for (int i = 0; i<sizeof(GUID_DEVINTERFACE_LIST) / sizeof(GUID); i++) {
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
		hDevNotify = ::RegisterDeviceNotification(this->GetSafeHwnd(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
		if (!hDevNotify) {
			AfxMessageBox(CString("Can't register device notification: ")
				+ _com_error(GetLastError()).ErrorMessage(), MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	return TRUE;
}

void CFindVideo_middle_reDlg::OnBnClickedLock()
{
	// TODO: Add your control notification handler code here
	bool correctPswd = false;
	if (isLocked)
	{
		if (checkDlg.DoModal() == IDOK)
			correctPswd = checkDlg.GetCorrectIncorrect();

		if (correctPswd == CORRECT_PASSWORD)
		{
			// deprotect avs.exe & uninstall driver
			TcRemoveProtection();
			TcUninstallDriver();

			// Stop monitoring
			TerminateProcess(JUST_STOP_MONITORING);
		}
		else
			AfxMessageBox(_T("Incorrect Password"));
	}
	else
	{
		if (pswdDlg.DoModal() == IDOK)
		{
			// save the current data to registry
			// later, so we can use it in restarted program
			isLocked = true;

			// Write 'isLocked' registry key to hive
			if (!GlobalFunction::WriteToRegistryDW(1))
				AfxMessageBox(_T("Writing the DWORD to registry failed!"));

			DWORD numberOfItems = m_listCtrlPaths.GetItemCount();
			for (DWORD i = 0; i < numberOfItems; i++)
			{
				CString itemText = m_listCtrlPaths.GetItemText(i, 0);
				itemText.Replace(_T("/"), _T("\\"));
				
				// Write 'Paths' registry key to hive
				CString key;
				key.Format(_T("File%02d"), i);
				if (!GlobalFunction::WriteToRigestrySZ(FILE_LIST_PATH, key, itemText))
					AfxMessageBox(_T("Wrting the SZ to registry failed!"));

			}

			// driver installing tasks
			// Install & Load driver
			if (!TcInitialize()){
				AfxMessageBox(L"Initialization failed - program exiting");
				TerminateProcess(TERMINATE_PROCESS);
			}
			else
			{
				// Install driver & protect avs.exe from being terminated
				TcInstallDriver();
				TcProcessName(PROGRAM_NAME, TDProtectName_Protect);

				// Restart Program
				RestartProcess();
			}
		}
		else
			AfxMessageBox(_T("Fail to open password dialog"));
	}
}

void CFindVideo_middle_reDlg::RestartProcess()
{
	
	TCHAR szAppPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szAppPath, MAX_PATH);

	STARTUPINFO				si = { 0 };
	PROCESS_INFORMATION		pi = { 0 };
	si.cb = sizeof(STARTUPINFO);
	// Create New Instance command line
	::PathQuoteSpaces(szAppPath);
	::lstrcat(szAppPath, _T(" "));
	::lstrcat(szAppPath, CMDLINE_RESTART_PROCESS); // Add command line key for restart
	// Create another copy of process
	::CreateProcess(NULL, szAppPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	TerminateProcess(RESTART_PROCESS);
}

void CFindVideo_middle_reDlg::TerminateProcess(UINT flag)
{
	// need to delete registries
	if (flag != RESTART_PROCESS)
		GlobalFunction::DeleteConfiguration(DELETE_ALL);

	// Stop monitoring directory changes
	fThread.TerminateEvent();
	
	// Halt the external device notification
	SetupDiDestroyClassImageList(&m_imgList);
	UnregisterDeviceNotification(hDevNotify);

	filePaths.clear();
	fileHandles.clear();
	isLocked = false;

	if (flag != JUST_STOP_MONITORING)
	{
		wThread.ShutdownThread();
		DestroyWindow();
	}
	else
		SetDlgItemText(BUTTON_LOCK, _T("Lock"));
}

void CFindVideo_middle_reDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	if (isLocked == true)
		AfxMessageBox(_T("First, Unlock the program"));
	else
	{
		// delete the file path in the list & in the registry and unlock the file(UnlockFile())
		POSITION pos = m_listCtrlPaths.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			TRACE(_T("No items were selected!\n"));
		}
		else
		{
			while (pos)
			{
				// get position of selected item & delete it from the list
				int nItem = m_listCtrlPaths.GetNextSelectedItem(pos);
				m_listCtrlPaths.DeleteItem(nItem);
			}
		}
	}
}

// Complete
LRESULT CFindVideo_middle_reDlg::OnUpdateUI(WPARAM, LPARAM lParam)
{
	std::string *msg = reinterpret_cast<string*>(lParam);
	CString detectedPath(msg->c_str());
	SetDlgItemText(STATIC_CURRPATH, detectedPath);
	delete msg;
	return S_OK;
}

LRESULT CFindVideo_middle_reDlg::OnDeviceChangeHandler(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	if (isLocked)
	{
		if (wParam == DBT_DEVICEARRIVAL)
		{
			Sleep(300);
			fThread.TerminateEvent();
			Sleep(200);
			fThread.CreateThread();
		}
		else if (wParam == DBT_DEVICEREMOVECOMPLETE)
		{
			AfxMessageBox(_T("Enter OnDeviceChangeHandler after usb removed"));
			Sleep(300);
			fThread.UpdateLocalDrives();
			fThread.TerminateEvent();
			Sleep(200);
			fThread.CreateThread();

			// update UI & file list
			UpdateUIAndDataAfterDeviceRemoved();
		}
	}
	return S_OK;
}

void CFindVideo_middle_reDlg::UpdateUIAndDataAfterDeviceRemoved()
{
	filePaths.clear();
	fileHandles.clear();
	GlobalFunction::DeleteConfiguration(DELETE_ONLY_PATHS);
	DWORD numberOfItems = m_listCtrlPaths.GetItemCount();
	UINT count = 0;
	for (DWORD i = 0; i < numberOfItems; i++)
	{
		CString itemText = m_listCtrlPaths.GetItemText(i, 0);
		itemText.Replace(_T("/"), _T("\\"));

		HANDLE handle = ::CreateFile(itemText, GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, 0, NULL);
		if (handle == INVALID_HANDLE_VALUE)
			continue;

		fThread.MyFileLock(handle);
		filePaths.push_back(itemText);

		// Write 'Paths' registry key to hive
		CString key;
		key.Format(_T("File%02d"), i);
		if (!GlobalFunction::WriteToRigestrySZ(FILE_LIST_PATH, key, itemText))
			AfxMessageBox(_T("Wrting the SZ to registry failed!"));
		count++;
	}

	m_listCtrlPaths.DeleteAllItems();
	for (CString member : filePaths)
	{
		member.Replace(_T("\\"), _T("/"));
		m_listCtrlPaths.InsertItem(LVIF_TEXT, member);
	}
}

char CFindVideo_middle_reDlg::FirstDriveFromMask(ULONG unitmask)
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return 'A' + i;
}
// Complete
LRESULT CFindVideo_middle_reDlg::OnThreadCompleted(WPARAM, LPARAM)
{
	isSearching = false;
	((CButton*)GetDlgItem(BUTTON_SEARCH))->EnableWindow(TRUE);
	SetDlgItemText(STATIC_CURRPATH, _T("Complete!"));
	SetDlgItemText(BUTTON_SEARCH, _T("Search"));
	FlashWindowEx(FLASHW_ALL, 5, 0);
	
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NIF_INFO;
	nid.dwInfoFlags = NIIF_INFO;
	nid.uTimeout = 5000;
	lstrcpy(nid.szInfoTitle, _T("Search completed!!"));
	lstrcpy(nid.szInfo, _T("Check the file list\nThere may be wrong files"));

	BOOL bRet = ::Shell_NotifyIcon(NIM_MODIFY, &nid);
	return S_OK;
}

// Complete
LRESULT CFindVideo_middle_reDlg::OnOneFileCompleted(WPARAM, LPARAM lParam)
{
	m_pgctrlNumOfFiles.StepIt();
	Sleep(300);
	std::string *msg = reinterpret_cast<string*>(lParam);
	if(!msg->empty())
	{
		CString changedDirec(msg->c_str());
		changedDirec.Replace(_T("/"), _T("\\"));
		if (isLocked)
		{
			HANDLE handle = ::CreateFile(changedDirec, GENERIC_READ, NULL, NULL,
				OPEN_EXISTING, 0, NULL);
			if (handle == INVALID_HANDLE_VALUE)
			{
				CString errorStr;
				errorStr.Format(_T("Error during opening the file : %s, code : %d"), changedDirec, GetLastError());
				AfxMessageBox(errorStr);
			}
			fThread.MyFileLock(handle);

			// Write 'Paths' registry key to hive
			DWORD numberOfItems = m_listCtrlPaths.GetItemCount();
			CString key;
			key.Format(_T("File%02d"), numberOfItems);
			if (!GlobalFunction::WriteToRigestrySZ(FILE_LIST_PATH, key, changedDirec))
				AfxMessageBox(_T("Wrting the SZ to registry failed!"));
		}
		m_listCtrlPaths.InsertItem(LVIF_TEXT, changedDirec);
	}
	delete msg;
	return S_OK;
}

LRESULT CFindVideo_middle_reDlg::OnNotificationOccured(WPARAM, LPARAM lParam)
{
	SetDlgItemText(STATIC_CURRPATH, _T("Complete!"));
	std::string *msg = reinterpret_cast<string*>(lParam);
	CString changedDirec(msg->c_str());
	changedDirec.Replace(_T("/"), _T("\\"));
	m_listCtrlPaths.InsertItem(LVIF_TEXT, changedDirec);
	Sleep(300);		// Wait for release file handle
	HANDLE hFile = ::CreateFile(changedDirec, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		UINT dwError = GetLastError();
		AfxMessageBox(_T("Error during opening the file"));
		return S_FALSE;
	}

	DWORD numOfItem = m_listCtrlPaths.GetItemCount() - 1;
	CString key;
	key.Format(_T("File%02d"),numOfItem);
	GlobalFunction::WriteToRigestrySZ(FILE_LIST_PATH, key, changedDirec);

	fThread.MyFileLock(hFile);
	FlashWindowEx(FLASHW_ALL, 5, 0);

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NIF_INFO;
	nid.dwInfoFlags = NIIF_INFO;
	nid.uTimeout = 5000;
	lstrcpy(nid.szInfoTitle, _T("19 video file found under monitoring"));
	lstrcpy(nid.szInfo, _T("I'm professional, right?? :)"));
	//nid.uCallbackMessage = WM_USER_TRAY_NOTIFICATION;

	BOOL bRet = ::Shell_NotifyIcon(NIM_MODIFY, &nid);
	delete msg;
	return S_OK;
}

LRESULT CFindVideo_middle_reDlg::OnInitSlideControl(WPARAM wParam, LPARAM)
{
	short numberOfFiles = (short)wParam;
	m_pgctrlNumOfFiles.SetRange(0, numberOfFiles);
	m_pgctrlNumOfFiles.SetPos(0);
	return S_OK;
}

void CFindVideo_middle_reDlg::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
	if (!isSearching)
	{
		if (m_strTargetPath.IsEmpty())
		{
			AfxMessageBox(_T("Must Configure the option"));
			return;
		}
		isSearching = true;
		SetDlgItemText(BUTTON_SEARCH, _T("Stop"));
		wThread.WakeupAndSearch(levelOfDetection, m_strTargetPath);
	}
	else
	{
		wThread.StopRequest(DIRECTORY_SEARCH);
		SetDlgItemText(BUTTON_SEARCH, _T("Search"));
		SetDlgItemText(STATIC_CURRPATH, _T("Stopped."));
		m_pgctrlNumOfFiles.SetPos(0);
		isSearching = false;
	}
}

void CFindVideo_middle_reDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	bool correctPswd = false;
	if (isLocked)
	{
		if (checkDlg.DoModal() == IDOK)
			correctPswd = checkDlg.GetCorrectIncorrect();

		if (correctPswd == CORRECT_PASSWORD)
		{
			// deprotect avs.exe & uninstall driver
			TcRemoveProtection();
			TcUninstallDriver();
			TerminateProcess(TERMINATE_PROCESS);
		}
		else
			AfxMessageBox(_T("Incorrect Password"));
	}
	else
		CDialogEx::OnClose();
	
}

BOOL CFindVideo_middle_reDlg::CheckPassword()
{
	bool correctPswd = false;
	if (checkDlg.DoModal() == IDOK)
		correctPswd = checkDlg.GetCorrectIncorrect();
	return correctPswd;
}

afx_msg LRESULT CFindVideo_middle_reDlg::OnUserTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_TRAY);
		CMenu *pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			ptMouse.x, ptMouse.y, AfxGetMainWnd());
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		NOTIFYICONDATA nid;
		ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(nid);
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();

		BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid);
		if (!bRet)
		{
			AfxMessageBox(_T("Fail to delete tray icon"));
			return -1;
		}
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
		break;
	}
	}
	return 0;
}

LRESULT CFindVideo_middle_reDlg::OnReceiveNumOfFiles(WPARAM wParam, LPARAM)
{
	int numOfFiles = (int)wParam;
	m_pgctrlNumOfFiles.SetRange(0, numOfFiles);
	m_pgctrlNumOfFiles.SetPos(0);
	return S_OK;
}

void CFindVideo_middle_reDlg::OnMenuExit()
{
	// TODO: Add your command handler code here
	bool correctPswd = false;
	if (isLocked)
	{
		if (checkDlg.DoModal() == IDOK)
			correctPswd = checkDlg.GetCorrectIncorrect();

		if (correctPswd == CORRECT_PASSWORD)
		{
			// deprotect avs.exe & uninstall driver
			TcRemoveProtection();
			TcUninstallDriver();
			TerminateProcess(TERMINATE_PROCESS);
		}
		else
			AfxMessageBox(_T("Incorrect Password"));
	}
}


void CFindVideo_middle_reDlg::OnMenuLock()
{
	// TODO: Add your command handler code here
	OnBnClickedLock();
}


void CFindVideo_middle_reDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	GoToTrayIcon();
}


void CFindVideo_middle_reDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
}

void CFindVideo_middle_reDlg::GoToTrayIcon()
{
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	DWORD result = GetLastError();
	nid.cbSize = sizeof(nid);
	
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	lstrcpy(nid.szTip, _T("I've been monitoring..hhh"));
	nid.uCallbackMessage = WM_USER_TRAY_NOTIFICATION;

	BOOL bRet = ::Shell_NotifyIcon(NIM_ADD, &nid);
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
}
