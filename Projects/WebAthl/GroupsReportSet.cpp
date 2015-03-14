// GroupsReportSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "GroupsReportSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupsReportSet

IMPLEMENT_DYNAMIC(CGroupsReportSet, CRecordsetEx)

CGroupsReportSet::CGroupsReportSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CGroupsReportSet)
	m_PFS_SeriesID = 0;
	m_PFS_PersonID = 0;
	m_PFS_GroupIDSupposedTo = 0;
	m_PFS_DivisionSupposedTo = 0;
	m_PFS_ConsistencyAgeGroup = 0;
	m_PFS_ConsistencyEventsCurrent = 0;
	m_PFS_ConsistencyEventsOlder = 0;
	m_PFS_ConsistencyEventsRate = 0.0f;
	m_PFS_EventsForSeason = 0;
	m_PFS_GrossPoints = 0;
	m_PFS_LowPoints = 0;
	m_PFS_NetPoints = 0;
	m_PFS_EligibilityForEvent = _T("");
	m_PFS_OrgID = 0;
	m_PFS_EventsForSeries = 0;
	m_PFS_ConsistencyAgeStandard = 0.0f;

	m_Person_PersonID = 0;
	m_Person_LastName = _T("");
	m_Person_FirstName = _T("");
	m_Person_MiddleName = _T("");
	m_Person_dobDAY = 0;
	m_Person_dobMONTH = 0;
	m_Person_dobYEAR = 0;
	m_Person_Sex = _T("");
	m_Person_Address1 = _T("");
	m_Person_Address2 = _T("");
	m_Person_Town = _T("");
	m_Person_State = _T("");
	m_Person_Country = _T("");
	m_Person_PostCode = _T("");
	m_Person_PhoneHm = _T("");
	m_Person_PhoneWk = _T("");
	m_Person_Fax = _T("");
	m_Person_Mobile = _T("");
	m_Person_email = _T("");
	m_Person_ContactPersonID = 0;

	m_Groups_SeriesID = 0;
	m_Groups_EventTypeID = 0;
	m_Groups_GroupID = 0;
	m_Groups_GroupRate = 0.0f;
	m_Groups_GroupStart = 0.0f;

	m_Series_SeriesID = 0;
	m_Series_SeriesDescription = _T("");
//	m_Series_Handicapped = FALSE;
//	m_Series_AgeCategory = _T("");

	m_Event_SeriesID = 0;
	m_Event_EventNo = 0;
	m_Event_EventID = 0;
	m_Event_LocationID = 0;
	m_Event_EventTypeID = 0;
	m_Event_DateDAY = 0;
	m_Event_DateMONTH = 0;
	m_Event_DateYEAR = 0;
	m_Event_PreEntryOpen = 0;
	m_Event_DateAgeDAY = 0;
	m_Event_DateAgeMONTH = 0;
	m_Event_DateAgeYEAR = 0;

	m_EventType_EventTypeID = 0;
	m_EventType_EventDescription = _T("");
	m_EventType_Timed = 0;
	m_EventType_EventLength = 0.0f;

	m_Location_LocationID = 0;
	m_Location_LocationDescription = _T("");

	m_nFields = 61;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CGroupsReportSet::GetDefaultConnect()
{
	return _T("");
}

CString CGroupsReportSet::GetDefaultSQL()
{
	return _T("[ParticipantForSeries],[Person],[Groups],[Series],[Event],[EventType],[Location]");
}

void CGroupsReportSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGroupsReportSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ParticipantForSeries].[SeriesID]"), m_PFS_SeriesID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[PersonID]"), m_PFS_PersonID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[GroupIDSupposedTo]"), m_PFS_GroupIDSupposedTo);
	RFX_Long(pFX, _T("[ParticipantForSeries].[DivisionSupposedTo]"), m_PFS_DivisionSupposedTo);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyAgeGroup]"), m_PFS_ConsistencyAgeGroup);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyEventsCurrent]"), m_PFS_ConsistencyEventsCurrent);
	RFX_Long(pFX, _T("[ParticipantForSeries].[ConsistencyEventsOlder]"), m_PFS_ConsistencyEventsOlder);
	RFX_Double(pFX, _T("[ParticipantForSeries].[ConsistencyEventsRate]"), m_PFS_ConsistencyEventsRate);
	RFX_Long(pFX, _T("[ParticipantForSeries].[EventsForSeason]"), m_PFS_EventsForSeason);
	RFX_Long(pFX, _T("[ParticipantForSeries].[GrossPoints]"), m_PFS_GrossPoints);
	RFX_Long(pFX, _T("[ParticipantForSeries].[LowPoints]"), m_PFS_LowPoints);
	RFX_Long(pFX, _T("[ParticipantForSeries].[NetPoints]"), m_PFS_NetPoints);
	RFX_Text(pFX, _T("[ParticipantForSeries].[EligibilityForEvent]"), m_PFS_EligibilityForEvent);
	RFX_Long(pFX, _T("[ParticipantForSeries].[OrgID]"), m_PFS_OrgID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[EventsForSeries]"), m_PFS_EventsForSeries);
	RFX_Double(pFX, _T("[ParticipantForSeries].[ConsistencyAgeStandard]"), m_PFS_ConsistencyAgeStandard);

	RFX_Long(pFX, _T("[Person].[PersonID]"), m_Person_PersonID);
	RFX_Text(pFX, _T("[Person].[LastName]"), m_Person_LastName);
	RFX_Text(pFX, _T("[Person].[FirstName]"), m_Person_FirstName);
	RFX_Text(pFX, _T("[Person].[MiddleName]"), m_Person_MiddleName);
	RFX_Long(pFX, _T("[Person].[dobDAY]"), m_Person_dobDAY);
	RFX_Long(pFX, _T("[Person].[dobMONTH]"), m_Person_dobMONTH);
	RFX_Long(pFX, _T("[Person].[dobYEAR]"), m_Person_dobYEAR);
	RFX_Text(pFX, _T("[Person].[Sex]"), m_Person_Sex);
	RFX_Text(pFX, _T("[Person].[Address1]"), m_Person_Address1);
	RFX_Text(pFX, _T("[Person].[Address2]"), m_Person_Address2);
	RFX_Text(pFX, _T("[Person].[Town]"), m_Person_Town);
	RFX_Text(pFX, _T("[Person].[State]"), m_Person_State);
	RFX_Text(pFX, _T("[Person].[Country]"), m_Person_Country);
	RFX_Text(pFX, _T("[Person].[PostCode]"), m_Person_PostCode);
	RFX_Text(pFX, _T("[Person].[PhoneHm]"), m_Person_PhoneHm);
	RFX_Text(pFX, _T("[Person].[PhoneWk]"), m_Person_PhoneWk);
	RFX_Text(pFX, _T("[Person].[Fax]"), m_Person_Fax);
	RFX_Text(pFX, _T("[Person].[Mobile]"), m_Person_Mobile);
	RFX_Text(pFX, _T("[Person].[email]"), m_Person_email);
	RFX_Long(pFX, _T("[Person].[ContactPersonID]"), m_Person_ContactPersonID);

	RFX_Long(pFX, _T("[Groups].[SeriesID]"), m_Groups_SeriesID);
	RFX_Long(pFX, _T("[Groups].[EventTypeID]"), m_Groups_EventTypeID);
	RFX_Long(pFX, _T("[Groups].[GroupID]"), m_Groups_GroupID);
	RFX_Double(pFX, _T("[Groups].[GroupRate]"), m_Groups_GroupRate);
	RFX_Double(pFX, _T("[Groups].[GroupStart]"), m_Groups_GroupStart);

	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_Series_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_Series_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Series_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_Series_AgeCategory);

	RFX_Long(pFX, _T("[Event].[SeriesID]"), m_Event_SeriesID);
	RFX_Long(pFX, _T("[Event].[EventNo]"), m_Event_EventNo);
	RFX_Long(pFX, _T("[Event].[EventID]"), m_Event_EventID);
	RFX_Long(pFX, _T("[Event].[LocationID]"), m_Event_LocationID);
	RFX_Long(pFX, _T("[Event].[EventTypeID]"), m_Event_EventTypeID);
	RFX_Long(pFX, _T("[Event].[DateDAY]"), m_Event_DateDAY);
	RFX_Long(pFX, _T("[Event].[DateMONTH]"), m_Event_DateMONTH);
	RFX_Long(pFX, _T("[Event].[DateYEAR]"), m_Event_DateYEAR);
	RFX_Long(pFX, _T("[Event].[PreEntryOpen]"), m_Event_PreEntryOpen);
	RFX_Long(pFX, _T("[Event].[DateAgeDAY]"), m_Event_DateAgeDAY);
	RFX_Long(pFX, _T("[Event].[DateAgeMONTH]"), m_Event_DateAgeMONTH);
	RFX_Long(pFX, _T("[Event].[DateAgeYEAR]"), m_Event_DateAgeYEAR);

	RFX_Long(pFX, _T("[EventType].[EventTypeID]"), m_EventType_EventTypeID);
	RFX_Text(pFX, _T("[EventType].[EventDescription]"), m_EventType_EventDescription);
	RFX_Long(pFX, _T("[EventType].[Timed]"), m_EventType_Timed);
	RFX_Double(pFX, _T("[EventType].[EventLength]"), m_EventType_EventLength);

	RFX_Long(pFX, _T("[Location].[LocationID]"), m_Location_LocationID);
	RFX_Text(pFX, _T("[Location].[LocationDescription]"), m_Location_LocationDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGroupsReportSet diagnostics

#ifdef _DEBUG
void CGroupsReportSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CGroupsReportSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
