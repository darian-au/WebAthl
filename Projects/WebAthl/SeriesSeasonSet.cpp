// SeriesSeasonSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SeriesSeasonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesSeasonSet

IMPLEMENT_DYNAMIC(CSeriesSeasonSet, CRecordsetEx)

CSeriesSeasonSet::CSeriesSeasonSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSeriesSeasonSet)
	m_SeriesID = 0;
	m_FirstEventForSeason = 0;
	m_EventsInSeason = 0;
	m_NextEventForProcess = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSeriesSeasonSet::GetDefaultConnect()
{
	return _T("");
}

CString CSeriesSeasonSet::GetDefaultSQL()
{
	return _T("[SeriesSeason]");
}

void CSeriesSeasonSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSeriesSeasonSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SeriesSeason].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[SeriesSeason].[FirstEventForSeason]"), m_FirstEventForSeason);
	RFX_Long(pFX, _T("[SeriesSeason].[EventsInSeason]"), m_EventsInSeason);
	RFX_Long(pFX, _T("[SeriesSeason].[NextEventForProcess]"), m_NextEventForProcess);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSeriesSeasonSet diagnostics

#ifdef _DEBUG
void CSeriesSeasonSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSeriesSeasonSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
