#include "stdafx.h"
#include "ImageProcessThread.h"
#include "ImageProcessNotificationWorkerThread.h"
#include "ImageProcessSearchWorkerThread.h"

ImageProcessThread::ImageProcessThread(UINT nMaxCount)
	: m_hThread(NULL)
	, m_hShutdownEvent(::CreateEvent(NULL, TRUE, FALSE, NULL))
	, choiceLevel(SEARCH_LEVEL_MEDIUM)
	, isTerminate(false)
	, fileList(nMaxCount)
	, stopRequest(false)
	, m_StartSearching(FALSE, TRUE)
{
	
}

ImageProcessThread::~ImageProcessThread()
{
	// WaitForSingleObject(m_hThread, 10000);
	::CloseHandle(m_hThread);
	delete pNotification;
	delete pDirectory;
}

void ImageProcessThread::StopRequest(UINT flag)
{
	if (flag == DIRECTORY_SEARCH)
		pDirectory->StopRequest();
	else if (flag == NOTIFICATION_SEARCH)
		pNotification->StopRequest();
}
// Complete
void ImageProcessThread::PrePareWorker(HWND hWnd, CWnd *pWnd)
{
	HRESULT hr = S_OK;
	m_hWnd = hWnd;
	m_pWnd = pWnd;
	pNotification = new ImageProcessNotificationWorkerThread(m_hWnd, m_pWnd);
	pDirectory = new ImageProcessSearchWorkerThread(m_hWnd, m_pWnd);
	hr = CreateThread();
}

void ImageProcessThread::WakeupAndSearch(double choicelevel, CString dirPath)
{
	this->choiceLevel = choicelevel;
	this->m_cstrTargetPath = dirPath;
	m_StartSearching.SetEvent();
}

void ImageProcessThread::WakeupAndSearch(CString devPath)
{
	this->m_cstrTargetPath = devPath;
	m_StartSearching.SetEvent();
}

HRESULT ImageProcessThread::ShutdownThread()
{
	isTerminate = true;
	return S_OK;
}

// Complete
HRESULT ImageProcessThread::CreateThread()
{
	if ((m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, static_cast<LPVOID>(this), 0, NULL)) == NULL)
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}

static UINT WINAPI ThreadProc(LPVOID lpContext)
{
	ImageProcessThread* pwThread = reinterpret_cast<ImageProcessThread*>(lpContext);
	pwThread->Run();
	return 0;
}

void ImageProcessThread::PushPathToList(CStringW& pszPath)
{
	fileList.push(pszPath);
}

BOOL ImageProcessThread::PopPath(CStringW& pszPath)
{
	return fileList.pop(pszPath);
}

// Wait for the signal from the ThreadSafeQueue<CString> object(Semaphore) 
// -> This will be activated when the directory change notifications occur
void ImageProcessThread::Run()
{
	pNotification->CreateThread();
	pDirectory->CreateThread();

	while (!isTerminate)
	{
		HANDLE handles[] = { fileList.GetWaitHandle(), m_StartSearching };
		DWORD state = ::WaitForMultipleObjectsEx(_countof(handles), handles, FALSE, INFINITE, true);
		switch (state){
			// need to create new thread : only infinite loop for waiting notification
		case WAIT_OBJECT_0 + 0:
		{
			// add the notification file path to notification worker thread queue
			CString tmpPath;
			PopPath(tmpPath);
			pNotification->PushPathToQueue(tmpPath);
			break;
		}
		case WAIT_OBJECT_0 + 1:
			// add the searching worker queue to thie directory path
			pDirectory->PushPathToQueue(this->m_cstrTargetPath);
			m_StartSearching.ResetEvent();
			break;
		default:
			break;
		}
	}
	pNotification->TerminateRequest();
	pDirectory->TerminateRequest();
	WaitForSingleObject(pNotification->GetSafeHandle(), INFINITE);
	WaitForSingleObject(pDirectory->GetSafeHandle(), INFINITE);
}