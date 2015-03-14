// RecordsetEx.cpp : implementation file
//

#include "stdafx.h"

//#include "CSV.h"
//#include "StringStream.h"
#include "RecordsetEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordsetEx

LPCTSTR CRecordsetEx::useDSN = _T("(dsn)");
LPCTSTR CRecordsetEx::noDSN = _T("(none)");
LPCTSTR CRecordsetEx::driverMSSQLServer = _T("SQL Server");
LPCTSTR CRecordsetEx::driverMSAccess = _T("Microsoft Access Driver (*.mdb)");

LPCTSTR CRecordsetEx::m_szMsgCannotUpdate = _T("Error, Cannot Update the database.");
//LPCTSTR CRecordsetEx::m_szMsgCanUpdate = _T("Can Update the database.");
LPCTSTR CRecordsetEx::m_szMsgCanUpdate = _T("");
LPCTSTR CRecordsetEx::m_szMsgNotUpdated = _T("Database Unchanged.");
LPCTSTR CRecordsetEx::m_szMsgEmptyRecordset = _T("No Records Available.");

LPCTSTR CRecordsetEx::m_szNull = _T("(null)");
LPCTSTR CRecordsetEx::m_szNullField = _T("NULL");

LPCTSTR CRecordsetEx::m_szSeqId = _T("SeqId");
LPCTSTR CRecordsetEx::m_szSeqCount = _T("SeqCount");


IMPLEMENT_DYNAMIC(CRecordsetEx, CRecordset)

//CRecordsetEx::CRecordsetEx(CDatabase* pdb, CCSV csv)
CRecordsetEx::CRecordsetEx(CDatabase* pdb, LPCTSTR szCsvFieldTerminator, LPCTSTR szCsvQuotedIdentifier)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRecordsetEx)
	//m_SeriesID = 0;
	m_nFields = 0;
	//}}AFX_FIELD_INIT
	m_nDefaultType = forwardOnly;

	m_strIdentityColumn = _T("");
	m_nIdentityColumn = NULL;

	m_nIdentitySeed = 1;
	m_nIdentityIncrement = 1;

	m_strCountWhereClause = _T("");
	m_nCountMax = -1;


	m_strColumnNames = NULL;
	m_dwColumnTypes = NULL;

	//m_csv = csv;

	m_szSqlQuotedIdentifier = "'";

	m_strSqlDoubleQuotedIdentifier = (CString(m_szSqlQuotedIdentifier[0]) + m_szSqlQuotedIdentifier[0]);

	//m_strCsvFieldTerminator = csv.GetFieldTerminator();
	//m_strCsvQuotedIdentifier = csv.GetQuotedIdentifier();
	//m_strCsvDoubleQuotedIdentifier = csv.GetDoubleQuotedIdentifier();

	m_strCsvFieldTerminator = szCsvFieldTerminator;
	m_strCsvQuotedIdentifier = szCsvQuotedIdentifier;
	m_strCsvDoubleQuotedIdentifier = (CString(szCsvQuotedIdentifier[0]) + szCsvQuotedIdentifier[0]);

	m_strCsvFirstQuotedIdentifier = m_strCsvQuotedIdentifier.Left(1);
}

CString CRecordsetEx::GetDefaultConnect()
{
	return _T("");
}

CString CRecordsetEx::GetDefaultSQL()
{
	return _T("");
}

CString CRecordsetEx::GetDefaultSQL(LPCTSTR lpszTable)
{
	CString strSelect = CString(lpszTable).Left(6);

	CString strSQL;

	strSelect.MakeUpper();

	if( strSelect.Find("SELECT") < 0 )
	{
		strSQL.Format("SELECT * FROM %s ", lpszTable);
	}
	else
	{
		strSQL = lpszTable;
	}
	return _T(strSQL);

}

CString CRecordsetEx::GetDefaultSQL(LPCTSTR lpszTable, CStringArray* strColumnNames)
{
	CString strSQL = _T( "SELECT " );

	int nFields = strColumnNames->GetSize();

	for( short nIndex = 0 ; nIndex < nFields ; nIndex++ )
	{
		strSQL += _T( strColumnNames->GetAt(nIndex) );

		if( nIndex != nFields -1 )
		{
			strSQL += _T( " , " );
		}
	}

	strSQL += _T(" FROM ");
	strSQL += _T(lpszTable);

	return _T(strSQL);
}

void CRecordsetEx::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecordsetEx)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//RFX_Long(pFX, _T("[Results].[SeriesID]"), m_SeriesID);
	//}}AFX_FIELD_MAP
}

void CRecordsetEx::DoBulkFieldExchange( CFieldExchange* pFX )
{
/*
   // call the Bulk RFX functions
   // for field data members
   pFX->SetFieldType( CFieldExchange::outputColumn );
   RFX_Long_Bulk( pFX, _T( "[colRecID]" ),
                  &m_rgID, &m_rgIDLengths );
   RFX_Text_Bulk( pFX, _T( "[colName]" ),
                  &m_rgName, &m_rgNameLengths, 30 );


   // call the RFX functions for
   // for parameter data members
   pFX->SetFieldType( CFieldExchange::inputParam );
   RFX_Text( pFX, "NameParam", m_strNameParam );
*/
}


BOOL CRecordsetEx::Open( UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions )
{
	BOOL status;

	status = CRecordset::Open( nOpenType, GetDefaultSQL(lpszSQL), dwOptions );

	// m_nFields should be non zero if you extend CRecordsetEx
	if( m_nFields == 0)
	{
		m_nFields = GetODBCFieldCount( );

		// Although these 3 functions should work when you extend 
		// CRecordsetEx, some wierd problem happens.
		// But if you are extending CRecordsetEx, then you probably
		// don't want to use them anyway.

		SetColumnTypes( );
		SetColumnNames( );
		SetInsertSQL( );
	}

	return status;
}

void CRecordsetEx::AddNew( )
{
	CRecordset::AddNew( );

	if( m_nIdentityColumn != NULL )
	{
		*m_nIdentityColumn = GetNextSequence( );
	}

}


void CRecordsetEx::SetInsertSQL()
{
	m_strInsertSQL  = _T( "INSERT INTO " );
	m_strInsertSQL += _T( GetTableName() );
	m_strInsertSQL += _T( " ( " );

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		m_strInsertSQL += _T( m_strColumnNames->GetAt(nIndex) );

		if( nIndex != (int)m_nFields -1 )
		{
			m_strInsertSQL += _T( " , " );
		}
		else
		{
			m_strInsertSQL += _T( " ) " );
		}
	}

	m_strInsertSQL += _T( " VALUES ( %s ) " );

}

CString CRecordsetEx::GetInsertSQL(CStringArray* strItems) 
{

	if( strItems->GetSize( ) < (int)m_nFields )
	{
		CDBException* pDbEx;

		pDbEx = new CDBException();

		pDbEx->m_nRetCode = SQL_ERROR;
		pDbEx->m_strError = _T("Number of Items does not match the number of Fields. Cannot create INSERT SQL statement.\r\n");

		throw pDbEx;

		//AfxThrowDBException( SQL_ERROR, m_pDatabase, m_hstmt );
	}

	SetInsertSQLItems(strItems);

	m_strSQL.Format( m_strInsertSQL, m_strSQLInsertItems );

	return m_strSQL;
}

void CRecordsetEx::SetInsertSQLItems(CStringArray* strItems)
{
	m_strSQLInsertItems = "";

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		m_strSQL = strItems->GetAt( nIndex );

		if( m_strSQL.GetLength( ) < 1 )
		{
			m_strSQLInsertItems += "NULL";
		}
		else
		{
			switch( m_dwColumnTypes->GetAt( nIndex ) )
			{
				case DBVT_BOOL :
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_UCHAR :
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_SHORT :
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_LONG :
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_SINGLE :
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_DOUBLE :
					m_strSQLInsertItems += m_strSQL;
					break;

				//	For more information about the TIMESTAMP_STRUCT data
				//	type, see the topic "C Data Types" in Appendix D of 
				//	the ODBC SDK Programmer's Reference.

				case DBVT_DATE :
					m_strSQLInsertItems += m_szSqlQuotedIdentifier;
					m_strSQLInsertItems += m_strSQL;
					m_strSQLInsertItems += m_szSqlQuotedIdentifier;
					break;

				case DBVT_STRING :
					if( m_strSQL.FindOneOf( m_szSqlQuotedIdentifier ) > -1 )
					{
						m_strSQL.Replace(m_szSqlQuotedIdentifier, m_strSqlDoubleQuotedIdentifier);
					}

					m_strSQLInsertItems += m_szSqlQuotedIdentifier;
					m_strSQLInsertItems += m_strSQL;
					m_strSQLInsertItems += m_szSqlQuotedIdentifier;

					break;

				case DBVT_BINARY :
					if( m_strSQL.Left(2).CompareNoCase( "0x" ) != 0 )
					{
						m_strSQLInsertItems += "0x";
					}
					m_strSQLInsertItems += m_strSQL;
					break;

				case DBVT_NULL :
					break;

			}
		}

		if( nIndex != (int)m_nFields -1 )
		{
			m_strSQLInsertItems += _T( " , " );
		}
	}

}


CDWordArray* CRecordsetEx::GetColumnTypes()
{
//	DWORD dwType == DBVT_NULL ;
//	DWORD dwType == DBVT_BOOL ;
//	DWORD dwType == DBVT_UCHAR ;
//	DWORD dwType == DBVT_SHORT ;
//	DWORD dwType == DBVT_LONG ;
//	DWORD dwType == DBVT_SINGLE ;
//	DWORD dwType == DBVT_DOUBLE ;
//	DWORD dwType == DBVT_DATE ;
//	DWORD dwType == DBVT_STRING ;
//	DWORD dwType == DBVT_BINARY ;

	return m_dwColumnTypes;
}

void CRecordsetEx::SetColumnTypes()
{
	CODBCFieldInfo fieldInfo;
	DWORD dwType ;

	if( m_dwColumnTypes != NULL )
	{
		m_dwColumnTypes->RemoveAll( );
	}
	else
	{
		m_dwColumnTypes = new CDWordArray();
	}

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		GetODBCFieldInfo( nIndex, fieldInfo );

		switch(fieldInfo.m_nSQLType)
		{
			//	Character Strings

			case SQL_CHAR :
			case SQL_VARCHAR :
			case SQL_LONGVARCHAR :
				dwType = DBVT_STRING ;
				break;

			//	Unicode Character Strings

			case SQL_WCHAR :
			case SQL_WVARCHAR :
			case SQL_WLONGVARCHAR :
				dwType = DBVT_STRING ;
				break;

			//	Integers

			case SQL_BIT :
				dwType = DBVT_BOOL ;
				break;

			case SQL_BIGINT :
			case SQL_INTEGER :
				dwType = DBVT_LONG ;
				break;
			case SQL_SMALLINT :
			case SQL_TINYINT :
				dwType = DBVT_SHORT ;
				break;

			//	decimal and numeric

			case SQL_DECIMAL :
			case SQL_NUMERIC :
				dwType = DBVT_DOUBLE ;
				break;

			//	Approximate Numerics

			case SQL_REAL :
			case SQL_FLOAT :
				dwType = DBVT_SINGLE ;
				break;
			case SQL_DOUBLE :
				dwType = DBVT_DOUBLE ;
				break;

			//	Binary Strings

			case SQL_BINARY :
			case SQL_VARBINARY :
			case SQL_LONGVARBINARY :
				dwType = DBVT_BINARY ;
				break;

			//	Numerics

			//	globally unique identifier

			case SQL_GUID :
				dwType = DBVT_BINARY ;
				break;

			//	datetime and smalldatetime

			case SQL_DATE :
			case SQL_TIME :
			case SQL_TIMESTAMP :
				dwType = DBVT_DATE ;
				break;

			case SQL_TYPE_DATE :
			case SQL_TYPE_TIME :
			case SQL_TYPE_TIMESTAMP :
				dwType = DBVT_DATE ;
				break;

			case SQL_INTERVAL_MONTH :
			case SQL_INTERVAL_YEAR :
			case SQL_INTERVAL_YEAR_TO_MONTH :
			case SQL_INTERVAL_DAY :
			case SQL_INTERVAL_HOUR :
			case SQL_INTERVAL_MINUTE :
			case SQL_INTERVAL_SECOND :
			case SQL_INTERVAL_DAY_TO_HOUR :
			case SQL_INTERVAL_DAY_TO_MINUTE :
			case SQL_INTERVAL_DAY_TO_SECOND :
			case SQL_INTERVAL_HOUR_TO_MINUTE :
			case SQL_INTERVAL_HOUR_TO_SECOND :
			case SQL_INTERVAL_MINUTE_TO_SECOND :
				dwType = DBVT_DATE ;
				break;

			default : 
				dwType = DBVT_NULL ;
				break;

		}

		m_dwColumnTypes->Add( dwType );
	}
}


void CRecordsetEx::SetColumnNames()
{
	CODBCFieldInfo fieldInfo;

	if( m_strColumnNames != NULL )
	{
		m_strColumnNames->RemoveAll();
	}
	else
	{
		m_strColumnNames = new CStringArray();
	}

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		GetODBCFieldInfo( nIndex, fieldInfo );

		m_strColumnNames->Add( fieldInfo.m_strName );
	}
}

CStringArray* CRecordsetEx::GetColumnNames() const
{
	return m_strColumnNames;
}

CString* CRecordsetEx::GetCSVColumnNames(CString* strRow)
{
	strRow->Empty();

	int nFields = m_strColumnNames->GetSize();

	for( int nIndex = 0 ; nIndex < nFields ; nIndex++ )
	{
		*strRow += m_strColumnNames->GetAt(nIndex);

		if( nIndex != nFields -1 )
		{
			*strRow += _T( m_strCsvFieldTerminator[0] );
		}
	}
	return strRow;
}

CStringArray* CRecordsetEx::GetRow(CStringArray* strItems)
{
	strItems->RemoveAll( );

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		GetFieldValue( nIndex, m_strValue );
		strItems->Add( _T( m_strValue ) );


		//GetFieldValue( nIndex, m_varValue );

		//m_strStream.Flush( );
		//m_strStream << m_varValue;

		//strItems->Add( _T( m_strStream ) );
	}

	return strItems;
}

CString* CRecordsetEx::GetCSVRow(CString* strRow)
{
	strRow->Empty();

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		GetFieldValue( nIndex, m_strValue );

		switch( m_dwColumnTypes->GetAt( nIndex ) )
		{
			case DBVT_BOOL :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_UCHAR :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_SHORT :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_LONG :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_SINGLE :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_DOUBLE :
				*strRow += (LPCTSTR)m_strValue;
				break;

			//	For more information about the TIMESTAMP_STRUCT data
			//	type, see the topic "C Data Types" in Appendix D of 
			//	the ODBC SDK Programmer's Reference.

			case DBVT_DATE :
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_STRING :
				if( m_strValue.FindOneOf( m_strCsvQuotedIdentifier ) < 0 &&
					m_strValue.FindOneOf( m_strCsvFieldTerminator )  < 0 )
				{
					*strRow += (LPCTSTR)m_strValue;
				}
				else
				{
					m_strValue.Replace(m_strCsvFirstQuotedIdentifier, m_strCsvDoubleQuotedIdentifier);

					*strRow += m_strCsvQuotedIdentifier[0];
					*strRow += (LPCTSTR)m_strValue;
					*strRow += m_strCsvQuotedIdentifier[0];
				}
				break;

			case DBVT_BINARY :
				//*strRow += "0x";
				*strRow += (LPCTSTR)m_strValue;
				break;

			case DBVT_NULL :
				break;
		}

		if( nIndex != (int)m_nFields -1 )
		{
			*strRow += _T( m_strCsvFieldTerminator[0] );
		}
	}

	return strRow;
}

CString CRecordsetEx::Describe()
{
	// Describes the Columns of a CRecordset object,

	// NOTE: we can still get the Column Descriptions
	// even if the CRecordset has no rows. 

	// For a list of valid ODBC SQL data types, 
	// see "SQL Data Types" in Appendix D of the 
	// ODBC SDK Programmer's Reference

	// Using Binary Data
	// The SQL_BINARY and SQL_VARBINARY data types store strings of bits. 
	// Binary constants have a leading 0x (a zero and the lowercase letter x) 
	// followed by the hexadecimal representation of the bit pattern. 
	// For example, 0x2A specifies the hexadecimal value of 2A, which 
	// is equivalent to a decimal value of 42 or a one-byte bit pattern of 00101010.
	//
	// INSERT INTO SecurityPerson
	// VALUES ( 7777, 'woof', 
	//          0x180000004441522023029B9E8FA7BB3E9534ED0351733724 );
	//
	// note that if no columns are specified in the INSERT statement
	// the VALUES must be in the same order as the columns in the table 

	CODBCFieldInfo fieldInfo;

	CString strDescribe;
	CString strType;

	strDescribe.Format("CREATE TABLE %s ( \r\n", GetTableName() );

	for( short nIndex = 0 ; nIndex < (int)m_nFields ; nIndex++ )
	{
		GetODBCFieldInfo( nIndex, fieldInfo );

		switch(fieldInfo.m_nSQLType)
		{
			//	Character Strings

			case SQL_CHAR :
				strType.Format("CHAR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_VARCHAR :
				strType.Format("VARCHAR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_LONGVARCHAR :
				strType.Format("LONG VARCHAR");
				break;

			//	Unicode Character Strings

			case SQL_WCHAR :
				strType.Format("NCHAR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_WVARCHAR :
				strType.Format("NVARCHAR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_WLONGVARCHAR :
				strType.Format("LONG NVARCHAR");
				break;

			//	Integers

			case SQL_BIT :
				strType.Format("BIT");
				break;

			case SQL_BIGINT :
				strType.Format("BIGINT");
				break;
			case SQL_INTEGER :
				strType.Format("INT");
				break;
			case SQL_SMALLINT :
				strType.Format("SMALLINT");
				break;
			case SQL_TINYINT :
				strType.Format("TINYINT");
				break;

			//	decimal and numeric

			case SQL_DECIMAL :
				strType.Format("DECIMAL(%d,%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;
			case SQL_NUMERIC :
				strType.Format("NUMERIC(%d,%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;

			//	Approximate Numerics

			case SQL_REAL :
				strType.Format("REAL");
				break;
			case SQL_FLOAT :
				strType.Format("FLOAT(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_DOUBLE :
				strType.Format("DOUBLE PRECISION");
				break;

			//	Binary Strings

			case SQL_BINARY :
				strType.Format("BINARY(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_VARBINARY :
				strType.Format("VARBINARY(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_LONGVARBINARY :
				strType.Format("LONG VARBINARY(%d)", fieldInfo.m_nPrecision );
				break;

			//	Numerics

			//	globally unique identifier

			case SQL_GUID :
				strType.Format("GUID" ); 
				break;

			//	datetime and smalldatetime

			case SQL_DATE :
			case SQL_TYPE_DATE :
			case SQL_TIME :
			case SQL_TYPE_TIME :
			case SQL_TIMESTAMP :
			case SQL_TYPE_TIMESTAMP :
				strType.Format("DATETIME");
				break;
			case SQL_INTERVAL_MONTH :
				strType.Format("INTERVAL MONTH(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_YEAR :
				strType.Format("INTERVAL YEAR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_YEAR_TO_MONTH :
				strType.Format("INTERVAL YEAR(%d) TO MONTH", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_DAY :
				strType.Format("INTERVAL DAY(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_HOUR :
				strType.Format("INTERVAL HOUR(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_MINUTE :
				strType.Format("INTERVAL MINUTE(%d)", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_SECOND :
				strType.Format("INTERVAL SECOND(%d,%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;
			case SQL_INTERVAL_DAY_TO_HOUR :
				strType.Format("INTERVAL DAY(%d) TO HOUR", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_DAY_TO_MINUTE :
				strType.Format("INTERVAL DAY(%d) TO MINUTE", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_DAY_TO_SECOND :
				strType.Format("INTERVAL DAY(%d) TO SECOND(%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;
			case SQL_INTERVAL_HOUR_TO_MINUTE :
				strType.Format("INTERVAL HOUR(%d) TO MINUTE", fieldInfo.m_nPrecision );
				break;
			case SQL_INTERVAL_HOUR_TO_SECOND :
				strType.Format("INTERVAL HOUR(%d) TO SECOND(%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;
			case SQL_INTERVAL_MINUTE_TO_SECOND :
				strType.Format("INTERVAL MINUTE(%d) TO SECOND(%d)", fieldInfo.m_nPrecision, fieldInfo.m_nScale );
				break;
		}

		strType += " \t";

		switch(fieldInfo.m_nNullability)
		{
			case SQL_NULLABLE :
				strType += "NULL";
				break;
			case SQL_NO_NULLS :
				strType += "NOT NULL";
				break;
		}

		if( nIndex != (int)m_nFields -1 )
		{
			strType += " , ";
		}

		strDescribe += " \t";
		strDescribe += fieldInfo.m_strName;
		strDescribe += " \t";
		strDescribe += strType;
		strDescribe += " \r\n";
	}
	strDescribe += " ) \r\n";

	return _T(strDescribe);
}


CString CRecordsetEx::GetDefaultConnect(LPCTSTR strServer,
										LPCTSTR strUID,
										LPCTSTR strPWD,
										LPCTSTR strDatabase,
										LPCTSTR strDriver,
										LPCTSTR strDSN,
										BOOL bTrusted)
{
	CString strConnect = _T("");

	if ( _tcscmp(strDSN, CRecordsetEx::noDSN) || 
		!_tcscmp(strDriver, CRecordsetEx::useDSN) ) // ODBC32 Data Sources (Control Panel)
	{
//		creates a ConnectString of the form: "DSN=WebAthletics;UID=sa;PWD=;"
		strConnect += _T("DSN=");
		strConnect += _T(strDSN);
		strConnect += _T(";");
	}
	else if (!_tcscmp(strDriver, CRecordsetEx::driverMSSQLServer))
	{
//		creates a ConnectString of the form: "DRIVER={SQL Server};SERVER=QONOS;DATABASE=athletics;UID=sa;PWD=;"
		strConnect += _T("DRIVER={");
		strConnect += _T(strDriver);
		strConnect += _T("};SERVER=");
		strConnect += _T(strServer);
		strConnect += _T(";DATABASE=");
		strConnect += _T(strDatabase);
		strConnect += _T(";");
	}
	else if (!_tcscmp(strDriver, CRecordsetEx::driverMSAccess))
	{
		TCHAR pszDrive[_MAX_PATH];
		TCHAR pszDir[_MAX_PATH];
		TCHAR pszFileName[_MAX_PATH];
		TCHAR pszExt[_MAX_PATH];

		TCHAR pszPath[_MAX_PATH];
		TCHAR pszFilePath[_MAX_PATH];

		_tfullpath( pszFilePath, strDatabase, _MAX_PATH );
		_tsplitpath( pszFilePath, pszDrive, pszDir, pszFileName, pszExt );
		wsprintf(pszPath, "%s%s", pszDrive, pszDir);

//		creates a ConnectString of the form: "DRIVER={Microsoft Access Driver (*.mdb)};DefaultDir=c:\Athletics\ACTVAC;DBQ=c:\Athletics\ACTVAC\db2.mdb;UID=sa;PWD=;"

		strConnect += _T("DRIVER={");
		strConnect += _T(strDriver);
		strConnect += _T("};DefaultDir=");
		strConnect += _T(pszPath);
		strConnect += _T(";DBQ=");
		strConnect += _T(pszFilePath);
		strConnect += _T(";");
	}


    if(bTrusted)
	{
		strConnect += "Trusted Connection=TRUE;";
	}
	else
	{
		strConnect += "UID=" ;
		strConnect += strUID ;
		strConnect += ";" ;

		strConnect += "PWD=";
		strConnect += strPWD ;
		strConnect += ";" ;
	}

	return _T(strConnect);
}


int CRecordsetEx::GetODBCDrivers(CStringArray* strDescription, CStringArray* strAttributes)
{
	return GetODBC(strDescription, strAttributes, CRecordsetEx::getDrivers);
}

int CRecordsetEx::GetODBCDataSources(CStringArray* strDescription, CStringArray* strAttributes)
{
	return GetODBC(strDescription, strAttributes, CRecordsetEx::getDataSources);
}

int CRecordsetEx::GetODBC(CStringArray* strDescription, CStringArray* strAttributes, DWORD dwType)
{
	SQLHENV hEnv;
	SQLRETURN status;

	SQLSMALLINT dDescriptionLen;
	SQLSMALLINT dAttributesLen;
	SQLCHAR szDescription[1024];
	SQLCHAR szAttributes[1024];

	int dItems = 0;

	//status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) ;
	status = SQLAllocEnv(&hEnv);

	if( status == SQL_SUCCESS )
	{
		while( status == SQL_SUCCESS )
		{
			if ( dwType == CRecordsetEx::getDataSources )
			{
				status = SQLDataSources(
					hEnv, SQL_FETCH_NEXT,
					szDescription, sizeof(szDescription), &dDescriptionLen,
					szAttributes,  sizeof(szAttributes), &dAttributesLen
				);
			}
			else if ( dwType == CRecordsetEx::getDrivers )
			{
				status = SQLDrivers(
					hEnv, SQL_FETCH_NEXT,
					szDescription, sizeof(szDescription), &dDescriptionLen,
					szAttributes,  sizeof(szAttributes), &dAttributesLen
				);
			}
			else 
			{
				return -1;
			}

			if( status == SQL_SUCCESS)
			{
				dItems++;

				if ( dwType == CRecordsetEx::getDrivers )
				{
					// '\0' seperated list of attributes, "\0\0" terminated.

					for( SQLSMALLINT i = 0; i < dAttributesLen ; i++ )
					{
						if( szAttributes[i] == '\0' )
							szAttributes[i]  = ';';

					}
				}
				strAttributes->Add( szAttributes );
				strDescription->Add( szDescription );
			}
		}

		//SQLFreeHandle( SQL_HANDLE_ENV, hEnv );
		SQLFreeEnv( hEnv );
	}
	return dItems;
}

void CRecordsetEx::SetCountWhereClause( CString strWhereClause )
{
	m_strCountWhereClause = strWhereClause;
}

CString CRecordsetEx::GetCountMessage( )
{
	if( m_strCountMessage.GetLength( ) > 0 )
	{
		return m_strCountMessage;
	}
	else
	{
		return _T("Maximum Row Count Reached.\r\n");
	}
}

void CRecordsetEx::SetCountMessage( CString strCountMessage )
{
	m_strCountMessage = strCountMessage;
}

BOOL CRecordsetEx::HasMaxCountReached( BOOL bAboutToAdd )
{
	if( m_nCountMax > 0 )
	{
		long nCountMax = m_nCountMax;

		if( !bAboutToAdd )
		{
			nCountMax++;
		}

		if( GetCountSequence( m_strCountWhereClause ) >= nCountMax )
		{
			CDBException* pDbEx;

			pDbEx = new CDBException();

			pDbEx->m_nRetCode = SQL_ERROR;
			pDbEx->m_strError = GetCountMessage( );

			throw pDbEx;
		}
	}

	return FALSE;
}

long CRecordsetEx::GetCountSequence( LPCTSTR szWhereClause )
{
	long nSeqCount;

	CString strSQL;
	CString strValue;

	CRecordset rs( m_pDatabase );


	strSQL.Format( _T("SELECT COUNT(*) AS %s FROM %s "), 
		CRecordsetEx::m_szSeqCount, 
		GetTableName( ) 
	);

	if( szWhereClause != NULL )
	{
		if( _tcslen(szWhereClause) > 0 )
		{
			strSQL += _T(szWhereClause);
		}
	}

	rs.Open(CRecordset::forwardOnly, strSQL );

	rs.GetFieldValue( CRecordsetEx::m_szSeqCount, strValue );
	nSeqCount = atol( strValue );

	rs.Close( );

	return nSeqCount;
}

long CRecordsetEx::GetNextSequence( )
{
	long nSeqId;
	long nSeqCount;

	CString strSQL;
	CString strValue;

	if( !m_strIdentityColumn.IsEmpty( ) )
	{
		CRecordset rs( m_pDatabase );

		nSeqCount = GetCountSequence( );

		if( nSeqCount > 0 )
		{
			strSQL.Format( _T("SELECT MAX(%s) + %d AS %s FROM %s"), 
				m_strIdentityColumn, 
				m_nIdentityIncrement, 
				CRecordsetEx::m_szSeqId, 
				GetTableName( ) 
			);

			rs.Open(CRecordset::forwardOnly, strSQL );

			rs.GetFieldValue( CRecordsetEx::m_szSeqId, strValue );
			nSeqId = atol( strValue );

			rs.Close( );
		}
		else
		{
			nSeqId = m_nIdentitySeed;
		}
	}
	else
	{
		nSeqId = 0;
	}

	return nSeqId;
}


// As defined in : AFXDB_.H
//
// short			AFX_RFX_SHORT_PSEUDO_NULL == (0x7EE4)
// int				AFX_RFX_INT_PSEUDO_NULL == (0x7EE4)
// long				AFX_RFX_LONG_PSEUDO_NULL == (0x4a4d4120L)
// BYTE				AFX_RFX_BYTE_PSEUDO_NULL == 255
// CByteArray[0]	AFX_RFX_BYTE_PSEUDO_NULL == 255
// float			AFX_RFX_SINGLE_PSEUDO_NULL == (-9.123e19f)
// double			AFX_RFX_DOUBLE_PSEUDO_NULL == (-9.123e19)
// BOOL				AFX_RFX_BOOL_PSEUDO_NULL == 2
// CTime			AFX_RFX_DATE_PSEUDO_NULL == CTime(0)
// TIMESTAMP_STRUCT	AFX_RFX_TIMESTAMP_PSEUDO_NULL == 99
//

BOOL CRecordsetEx::IsItemNull(short& value)
{
	return (AFX_RFX_SHORT_PSEUDO_NULL == value);
}
BOOL CRecordsetEx::IsItemNull(int& value)
{
//	return (AFX_RFX_INT_PSEUDO_NULL == value);

	long nValue = value;

	return IsItemNull( nValue );
}
BOOL CRecordsetEx::IsItemNull(long& value)
{
	return (AFX_RFX_LONG_PSEUDO_NULL == value);
}
BOOL CRecordsetEx::IsItemNull(BYTE& value)
{
	return (AFX_RFX_BYTE_PSEUDO_NULL == value);
}
BOOL CRecordsetEx::IsItemNull(CByteArray& value)
{
	if( value.GetSize() == 1 )
		return (AFX_RFX_BYTE_PSEUDO_NULL == value[0]);
	else
		return FALSE;
}
BOOL CRecordsetEx::IsItemNull(float& value)
{
	return (AFX_RFX_SINGLE_PSEUDO_NULL == value);
}
BOOL CRecordsetEx::IsItemNull(double& value)
{
	return (AFX_RFX_DOUBLE_PSEUDO_NULL == value);
}
BOOL CRecordsetEx::IsItemNull(CTime& value)
{
	CTime timeNull = AFX_RFX_DATE_PSEUDO_NULL;

	return (timeNull == value);
}
BOOL CRecordsetEx::IsItemNull(TIMESTAMP_STRUCT& value)
{
	return ( (value.year == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.month == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.day == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.hour == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.minute == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.second == AFX_RFX_TIMESTAMP_PSEUDO_NULL) &&
			 (value.fraction == AFX_RFX_TIMESTAMP_PSEUDO_NULL) );
}
BOOL CRecordsetEx::IsBoolItemNull(BOOL& value)
{
	return (AFX_RFX_BOOL_PSEUDO_NULL == value);
}

void CRecordsetEx::GetNullItem(short* pValue)
{
	*pValue = AFX_RFX_SHORT_PSEUDO_NULL;
}
void CRecordsetEx::GetNullItem(int* pValue)
{
//	*pValue = AFX_RFX_INT_PSEUDO_NULL;

	long nValue;
	
	GetNullItem( &nValue );

	*pValue = nValue;
}
void CRecordsetEx::GetNullItem(long* pValue)
{
	*pValue = AFX_RFX_LONG_PSEUDO_NULL;
}
void CRecordsetEx::GetNullItem(BYTE* pValue)
{
	*pValue = AFX_RFX_BYTE_PSEUDO_NULL;
}
void CRecordsetEx::GetNullItem(CByteArray* pValue)
{
	pValue->RemoveAll( );
	pValue->Add( AFX_RFX_BYTE_PSEUDO_NULL );
}
void CRecordsetEx::GetNullItem(float* pValue)
{
	*pValue = AFX_RFX_SINGLE_PSEUDO_NULL;
}
void CRecordsetEx::GetNullItem(double* pValue)
{
	*pValue = AFX_RFX_DOUBLE_PSEUDO_NULL;
}
void CRecordsetEx::GetNullItem(CTime* pValue)
{
	CTime timeNull = AFX_RFX_DATE_PSEUDO_NULL;

	*pValue = timeNull;
}
void CRecordsetEx::GetNullItem(TIMESTAMP_STRUCT* pValue)
{
	pValue->year = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->month = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->day = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->hour = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->minute = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->second = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
	pValue->fraction = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
}
void CRecordsetEx::GetNullBoolItem(BOOL* pValue)
{
	*pValue = AFX_RFX_BOOL_PSEUDO_NULL;
}


BOOL CRecordsetEx::TestConnect(LPCTSTR szConnect, CString* strError)
{
	BOOL bStatus = FALSE;

 	try
	{
		CDatabase db;

		db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );
		db.Close( );

		bStatus = TRUE;
	}

	catch (CDBException* pEx)
	{
		if( strError != NULL )
		{
			strError->Format("%s", pEx->m_strError);
		}

		pEx->Delete();
	}

	return bStatus;
}


/////////////////////////////////////////////////////////////////////////////
// CRecordsetEx diagnostics

#ifdef _DEBUG
void CRecordsetEx::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetEx::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
