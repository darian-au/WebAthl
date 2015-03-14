// EventTallySet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "EventTallySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventTallySet

IMPLEMENT_DYNAMIC(CEventTallySet, CRecordsetEx)

CEventTallySet::CEventTallySet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CEventTallySet)
	m_PersonID = 0;
	m_FirstName = _T("");
	m_LastName = _T("");
	m_EventTally = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEventTallySet::GetDefaultConnect()
{
	return _T("");
}

CString CEventTallySet::GetDefaultSQL()
{
	return _T("");
}

void CEventTallySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEventTallySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PersonID]"), m_PersonID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Long(pFX, _T("[EventTally]"), m_EventTally);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEventTallySet diagnostics

#ifdef _DEBUG
void CEventTallySet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CEventTallySet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
