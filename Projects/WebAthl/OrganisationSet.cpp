// OrganisationSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "OrganisationSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrganisationSet

IMPLEMENT_DYNAMIC(COrganisationSet, CRecordsetEx)

COrganisationSet::COrganisationSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(COrganisationSet)
	m_OrgID = 0;
	m_OrgName = _T("");
	m_Address1 = _T("");
	m_Address2 = _T("");
	m_Town = _T("");
	m_State = _T("");
	m_Country = _T("");
	m_PostCode = _T("");
	m_Phone = _T("");
	m_Fax = _T("");
	m_Mobile = _T("");
	m_email = _T("");
	m_URL = _T("");
	m_RegistrarPersonID = 0;
	m_AdministratorPersonID = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("OrgID");
	m_nIdentityColumn = &m_OrgID;
}


CString COrganisationSet::GetDefaultConnect()
{
	return _T("");
}

CString COrganisationSet::GetDefaultSQL()
{
	return _T("[Organisation]");
}

void COrganisationSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COrganisationSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Organisation].[OrgID]"), m_OrgID);
	RFX_Text(pFX, _T("[Organisation].[OrgName]"), m_OrgName);
	RFX_Text(pFX, _T("[Organisation].[Address1]"), m_Address1);
	RFX_Text(pFX, _T("[Organisation].[Address2]"), m_Address2);
	RFX_Text(pFX, _T("[Organisation].[Town]"), m_Town);
	RFX_Text(pFX, _T("[Organisation].[State]"), m_State);
	RFX_Text(pFX, _T("[Organisation].[Country]"), m_Country);
	RFX_Text(pFX, _T("[Organisation].[PostCode]"), m_PostCode);
	RFX_Text(pFX, _T("[Organisation].[Phone]"), m_Phone);
	RFX_Text(pFX, _T("[Organisation].[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[Organisation].[Mobile]"), m_Mobile);
	RFX_Text(pFX, _T("[Organisation].[email]"), m_email);
	RFX_Text(pFX, _T("[Organisation].[URL]"), m_URL);
	RFX_Long(pFX, _T("[Organisation].[RegistrarPersonID]"), m_RegistrarPersonID);
	RFX_Long(pFX, _T("[Organisation].[AdministratorPersonID]"), m_AdministratorPersonID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COrganisationSet diagnostics

#ifdef _DEBUG
void COrganisationSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void COrganisationSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
