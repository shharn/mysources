#include "stdafx.h"
#include "sha1.h"
#define REGISTRY_PATH		_T("SOFTWARE\\VideoLock")
#define FILE_LIST_PATH		_T("SOFTWARE\\VideoLock\\Paths")
#define ISLOCKED_KEY		_T("isLocked")
#define PASSWORD_KEY		_T("Password")
#define NOTHING				-100000
#define MAX_KEY_LENGTH		255
#define MAX_VALUE_NAME		16383
#define DELETE_ALL			5000
#define DELETE_ONLY_PATHS	5001

class GlobalFunction{
public:
	//PVOID GetHashedValue();
	static BOOL WriteToRigestrySZ(LPCTSTR path, CString keyName, CString value);
	static BOOL WriteToRegistryDW(UINT dwData);
	static BOOL GetConfigurationInfo(BOOL&/*isLocked*/, std::vector<CString>& /*file list*/, CString& /*hased password*/);
	static BOOL GetConfigurationIslocked(BOOL &isLocked);
	static BOOL GetConfigurationFileList(std::vector<CString> &list);
	static BOOL GetConfigurationPassword(CString &password);
	static void QueryAndEnumerateKey(HKEY hKey, std::vector<CString>& list/*file list*/);
	static BOOL DeleteConfiguration(UINT flag);
	static void GetHashedValueFromPassword(_In_ CString orgPassword, _Out_ CString &hashedPassword);
};