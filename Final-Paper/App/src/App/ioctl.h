#pragma once
#include "afxwin.h"
#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <strsafe.h>
#include <winioctl.h>

//#define LOG_INFO(FormatString, ...)    
//#define LOG_INFO_FAILURE(FormatString, ...) 

#define LOG_INFO(FormatString, ...) 
#define LOG_INFO_FAILURE(FormatString, ...)

#define LOG_PASSED(FormatString, ...)      
#define LOG_ERROR(FormatString, ...)

extern HANDLE TcDeviceHandle;

BOOL TcInitialize();
BOOL TcUnInitialize();
BOOL TcCleanupSCM();

BOOL TcInstallDriver();

BOOL TcUninstallDriver();

BOOL TcRemoveProtection();

BOOL TcProcessName(
	_In_reads_(argc) LPCWSTR processName,
	_In_ ULONG ulOperation
	);

BOOL TcUnprotectCallback();

BOOL TcProcessNameCallback(
	_In_reads_(NAME_SIZE + 1) PCWSTR  pnametoprotect,
	_In_ ULONG ulOperation
	);

//
// Utility functions
//

BOOL TcInitializeGlobals();
BOOL TcLoadDriver();
BOOL TcUnloadDriver();

BOOL TcCreateService();
BOOL TcDeleteService();
BOOL TcStartService();
BOOL TcStopService();

BOOL TcOpenDevice();
BOOL TcCloseDevice();

#define TD_DRIVER_NAME             L"ProtectAVS"
#define TD_DRIVER_NAME_WITH_EXT    L"ProtectAVS.sys"

#define TD_NT_DEVICE_NAME          L"\\Device\\ProtectAVS"
#define TD_DOS_DEVICES_LINK_NAME   L"\\DosDevices\\ProtectAVS"
#define TD_WIN32_DEVICE_NAME       L"\\\\.\\ProtectAVS"


#define NAME_SIZE   200

#define TD_INVALID_CALLBACK_ID ((ULONG)-1)

//
// IOCTLs exposed by the driver.
//

// #define TD_IOCTL_REGISTER_CALLBACK   CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 0), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
// #define TD_IOCTL_UNREGISTER_CALLBACK CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 1), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define TD_IOCTL_PROTECT_NAME_CALLBACK        CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 2), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define TD_IOCTL_UNPROTECT_CALLBACK           CTL_CODE (FILE_DEVICE_UNKNOWN, (0x800 + 3), METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


#define TDProtectName_Protect  0            // name of programs to proect and filter out the desiredAccess on Process Open
#define TDProtectName_Reject   1            // name of programs to reject during ProcessCreate

//
// Structures used by TD_IOCTL_PROTECTNAME
//

typedef struct _TD_PROTECTNAME_INPUT {
	ULONG Operation;
	WCHAR Name[NAME_SIZE + 1];      // what is the filename to protect - extra wchar for forced NULL
}
TD_PROTECTNAME_INPUT, *PTD_PROTECTNAME_INPUT;

//
// Structures used by TD_IOCTL_UNPROTECT_CALLBACK
//

typedef struct _TD_UNPROTECT_CALLBACK_INPUT {
	ULONG UnusedParameter;
}
TD_UNPROTECT_CALLBACK_INPUT, *PTD_UNPROTECT_CALLBACK_INPUT;