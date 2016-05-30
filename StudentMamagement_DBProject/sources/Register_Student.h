// Register_Student.h : Declaration of the CRegister_Student

#pragma once

// code generated on 2014년 6월 20일 금요일, 오후 10:07
// 100835 한승환
class CRegister_StudentAccessor
{
public:




	LONG m_RETURN_VALUE;
	LONG m_SID;
	LONG m_PASSWORD;
	TCHAR m_GENDER[21];
	TCHAR m_MAJOR[21];
	LONG m_Curri_Year;
	TCHAR m_Phone_Number[21];
	TCHAR m_SNAME[21];
	TCHAR m_ADDERSS[21];

	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
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

	DEFINE_COMMAND_EX(CRegister_StudentAccessor, L"{ ? = CALL dbo.Register_Student(?,?,?,?,?,?,?,?) }")


	BEGIN_PARAM_MAP(CRegister_StudentAccessor)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY(1, m_RETURN_VALUE)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(2, m_SID)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(3, m_PASSWORD)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(4, m_GENDER)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(5, m_MAJOR)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(6, m_Curri_Year)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(7, m_Phone_Number)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(8, m_SNAME)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(9, m_ADDERSS)
	END_PARAM_MAP()
};
template <class T>
class CRegister_Student : public CCommand<CAccessor<T>, CNoRowset >
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