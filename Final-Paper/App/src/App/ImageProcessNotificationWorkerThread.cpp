#include "stdafx.h"
#include "ImageProcessNotificationWorkerThread.h"

ImageProcessNotificationWorkerThread::ImageProcessNotificationWorkerThread(HWND hWnd, CWnd *pWnd)
			: ImageProcessThreadWorker(hWnd, pWnd)
{

}

LRESULT ImageProcessNotificationWorkerThread::CreateThread()
{
	if ((m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, static_cast<LPVOID>(this), 0, NULL)) == NULL)
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}

UINT ImageProcessNotificationWorkerThread::Search(CString path, UINT flag)
{
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(path);
	// construct a std::string using the LPCSTR input
	std::string strPath(pszConvertedAnsiString);

	return ExtractFrames(strPath);
}

BOOL ImageProcessNotificationWorkerThread::createImage(ImageInfoForCreating* pInfo)
{
	GrabcutHelper helper;
	bool isFound = false;
	std::string winName = "winName";
	// Set current position to oneUnit
	pInfo->capture->set(CV_CAP_PROP_POS_MSEC, pInfo->oneUnit);
	for (int unit = pInfo->oneUnit - pInfo->oneUnit / 5; unit < pInfo->wholeLengthOfVideo - pInfo->oneUnit / 5 && 
															!isTerminate  && !stopRequest; unit += pInfo->oneUnit)
	{
		// get the frame
		pInfo->capture->set(CV_CAP_PROP_POS_MSEC, unit);
		Mat frame;
		(*pInfo->capture) >> frame;
		if (frame.empty())	// frame check if properly get
			continue;


		helper.setImage(frame, winName);
		helper.setRect();

		int iterCount = helper.getIterCount();
		int newIterCount = helper.doGrabcut();
		if (newIterCount > iterCount)
			helper.setTransformedImage();
		else
			cout << "rect must be determined>" << endl;

		Mat tempImage = helper.getConvertedImage();
		int totalCount = getCount(tempImage);

		Mat skin = GetSkin(tempImage);
		int skinCount = getCount(skin);

		double skinRatio = (double)((double)skinCount / (double)totalCount);

		if (skinRatio >= pInfo->choiceLevel)
		{
			isFound = true;
			break;
		}
	}

	this->NotifyUI(NOTIFY_NOTIFICATION_REQUEST_COMPLETE, isFound ? pInfo->orgPath : "");
	//delete capture object
	if (pInfo->capture->isOpened())
		pInfo->capture->release();
	delete pInfo;
	return 0;
}

VOID ImageProcessNotificationWorkerThread::Run()
{
	while (!isTerminate)
	{
		if (!paths.empty())
		{
			CString path;
			paths.pop(path);
			this->NotifyUI(NOTIFY_SEND_NUM_OF_FILES, "", 1);
			CWaitDlg dlg(path, this, m_pWnd);
			dlg.DoModal();
			Search(path);
			this->NotifyUI(NOTIFY_ONE_FILE_COMPLETED, "");
		}
		Sleep(100);
	}
}

static UINT WINAPI ThreadProc(LPVOID lpContext)
{
	ImageProcessNotificationWorkerThread *p = (ImageProcessNotificationWorkerThread *)lpContext;
	p->Run();
	return 0;
}