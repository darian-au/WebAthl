// Registry.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistry

/////////////////////////////////////////////////////////////////////////////
// Constructor

CRegistry::CRegistry( LPCTSTR szCompany, LPCTSTR szProgram, LPCTSTR szProfile, DWORD dwLen)
{
	m_strCompany.Format(szCompany);
	m_strProgram.Format(szProgram);

	m_dwLen = dwLen;

	SetProfile( szProfile );
}

CRegistry::CRegistry( LPCTSTR szCompany, LPCTSTR szProgram, DWORD dwLen )
{
	m_strCompany.Format(szCompany);
	m_strProgram.Format(szProgram);

	m_dwLen = dwLen;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CRegistry::~CRegistry( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CRegistry::SetProfile( LPCTSTR szProfile )
{
	m_strProfile.Format(szProfile);

	m_strProfile.Replace('/', '_');
	m_strProfile.Replace('\\', '_');
}

LONG CRegistry::Get(LPCTSTR szSection, LPCTSTR szKey, CString* strValue)
{
	HKEY    hKeySoftware;
	HKEY    hKeyCompany;
	HKEY    hKeyProgram;
	HKEY    hKeyProfile;
	HKEY    hKeySection;
    
	LONG    nStatus;

	DWORD   dwRegType;

	DWORD   dwLen = m_dwLen;	
	LPTSTR  szValue = strValue->GetBuffer( dwLen );

	nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
						  TEXT("SOFTWARE"),
						  0,
						  KEY_READ,
						  &hKeySoftware);

	if (nStatus == ERROR_SUCCESS) 
	{

		nStatus = RegOpenKeyEx(hKeySoftware,
							  TEXT((LPCTSTR)m_strCompany),
							  0,
							  KEY_READ,
							  &hKeyCompany);

		if (nStatus == ERROR_SUCCESS) 
		{

			nStatus = RegOpenKeyEx(hKeyCompany,
								  TEXT((LPCTSTR)m_strProgram),
								  0,
								  KEY_READ,
								  &hKeyProgram);

			if (nStatus == ERROR_SUCCESS) 
			{

				nStatus = RegOpenKeyEx(hKeyProgram,
									  TEXT((LPCTSTR)m_strProfile),
									  0,
									  KEY_READ,
									  &hKeyProfile);

				if (nStatus == ERROR_SUCCESS) 
				{

					nStatus = RegOpenKeyEx(hKeyProfile,
										  TEXT(szSection),
										  0,
										  KEY_READ,
										  &hKeySection);

					if (nStatus == ERROR_SUCCESS) 
					{

						nStatus = RegQueryValueEx(hKeySection,
												 TEXT(szKey),
												 NULL,
												 &dwRegType,
												 (LPBYTE)szValue,
												 &dwLen);

						RegCloseKey(hKeySection);
					}
					RegCloseKey(hKeyProfile);
				}
				RegCloseKey(hKeyProgram);
			}
			RegCloseKey(hKeyCompany);
		}
		RegCloseKey(hKeySoftware);
	}

	strValue->ReleaseBuffer( );

	return nStatus;
}


LONG CRegistry::Set(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue)
{
	HKEY    hKeySoftware;
	HKEY    hKeyCompany;
	HKEY    hKeyProgram;
	HKEY    hKeyProfile;
	HKEY    hKeySection;
    
	LONG    nStatus;


	nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
						  TEXT("SOFTWARE"),
						  0,
						  KEY_WRITE,
						  &hKeySoftware);

	if (nStatus == ERROR_SUCCESS) 
	{
		nStatus = RegCreateKeyEx(hKeySoftware,
								TEXT((LPCTSTR)m_strCompany),
								0,
								NULL,
								REG_OPTION_NON_VOLATILE,
								KEY_WRITE,
								NULL,
								&hKeyCompany,
								NULL);

		if (nStatus == ERROR_SUCCESS) 
		{

			nStatus = RegCreateKeyEx(hKeyCompany,
									TEXT((LPCTSTR)m_strProgram),
									0,
									NULL,
									REG_OPTION_NON_VOLATILE,
									KEY_WRITE,
									NULL,
									&hKeyProgram,
									NULL);

			if (nStatus == ERROR_SUCCESS) 
			{

				nStatus = RegCreateKeyEx(hKeyProgram,
										TEXT((LPCTSTR)m_strProfile),
										0,
										NULL,
										REG_OPTION_NON_VOLATILE,
										KEY_WRITE,
										NULL,
										&hKeyProfile,
										NULL);

				if (nStatus == ERROR_SUCCESS) 
				{

					nStatus = RegCreateKeyEx(hKeyProfile,
											TEXT(szSection),
											0,
											NULL,
											REG_OPTION_NON_VOLATILE,
											KEY_WRITE,
											NULL,
											&hKeySection,
											NULL);

					if (nStatus == ERROR_SUCCESS) 
					{

						//if(strcmp(szValue,""))
						//{
							nStatus = RegSetValueEx(hKeySection,
												   TEXT(szKey),
												   NULL,
												   REG_SZ,
												   (LPBYTE)szValue,
												   strlen(szValue));
						//}

						RegCloseKey(hKeySection);
					}
					RegCloseKey(hKeyProfile);
				}
				RegCloseKey(hKeyProgram);
			}
			RegCloseKey(hKeyCompany);
		}
		RegCloseKey(hKeySoftware);
	}
	return nStatus;
}




LONG CRegistry::GetComputerName(CString* strValue)
{
    HKEY    hKeySystem;
    HKEY    hKeyControlSet;
    HKEY    hKeyControl;
    HKEY    hKeyComputerName;
    HKEY    hKeyTarget;
    
    LONG    nStatus;

    DWORD   dwRegType;

	DWORD   dwLen = m_dwLen;	
	LPTSTR  szValue = strValue->GetBuffer( dwLen );

    nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                          TEXT("SYSTEM"),
                          0,
                          KEY_READ,
                          &hKeySystem);

    if (nStatus == ERROR_SUCCESS) {

        nStatus = RegOpenKeyEx(hKeySystem,
                              TEXT("CurrentControlSet"),
                              0,
                              KEY_READ,
                              &hKeyControlSet);

        if (nStatus == ERROR_SUCCESS) {

            nStatus = RegOpenKeyEx(hKeyControlSet,
                                  TEXT("Control"),
                                  0,
                                  KEY_READ,
                                  &hKeyControl);

            if (nStatus == ERROR_SUCCESS) {

                nStatus = RegOpenKeyEx(hKeyControl,
                                      TEXT("ComputerName"),
                                      0,
                                      KEY_READ,
                                      &hKeyComputerName);

                if (nStatus == ERROR_SUCCESS) {

                    nStatus = RegOpenKeyEx(hKeyComputerName,
                                          TEXT("ComputerName"),
                                          0,
                                          KEY_READ,
                                          &hKeyTarget);

                    if (nStatus == ERROR_SUCCESS) {

                        nStatus = RegQueryValueEx(hKeyTarget,
                                                 TEXT("ComputerName"),
                                                 NULL,
                                                 &dwRegType,
                                                 (LPBYTE)szValue,
                                                 &dwLen);

                        RegCloseKey(hKeyTarget);
                    }
                    RegCloseKey(hKeyComputerName);
                }
                RegCloseKey(hKeyControl);
            }
            RegCloseKey(hKeyControlSet);
        }
        RegCloseKey(hKeySystem);
    }

	strValue->ReleaseBuffer( );
    
    return nStatus;
}


LONG CRegistry::GetWinZipLocation(CString* strValue)
{
    HKEY    hKeySoftware;
    HKEY    hKeyMicrosoft;
    HKEY    hKeyWindows;
    HKEY    hKeyCurrentVersion;
    HKEY    hKeyAppPaths;
    HKEY    hKeyTarget;

    LONG    nStatus;

    DWORD   dwRegType;

	DWORD   dwLen = m_dwLen;	
	LPTSTR  szValue = strValue->GetBuffer( dwLen );

	//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\winzip32.exe

    nStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                          TEXT("SOFTWARE"),
                          0,
                          KEY_READ,
                          &hKeySoftware);

    if (nStatus == ERROR_SUCCESS) {

        nStatus = RegOpenKeyEx(hKeySoftware,
                              TEXT("Microsoft"),
                              0,
                              KEY_READ,
                              &hKeyMicrosoft);

        if (nStatus == ERROR_SUCCESS) {

            nStatus = RegOpenKeyEx(hKeyMicrosoft,
                                  TEXT("Windows"),
                                  0,
                                  KEY_READ,
                                  &hKeyWindows);

            if (nStatus == ERROR_SUCCESS) {

                nStatus = RegOpenKeyEx(hKeyWindows,
                                      TEXT("CurrentVersion"),
                                      0,
                                      KEY_READ,
                                      &hKeyCurrentVersion);

                if (nStatus == ERROR_SUCCESS) {

                    nStatus = RegOpenKeyEx(hKeyCurrentVersion,
                                          TEXT("App Paths"),
                                          0,
                                          KEY_READ,
                                          &hKeyAppPaths);

	                if (nStatus == ERROR_SUCCESS) {

		                nStatus = RegOpenKeyEx(hKeyAppPaths,
			                                  TEXT("winzip32.exe"),
				                              0,
					                          KEY_READ,
						                      &hKeyTarget);

						if (nStatus == ERROR_SUCCESS) {

							nStatus = RegQueryValueEx(hKeyTarget,
								                     NULL,	//(Default) Key
									                 NULL,
										             &dwRegType,
											         (LPBYTE)szValue,
												     &dwLen);

							RegCloseKey(hKeyTarget);
					    }
                        RegCloseKey(hKeyAppPaths);
                    }
                    RegCloseKey(hKeyCurrentVersion);
                }
                RegCloseKey(hKeyWindows);
            }
            RegCloseKey(hKeyMicrosoft);
        }
        RegCloseKey(hKeySoftware);
    }

	strValue->ReleaseBuffer( );
    
	return nStatus;
}




