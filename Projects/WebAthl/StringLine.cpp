// CStringLine.cpp : implementation file
//

#include "stdafx.h"

#include "StringLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringLine

/////////////////////////////////////////////////////////////////////////////
// Constructor
CStringLine::CStringLine(LPCTSTR sz, LPCTSTR szRowTerminator)
{
	m_szRowTerminator = szRowTerminator;

	m_str = CString(sz);

	SetRecordCount( );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor
//CStringLine::~CStringLine()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions
BOOL CStringLine::GetLine(CString& strLine)
{
	int nIndex;
	int nLen;

	nLen = m_str.GetLength();

	nIndex = m_str.FindOneOf( m_szRowTerminator ) ;

	if( nIndex > -1 || nLen > 0 )
	{
		strLine = m_str.SpanExcluding( m_szRowTerminator );

		if( nIndex > -1 )
		{
			m_str = m_str.Right( nLen - nIndex );
		}
		else
		{
			m_str.Empty( );
		}

		m_str.TrimLeft( m_szRowTerminator );

		m_nRecordCount++;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

LPCTSTR CStringLine::GetRowTerminator()
{	
	return m_szRowTerminator;	
}

long CStringLine::GetRecordCount() const
{
	return m_nRecordCount;
}

void CStringLine::SetRecordCount()
{
	m_nRecordCount = 0;
}

