// CSwitch.cpp : implementation file
//

#include "stdafx.h"

#include "Switch.h"

//#include <math.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitch

/////////////////////////////////////////////////////////////////////////////
// Constructor
CSwitch::CSwitch(int *nArgc, char **szArgv, 
				 bool bRemoveUsedSwitches,
				 bool bFirstIndexIsZero,
				 bool bCompareCase)
{
	m_nArgc = nArgc;
	m_szArgv = szArgv;

	m_bRemoveUsedSwitches = bRemoveUsedSwitches;
	if(bFirstIndexIsZero)
		m_bFirstIndex = 0;
	else
		m_bFirstIndex = 1;
	m_bCompareCase = bCompareCase;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor
//CSwitch::~CSwitch()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions
const char* CSwitch::GetString(char *szName, const char *szDefault, int nArgs)
{
	int i, nArgn;
	char *szRet;

	for(i = m_bFirstIndex ; i < *m_nArgc ; i++)
	{
		int nCompare; 
		
		if( m_bCompareCase )
			nCompare = strcmp(szName, m_szArgv[i]);
		else
			nCompare = stricmp(szName, m_szArgv[i]);

		if( nCompare == 0)
		{
			nArgn = i+1;

			if (i + nArgs >= *m_nArgc)
			{
				cerr << "Missing argument after \"" << m_szArgv[i] << "\"" << endl;
				exit(2);
			}

			szRet = m_szArgv[nArgs ? i+1 : i];

			if( m_bRemoveUsedSwitches )
			{
				nArgn = i + 1 + nArgs;
				while(nArgn < *m_nArgc)
					m_szArgv[i++] = m_szArgv[nArgn++];

				*m_nArgc = *m_nArgc - nArgn + i;
			}

			if (nArgs-- <= 1) 
				return(szRet);

			while(nArgs--) 
				szRet[strlen(szRet)] = ' ';

			return(szRet);
		}
	}
	return(szDefault);
}

bool CSwitch::GetBoolean(char *szName)
{
	return(GetString(szName, NULL, 0) != NULL);
}

long CSwitch::GetLong(char *szName, long nDefault)
{
	const char *szRes;
	char *szPtr;
	int nVal;

	szRes = GetString(szName, NULL, 1);

	if (szRes == NULL) 
		return(nDefault);

	nVal = strtol(szRes, &szPtr, 0);
	if (*szPtr)
	{
		cerr << "Integer argument to \"" << szName << "\" expected" << endl;
		exit(2);
	}
	return(nVal);
}

double CSwitch::GetDouble(char *szName, double dDefault)
{
	const char *szRes;
	char *szPtr;
	double dVal;

	szRes = GetString(szName, NULL, 1);

	if (szRes == NULL) 
		return(dDefault);

	dVal = strtod(szRes, &szPtr);
	if (*szPtr)
	{
		cerr << "Numeric argument to \"" << szName << "\" expected" << endl;
		exit(2);
	}
	return(dVal);
}

/* Assume that **szArgv is NULL terminated, ie.
 *
 *    **szArgv -> [*psz, *psz, *psz, ..., NULL]
 *
 */
int CSwitch::GetArgCount(char **szArgv)
{
	int nArgc;
	
	if (!szArgv) 
		return -1;

	for( nArgc = 0 ; szArgv[nArgc] ; nArgc++ )
		;

	return nArgc;
}
