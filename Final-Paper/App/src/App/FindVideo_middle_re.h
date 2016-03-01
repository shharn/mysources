
// FindVideo_middle_re.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "GlobalFunction.h"
#include "sha1.h"

// CFindVideo_middle_reApp:
// See FindVideo_middle_re.cpp for the implementation of this class
//

class CFindVideo_middle_reApp : public CWinApp
{
public:
	CFindVideo_middle_reApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFindVideo_middle_reApp theApp;

