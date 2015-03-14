// PersonFinancialSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "PersonFinancialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonFinancialSet

IMPLEMENT_DYNAMIC(CPersonFinancialSet, CRecordsetEx)

CPersonFinancialSet::CPersonFinancialSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CPersonFinancialSet)
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
	m_Financial_PersonID = 0;
	m_DateRenewedDAY = 0;
	m_DateRenewedMONTH = 0;
	m_DateRenewedYEAR = 0;
	m_Year = 0;
	m_RegistrationID = 0;
	m_RegistrationTypeID = 0;
	m_MailListFlag = FALSE;
	m_OrgID = 0;
	m_RegistrationTypeID = 0;
	m_RegistrationDescription = _T("");
	m_MonthStart = 0;
	m_MonthStop = 0;

	m_Organisation_OrgID = 0;
	m_OrgName = _T("");
	m_Organisation_Address1 = _T("");
	m_Organisation_Address2 = _T("");
	m_Organisation_Town = _T("");
	m_Organisation_State = _T("");
	m_Organisation_Country = _T("");
	m_Organisation_PostCode = _T("");
	m_Organisation_Phone = _T("");
	m_Organisation_Fax = _T("");
	m_Organisation_Mobile = _T("");
	m_Organisation_email = _T("");
	m_Organisation_URL = _T("");
	m_Organisation_RegistrarPersonID = 0;
	m_Organisation_AdministratorPersonID = 0;
	m_nFields = 48;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CPersonFinancialSet::GetDefaultConnect()
{
	return _T("");
}

CString CPersonFinancialSet::GetDefaultSQL()
{
	return _T("[Person],[Financial],[RegistrationType],[Organisation]");
}

void CPersonFinancialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonFinancialSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
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

	RFX_Long(pFX, _T("[Financial].[PersonID]"), m_Financial_PersonID);
	RFX_Long(pFX, _T("[Financial].[DateRenewedDAY]"), m_DateRenewedDAY);
	RFX_Long(pFX, _T("[Financial].[DateRenewedMONTH]"), m_DateRenewedMONTH);
	RFX_Long(pFX, _T("[Financial].[DateRenewedYEAR]"), m_DateRenewedYEAR);
	RFX_Long(pFX, _T("[Financial].[Year]"), m_Year);
	RFX_Long(pFX, _T("[Financial].[RegistrationID]"), m_RegistrationID);
	RFX_Long(pFX, _T("[Financial].[RegistrationTypeID]"), m_RegistrationTypeID);
	RFX_Long(pFX, _T("[Financial].[MailListFlag]"), m_MailListFlag);
	RFX_Long(pFX, _T("[Financial].[OrgID]"), m_OrgID);

	RFX_Long(pFX, _T("[RegistrationType].[RegistrationTypeID]"), m_RegistrationType_RegistrationTypeID);
	RFX_Text(pFX, _T("[RegistrationType].[RegistrationDescription]"), m_RegistrationDescription);
	RFX_Long(pFX, _T("[RegistrationType].[MonthStart]"), m_MonthStart);
	RFX_Long(pFX, _T("[RegistrationType].[MonthStop]"), m_MonthStop);

	RFX_Long(pFX, _T("[Organisation].[OrgID]"), m_Organisation_OrgID);
	RFX_Text(pFX, _T("[Organisation].[OrgName]"), m_OrgName);
	RFX_Text(pFX, _T("[Organisation].[Address1]"), m_Organisation_Address1);
	RFX_Text(pFX, _T("[Organisation].[Address2]"), m_Organisation_Address2);
	RFX_Text(pFX, _T("[Organisation].[Town]"), m_Organisation_Town);
	RFX_Text(pFX, _T("[Organisation].[State]"), m_Organisation_State);
	RFX_Text(pFX, _T("[Organisation].[Country]"), m_Organisation_Country);
	RFX_Text(pFX, _T("[Organisation].[PostCode]"), m_Organisation_PostCode);
	RFX_Text(pFX, _T("[Organisation].[Phone]"), m_Organisation_Phone);
	RFX_Text(pFX, _T("[Organisation].[Fax]"), m_Organisation_Fax);
	RFX_Text(pFX, _T("[Organisation].[Mobile]"), m_Organisation_Mobile);
	RFX_Text(pFX, _T("[Organisation].[email]"), m_Organisation_email);
	RFX_Text(pFX, _T("[Organisation].[URL]"), m_Organisation_URL);
	RFX_Long(pFX, _T("[Organisation].[RegistrarPersonID]"), m_Organisation_RegistrarPersonID);
	RFX_Long(pFX, _T("[Organisation].[AdministratorPersonID]"), m_Organisation_AdministratorPersonID);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPersonFinancialSet diagnostics

#ifdef _DEBUG
void CPersonFinancialSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CPersonFinancialSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
