// RegistrationTypeSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "RegistrationTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistrationTypeSet

IMPLEMENT_DYNAMIC(CRegistrationTypeSet, CRecordsetEx)

CRegistrationTypeSet::CRegistrationTypeSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CRegistrationTypeSet)
	m_RegistrationTypeID = 0;
	m_RegistrationDescription = _T("");
	m_MonthStart = 0;
	m_MonthStop = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("RegistrationTypeID");
	m_nIdentityColumn = &m_RegistrationTypeID;
}


CString CRegistrationTypeSet::GetDefaultConnect()
{
	return _T("");
}

CString CRegistrationTypeSet::GetDefaultSQL()
{
	return _T("[RegistrationType]");
}

void CRegistrationTypeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRegistrationTypeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[RegistrationType].[RegistrationTypeID]"), m_RegistrationTypeID);
	RFX_Text(pFX, _T("[RegistrationType].[RegistrationDescription]"), m_RegistrationDescription);
	RFX_Long(pFX, _T("[RegistrationType].[MonthStart]"), m_MonthStart);
	RFX_Long(pFX, _T("[RegistrationType].[MonthStop]"), m_MonthStop);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRegistrationTypeSet diagnostics

#ifdef _DEBUG
void CRegistrationTypeSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CRegistrationTypeSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
