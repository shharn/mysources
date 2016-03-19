// STUDENT_info.h : Declaration of the CSTUDENT_info

#pragma once

// code generated on 2014년 6월 19일 목요일, 오후 9:48
// 100835 한승환
class CSTUDENT_GETCOURSEYEAR
{
public:
	LONG m_SID;
	LONG m_Curri_Year;

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwSIDStatus;
	DBSTATUS m_dwCurri_YearStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwSIDLength;
	DBLENGTH m_dwCurri_YearLength;


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

	DEFINE_COMMAND_EX(CSTUDENT_GETCOURSEYEAR, L" \
		SELECT Curri_Year \
		FROM dbo.STUDENT_info \
		WHERE SID = ?")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CSTUDENT_GETCOURSEYEAR)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		END_PARAM_MAP()

		BEGIN_COLUMN_MAP(CSTUDENT_GETCOURSEYEAR)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_Curri_Year, m_dwCurri_YearLength, m_dwCurri_YearStatus)
		END_COLUMN_MAP()
};
class CSTUDENT_infoAccessor
{
public:
	LONG m_SID;
	TCHAR m_SNAME[51];
	LONG m_PASSWORD;

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwSNAMEStatus;
	DBSTATUS m_dwSIDStatus;
	DBSTATUS m_dwPASSWORDStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwSNAMELength;
	DBLENGTH m_dwSIDLength;
	DBLENGTH m_dwPASSWORDLength;


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

		DEFINE_COMMAND_EX(CSTUDENT_infoAccessor, L" \
		SELECT \
		PASSWORD, SNAME \
		FROM dbo.STUDENT_info \
		WHERE SID = ? ")


		// In order to fix several issues with some providers, the code below may bind
		// columns in a different order than reported by the provider
		BEGIN_PARAM_MAP(CSTUDENT_infoAccessor)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
		END_PARAM_MAP()
		
		BEGIN_COLUMN_MAP(CSTUDENT_infoAccessor)
			COLUMN_ENTRY_LENGTH_STATUS(1, m_PASSWORD, m_dwPASSWORDLength, m_dwPASSWORDStatus)
			COLUMN_ENTRY_LENGTH_STATUS(2, m_SNAME, m_dwSNAMELength, m_dwSNAMEStatus)
		END_COLUMN_MAP()
};
//class CSTUDENT_infoAccessor
//{
//public:
//	LONG m_SID;
//	TCHAR m_SNAME[51];
//	LONG m_PASSWORD;
//	TCHAR m_GENDER[51];
//	LONG m_Curri_Year;
//	LONG m_GRADER;
//	TCHAR m_ADDERSS[51];
//	TCHAR m_Phone_Number[51];
//	TCHAR m_MAJOR[51];
//	LONG m_Required_Cultural;
//	LONG m_Cultural_Course;
//	LONG m_Cultural_Credits;
//	LONG m_Required_Major;
//	LONG m_Major_Course;
//	LONG m_Major_Credits;
//	LONG m_General_Course;
//	LONG m_Total_Credits;
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
//	DBSTATUS m_dwSIDStatus;
//	DBSTATUS m_dwSNAMEStatus;
//	DBSTATUS m_dwPASSWORDStatus;
//	DBSTATUS m_dwGENDERStatus;
//	DBSTATUS m_dwCurri_YearStatus;
//	DBSTATUS m_dwGRADERStatus;
//	DBSTATUS m_dwADDERSSStatus;
//	DBSTATUS m_dwPhone_NumberStatus;
//	DBSTATUS m_dwMAJORStatus;
//	DBSTATUS m_dwRequired_CulturalStatus;
//	DBSTATUS m_dwCultural_CourseStatus;
//	DBSTATUS m_dwCultural_CreditsStatus;
//	DBSTATUS m_dwRequired_MajorStatus;
//	DBSTATUS m_dwMajor_CourseStatus;
//	DBSTATUS m_dwMajor_CreditsStatus;
//	DBSTATUS m_dwGeneral_CourseStatus;
//	DBSTATUS m_dwTotal_CreditsStatus;
//
//	// The following wizard-generated data members contain length
//	// values for the corresponding fields in the column map.
//	// NOTE: For variable-length columns, you must initialize these
//	//       fields before setting/inserting data!
//
//	DBLENGTH m_dwSIDLength;
//	DBLENGTH m_dwSNAMELength;
//	DBLENGTH m_dwPASSWORDLength;
//	DBLENGTH m_dwGENDERLength;
//	DBLENGTH m_dwCurri_YearLength;
//	DBLENGTH m_dwGRADERLength;
//	DBLENGTH m_dwADDERSSLength;
//	DBLENGTH m_dwPhone_NumberLength;
//	DBLENGTH m_dwMAJORLength;
//	DBLENGTH m_dwRequired_CulturalLength;
//	DBLENGTH m_dwCultural_CourseLength;
//	DBLENGTH m_dwCultural_CreditsLength;
//	DBLENGTH m_dwRequired_MajorLength;
//	DBLENGTH m_dwMajor_CourseLength;
//	DBLENGTH m_dwMajor_CreditsLength;
//	DBLENGTH m_dwGeneral_CourseLength;
//	DBLENGTH m_dwTotal_CreditsLength;
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
//	DEFINE_COMMAND_EX(CSTUDENT_infoAccessor, L" \
//	SELECT \
//		SID, \
//		SNAME, \
//		PASSWORD, \
//		GENDER, \
//		Curri_Year, \
//		GRADER, \
//		ADDERSS, \
//		Phone_Number, \
//		MAJOR, \
//		Required_Cultural, \
//		Cultural_Course, \
//		Cultural_Credits, \
//		Required_Major, \
//		Major_Course, \
//		Major_Credits, \
//		General_Course, \
//		Total_Credits \
//		FROM dbo.STUDENT_info")
//
//
//	// In order to fix several issues with some providers, the code below may bind
//	// columns in a different order than reported by the provider
//
//	BEGIN_COLUMN_MAP(CSTUDENT_infoAccessor)
//		COLUMN_ENTRY_LENGTH_STATUS(1, m_SID, m_dwSIDLength, m_dwSIDStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(2, m_SNAME, m_dwSNAMELength, m_dwSNAMEStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(3, m_PASSWORD, m_dwPASSWORDLength, m_dwPASSWORDStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(4, m_GENDER, m_dwGENDERLength, m_dwGENDERStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(5, m_Curri_Year, m_dwCurri_YearLength, m_dwCurri_YearStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(6, m_GRADER, m_dwGRADERLength, m_dwGRADERStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(7, m_ADDERSS, m_dwADDERSSLength, m_dwADDERSSStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(8, m_Phone_Number, m_dwPhone_NumberLength, m_dwPhone_NumberStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(9, m_MAJOR, m_dwMAJORLength, m_dwMAJORStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(10, m_Required_Cultural, m_dwRequired_CulturalLength, m_dwRequired_CulturalStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(11, m_Cultural_Course, m_dwCultural_CourseLength, m_dwCultural_CourseStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(12, m_Cultural_Credits, m_dwCultural_CreditsLength, m_dwCultural_CreditsStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(13, m_Required_Major, m_dwRequired_MajorLength, m_dwRequired_MajorStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(14, m_Major_Course, m_dwMajor_CourseLength, m_dwMajor_CourseStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(15, m_Major_Credits, m_dwMajor_CreditsLength, m_dwMajor_CreditsStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(16, m_General_Course, m_dwGeneral_CourseLength, m_dwGeneral_CourseStatus)
//		COLUMN_ENTRY_LENGTH_STATUS(17, m_Total_Credits, m_dwTotal_CreditsLength, m_dwTotal_CreditsStatus)
//	END_COLUMN_MAP()
//};
template <class T>
class CSTUDENT_info : public CCommand<CAccessor<T> >
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