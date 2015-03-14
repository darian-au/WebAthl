// HttpServerProperties.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HttpServerProperties.h"

#include "StringSet.h"

#define REG_DEFAULT_COMPANY	"Darian"
#define REG_DEFAULT_PROGRAM	"WebAthl"
#define REG_EMPTY_VALUE		"REG_EMPTY_VALUE"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpServerProperties

LPCTSTR CHttpServerProperties::m_szDefaultCompany = _T(REG_DEFAULT_COMPANY);
LPCTSTR CHttpServerProperties::m_szDefaultProgram = _T(REG_DEFAULT_PROGRAM);
LPCTSTR CHttpServerProperties::m_szEmptyValue = _T(REG_EMPTY_VALUE);

/////////////////////////////////////////////////////////////////////////////
// Constructor

CHttpServerProperties::CHttpServerProperties( CHttpServerVariable* pSrvVar, LPCTSTR szCompany, LPCTSTR szProgram )
	: CProperties( szCompany , szProgram ) 
{
	CRegistry::SetProfile(pSrvVar->GetPathName( ));

	m_pSrvVar = pSrvVar;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CHttpServerProperties::~CHttpServerProperties( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

BOOL CHttpServerProperties::IsEmpty( LPCTSTR szValue )
{
	return ! _tcscmp( szValue, CHttpServerProperties::m_szEmptyValue );
}

BOOL CHttpServerProperties::IsEmpty( LPCTSTR szSection, LPCTSTR szKey )
{
	return IsEmpty( Get( szSection, szKey ) );
}

CString CHttpServerProperties::Get( LPCTSTR szSection, LPCTSTR szKey )
{
	CString strValue = CProperties::Get( szSection, szKey, CHttpServerProperties::m_szEmptyValue );
	return strValue;
}

CString CHttpServerProperties::GetEx( LPCTSTR szSection, LPCTSTR szKey )
{
	CString strValue = Get( szSection, szKey );

	if( IsEmpty( strValue ) && _tcscmp( szSection, CHtmlKey::ODBC ) )
	{
		SetEx( );

		strValue = Get( szSection, szKey );
	}
/*
	if( !_tcscmp( szSection, "Appearance") )
	{
		try
		{
			CString strLoginName = m_pSrvVar->GetCookie(CHtmlKey::LoginName);

			CString strSQL;

			CDatabase db;
			db.OpenEx( _T( GetDefaultConnect() ), CDatabase::noOdbcDialog );

			CStringSet rs( &db );
			strSQL.Format( "SELECT Options.%s AS Val FROM Options, SecurityPerson WHERE SecurityPerson.LoginName = '%s' AND Options.PersonID = SecurityPerson.PersonID", szKey, strLoginName );
			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				strValue = rs.m_Val;
			}
			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			// Do Nothing
			pEx->m_strError;

			pEx->Delete();
		}
	}
*/
	return strValue;
}

BOOL CHttpServerProperties::SetEx( )
{
	BOOL nStatus = ERROR_SUCCESS;

	nStatus |= Set(CHtmlKey::AgeGroup,     CHtmlKey::MaxJunior,         "18" );
	nStatus |= Set(CHtmlKey::AgeGroup,     CHtmlKey::JuniorGroup,       "2" );
	nStatus |= Set(CHtmlKey::AgeGroup,     CHtmlKey::MinVeteran,        "30" );
	nStatus |= Set(CHtmlKey::AgeGroup,     CHtmlKey::VeteranGroup,      "5" );
	nStatus |= Set(CHtmlKey::AgeGroup,     CHtmlKey::NullDoB,           "999" );

	nStatus |= Set(CHtmlKey::Processing,   CHtmlKey::TimeOut,           "30" );

	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::Font,              "Verdana" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::BackgroundColor,   "#F2F2F2" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::MenuColor,         "#A5A5CB" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::Logo,              "" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::BackgroundImage,   "" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::MenuImage,         "" );
	nStatus |= Set(CHtmlKey::Appearance,   CHtmlKey::StyleSheet,        "" );

	nStatus |= Set(CHtmlKey::Cryptography, CHtmlKey::Enabled,           "0" );
	nStatus |= Set(CHtmlKey::Cryptography, CHtmlKey::Password,          "apple-camshaft" );

	nStatus |= Set(CHtmlKey::UserAccess,   CHtmlKey::Enabled,           "0" );

	nStatus |= Set(CHtmlKey::Navigation,   CHtmlKey::ExitURL,           "/" );

	nStatus |= Set(CHtmlKey::PersonSearch, CHtmlKey::LastName,          "3,2,1" );
	nStatus |= Set(CHtmlKey::PersonSearch, CHtmlKey::FirstName,         "0,2,1" );
	nStatus |= Set(CHtmlKey::PersonSearch, CHtmlKey::MiddleName,        "0,0,1" );
	nStatus |= Set(CHtmlKey::PersonSearch, CHtmlKey::DateOfBirth,       "0" );
	nStatus |= Set(CHtmlKey::PersonSearch, CHtmlKey::Sex,               "0" );

	return nStatus;
}

BOOL CHttpServerProperties::CanSet( )
{
	BOOL nStatus = ERROR_SUCCESS;

	nStatus |= Set(CHtmlKey::Properties,CHtmlKey::Enabled,"1");

	if( nStatus == ERROR_SUCCESS )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CHttpServerProperties::GetDefaultConnect()
{
	return CRecordsetEx::GetDefaultConnect(
		Get(CHtmlKey::ODBC, CHtmlKey::SERVER),
		Get(CHtmlKey::ODBC, CHtmlKey::UID),
		Get(CHtmlKey::ODBC, CHtmlKey::PWD),
		Get(CHtmlKey::ODBC, CHtmlKey::DATABASE),
		Get(CHtmlKey::ODBC, CHtmlKey::DRIVER),
		Get(CHtmlKey::ODBC, CHtmlKey::DSN),
		FALSE );
}

BOOL CHttpServerProperties::SetDefaultConnect(LPCTSTR szServer,
											  LPCTSTR szUID,
											  LPCTSTR szPWD,
											  LPCTSTR szDatabase,
											  LPCTSTR szDriver,
											  LPCTSTR szDSN)
{
	BOOL nStatus;

	CString strError;

	CString strConnect = CRecordsetEx::GetDefaultConnect(
		szServer,
		szUID,
		szPWD,
		szDatabase,
		szDriver,
		szDSN,
		FALSE );

	if( nStatus = CRecordsetEx::TestConnect(strConnect, &strError) )
	{
		nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::SERVER,	szServer );
		nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::UID,		szUID );
		nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::PWD,		szPWD );

		if ( _tcscmp(szDSN, CRecordsetEx::noDSN) || 
			!_tcscmp(szDriver, CRecordsetEx::useDSN) )
		{
			nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::DATABASE,	szDSN );
		}
		else
		{
			nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::DATABASE,	szDatabase );
		}

		nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::DRIVER,	szDriver );
		nStatus |= Set( CHtmlKey::ODBC, CHtmlKey::DSN,		szDSN );
	}

	return nStatus;
}

BOOL CHttpServerProperties::IsLicensed(LPTSTR szKeyMsg)
{
	if( GetLicense(szKeyMsg) == ERC_SUCCESS )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CHttpServerProperties::GetLicense(LPTSTR szKeyMsg)
{
	CString strRegNo = Get(CHtmlKey::License, CHtmlKey::No); 
	CString strRegName = Get(CHtmlKey::License, CHtmlKey::Name);
	CString strKey = Get(CHtmlKey::License, CHtmlKey::Key);

	if( IsEmpty(strRegNo) || IsEmpty(strRegName) || IsEmpty(strKey) )
	{
		return ERC_ERROR;
	}

	return CRegKey::DecKey( strRegNo, strRegName, strKey, szKeyMsg );
}

int CHttpServerProperties::SetLicense(LPCTSTR szRegNo, 
									  LPCTSTR szRegName, 
									  LPCTSTR szKey, 
									  LPTSTR szKeyMsg)
{
	int nStatus;
	int nRegStatus = ERROR_SUCCESS;

	nStatus = CRegKey::DecKey(szRegNo, szRegName, szKey, szKeyMsg);

	if( nStatus == ERC_SUCCESS )
	{
		nRegStatus |= Set( CHtmlKey::License, CHtmlKey::No,	szRegNo );
		nRegStatus |= Set( CHtmlKey::License, CHtmlKey::Name, szRegName );
		nRegStatus |= Set( CHtmlKey::License, CHtmlKey::Key, szKey );
	}

	if( nRegStatus != ERROR_SUCCESS )
	{
		nStatus = ERC_ERROR;
		if( szKeyMsg != NULL )
			_tcscpy(szKeyMsg, _T("Unable to Save License Details.\0"));
	}

	return nStatus;
}
