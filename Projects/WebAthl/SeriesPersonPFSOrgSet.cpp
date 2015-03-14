// SeriesPersonPFSOrgSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SeriesPersonPFSOrgSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesPersonPFSSet

IMPLEMENT_DYNAMIC(CSeriesPersonPFSOrgSet, CRecordsetEx)

CSeriesPersonPFSOrgSet::CSeriesPersonPFSOrgSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSeriesPersonPFSOrgSet)
	m_Series_SeriesID = 0;
	m_SeriesDescription = _T("");
//	m_Handicapped = FALSE;
//	m_AgeCategory = _T("");

	m_Person_PersonID = 0;
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

	m_ParticipantForSeries_SeriesID = 0;
	m_ParticipantForSeries_PersonID = 0;
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
	m_ParticipantForSeries_OrgID = 0;
	m_EventsForSeries = 0;
	m_ConsistencyAgeStandard = 0.0f;

	m_Org_OrgID = 0;
	m_OrgName = _T("");
	m_Org_Address1 = _T("");
	m_Org_Address2 = _T("");
	m_Org_Town = _T("");
	m_Org_State = _T("");
	m_Org_Country = _T("");
	m_Org_PostCode = _T("");
	m_Org_Phone = _T("");
	m_Org_Fax = _T("");
	m_Org_Mobile = _T("");
	m_Org_email = _T("");
	m_URL = _T("");
	m_RegistrarPersonID = 0;
	m_AdministratorPersonID = 0;


	m_nFields = 53;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSeriesPersonPFSOrgSet::GetDefaultConnect()
{
	return _T("");
}

CString CSeriesPersonPFSOrgSet::GetDefaultSQL()
{
	return _T("[Series],[Person],[ParticipantForSeries],[Organisation]");
}

void CSeriesPersonPFSOrgSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSeriesPersonPFSOrgSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_Series_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_AgeCategory);

	RFX_Long(pFX, _T("[Person].[PersonID]"), m_Person_PersonID);
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

	RFX_Long(pFX, _T("[ParticipantForSeries].[SeriesID]"), m_ParticipantForSeries_SeriesID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[PersonID]"), m_ParticipantForSeries_PersonID);
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
	RFX_Long(pFX, _T("[ParticipantForSeries].[OrgID]"), m_ParticipantForSeries_OrgID);
	RFX_Long(pFX, _T("[ParticipantForSeries].[EventsForSeries]"), m_EventsForSeries);
	RFX_Double(pFX, _T("[ParticipantForSeries].[ConsistencyAgeStandard]"), m_ConsistencyAgeStandard);

	RFX_Long(pFX, _T("[Organisation].[OrgID]"), m_Org_OrgID);
	RFX_Text(pFX, _T("[Organisation].[OrgName]"), m_OrgName);
	RFX_Text(pFX, _T("[Organisation].[Address1]"), m_Org_Address1);
	RFX_Text(pFX, _T("[Organisation].[Address2]"), m_Org_Address2);
	RFX_Text(pFX, _T("[Organisation].[Town]"), m_Org_Town);
	RFX_Text(pFX, _T("[Organisation].[State]"), m_Org_State);
	RFX_Text(pFX, _T("[Organisation].[Country]"), m_Org_Country);
	RFX_Text(pFX, _T("[Organisation].[PostCode]"), m_Org_PostCode);
	RFX_Text(pFX, _T("[Organisation].[Phone]"), m_Org_Phone);
	RFX_Text(pFX, _T("[Organisation].[Fax]"), m_Org_Fax);
	RFX_Text(pFX, _T("[Organisation].[Mobile]"), m_Org_Mobile);
	RFX_Text(pFX, _T("[Organisation].[email]"), m_Org_email);
	RFX_Text(pFX, _T("[Organisation].[URL]"), m_URL);
	RFX_Long(pFX, _T("[Organisation].[RegistrarPersonID]"), m_RegistrarPersonID);
	RFX_Long(pFX, _T("[Organisation].[AdministratorPersonID]"), m_AdministratorPersonID);
	
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSeriesPersonPFSOrgSet diagnostics

#ifdef _DEBUG
void CSeriesPersonPFSOrgSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSeriesPersonPFSOrgSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
