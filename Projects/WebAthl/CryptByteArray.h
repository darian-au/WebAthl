#if !defined(AFX_CRYPTBYTEARRAY_H__INCLUDED_)
#define AFX_CRYPTBYTEARRAY_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CryptByteArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCryptByteArray string

class CCryptByteArray : public CByteArray
{

	public:

		// Constructor
		CCryptByteArray( );
		CCryptByteArray( const CString& strSrc );
		CCryptByteArray( const CByteArray& cbaSrc );
		CCryptByteArray( const BYTE* pBySrc, int nLen );

		// Destructor
		~CCryptByteArray( );

		// Member functions
		CString GetString( );
		CString GetHexString( );
		CString GetBase64String( int nBytesPerLine = 72 ); // Use nBytesPerLine = -1 for no CR/LF's

		DWORD EnCrypt( CString strPassword );
		DWORD DeCrypt( CString strPassword );

		DWORD EnCrypt( );
		DWORD DeCrypt( );

		void Init( LPCTSTR szPassword, BOOL bCryptEnabled );
		int Copy( CByteArray* cbaDst );
		int Set( const CString& strSrc );
		int Set( LPCTSTR szSrc );	
		int Set( const CByteArray& cbaSrc);
		int Set( const BYTE* pBySrc, int nLen );

		int SetHexString( LPCTSTR szHexSrc );
		int SetBase64String( LPCTSTR szBase64Src );

		void Clear( );

		BOOL IsCrypt( );
		BOOL GetSuccess( );

		// Static functions
		static int CopyByteArray( CByteArray* cbaDst, const BYTE* pBySrc, int nLen );
		static int CopyByteArray( BYTE* pByDst, const CByteArray* cbaSrc);
		static int CopyByteArray( CByteArray* cbaDst, const CByteArray* cbaSrc );
		static int CopyByteArray( CByteArray* cbaDst, const CString* strSrc );
		static int CopyByteArray( CString* strDst, const CByteArray* cbaSrc );

		static int CopyByteArray( LPTSTR pszDst, const BYTE* pBySrc, int nLen );
		static int CopyByteArray( BYTE* pByDst, LPCTSTR pszSrc, int nLen );

		static DWORD HexString( CString* strDst, CByteArray* cbaSrc );
		static DWORD HexString( CByteArray* cbaDst, LPCTSTR szSrc );

		static void Clear( CByteArray* cbaDst );

		static DWORD Base64String( CString* strDst, CByteArray* cbaSrc, int nBytesPerLine = 72 ); // Use nBytesPerLine = -1 for no CR/LF's
		static DWORD Base64String( CByteArray* cbaDst, LPCTSTR szSrc );

	private:

		// Member variables
		CString m_strPassword;
		BOOL m_bCryptEnabled;

		// Static variables
		static LPCTSTR szHexStringDelim;
		static LPCTSTR szHexFormat;
};

#endif // !defined(AFX_CRYPTBYTEARRAY_H__INCLUDED_)
