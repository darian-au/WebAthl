#if !defined(AFX_CCRYPT_H__INCLUDED_)
#define AFX_CCRYPT_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Crypt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrypt

class CCrypt 
{
	public:

		// Constructor
		//CCrypt();

		// Destructor
		//~CCrypt();

		// Member functions
		static DWORD Crypt(LPCTSTR szPassword, BOOL bEncrypt, char *pBuf, BYTE *pCyBuf, const int block_size);

		static BOOL IsCrypt(BYTE *pCyBuf);

		static USHORT GetCheckSum(const char *pBuf);

		// Static variables
		static LPCTSTR szCryptAcquireContextFailure;
		static LPCTSTR szCryptCreateHashFailure;
		static LPCTSTR szCryptHashDataFailure;
		static LPCTSTR szCryptDeriveKeyFailure;
		static LPCTSTR szCryptDecryptFailure;
		static LPCTSTR szCryptEncryptFailure;
		static LPCTSTR szCryptCheckSumFailure;


	private:

		// Member variables
		static BYTE m_dwTag[];

};

#endif // !defined(AFX_CCRYPT_H__INCLUDED_)
