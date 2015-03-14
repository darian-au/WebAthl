// CReportResultsBySeriesOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportResultsBySeriesOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportResultsBySeriesOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportResultsBySeriesOption::CReportResultsBySeriesOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportResultsBySeriesOption::~CReportResultsBySeriesOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportResultsBySeriesOption::GetName()
{
	return CReportResultsBySeriesOption::GetName(m_dwItemEnum);
}

DWORD CReportResultsBySeriesOption::GetDefaultSelect()
{
	return CReportResultsBySeriesOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportResultsBySeriesOption::GetLabel()
{
	return CReportResultsBySeriesOption::GetLabel(m_dwItemEnum);
}


CString CReportResultsBySeriesOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsBySeriesOption::DisplaySeriesDesc :
			return "Series Description";
			break;
		case CReportResultsBySeriesOption::DisplayEventNo :
			return "Event Number";
			break;
		case CReportResultsBySeriesOption::DisplayLocationDesc :
			return "Location Description";
			break;
		case CReportResultsBySeriesOption::DisplayEventDesc :
			return "Event Description";
			break;
		case CReportResultsBySeriesOption::DisplayEventDate :
			return "Event Date";
			break;
		case CReportResultsBySeriesOption::DisplayDivisionAct :
			return "Division Actual";
			break;
		case CReportResultsBySeriesOption::DisplayDivision :
			return "Division Supposed To";
			break;
		case CReportResultsBySeriesOption::DisplayOverallPlace :
			return "Overall Place";
			break;
		case CReportResultsBySeriesOption::DisplayPlace :
			return "Place";
			break;
		case CReportResultsBySeriesOption::DisplayPersonID :
			return "Person ID";
			break;
		case CReportResultsBySeriesOption::DisplayFirstName :
			return "First Name";
			break;
		case CReportResultsBySeriesOption::DisplayLastName :
			return "Last Name";
			break;
		case CReportResultsBySeriesOption::DisplayAgeGroup :
			return "AgeGroup";
			break;
		case CReportResultsBySeriesOption::DisplayGroup :
			return "Group Supposed To";
			break;
		case CReportResultsBySeriesOption::DisplayGroupAct :
			return "Group Actual";
			break;
		case CReportResultsBySeriesOption::DisplayGroupStart :
			return "Group Start Actual";
			break;
		case CReportResultsBySeriesOption::DisplayGrossPerformance :
			return "Gross Performance";
			break;
		case CReportResultsBySeriesOption::DisplayNetPerformance :
			return "Net Performance";
			break;
		case CReportResultsBySeriesOption::DisplayEventRate :
			return "Event Rate";
			break;
		case CReportResultsBySeriesOption::DisplayGroupRate :
			return "Group Rate";
			break;
		case CReportResultsBySeriesOption::DisplayWAVA :
			return "Age Standard";
			break;
		case CReportResultsBySeriesOption::DisplayPoints :
			return "Points";
			break;
		case CReportResultsBySeriesOption::DisplayPercentile :
			return "Percentile";
			break;
		case CReportResultsBySeriesOption::DisplayEligible :
			return "Eligibility";
			break;
		case CReportResultsBySeriesOption::DisplayNewGroupMsg :
			return "Comment";
			break;
		case CReportResultsBySeriesOption::DisplayNewGroup :
			return "New Group";
			break;
		case CReportResultsBySeriesOption::DisplayOrganisation :
			return "Organisation";
			break;
		case CReportResultsBySeriesOption::DisplayChestNumber :
			return "Chest Number";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportResultsBySeriesOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsBySeriesOption::DisplaySeriesDesc :
		case CReportResultsBySeriesOption::DisplayEventNo :
		case CReportResultsBySeriesOption::DisplayLocationDesc :
		case CReportResultsBySeriesOption::DisplayEventDesc :
		case CReportResultsBySeriesOption::DisplayEventDate :
		case CReportResultsBySeriesOption::DisplayPlace :
		case CReportResultsBySeriesOption::DisplayPersonID :
		case CReportResultsBySeriesOption::DisplayFirstName :
		case CReportResultsBySeriesOption::DisplayLastName :
		case CReportResultsBySeriesOption::DisplayNetPerformance :
			return dwItem;
			break;

		case CReportResultsBySeriesOption::DisplayDivisionAct :
		case CReportResultsBySeriesOption::DisplayDivision :
		case CReportResultsBySeriesOption::DisplayOverallPlace :
		case CReportResultsBySeriesOption::DisplayAgeGroup :
		case CReportResultsBySeriesOption::DisplayGroup :
		case CReportResultsBySeriesOption::DisplayGroupAct :
		case CReportResultsBySeriesOption::DisplayGroupStart :
		case CReportResultsBySeriesOption::DisplayGrossPerformance :
		case CReportResultsBySeriesOption::DisplayEventRate :
		case CReportResultsBySeriesOption::DisplayGroupRate :
		case CReportResultsBySeriesOption::DisplayWAVA :
		case CReportResultsBySeriesOption::DisplayPoints :
		case CReportResultsBySeriesOption::DisplayPercentile :
		case CReportResultsBySeriesOption::DisplayEligible :
		case CReportResultsBySeriesOption::DisplayNewGroupMsg :
		case CReportResultsBySeriesOption::DisplayNewGroup :
		case CReportResultsBySeriesOption::DisplayOrganisation :
		case CReportResultsBySeriesOption::DisplayChestNumber :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportResultsBySeriesOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportResultsBySeriesOption::DisplaySeriesDesc :
			return "Display";
			break;
		case CReportResultsBySeriesOption::DisplayEventNo :
		case CReportResultsBySeriesOption::DisplayLocationDesc :
		case CReportResultsBySeriesOption::DisplayEventDesc :
		case CReportResultsBySeriesOption::DisplayEventDate :
		case CReportResultsBySeriesOption::DisplayDivisionAct :
		case CReportResultsBySeriesOption::DisplayDivision :
		case CReportResultsBySeriesOption::DisplayOverallPlace :
		case CReportResultsBySeriesOption::DisplayPlace :
		case CReportResultsBySeriesOption::DisplayPersonID :
		case CReportResultsBySeriesOption::DisplayFirstName :
		case CReportResultsBySeriesOption::DisplayLastName :
		case CReportResultsBySeriesOption::DisplayAgeGroup :
		case CReportResultsBySeriesOption::DisplayGroup :
		case CReportResultsBySeriesOption::DisplayGroupAct :
		case CReportResultsBySeriesOption::DisplayGroupStart :
		case CReportResultsBySeriesOption::DisplayGrossPerformance :
		case CReportResultsBySeriesOption::DisplayNetPerformance :
		case CReportResultsBySeriesOption::DisplayEventRate :
		case CReportResultsBySeriesOption::DisplayGroupRate :
		case CReportResultsBySeriesOption::DisplayWAVA :
		case CReportResultsBySeriesOption::DisplayPoints :
		case CReportResultsBySeriesOption::DisplayPercentile :
		case CReportResultsBySeriesOption::DisplayEligible :
		case CReportResultsBySeriesOption::DisplayNewGroupMsg :
		case CReportResultsBySeriesOption::DisplayNewGroup :
		case CReportResultsBySeriesOption::DisplayOrganisation :
		case CReportResultsBySeriesOption::DisplayChestNumber :
			return "";
			break;
		default :
			return "";
			break;
	}

}
