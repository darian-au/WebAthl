// SecurityPersonSeriesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SecurityPersonSeriesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSeriesSet

IMPLEMENT_DYNAMIC(CSecurityPersonSeriesSet, CRecordsetEx)

CSecurityPersonSeriesSet::CSecurityPersonSeriesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSecurityPersonSeriesSet)
	m_PersonID = 0;
	m_SeriesID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSecurityPersonSeriesSet::GetDefaultConnect()
{
	return _T("");
}

CString CSecurityPersonSeriesSet::GetDefaultSQL()
{
	return _T("[SecurityPersonSeries]");
}

void CSecurityPersonSeriesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSecurityPersonSeriesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SecurityPersonSeries].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[SecurityPersonSeries].[SeriesID]"), m_SeriesID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSeriesSet diagnostics

#ifdef _DEBUG
void CSecurityPersonSeriesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSecurityPersonSeriesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
