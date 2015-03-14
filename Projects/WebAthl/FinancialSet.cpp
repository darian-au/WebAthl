// FinancialSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "FinancialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinancialSet

IMPLEMENT_DYNAMIC(CFinancialSet, CRecordsetEx)

CFinancialSet::CFinancialSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CFinancialSet)
	m_PersonID = 0;
	m_DateRenewedDAY = 0;
	m_DateRenewedMONTH = 0;
	m_DateRenewedYEAR = 0;
	m_Year = 0;
	m_RegistrationID = 0;
	m_RegistrationTypeID = 0;
	m_MailListFlag = FALSE;
	m_OrgID = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CFinancialSet::GetDefaultConnect()
{
	return _T("");
}

CString CFinancialSet::GetDefaultSQL()
{
	return _T("[Financial]");
}

void CFinancialSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFinancialSet)
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
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFinancialSet diagnostics

#ifdef _DEBUG
void CFinancialSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CFinancialSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
