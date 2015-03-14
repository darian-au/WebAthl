// SecurityPersonSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SecurityPersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSet

IMPLEMENT_DYNAMIC(CSecurityPersonSet, CRecordsetEx)

CSecurityPersonSet::CSecurityPersonSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSecurityPersonSet)
	m_PersonID = 0;
	m_LoginName = _T("");
	m_RoleID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSecurityPersonSet::GetDefaultConnect()
{
	return _T("");
}

CString CSecurityPersonSet::GetDefaultSQL()
{
	return _T("[SecurityPerson]");
}

void CSecurityPersonSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSecurityPersonSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SecurityPerson].[PersonID]"), m_PersonID);
	RFX_Text(pFX, _T("[SecurityPerson].[LoginName]"), m_LoginName);
	RFX_Binary(pFX, _T("[SecurityPerson].[Password]"), m_Password);
	RFX_Long(pFX, _T("[SecurityPerson].[RoleID]"), m_RoleID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSet diagnostics

#ifdef _DEBUG
void CSecurityPersonSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSecurityPersonSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
