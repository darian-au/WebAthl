#if !defined(AFX_RECORDSETEX_H__INCLUDED_)
#define AFX_RECORDSETEX_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RecordsetEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordsetEx recordset

class CRecordsetEx : public CRecordset
{
// Constructor
	public:
//	CRecordsetEx(CDatabase* pDatabase = NULL, CCSV csv = CCSV( "," , "\"" ) );
	CRecordsetEx(CDatabase* pDatabase = NULL, LPCTSTR szCsvFieldTerminator = ",", LPCTSTR szCsvQuotedIdentifier = "\"" );
	//CRecordsetEx(CDatabase* pDatabase = NULL );
	DECLARE_DYNAMIC(CRecordsetEx)

// Destructor

	//
	// Using Destructors
	//
	// ...
	//
	// If a base class or data member has an accessible destructor,
	// and if a derived class does not declare a destructor, the 
	// compiler generates one. This compiler-generated destructor 
	// calls the base class destructor and the destructors for members 
	// of the derived type. Default destructors are public. 


// Field/Param Data
	//{{AFX_FIELD(CRecordsetEx, CRecordset)
	//long	m_SeriesID;
	//}}AFX_FIELD

// Member variables
	public:

	// Static variables
	static enum GetDataSourcesOrDrivers { getDataSources, getDrivers };

	static LPCTSTR useDSN;
	static LPCTSTR noDSN;
	static LPCTSTR driverMSSQLServer;
	static LPCTSTR driverMSAccess;

	static LPCTSTR m_szMsgCannotUpdate;
	static LPCTSTR m_szMsgCanUpdate;
	static LPCTSTR m_szMsgNotUpdated;
	static LPCTSTR m_szMsgEmptyRecordset;

	static LPCTSTR m_szNull;
	static LPCTSTR m_szNullField;

	private:
	static LPCTSTR m_szSeqId;
	static LPCTSTR m_szSeqCount;

	public:
	CString m_strIdentityColumn;
	long m_nIdentitySeed;
	long m_nIdentityIncrement;

	long* m_nIdentityColumn;

	CString m_strCountMessage;
	CString m_strCountWhereClause;
	long m_nCountMax;

	private:
	//CCSV m_csv;
	CString m_strCsvFieldTerminator;
	CString m_strCsvQuotedIdentifier;
	CString m_strCsvDoubleQuotedIdentifier;
	CString m_strCsvFirstQuotedIdentifier;

	LPCTSTR m_szSqlQuotedIdentifier;
	CString m_strSqlDoubleQuotedIdentifier;

	CDWordArray* m_dwColumnTypes;

	CStringArray* m_strColumnNames;

	CString m_strInsertSQL;

	// These two are temporary Strings just for
	// creating and executing the Insert SQL.
	CString m_strSQL;
	CString m_strSQLInsertItems;

	// These two are temporary Strings just for
	// getting fields from the rowset.
	CDBVariant m_varValue;
	CString m_strValue;

	//CStringStream m_strStream;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordsetEx)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual void DoBulkFieldExchange( CFieldExchange* pFX ); // Bulk RFX support
	//}}AFX_VIRTUAL

// Overrides
	public:
	virtual BOOL Open( UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, DWORD dwOptions = none );

	virtual void AddNew( );


// Overloads
	public:
	static CString GetDefaultSQL(LPCTSTR lpszTable);
	static CString GetDefaultSQL(LPCTSTR lpszTable, CStringArray* strColumnNames);

// Implementation

	private:
	void SetColumnTypes();
	void SetColumnNames();
	void SetInsertSQL();
	void SetInsertSQLItems(CStringArray* strItems);

	public:
	CStringArray* CRecordsetEx::GetColumnNames() const;
	CStringArray* GetRow(CStringArray* strItems = new CStringArray() );

	CString Describe();
	CString* GetCSVRow(CString* strRow = new CString() );
	CString* GetCSVColumnNames(CString* strRow = new CString() );
	CDWordArray* GetColumnTypes();

	BOOL HasMaxCountReached( BOOL bAboutToAdd = FALSE );
	long GetCountSequence( LPCTSTR szWhereClause = NULL );
	long GetNextSequence( );
	virtual CString GetCountMessage( );
	virtual void SetCountWhereClause( CString strWhereClause );
	virtual void SetCountMessage( CString strCountMessage );



	virtual CString GetInsertSQL(CStringArray* strItems) ;

	static CString GetDefaultConnect(LPCTSTR strServer,
									 LPCTSTR strUID,
									 LPCTSTR strPWD,
									 LPCTSTR strDatabase,
									 LPCTSTR strDriver,
									 LPCTSTR strDSN,
									 BOOL bTrusted);

	static int GetODBC(CStringArray* strDescription, 
					   CStringArray* strAttributes,
					   DWORD dwType );

	static int GetODBCDrivers(CStringArray* strDescription, 
							  CStringArray* strAttributes);

	static int GetODBCDataSources(CStringArray* strDescription, 
								  CStringArray* strAttributes);

	static BOOL IsItemNull(short& value);
	static BOOL IsItemNull(int& value);
	static BOOL IsItemNull(long& value);
	static BOOL IsItemNull(BYTE& value);
	static BOOL IsItemNull(CByteArray& value);
	static BOOL IsItemNull(float& value);
	static BOOL IsItemNull(double& value);
	static BOOL IsItemNull(CTime& value);
	static BOOL IsItemNull(TIMESTAMP_STRUCT& value);
	static BOOL IsBoolItemNull(BOOL& value);

	static void GetNullItem(short* pValue);
	static void GetNullItem(int* pValue);
	static void GetNullItem(long* pValue);
	static void GetNullItem(BYTE* pValue);
	static void GetNullItem(CByteArray* pValue);
	static void GetNullItem(float* pValue);
	static void GetNullItem(double* pValue);
	static void GetNullItem(CTime* pValue);
	static void GetNullItem(TIMESTAMP_STRUCT* pValue);
	static void GetNullBoolItem(BOOL* pValue);

	static BOOL TestConnect(LPCTSTR szConnect, CString* strError = NULL);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDSETEX_H__INCLUDED_)
