#include "stdafx.h"
#include "GlobalFunction.h"

BOOL GlobalFunction::WriteToRigestrySZ(LPCTSTR path, CString keyName, CString value)
{
	HKEY hKey;
	DWORD result;
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, path, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);	
	if (result != ERROR_SUCCESS)
		return FALSE;
	
	LPTSTR szData = value.GetBuffer(value.GetLength());
	UINT length = value.GetLength();
	DWORD len = (value.GetLength() + 1)* 2;
	result = RegSetValueEx(hKey, keyName.GetBuffer(value.GetLength()), NULL, REG_SZ, (LPBYTE)szData, len);
	if (result != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}
BOOL GlobalFunction::WriteToRegistryDW(UINT dwData)
{
	HKEY hKey;
	DWORD result;
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, REGISTRY_PATH, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result != ERROR_SUCCESS)
		return FALSE;

	DWORD len = sizeof(DWORD);
	result = RegSetValueEx(hKey, ISLOCKED_KEY, NULL, REG_DWORD, (LPBYTE)&dwData, len);
	if (result != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

BOOL GlobalFunction::GetConfigurationInfo(BOOL& dwData/*isLocked*/, std::vector<CString>& list/*file list*/, CString& string/*hased password*/)
{
	BOOL result1, result2, result3;
	result1 = GlobalFunction::GetConfigurationIslocked(dwData);
	result2 = GlobalFunction::GetConfigurationFileList(list);
	result3 = GlobalFunction::GetConfigurationPassword(string);
	return (result1 && result2 && result3);
}

BOOL GlobalFunction::GetConfigurationIslocked(BOOL &isLocked)
{
	HKEY hKey;
	DWORD result;
	
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, REGISTRY_PATH, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result != ERROR_SUCCESS)
	{
		UINT errorcode = GetLastError();
		RegCloseKey(hKey);
		return FALSE;
	}

	// Get the lock-state information
	DWORD dwisLocked;
	DWORD size = sizeof(isLocked);
	result = RegQueryValueEx(hKey, ISLOCKED_KEY, NULL, NULL, (LPBYTE)&dwisLocked, (LPDWORD)&size);
	if (result == ERROR_MORE_DATA)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	isLocked = dwisLocked == 1 ? true : false;
	RegCloseKey(hKey);
	return TRUE;
}

BOOL GlobalFunction::GetConfigurationFileList(std::vector<CString> &list)
{
	HKEY hKey;
	DWORD result;
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, FILE_LIST_PATH, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result != ERROR_SUCCESS)
	{
		UINT errorcode = GetLastError();
		RegCloseKey(hKey);
		return FALSE;
	}
	GlobalFunction::QueryAndEnumerateKey(hKey, list);
	RegCloseKey(hKey);
	return TRUE;
}

BOOL GlobalFunction::GetConfigurationPassword(CString &password)
{
	HKEY hKey;
	DWORD result;
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, REGISTRY_PATH, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result != ERROR_SUCCESS)
	{
		UINT errorcode = GetLastError();
		CString temp;
		temp.Format(_T("Faild to get config from registry , errorcode : %d"), errorcode);
		RegCloseKey(hKey);
		return FALSE;
	}

	// Get the hashed password
	TCHAR passwd[512];
	DWORD len = sizeof(passwd);
	result = RegQueryValueEx(hKey, PASSWORD_KEY, NULL, NULL, (LPBYTE)passwd, (LPDWORD)&len);
	if (result == ERROR_MORE_DATA)
	{
		UINT errorcode = GetLastError();
		CString temp;
		temp.Format(_T("Faild to get config from registry , errorcode : %d"), errorcode);
		RegCloseKey(hKey);
		return FALSE;
	}
	password.Format(_T("%s"), passwd);
	RegCloseKey(hKey);
	return TRUE;
}

void GlobalFunction::QueryAndEnumerateKey(HKEY hKey, std::vector<CString>& list/*file list*/)
{
	DWORD    cValues;              // number of values for key 

	DWORD i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;
	TCHAR achData[MAX_VALUE_NAME];
	DWORD cchData = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,				// key handle 
		NULL,				// buffer for class name 
		NULL,				// size of class string 
		NULL,               // reserved 
		NULL,               // number of subkeys 
		NULL,				// longest subkey size 
		NULL,				// longest class string 
		&cValues,           // number of values for this key 
		NULL,				// longest value name 
		NULL,				// longest value data 
		NULL,				// security descriptor 
		NULL);				// last write time 

	// Enumerate the key values. 
	if (cValues)
	{
		for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++)
		{
			cchValue = MAX_VALUE_NAME;
			cchData = MAX_VALUE_NAME;
			achValue[0] = '\0';
			achData[0] = '\0';
			retCode = RegEnumValue(hKey, i,
				achValue,
				&cchValue,
				NULL,
				NULL,
				(LPBYTE)achData,
				&cchData);
			
			CString temp(achData);
			list.push_back(temp);
		}
	}
}

BOOL GlobalFunction::DeleteConfiguration(UINT flag)
{
	HKEY hKey;
	DWORD result;
	TCHAR path[MAX_PATH];
	if (flag == DELETE_ONLY_PATHS)
		_tcscpy_s(path, sizeof(FILE_LIST_PATH), FILE_LIST_PATH);
	else
		_tcscpy_s(path, sizeof(REGISTRY_PATH), REGISTRY_PATH);
	result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, path, NULL, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (result != ERROR_SUCCESS)
		return FALSE;

	result = RegDeleteTree(hKey, NULL);
	if (result != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

void GlobalFunction::GetHashedValueFromPassword(_In_ CString orgPassword, _Out_ CString &hashedPassword)
{
	SHA1 sha;
	UINT message_digest[5];
	ZeroMemory(message_digest, sizeof(message_digest));
	sha.Reset();
	char* password = NULL;

	int strSize = WideCharToMultiByte(CP_ACP, 0, orgPassword.GetString(), -1, NULL, 0, NULL, NULL);
	password = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, orgPassword.GetString(), -1, password, strSize, 0, 0);
	sha << password;

	if (!sha.Result(message_digest))
		AfxMessageBox(_T("ERROR : could not compute message diges"));

	hashedPassword.Empty();
	hashedPassword.Format(_T("%x%x%x%x%x"), message_digest[0],
		message_digest[1],
		message_digest[2],
		message_digest[3],
		message_digest[4]);
}

