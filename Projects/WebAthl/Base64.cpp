#include "stdafx.h"

#include "Base64.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// Static Member Initializers
//

// The 7-bit alphabet used to encode binary information
CString CBase64::m_sBase64Alphabet = 
_T( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" );

int CBase64::m_nMask[] = { 0, 1, 3, 7, 15, 31, 63, 127, 255 };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase64::CBase64(int nBytesPerLine)
{
	m_nBytesPerLine = nBytesPerLine;
	m_nBitsRemaining = 0;
}

CBase64::~CBase64()
{
}

CString CBase64::Encode(LPCTSTR szEncoding, int nSize)
{
	char *szOutput = new char[nSize*2];  // lazy/safe calculation
	int nNumBits = 6;
	UINT nDigit;
	int pos = 0;
	int target = m_nBytesPerLine;
	int lp = 0;
	CString strResult;

	ASSERT( szEncoding != NULL );

	if( szEncoding == NULL )
		return strResult;

	if( nSize == 0 )
		return strResult;

	m_szInput = szEncoding;
	m_nInputSize = nSize;

	m_nBitsRemaining = 0;

	nDigit = ReadBits( nNumBits, &nNumBits, lp );
	while( nNumBits > 0 )
	{
		szOutput[pos++] = m_sBase64Alphabet[ (int)nDigit ];

		nDigit = ReadBits( nNumBits, &nNumBits, lp );

		if(pos == target)
		{
			szOutput[pos++] = '\r';
			szOutput[pos++] = '\n';
			target = pos + m_nBytesPerLine;	 // Not including CR/LF, already handled
		}
	}

	szOutput[pos] = 0;
	strResult = szOutput;
	delete [] szOutput;
	
	return strResult;
}

// Pad with '=' as per RFC 1521
CString CBase64::GetPadding( int nBytesRead )
{
	char *szOutput = new char[4];

	CString strResult;
	int pos = 0;

	while( pos < (3 - nBytesRead % 3) % 3 )
	{
		szOutput[pos++] = '=';
	}

	szOutput[pos] = 0;
	strResult = szOutput;
	delete [] szOutput;

	return strResult;
}

// The size of the output buffer must not be less than
// 3/4 the size of the input buffer. For simplicity,
// make them the same size.
int CBase64::Decode(LPCTSTR szDecoding, LPTSTR szOutput)
{
	CString strInput;
    int c, lp = 0;
	int nDigit;
    int nDecode[ 256 ];

	ASSERT( szDecoding != NULL );
	ASSERT( szOutput != NULL );
	if( szOutput == NULL )
		return 0;

	if( szDecoding == NULL )
		return 0;

	strInput = szDecoding;

	if( strInput.GetLength() == 0 )
		return 0;

	// Build Decode Table
	//
	for( int i = 0; i < 256; i++ ) 
		nDecode[i] = -2; // Illegal digit

	for( int i = 0; i < 64; i++ )
	{
		nDecode[ m_sBase64Alphabet[ i ] ] = i;
		nDecode[ m_sBase64Alphabet[ i ] | 0x80 ] = i; // Ignore 8th bit
		nDecode[ '=' ] = -1; 
		nDecode[ '=' | 0x80 ] = -1; // Ignore MIME padding char
		nDecode[ '\r' ] = -1; 
		nDecode[ '\r' | 0x80 ] = -1; // Ignore CR/LF 
		nDecode[ '\n' ] = -1; 
		nDecode[ '\n' | 0x80 ] = -1; // Ignore CR/LF 
    }

	// Clear the output buffer
	memset( szOutput, '\0', strInput.GetLength() + 1 );

	// Decode the Input
	//
	int i;
	for( lp = 0, i = 0; lp < strInput.GetLength(); lp++ )
	{
		c = strInput[ lp ];
		nDigit = nDecode[ c & 0x7F ];
		if( nDigit < -1 ) 
		{
			return 0;
		} 
		else if( nDigit >= 0 ) 
			// i (index into output) is incremented by write_bits()
			WriteBits( nDigit & 0x3F, 6, szOutput, i );
    }	
	return i;
}




UINT CBase64::ReadBits(int nNumBits, int * pBitsRead, int& lp)
{
    ULONG lScratch;
    while( ( m_nBitsRemaining < nNumBits ) && 
		   ( lp < m_nInputSize ) ) 
	{
		int c = m_szInput[ lp++ ];
        m_lBitStorage <<= 8;
        m_lBitStorage |= (c & 0xff);
		m_nBitsRemaining += 8;
    }
    if( m_nBitsRemaining < nNumBits ) 
	{
		lScratch = m_lBitStorage << ( nNumBits - m_nBitsRemaining );
		*pBitsRead = m_nBitsRemaining;
		m_nBitsRemaining = 0;
    } 
	else 
	{
		lScratch = m_lBitStorage >> ( m_nBitsRemaining - nNumBits );
		*pBitsRead = nNumBits;
		m_nBitsRemaining -= nNumBits;
    }
    return (UINT)lScratch & m_nMask[nNumBits];
}


void CBase64::WriteBits(UINT nBits,
						int nNumBits,
						LPTSTR szOutput,
						int& i)
{
	UINT nScratch;

	m_lBitStorage = (m_lBitStorage << nNumBits) | nBits;
	m_nBitsRemaining += nNumBits;
	while( m_nBitsRemaining > 7 ) 
	{
		nScratch = m_lBitStorage >> (m_nBitsRemaining - 8);
		szOutput[ i++ ] = nScratch & 0xFF;
		m_nBitsRemaining -= 8;
	}
}

