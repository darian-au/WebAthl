// CReportAwardsOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportAwardsOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportAwardsOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportAwardsOption::CReportAwardsOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportAwardsOption::~CReportAwardsOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportAwardsOption::GetName()
{
	return CReportAwardsOption::GetName(m_dwItemEnum);
}

DWORD CReportAwardsOption::GetDefaultSelect()
{
	return CReportAwardsOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportAwardsOption::GetLabel()
{
	return CReportAwardsOption::GetLabel(m_dwItemEnum);
}


CString CReportAwardsOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportAwardsOption::DisplayPersonID :
			return "PersonID";
			break;
		case CReportAwardsOption::DisplayLastName :
			return "LastName";
			break;
		case CReportAwardsOption::DisplayFirstName :
			return "FirstName";
			break;
		case CReportAwardsOption::DisplaySexAgeGroup :
			return "AgeGroup";
			break;
		case CReportAwardsOption::DisplayDivisionSupposedTo :
			return "Division";
			break;
		case CReportAwardsOption::DisplayGroupIDSupposedTo :
			return "Group";
			break;
		case CReportAwardsOption::DisplayEventsForSeason :
			return "Events For Season";
			break;
		case CReportAwardsOption::DisplayEventsForSeries :
			return "Events For Series";
			break;
		case CReportAwardsOption::DisplayConsistencyAgeGroup :
			return "Consistency AgeGroup";
			break;
		case CReportAwardsOption::DisplayConsistencyEventsCurrent :
			return "Consistency Events Current";
			break;
		case CReportAwardsOption::DisplayConsistencyEventsOlder :
			return "Consistency Events Older";
			break;
		case CReportAwardsOption::DisplayConsistencyEventsRate :
			return "Consistency Events Rate";
			break;
		case CReportAwardsOption::DisplayConsistencyAgeStandard :
			return "Consistency Age Standard";
			break;
		case CReportAwardsOption::DisplayGrossPoints :
			return "GrossPoints";
			break;
		case CReportAwardsOption::DisplayNetPoints :
			return "NetPoints";
			break;
		case CReportAwardsOption::DisplayLowPoints :
			return "LowPoints";
			break;
		case CReportAwardsOption::DisplayEligibilityForEvent :
			return "Eligibility";
			break;
		case CReportAwardsOption::DisplayOrgName :
			return "Organisation";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportAwardsOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportAwardsOption::DisplayPersonID :
		case CReportAwardsOption::DisplayLastName :
		case CReportAwardsOption::DisplayFirstName :
		case CReportAwardsOption::DisplaySexAgeGroup :
		case CReportAwardsOption::DisplayDivisionSupposedTo :
		case CReportAwardsOption::DisplayGroupIDSupposedTo :
		case CReportAwardsOption::DisplayEventsForSeason :
		case CReportAwardsOption::DisplayEventsForSeries :
		case CReportAwardsOption::DisplayConsistencyAgeGroup :
		case CReportAwardsOption::DisplayConsistencyEventsCurrent :
		case CReportAwardsOption::DisplayConsistencyEventsOlder :
		case CReportAwardsOption::DisplayConsistencyEventsRate :
		case CReportAwardsOption::DisplayConsistencyAgeStandard :
		case CReportAwardsOption::DisplayGrossPoints :
		case CReportAwardsOption::DisplayNetPoints :
		case CReportAwardsOption::DisplayLowPoints :
		case CReportAwardsOption::DisplayEligibilityForEvent :
		case CReportAwardsOption::DisplayOrgName :
			return dwItem;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportAwardsOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportAwardsOption::DisplayPersonID :
			return "Display";
			break;
		case CReportAwardsOption::DisplayLastName :
		case CReportAwardsOption::DisplayFirstName :
		case CReportAwardsOption::DisplaySexAgeGroup :
		case CReportAwardsOption::DisplayDivisionSupposedTo :
		case CReportAwardsOption::DisplayGroupIDSupposedTo :
		case CReportAwardsOption::DisplayEventsForSeason :
		case CReportAwardsOption::DisplayEventsForSeries :
		case CReportAwardsOption::DisplayConsistencyAgeGroup :
		case CReportAwardsOption::DisplayConsistencyEventsCurrent :
		case CReportAwardsOption::DisplayConsistencyEventsOlder :
		case CReportAwardsOption::DisplayConsistencyEventsRate :
		case CReportAwardsOption::DisplayConsistencyAgeStandard :
		case CReportAwardsOption::DisplayGrossPoints :
		case CReportAwardsOption::DisplayNetPoints :
		case CReportAwardsOption::DisplayLowPoints :
		case CReportAwardsOption::DisplayEligibilityForEvent :
		case CReportAwardsOption::DisplayOrgName :
			return "";
			break;
		default :
			return "";
			break;
	}

}
