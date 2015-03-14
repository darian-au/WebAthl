// CBulkCopy.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "BulkCopy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBulkCopy



/////////////////////////////////////////////////////////////////////////////
// Constructor
CBulkCopy::CBulkCopy(CStringStream* strLog,
					 CStringStream* strErr,
					 LPCTSTR szUsername,
					 LPCTSTR szPassword,
					 bool bTrustedConnection,
					 LPCTSTR szDSN,
					 LPCTSTR szServer,
					 LPCTSTR szDatabase,
					 LPCTSTR szDriver,
					 bool bFirstRowIsColumnNames,
					 bool bHtml,
					 LPCTSTR szQuotedIdentifier,
					 LPCTSTR szFieldTerminator,
					 //LPCTSTR szRowTerminator,
					 LPCTSTR szOutputFileName,
					 LPCTSTR szInputFileName,
					 LPCTSTR szQueryString,
					 int dRowCountMark,
					 bool bRowCountMark,
					 LPCTSTR szConfigSQL)
{
	m_strLog = strLog;
	m_strErr = strErr;

	m_szUsername = szUsername;
	m_szPassword = szPassword;

	m_bTrustedConnection = bTrustedConnection;

	m_szDSN = szDSN;

	m_szServer = szServer;
	m_szDatabase = szDatabase;
	m_szDriver = szDriver;

	m_bFirstRowIsColumnNames = bFirstRowIsColumnNames;

	m_bHtml = bHtml;

	m_szQuotedIdentifier = szQuotedIdentifier;

	m_szFieldTerminator = szFieldTerminator;
	//m_szRowTerminator = szRowTerminator;

	m_szOutputFileName = szOutputFileName;
	m_szInputFileName = szInputFileName;

	m_szQueryString = szQueryString;

	m_dRowCountMark = dRowCountMark;
	m_bRowCountMark = bRowCountMark;

	m_szConfigSQL = szConfigSQL;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CBulkCopy::~CBulkCopy()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

long CBulkCopy::FileCopy()
{
	if( (m_szOutputFileName == NULL) || (m_szInputFileName == NULL) )
	{
		return -1;
	}

	m_dSuccessRecordCount = 0L;
	m_dFailRecordCount = 0L;

	// File Copy mode, no ODBC

	CStdioFile inFile( m_szInputFileName,
		CFile::modeRead | CFile::typeText );

	CStdioFile outFile( m_szOutputFileName,
		CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	*m_strLog << m_strLog->endl() << _T("Starting copy...") << m_strLog->endl();
	m_strLog->Flush();

	m_timeStart = clock();

	CCSV csv(m_szFieldTerminator, m_szQuotedIdentifier);

	CString strLine;
	CString strRow;

	CStringArray* strItems;
	strItems = new CStringArray();

	if( m_bHtml )
		outFile.WriteString( "<table>\n" ) ;

	if( m_bFirstRowIsColumnNames )
	{
		if( inFile.ReadString( strLine ) )
		{
			csv.GetItems(strItems, &strLine);

			if( m_bHtml )
				outFile.WriteString( csv.FormatHtmlItems(strItems, true) ) ;
			else
				outFile.WriteString( *(csv.GetCSVRow(strItems, &strRow)) ) ;

			outFile.WriteString( "\n" ) ;

			strItems->RemoveAll( );

			csv.SetRecordCount( );
		}
	}

	int dRowCount = 0;

	while( inFile.ReadString( strLine ) )
	{
		csv.GetItems(strItems, &strLine);

		if( m_bHtml )
			outFile.WriteString( csv.FormatHtmlItems(strItems) ) ;
		else
			outFile.WriteString( *(csv.GetCSVRow(strItems, &strRow)) ) ;

		outFile.WriteString( "\n" ) ;

		strItems->RemoveAll( );

		if( m_bRowCountMark && ((++dRowCount) % m_dRowCountMark) == 0)
		{
			cout << '.' ;
		}

	}

	if( m_bHtml )
		outFile.WriteString( "</table>\n" ) ;

	m_dSuccessRecordCount = csv.GetRecordCount( true );
	m_dFailRecordCount = csv.GetRecordCount( ) - csv.GetRecordCount( true );

	m_timeStop = clock();

	strItems->RemoveAll( );
	strItems->FreeExtra( );
	delete strItems;

	inFile.Close( );
	outFile.Close( );

	return m_dSuccessRecordCount;
}

long CBulkCopy::DatabaseCopyOut()
{
	if( m_szOutputFileName == NULL )
	{
		return -1;
	}

	m_dSuccessRecordCount = 0L;
	m_dFailRecordCount = 0L;

	// ODBC OUT mode

	CStdioFile outFile( m_szOutputFileName,
		CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	CString strConnectString = CRecordsetEx::GetDefaultConnect(
		m_szServer,m_szUsername,m_szPassword,m_szDatabase,m_szDriver,m_szDSN,m_bTrustedConnection);

	CDatabase db;
	db.OpenEx( strConnectString , CDatabase::noOdbcDialog );

	//db.OpenEx( strConnectString );
	//strLog << (LPCTSTR)db.GetConnect( ) << strLog.endl();

	CCSV csv(m_szFieldTerminator, m_szQuotedIdentifier);

	//CRecordsetEx rs( &db, csv );
	CRecordsetEx rs( &db, m_szFieldTerminator, m_szQuotedIdentifier );

	rs.Open(CRecordset::forwardOnly, m_szQueryString );

	//rs.SetRowsetSize( 100 );
	//rs.Open(CRecordset::snapshot, szQueryString, 
	//	CRecordset::useMultiRowFetch | CRecordset::readOnly );

	*m_strLog << m_strLog->endl() << _T("Starting copy...") << m_strLog->endl();
	m_strLog->Flush();

	m_timeStart = clock();

	CString strRow;

	CStringArray* strItems;
	strItems = new CStringArray();
	//strItems->SetSize( rs.m_nFields );

	if( m_bHtml )
		outFile.WriteString( "<table>\n" ) ;

	if( m_bFirstRowIsColumnNames )
	{
		if( m_bHtml )
			outFile.WriteString( csv.FormatHtmlItems(rs.GetColumnNames( ), true) ) ;
		else
			outFile.WriteString( *(rs.GetCSVColumnNames( &strRow )) ) ;

		outFile.WriteString( "\n" ) ;
	}

	int dRowCount = 0;

	while( !rs.IsEOF( ) )
	{
		//int dRow;
		//int dRowsFetched = (int)rs.GetRowsFetched( );

		//for( dRow = 0; dRow < dRowsFetched; dRow++ )
		//{
			//rs.SetRowsetCursorPosition( (WORD)(dRow+1) );

			if( m_bHtml )
				outFile.WriteString( csv.FormatHtmlItems(rs.GetRow( strItems )) ) ;
			else
				outFile.WriteString( *(rs.GetCSVRow( &strRow )) ) ;

			outFile.WriteString( "\n" ) ;
		//}

		rs.MoveNext( );

		if( m_bRowCountMark && ((++dRowCount) % m_dRowCountMark) == 0)
		{
			cout << '.' ;
		}
	}

	if( m_bHtml )
		outFile.WriteString( "</table>\n" ) ;

	m_dSuccessRecordCount = rs.GetRecordCount( );

	m_timeStop = clock();

	rs.Close( );
	db.Close( );

	strItems->RemoveAll( );
	strItems->FreeExtra( );
	delete strItems;

	outFile.Close( );

	return m_dSuccessRecordCount;
}


long CBulkCopy::DatabaseCopyIn()
{
	if( m_szInputFileName == NULL )
	{
		return -1;
	}

	m_dSuccessRecordCount = 0L;
	m_dFailRecordCount = 0L;

	// ODBC IN mode

	CString strConnectString = CRecordsetEx::GetDefaultConnect(
		m_szServer,m_szUsername,m_szPassword,m_szDatabase,m_szDriver,m_szDSN,m_bTrustedConnection);

	CDatabase db;
	db.OpenEx( strConnectString , CDatabase::noOdbcDialog );

	CDatabase dbUpdate;
	dbUpdate.OpenEx( strConnectString , CDatabase::noOdbcDialog );

	CCSV csv(m_szFieldTerminator, m_szQuotedIdentifier);

	//CRecordsetEx rs( &db, csv );
	CRecordsetEx rs( &db, m_szFieldTerminator, m_szQuotedIdentifier );

	CStdioFile inFile( m_szInputFileName,
		CFile::modeRead | CFile::typeText );

	CString strLine;

	CStringArray* strItems;
	strItems = new CStringArray();

	CString strQueryString;

	if( m_bFirstRowIsColumnNames )
	{
		if( inFile.ReadString( strLine ) )
		{
			csv.GetItems(strItems, &strLine);

			strQueryString = CRecordsetEx::GetDefaultSQL(m_szQueryString, strItems);

			strItems->RemoveAll( );

			csv.SetRecordCount( );
		}
		else
		{
			strQueryString = CRecordsetEx::GetDefaultSQL(m_szQueryString);
		}
	}
	else
	{
		strQueryString = CRecordsetEx::GetDefaultSQL(m_szQueryString);
	}

	rs.Open(CRecordset::forwardOnly, strQueryString );

	if( m_szConfigSQL != NULL )
	{
		if( _tcslen(m_szConfigSQL) > 0 )
		{
			*m_strLog << m_strLog->endl() << _T("Executing config SQL...") << m_strLog->endl();
			m_strLog->Flush();

			dbUpdate.ExecuteSQL( m_szConfigSQL );
		}
	}

	*m_strLog << m_strLog->endl() << _T("Starting copy...") << m_strLog->endl();
	m_strLog->Flush();

	m_timeStart = clock();

	int dRowCount = 0;

	while( inFile.ReadString( strLine ) )
	{
		csv.GetItems(strItems, &strLine);

		try
		{
			dbUpdate.ExecuteSQL( rs.GetInsertSQL(strItems) );
		}
		catch (CDBException* pEx)
		{
			*m_strErr << "#@ Row " 
					  << csv.GetRecordCount( ) 
					  << " : " 
			//		  << m_strErr->endl()
					  << (LPCTSTR)(pEx->m_strError) 
					  << m_strErr->endl() ;

			m_strErr->Flush( );

			pEx->Delete();

			csv.SetRecordCount( true );
		}

		strItems->RemoveAll( );

		if( m_bRowCountMark && ((++dRowCount) % m_dRowCountMark) == 0)
		{
			cout << '.' ;
		}

	}

	m_dSuccessRecordCount = csv.GetRecordCount( true );
	m_dFailRecordCount = csv.GetRecordCount( ) - csv.GetRecordCount( true );

	m_timeStop = clock();

	dbUpdate.Close( );
	rs.Close( );
	db.Close( );

	strItems->RemoveAll( );
	strItems->FreeExtra( );
	delete strItems;

	inFile.Close( );

	return m_dSuccessRecordCount;
}

void CBulkCopy::PrintStatistics()
{
	double timeTotal = (double)(m_timeStop - m_timeStart) / CLOCKS_PER_SEC;
	double timeAvg = timeTotal / ((double)m_dSuccessRecordCount + (double)m_dFailRecordCount);

	*m_strLog << m_strLog->endl() 
			  << _T("(") 
			  << m_dSuccessRecordCount 
			  << _T(" row(s) copied)") 
			  << m_strLog->endl();
	m_strLog->Flush();

	if( m_dFailRecordCount > 0 )
	{
		*m_strLog << _T("(") 
				  << m_dFailRecordCount 
				  << _T(" row(s) failed)") 
				  << m_strLog->endl();
		m_strLog->Flush();
	}

	*m_strLog << _T("Clock Time (sec):") 
			  << _T(" Total ") ;
	m_strLog->setWidth( 8 );
	m_strLog->setPrecision( 2 );
	*m_strLog << timeTotal ;
	m_strLog->Init( );
	*m_strLog << _T(" Avg ") ;
	m_strLog->setWidth( 8 );
	m_strLog->setPrecision( 4 );
	*m_strLog << timeAvg ;
	m_strLog->Init( );
	*m_strLog << _T(" (") ;
	m_strLog->setPrecision( 2 );
	*m_strLog << (1/timeAvg) ;
	m_strLog->Init( );
	*m_strLog << _T(" rows per sec.)") 
			  << m_strLog->endl();
	m_strLog->Flush();
}

long CBulkCopy::GetSuccessRecordCount()
{
	return m_dSuccessRecordCount;
}

long CBulkCopy::GetFailRecordCount()
{
	return m_dFailRecordCount;
}
