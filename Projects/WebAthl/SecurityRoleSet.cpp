// SecurityRoleSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SecurityRoleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecurityRoleSet

IMPLEMENT_DYNAMIC(CSecurityRoleSet, CRecordsetEx)

CSecurityRoleSet::CSecurityRoleSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSecurityRoleSet)
	m_RoleID = 0;
	m_RoleName = _T("");
	m_Permission = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("RoleID");
	m_nIdentityColumn = &m_RoleID;
}


CString CSecurityRoleSet::GetDefaultConnect()
{
	return _T("");
}

CString CSecurityRoleSet::GetDefaultSQL()
{
	return _T("[SecurityRole]");
}

void CSecurityRoleSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSecurityRoleSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SecurityRole].[RoleID]"), m_RoleID);
	RFX_Text(pFX, _T("[SecurityRole].[RoleName]"), m_RoleName);
	RFX_Long(pFX, _T("[SecurityRole].[Permission]"), m_Permission);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSecurityRoleSet diagnostics

#ifdef _DEBUG
void CSecurityRoleSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSecurityRoleSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
