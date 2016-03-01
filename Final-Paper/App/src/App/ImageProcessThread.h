#pragma once
#define SEARCH_LEVEL_UNDEF 0x111111
#define SEARCH_LEVEL_LOW 0.6
#define SEARCH_LEVEL_MEDIUM 0.5
#define SEARCH_LEVEL_HIGH 0.4

#define DIRECTORY_SEARCH	10000
#define NOTIFICATION_SEARCH	10001

class ImageProcessNotificationWorkerThread;
class ImageProcessSearchWorkerThread;
class ImageProcessThread
{
public:
	ImageProcessThread(UINT nMaxCount = 1000);
	~ImageProcessThread();
	void PrePareWorker(HWND hWnd, CWnd *);
	void WakeupAndSearch(double choicelevel, CString dirPath);
	void WakeupAndSearch(CString dirPath);
	HRESULT ShutdownThread();
	HRESULT CreateThread();
	HANDLE GetSafeThreadHandle(){ return this->m_hThread; }
	void PushPathToList(CStringW& pszPath);
	BOOL PopPath(CStringW& pszPath);
	void Run();
	void StopRequest(UINT flag);

protected:
	HANDLE m_hThread;
	HANDLE m_hShutdownEvent;
	
private:
	CEvent m_StartSearching;
	HWND m_hWnd;
	CString m_cstrTargetPath;
	double choiceLevel;
	bool isTerminate;
	bool stopRequest;
	CThreadSafeQueue<CStringW> fileList;
	CWnd *m_pWnd;

	ImageProcessNotificationWorkerThread *pNotification;
	ImageProcessSearchWorkerThread *pDirectory;
	
};

static UINT WINAPI ThreadProc(LPVOID lpContext);