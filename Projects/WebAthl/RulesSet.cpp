// RulesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RulesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRulesSet

IMPLEMENT_DYNAMIC(CRulesSet, CRecordsetEx)

CRulesSet::CRulesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRulesSet)
	m_SeriesID = 0;
	m_RuleTypeID = 0;
	m_RuleSubTypeID = 0;
	m_RuleID = 0;
	m_Law = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("RuleID");
	m_nIdentityColumn = &m_RuleID;
}


CString CRulesSet::GetDefaultConnect()
{
	return _T("");
}

CString CRulesSet::GetDefaultSQL()
{
	return _T("[Rules]");
}

void CRulesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRulesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Rules].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Rules].[RuleTypeID]"), m_RuleTypeID);
	RFX_Long(pFX, _T("[Rules].[RuleSubTypeID]"), m_RuleSubTypeID);
	RFX_Long(pFX, _T("[Rules].[RuleID]"), m_RuleID);
	RFX_Long(pFX, _T("[Rules].[Law]"), m_Law);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRulesSet diagnostics

#ifdef _DEBUG
void CRulesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRulesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
