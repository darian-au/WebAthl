// HttpServerVariable.cpp : implementation file
//

#include "stdafx.h"

#include "HttpServerVariable.h"
#include "CSV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpServerVariable

/////////////////////////////////////////////////////////////////////////////
// Constructor

CHttpServerVariable::CHttpServerVariable( CHttpServerContext* pCtxt , DWORD dwLen )
{
	m_pCtxt = pCtxt;
	m_dwLen = dwLen;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CHttpServerVariable::~CHttpServerVariable( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CHttpServerVariable::PrintServerVariables()
{
	char *aszServerVariables[] = {
		"ALL_HTTP", 
		"ALL_RAW", 
		"APPL_MD_PATH", 
		"APPL_PHYSICAL_PATH", 
		"AUTH_PASSWORD", 
		"AUTH_TYPE", 
		"AUTH_USER", 
		"CERT_COOKIE", 
		"CERT_FLAGS", 
		"CERT_ISSUER", 
		"CERT_KEYSIZE", 
		"CERT_SECRETKEYSIZE", 
		"CERT_SERIALNUMBER", 
		"CERT_SERVER_ISSUER", 
		"CERT_SERVER_SUBJECT", 
		"CERT_SUBJECT", 
		"CF_TEMPLATE_PATH", 
		"CONTENT_LENGTH", 
		"CONTENT_TYPE", 
		"GATEWAY_INTERFACE", 
		"HTTP_ACCEPT", 
		"HTTPS", 
		"HTTPS_KEYSIZE", 
		"HTTPS_SECRETKEYSIZE", 
		"HTTPS_SERVER_ISSUER", 
		"HTTPS_SERVER_SUBJECT", 
		"INSTANCE_ID", 
		"INSTANCE_META_PATH", 
		"LOCAL_ADDR", 
		"LOGON_USER", 
		"PATH_INFO", 
		"PATH_TRANSLATED", 
		"QUERY_STRING", 
		"REMOTE_ADDR", 
		"REMOTE_HOST", 
		"REMOTE_USER", 
		"REQUEST_METHOD", 
		"SCRIPT_NAME", 
		"SERVER_NAME", 
		"SERVER_PORT", 
		"SERVER_PORT_SECURE", 
		"SERVER_PROTOCOL", 
		"SERVER_SOFTWARE", 
		"URL",
		"WEB_SERVER_API",
	};
	char *aszServerVariablesEx[] = {
		"HTTP_ACCEPT", 
		"HTTP_ACCEPT_ENCODING",
		"HTTP_ACCEPT_LANGUAGE", 
		"HTTP_CONNECTION", 
		"HTTP_COOKIE",
		"HTTP_HOST",
		"HTTP_REFERER",
		"HTTP_USER_AGENT",
		"HTTP_VIA",
		"HTTP_X_FORWARDED_FOR",
		"HTTP_CACHE_CONTROL",
	};

	DWORD	dwNumVars;
	DWORD	dw;

	dwNumVars = ( sizeof aszServerVariables )/( sizeof aszServerVariables[0] );

	for( dw = 0; dw < dwNumVars; dw++ )
	{
		*m_pCtxt << _T("<B>");
		*m_pCtxt << _T(aszServerVariables[dw]);
		*m_pCtxt << _T("</B> -> ");
		*m_pCtxt << _T( GetVariable(aszServerVariables[dw]) );
		*m_pCtxt << _T("<BR>\r\n");
	} 

	dwNumVars = ( sizeof aszServerVariablesEx )/( sizeof aszServerVariablesEx[0] );

	for( dw = 0; dw < dwNumVars; dw++ )
	{
		*m_pCtxt << _T("<B>");
		*m_pCtxt << _T(aszServerVariablesEx[dw]);
		*m_pCtxt << _T("</B> -> ");
		*m_pCtxt << _T( GetVariableEx(aszServerVariablesEx[dw]) );
		*m_pCtxt << _T("<BR>\r\n");
	} 
}

CString CHttpServerVariable::GetVariable(LPCTSTR szVarName)
{
	DWORD dwLen = m_dwLen;
	CString strBuf;

	LPTSTR szBuf = strBuf.GetBuffer( dwLen );

	BOOL bSuccess = m_pCtxt->GetServerVariable ((LPTSTR)szVarName, szBuf, &dwLen);

	strBuf.ReleaseBuffer( );

	if( !bSuccess )
	{
		strBuf.Empty( );
	}

	return strBuf;
}

CString CHttpServerVariable::GetVariableEx(LPCTSTR szVarName)
{
	CString strVars = GetVariable("ALL_HTTP");
	CStringArray* strItems = new CStringArray();
	CString strVarValue;
	CString strVarName;
	CCSV csv(":\r\n");

	csv.GetItems(strItems, &strVars);

	for( int i = 0 ; i < strItems->GetSize( ) ; i++ )
	{
		strVarName = strItems->GetAt( i );
		strVarName.TrimLeft( );

		if( !strVarName.Compare( szVarName ) )
		{
			if( strItems->GetSize( ) > i )
			{
				strVarValue = strItems->GetAt( i+1 );
			}
			break;
		}
	}

	delete strItems;

	return strVarValue;
}

CString CHttpServerVariable::GetCookie(LPCTSTR szCookieName)
{
	CString strCookies = GetVariableEx("HTTP_COOKIE");
	CStringArray* strArPairs = new CStringArray();
	CStringArray* strArPair = new CStringArray();

	CString strCookieValue;
	CString strCookieName;

	CString strPair;
	CCSV csvPairs(";");
	CCSV csvPair("=");

	csvPairs.GetItems(strArPairs, &strCookies);

	for( int i = 0 ; i < strArPairs->GetSize( ) ; i++ )
	{
		strPair = strArPairs->GetAt( i );

		csvPair.GetItems(strArPair, &strPair);

		strCookieName = strArPair->GetAt( 0 );
		strCookieName.TrimLeft( );

		if( !strCookieName.Compare( szCookieName ) )
		{
			if( strArPair->GetSize( ) > 1 )
			{
				strCookieValue = strArPair->GetAt( 1 );
			}
			break;
		}
		strArPair->RemoveAll( );
	}

	delete strArPair;
	delete strArPairs;

	return strCookieValue;
}

CString CHttpServerVariable::MakeStringSetCookie(LPCTSTR szCookieName, LPCTSTR szCookieValue)
{
	CString str;

	str.Format( "Set-Cookie: %s=%s;\n", szCookieName, szCookieValue);

	return str;
}

CString CHttpServerVariable::MakeStringSetContent(LPCTSTR szContentType)
{
	CString str;

	str.Format( szContentType );

	return str;
}

CString CHttpServerVariable::MakeStringEndHeader()
{
	CString str;

	str.Format( "\n\n\n" );

	return str;
}

CString CHttpServerVariable::GetFileName()
{
	CString strScript = GetVariable("SCRIPT_NAME");
	CString str;

	int nIndex = strScript.ReverseFind( '/' );

	if( nIndex > -1 )
	{
		str = strScript.Right( strScript.GetLength( ) - nIndex -1 );
	}

	return str;
}

CString CHttpServerVariable::GetPathName()
{
	CString strScriptName = GetVariable("SCRIPT_NAME");
	CString strFileName = GetFileName( );
	CString str;

	int nIndex = strScriptName.Find( strFileName );

	if( nIndex > -1 )
	{
		str = strScriptName.Left( nIndex );
	}

	return str;
}


CHttpServerContext& CHttpServerVariable::operator<<( LPCTSTR psz )
{
	return *m_pCtxt << psz;
}

CHttpServerContext& CHttpServerVariable::operator<<( long int dw )
{
	return *m_pCtxt << dw;
}

CHttpServerContext& CHttpServerVariable::operator<<( short int w )
{
	return *m_pCtxt << w;
}

CHttpServerContext& CHttpServerVariable::operator<<( const CHtmlStream& stream )
{
	return *m_pCtxt << stream;
}

CHttpServerContext& CHttpServerVariable::operator<<( double d )
{
	return *m_pCtxt << d;
}

CHttpServerContext& CHttpServerVariable::operator<<( float f )
{
	return *m_pCtxt << f;
}

CHttpServerContext& CHttpServerVariable::operator<<( const CLongBinary& blob )
{
	return *m_pCtxt << blob;
}

CHttpServerContext& CHttpServerVariable::operator<<( const CByteArray& array )
{
	return *m_pCtxt << array;
}

CHttpServerContext& CHttpServerVariable::operator<<( CDBException* pEx )
{
	return *m_pCtxt << _T(pEx->m_strError) << _T("<BR>\r\n");
}

CHttpServerContext& CHttpServerVariable::operator<<( CFileException* pEx )
{
	TCHAR szCause[1024];

	pEx->GetErrorMessage(szCause, 1024);

	return *m_pCtxt << _T(szCause) << _T("<BR>\r\n");
}

CHttpServerContext& CHttpServerVariable::operator<<( CException* pEx )
{
	TCHAR szCause[1024];

	pEx->GetErrorMessage(szCause, 1024);

	return *m_pCtxt << _T(szCause) << _T("<BR>\r\n");
}
