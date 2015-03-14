// CCalculate.cpp : implementation file
//

#include "stdafx.h"

#include <math.h>

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HttpServerProperties.h"
#include "Convert.h"
#include "Calculate.h"

#include "RegistrationTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Calculate

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CCalculate::CCalculate( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CCalculate::~CCalculate( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

int CCalculate::YearDiff(int nDay, int nMonth, int nYear)
{
	COleDateTime t = COleDateTime::GetCurrentTime();

	return CCalculate::YearDiff(nDay, nMonth, nYear, t.GetDay( ), t.GetMonth( ), t.GetYear( ));
}

int CCalculate::YearDiff(int nDay1, int nMonth1, int nYear1, int nDay2, int nMonth2, int nYear2)
{

	// special case for null Date, return null
	if( CRecordsetEx::IsItemNull(nYear1) ) 
		return nYear1; // return null

	if( CRecordsetEx::IsItemNull(nYear2) ) 
		return nYear2; // return null

	if( CRecordsetEx::IsItemNull(nMonth1) ) 
		return nMonth1; // return null

	if( CRecordsetEx::IsItemNull(nMonth2) ) 
		return nMonth2; // return null

	if( CRecordsetEx::IsItemNull(nDay1) ) 
		return nDay1; // return null

	if( CRecordsetEx::IsItemNull(nDay2) ) 
		return nDay2; // return null


	int nDiff = (nYear2 - nYear1);

	if(nMonth1 > nMonth2) 
		return nDiff-1;
	else
		if((nMonth1 == nMonth2) && (nDay1 > nDay2))
			return nDiff-1;

	return nDiff;
}


int CCalculate::GroupAge(int nAge, CString& strCategory, CHttpServerProperties* pProp)
{
	int nMaxJunior = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
	int nMinVeteran = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
	int nJuniorGroup = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
	int nVeteranGroup = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

	return GroupAge(nAge, strCategory, pProp, nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);
}

int CCalculate::GroupAge(int nAge, CString& strCategory, CHttpServerProperties* pProp, int nMaxJunior, int nMinVeteran, int nJuniorGroup, int nVeteranGroup)
{
	if( CRecordsetEx::IsItemNull( nAge ) )
	{
		strCategory.Format(CRecordsetEx::m_szNull);
		return atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::NullDoB));
	}
	else if(nAge >= nMinVeteran)
	{
		strCategory.Format("Veteran");
		return (nAge - (nAge % nVeteranGroup));
	}
	else if(nAge < nMaxJunior && nAge > 0)
	{
		strCategory.Format("Junior");
		return (nAge - (nAge % nJuniorGroup) + nJuniorGroup);
	}
	else
	{
		strCategory.Format("Open");
//		return nAge;
		return 0;
	}
}

int CCalculate::Current(COleDateTime t, int nYearValid, int nMonthStart, int nMonthStop)
{
	if( (nMonthStop == 0) && (nMonthStart == 0) )
	{
		if( ( t.GetYear ( ) >= nYearValid  ) )
		{
			return 1; // TRUE
		}
	}
	else if( (nMonthStop - nMonthStart) == 0 )
	{
		if( ( t.GetMonth( ) == nMonthStart ) && 
			( t.GetMonth( ) == nMonthStop  ) &&
			( t.GetYear ( ) <= nYearValid  ) )
		{
			if(t.GetYear ( ) < nYearValid)
				return 2; // TRUE; FUTURE
			else
				return 1; // TRUE
		}
	}
	else if( (nMonthStop - nMonthStart) >  0 )
	{
		if( ( t.GetMonth( ) >= nMonthStart ) && 
			( t.GetMonth( ) <= nMonthStop  ) && 
			( t.GetYear ( ) <= nYearValid  ) )
		{
			if(t.GetYear ( ) < nYearValid)
				return 2; // TRUE; FUTURE
			else
				return 1; // TRUE
		}
	}
	else if( (nMonthStop - nMonthStart) <  0 )
	{
		if( (( t.GetMonth( ) >= nMonthStart ) && ( t.GetYear( ) <= nYearValid   )) ) 
		{
			if(t.GetYear ( ) < nYearValid)
				return 2; // TRUE; FUTURE
			else
				return 1; // TRUE
		}

		if( (( t.GetMonth( ) <= nMonthStop  ) && ( t.GetYear( ) <= nYearValid +1)) ) 
		{
			if(t.GetYear ( ) < nYearValid +1)
				return 2; // TRUE; FUTURE
			else
				return 1; // TRUE
		}
	}

	return 0; //FALSE
}


int CCalculate::Current(int nYearValid, int nMonthStart, int nMonthStop)
{
	COleDateTime today = COleDateTime::GetCurrentTime();

	return ( Current(today, nYearValid, nMonthStart, nMonthStop) );
}


int CCalculate::Current(int nYearValid, int nRegistrationTypeID, LPCTSTR szConnect)
{
	int nMonthStart;
	int nMonthStop;

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

		rs.Close( );
		db.Close( );

		return ( Current(nYearValid, nMonthStart, nMonthStop) );
	}
	catch (CDBException* pEx)
	{
		pEx->m_strError;

		pEx->Delete();
	}

	return 0; //FALSE
}

int CCalculate::GetCurrentYear(int nRegistrationTypeID, LPCTSTR szConnect)
{
	COleDateTime t = COleDateTime::GetCurrentTime();

	int nMonthStart = 0;
	int nMonthStop = 0;

	CString strSQL;

	try
	{
		CDatabase db;
	
		db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

		strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %d ", nRegistrationTypeID );
		CRegistrationTypeSet rs( &db );
		rs.Open(CRecordset::dynaset, strSQL );
	
		if( !rs.IsEOF( ) )
		{
			nMonthStart = rs.m_MonthStart;
			nMonthStop = rs.m_MonthStop;
		}

		rs.Close( );
		db.Close( );


		if( (nMonthStop == 0) && (nMonthStart == 0) )
		{
			return t.GetYear( );
		}
		else if( (nMonthStop - nMonthStart) == 0 )
		{
			return t.GetYear( );
		}
		else if( (nMonthStop - nMonthStart) >  0 )
		{
			return t.GetYear( );
		}
		else if( (nMonthStop - nMonthStart) <  0 )
		{
			if( ( t.GetMonth( ) >= nMonthStart )  )
				return (t.GetYear( ));

			if(	( t.GetMonth( ) <= nMonthStop  )  ) 
				return (t.GetYear( ) -1);
		}
	}
	catch (CDBException* pEx)
	{
		pEx->m_strError;

		pEx->Delete();
	}

	return t.GetYear( );
}


double CCalculate::GetSeconds(int iHours, int iMinutes, double dSeconds)
{
	return 
	(
		( (double)iHours * 3600.0 ) +
		( (double)iMinutes * 60.0 ) +
		( dSeconds )
	);
}

double CCalculate::GetSeconds(double dMinSec)
{
	return 
	(
		( (double)((int)dMinSec) * 60 ) + 
		(         (dMinSec - (double)((int)dMinSec)) * 100.0 )
	);
}

double CCalculate::GetMinSec(double dSeconds)
{
	return 
	(
		(double)((int)( dSeconds / 60.0 )) + (GetSecondsPart(dSeconds) / 100.0)
	);
}

int CCalculate::GetHoursPart(double dSeconds)
{
	return
	(
		(int)(dSeconds / 3600.0)
	);
}

int CCalculate::GetMinutesPart(double dSeconds)
{
	return
	(
		(int)(  (double)( (int)(dSeconds) % 3600 ) / 60.0  )
	);
}

double CCalculate::GetSecondsPart(double dSeconds)
{
	// to preserve the 1000th seconds we use a multiplier
	//
	// ie (15min 26.793sec) -> 926.793sec
	//
	//    will return 26.793sec seconds part

	const double d = 1000.0;
	const int i = 1000;

	return
	(
		(double)( (int)(dSeconds * d) % (60 * i) ) / d
	);
}

int CCalculate::GetPercentile(int iPlace, int iParticipantCount)
{
	return
	(
		(int) ceil(   (  ((double)iPlace) / ((double)iParticipantCount)  ) * 100.0   )
	);
}



double CCalculate::GetEventRateLongDistance(double dEventLength, double dNetPerfSEC)
{
	const double d = 1000.0;
	const int i = 1000;

	// EventLength is in metres
	// need to convert to kilometres

	double dKMEventLength = dEventLength / 1000.0;

	return
	(
		// MIN
		(     (double)((int)(  (dNetPerfSEC / dKMEventLength) / 60.0  ))     ) +  

		// SEC
		(     (double)((int)(  (dNetPerfSEC / dKMEventLength) * d  ) % (60 * i)) / ( 100.0 * d )    )

	);
}

double CCalculate::GetEventRateJumpThrow(double dEventLength, double dNetPerfSEC)
{
	// this is a percentage of the EventLength
	return
	(
		(dNetPerfSEC / dEventLength) * 100.0
	);
}

double CCalculate::GetEventRateSprint(double dEventLength, double dGrossPerfSEC, double dGroupStartActual)
{
	// this is the time they would have run the event, if they had run the
	// full distance.
	return 
	(
		( dGrossPerfSEC / (dEventLength - dGroupStartActual) ) * dEventLength
	);
}

int CCalculate::GetPointDecrementValue(int iPoint, int iPointscale)
{
	return
	(
		(int)ceil( ((double)iPoint) / ((double)iPointscale) )
	);
}




double CCalculate::GetNetPerformance(int iTimed,
									 double dGroupStartActual,
									 int iGrossPerformanceHOUR,
									 int iGrossPerformanceMIN,
									 double dGrossPerformanceSEC)
{
	// Calculate NetPerformance

	if(iTimed == 1) // Long Distance 
	{
		double dGrossPerfSEC = CCalculate::GetSeconds(
			iGrossPerformanceHOUR,
			iGrossPerformanceMIN,
			dGrossPerformanceSEC
		);

		double dGroupStartSEC = CCalculate::GetSeconds(dGroupStartActual);

		double dNetPerfSEC = dGrossPerfSEC - dGroupStartSEC;

		return dNetPerfSEC;
	}
	else if(iTimed == 0) // Jump or Throw
	{
		double dGrossPerfSEC = dGrossPerformanceSEC;

		double dNetPerfSEC = dGrossPerfSEC - dGroupStartActual;

		return dNetPerfSEC;
	}
	else if(iTimed == 2) // Sprint
	{
		double dGrossPerfSEC = CCalculate::GetSeconds(
			iGrossPerformanceHOUR,
			iGrossPerformanceMIN,
			dGrossPerformanceSEC
		);

		double dNetPerfSEC = dGrossPerfSEC;

		return dNetPerfSEC;
	}
	else
	{
		return 0.0;
	}

	//iNetPerformanceHOUR = CCalculate::GetHoursPart(dNetPerfSEC);
	//iNetPerformanceMIN = CCalculate::GetMinutesPart(dNetPerfSEC);
	//dNetPerformanceSEC = CCalculate::GetSecondsPart(dNetPerfSEC);
}



