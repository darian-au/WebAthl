// CReportGroupsListOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportGroupsListOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportGroupsListOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportGroupsListOption::CReportGroupsListOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportGroupsListOption::~CReportGroupsListOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportGroupsListOption::GetName()
{
	return CReportGroupsListOption::GetName(m_dwItemEnum);
}

DWORD CReportGroupsListOption::GetDefaultSelect()
{
	return CReportGroupsListOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportGroupsListOption::GetLabel()
{
	return CReportGroupsListOption::GetLabel(m_dwItemEnum);
}


CString CReportGroupsListOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportGroupsListOption::DisplayPersonID :
			return "PersonID";
			break;
		case CReportGroupsListOption::DisplayLastName :
			return "LastName";
			break;
		case CReportGroupsListOption::DisplayFirstName :
			return "FirstName";
			break;
		case CReportGroupsListOption::DisplaySexAgeGroup :
			return "AgeGroup";
			break;
		case CReportGroupsListOption::DisplayDivisionSupposedTo :
			return "Division";
			break;
		case CReportGroupsListOption::DisplayGroupIDSupposedTo :
			return "Group";
			break;
		case CReportGroupsListOption::DisplayEventsForSeason :
			return "Events For Season";
			break;
		case CReportGroupsListOption::DisplayEventsForSeries :
			return "Events For Series";
			break;
		case CReportGroupsListOption::DisplayNetPoints :
			return "NetPoints";
			break;
		case CReportGroupsListOption::DisplayEligibilityForEvent :
			return "Eligibility";
			break;
		case CReportGroupsListOption::DisplayGroupStart :
			return "GroupStart";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportGroupsListOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportGroupsListOption::DisplayPersonID :
		case CReportGroupsListOption::DisplayLastName :
		case CReportGroupsListOption::DisplayFirstName :
		case CReportGroupsListOption::DisplaySexAgeGroup :
		case CReportGroupsListOption::DisplayDivisionSupposedTo :
		case CReportGroupsListOption::DisplayGroupIDSupposedTo :
		case CReportGroupsListOption::DisplayEventsForSeason :
		case CReportGroupsListOption::DisplayEventsForSeries :
		case CReportGroupsListOption::DisplayNetPoints :
		case CReportGroupsListOption::DisplayEligibilityForEvent :
		case CReportGroupsListOption::DisplayGroupStart :
			return dwItem;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportGroupsListOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportGroupsListOption::DisplayPersonID :
			return "Display";
			break;
		case CReportGroupsListOption::DisplayLastName :
		case CReportGroupsListOption::DisplayFirstName :
		case CReportGroupsListOption::DisplaySexAgeGroup :
		case CReportGroupsListOption::DisplayDivisionSupposedTo :
		case CReportGroupsListOption::DisplayGroupIDSupposedTo :
		case CReportGroupsListOption::DisplayEventsForSeason :
		case CReportGroupsListOption::DisplayEventsForSeries :
		case CReportGroupsListOption::DisplayNetPoints :
		case CReportGroupsListOption::DisplayEligibilityForEvent :
		case CReportGroupsListOption::DisplayGroupStart :
			return "";
			break;
		default :
			return "";
			break;
	}

}
