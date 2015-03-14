// StringStream.cpp : implementation file
//

#include "stdafx.h"
#include "StringStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static const LPCTSTR szDecimalFormat = _T("%d");
static const LPCTSTR szFloatFormat = _T("%.*f");
static const LPCTSTR szByteFormat = _T("%02X");
static const LPCTSTR szBitFormat = _T("%X");

static const LPCTSTR szDateFormat = _T("%04d-%02d-%02d %02d:%02d:%06.3f");

static const char chEndl = '\n';

//static const CIgnore m_ignore = {true};

/////////////////////////////////////////////////////////////////////////////
// CStringStream

/////////////////////////////////////////////////////////////////////////////
// Constructor

CStringStream::CStringStream( ostream* costream, LPCTSTR szFileName, bool bEmptyOnFlush )
{
	m_costream = costream;
	m_bEmptyOnFlush = bEmptyOnFlush;

	Init( );
	OpenFile( szFileName );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

CStringStream::~CStringStream( )
{
	CloseFile( );
}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CStringStream::Flush( )
{
	if( m_costream )
	{
		*m_costream << (LPCTSTR) *this;
	}

	if( m_bFile )
	{
		m_file.WriteString( (LPCTSTR) *this ) ;
	}

	if( m_bEmptyOnFlush )
	{
		Empty( );
	}
}


bool CStringStream::OpenFile( LPCTSTR szFileName )
{
	m_bFile = false;

	if( szFileName != NULL )
	{
		CFileException pEx;

		if( m_file.Open( szFileName, 
			CFile::modeCreate | CFile::modeWrite | CFile::typeText, 
			&pEx ) )
		{
			m_bFile = true;
		}
		else
		{
			TCHAR szCause[1024];

			pEx.GetErrorMessage(szCause, 1024);

			cerr << szCause 
				 << "\n"
				 << "Logging to file '"
				 << szFileName
				 << "' has been disabled." 
				 << "\n";

			//pEx.Delete();
		}
	}

	return m_bFile;
}

void CStringStream::CloseFile( )
{
	if( m_bFile )
	{
		m_file.Close( );
	}
}


void CStringStream::Init( int nWidth, int nPrecision, char chFill )
{
	m_nWidth = nWidth;
	m_nPrecision = nPrecision;

	m_chFill = chFill;
}

/////////////////////////////////////////////////////////////////////////////
// Insertion (<<) Operator Member functions

//CStringStream& CStringStream::operator<<( const CIgnore& ignore )
//{
//	return *this;
//}

CStringStream& CStringStream::operator<<( CDBException* pEx )
{
	return *this << _T(pEx->m_strError) << endl();
}

CStringStream& CStringStream::operator<<( CFileException* pEx )
{
	TCHAR szCause[1024];

	pEx->GetErrorMessage(szCause, 1024);

	return *this << _T(szCause) << endl();
}

CStringStream& CStringStream::operator<<( CException* pEx )
{
	TCHAR szError[1024];

	pEx->GetErrorMessage(szError, 1024);

	return *this << _T(szError) << endl();
}

CStringStream& CStringStream::operator<<( const CStringStream& stream )
{
	*this << (LPCTSTR)stream;
	return *this;
}
CStringStream& CStringStream::operator<<( LPCTSTR psz )
{
	Write(psz, lstrlen(psz));
	return *this;
}
CStringStream& CStringStream::operator<<( char c )
{
	Write(&c, 1);
	return *this;
}
CStringStream& CStringStream::operator<<( short d )
{
	*this << (long)d;
	return *this;
}
CStringStream& CStringStream::operator<<( int d )
{
	*this << (long)d;
	return *this;
}
CStringStream& CStringStream::operator<<( float f )
{
	*this << (double)f;
	return *this;
}
CStringStream& CStringStream::operator<<( BYTE by )
{
	TCHAR sz[3];
	int nLen = _stprintf(sz, szBitFormat, by);
	Write(sz, nLen);
	return *this;
}
CStringStream& CStringStream::operator<<( long d )
{
	TCHAR sz[16];
	int nLen = _stprintf(sz, szDecimalFormat, d);
	Write(sz, nLen);
	return *this;
}
CStringStream& CStringStream::operator<<( double f )
{
	TCHAR sz[64];
	int nLen = _stprintf(sz, szFloatFormat, m_nPrecision, f);
	Write(sz, nLen);
	return *this;
}

CStringStream& CStringStream::operator<<(const CByteArray& array)
{
	int nSize = array.GetSize();
	if (nSize > 0)
	{
		const BYTE* pByte = array.GetData();

		if (pByte != NULL)
		{
			WriteBytes(pByte, nSize);
		}
	}

	return *this;
}

CStringStream& CStringStream::operator<<(const CLongBinary& blob)
{
	if( (blob.m_dwDataLength > 0) && (blob.m_hData != NULL) )
	{
		// Size of Allocated Memory
		DWORD dwSize = ::GlobalSize(blob.m_hData);

		// Size of Actual Memory used, (supposedly)
		UINT nSize = (UINT)blob.m_dwDataLength;

		LPVOID lpData = ::GlobalLock(blob.m_hData);
		if (lpData != NULL)
		{
			WriteBytes((BYTE*)lpData, nSize );
			//WriteBytes((BYTE*)lpData, dwSize);

			::GlobalUnlock(blob.m_hData);
		}
	}

	return *this;
}

CStringStream& CStringStream::operator<<( const TIMESTAMP_STRUCT& date )
{
	double sec;
	
	sec  = (double)(date.fraction) / 1000000000.0;
	sec += (double)date.second;

	TCHAR sz[32];
	int nLen = _stprintf(sz, szDateFormat, 
						 date.year, date.month, date.day,
						 date.hour, date.minute, sec);
	Write(sz, nLen);
	return *this;
}


CStringStream& CStringStream::operator<<( const CDBVariant& dbVariant )
{
	switch( dbVariant.m_dwType)
	{
		case DBVT_UCHAR : 
			*this << dbVariant.m_chVal ;
			break;

		case DBVT_SHORT : 
			*this << dbVariant.m_iVal ;
			break;

		case DBVT_LONG : 
			*this << dbVariant.m_lVal ;
			break;

		case DBVT_SINGLE : 
			*this << dbVariant.m_fltVal ;
			break;

		case DBVT_DOUBLE : 
			*this << dbVariant.m_dblVal ;
			break;

		case DBVT_DATE : 
			*this << *(dbVariant.m_pdate) ;
			break;

		case DBVT_STRING : 
			*this << *(dbVariant.m_pstring) ;
			break;

		case DBVT_BOOL :
			*this << (BYTE)dbVariant.m_boolVal ;
			break;

		case DBVT_BINARY : 
			*this << *(dbVariant.m_pbinary) ;
			break;

		case DBVT_NULL :
			break;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CStringStream::Write( const void* lpBuf, UINT nCount )
{
	int nSize = GetLength( );

	int nWidth;

	if( nCount < m_nWidth)
	{
		nWidth = m_nWidth - nCount;
	}
	else
	{
		nWidth = 0;
	}

	LPTSTR psz = GetBuffer( nSize + nCount + nWidth );

	if( nWidth )
	{
		memset( psz + nSize, m_chFill, nWidth );
	}

	psz[nSize + nCount + nWidth] = '\0';

	memcpy((BYTE*)psz + nSize + nWidth, (BYTE*)lpBuf, nCount);

	ReleaseBuffer( );
}


void CStringStream::WriteBytes( const BYTE* byBuf, UINT nCount)
{
	int nSize = GetLength( );

	int nWidth;

	if( (nCount * 2) < m_nWidth)
	{
		nWidth = m_nWidth - (nCount * 2);
	}
	else
	{
		nWidth = 0;
	}

	LPTSTR psz = GetBuffer( nSize + (nCount * 2) + nWidth );

	if( nWidth )
	{
		memset( psz + nSize, m_chFill, nWidth );
	}

	psz[nSize + (nCount * 2) + nWidth] = '\0';


	int nLen = 0;
	for( int i = 0 ; i < nCount ; i++ )
	{
		nLen += wsprintf(psz + nSize + nWidth + nLen, szByteFormat, byBuf[i]);
	}

	ReleaseBuffer( );
}


/////////////////////////////////////////////////////////////////////////////
// Manipulator Member functions

char CStringStream::endl( ) 
{
	return chEndl;
}

void CStringStream::setWidth( int nWidth )
{
	m_nWidth = nWidth;
}

void CStringStream::setFill( char chFill )
{
	m_chFill = chFill;
}

void CStringStream::setPrecision( int nPrecision )
{
	m_nPrecision = nPrecision;
}
