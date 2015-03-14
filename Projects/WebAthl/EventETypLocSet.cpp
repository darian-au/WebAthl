// EventETypLocSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "EventETypLocSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventETypLocSet

IMPLEMENT_DYNAMIC(CEventETypLocSet, CRecordsetEx)

CEventETypLocSet::CEventETypLocSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CEventETypLocSet)
	m_SeriesID = 0;
	m_SeriesDescription = _T("");
//	m_Handicapped = FALSE;
//	m_AgeCategory = _T("");

	m_Event_SeriesID = 0;
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

	m_EventType_EventTypeID = 0;
	m_EventDescription = _T("");
	m_Timed = 0;
	m_EventLength = 0.0f;

	m_Location_LocationID = 0;
	m_LocationDescription = _T("");
	
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEventETypLocSet::GetDefaultConnect()
{
	return _T("");
}

CString CEventETypLocSet::GetDefaultSQL()
{
	return _T("[Series],[Event],[EventType],[Location]");
}

void CEventETypLocSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEventETypLocSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_AgeCategory);

	RFX_Long(pFX, _T("[Event].[SeriesID]"), m_Event_SeriesID);
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

	RFX_Long(pFX, _T("[EventType].[EventTypeID]"), m_EventType_EventTypeID);
	RFX_Text(pFX, _T("[EventType].[EventDescription]"), m_EventDescription);
	RFX_Long(pFX, _T("[EventType].[Timed]"), m_Timed);
	RFX_Double(pFX, _T("[EventType].[EventLength]"), m_EventLength);

	RFX_Long(pFX, _T("[Location].[LocationID]"), m_Location_LocationID);
	RFX_Text(pFX, _T("[Location].[LocationDescription]"), m_LocationDescription);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEventETypLocSet diagnostics

#ifdef _DEBUG
void CEventETypLocSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CEventETypLocSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
