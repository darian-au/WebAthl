#if !defined(AFX_STRINGSTREAM_H__INCLUDED_)
#define AFX_STRINGSTREAM_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StringStream.h : header file
//

#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CStringStream string

class CStringStream : public CString
{

public:

	CStringStream( ostream* costream = NULL, LPCTSTR szFileName = NULL, bool bEmptyOnFlush = true);
	~CStringStream( );

	CStringStream& operator<<( CDBException* pEx );
	CStringStream& operator<<( CFileException* pEx );
	CStringStream& operator<<( CException* pEx );

	CStringStream& operator<<( const CStringStream& stream );

	CStringStream& operator<<( BYTE by );
	CStringStream& operator<<( LPCTSTR psz );
	CStringStream& operator<<( char c );
	CStringStream& operator<<( long d );
	CStringStream& operator<<( int d );
	CStringStream& operator<<( short d );
	CStringStream& operator<<( double f );
	CStringStream& operator<<( float f );
	CStringStream& operator<<( const CByteArray& array );
	CStringStream& operator<<( const CLongBinary& blob );
	CStringStream& operator<<( const TIMESTAMP_STRUCT& date );

	CStringStream& operator<<( const CDBVariant& dbVariant );

	virtual void Write( const void* lpBuf, UINT nCount );

	virtual void WriteBytes( const BYTE* byBuf, UINT nCount);


	virtual char endl( ) ;
	virtual void setWidth( int nWidth ) ;
	virtual void setPrecision( int nPrecision);
	virtual void setFill( char chFill ) ;

	virtual void Init( int nWidth = 0, int nPrecision = 1, char chFill = ' ' );

	virtual bool OpenFile( LPCTSTR szFileName );
	virtual void CloseFile( );

	virtual void Flush( );

private:

	int m_nWidth;
	int m_nPrecision;
	char m_chFill;

	CStdioFile m_file;
	bool m_bFile;

	ostream* m_costream;

	bool m_bEmptyOnFlush;
};

#endif // !defined(AFX_STRINGSTREAM_H__INCLUDED_)
