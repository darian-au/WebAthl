// ClubRecordsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ClubRecordsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClubRecordsSet

IMPLEMENT_DYNAMIC(CClubRecordsSet, CRecordsetEx)

CClubRecordsSet::CClubRecordsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CClubRecordsSet)
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

	m_Series_SeriesID = 0;
	m_SeriesDescription = _T("");
//	m_Handicapped = FALSE;
//	m_Series_AgeCategory = _T("");

	m_Location_LocationID = 0;
	m_LocationDescription = _T("");

	m_EventType_EventTypeID = 0;
	m_EventDescription = _T("");
	m_Timed = 0;
	m_EventLength = 0.0f;

	m_Person_PersonID = 0;
	m_LastName = _T("");
	m_FirstName = _T("");
	m_MiddleName = _T("");
	m_dobDAY = 0;
	m_dobMONTH = 0;
	m_dobYEAR = 0;
	m_Person_Sex = _T("");
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
	m_Event_EventID = 0;
	m_Event_LocationID = 0;
	m_Event_EventTypeID = 0;
	m_DateDAY = 0;
	m_DateMONTH = 0;
	m_DateYEAR = 0;
	m_PreEntryOpen = 0;
	m_DateAgeDAY = 0;
	m_DateAgeMONTH = 0;
	m_DateAgeYEAR = 0;

	m_nFields = 51;

	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CClubRecordsSet::GetDefaultConnect()
{
	return _T("");
}

CString CClubRecordsSet::GetDefaultSQL()
{
	return _T("[EventRecord],[Series],[Location],[EventType],[Person],[Event]");
}

void CClubRecordsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClubRecordsSet)
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

	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_Series_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_Series_AgeCategory);

	RFX_Long(pFX, _T("[Location].[LocationID]"), m_Location_LocationID);
	RFX_Text(pFX, _T("[Location].[LocationDescription]"), m_LocationDescription);

	RFX_Long(pFX, _T("[EventType].[EventTypeID]"), m_EventType_EventTypeID);
	RFX_Text(pFX, _T("[EventType].[EventDescription]"), m_EventDescription);
	RFX_Long(pFX, _T("[EventType].[Timed]"), m_Timed);
	RFX_Double(pFX, _T("[EventType].[EventLength]"), m_EventLength);

	RFX_Long(pFX, _T("[Person].[PersonID]"), m_Person_PersonID);
	RFX_Text(pFX, _T("[Person].[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[Person].[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Person].[MiddleName]"), m_MiddleName);
	RFX_Long(pFX, _T("[Person].[dobDAY]"), m_dobDAY);
	RFX_Long(pFX, _T("[Person].[dobMONTH]"), m_dobMONTH);
	RFX_Long(pFX, _T("[Person].[dobYEAR]"), m_dobYEAR);
	RFX_Text(pFX, _T("[Person].[Sex]"), m_Person_Sex);
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
	RFX_Long(pFX, _T("[Event].[EventID]"), m_Event_EventID);
	RFX_Long(pFX, _T("[Event].[LocationID]"), m_Event_LocationID);
	RFX_Long(pFX, _T("[Event].[EventTypeID]"), m_Event_EventTypeID);
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
// CClubRecordsSet diagnostics

#ifdef _DEBUG
void CClubRecordsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CClubRecordsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
