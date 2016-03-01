#pragma once
#include "ImageProcessThread.h"

class FileLockThread{
public:
	FileLockThread(ImageProcessThread*, std::vector<HANDLE> &);
	~FileLockThread();
	HRESULT CreateThread();
	BOOL MyFileLock(HANDLE);
	BOOL MyFileLock();
	BOOL ReleaseFileLock();
	DWORD GetSizeOfHandles(){ return fileHandles.size(); }
	HANDLE GetLockThreadHandle(){ return m_hFilelock; }
	BOOL TerminateEvent();
	VOID PushPathToImageProcessThread(CStringW pszPath);
	VOID Initialize(HANDLE);
	VOID StartWatchingLocalDrives();
	VOID Run();
	void UpdateLocalDrives();
	static UINT WINAPI StartThreadProc(LPVOID lpContext)
	{
		FileLockThread* pwThread = reinterpret_cast<FileLockThread*>(lpContext);
		pwThread->Run();
		return 0;
	}

private:
	std::vector<HANDLE> &fileHandles;
	std::vector<CString> m_localDrives;
	ImageProcessThread* workingThread;
	CReadDirectoryChanges changes;
	HANDLE m_hFilelock;
	HANDLE m_hImageProcess;
	bool isTerminate;
	CEvent m_StartStopEvent;
};