// RuleTypeSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RuleTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleTypeSet

IMPLEMENT_DYNAMIC(CRuleTypeSet, CRecordsetEx)

CRuleTypeSet::CRuleTypeSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRuleTypeSet)
	m_RuleTypeID = 0;
	m_RuleTypeDescription = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("RuleTypeID");
	m_nIdentityColumn = &m_RuleTypeID;
}


CString CRuleTypeSet::GetDefaultConnect()
{
	return _T("");
}

CString CRuleTypeSet::GetDefaultSQL()
{
	return _T("[RuleType]");
}

void CRuleTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRuleTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[RuleType].[RuleTypeID]"), m_RuleTypeID);
	RFX_Text(pFX, _T("[RuleType].[RuleTypeDescription]"), m_RuleTypeDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRuleTypeSet diagnostics

#ifdef _DEBUG
void CRuleTypeSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRuleTypeSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
