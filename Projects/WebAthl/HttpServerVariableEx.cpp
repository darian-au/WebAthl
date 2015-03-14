// HttpServerVariableEx.cpp : implementation file
//

#include "stdafx.h"

#include "HttpServerVariable.h"
#include "HttpServerVariableEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpServerVariableEx

LPCTSTR CHttpServerVariableEx::m_szDefaultContentType = _T("Content-type: text/html\n");

/////////////////////////////////////////////////////////////////////////////
// Constructor

CHttpServerVariableEx::CHttpServerVariableEx( CHttpServerContext* pCtxt , CHttpServer* pSrv, DWORD dwLen )
	: CHttpServerVariable(pCtxt, dwLen)
{
	m_pSrv = pSrv;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CHttpServerVariableEx::~CHttpServerVariableEx( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CHttpServerVariableEx::AddHeader( LPCTSTR pszString ) const
{
	 m_pSrv->AddHeader( m_pCtxt, pszString );
}

void CHttpServerVariableEx::EndContent( ) const
{
	m_pSrv->EndContent( m_pCtxt );
}


void CHttpServerVariableEx::SetCookie(LPCTSTR szCookieName, LPCTSTR szCookieValue)
{
	AddHeader( MakeStringSetCookie(szCookieName, szCookieValue) );
}

void CHttpServerVariableEx::SetContent(LPCTSTR szContentType)
{
    AddHeader( MakeStringSetContent(szContentType) );
}

void CHttpServerVariableEx::EndHeader()
{
    AddHeader( MakeStringEndHeader() );
}


