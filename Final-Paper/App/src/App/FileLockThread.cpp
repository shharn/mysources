#include "stdafx.h"
#include "FileLockThread.h"

FileLockThread::FileLockThread(ImageProcessThread *pThread, std::vector<HANDLE> &fileHandles)
	:isTerminate(false)
	,m_StartStopEvent(FALSE, TRUE)
	,workingThread(pThread)
	,fileHandles(fileHandles)
{
	UpdateLocalDrives();
}

FileLockThread::~FileLockThread()
{

}

BOOL FileLockThread::MyFileLock(HANDLE fileHandle)
{
	if (LockFile(fileHandle, 0, 0, GetFileSize(fileHandle, 0), 0))
	{
		fileHandles.push_back(fileHandle);
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("Fail to lock file"));
		return FALSE;
	}
}

BOOL FileLockThread::MyFileLock()
{
	for (auto it = fileHandles.begin(); it != fileHandles.end(); it++)
		LockFile(*it, 0, 0, GetFileSize(*it, 0), 0);
	return TRUE;
}

BOOL FileLockThread::TerminateEvent()
{
	ReleaseFileLock();
	changes.Terminate();
	isTerminate = true;
	return m_StartStopEvent.SetEvent();
}

BOOL FileLockThread::ReleaseFileLock()
{
	for (auto it = fileHandles.begin(); it != fileHandles.end(); it++)
	{
		if (UnlockFile(*it, 0, 0, GetFileSize(*it, 0), 0) != 0)
			::CloseHandle(*it);
	}
	fileHandles.clear();
	return TRUE;
}

HRESULT FileLockThread::CreateThread()
{
	if ((m_hFilelock = (HANDLE)_beginthreadex(NULL, 0, StartThreadProc, static_cast<LPVOID>(this), 0, NULL)) == NULL)
		return HRESULT_FROM_WIN32(::GetLastError());

	return S_OK;
}

VOID FileLockThread::PushPathToImageProcessThread(CStringW pszPath)
{
	workingThread->PushPathToList(CStringW(pszPath));
}

VOID FileLockThread::Initialize(HANDLE hImageThread)
{
	m_hImageProcess = hImageThread;

}

void FileLockThread::UpdateLocalDrives()
{
	m_localDrives.clear();
	DWORD drives = 0;
	drives = ::GetLogicalDrives();
	UINT temp = 1;
	for (UINT i = 0; i < 26; i++)
	{
		UINT exist = drives & temp;
		temp = temp << 1;
		if (exist)
		{
			CString localDrive; localDrive.Format(_T("%c:\\"), 'A' + i);
			if (GetDriveType(localDrive) == DRIVE_FIXED)
				m_localDrives.push_back(localDrive);
		}
	}
}
VOID FileLockThread::StartWatchingLocalDrives()
{
	const DWORD dwNotificationFlags =
		FILE_NOTIFY_CHANGE_CREATION;

	DWORD drives = 0;
	drives = ::GetLogicalDrives();
	UINT temp = 1;
	
	for (UINT i = 0; i < 26; i++)
	{
		UINT exist = drives & temp;
		temp = temp << 1;
		if (exist)
		{
			BOOL isNew = true;
			CString localDrive; localDrive.Format(_T("%c:\\"), 'A' + i);
			if (GetDriveType(localDrive) == DRIVE_FIXED)
			{
				for (std::vector<CString>::iterator it = m_localDrives.begin(); it != m_localDrives.end(); it++)
				{
					if (localDrive.Compare(*it) == 0) // if identical
					{
						isNew = false;
						break;
					}
				}
				changes.AddDirectory(localDrive, TRUE, dwNotificationFlags);
				if (isNew)
					workingThread->WakeupAndSearch(localDrive);
			}
		}
	}
}
VOID FileLockThread::Run()
{
	
	StartWatchingLocalDrives();
	HANDLE waitHandles[] = { m_StartStopEvent, changes.GetWaitHandle() };
	while (!isTerminate)
	{
		DWORD rc = ::WaitForMultipleObjectsEx(_countof(waitHandles), waitHandles, FALSE, INFINITE, true);
		
		switch (rc)
		{
		case WAIT_OBJECT_0 + 0:	// Termination signal
			m_StartStopEvent.ResetEvent();
			break;
		case WAIT_OBJECT_0 + 1: // Change notification
		{
			DWORD dwAction;
			CStringW wstrFilename;
			wstrFilename.Empty();
			if (changes.CheckOverflow())
				AfxMessageBox(L"Queue overflowed.\n");
			else
			{
				changes.Pop(dwAction, wstrFilename);
				PushPathToImageProcessThread(wstrFilename);
			}
			// signal to main thread(UI) to add additional file path to list control
			break;
		}
		case WAIT_IO_COMPLETION:
			break;
		}
	}
	isTerminate = false;
}