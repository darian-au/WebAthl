// CFormat.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HtmlMonth.h"
#include "Convert.h"
#include "Format.h"

#include "RegistrationTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Format

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CFormat::CFormat( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CFormat::~CFormat( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CFormat::FormatRegistration(int nYearValid, int nRegistrationTypeID, LPCTSTR szConnect)
{
	int nMonthStart;
	int nMonthStop;
	CString strRegistrationDescription;

	try
	{
		CString strSQL;

		CDatabase db;
	
		db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

		strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %d ", nRegistrationTypeID );
		CRegistrationTypeSet rs( &db );
		rs.Open(CRecordset::dynaset, strSQL );
	
		nMonthStart = rs.m_MonthStart;
		nMonthStop = rs.m_MonthStop;
		strRegistrationDescription = rs.m_RegistrationDescription;

		rs.Close( );
		db.Close( );

		return FormatRegistration(nYearValid, nMonthStart, nMonthStop, strRegistrationDescription);
	}
	catch (CDBException* pEx)
	{
		CString strError = pEx->m_strError;

		pEx->Delete();

		return strError;
	}
}


CString CFormat::FormatRegistration(int nYearValid, int nMonthStart, int nMonthStop, LPCTSTR szRegistrationDescription)
{
	CString strReg;
	CString strDesc;

	if( _tcslen(szRegistrationDescription) > 0 )
		strDesc.Format("%s ; ", szRegistrationDescription);


	if( (nMonthStop == 0) && (nMonthStart == 0) )
	{
		strReg.Format("%sfrom %d", strDesc, nYearValid);
	}
	else if( (nMonthStop - nMonthStart) == 0 )
	{
		strReg.Format("%s%s %d", strDesc, CHtmlMonth::GetName(nMonthStart), nYearValid);
	}
	else if( (nMonthStop - nMonthStart) >  0 )
	{
		strReg.Format("%s%s %d to %s %d", strDesc, CHtmlMonth::GetName(nMonthStart), nYearValid, CHtmlMonth::GetName(nMonthStop), nYearValid);
	}
	else if( (nMonthStop - nMonthStart) <  0 )
	{
		strReg.Format("%s%s %d to %s %d", strDesc, CHtmlMonth::GetName(nMonthStart), nYearValid, CHtmlMonth::GetName(nMonthStop), nYearValid+1);
	}

	return strReg;
}


CString CFormat::FormatName(LPCTSTR szLastName, LPCTSTR szFirstName, LPCTSTR szMiddleName)
{
	CString str;

	if( _tcslen(szFirstName) > 0 )
	{
		str += szLastName;
		str += " , ";
		str += szFirstName;
		str += " ";
		str += szMiddleName;
	}
	else
	{
		str += szLastName;
	}
	
	return str;
}


CString CFormat::FormatDate(int nDateDAY, int nDateMONTH, int nDateYEAR)
{
	CString str;


	if( CRecordsetEx::IsItemNull(nDateDAY) && 
		CRecordsetEx::IsItemNull(nDateMONTH)  && 
		CRecordsetEx::IsItemNull(nDateYEAR)  )
	{
		str.Format( CRecordsetEx::m_szNull );
	}
	else
	{
		str.Format( "%s %s %s",
			_T( CConvert::itoa(nDateDAY) ),
			_T( CHtmlMonth::GetName(nDateMONTH) ),
			_T( CConvert::itoa(nDateYEAR) )  );
	}

	return str ;
}


CString CFormat::FormatPerf(int nTimed, int nPerfHOUR, int nPerfMIN, double dPerfSEC)
{
//	Timed = 1 -> Long Distance
//	Timed = 0 -> Jump or Throw
//	Timed = 2 -> Sprint

	CString str;

	switch(nTimed)
	{
		case 0 : // Jump or Throw
		{
			str.Format( CConvert::dtoa(dPerfSEC) );
			break;
		}
		case 1 : //Long Distance
		{
			if( CRecordsetEx::IsItemNull(nPerfHOUR) && 
				CRecordsetEx::IsItemNull(nPerfMIN)  && 
				CRecordsetEx::IsItemNull(dPerfSEC)  )
			{
				str.Format( CRecordsetEx::m_szNull );
			}
			else
			{
				str.Format( "%s:%s:%s",
					CConvert::itoa(nPerfHOUR, 2),
					CConvert::itoa(nPerfMIN, 2),
					CConvert::dtoa(dPerfSEC, 2,2 ) );
			}
			break;
		}
		case 2 : //	Sprint
		{
			if( CRecordsetEx::IsItemNull(nPerfMIN)  && 
				CRecordsetEx::IsItemNull(dPerfSEC)  )
			{
				str.Format( CRecordsetEx::m_szNull );
			}
			else
			{
				str.Format( "%s:%s",
					CConvert::itoa(nPerfMIN, 2),
					CConvert::dtoa(dPerfSEC, 2,2) );
			}
			break;
		}
	}

	return str ;
}

CString CFormat::FormatPerf(int nTimed, LPCTSTR szPerfHOUR, LPCTSTR szPerfMIN, LPCTSTR szPerfSEC, LPCTSTR szPerfJumpThrow)
{
//	Timed = 1 -> Long Distance
//	Timed = 0 -> Jump or Throw
//	Timed = 2 -> Sprint

	CString str;

	switch(nTimed)
	{
		case 0 : // Jump or Throw
		{
			str.Format( szPerfJumpThrow == NULL ? szPerfSEC : szPerfJumpThrow );
			break;
		}
		case 1 : //Long Distance
		{
			str.Format( "%s:%s:%s",
				szPerfHOUR,
				szPerfMIN,
				szPerfSEC );
			break;
		}
		case 2 : //	Sprint
		{
			str.Format( "%s:%s",
				szPerfMIN,
				szPerfSEC );
			break;
		}
	}

	return str ;
}
