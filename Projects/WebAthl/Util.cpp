// CUtil.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HttpServerProperties.h"

#include "Util.h"

#include "CountResultSet.h"
#include "IntegerSet.h"
#include "Convert.h"
#include "EventSet.h"

#include <direct.h> // _tmkdir

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Util

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CUtil::CUtil( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CUtil::~CUtil( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

BOOL CUtil::LoadLongResource(CString& str, UINT nID)
{
	HRSRC hRes;
	HINSTANCE hInst = AfxGetResourceHandle();
	BOOL bResult = FALSE;
	
//	hRes = FindResource(hInst, MAKEINTRESOURCE(nID), szHTMLType);
	hRes = FindResource(hInst, MAKEINTRESOURCE(nID), RT_RCDATA );
	if (hRes == NULL)
	{
		ISAPITRACE1("Error: Resource %d could not be found\r\n", nID);
		str.Format(_T("<b>Error Code: %d</b>"),GetLastError());
	}
	else
	{
		DWORD dwSize = SizeofResource(hInst, hRes);
		if (dwSize == 0)
		{
			str.Empty();
			bResult = TRUE;
		}
		else
		{
			LPTSTR pszStorage = str.GetBufferSetLength(dwSize);

			HGLOBAL hGlob = LoadResource(hInst, hRes);
			if (hGlob != NULL)
			{
				LPVOID lpData = LockResource(hGlob);

				if (lpData != NULL)
				{
					memcpy(pszStorage, lpData, dwSize);
					bResult = TRUE;
				}

				FreeResource(hGlob);
			}
		}
	}

#ifdef _DEBUG
	if (!bResult)
		str.Format(_T("<b>Could not find string %d</b>"), nID);
#endif

	return bResult;
}


CString CUtil::AppendFolder(CString strPath, int nInitNum, ...)
{
	TCHAR pszPath[_MAX_PATH];

	CString strFolder;

	if( strPath.GetLength() > 0 )
	{
		strFolder += _T(strPath);

		if( strPath.GetAt(strPath.GetLength() -1) != _T('\\')  )
		{
			strFolder += _T("\\");
		}
	}


	va_list marker;
	char    *szInit;
	int		nInitCounter = 0;

	// Initialize variable arguments.	//
	va_start( marker, nInitNum );				

	// Get next variable argument.		//
	for( nInitCounter = 0 ; nInitCounter < nInitNum ; nInitCounter++ )	
	{
		szInit = va_arg( marker, char* );

		if ( _tcslen(szInit) > 0 )
		{
			strFolder += _T(szInit);
			if( strFolder.GetAt(strFolder.GetLength() -1) != _T('\\')  )
			{
				strFolder += _T("\\");
			}
		}
	}

	// Reset variable arguments.		//
	va_end( marker );						


	_tfullpath( pszPath, strFolder, _MAX_PATH );

	strFolder = pszPath;

	return strFolder;

}


BOOL CUtil::CreateFolders(CHttpServerProperties* pProp)
{
	CString strBackupFolder = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);
	CString strDatabase = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::DATABASE);
		
	int nSuccess = 0;

	nSuccess += _tmkdir( MakeFolderDatabase(strBackupFolder, strDatabase) );
	nSuccess += _tmkdir( MakeFolderData(strBackupFolder, strDatabase) );
	nSuccess += _tmkdir( MakeFolderLog(strBackupFolder, strDatabase) );
	nSuccess += _tmkdir( MakeFolderError(strBackupFolder, strDatabase) );

	if( nSuccess == 0 )
	{
		return TRUE;
	}
	else if( errno == EEXIST ) // EEXIST (17) File exists
	{
		// Ignore
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CUtil::MakeFolderDatabase(CString strBackupFolder, CString strDatabase)
{
	TCHAR pszFileName[_MAX_PATH];

	_tsplitpath( strDatabase, NULL, NULL, pszFileName, NULL );

	return AppendFolder(strBackupFolder, 1, pszFileName);
}

CString CUtil::MakeFolderData(CString strBackupFolder, CString strDatabase)
{
	TCHAR pszFileName[_MAX_PATH];

	_tsplitpath( strDatabase, NULL, NULL, pszFileName, NULL );

	return AppendFolder(strBackupFolder, 2, pszFileName, _T("Data"));
}

CString CUtil::MakeFolderLog(CString strBackupFolder, CString strDatabase)
{
	TCHAR pszFileName[_MAX_PATH];

	_tsplitpath( strDatabase, NULL, NULL, pszFileName, NULL );

	return AppendFolder(strBackupFolder, 2, pszFileName, _T("Log"));
}

CString CUtil::MakeFolderError(CString strBackupFolder, CString strDatabase)
{
	TCHAR pszFileName[_MAX_PATH];

	_tsplitpath( strDatabase, NULL, NULL, pszFileName, NULL );

	return AppendFolder(strBackupFolder, 2, pszFileName, _T("Error"));
}


CString CUtil::GetFolderDatabase(CHttpServerProperties* pProp)
{
	CString strBackupFolder = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);
	CString strDatabase = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::DATABASE);

	return MakeFolderDatabase(strBackupFolder, strDatabase);
}

CString CUtil::GetFolderData(CHttpServerProperties* pProp)
{
	CString strBackupFolder = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);
	CString strDatabase = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::DATABASE);

	return MakeFolderData(strBackupFolder, strDatabase);
}

CString CUtil::GetFolderLog(CHttpServerProperties* pProp)
{
	CString strBackupFolder = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);
	CString strDatabase = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::DATABASE);

	return MakeFolderLog(strBackupFolder, strDatabase);
}

CString CUtil::GetFolderError(CHttpServerProperties* pProp)
{
	CString strBackupFolder = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);
	CString strDatabase = pProp->GetEx(CHtmlKey::ODBC,CHtmlKey::DATABASE);

	return MakeFolderError(strBackupFolder, strDatabase);
}



CString CUtil::ParseHttpPostQuery(CString strQuerys, TCHAR chDelimiter)
{
	CStringArray* strArPairs = new CStringArray();
	CStringArray* strArPair = new CStringArray();

	CString strQueryValue;
	CString strQueryName;

	CString strQueryNewValue;

	CString strPair;
	CCSV csvPairs('&');
	CCSV csvPair('=');

	csvPairs.GetItems(strArPairs, &strQuerys);

	CStringList strKeyList;

	CMapStringToString map;

	int nLength = strArPairs->GetSize( );

	// Parse the Query String and put the key-values pairs into
	// a hash map, also remember the order that the keys were in
	// by putting them into a list.

	for( int nIndex = 0 ; nIndex < nLength ; nIndex++ )
	{
		strPair = strArPairs->GetAt( nIndex );

		csvPair.GetItems(strArPair, &strPair);

		strQueryName = strArPair->GetAt( 0 );
		strQueryName.TrimLeft( );

		if( !(nLength == 1 && strQueryName.IsEmpty( )) )
		{
			strKeyList.AddTail(strQueryName);
		}

		if( strArPair->GetSize( ) > 1 )
		{
			strQueryNewValue = strArPair->GetAt( 1 );
		}
		else
		{
			strQueryNewValue.Empty( );
		}

		if( map.Lookup( strQueryName, strQueryValue ) )
		{
			strQueryValue += _T(chDelimiter) + strQueryNewValue;
		}
		else
		{
			strQueryValue = strQueryNewValue;
		}

		map.SetAt( strQueryName, strQueryValue );


		strArPair->RemoveAll( );
	}


	CMapStringToString mapKeysUsed;

	BOOL bIsFirst;
	CString strNewQuerys;

	// Iterate the key list, and get the value for each key out of
	// the hash map.  Then recombine the key-value pairs into a 
	// new Query String.

	for( POSITION pos = strKeyList.GetHeadPosition( ) ; pos != NULL ; )
	{
		strQueryName = strKeyList.GetNext( pos ) ;
		
		bIsFirst = !strQueryName.Compare( strKeyList.GetHead( ) );

		if( !mapKeysUsed.Lookup( strQueryName, strQueryValue ) )
		{
			mapKeysUsed.SetAt( strQueryName, "" );

			if( !map.Lookup( strQueryName, strQueryValue ) )
			{
				strQueryValue.Empty( );
			}

			if( !bIsFirst )
			{
				strNewQuerys += _T('&') ;
			}

			strNewQuerys += strQueryName;

			if( !(bIsFirst && strQueryValue.IsEmpty( )) )
			{
				strNewQuerys += _T('=') ;
				strNewQuerys += strQueryValue;
			}
		}
	}




	delete strArPair;
	delete strArPairs;

	return strNewQuerys;

}


int CUtil::Max(int nCount, ...)
{
	int nIndex;
	int nItem;
	int nItemMax = INT_MIN;

	va_list marker;

	va_start( marker, nCount );     // Initialize variable arguments.

	for( nIndex = 0 ; nIndex < nCount ; nIndex++ )
	{
		nItem = va_arg( marker, int );

		nItemMax = (nItemMax < nItem) ? nItem : nItemMax ;
	}

	va_end( marker );              // Reset variable arguments.

	return nItemMax;
}


int CUtil::Count(CDatabase* db, LPCTSTR szSQL)
{
	int nCount = 0;

	try
	{
		CCountResultSet rs( db );
		rs.Open(CRecordset::forwardOnly, szSQL);

		if( !rs.IsEOF( ) && rs.m_Total > 0 )
		{
			nCount = rs.m_Total;
		}

		rs.Close( );
	}
	catch (CDBException* pEx)
	{
		pEx->Delete();
	}

	return nCount;
}

int CUtil::GetIntegerItems(CDatabase* db, LPCTSTR szSQL, CStringArray* strItems)
{
	int nCount = 0;

	try
	{
		CIntegerSet rs( db );
		rs.Open(CRecordset::forwardOnly, szSQL);

		while( !rs.IsEOF( ) )
		{
			strItems->Add( CConvert::itoa(rs.m_Val) );
			nCount++;

			rs.MoveNext( );
		}

		rs.Close( );
	}
	catch (CDBException* pEx)
	{
		pEx->Delete();
	}

	return nCount;
}


CMap<int,int,CPoint,CPoint>* CUtil::FindEventsBetweenDates(	LPCTSTR szConnect,
															COleDateTime dateEventFrom,
															COleDateTime dateEventTo,
															CStringArray* strSeriesIDItems,
															CString* strError)
{
	// maps key-value pairs.
	// this map, maps an int key to an CPoint(int x, int y) value.
	CMap<int,int,CPoint,CPoint>* pMap = new CMap<int,int,CPoint,CPoint> ;

	CString strSQLEventDateFrom = _T("SELECT * FROM Event WHERE SeriesID = %d ORDER BY DateYEAR ASC, DateMONTH ASC, DateDAY ASC, EventNo ASC ");
	CString strSQLEventDateTo = _T("SELECT * FROM Event WHERE SeriesID = %d ORDER BY DateYEAR DESC, DateMONTH DESC, DateDAY DESC, EventNo DESC ");

	try
	{
		CString strConnect = szConnect;
		CString strSQL;

		CDatabase db;
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );


		CEventSet rs( &db );

		// For each Series, get the EventNo for the First Date after the EventDateFrom
		//                  and the EventNo for the Last Date before the EventDateTo
		for( int nIndex = 0; nIndex < strSeriesIDItems->GetSize( ) ; nIndex++ )
		{
			CString strSeriesID = strSeriesIDItems->GetAt(nIndex);
			int iSeriesID = atoi(strSeriesID);

			int iEventNoFrom = 0;
			int iEventNoTo = 0;

			if( iSeriesID > 0 )
			{
				COleDateTime dateEvent;

				bool bFound; 


				strSQL.Format(strSQLEventDateFrom, iSeriesID);
				rs.Open(CRecordset::forwardOnly, strSQL );

				bFound = false;

				while( !rs.IsEOF( ) )
				{
					dateEvent.SetDate( rs.m_DateYEAR , rs.m_DateMONTH, rs.m_DateDAY );

					iEventNoFrom = rs.m_EventNo;

					if( dateEvent >= dateEventFrom )
					{
						bFound = true;
						break;
					}

					rs.MoveNext( );
				}

				rs.Close( );

				if( !bFound )
				{
					iEventNoFrom++;
				}


				strSQL.Format(strSQLEventDateTo, iSeriesID);
				rs.Open(CRecordset::forwardOnly, strSQL );

				bFound = false;

				while( !rs.IsEOF( ) )
				{
					dateEvent.SetDate( rs.m_DateYEAR , rs.m_DateMONTH, rs.m_DateDAY );

					iEventNoTo = rs.m_EventNo;

					if( dateEvent <= dateEventTo )
					{
						bFound = true;
						break;
					}

					rs.MoveNext( );
				}

				rs.Close( );

				if( !bFound )
				{
					iEventNoTo--;
				}

				pMap->SetAt(iSeriesID, CPoint(iEventNoFrom, iEventNoTo) ); 
			}
		}

		db.Close( );

		return pMap;
	}
	catch (CDBException* pEx)
	{
		if( strError != NULL )
			strError->Format(pEx->m_strError);

		pEx->Delete();

		delete pMap;

		return NULL;
	}
}


