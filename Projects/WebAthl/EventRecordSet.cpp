// EventRecordSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "EventRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventRecordSet

IMPLEMENT_DYNAMIC(CEventRecordSet, CRecordsetEx)

CEventRecordSet::CEventRecordSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CEventRecordSet)
	m_SeriesID = 0;
	m_LocationID = 0;
	m_EventID = 0;
	m_EventTypeID = 0;
	m_Sex = _T("");
	m_AgeGroup = 0;
	m_AgeCategory = _T("");
	m_PersonID = 0;
	m_ClubPerformanceHOUR = 0;
	m_ClubPerformanceMIN = 0;
	m_ClubPerformanceSEC = 0.0f;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEventRecordSet::GetDefaultConnect()
{
	return _T("");
}

CString CEventRecordSet::GetDefaultSQL()
{
	return _T("[EventRecord]");
}

void CEventRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEventRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[EventRecord].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[EventRecord].[LocationID]"), m_LocationID);
	RFX_Long(pFX, _T("[EventRecord].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[EventRecord].[EventTypeID]"), m_EventTypeID);
	RFX_Text(pFX, _T("[EventRecord].[Sex]"), m_Sex);
	RFX_Long(pFX, _T("[EventRecord].[AgeGroup]"), m_AgeGroup);
	RFX_Text(pFX, _T("[EventRecord].[AgeCategory]"), m_AgeCategory);
	RFX_Long(pFX, _T("[EventRecord].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[EventRecord].[ClubPerformanceHOUR]"), m_ClubPerformanceHOUR);
	RFX_Long(pFX, _T("[EventRecord].[ClubPerformanceMIN]"), m_ClubPerformanceMIN);
	RFX_Double(pFX, _T("[EventRecord].[ClubPerformanceSEC]"), m_ClubPerformanceSEC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEventRecordSet diagnostics

#ifdef _DEBUG
void CEventRecordSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CEventRecordSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
