// ConsistencyAgeGroupSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ConsistencyAgeGroupSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConsistencyAgeGroupSet

IMPLEMENT_DYNAMIC(CConsistencyAgeGroupSet, CRecordsetEx)

CConsistencyAgeGroupSet::CConsistencyAgeGroupSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CConsistencyAgeGroupSet)
	m_PersonID = 0;
	m_MinAgeGroup = 0;
	m_MaxAgeGroup = 0;
	m_EventsForSeason = 0;
	m_EventsForSeries = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CConsistencyAgeGroupSet::GetDefaultConnect()
{
	return _T("");
}

CString CConsistencyAgeGroupSet::GetDefaultSQL()
{
	return _T("");
}

void CConsistencyAgeGroupSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CConsistencyAgeGroupSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[MinAgeGroup]"), m_MinAgeGroup);
	RFX_Long(pFX, _T("[MaxAgeGroup]"), m_MaxAgeGroup);
	RFX_Long(pFX, _T("[EventsForSeason]"), m_EventsForSeason);
	RFX_Long(pFX, _T("[EventsForSeries]"), m_EventsForSeries);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CConsistencyAgeGroupSet diagnostics

#ifdef _DEBUG
void CConsistencyAgeGroupSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CConsistencyAgeGroupSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
