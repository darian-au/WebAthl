// CCrypt.cpp : implementation file
//

#include "stdafx.h"

#include "Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrypt

BYTE CCrypt::m_dwTag[] = "DAR ";

LPCTSTR CCrypt::szCryptAcquireContextFailure = _T("Crypt Acquire Context Failure");
LPCTSTR CCrypt::szCryptCreateHashFailure = _T("Crypt Create Hash Failure");
LPCTSTR CCrypt::szCryptHashDataFailure = _T("Crypt Hash Data Failure");
LPCTSTR CCrypt::szCryptDeriveKeyFailure = _T("Crypt Derive Key Failure");
LPCTSTR CCrypt::szCryptDecryptFailure = _T("Crypt Decrypt Failure");
LPCTSTR CCrypt::szCryptEncryptFailure = _T("Crypt Encrypt Failure");
LPCTSTR CCrypt::szCryptCheckSumFailure = _T("Crypt CheckSum Failure");

/////////////////////////////////////////////////////////////////////////////
// Constructor
//CCrypt::CCrypt()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor
//CCrypt::~CCrypt()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions
DWORD CCrypt::Crypt(LPCTSTR szPassword, BOOL bEncrypt, char *pBuf, BYTE *pCyBuf, const int nBlockSize)
{
	HCRYPTHASH hHash = 0;
	DWORD dwLength;

	HCRYPTPROV	hProv = 0;
	HCRYPTKEY	hKey = 0;

	BYTE	*pbBuffer;
	DWORD	dwCount;
	//BYTE	m_dwTag[ ] = "DAR ";

	DWORD	dwError = 0;

	int nBufSize = nBlockSize + 16;	// Give buffer 16 bytes of extra room
									// for padding, and so forth.

	pbBuffer = (BYTE*) malloc( nBufSize );

	// Get a handle to the default provider.
	if(!CryptAcquireContext(&hProv, 0, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_MACHINE_KEYSET ))
	{
	    dwError = GetLastError();

		if( dwError == NTE_BAD_KEYSET )
		{
			dwError = 0;
			// Get a handle to the default provider, and create the key if it does not exist
			if(!CryptAcquireContext(&hProv, 0, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_MACHINE_KEYSET | CRYPT_NEWKEYSET))
			{
			    dwError = GetLastError();
				_stprintf(pBuf, "%s", CCrypt::szCryptAcquireContextFailure );
			}
		}
	}
	if(dwError == 0)
	{
		// Create a hash object.
		if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
		{
		    dwError = GetLastError();
			_stprintf(pBuf, "%s", CCrypt::szCryptCreateHashFailure );
		}
		else
		{
			// Hash the password string.
			dwLength = _tcslen(szPassword);

			if(!CryptHashData(hHash, (BYTE *)szPassword, dwLength, 0))
			{
			    dwError = GetLastError();
				_stprintf(pBuf, "%s", CCrypt::szCryptHashDataFailure );
			}
			else
			{
				// Create a block cipher session key based on the hash of the password.
				if(!CryptDeriveKey(hProv, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hKey))
				{
				    dwError = GetLastError();
					_stprintf(pBuf, "%s", CCrypt::szCryptDeriveKeyFailure );
				}
				else
				{
					if(bEncrypt)
					{
						// Encrypt

						USHORT usCheckSum = GetCheckSum(pBuf);


						dwCount = _tcslen(pBuf)+1; //take the null terminator at the end of the string too

						memcpy(pbBuffer, pBuf, dwCount);

					    // Encrypt the data.
					    if(!CryptEncrypt(hKey, 0, TRUE, 0, pbBuffer, &dwCount, nBufSize))
					    {
						    dwError = GetLastError();
							_stprintf(pBuf, "%s", CCrypt::szCryptEncryptFailure );
					    }
						else
						{
						    // Write the data to the destination file.
							memcpy(pCyBuf+2*sizeof(DWORD)+sizeof(USHORT), pbBuffer, dwCount);

							// Store the length of the encrypted data.
							dwCount = dwCount + 2*sizeof(DWORD) + sizeof(USHORT);
							memcpy(pCyBuf, &dwCount, sizeof(DWORD));
							memcpy(pCyBuf+sizeof(DWORD), &usCheckSum, sizeof(USHORT));
							memcpy(pCyBuf+sizeof(DWORD)+sizeof(USHORT), &m_dwTag, sizeof(DWORD));
						}
					}
					else
					{
						// Decrypt

						USHORT usOldCheckSum;

						memcpy(&usOldCheckSum, pCyBuf+sizeof(DWORD), sizeof(USHORT));

						memcpy(&dwCount, pCyBuf, sizeof(DWORD));

						dwCount = dwCount - 2*sizeof(DWORD) - sizeof(USHORT);

						memcpy(pbBuffer, pCyBuf+2*sizeof(DWORD)+sizeof(USHORT), dwCount);

					    // Decrypt the data.
						if(!CryptDecrypt(hKey, 0, TRUE, 0, pbBuffer, &dwCount))
						{
						    dwError = GetLastError();
							_stprintf(pBuf, "%s", CCrypt::szCryptDecryptFailure );
						}
						else
						{
							// Write the data to the destination file.
							memcpy(pBuf, pbBuffer, dwCount);

							USHORT usNewCheckSum = GetCheckSum(pBuf);

							if( usNewCheckSum != usOldCheckSum)
							{
								_stprintf(pBuf, "%s", CCrypt::szCryptCheckSumFailure );
							}
						}
					}
				}
			}
		}
	}
	// Destroy the hash object.
	if(hHash != 0) CryptDestroyHash(hHash);

	// Destroy the session key.
	if(hKey != 0) CryptDestroyKey(hKey);

	// Release the provider handle.
	if(hProv != 0) CryptReleaseContext(hProv, 0);

	if (dwError != 0)
		return dwError;
	else
		return dwCount;
}




BOOL CCrypt::IsCrypt(BYTE *pCyBuf)
{
	DWORD	dwCount;
	//BYTE	m_dwTag[ ] = "DAR ";
	BYTE	dwIdent[5];

	int i;

	dwIdent[4] = 0;

	memcpy(&dwCount, pCyBuf, sizeof(DWORD));

	for( i = 0 ; i < sizeof(DWORD) ; i++ )
	{
		memcpy(&(dwIdent[i]), pCyBuf+sizeof(DWORD)+sizeof(USHORT)+i*sizeof(BYTE), sizeof(BYTE));
	}

	if( !memcmp( dwIdent, m_dwTag, sizeof(DWORD) ) )
	{
		if( dwCount > 2*sizeof(DWORD)+sizeof(USHORT) )
		{
			return TRUE;
		}
	}
	return FALSE;
}


USHORT CCrypt::GetCheckSum(const char *pBuf)
{
	int nLen = _tcslen(pBuf);

	ULONG ulSum = 0;

	for( int nIndex = 0 ; nIndex < nLen ; nIndex++ )
	{
		ulSum += pBuf[nIndex];

		if( ulSum & 0xFFFF0000 )
		{
			// carry occurred, so wrap around

			ulSum &= 0x0000FFFF;
			ulSum++;
		}
	}

	return (USHORT) ~(ulSum & 0x0000FFFF);
}










