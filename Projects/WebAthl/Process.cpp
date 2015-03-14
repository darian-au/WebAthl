// CProcess.cpp : implementation file
//

#include "stdafx.h"

#include "BitMaskEnum.h"
#include "ProcessGroup.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Process

/////////////////////////////////////////////////////////////////////////////
// Constructor

CProcess::CProcess( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CProcess::~CProcess( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CProcess::GetShortName()
{
	return CProcess::GetShortName(m_dwItemEnum);
}

CString CProcess::GetName()
{
	return CProcess::GetName(m_dwItemEnum);
}

DWORD CProcess::GetGroup()
{
	return CProcess::GetGroup(m_dwItemEnum);
}

bool CProcess::IsMember(DWORD dwGroup)
{
	return CBitMaskEnum::IsMember(CProcess::GetGroup(m_dwItemEnum), dwGroup);
}


CString CProcess::GetShortName(DWORD dwItem)
{

	switch( dwItem )
	{
		// Insert Pre-Event Entries
		case CProcess::PadPreResults :
			return "PadPreResults";
			break;
		case CProcess::ClosePreEntry :
			return "ClosePreEntry";
			break;

		// Post-Event Processing
		case CProcess::PostEventProcessAll :
			return "PostEventProcessAll";
			break;
		case CProcess::ClearNewGroup :
			return "ClearNewGroup";
			break;
		case CProcess::PadPostResults :
			return "PadPostResults";
			break;
		case CProcess::SetDivisionEligibility :
			return "SetDivisionEligibility";
			break;
		case CProcess::SetGroupsEligibility :
			return "SetGroupsEligibility";
			break;
		case CProcess::SetFinancialEligibility :
			return "SetFinancialEligibility";
			break;
		case CProcess::SetOverAllPlace :
			return "SetOverAllPlace";
			break;

//		case CProcess::SetMiscResults :
//			return "SetMiscResults";
//			break;

		case CProcess::SetNetPerformance :
			return "SetNetPerformance";
			break;
		case CProcess::SetPercentile :
			return "SetPercentile";
			break;
		case CProcess::SetPoints :
			return "SetPoints";
			break;
		case CProcess::SetEventRate :
			return "SetEventRate";
			break;

		case CProcess::SetWorldStandards :
			return "SetWorldStandards";
			break;
		case CProcess::ReGroup :
			return "ReGroup";
			break;

		// Pre-Event Processing (and some Post-Event)
		case CProcess::PreEventProcessAll :
			return "PreEventProcessAll";
			break;
		case CProcess::RebuildParticipantForSeries :
			return "RebuildParticipantForSeries";
			break;
		case CProcess::SetPointScore :
			return "SetPointScore";
			break;
		case CProcess::SetConsistencyEventsRate :
			return "SetConsistencyEventsRate";
			break;
		case CProcess::SetConsistencyAgeStandard :
			return "SetConsistencyAgeStandard";
			break;
		case CProcess::SetConsistencyAgeGroup :
			return "SetConsistencyAgeGroup";
			break;
		case CProcess::SetEventsForSeason :
			return "SetEventsForSeason";
			break;
		case CProcess::SetEventsForSeries :
			return "SetEventsForSeries";
			break;
		case CProcess::ReSetEligibility :
			return "ReSetEligibility";
			break;
		case CProcess::SetEligibilityXMore :
			return "SetEligibilityXMore";
			break;
		case CProcess::SetSeriesFinancialEligibility :
			return "SetSeriesFinancialEligibility";
			break;

		// Lock Out
		case CProcess::LockOut :
			return "LockOut";
			break;

		// Club Records
		case CProcess::RebuildClubRecords :
			return "RebuildClubRecords";
			break;

		default :
			return "";
			break;
	}

}





CString CProcess::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		// Insert Pre-Event Entries
		case CProcess::PadPreResults :
			return "Insert Pre-Event Entries";
			break;
		case CProcess::ClosePreEntry :
			return "Close Pre-Event Entry From Public";
			break;

		// Post-Event Processing
		case CProcess::PostEventProcessAll :
			return "Post-Event Processing";
			break;
		case CProcess::ClearNewGroup :
			return "Clear NewGroup from Event Results";
			break;
		case CProcess::PadPostResults :
			return "Update with PostEvent Results";
			break;
		case CProcess::SetDivisionEligibility :
			return "Set Eligibility for Division";
			break;
		case CProcess::SetGroupsEligibility :
			return "Set Eligibility for Groups";
			break;
		case CProcess::SetFinancialEligibility :
			return "Set Eligibility for Current Financial";
			break;
		case CProcess::SetOverAllPlace :
			return "Calculate Over All Place";
			break;

//		case CProcess::SetMiscResults :
//			return "Calculate Net-Performance; Percentile; Points; Event-Rate";
//			break;

		case CProcess::SetNetPerformance :
			return "Calculate Net-Performance";
			break;
		case CProcess::SetPercentile :
			return "Calculate Percentile";
			break;
		case CProcess::SetPoints :
			return "Calculate Points";
			break;
		case CProcess::SetEventRate :
			return "Calculate Event-Rate";
			break;

		case CProcess::SetWorldStandards :
			return "Calculate World-Standard";
			break;
		case CProcess::ReGroup :
			return "ReGroup";
			break;

		// Pre-Event Processing (and some Post-Event)
		case CProcess::PreEventProcessAll :
			return "Pre-Event Processing";
			break;
		case CProcess::RebuildParticipantForSeries :
			return "Rebuild Participants for the Series";
			break;
		case CProcess::SetPointScore :
			return "Update Point-Scores";
			break;
		case CProcess::SetConsistencyEventsRate :
			return "Set Consistency Events Rate";
			break;
		case CProcess::SetConsistencyAgeStandard :
			return "Set Consistency Age-Standard";
			break;
		case CProcess::SetConsistencyAgeGroup :
			return "Set Consistency Age-Groups";
			break;
		case CProcess::SetEventsForSeason :
			return "Set Events For Season";
			break;
		case CProcess::SetEventsForSeries :
			return "Set Events For Series";
			break;
		case CProcess::ReSetEligibility :
			return "Reset Eligibility for the Series";
			break;
		case CProcess::SetEligibilityXMore :
			return "Update Events Completed/Needed Eligibility for the Series";
			break;
		case CProcess::SetSeriesFinancialEligibility :
			return "Update Financial Eligibility for the Series";
			break;

		// Lock Out
		case CProcess::LockOut :
			return "Lock Out Post-Event Processing";
			break;

		// Club Records
		case CProcess::RebuildClubRecords :
			return "Rebuild Club Records for the Series";
			break;

		default :
			return "";
			break;
	}

}


DWORD CProcess::GetGroup(DWORD dwItem)
{

	switch( dwItem )
	{
		// Insert Pre-Event Entries
		case CProcess::PadPreResults :
			return CProcessGroup::PreResults;
			break;
		case CProcess::ClosePreEntry :
			return CProcessGroup::PreResults;
			break;

		// Post-Event Processing
		case CProcess::PostEventProcessAll :
			return CProcessGroup::PostEvent;
			break;
		case CProcess::ClearNewGroup :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::PadPostResults :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetDivisionEligibility :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetGroupsEligibility :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetFinancialEligibility :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetOverAllPlace :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;

//		case CProcess::SetMiscResults :
//			return CProcessGroup::PostEvent | CProcessGroup::Admin;
//			break;

		case CProcess::SetNetPerformance :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetPercentile :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetPoints :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetEventRate :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;

		case CProcess::SetWorldStandards :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;
		case CProcess::ReGroup :
			return CProcessGroup::PostEvent | CProcessGroup::Admin;
			break;

		// Pre-Event Processing (and some Post-Event)
		case CProcess::PreEventProcessAll :
			return CProcessGroup::PreEvent;
			break;
		case CProcess::RebuildParticipantForSeries :
			return CProcessGroup::PreEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetPointScore :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::SetConsistencyEventsRate :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::SetConsistencyAgeStandard :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::SetConsistencyAgeGroup :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::SetEventsForSeason :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::SetEventsForSeries :
			return CProcessGroup::PreEvent | CProcessGroup::Admin | CProcessGroup::PostEvent;
			break;
		case CProcess::ReSetEligibility :
			return CProcessGroup::PreEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetEligibilityXMore :
			return CProcessGroup::PreEvent | CProcessGroup::Admin;
			break;
		case CProcess::SetSeriesFinancialEligibility :
			return CProcessGroup::PreEvent | CProcessGroup::Admin;
			break;

		// Lock Out
		case CProcess::LockOut :
			return CProcessGroup::LockOut;
			break;

		// Club Records
		case CProcess::RebuildClubRecords :
			return CProcessGroup::ClubRecords;
			break;

		default :
			return CProcessGroup::none;
			break;
	}

}


