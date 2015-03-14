// PostResultsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "PostResultsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostResultsSet

IMPLEMENT_DYNAMIC(CPostResultsSet, CRecordsetEx)

CPostResultsSet::CPostResultsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CPostResultsSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_GroupIDActual = 0;
	m_DivisionActual = 0;
	m_GrossPerformanceHOUR = 0;
	m_GrossPerformanceMIN = 0;
	m_GrossPerformanceSEC = 0.0f;
	m_Place = 0;
	m_AgeGroup = 0;
	m_ChestNumber = _T("");
	m_NewGroupID = 0;
	m_NewGroupMessage = _T("");
	m_Points = 0;

	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CPostResultsSet::GetDefaultConnect()
{
	return _T("");
}

CString CPostResultsSet::GetDefaultSQL()
{
	return _T("[PostResults]");
}

void CPostResultsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPostResultsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PostResults].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[PostResults].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[PostResults].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[PostResults].[GroupIDActual]"), m_GroupIDActual);
	RFX_Long(pFX, _T("[PostResults].[DivisionActual]"), m_DivisionActual);
	RFX_Long(pFX, _T("[PostResults].[GrossPerformanceHOUR]"), m_GrossPerformanceHOUR);
	RFX_Long(pFX, _T("[PostResults].[GrossPerformanceMIN]"), m_GrossPerformanceMIN);
	RFX_Double(pFX, _T("[PostResults].[GrossPerformanceSEC]"), m_GrossPerformanceSEC);
	RFX_Long(pFX, _T("[PostResults].[Place]"), m_Place);
	RFX_Long(pFX, _T("[PostResults].[AgeGroup]"), m_AgeGroup);
	RFX_Text(pFX, _T("[PostResults].[ChestNumber]"), m_ChestNumber);
	RFX_Long(pFX, _T("[PostResults].[NewGroupID]"), m_NewGroupID);
	RFX_Text(pFX, _T("[PostResults].[NewGroupMessage]"), m_NewGroupMessage);
	RFX_Long(pFX, _T("[PostResults].[Points]"), m_Points);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPostResultsSet diagnostics

#ifdef _DEBUG
void CPostResultsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CPostResultsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
