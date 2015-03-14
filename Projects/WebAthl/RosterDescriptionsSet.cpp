// RosterDescriptionsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RosterDescriptionsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRosterDescriptionsSet

IMPLEMENT_DYNAMIC(CRosterDescriptionsSet, CRecordsetEx)

CRosterDescriptionsSet::CRosterDescriptionsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRosterDescriptionsSet)
	m_TaskID = 0;
	m_TaskDescription = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("TaskID");
	m_nIdentityColumn = &m_TaskID;
}


CString CRosterDescriptionsSet::GetDefaultConnect()
{
	return _T("");
}

CString CRosterDescriptionsSet::GetDefaultSQL()
{
	return _T("[RosterDescriptions]");
}

void CRosterDescriptionsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRosterDescriptionsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[RosterDescriptions].[TaskID]"), m_TaskID);
	RFX_Text(pFX, _T("[RosterDescriptions].[TaskDescription]"), m_TaskDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRosterDescriptionsSet diagnostics

#ifdef _DEBUG
void CRosterDescriptionsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRosterDescriptionsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
