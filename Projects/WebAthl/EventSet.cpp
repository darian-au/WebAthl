// EventSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "EventSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventSet

IMPLEMENT_DYNAMIC(CEventSet, CRecordsetEx)

CEventSet::CEventSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CEventSet)
	m_SeriesID = 0;
	m_EventNo = 0;
	m_EventID = 0;
	m_LocationID = 0;
	m_EventTypeID = 0;
	m_DateDAY = 0;
	m_DateMONTH = 0;
	m_DateYEAR = 0;
	m_PreEntryOpen = 0;
	m_DateAgeDAY = 0;
	m_DateAgeMONTH = 0;
	m_DateAgeYEAR = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("EventID");
	m_nIdentityColumn = &m_EventID;

	// For Non Licensed Version
	m_nCountMax = 10;
}


CString CEventSet::GetDefaultConnect()
{
	return _T("");
}

CString CEventSet::GetDefaultSQL()
{
	return _T("[Event]");
}

void CEventSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEventSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Event].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Event].[EventNo]"), m_EventNo);
	RFX_Long(pFX, _T("[Event].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Event].[LocationID]"), m_LocationID);
	RFX_Long(pFX, _T("[Event].[EventTypeID]"), m_EventTypeID);
	RFX_Long(pFX, _T("[Event].[DateDAY]"), m_DateDAY);
	RFX_Long(pFX, _T("[Event].[DateMONTH]"), m_DateMONTH);
	RFX_Long(pFX, _T("[Event].[DateYEAR]"), m_DateYEAR);
	RFX_Long(pFX, _T("[Event].[PreEntryOpen]"), m_PreEntryOpen);
	RFX_Long(pFX, _T("[Event].[DateAgeDAY]"), m_DateAgeDAY);
	RFX_Long(pFX, _T("[Event].[DateAgeMONTH]"), m_DateAgeMONTH);
	RFX_Long(pFX, _T("[Event].[DateAgeYEAR]"), m_DateAgeYEAR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEventSet diagnostics

#ifdef _DEBUG
void CEventSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CEventSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
