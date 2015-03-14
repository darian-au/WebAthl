// CHtmlMonth.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "Convert.h"

#include "HtmlMonth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HtmlMonth

LPCTSTR CHtmlMonth::m_szSelected = _T("selected");

/////////////////////////////////////////////////////////////////////////////
// Constructor

CHtmlMonth::CHtmlMonth( )
{
}

CHtmlMonth::CHtmlMonth( int nMonth )
{
	Select( nMonth );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CHtmlMonth::~CHtmlMonth( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CHtmlMonth::Empty( )
{
	m_strJan.Empty( );
	m_strFeb.Empty( );
	m_strMar.Empty( );
	m_strApr.Empty( );
	m_strMay.Empty( );
	m_strJun.Empty( );
	m_strJul.Empty( );
	m_strAug.Empty( );
	m_strSep.Empty( );
	m_strOct.Empty( );
	m_strNov.Empty( );
	m_strDec.Empty( );
}

void CHtmlMonth::Select( int nMonth )
{
	Empty( );

	switch (nMonth)
	{
		case 1 : 
			m_strJan = m_szSelected;
			break;
		case 2 : 
			m_strFeb = m_szSelected;
			break;
		case 3 : 
			m_strMar = m_szSelected;
			break;
		case 4 : 
			m_strApr = m_szSelected;
			break;
		case 5 : 
			m_strMay = m_szSelected;
			break;
		case 6 : 
			m_strJun = m_szSelected;
			break;
		case 7 : 
			m_strJul = m_szSelected;
			break;
		case 8 : 
			m_strAug = m_szSelected;
			break;
		case 9 : 
			m_strSep = m_szSelected;
			break;
		case 10 : 
			m_strOct = m_szSelected;
			break;
		case 11 : 
			m_strNov = m_szSelected;
			break;
		case 12 : 
			m_strDec = m_szSelected;
			break;
	}
}

CString CHtmlMonth::GetName(int nMonth)
{
	switch (nMonth)
	{
		case  1 : return _T("Jan");
		case  2 : return _T("Feb");
		case  3 : return _T("Mar");
		case  4 : return _T("Apr");
		case  5 : return _T("May");
		case  6 : return _T("Jun");
		case  7 : return _T("Jul");
		case  8 : return _T("Aug");
		case  9 : return _T("Sep");
		case 10 : return _T("Oct");
		case 11 : return _T("Nov");
		case 12 : return _T("Dec");
	}

	return CConvert::itoa(nMonth) ;
}

