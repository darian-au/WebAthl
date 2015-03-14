// RegKey.cpp :  implementation file
//

#include "stdafx.h"

#include "key_intf.h"
#include "RegKey.h"

/////////////////////////////////////////////////////////////////////////////
// CRegKey

LPCTSTR CRegKey::szMessage = _T("Web Athletics");
LPCTSTR CRegKey::szSecret = _T("Password");

/////////////////////////////////////////////////////////////////////////////
// Static functions

CString CRegKey::GetRegNo(LPCTSTR szPurchaseId, LPCTSTR szRunningNo)
{
	CString strRegNo;

	strRegNo.Format( _T("%s%s"), _T(szPurchaseId), _T(szRunningNo) );

	return strRegNo;
}

CString CRegKey::GetPassword(LPCTSTR szRegNo, LPCTSTR szRegName)
{
	CString strPwd;

	strPwd.Format( _T("%s%s%s"), _T(szRegNo), _T(szRegName), _T(CRegKey::szSecret) );

	return strPwd;
}

CString CRegKey::GetMessage(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey)
{
	CString strReg;
	
	strReg += _T("Your License Details are as follows : \r\n\r\n");
	strReg += _T("\tLicense No : %s\r\n\tLicense Name : %s\r\n\tLicense Key : %s\r\n");

	CString strMsg;

	strMsg.Format( strReg, _T(szRegNo), _T(szRegName), _T(szKey) );

	return strMsg;
}

CString CRegKey::GetShortMessage(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey)
{
	CString strMsg;

	strMsg.Format( _T("%s:%s:%s"), _T(szRegNo), _T(szRegName), _T(szKey) );

	return strMsg;
}

int CRegKey::DecKey(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey, LPTSTR szKeyMsg)
{
	int nStatus = ERC_SUCCESS;

	try
	{
		if( nStatus == ERC_SUCCESS )
		{
			CString strMessage = CString(CRegKey::szMessage);
			CString strPwd = CRegKey::GetPassword(szRegNo, szRegName);

			CCryptByteArray* cba = new CCryptByteArray();

			cba->Init( strPwd, true );
			cba->SetHexString( szKey );
			cba->DeCrypt();

			if( cba->GetSuccess() )
			{
				if( strMessage.Compare( cba->GetString() ) == 0 )
				{
					nStatus = ERC_SUCCESS;
					if( szKeyMsg != NULL )
						_tcscpy(szKeyMsg, _T("Valid License Details.\0"));
				}
				else
				{
					nStatus = ERC_ERROR;
					if( szKeyMsg != NULL )
						_tcscpy(szKeyMsg, _T("Invalid License Details.\0"));
				}
			}
			else
			{
				nStatus = ERC_INTERNAL;
				if( szKeyMsg != NULL )
					_tcscpy(szKeyMsg, _T(cba->GetString()));
			}
			delete cba;
		}
	}
	catch( CMemoryException* pEx )
	{
		nStatus = ERC_MEMORY;
		if( szKeyMsg != NULL )
			_tcscpy(szKeyMsg, _T("Out-of-memory\0"));

		pEx->Delete();
	}
	catch( CException* pEx )
	{
		nStatus = ERC_INTERNAL;
		if( szKeyMsg != NULL )
			pEx->GetErrorMessage(szKeyMsg, 1024);

		pEx->Delete();
	}

	return nStatus;
}