
// Portal.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "STUDENT_info.h"
#include "Student.h"
#include "LECTURE_info.h"
#include "SUBJECT_info.h"
#include "Drop_Lecture.h"
#include "ADD_Lecture.h"
#include "UPDATE_STUCOURSE.h"
#include "GET_COURSE.h"
#include "GET_STUINFO.h"
#include "Stu_ModiInfo.h"
#include "FIX_STUINFO.h"
#include "Register.h"
#include "Register_Student.h"

// CPortalApp:
// See Portal.cpp for the implementation of this class
//

class CPortalApp : public CWinApp
{
public:
	CPortalApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPortalApp theApp;