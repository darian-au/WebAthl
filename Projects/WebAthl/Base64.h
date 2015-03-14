#if !defined(AFX_BASE64_H__FD6A25D1_EE0E_11D1_870E_444553540001__INCLUDED_)
#define AFX_BASE64_H__FD6A25D1_EE0E_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MIMECode.h"

// CBase64
// An encoding agent that handles Base64
//
class CBase64 : public CMIMECode  
{
public:
	CBase64(int nBytesPerLine = 72); // Use nBytesPerLine = -1 for no CR/LF's
	virtual ~CBase64();

// Override the base class mandatory functions
	virtual int Decode( LPCTSTR szDecoding, LPTSTR szOutput );
	virtual CString Encode( LPCTSTR szEncoding, int nSize );
	virtual CString GetPadding( int nBytesRead );

protected:
	void WriteBits( UINT nBits, int nNumBts, LPTSTR szOutput, int& lp );
	UINT ReadBits( int nNumBits, int* pBitsRead, int& lp );

	int m_nInputSize;
	int m_nBitsRemaining;
	ULONG m_lBitStorage;
	LPCTSTR m_szInput;

	int m_nBytesPerLine;

	static int m_nMask[];
	static CString m_sBase64Alphabet;
private:
};

#endif // !defined(AFX_BASE64_H__FD6A25D1_EE0E_11D1_870E_444553540001__INCLUDED_)
