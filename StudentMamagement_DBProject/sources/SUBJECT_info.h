// SUBJECT_info.h : Declaration of the CSUBJECT_info

#pragma once

// code generated on 2014년 6월 20일 금요일, 오전 12:01
// 100835 한승환
class CSUBJECT_Schedule
{
public:
	TCHAR m_Subject_Number[51];
	TCHAR m_Subject_Name[51];
	LONG m_Class_Time;
	TCHAR m_CLASSROOM[51];
	LONG m_CREDITS;
	TCHAR m_PROFESSOR[51];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwSubject_NumberStatus;
	DBSTATUS m_dwSubject_NameStatus;
	DBSTATUS m_dwClass_TimeStatus;
	DBSTATUS m_dwCLASSROOMStatus;
	DBSTATUS m_dwCREDITSStatus;
	DBSTATUS m_dwPROFESSORStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!
	
	DBLENGTH m_dwSubject_NumberLength;
	DBLENGTH m_dwSubject_NameLength;
	DBLENGTH m_dwClass_TimeLength;
	DBLENGTH m_dwCLASSROOMLength;
	DBLENGTH m_dwCREDITSLength;
	DBLENGTH m_dwPROFESSORLength;



	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
		//#error Security Issue: The connection string may contain a password
		// The connection string below may contain plain text passwords and/or
		// other sensitive information. Please remove the #error after reviewing
		// the connection string for any security related issues. You may want to
		// store the password in some other form or use a different user authentication.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Student_Management;Data Source=HOPE-HP\\TURTLEDB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOPE-HP;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CSUBJECT_Schedule, L" \
		SELECT \
		Subject_Name, \
		Class_Time, \
		CLASSROOM, \
		CREDITS, \
		PROFESSOR \
		FROM dbo.SUBJECT_info \
		WHERE Subject_Number = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CSUBJECT_Schedule)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CSUBJECT_Schedule)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_Class_Time, m_dwClass_TimeLength, m_dwClass_TimeStatus)
			COLUMN_ENTRY_LENGTH_STATUS(3, m_CLASSROOM, m_dwCLASSROOMLength, m_dwCLASSROOMStatus)
			COLUMN_ENTRY_LENGTH_STATUS(4, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
			COLUMN_ENTRY_LENGTH_STATUS(5, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
		END_COLUMN_MAP()
};
class CSUBJECT_SEARCHKEYWORD
{
public:
	LONG m_YEAR;
	LONG m_SEMESTER;
	TCHAR m_MAJOR[51];
	TCHAR m_Course_Type[51];
	LONG m_CREDITS;
	TCHAR m_Subject_Name[51];
	TCHAR m_Subject_Number[51];
	TCHAR m_PROFESSOR[51];
	TCHAR m_KEYWORD[501];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwYEARStatus;
	DBSTATUS m_dwSEMESTERStatus;
	DBSTATUS m_dwMAJORStatus;
	DBSTATUS m_dwCourse_TypeStatus;
	DBSTATUS m_dwCREDITSStatus;
	DBSTATUS m_dwSubject_NameStatus;
	DBSTATUS m_dwSubject_NumberStatus;
	DBSTATUS m_dwPROFESSORStatus;
	DBSTATUS m_dwKEYWORDStatus;



	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwYEARLength;
	DBLENGTH m_dwSEMESTERLength;
	DBLENGTH m_dwMAJORLength;
	DBLENGTH m_dwCourse_TypeLength;
	DBLENGTH m_dwCREDITSLength;
	DBLENGTH m_dwSubject_NameLength;
	DBLENGTH m_dwSubject_NumberLength;
	DBLENGTH m_dwPROFESSORLength;
	DBLENGTH m_dwKEYWORDLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
		//#error Security Issue: The connection string may contain a password
		// The connection string below may contain plain text passwords and/or
		// other sensitive information. Please remove the #error after reviewing
		// the connection string for any security related issues. You may want to
		// store the password in some other form or use a different user authentication.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Student_Management;Data Source=HOPE-HP\\TURTLEDB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOPE-HP;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CSUBJECT_SEARCHKEYWORD, L" \
		SELECT Course_Type, CREDITS, Subject_Name, Subject_Number, PROFESSOR, Keyword, MAJOR \
		FROM dbo.SUBJECT_info \
		WHERE YEAR=? AND SEMESTER=? ")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider

		BEGIN_PARAM_MAP(CSUBJECT_SEARCHKEYWORD)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CSUBJECT_SEARCHKEYWORD)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
			COLUMN_ENTRY_LENGTH_STATUS(3, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
			COLUMN_ENTRY_LENGTH_STATUS(4, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
			COLUMN_ENTRY_LENGTH_STATUS(5, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
			COLUMN_ENTRY_LENGTH_STATUS(6, m_KEYWORD, m_dwKEYWORDLength, m_dwKEYWORDStatus);
			COLUMN_ENTRY_LENGTH_STATUS(7, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus);
		END_COLUMN_MAP()
};

class CSUBJECT_GETMAJOR
{
public:
	LONG m_YEAR;
	LONG m_SEMESTER;
	TCHAR m_MAJOR[51];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	DBSTATUS m_dwYEARStatus;
	DBSTATUS m_dwSEMESTERStatus;
	DBSTATUS m_dwMAJORStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!
	DBLENGTH m_dwYEARLength;
	DBLENGTH m_dwSEMESTERLength;
	DBLENGTH m_dwMAJORLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error Security Issue: The connection string may contain a password
		// The connection string below may contain plain text passwords and/or
		// other sensitive information. Please remove the #error after reviewing
		// the connection string for any security related issues. You may want to
		// store the password in some other form or use a different user authentication.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Student_Management;Data Source=HOPE-HP\\TURTLEDB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOPE-HP;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CSUBJECT_GETMAJOR, L" \
		SELECT DISTINCT MAJOR \
		FROM dbo.SUBJECT_info \
		WHERE YEAR=? AND SEMESTER=?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider

		BEGIN_PARAM_MAP(CSUBJECT_GETMAJOR)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CSUBJECT_GETMAJOR)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
		END_COLUMN_MAP()
};
class CSUBJECT_GETSUBJECTINFO
{
public:
	LONG m_YEAR;
	LONG m_SEMESTER;
	TCHAR m_MAJOR[51];

	TCHAR m_Course_Type[51];
	LONG m_CREDITS;
	TCHAR m_Subject_Name[51];
	TCHAR m_Subject_Number[51];
	TCHAR m_PROFESSOR[51];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwYEARStatus;
	DBSTATUS m_dwSEMESTERStatus;
	DBSTATUS m_dwMAJORStatus;

	DBSTATUS m_dwCourse_TypeStatus;
	DBSTATUS m_dwCREDITSStatus;
	DBSTATUS m_dwSubject_NameStatus;
	DBSTATUS m_dwSubject_NumberStatus;
	DBSTATUS m_dwPROFESSORStatus;



	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwYEARLength;
	DBLENGTH m_dwSEMESTERLength;
	DBLENGTH m_dwMAJORLength;

	DBLENGTH m_dwCourse_TypeLength;
	DBLENGTH m_dwCREDITSLength;
	DBLENGTH m_dwSubject_NameLength;
	DBLENGTH m_dwSubject_NumberLength;
	DBLENGTH m_dwPROFESSORLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error Security Issue: The connection string may contain a password
		// The connection string below may contain plain text passwords and/or
		// other sensitive information. Please remove the #error after reviewing
		// the connection string for any security related issues. You may want to
		// store the password in some other form or use a different user authentication.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Student_Management;Data Source=HOPE-HP\\TURTLEDB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOPE-HP;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CSUBJECT_GETSUBJECTINFO, L" \
		SELECT Course_Type, CREDITS, Subject_Name, Subject_Number, PROFESSOR \
		FROM dbo.SUBJECT_info \
		WHERE MAJOR = ? AND YEAR = ? AND SEMESTER = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider

		BEGIN_PARAM_MAP(CSUBJECT_GETSUBJECTINFO)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
			COLUMN_ENTRY_LENGTH_STATUS(3, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CSUBJECT_GETSUBJECTINFO)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
			COLUMN_ENTRY_LENGTH_STATUS(3, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
			COLUMN_ENTRY_LENGTH_STATUS(4, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
			COLUMN_ENTRY_LENGTH_STATUS(5, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
		END_COLUMN_MAP()
};
//class CSUBJECT_infoAccessor
//{
//public:
//	TCHAR m_MAJOR[51];
//	TCHAR m_Course_Type[51];
//	TCHAR m_Subject_Name[51];
//	TCHAR m_Subject_Number[51];
//	LONG m_Class_Time;
//	TCHAR m_CLASSROOM[51];
//	LONG m_CREDITS;
//	LONG m_YEAR;
//	LONG m_SEMESTER;
//	LONG m_GRADER;
//	LONG m_Max_Number;
//	TCHAR m_PROFESSOR[51];
//	TCHAR m_Keyword[501];
//
//	// The following wizard-generated data members contain status
//	// values for the corresponding fields in the column map. You
//	// can use these values to hold NULL values that the database
//	// returns or to hold error information when the compiler returns
//	// errors. See Field Status Data Members in Wizard-Generated
//	// Accessors in the Visual C++ documentation for more information
//	// on using these fields.
//	// NOTE: You must initialize these fields before setting/inserting data!
//
//	DBSTATUS m_dwMAJORStatus;
//	DBSTATUS m_dwCourse_TypeStatus;
//	DBSTATUS m_dwSubject_NameStatus;
//	DBSTATUS m_dwSubject_NumberStatus;
//	DBSTATUS m_dwClass_TimeStatus;
//	DBSTATUS m_dwCLASSROOMStatus;
//	DBSTATUS m_dwCREDITSStatus;
//	DBSTATUS m_dwYEARStatus;
//	DBSTATUS m_dwSEMESTERStatus;
//	DBSTATUS m_dwGRADERStatus;
//	DBSTATUS m_dwMax_NumberStatus;
//	DBSTATUS m_dwPROFESSORStatus;
//	DBSTATUS m_dwKeywordStatus;
//
//	// The following wizard-generated data members contain length
//	// values for the corresponding fields in the column map.
//	// NOTE: For variable-length columns, you must initialize these
//	//       fields before setting/inserting data!
//
//	DBLENGTH m_dwMAJORLength;
//	DBLENGTH m_dwCourse_TypeLength;
//	DBLENGTH m_dwSubject_NameLength;
//	DBLENGTH m_dwSubject_NumberLength;
//	DBLENGTH m_dwClass_TimeLength;
//	DBLENGTH m_dwCLASSROOMLength;
//	DBLENGTH m_dwCREDITSLength;
//	DBLENGTH m_dwYEARLength;
//	DBLENGTH m_dwSEMESTERLength;
//	DBLENGTH m_dwGRADERLength;
//	DBLENGTH m_dwMax_NumberLength;
//	DBLENGTH m_dwPROFESSORLength;
//	DBLENGTH m_dwKeywordLength;
//
//
//	void GetRowsetProperties(CDBPropSet* pPropSet)
//	{
//		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
//		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
//		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
//		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
//	}
//
//	HRESULT OpenDataSource()
//	{
//		CDataSource _db;
//		HRESULT hr;
////#error Security Issue: The connection string may contain a password
//// The connection string below may contain plain text passwords and/or
//// other sensitive information. Please remove the #error after reviewing
//// the connection string for any security related issues. You may want to
//// store the password in some other form or use a different user authentication.
//		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Student_Management;Data Source=HOPE-HP\\TURTLEDB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOPE-HP;Use Encryption for Data=False;Tag with column collation when possible=False");
//		if (FAILED(hr))
//		{
//#ifdef _DEBUG
//			AtlTraceErrorRecords(hr);
//#endif
//			return hr;
//		}
//		return m_session.Open(_db);
//	}
//
//	void CloseDataSource()
//	{
//		m_session.Close();
//	}
//
//	operator const CSession&()
//	{
//		return m_session;
//	}
//
//	CSession m_session;
//
//	DEFINE_COMMAND_EX(CSUBJECT_infoAccessor, L" \
//	SELECT \
//		MAJOR, \
//		Course_Type, \
//		Subject_Name, \
//		Subject_Number, \
//		Class_Time, \
//		CLASSROOM, \
//		CREDITS, \
//		YEAR, \
//		SEMESTER, \
//		GRADER, \
//		Max_Number, \
//		PROFESSOR, \
//		Keyword \
//		FROM dbo.SUBJECT_info")
//
//
//	// In order to fix several issues with some providers, the code below may bind
//	// columns in a different order than reported by the provider
//
//	BEGIN_COLUMN_MAP(CSUBJECT_infoAccessor)
//		COLUMN_ENTRY_LENGTH_STATUS(1, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(2, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(3, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(4, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(5, m_Class_Time, m_dwClass_TimeLength, m_dwClass_TimeStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(6, m_CLASSROOM, m_dwCLASSROOMLength, m_dwCLASSROOMStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(7, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(8, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(9, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(10, m_GRADER, m_dwGRADERLength, m_dwGRADERStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(11, m_Max_Number, m_dwMax_NumberLength, m_dwMax_NumberStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(12, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(13, m_Keyword, m_dwKeywordLength, m_dwKeywordStatus)
//	END_COLUMN_MAP()
//};
template <class T>
class CSUBJECT_info : public CCommand<CAccessor<T> >
{
public:
	HRESULT OpenAll()
	{
		HRESULT hr;
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
		__if_exists(GetRowsetProperties)
		{
			CDBPropSet propset(DBPROPSET_ROWSET);
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
					propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
			GetRowsetProperties(&propset);
			return OpenRowset(&propset);
		}
		__if_not_exists(GetRowsetProperties)
		{
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
				{
					CDBPropSet propset(DBPROPSET_ROWSET);
					propset.AddProperty(DBPROP_IRowsetLocate, true);
					return OpenRowset(&propset);
				}
			}
		}
		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET *pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, NULL, pPropSet);
#ifdef _DEBUG
		if(FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		ReleaseCommand();
		CloseDataSource();
	}
};


