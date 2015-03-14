// KeyGen.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "RegKey.h"
#include "GenKeyEx.h"

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code.  
// If you convert your extension to not be dependent on MFC,
// remove the comments around the following  DllMain() function.

/****

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  dwReason, 
                       LPVOID lpReserved )
{
    switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

****/

int __stdcall GenKeyEx(LPTSTR argv[], LPTSTR szKeyMsg, LPTSTR szKey)
{
	if( szKeyMsg == NULL || szKey == NULL )
	{
		return ERC_INTERNAL;
	}

	// try to initialize MFC
	if ( !AfxWinInit( ::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0 ) )
	{
		_tcscpy(szKey, _T(" \0"));
		_tcscpy(szKeyMsg, _T("MFC Failed to Initialize.\0"));
		return ERC_INTERNAL;
	}


	int nStatus = ERC_SUCCESS;

	int argc = CSwitch::GetArgCount(argv);

	CSwitch sw(&argc, argv, false, true, false);

	// Mandatory
	LPCTSTR szPurchaseId = sw.GetString( "PURCHASE_ID", "" );
	LPCTSTR szRunningNo = sw.GetString( "RUNNING_NO", "" );
	LPCTSTR szProductId = sw.GetString( "PRODUCT_ID", "" );
	LPCTSTR szQuantity = sw.GetString( "QUANTITY", "" );
	LPCTSTR szLanguageId = sw.GetString( "LANGUAGE_ID", "" );

	LPCTSTR szPurchaseDate = sw.GetString( "PURCHASE_DATE", "" );
	LPCTSTR szRegName = sw.GetString( "REG_NAME", "" );

	if( _tcslen(szRegName) < 8 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <REG_NAME> , Minimum 8 characters required\r\n\0"));
	}
	if( _tcslen(szPurchaseId) < 4 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <PURCHASE_ID>\r\n\0"));
	}
	if( _tcslen(szRunningNo) < 1 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <RUNNING_NO>\r\n\0"));
	}

	// Optional
	LPCTSTR szAdditional1 = sw.GetString( "ADDITIONAL1", "" );
	LPCTSTR szAdditional2 = sw.GetString( "ADDITIONAL2", "" );
	LPCTSTR szReseller = sw.GetString( "RESELLER", "" );
	LPCTSTR szLastName = sw.GetString( "LASTNAME", "" );
	LPCTSTR szFirstName = sw.GetString( "FIRSTNAME", "" );
	LPCTSTR szCompany = sw.GetString( "COMPANY", "" );
	LPCTSTR szEmail = sw.GetString( "EMAIL", "" );
	LPCTSTR szPhone = sw.GetString( "PHONE", "" );
	LPCTSTR szFax = sw.GetString( "FAX", "" );
	LPCTSTR szStreet = sw.GetString( "STREET", "" );
	LPCTSTR szZip = sw.GetString( "ZIP", "" );
	LPCTSTR szState = sw.GetString( "STATE", "" );
	LPCTSTR szCountry = sw.GetString( "COUNTRY", "" );

	try
	{
		if( nStatus == ERC_SUCCESS )
		{
			CString strMessage = CString(CRegKey::szMessage);
			CString strPwd = CRegKey::GetPassword(CRegKey::GetRegNo(szPurchaseId, szRunningNo), szRegName);

			CCryptByteArray* cba = new CCryptByteArray();

			cba->Init( strPwd, true );
			cba->Set( strMessage );
			cba->EnCrypt();

			if( cba->GetSuccess() )
			{
				CString strKey = cba->GetHexString();

				_tcscpy(szKey, CRegKey::GetShortMessage(CRegKey::GetRegNo(szPurchaseId, szRunningNo), szRegName, strKey));
				_tcscpy(szKeyMsg, CRegKey::GetMessage(CRegKey::GetRegNo(szPurchaseId, szRunningNo), szRegName, strKey));
			}
			else
			{
				nStatus = ERC_INTERNAL;
				_tcscpy(szKeyMsg, _T(cba->GetString()));
			}
			delete cba;
		}
	}
	catch( CMemoryException* pEx )
	{
		nStatus = ERC_MEMORY;
		_tcscpy(szKeyMsg, _T("Out-of-memory\0"));

		pEx->Delete();
	}
	catch( CException* pEx )
	{
		nStatus = ERC_INTERNAL;
		pEx->GetErrorMessage(szKeyMsg, 1024);

		pEx->Delete();
	}

//	nStatus = CRegKey::DecKey(CRegKey::GetRegNo(szPurchaseId, szRunningNo), szRegName, szKey, szKeyMsg);

/*
	_stprintf(szKeyMsg, 
		_T("[%d] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s]"), 
		argc,
		szPurchaseId , szRunningNo , szProductId , szQuantity , szLanguageId ,
		szPurchaseDate , szRegName , szAdditional1 , szAdditional2 , szReseller ,
		szLastName , szFirstName , szCompany , szEmail , szPhone ,
		szFax , szStreet , szZip , szState , szCountry 
	);
*/


	if( _tcslen(szKey) < 1 )
		_tcscpy(szKey, _T(" \0"));

	if( _tcslen(szKeyMsg) < 1 )
		_tcscpy(szKeyMsg, _T(" \0"));

	return nStatus;
}



int __stdcall DecKeyEx(LPTSTR argv[], LPTSTR szKeyMsg)
{
	if( szKeyMsg == NULL )
	{
		return ERC_INTERNAL;
	}

	// try to initialize MFC
	if ( !AfxWinInit( ::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0 ) )
	{
		_tcscpy(szKeyMsg, _T("MFC Failed to Initialize.\0"));
		return ERC_INTERNAL;
	}

	int nStatus = ERC_SUCCESS;

	int argc = CSwitch::GetArgCount(argv);

	CSwitch sw(&argc, argv, false, true, false);

	// Mandatory
	LPCTSTR szRegNo = sw.GetString( "REG_NO", "" );
	LPCTSTR szRegName = sw.GetString( "REG_NAME", "" );
	LPCTSTR szKey = sw.GetString( "REG_KEY", "" );

	if( _tcslen(szRegName) < 1 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <REG_NAME>\r\n\0"));
	}
	if( _tcslen(szRegNo) < 1 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <REG_NO>\r\n\0"));
	}
	if( _tcslen(szKey) < 1 ) 
	{
		nStatus = ERC_BAD_INPUT;
		_tcscat(szKeyMsg, _T("Invalid <REG_KEY>\r\n\0"));
	}

	if( nStatus == ERC_SUCCESS )
	{
		nStatus = CRegKey::DecKey(szRegNo, szRegName, szKey, szKeyMsg);
	}

	return nStatus;
}
