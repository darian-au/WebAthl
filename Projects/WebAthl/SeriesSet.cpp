// SeriesSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "SeriesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet

IMPLEMENT_DYNAMIC(CSeriesSet, CRecordsetEx)

CSeriesSet::CSeriesSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CSeriesSet)
	m_SeriesID = 0;
	m_SeriesDescription = _T("");
//	m_Handicapped = FALSE;
//	m_AgeCategory = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("SeriesID");
	m_nIdentityColumn = &m_SeriesID;

	// For Non Licensed Version
	m_nCountMax = 2;
}


CString CSeriesSet::GetDefaultConnect()
{
	return _T("");
}

CString CSeriesSet::GetDefaultSQL()
{
	return _T("[Series]");
}

void CSeriesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSeriesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Series].[SeriesID]"), m_SeriesID);
	RFX_Text(pFX, _T("[Series].[SeriesDescription]"), m_SeriesDescription);
//	RFX_Bool(pFX, _T("[Series].[Handicapped]"), m_Handicapped);
//	RFX_Text(pFX, _T("[Series].[AgeCategory]"), m_AgeCategory);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet diagnostics

#ifdef _DEBUG
void CSeriesSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CSeriesSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
