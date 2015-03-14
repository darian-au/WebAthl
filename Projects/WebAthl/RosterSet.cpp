// RosterSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RosterSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRosterSet

IMPLEMENT_DYNAMIC(CRosterSet, CRecordsetEx)

CRosterSet::CRosterSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRosterSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_TaskID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRosterSet::GetDefaultConnect()
{
	return _T("");
}

CString CRosterSet::GetDefaultSQL()
{
	return _T("[Roster]");
}

void CRosterSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRosterSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Roster].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Roster].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Roster].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[Roster].[TaskID]"), m_TaskID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRosterSet diagnostics

#ifdef _DEBUG
void CRosterSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRosterSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
