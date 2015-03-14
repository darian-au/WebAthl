// EventTypeSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "EventTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventTypeSet

IMPLEMENT_DYNAMIC(CEventTypeSet, CRecordsetEx)

CEventTypeSet::CEventTypeSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CEventTypeSet)
	m_EventTypeID = 0;
	m_EventDescription = _T("");
	m_Timed = 0;
	m_EventLength = 0.0f;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("EventTypeID");
	m_nIdentityColumn = &m_EventTypeID;
}


CString CEventTypeSet::GetDefaultConnect()
{
	return _T("");
}

CString CEventTypeSet::GetDefaultSQL()
{
	return _T("[EventType]");
}

void CEventTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEventTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[EventType].[EventTypeID]"), m_EventTypeID);
	RFX_Text(pFX, _T("[EventType].[EventDescription]"), m_EventDescription);
	RFX_Long(pFX, _T("[EventType].[Timed]"), m_Timed);
	RFX_Double(pFX, _T("[EventType].[EventLength]"), m_EventLength);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEventTypeSet diagnostics

#ifdef _DEBUG
void CEventTypeSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CEventTypeSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
