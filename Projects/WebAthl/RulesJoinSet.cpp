// RulesJoinSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RulesJoinSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulesJoinSet

IMPLEMENT_DYNAMIC(CRulesJoinSet, CRecordsetEx)

CRulesJoinSet::CRulesJoinSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRulesJoinSet)
	m_SeriesID = 0;
	m_RuleTypeID = 0;
	m_RuleSubTypeID = 0;
	m_RuleID = 0;
	m_Law = 0;

	m_RuleType_RuleTypeID = 0;
	m_RuleTypeDescription = _T("");

	m_RuleSubType_RuleTypeID = 0;
	m_RuleSubType_RuleSubTypeID = 0;
	m_RuleSubTypeDescription = _T("");

	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRulesJoinSet::GetDefaultConnect()
{
	return _T("");
}

CString CRulesJoinSet::GetDefaultSQL()
{
	return _T("[Rules],[RuleType],[RuleSubType]");
}

void CRulesJoinSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRulesJoinSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Rules].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Rules].[RuleTypeID]"), m_RuleTypeID);
	RFX_Long(pFX, _T("[Rules].[RuleSubTypeID]"), m_RuleSubTypeID);
	RFX_Long(pFX, _T("[Rules].[RuleID]"), m_RuleID);
	RFX_Long(pFX, _T("[Rules].[Law]"), m_Law);

	RFX_Long(pFX, _T("[RuleType].[RuleTypeID]"), m_RuleType_RuleTypeID);
	RFX_Text(pFX, _T("[RuleType].[RuleTypeDescription]"), m_RuleTypeDescription);

	RFX_Long(pFX, _T("[RuleSubType].[RuleTypeID]"), m_RuleSubType_RuleTypeID);
	RFX_Long(pFX, _T("[RuleSubType].[RuleSubTypeID]"), m_RuleSubType_RuleSubTypeID);
	RFX_Text(pFX, _T("[RuleSubType].[RuleSubTypeDescription]"), m_RuleSubTypeDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRulesJoinSet diagnostics

#ifdef _DEBUG
void CRulesJoinSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRulesJoinSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
