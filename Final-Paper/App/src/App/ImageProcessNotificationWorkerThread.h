#pragma once
#include "ImageProcessThreadWorker.h"

class ImageProcessNotificationWorkerThread : public ImageProcessThreadWorker
{
public:
	ImageProcessNotificationWorkerThread();
	ImageProcessNotificationWorkerThread(HWND hWnd, CWnd *pWnd);
	~ImageProcessNotificationWorkerThread()
	{
		paths.clear();
		m_hThread = NULL;
	};
	
	LRESULT CreateThread();
	VOID Run();
	UINT Search(CString, UINT flag = 0);
private:
	
	BOOL createImage(ImageInfoForCreating* pInfo);
};

static UINT WINAPI ThreadProc(LPVOID lpContext);