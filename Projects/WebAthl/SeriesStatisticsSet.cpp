// SeriesStatisticsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SeriesStatisticsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesStatisticsSet

IMPLEMENT_DYNAMIC(CSeriesStatisticsSet, CRecordsetEx)

CSeriesStatisticsSet::CSeriesStatisticsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSeriesStatisticsSet)
	m_AgeGroup = 0;
	m_Total = 0;
	m_Sex = _T("");

	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSeriesStatisticsSet::GetDefaultConnect()
{
	return _T("");
}

CString CSeriesStatisticsSet::GetDefaultSQL()
{
	return _T("");
}

void CSeriesStatisticsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSeriesStatisticsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AgeGroup]"), m_AgeGroup);
	RFX_Long(pFX, _T("[Total]"), m_Total);
	RFX_Text(pFX, _T("[Sex]"), m_Sex);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSeriesStatisticsSet diagnostics

#ifdef _DEBUG
void CSeriesStatisticsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSeriesStatisticsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
