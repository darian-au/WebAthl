// PersonParticipantForSeriesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "PersonParticipantForSeriesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonParticipantForSeriesSet

IMPLEMENT_DYNAMIC(CPersonParticipantForSeriesSet, CRecordsetEx)

CPersonParticipantForSeriesSet::CPersonParticipantForSeriesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CPersonParticipantForSeriesSet)
	m_SeriesID = 0;
	m_PFS_PersonID = 0;
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

	m_PersonID = 0;
	m_LastName = _T("");
	m_FirstName = _T("");
	m_MiddleName = _T("");
	m_dobDAY = 0;
	m_dobMONTH = 0;
	m_dobYEAR = 0;
	m_Sex = _T("");
	m_Address1 = _T("");
	m_Address2 = _T("");
	m_Town = _T("");
	m_State = _T("");
	m_Country = _T("");
	m_PostCode = _T("");
	m_PhoneHm = _T("");
	m_PhoneWk = _T("");
	m_Fax = _T("");
	m_Mobile = _T("");
	m_email = _T("");
	m_ContactPersonID = 0;
	m_nFields = 35;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CPersonParticipantForSeriesSet::GetDefaultConnect()
{
	return _T("");
}

CString CPersonParticipantForSeriesSet::GetDefaultSQL()
{
	return _T("[ParticipantForSeries],[Person]");
}

void CPersonParticipantForSeriesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonParticipantForSeriesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ParticipantForSeries].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[PersonID]"), m_PFS_PersonID);
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

	RFX_Long(pFX, _T("[Person].[PersonID]"), m_PersonID);
	RFX_Text(pFX, _T("[Person].[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[Person].[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Person].[MiddleName]"), m_MiddleName);
	RFX_Long(pFX, _T("[Person].[dobDAY]"), m_dobDAY);
	RFX_Long(pFX, _T("[Person].[dobMONTH]"), m_dobMONTH);
	RFX_Long(pFX, _T("[Person].[dobYEAR]"), m_dobYEAR);
	RFX_Text(pFX, _T("[Person].[Sex]"), m_Sex);
	RFX_Text(pFX, _T("[Person].[Address1]"), m_Address1);
	RFX_Text(pFX, _T("[Person].[Address2]"), m_Address2);
	RFX_Text(pFX, _T("[Person].[Town]"), m_Town);
	RFX_Text(pFX, _T("[Person].[State]"), m_State);
	RFX_Text(pFX, _T("[Person].[Country]"), m_Country);
	RFX_Text(pFX, _T("[Person].[PostCode]"), m_PostCode);
	RFX_Text(pFX, _T("[Person].[PhoneHm]"), m_PhoneHm);
	RFX_Text(pFX, _T("[Person].[PhoneWk]"), m_PhoneWk);
	RFX_Text(pFX, _T("[Person].[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[Person].[Mobile]"), m_Mobile);
	RFX_Text(pFX, _T("[Person].[email]"), m_email);
	RFX_Long(pFX, _T("[Person].[ContactPersonID]"), m_ContactPersonID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPersonParticipantForSeriesSet diagnostics

#ifdef _DEBUG
void CPersonParticipantForSeriesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CPersonParticipantForSeriesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
