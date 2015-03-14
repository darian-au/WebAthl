// FinancialRegistrationSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "FinancialRegistrationSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinancialRegistrationSet

IMPLEMENT_DYNAMIC(CFinancialRegistrationSet, CRecordsetEx)

CFinancialRegistrationSet::CFinancialRegistrationSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CFinancialRegistrationSet)
	m_PersonID = 0;
	m_DateRenewedDAY = 0;
	m_DateRenewedMONTH = 0;
	m_DateRenewedYEAR = 0;
	m_Year = 0;
	m_RegistrationID = 0;
	m_RegistrationTypeID = 0;
	m_MailListFlag = FALSE;
	m_OrgID = 0;

	m_RegistrationType_RegistrationTypeID = 0;
	m_RegistrationDescription = _T("");
	m_MonthStart = 0;
	m_MonthStop = 0;

	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CFinancialRegistrationSet::GetDefaultConnect()
{
	return _T("");
}

CString CFinancialRegistrationSet::GetDefaultSQL()
{
	return _T("[Financial],[RegistrationType]");
}

void CFinancialRegistrationSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFinancialRegistrationSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Financial].[PersonID]"), m_PersonID);
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
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFinancialRegistrationSet diagnostics

#ifdef _DEBUG
void CFinancialRegistrationSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CFinancialRegistrationSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
