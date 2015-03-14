// CryptByteArray.cpp : implementation file
//

#include "stdafx.h"

#include "CryptByteArray.h"
#include "Crypt.h"
#include "MIMECode.h"
#include "Base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCryptByteArray

LPCTSTR CCryptByteArray::szHexStringDelim = _T("-");
LPCTSTR CCryptByteArray::szHexFormat = _T("%02X");

/////////////////////////////////////////////////////////////////////////////
// Constructor

CCryptByteArray::CCryptByteArray( )	
{
}

CCryptByteArray::CCryptByteArray( const CString& strSrc )	
{
	Set( strSrc );
}

CCryptByteArray::CCryptByteArray( const CByteArray& cbaSrc)
{
	Set( cbaSrc );
}

CCryptByteArray::CCryptByteArray( const BYTE* pBySrc, int nLen )	
{
	Set( pBySrc, nLen );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

CCryptByteArray::~CCryptByteArray( )
{
	CByteArray::RemoveAll( );
	CByteArray::FreeExtra( );

	CByteArray::~CByteArray( );
}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CCryptByteArray::GetString( )
{
	CString str;

	CopyByteArray( &str, this );

	return str;
}

CString CCryptByteArray::GetHexString( )
{
	CString str;

	HexString( &str, this );

	return str;
}

CString CCryptByteArray::GetBase64String( int nBytesPerLine )
{
	CString str;

	Base64String( &str, this, nBytesPerLine );

	return str;
}

DWORD CCryptByteArray::EnCrypt( )
{
	if( m_bCryptEnabled )
		return EnCrypt( m_strPassword );
	else
		return 0;
}

DWORD CCryptByteArray::DeCrypt( )
{
	return DeCrypt( m_strPassword );
}

void CCryptByteArray::Init( LPCTSTR szPassword, BOOL bCryptEnabled )
{
	m_strPassword = szPassword;
	m_bCryptEnabled = bCryptEnabled;
}


DWORD CCryptByteArray::EnCrypt( CString strPassword )
{
	DWORD dwLen = 0;

	// SQL NULL value : 
	// CByteArray[0] == AFX_RFX_BYTE_PSEUDO_NULL == 255

	if( !this->IsCrypt() && this->GetSize() > 1 )
	{
		// Need to copy the password, as CCrypt::Crypt( )
		// destroys it when it Hashes it.
		CString strPwd = strPassword;
		LPCTSTR szPwd = strPwd;

		CString str = this->GetString( );

		LPCTSTR psz = str;

		// Assume the Length of the Encrypted Data is no more
		// than 8 times the size of the Unencrypted Data.
		int nBufLen = str.GetLength( ) * sizeof(TCHAR) * 8;

		this->SetSize( nBufLen );

		BYTE *pBy = this->GetData( );

		memset(pBy, 0, nBufLen);
		dwLen = CCrypt::Crypt(szPwd, TRUE, (LPTSTR)psz, pBy, nBufLen);

		this->SetSize( dwLen );
	}

	return dwLen;
}

DWORD CCryptByteArray::DeCrypt( CString strPassword )
{
	DWORD dwLen = 0;

	if( this->IsCrypt() )
	{
		// Need to copy the password, as CCrypt::Crypt( )
		// destroys it when it Hashes it.
		CString strPwd = strPassword;
		LPCTSTR szPwd = strPwd;

		int nBufLen = this->GetSize( ) * sizeof(TCHAR);

		CString str;
		LPTSTR psz = str.GetBuffer( nBufLen );

		dwLen = CCrypt::Crypt(szPwd, FALSE, psz, this->GetData( ), nBufLen);

		str.ReleaseBuffer( );
		CopyByteArray( this, &str );
	}

	return dwLen;
}

int CCryptByteArray::Copy( CByteArray* cbaDst )
{
	return CopyByteArray( cbaDst, this );
}

int CCryptByteArray::Set( const CString& strSrc )	
{
	return CopyByteArray( this, &strSrc );
}

int CCryptByteArray::Set( LPCTSTR szSrc )	
{
	return CopyByteArray( this, &CString(szSrc) );
}

int CCryptByteArray::Set( const CByteArray& cbaSrc)
{
	return CopyByteArray( this, &cbaSrc );
}

int CCryptByteArray::Set( const BYTE* pBySrc, int nLen )	
{
	return CopyByteArray( this, pBySrc, nLen );
}

int CCryptByteArray::SetHexString( LPCTSTR szHexSrc )	
{
	return HexString(this, szHexSrc);
}

int CCryptByteArray::SetBase64String( LPCTSTR szBase64Src )	
{
	return Base64String(this, szBase64Src);
}

BOOL CCryptByteArray::IsCrypt( )
{
	if( this->GetSize() > 2*sizeof(DWORD)+sizeof(USHORT) )
	{
		return CCrypt::IsCrypt(this->GetData( ));
	}
	else
	{
		return FALSE;
	}
}

void CCryptByteArray::Clear( )
{
	Clear( this );
}

BOOL CCryptByteArray::GetSuccess( )
{
	CString str = this->GetString( );

	BOOL bSuccess = TRUE;

	if( !str.Compare( CCrypt::szCryptAcquireContextFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptCreateHashFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptHashDataFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptDeriveKeyFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptDecryptFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptEncryptFailure ) )
	{
		bSuccess = FALSE;
	}
	else if( !str.Compare( CCrypt::szCryptCheckSumFailure ) )
	{
		bSuccess = FALSE;
	}

	return bSuccess;
}

/////////////////////////////////////////////////////////////////////////////
// Static functions

void CCryptByteArray::Clear( CByteArray* cbaDst )
{
	int nLen = cbaDst->GetSize( );

	// Clear cbaDst (set it to 0's)
	//for( int i = 0 ; i < nLen ; i++ )
	//{
	//	cbaDst->SetAt( i, 0 );
	//}


	BYTE* pBy = cbaDst->GetData( );

	// Clear cbaDst (set it to 0's)
	memset(pBy, '\0', nLen);
}

int CCryptByteArray::CopyByteArray( CByteArray* cbaDst, const BYTE* pBySrc, int nLen )
{
	cbaDst->RemoveAll( );
	cbaDst->FreeExtra( );
	cbaDst->SetSize( nLen );
	Clear( cbaDst );

	for( int i = 0 ; i < nLen ; i++ )
	{
		cbaDst->SetAtGrow( i, pBySrc[i] );
	}

	return cbaDst->GetSize( );
}

int CCryptByteArray::CopyByteArray( BYTE* pByDst, const CByteArray* cbaSrc)
{
	int nLen = cbaSrc->GetSize( );

	memset(pByDst, 0, nLen);

	for( int i = 0 ; i < nLen ; i++ )
	{
		pByDst[i] = cbaSrc->GetAt( i );
	}

	return nLen;
}

int CCryptByteArray::CopyByteArray( CByteArray* cbaDst, const CByteArray* cbaSrc )
{
	int nLen = cbaSrc->GetSize( );

//	cbaDst->RemoveAll( );
//	cbaDst->FreeExtra( );
	cbaDst->SetSize( nLen );
	Clear( cbaDst );

	for( int i = 0 ; i < nLen  ; i++ )
	{
		cbaDst->SetAtGrow( i, cbaSrc->GetAt( i ) );
	}

	return nLen;
}

int CCryptByteArray::CopyByteArray( CByteArray* cbaDst, const CString* strSrc )
{
	int nLen = strSrc->GetLength( );

//	cbaDst->RemoveAll( );
//	cbaDst->FreeExtra( );
	cbaDst->SetSize( nLen );
	Clear( cbaDst );

	int i = 0;

	for( i = 0 ; i < nLen  ; i++ )
	{
		cbaDst->SetAtGrow( i, strSrc->GetAt( i ) );
	}
	cbaDst->SetAtGrow( i, '\0' );

	return nLen;
}

int CCryptByteArray::CopyByteArray( CString* strDst, const CByteArray* cbaSrc )
{
	int nLen = cbaSrc->GetSize( );

	strDst->Empty( );

	LPTSTR pszDst = strDst->GetBuffer( nLen +1 );

	int i;

	for( i = 0 ; i < nLen ; i++ )
	{
		//strDst->Insert( i, cbaSrc->GetAt( i ) );
		pszDst[i] = (TCHAR) cbaSrc->GetAt( i );
	}
	pszDst[i] = '\0';

	strDst->ReleaseBuffer( );

	return nLen;
}

int CCryptByteArray::CopyByteArray( LPTSTR pszDst, const BYTE* pBySrc, int nLen )
{
	int i;

	for( i = 0 ; i < nLen ; i++ )
	{
		pszDst[i] = (TCHAR) pBySrc[i];
	}
	pszDst[i] = '\0';

	return i;
}

int CCryptByteArray::CopyByteArray( BYTE* pByDst, LPCTSTR pszSrc, int nLen )
{
	int i;

	for( i = 0 ; i < nLen ; i++ )
	{
		pByDst[i] = (BYTE) pszSrc[i];
	}
	pByDst[i] = '\0';

	return i;
}

DWORD CCryptByteArray::HexString(CString* strDst, CByteArray* cbaSrc)	
{ 
	TCHAR szHex[3]; 
	int i; 

	int nLen = cbaSrc->GetSize( );

	LPTSTR psz = strDst->GetBuffer( 3 * nLen );

	for( i = 0; i < nLen; i++ )
	{ 
		_stprintf(szHex, szHexFormat, cbaSrc->GetAt(i) ); 
		//_tcscat(psz, szHex ); 

		//if( i < (nLen -1) )
		//	_tcscat(psz, szHexStringDelim ); 

		psz[i*3 + 0] = szHex[0];
		psz[i*3 + 1] = szHex[1];

		if( i < (nLen -1) )
			psz[i*3 + 2] = szHexStringDelim[0];
		else
			psz[i*3 + 2] = '\0';
	} 

	strDst->ReleaseBuffer( );

	return (DWORD)i;
} 


DWORD CCryptByteArray::HexString(CByteArray* cbaDst, LPCTSTR szSrc)
{
	TCHAR szHex[3]; 
	LPTSTR szTok;

	int i = 0;

	BYTE byDst;

	CString str = CString(szSrc);
	
	LPTSTR psz = str.GetBuffer( str.GetLength( ) );

	if(szTok = _tcstok(psz, szHexStringDelim))
	{
		_tcsncpy( szHex, szTok, 2 );
		_stscanf( szHex, szHexFormat, &byDst );
		cbaDst->SetAtGrow( i++, byDst );

		while(szTok = _tcstok(NULL, szHexStringDelim))
		{
			_tcsncpy( szHex, szTok, 2 );
			_stscanf( szHex, szHexFormat, &byDst );
			cbaDst->SetAtGrow( i++, byDst );
		}
	}

	str.ReleaseBuffer( );

	return (DWORD)i;
} 

DWORD CCryptByteArray::Base64String(CString* strDst, CByteArray* cbaSrc, int nBytesPerLine)	
{
	int nLen = cbaSrc->GetSize( );

	CMIMECode* pEncoder = new CBase64( nBytesPerLine );

	CString strBuf;

	LPTSTR psz = strBuf.GetBuffer( 2 * nLen );

	BYTE* pBy = cbaSrc->GetData( );

	CopyByteArray( psz, pBy, nLen );

	*strDst = pEncoder->Encode( psz, nLen );
	*strDst += pEncoder->GetPadding( nLen );

	strBuf.ReleaseBuffer( );

	delete pEncoder;

	return (DWORD)strDst->GetLength( );
} 

DWORD CCryptByteArray::Base64String(CByteArray* cbaDst, LPCTSTR szSrc)
{
	int nLen = _tcslen(szSrc);

	CMIMECode* pEncoder = new CBase64( );

	CString strBuf;
	LPTSTR pszBuf = strBuf.GetBuffer( nLen );

	nLen = pEncoder->Decode(szSrc, pszBuf);

	strBuf.ReleaseBuffer( nLen );

	CopyByteArray( cbaDst, &strBuf );

	delete pEncoder;

	return (DWORD)nLen;
} 
