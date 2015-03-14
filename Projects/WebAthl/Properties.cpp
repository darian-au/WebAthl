// Properties.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"
#include "Properties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProperties

/////////////////////////////////////////////////////////////////////////////
// Constructor

CProperties::CProperties( LPCTSTR szCompany, LPCTSTR szProgram, LPCTSTR szProfile )
	: CRegistry(szCompany, szProgram, szProfile)
{
}

CProperties::CProperties( LPCTSTR szCompany, LPCTSTR szProgram )
	: CRegistry(szCompany, szProgram)
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CProperties::~CProperties( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CProperties::Get(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue)
{
	CString strValue;

	LONG nStatus;

	nStatus = CRegistry::Get(szSection, szKey, &strValue);

	if (nStatus != ERROR_SUCCESS) 
	{
		strValue = szDefaultValue;
	}

	return strValue;
}

CString CProperties::GetComputerName()
{
	CString strValue;

	LONG nStatus;

	nStatus = CRegistry::GetComputerName(&strValue);

	if (nStatus != ERROR_SUCCESS) 
	{
		strValue = "";
	}

	return strValue;
}

CString CProperties::GetWinZipLocation()
{
	CString strValue;

	LONG nStatus;

	nStatus = CRegistry::GetWinZipLocation(&strValue);

	if (nStatus != ERROR_SUCCESS) 
	{
		strValue = "";
	}

	return strValue;
}




