// LECTURE_info.h : Declaration of the CLECTURE_info

#pragma once

// code generated on 2014년 6월 19일 목요일, 오후 10:45
// 100835 한승환
class CLECTURE_GETCREDIT
{
public:
	LONG m_SID;
	TCHAR m_Course_Type[51];
	LONG m_CREDITS;
	

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwSIDStatus;
	DBSTATUS m_dwCourse_TypeStatus;
	DBSTATUS m_dwCREDITSStatus;
	

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwSIDLength;
	DBLENGTH m_dwCourse_TypeLength;
	DBLENGTH m_dwCREDITSLength;



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

	DEFINE_COMMAND_EX(CLECTURE_GETCREDIT, L" \
		SELECT Course_Type, CREDITS \
		FROM dbo.LECTURE_info \
		WHERE SID = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETCREDIT)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETCREDIT)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
		END_COLUMN_MAP()
};

class CLECTURE_GETGRADE
{
public:
	LONG m_YEAR;
	LONG m_SEMESTER;
	LONG m_SID;
	
	double m_RESULT;
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
	DBSTATUS m_dwSIDStatus;

	DBSTATUS m_dwRESULTStatus;
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
	DBLENGTH m_dwSIDLength;

	DBLENGTH m_dwRESULTLength;
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

	DEFINE_COMMAND_EX(CLECTURE_GETGRADE, L" \
		SELECT RESULT, CREDITS, Subject_Name, Subject_Number, PROFESSOR \
		FROM dbo.LECTURE_info \
		WHERE SID = ? AND YEAR = ? AND SEMESTER = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETGRADE)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETGRADE)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_RESULT, m_dwRESULTLength, m_dwRESULTStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
		END_COLUMN_MAP()
};
class CLECTURE_GETSEMESTER
{
public:
	LONG m_SID;
	LONG m_YEAR;
	LONG m_SEMESTER;
	

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwSIDStatus;
	DBSTATUS m_dwYEARStatus;
	DBSTATUS m_dwSEMESTERStatus;
	

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwSIDLength;
	DBLENGTH m_dwYEARLength;
	DBLENGTH m_dwSEMESTERLength;
	

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

	DEFINE_COMMAND_EX(CLECTURE_GETSEMESTER, L" \
		SELECT DISTINCT SEMESTER \
		FROM dbo.LECTURE_info \
		WHERE SID = ? AND YEAR = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETSEMESTER)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETSEMESTER)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_COLUMN_MAP()
};
class CLECTURE_GETYEAR
{
public:
	LONG m_SID;
	LONG m_YEAR;
	
	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwSIDStatus;
	DBSTATUS m_dwYEARStatus;
	
	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!
	
	DBLENGTH m_dwSIDLength;
	DBLENGTH m_dwYEARLength;


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

	DEFINE_COMMAND_EX(CLECTURE_GETYEAR, L" \
		SELECT DISTINCT YEAR \
		FROM dbo.LECTURE_info \
		WHERE SID = ? ")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETYEAR)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETYEAR)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
		END_COLUMN_MAP()
};

class CLECTURE_GETCURRENTSUBJECT
{
public:
	LONG m_YEAR;
	LONG m_SEMESTER;
	LONG m_SID;

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
	DBSTATUS m_dwSIDStatus;

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
	DBLENGTH m_dwSIDLength;

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

	DEFINE_COMMAND_EX(CLECTURE_GETCURRENTSUBJECT, L" \
		SELECT Course_Type, CREDITS, Subject_Name, Subject_Number, PROFESSOR \
		FROM dbo.LECTURE_info \
		WHERE SID = ? AND YEAR = ? AND SEMESTER = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETCURRENTSUBJECT)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETCURRENTSUBJECT)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
		END_COLUMN_MAP()
};
class CLECTURE_GETMAJOR
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

	DEFINE_COMMAND_EX(CLECTURE_GETMAJOR, L" \
		SELECT \
		DISTINCT MAJOR \
		FROM dbo.LECTURE_info \
		WHERE YEAR = ? AND SEMESTER = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CLECTURE_GETMAJOR)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CLECTURE_GETMAJOR)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
		END_COLUMN_MAP()
};
//class CLECTURE_infoAccessor
//{
//public:
//	LONG m_Order_Number;
//	LONG m_YEAR;
//	LONG m_SEMESTER;
//	TCHAR m_Course_Type[51];
//	LONG m_CREDITS;
//	TCHAR m_Subject_Name[51];
//	TCHAR m_Subject_Number[51];
//	TCHAR m_PROFESSOR[51];
//	TCHAR m_MAJOR[51];
//	LONG m_SID;
//	TCHAR m_SNAME[51];
//	double m_RESULT;
//	TCHAR m_Make_Up[51];
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
//	DBSTATUS m_dwOrder_NumberStatus;
//	DBSTATUS m_dwYEARStatus;
//	DBSTATUS m_dwSEMESTERStatus;
//	DBSTATUS m_dwCourse_TypeStatus;
//	DBSTATUS m_dwCREDITSStatus;
//	DBSTATUS m_dwSubject_NameStatus;
//	DBSTATUS m_dwSubject_NumberStatus;
//	DBSTATUS m_dwPROFESSORStatus;
//	DBSTATUS m_dwMAJORStatus;
//	DBSTATUS m_dwSIDStatus;
//	DBSTATUS m_dwSNAMEStatus;
//	DBSTATUS m_dwRESULTStatus;
//	DBSTATUS m_dwMake_UpStatus;
//
//	// The following wizard-generated data members contain length
//	// values for the corresponding fields in the column map.
//	// NOTE: For variable-length columns, you must initialize these
//	//       fields before setting/inserting data!
//
//	DBLENGTH m_dwOrder_NumberLength;
//	DBLENGTH m_dwYEARLength;
//	DBLENGTH m_dwSEMESTERLength;
//	DBLENGTH m_dwCourse_TypeLength;
//	DBLENGTH m_dwCREDITSLength;
//	DBLENGTH m_dwSubject_NameLength;
//	DBLENGTH m_dwSubject_NumberLength;
//	DBLENGTH m_dwPROFESSORLength;
//	DBLENGTH m_dwMAJORLength;
//	DBLENGTH m_dwSIDLength;
//	DBLENGTH m_dwSNAMELength;
//	DBLENGTH m_dwRESULTLength;
//	DBLENGTH m_dwMake_UpLength;
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
//#error Security Issue: The connection string may contain a password
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
//	DEFINE_COMMAND_EX(CLECTURE_infoAccessor, L" \
//	SELECT \
//		Order_Number, \
//		YEAR, \
//		SEMESTER, \
//		Course_Type, \
//		CREDITS, \
//		Subject_Name, \
//		Subject_Number, \
//		PROFESSOR, \
//		MAJOR, \
//		SID, \
//		SNAME, \
//		RESULT, \
//		Make_Up \
//		FROM dbo.LECTURE_info")
//
//
//	// In order to fix several issues with some providers, the code below may bind
//	// columns in a different order than reported by the provider
//
//	BEGIN_COLUMN_MAP(CLECTURE_infoAccessor)
//		COLUMN_ENTRY_LENGTH_STATUS(1, m_Order_Number, m_dwOrder_NumberLength, m_dwOrder_NumberStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(2, m_YEAR, m_dwYEARLength, m_dwYEARStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(3, m_SEMESTER, m_dwSEMESTERLength, m_dwSEMESTERStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(4, m_Course_Type, m_dwCourse_TypeLength, m_dwCourse_TypeStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(5, m_CREDITS, m_dwCREDITSLength, m_dwCREDITSStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(6, m_Subject_Name, m_dwSubject_NameLength, m_dwSubject_NameStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(7, m_Subject_Number, m_dwSubject_NumberLength, m_dwSubject_NumberStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(8, m_PROFESSOR, m_dwPROFESSORLength, m_dwPROFESSORStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(9, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(10, m_SID, m_dwSIDLength, m_dwSIDStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(11, m_SNAME, m_dwSNAMELength, m_dwSNAMEStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(12, m_RESULT, m_dwRESULTLength, m_dwRESULTStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(13, m_Make_Up, m_dwMake_UpLength, m_dwMake_UpStatus)
//	END_COLUMN_MAP()
//};
template <class T>
class CLECTURE_info : public CCommand<CAccessor<T> >
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


// 100835 한승환