#pragma once
#include "WaitDlg.h"
using namespace cv;

#define NS_FSYS std::tr2::sys::

#define SEARCH_LEVEL_UNDEF 0x111111
#define SEARCH_LEVEL_LOW 0.6
#define SEARCH_LEVEL_MEDIUM 0.5
#define SEARCH_LEVEL_HIGH 0.4

#define GET_NUMBER_OF_FILES	10000

#define NOTIFY_REQUEST_UPDATE					777
#define NOTIFY_DIRECTORY_SEARCH_COMPLETED		778
#define NOTIFY_ONE_FILE_COMPLETED				779
#define NOTIFY_NOTIFICATION_REQUEST_COMPLETE	780
#define WM_USER_TERMINATE_WAITDIALOG			781
#define NOTIFY_SEND_NUM_OF_FILES				782


typedef struct ImageInfoForCreating
{
	VideoCapture* capture;
	int numberOfFrames;
	int wholeLengthOfVideo;
	int oneUnit;
	double choiceLevel;
	UINT whoFlag;

	std::string orgPath;

	ImageInfoForCreating()
		: capture(NULL)
		, numberOfFrames(0)
		, wholeLengthOfVideo(0)
		, oneUnit(0)
		, orgPath("")
		, choiceLevel(SEARCH_LEVEL_LOW)
	{}
} ImageInfoForCreating;

class ImageProcessThreadWorker
{
public:
	ImageProcessThreadWorker();
	ImageProcessThreadWorker(HWND hWnd, CWnd *pWnd) : paths(5000)
	{
		this->m_hWnd = hWnd;
		this->m_pWnd = pWnd;
		this->isTerminate = false;
		this->stopRequest = false;
		paths.clear();
	}
	~ImageProcessThreadWorker()
	{
		CloseHandle(m_hThread);
	}
	
	virtual UINT Search(CString, UINT) = 0; // ok
	virtual VOID Run() = 0; // ok
	virtual BOOL createImage(ImageInfoForCreating* pInfo) = 0; // ok
	virtual LRESULT CreateThread() = 0; // ok

	void NotifyUI(UINT  uNotificationType, string path = "", UINT additional = 0); // ok
	BOOL ExtractFrames(std::string); // ok
	BOOL process(VideoCapture& capture, std::string szFullFilePath); // ok
	
	void IsBeingCopied(CStringW pszPath); // ok
	int getCount(Mat image); // ok 
	void StopRequest(); // ok
	void TerminateRequest(); // ok
	VOID PushPathToQueue(CString); // ok
	BOOL PopFromQueue(); // ok
	HANDLE GetSafeHandle() { return this->m_hThread; } // ok

	
protected:
	bool isTerminate;
	bool stopRequest;
	int searchLevel;
	HWND m_hWnd;
	CWnd *m_pWnd;
	CThreadSafeQueue<CString> paths;
	HANDLE m_hThread;
}; 

