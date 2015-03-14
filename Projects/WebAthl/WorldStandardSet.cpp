// WorldStandardSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "WorldStandardSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldStandardSet

IMPLEMENT_DYNAMIC(CWorldStandardSet, CRecordsetEx)

CWorldStandardSet::CWorldStandardSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CWorldStandardSet)
	m_EventTypeID = 0;
	m_AgeGroup = 0;
	m_Sex = _T("");
	m_AgeCategory = _T("");
	m_RecCategory = _T("");
	m_PerfHOUR = 0;
	m_PerfMIN = 0;
	m_PerfSEC = 0.0f;
	m_PerfFactor = 0.0f;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CWorldStandardSet::GetDefaultConnect()
{
	return _T("");
}

CString CWorldStandardSet::GetDefaultSQL()
{
	return _T("[WorldStandard]");
}

void CWorldStandardSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CWorldStandardSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[WorldStandard].[EventTypeID]"), m_EventTypeID);
	RFX_Long(pFX, _T("[WorldStandard].[AgeGroup]"), m_AgeGroup);
	RFX_Text(pFX, _T("[WorldStandard].[Sex]"), m_Sex);
	RFX_Text(pFX, _T("[WorldStandard].[AgeCategory]"), m_AgeCategory);
	RFX_Text(pFX, _T("[WorldStandard].[RecCategory]"), m_RecCategory);
	RFX_Long(pFX, _T("[WorldStandard].[PerfHOUR]"), m_PerfHOUR);
	RFX_Long(pFX, _T("[WorldStandard].[PerfMIN]"), m_PerfMIN);
	RFX_Double(pFX, _T("[WorldStandard].[PerfSEC]"), m_PerfSEC);
	RFX_Double(pFX, _T("[WorldStandard].[PerfFactor]"), m_PerfFactor);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CWorldStandardSet diagnostics

#ifdef _DEBUG
void CWorldStandardSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CWorldStandardSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
