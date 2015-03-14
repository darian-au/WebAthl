// RosterNamesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RosterNamesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRosterNamesSet

IMPLEMENT_DYNAMIC(CRosterNamesSet, CRecordsetEx)

CRosterNamesSet::CRosterNamesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRosterNamesSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_Roster_PersonID = 0;
	m_Roster_TaskID = 0;
	m_RosterDescriptions_TaskID = 0;
	m_TaskDescription = _T("");
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
	m_nFields = 26;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRosterNamesSet::GetDefaultConnect()
{
	return _T("");
}

CString CRosterNamesSet::GetDefaultSQL()
{
	return _T("[Roster],[RosterDescriptions],[Person]");
}

void CRosterNamesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRosterNamesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Roster].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Roster].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Roster].[PersonID]"), m_Roster_PersonID);
	RFX_Long(pFX, _T("[Roster].[TaskID]"), m_Roster_TaskID);

	RFX_Long(pFX, _T("[RosterDescriptions].[TaskID]"), m_RosterDescriptions_TaskID);
	RFX_Text(pFX, _T("[RosterDescriptions].[TaskDescription]"), m_TaskDescription);

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
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRosterNamesSet diagnostics

#ifdef _DEBUG
void CRosterNamesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRosterNamesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
