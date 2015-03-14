// PreResultsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "PreResultsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreResultsSet

IMPLEMENT_DYNAMIC(CPreResultsSet, CRecordsetEx)

CPreResultsSet::CPreResultsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CPreResultsSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_GroupIDSupposedTo = 0;
	m_DivisionSupposedTo = 0;
	m_GrossPerformanceHOUR = 0;
	m_GrossPerformanceMIN = 0;
	m_GrossPerformanceSEC = 0.0f;
	m_Place = 0;
	m_AgeGroup = 0;
	m_ChestNumber = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CPreResultsSet::GetDefaultConnect()
{
	return _T("");
}

CString CPreResultsSet::GetDefaultSQL()
{
	return _T("[PreResults]");
}

void CPreResultsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPreResultsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PreResults].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[PreResults].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[PreResults].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[PreResults].[GroupIDSupposedTo]"), m_GroupIDSupposedTo);
	RFX_Long(pFX, _T("[PreResults].[DivisionSupposedTo]"), m_DivisionSupposedTo);
	RFX_Long(pFX, _T("[PreResults].[GrossPerformanceHOUR]"), m_GrossPerformanceHOUR);
	RFX_Long(pFX, _T("[PreResults].[GrossPerformanceMIN]"), m_GrossPerformanceMIN);
	RFX_Double(pFX, _T("[PreResults].[GrossPerformanceSEC]"), m_GrossPerformanceSEC);
	RFX_Long(pFX, _T("[PreResults].[Place]"), m_Place);
	RFX_Long(pFX, _T("[PreResults].[AgeGroup]"), m_AgeGroup);
	RFX_Text(pFX, _T("[PreResults].[ChestNumber]"), m_ChestNumber);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPreResultsSet diagnostics

#ifdef _DEBUG
void CPreResultsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CPreResultsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
