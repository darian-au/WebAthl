// ParticipantHistorySet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ParticipantHistorySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParticipantHistorySet

IMPLEMENT_DYNAMIC(CParticipantHistorySet, CRecordsetEx)

CParticipantHistorySet::CParticipantHistorySet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CParticipantHistorySet)
	m_SeriesID = 0;
	m_SeriesDescription = _T("");
//	m_Handicapped = FALSE;
//	m_AgeCategory = _T("");

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

	m_Event_SeriesID = 0;
	m_EventNo = 0;
	m_EventID = 0;
	m_Event_LocationID = 0;
	m_Event_EventTypeID = 0;
	m_DateDAY = 0;
	m_DateMONTH = 0;
	m_DateYEAR = 0;
	m_PreEntryOpen = 0;
	m_DateAgeDAY = 0;
	m_DateAgeMONTH = 0;
	m_DateAgeYEAR = 0;

	m_LocationID = 0;
	m_LocationDescription = _T("");

	m_EventTypeID = 0;
	m_EventDescription = _T("");
	m_Timed = 0;
	m_EventLength = 0.0f;

	m_Results_SeriesID = 0;
	m_Results_EventID = 0;
	m_Results_PersonID = 0;
	m_DivisionActual = 0;
	m_AgeGroup = 0;
	m_GroupIDActual = 0;
	m_GroupStartActual = 0.0f;
	m_NewGroupID = 0;
	m_NewGroupMessage = _T("");
	m_GrossPerformanceHOUR = 0;
	m_GrossPerformanceMIN = 0;
	m_GrossPerformanceSEC = 0.0f;
	m_NetPerformanceHOUR = 0;
	m_NetPerformanceMIN = 0;
	m_NetPerformanceSEC = 0.0f;
	m_Place = 0;
	m_OverallPlace = 0;
	m_Percentile = 0;
	m_Points = 0;
	m_Eligible = _T("");
	m_EventRate = 0.0f;
	m_GroupRateActual = 0.0f;
	m_ChestNumber = _T("");
	m_WorldStandard = 0.0f;
	m_GroupIDSupposedTo = 0;
	m_DivisionSupposedTo = 0;
	m_OrgID = 0;

	m_nFields = 67;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CParticipantHistorySet::GetDefaultConnect()
{
	return _T("");
}

CString CParticipantHistorySet::GetDefaultSQL()
{
	return _T("[Series],[Person],[Event],[Location],[EventType],[Results]");
}

void CParticipantHistorySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CParticipantHistorySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_AgeCategory);

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

	RFX_Long(pFX, _T("[Event].[SeriesID]"), m_Event_SeriesID);
	RFX_Long(pFX, _T("[Event].[EventNo]"), m_EventNo);
	RFX_Long(pFX, _T("[Event].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Event].[LocationID]"), m_Event_LocationID);
	RFX_Long(pFX, _T("[Event].[EventTypeID]"), m_Event_EventTypeID);
	RFX_Long(pFX, _T("[Event].[DateDAY]"), m_DateDAY);
	RFX_Long(pFX, _T("[Event].[DateMONTH]"), m_DateMONTH);
	RFX_Long(pFX, _T("[Event].[DateYEAR]"), m_DateYEAR);
	RFX_Long(pFX, _T("[Event].[PreEntryOpen]"), m_PreEntryOpen);
	RFX_Long(pFX, _T("[Event].[DateAgeDAY]"), m_DateAgeDAY);
	RFX_Long(pFX, _T("[Event].[DateAgeMONTH]"), m_DateAgeMONTH);
	RFX_Long(pFX, _T("[Event].[DateAgeYEAR]"), m_DateAgeYEAR);

	RFX_Long(pFX, _T("[Location].[LocationID]"), m_LocationID);
	RFX_Text(pFX, _T("[Location].[LocationDescription]"), m_LocationDescription);

	RFX_Long(pFX, _T("[EventType].[EventTypeID]"), m_EventTypeID);
	RFX_Text(pFX, _T("[EventType].[EventDescription]"), m_EventDescription);
	RFX_Long(pFX, _T("[EventType].[Timed]"), m_Timed);
	RFX_Double(pFX, _T("[EventType].[EventLength]"), m_EventLength);

	RFX_Long(pFX, _T("[Results].[SeriesID]"), m_Results_SeriesID);
	RFX_Long(pFX, _T("[Results].[EventID]"), m_Results_EventID);
	RFX_Long(pFX, _T("[Results].[PersonID]"), m_Results_PersonID);
	RFX_Long(pFX, _T("[Results].[DivisionActual]"), m_DivisionActual);
	RFX_Long(pFX, _T("[Results].[AgeGroup]"), m_AgeGroup);
	RFX_Long(pFX, _T("[Results].[GroupIDActual]"), m_GroupIDActual);
	RFX_Double(pFX, _T("[Results].[GroupStartActual]"), m_GroupStartActual);
	RFX_Long(pFX, _T("[Results].[NewGroupID]"), m_NewGroupID);
	RFX_Text(pFX, _T("[Results].[NewGroupMessage]"), m_NewGroupMessage);
	RFX_Long(pFX, _T("[Results].[GrossPerformanceHOUR]"), m_GrossPerformanceHOUR);
	RFX_Long(pFX, _T("[Results].[GrossPerformanceMIN]"), m_GrossPerformanceMIN);
	RFX_Double(pFX, _T("[Results].[GrossPerformanceSEC]"), m_GrossPerformanceSEC);
	RFX_Long(pFX, _T("[Results].[NetPerformanceHOUR]"), m_NetPerformanceHOUR);
	RFX_Long(pFX, _T("[Results].[NetPerformanceMIN]"), m_NetPerformanceMIN);
	RFX_Double(pFX, _T("[Results].[NetPerformanceSEC]"), m_NetPerformanceSEC);
	RFX_Long(pFX, _T("[Results].[Place]"), m_Place);
	RFX_Long(pFX, _T("[Results].[OverallPlace]"), m_OverallPlace);
	RFX_Long(pFX, _T("[Results].[Percentile]"), m_Percentile);
	RFX_Long(pFX, _T("[Results].[Points]"), m_Points);
	RFX_Text(pFX, _T("[Results].[Eligible]"), m_Eligible);
	RFX_Double(pFX, _T("[Results].[EventRate]"), m_EventRate);
	RFX_Double(pFX, _T("[Results].[GroupRateActual]"), m_GroupRateActual);
	RFX_Text(pFX, _T("[Results].[ChestNumber]"), m_ChestNumber);
	RFX_Double(pFX, _T("[Results].[WorldStandard]"), m_WorldStandard);
	RFX_Long(pFX, _T("[Results].[GroupIDSupposedTo]"), m_GroupIDSupposedTo);
	RFX_Long(pFX, _T("[Results].[DivisionSupposedTo]"), m_DivisionSupposedTo);
	RFX_Long(pFX, _T("[Results].[OrgID]"), m_OrgID);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CParticipantHistorySet diagnostics

#ifdef _DEBUG
void CParticipantHistorySet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CParticipantHistorySet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
