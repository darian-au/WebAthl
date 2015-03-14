// CReportResultsOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportResultsOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportResultsOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportResultsOption::CReportResultsOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportResultsOption::~CReportResultsOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportResultsOption::GetName()
{
	return CReportResultsOption::GetName(m_dwItemEnum);
}

DWORD CReportResultsOption::GetDefaultSelect()
{
	return CReportResultsOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportResultsOption::GetLabel()
{
	return CReportResultsOption::GetLabel(m_dwItemEnum);
}


CString CReportResultsOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsOption::DisplayDivisionAct :
			return "Division Actual";
			break;
		case CReportResultsOption::DisplayDivision :
			return "Division Supposed To";
			break;
		case CReportResultsOption::DisplayOverallPlace :
			return "Overall Place";
			break;
		case CReportResultsOption::DisplayPlace :
			return "Place";
			break;
		case CReportResultsOption::DisplayPersonID :
			return "Person ID";
			break;
		case CReportResultsOption::DisplayFirstName :
			return "First Name";
			break;
		case CReportResultsOption::DisplayLastName :
			return "Last Name";
			break;
		case CReportResultsOption::DisplayAgeGroup :
			return "AgeGroup";
			break;
		case CReportResultsOption::DisplayGroup :
			return "Group Supposed To";
			break;
		case CReportResultsOption::DisplayGroupAct :
			return "Group Actual";
			break;
		case CReportResultsOption::DisplayGroupStart :
			return "Group Start Actual";
			break;
		case CReportResultsOption::DisplayGrossPerformance :
			return "Gross Performance";
			break;
		case CReportResultsOption::DisplayNetPerformance :
			return "Net Performance";
			break;
		case CReportResultsOption::DisplayEventRate :
			return "Event Rate";
			break;
		case CReportResultsOption::DisplayGroupRate :
			return "Group Rate";
			break;
		case CReportResultsOption::DisplayWAVA :
			return "Age Standard";
			break;
		case CReportResultsOption::DisplayPoints :
			return "Points";
			break;
		case CReportResultsOption::DisplayPercentile :
			return "Percentile";
			break;
		case CReportResultsOption::DisplayEligible :
			return "Eligibility";
			break;
		case CReportResultsOption::DisplayNewGroupMsg :
			return "Comment";
			break;
		case CReportResultsOption::DisplayNewGroup :
			return "New Group";
			break;
		case CReportResultsOption::DisplayOrganisation :
			return "Organisation";
			break;
		case CReportResultsOption::DisplayChestNumber :
			return "Chest Number";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportResultsOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsOption::DisplayPlace :
		case CReportResultsOption::DisplayPersonID :
		case CReportResultsOption::DisplayFirstName :
		case CReportResultsOption::DisplayLastName :
		case CReportResultsOption::DisplayNetPerformance :
			return dwItem;
			break;

		case CReportResultsOption::DisplayDivisionAct :
		case CReportResultsOption::DisplayDivision :
		case CReportResultsOption::DisplayOverallPlace :
		case CReportResultsOption::DisplayAgeGroup :
		case CReportResultsOption::DisplayGroup :
		case CReportResultsOption::DisplayGroupAct :
		case CReportResultsOption::DisplayGroupStart :
		case CReportResultsOption::DisplayGrossPerformance :
		case CReportResultsOption::DisplayEventRate :
		case CReportResultsOption::DisplayGroupRate :
		case CReportResultsOption::DisplayWAVA :
		case CReportResultsOption::DisplayPoints :
		case CReportResultsOption::DisplayPercentile :
		case CReportResultsOption::DisplayEligible :
		case CReportResultsOption::DisplayNewGroupMsg :
		case CReportResultsOption::DisplayNewGroup :
		case CReportResultsOption::DisplayOrganisation :
		case CReportResultsOption::DisplayChestNumber :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportResultsOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsOption::DisplayDivisionAct :
			return "Display";
			break;
		case CReportResultsOption::DisplayDivision :
		case CReportResultsOption::DisplayOverallPlace :
		case CReportResultsOption::DisplayPlace :
		case CReportResultsOption::DisplayPersonID :
		case CReportResultsOption::DisplayFirstName :
		case CReportResultsOption::DisplayLastName :
		case CReportResultsOption::DisplayAgeGroup :
		case CReportResultsOption::DisplayGroup :
		case CReportResultsOption::DisplayGroupAct :
		case CReportResultsOption::DisplayGroupStart :
		case CReportResultsOption::DisplayGrossPerformance :
		case CReportResultsOption::DisplayNetPerformance :
		case CReportResultsOption::DisplayEventRate :
		case CReportResultsOption::DisplayGroupRate :
		case CReportResultsOption::DisplayWAVA :
		case CReportResultsOption::DisplayPoints :
		case CReportResultsOption::DisplayPercentile :
		case CReportResultsOption::DisplayEligible :
		case CReportResultsOption::DisplayNewGroupMsg :
		case CReportResultsOption::DisplayNewGroup :
		case CReportResultsOption::DisplayOrganisation :
		case CReportResultsOption::DisplayChestNumber :
			return "";
			break;
		default :
			return "";
			break;
	}

}
