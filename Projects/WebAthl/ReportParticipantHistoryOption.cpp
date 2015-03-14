// CReportParticipantHistoryOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportParticipantHistoryOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportParticipantHistoryOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportParticipantHistoryOption::CReportParticipantHistoryOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportParticipantHistoryOption::~CReportParticipantHistoryOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportParticipantHistoryOption::GetName()
{
	return CReportParticipantHistoryOption::GetName(m_dwItemEnum);
}

DWORD CReportParticipantHistoryOption::GetDefaultSelect()
{
	return CReportParticipantHistoryOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportParticipantHistoryOption::GetLabel()
{
	return CReportParticipantHistoryOption::GetLabel(m_dwItemEnum);
}


CString CReportParticipantHistoryOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportParticipantHistoryOption::DisplaySeriesDescription :
			return "Series";
			break;
		case CReportParticipantHistoryOption::DisplayEventNo :
			return "Event Number";
			break;
		case CReportParticipantHistoryOption::DisplayDate :
			return "Event Date";
			break;
		case CReportParticipantHistoryOption::DisplayLocationDescription :
			return "Location";
			break;
		case CReportParticipantHistoryOption::DisplayEventDescription :
			return "Event";
			break;
		case CReportParticipantHistoryOption::DisplayDivisionActual :
			return "Division Actual";
			break;
		case CReportParticipantHistoryOption::DisplayDivisionSupposedTo :
			return "Division Supposed To";
			break;
		case CReportParticipantHistoryOption::DisplayAgeGroup :
			return "AgeGroup";
			break;
		case CReportParticipantHistoryOption::DisplayGroupIDActual :
			return "Group Actual";
			break;
		case CReportParticipantHistoryOption::DisplayGroupIDSupposedTo :
			return "Group Supposed To";
			break;
		case CReportParticipantHistoryOption::DisplayGroupStartActual :
			return "Group Start Actual";
			break;
		case CReportParticipantHistoryOption::DisplayGrossPerformance :
			return "Gross Performance";
			break;
		case CReportParticipantHistoryOption::DisplayNetPerformance :
			return "Net Performance";
			break;
		case CReportParticipantHistoryOption::DisplayPlace :
			return "Place";
			break;
		case CReportParticipantHistoryOption::DisplayOverallPlace :
			return "Overall Place";
			break;
		case CReportParticipantHistoryOption::DisplayPercentile :
			return "Percentile";
			break;
		case CReportParticipantHistoryOption::DisplayPoints :
			return "Points";
			break;
		case CReportParticipantHistoryOption::DisplayEligible :
			return "Eligible";
			break;
		case CReportParticipantHistoryOption::DisplayEventRate :
			return "Event Rate";
			break;
		case CReportParticipantHistoryOption::DisplayGroupRateActual :
			return "Group Rate";
			break;
		case CReportParticipantHistoryOption::DisplayChestNumber :
			return "Chest Number";
			break;
		case CReportParticipantHistoryOption::DisplayWorldStandard :
			return "Age Standard";
			break;
		case CReportParticipantHistoryOption::DisplayNewGroupID :
			return "New Group";
			break;
		case CReportParticipantHistoryOption::DisplayNewGroupMessage :
			return "Comment";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportParticipantHistoryOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportParticipantHistoryOption::DisplaySeriesDescription :
		case CReportParticipantHistoryOption::DisplayEventNo :
		case CReportParticipantHistoryOption::DisplayDate :
		case CReportParticipantHistoryOption::DisplayLocationDescription :
		case CReportParticipantHistoryOption::DisplayEventDescription :
		case CReportParticipantHistoryOption::DisplayAgeGroup :
		case CReportParticipantHistoryOption::DisplayNetPerformance :
		case CReportParticipantHistoryOption::DisplayPlace :
		case CReportParticipantHistoryOption::DisplayEventRate :
			return dwItem;
			break;

		case CReportParticipantHistoryOption::DisplayDivisionActual :
		case CReportParticipantHistoryOption::DisplayDivisionSupposedTo :
		case CReportParticipantHistoryOption::DisplayGroupIDActual :
		case CReportParticipantHistoryOption::DisplayGroupIDSupposedTo :
		case CReportParticipantHistoryOption::DisplayGroupStartActual :
		case CReportParticipantHistoryOption::DisplayGrossPerformance :
		case CReportParticipantHistoryOption::DisplayOverallPlace :
		case CReportParticipantHistoryOption::DisplayPercentile :
		case CReportParticipantHistoryOption::DisplayPoints :
		case CReportParticipantHistoryOption::DisplayEligible :
		case CReportParticipantHistoryOption::DisplayGroupRateActual :
		case CReportParticipantHistoryOption::DisplayChestNumber :
		case CReportParticipantHistoryOption::DisplayWorldStandard :
		case CReportParticipantHistoryOption::DisplayNewGroupID :
		case CReportParticipantHistoryOption::DisplayNewGroupMessage :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportParticipantHistoryOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportParticipantHistoryOption::DisplaySeriesDescription :
			return "Display";
			break;
		case CReportParticipantHistoryOption::DisplayEventNo :
		case CReportParticipantHistoryOption::DisplayDate :
		case CReportParticipantHistoryOption::DisplayLocationDescription :
		case CReportParticipantHistoryOption::DisplayEventDescription :
		case CReportParticipantHistoryOption::DisplayDivisionActual :
		case CReportParticipantHistoryOption::DisplayDivisionSupposedTo :
		case CReportParticipantHistoryOption::DisplayAgeGroup :
		case CReportParticipantHistoryOption::DisplayGroupIDActual :
		case CReportParticipantHistoryOption::DisplayGroupIDSupposedTo :
		case CReportParticipantHistoryOption::DisplayGroupStartActual :
		case CReportParticipantHistoryOption::DisplayGrossPerformance :
		case CReportParticipantHistoryOption::DisplayNetPerformance :
		case CReportParticipantHistoryOption::DisplayPlace :
		case CReportParticipantHistoryOption::DisplayOverallPlace :
		case CReportParticipantHistoryOption::DisplayPercentile :
		case CReportParticipantHistoryOption::DisplayPoints :
		case CReportParticipantHistoryOption::DisplayEligible :
		case CReportParticipantHistoryOption::DisplayEventRate :
		case CReportParticipantHistoryOption::DisplayGroupRateActual :
		case CReportParticipantHistoryOption::DisplayChestNumber :
		case CReportParticipantHistoryOption::DisplayWorldStandard :
		case CReportParticipantHistoryOption::DisplayNewGroupID :
		case CReportParticipantHistoryOption::DisplayNewGroupMessage :
			return "";
			break;
		default :
			return "";
			break;
	}

}
