// CRuleSubType.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "RuleSubType.h"

#include "RuleType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RuleSubType

/////////////////////////////////////////////////////////////////////////////
// Constructor

CRuleSubType::CRuleSubType( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CRuleSubType::~CRuleSubType( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CRuleSubType::GetName()
{
	return CRuleSubType::GetName(m_dwItemEnum);
}

DWORD CRuleSubType::GetTypeCode()
{
	return CRuleSubType::GetTypeCode(m_dwItemEnum);
}

CString CRuleSubType::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CRuleSubType::EligibilityEventsCompleted :
			return "Events Completed";
			break;
		case CRuleSubType::PointscoreMaximumPoints :
			return "Maximum Points";
			break;
		case CRuleSubType::PointscoreMinimumPoints :
			return "Minimum Points";
			break;
		case CRuleSubType::PointscorePointscale :
			return "Pointscale";
			break;
		case CRuleSubType::PointscoreEventsToCountForPoints :
			return "Events to Count for Points";
			break;
		case CRuleSubType::ConsistencyEventsToQualify :
			return "Events to Qualify";
			break;
		case CRuleSubType::ConsistencyEventsBeforeAgegroupChange :
			return "Events before Agegroup Change";
			break;
		case CRuleSubType::RegroupEventsAbovePercentile :
			return "Events Above Percentile";
			break;
		case CRuleSubType::RegroupEventsBelowPercentile :
			return "Events Below Percentile";
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfDivision :
			return "Eligible Regardless of Division";
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfGroup :
			return "Eligible Regardless of Group";
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfFinancial :
			return "Eligible Regardless of Financial";
			break;
		case CRuleSubType::ProcessingSetOverallPlaceByDivision :
			return "Set Overall-Place By Division";
			break;
		default :
			return "";
			break;
	}

}


DWORD CRuleSubType::GetTypeCode(DWORD dwItem)
{

	switch( dwItem )
	{
		case CRuleSubType::EligibilityEventsCompleted :
			return CRuleType::Eligibility;
			break;
		case CRuleSubType::PointscoreMaximumPoints :
			return CRuleType::Pointscore;
			break;
		case CRuleSubType::PointscoreMinimumPoints :
			return CRuleType::Pointscore;
			break;
		case CRuleSubType::PointscorePointscale :
			return CRuleType::Pointscore;
			break;
		case CRuleSubType::PointscoreEventsToCountForPoints :
			return CRuleType::Pointscore;
			break;
		case CRuleSubType::ConsistencyEventsToQualify :
			return CRuleType::Consistency;
			break;
		case CRuleSubType::ConsistencyEventsBeforeAgegroupChange :
			return CRuleType::Consistency;
			break;
		case CRuleSubType::RegroupEventsAbovePercentile :
			return CRuleType::Regroup;
			break;
		case CRuleSubType::RegroupEventsBelowPercentile :
			return CRuleType::Regroup;
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfDivision :
			return CRuleType::Processing;
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfGroup :
			return CRuleType::Processing;
			break;
		case CRuleSubType::ProcessingEligibleRegardlessOfFinancial :
			return CRuleType::Processing;
			break;
		case CRuleSubType::ProcessingSetOverallPlaceByDivision :
			return CRuleType::Processing;
			break;
		default :
			return CRuleType::none;
			break;
	}

}
