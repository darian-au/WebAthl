// ParticipantForSeriesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ParticipantForSeriesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParticipantForSeriesSet

IMPLEMENT_DYNAMIC(CParticipantForSeriesSet, CRecordsetEx)

CParticipantForSeriesSet::CParticipantForSeriesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CParticipantForSeriesSet)
	m_SeriesID = 0;
	m_PersonID = 0;
	m_GroupIDSupposedTo = 0;
	m_DivisionSupposedTo = 0;
	m_ConsistencyAgeGroup = 0;
	m_ConsistencyEventsCurrent = 0;
	m_ConsistencyEventsOlder = 0;
	m_ConsistencyEventsRate = 0.0f;
	m_EventsForSeason = 0;
	m_GrossPoints = 0;
	m_LowPoints = 0;
	m_NetPoints = 0;
	m_EligibilityForEvent = _T("");
	m_OrgID = 0;
	m_EventsForSeries = 0;
	m_ConsistencyAgeStandard = 0.0f;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CParticipantForSeriesSet::GetDefaultConnect()
{
	return _T("");
}

CString CParticipantForSeriesSet::GetDefaultSQL()
{
	return _T("[ParticipantForSeries]");
}

void CParticipantForSeriesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CParticipantForSeriesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ParticipantForSeries].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[GroupIDSupposedTo]"), m_GroupIDSupposedTo);
	RFX_Long(pFX, _T("[ParticipantForSeries].[DivisionSupposedTo]"), m_DivisionSupposedTo);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyAgeGroup]"), m_ConsistencyAgeGroup);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyEventsCurrent]"), m_ConsistencyEventsCurrent);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyEventsOlder]"), m_ConsistencyEventsOlder);
	RFX_Double(pFX, _T("[ParticipantForSeries].[ConsistencyEventsRate]"), m_ConsistencyEventsRate);
	RFX_Long(pFX, _T("[ParticipantForSeries].[EventsForSeason]"), m_EventsForSeason);
	RFX_Long(pFX, _T("[ParticipantForSeries].[GrossPoints]"), m_GrossPoints);
	RFX_Long(pFX, _T("[ParticipantForSeries].[LowPoints]"), m_LowPoints);
	RFX_Long(pFX, _T("[ParticipantForSeries].[NetPoints]"), m_NetPoints);
	RFX_Text(pFX, _T("[ParticipantForSeries].[EligibilityForEvent]"), m_EligibilityForEvent);
	RFX_Long(pFX, _T("[ParticipantForSeries].[OrgID]"), m_OrgID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[EventsForSeries]"), m_EventsForSeries);
	RFX_Double(pFX, _T("[ParticipantForSeries].[ConsistencyAgeStandard]"), m_ConsistencyAgeStandard);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CParticipantForSeriesSet diagnostics

#ifdef _DEBUG
void CParticipantForSeriesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CParticipantForSeriesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
