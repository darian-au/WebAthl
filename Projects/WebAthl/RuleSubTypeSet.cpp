// RuleSubTypeSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RuleSubTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleSubTypeSet

IMPLEMENT_DYNAMIC(CRuleSubTypeSet, CRecordsetEx)

CRuleSubTypeSet::CRuleSubTypeSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRuleSubTypeSet)
	m_RuleTypeID = 0;
	m_RuleSubTypeID = 0;
	m_RuleSubTypeDescription = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("RuleSubTypeID");
	m_nIdentityColumn = &m_RuleSubTypeID;
}


CString CRuleSubTypeSet::GetDefaultConnect()
{
	return _T("");
}

CString CRuleSubTypeSet::GetDefaultSQL()
{
	return _T("[RuleSubType]");
}

void CRuleSubTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRuleSubTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[RuleSubType].[RuleTypeID]"), m_RuleTypeID);
	RFX_Long(pFX, _T("[RuleSubType].[RuleSubTypeID]"), m_RuleSubTypeID);
	RFX_Text(pFX, _T("[RuleSubType].[RuleSubTypeDescription]"), m_RuleSubTypeDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRuleSubTypeSet diagnostics

#ifdef _DEBUG
void CRuleSubTypeSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRuleSubTypeSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
