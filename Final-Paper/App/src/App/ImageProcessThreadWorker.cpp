#include "stdafx.h"
#include "ImageProcessThreadWorker.h"
#include "ImageProcessThread.h"

void ImageProcessThreadWorker::StopRequest()
{
	this->stopRequest = true;
}

void ImageProcessThreadWorker::TerminateRequest()
{
	this->isTerminate = true;
}

VOID ImageProcessThreadWorker::PushPathToQueue(CString path)
{
	paths.push(path);
}

BOOL ImageProcessThreadWorker::PopFromQueue()
{
	CString temp;
	return paths.pop(temp);
}

// Complete
BOOL ImageProcessThreadWorker::ExtractFrames(std::string path)
{
	std::string convFilePath(path);
	this->NotifyUI(NOTIFY_REQUEST_UPDATE, path);
	// '\\' -> '/' in the string(szFullFileName)
	for (int pos = 0; pos < convFilePath.length(); pos++)
	{
		if (convFilePath.at(pos) == '\\')
			convFilePath.replace(pos, 1, "/");
	}

	VideoCapture capture(convFilePath);
	if (!capture.isOpened())
		return FALSE;

	return process(capture, convFilePath);
}

// Complete
BOOL ImageProcessThreadWorker::process(VideoCapture& capture, std::string szFullFilePath)
{
	int fileNameCounter = 0;
	int numberOfFrames = capture.get(CV_CAP_PROP_FRAME_COUNT);
	int frameRate = capture.get(CV_CAP_PROP_FPS);
	int oneUnitWithMilliSecond = (int)((numberOfFrames / frameRate) * 1000) / 9/* number of frames */;

	ImageInfoForCreating* info = new ImageInfoForCreating;
	info->capture = &capture;
	info->numberOfFrames = numberOfFrames;
	info->wholeLengthOfVideo = (int)(numberOfFrames / frameRate) * 1000;
	info->oneUnit = oneUnitWithMilliSecond;
	info->orgPath = szFullFilePath;
	info->choiceLevel = this->searchLevel;

	return createImage(info);
}

int ImageProcessThreadWorker::getCount(Mat image)
{
	int count = 0;
	Mat3d temp = (Mat3d)image;
	for (int r = 0; r < temp.rows; ++r){
		for (int c = 0; c < temp.cols; ++c)
		{
			if (temp(r, c)[0] || temp(r, c)[1] || temp(r, c)[2]) count++;
		}
	}
	return count;
}

void ImageProcessThreadWorker::IsBeingCopied(CStringW pszPath)
{
	HANDLE fHandle = INVALID_HANDLE_VALUE;
	while ((fHandle = ::CreateFile(
		pszPath,					// pointer to the file name
		GENERIC_READ,		             // access (read/write) mode
		FILE_SHARE_READ						// share mode
		| FILE_SHARE_WRITE
		| FILE_SHARE_DELETE,
		NULL,                               // security descriptor
		OPEN_EXISTING,                      // how to create
		0,
		NULL)) == INVALID_HANDLE_VALUE)
		Sleep(100);                              // file with attributes to copy
	CloseHandle(fHandle);
}

void ImageProcessThreadWorker::NotifyUI(UINT uNotificationType, string path, UINT additional)
{
	if (::IsWindow(m_hWnd))
	{
		switch (uNotificationType)
		{
		case NOTIFY_REQUEST_UPDATE:
			::PostMessage(m_hWnd, WM_USER_UPDATE, 0, reinterpret_cast<LPARAM>(new string(path)));
			break;
		case NOTIFY_DIRECTORY_SEARCH_COMPLETED:
			::PostMessage(m_hWnd, WM_USER_DIRECTORY_SEARCH_COMPLETED, 0, 0);
			break;
		case NOTIFY_ONE_FILE_COMPLETED:
			::PostMessage(m_hWnd, WM_USER_ONE_FILE_COMPLETED, 0, reinterpret_cast<LPARAM>(new string(path)));
			break;
		case NOTIFY_NOTIFICATION_REQUEST_COMPLETE:
			::PostMessage(m_hWnd, WM_USER_NOTIFICATION_OCCUR, 0, reinterpret_cast<LPARAM>(new string(path)));
			break;
		case NOTIFY_SEND_NUM_OF_FILES:
			::PostMessage(m_hWnd, WM_USER_RECEIVE_NUM_OF_FILES, (WPARAM)additional, 0);
			break;
		default:
			ASSERT(0);
		}
	}
}
