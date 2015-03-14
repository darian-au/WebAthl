// CRuleType.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "RuleType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RuleType

/////////////////////////////////////////////////////////////////////////////
// Constructor

CRuleType::CRuleType( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CRuleType::~CRuleType( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CRuleType::GetName()
{
	return CRuleType::GetName(m_dwItemEnum);
}

int CRuleType::GetMax()
{
	return CRuleType::GetMax(m_dwItemEnum);
}

CString CRuleType::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CRuleType::Eligibility :
			return "Eligibility";
			break;
		case CRuleType::Pointscore :
			return "Pointscore";
			break;
		case CRuleType::Consistency :
			return "Consistency";
			break;
		case CRuleType::Regroup :
			return "Regroup";
			break;
		case CRuleType::Processing :
			return "Processing";
			break;
		default :
			return "";
			break;
	}

}

int CRuleType::GetMax(DWORD dwItem)
{

	switch( dwItem )
	{
		case CRuleType::Eligibility :
			return MAX_RULE_ELIGIBILITY;
			break;
		case CRuleType::Pointscore :
			return MAX_RULE_POINTSCORE;
			break;
		case CRuleType::Consistency :
			return MAX_RULE_CONSISTENCY;
			break;
		case CRuleType::Regroup :
			return MAX_RULE_REGROUP;
			break;
		case CRuleType::Processing :
			return MAX_RULE_PROCESS;
			break;
		default :
			return 0;
			break;
	}

}
