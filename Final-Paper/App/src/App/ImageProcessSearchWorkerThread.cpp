#include "stdafx.h"
#include "ImageProcessSearchWorkerThread.h"

ImageProcessSearchWorkerThread::ImageProcessSearchWorkerThread(HWND hWnd, CWnd *pWnd)
	: ImageProcessThreadWorker(hWnd, pWnd)
{

}

LRESULT ImageProcessSearchWorkerThread::CreateThread()
{
	if ((m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, static_cast<LPVOID>(this), 0, NULL)) == NULL)
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}

UINT ImageProcessSearchWorkerThread::Search(CString path, UINT flag)
{
	char* targetDirStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, path.GetString(), -1, NULL, 0, NULL, NULL);
	targetDirStr = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, path.GetString(), -1, targetDirStr, strSize, 0, 0);

	// Set members about path
	UINT cnt = 0;
	NS_FSYS path TargetPath(targetDirStr);
	for (auto it = NS_FSYS recursive_directory_iterator(TargetPath); it != NS_FSYS recursive_directory_iterator() && !stopRequest; ++it)
	{
		// file object contains relative path in the case of
		// directory iterators (i.e. just file name)
		const auto& file = it->path();

		// Convert directory path with (basic_string) to (char)
		std::string orgStrPath(file.directory_string());

		if (file.extension() == ".avi" || file.extension() == ".mkv" ||
			file.extension() == ".wmv" || file.extension() == ".mp4" || file.extension() == ".mov")	// Search for video files
		{
			if (flag == GET_NUMBER_OF_FILES)
				cnt++;
			else
				ExtractFrames(orgStrPath);
		}
	}
	return cnt;
}

BOOL ImageProcessSearchWorkerThread::createImage(ImageInfoForCreating* pInfo)
{
	GrabcutHelper helper;
	bool isFound = false;
	std::string winName = "winName";
	// Set current position to oneUnit
	pInfo->capture->set(CV_CAP_PROP_POS_MSEC, pInfo->oneUnit);
	for (int unit = pInfo->oneUnit - pInfo->oneUnit / 5; unit < pInfo->wholeLengthOfVideo - pInfo->oneUnit / 5 &&
								!isTerminate && !stopRequest ; unit += pInfo->oneUnit)
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

	this->NotifyUI(NOTIFY_ONE_FILE_COMPLETED, isFound ? pInfo->orgPath : "");
	//delete capture object
	if (pInfo->capture->isOpened())
		pInfo->capture->release();
	delete pInfo;
	return 0;
}

VOID ImageProcessSearchWorkerThread::Run()
{
	while (!isTerminate)
	{
		if (!paths.empty())
		{
			CString path;
			paths.pop(path);
			UINT cnt = Search(path, GET_NUMBER_OF_FILES);
			this->NotifyUI(NOTIFY_SEND_NUM_OF_FILES, "", cnt);
			Search(path);
			this->NotifyUI(NOTIFY_DIRECTORY_SEARCH_COMPLETED, "");
		}
		Sleep(300);
	}
}

static UINT WINAPI ThreadProc(LPVOID lpContext)
{
	ImageProcessSearchWorkerThread *p = (ImageProcessSearchWorkerThread *)lpContext;
	p->Run();
	return S_OK;
}
