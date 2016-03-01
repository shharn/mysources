#pragma once
#include "ImageProcessThreadWorker.h"

class ImageProcessSearchWorkerThread : public ImageProcessThreadWorker
{
public:
	ImageProcessSearchWorkerThread();
	ImageProcessSearchWorkerThread(HWND hWnd, CWnd *pWnd);
	~ImageProcessSearchWorkerThread()
	{
		paths.clear();
		m_hThread = NULL;
	};

	LRESULT CreateThread();
	VOID Run();
private:
	BOOL createImage(ImageInfoForCreating* pInfo);
	virtual UINT Search(CString, UINT flag = 0);
};

static UINT WINAPI ThreadProc(LPVOID lpContext);