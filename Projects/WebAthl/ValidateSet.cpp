// ValidateSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ValidateSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValidateSet

IMPLEMENT_DYNAMIC(CValidateSet, CRecordsetEx)

CValidateSet::CValidateSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CValidateSet)
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

	m_SecurityPerson_PersonID = 0;
	m_LoginName = _T("");
	m_SecurityPerson_RoleID = 0;

	m_RoleID = 0;
	m_RoleName = _T("");
	m_Permission = 0;

	m_nFields = 27;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CValidateSet::GetDefaultConnect()
{
	return _T("");
}

CString CValidateSet::GetDefaultSQL()
{
	return _T("[Person],[SecurityPerson],[SecurityRole]");
}

void CValidateSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CValidateSet)
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

	RFX_Long(pFX, _T("[SecurityPerson].[PersonID]"), m_SecurityPerson_PersonID);
	RFX_Text(pFX, _T("[SecurityPerson].[LoginName]"), m_LoginName);
	RFX_Binary(pFX, _T("[SecurityPerson].[Password]"), m_Password);
	RFX_Long(pFX, _T("[SecurityPerson].[RoleID]"), m_SecurityPerson_RoleID);

	RFX_Long(pFX, _T("[SecurityRole].[RoleID]"), m_RoleID);
	RFX_Text(pFX, _T("[SecurityRole].[RoleName]"), m_RoleName);
	RFX_Long(pFX, _T("[SecurityRole].[Permission]"), m_Permission);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CValidateSet diagnostics

#ifdef _DEBUG
void CValidateSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CValidateSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
