// GroupsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "GroupsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupsSet

IMPLEMENT_DYNAMIC(CGroupsSet, CRecordsetEx)

CGroupsSet::CGroupsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CGroupsSet)
	m_SeriesID = 0;
	m_EventTypeID = 0;
	m_GroupID = 0;
	m_GroupRate = 0.0f;
	m_GroupStart = 0.0f;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CGroupsSet::GetDefaultConnect()
{
	return _T("");
}

CString CGroupsSet::GetDefaultSQL()
{
	return _T("[Groups]");
}

void CGroupsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGroupsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Groups].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Groups].[EventTypeID]"), m_EventTypeID);
	RFX_Long(pFX, _T("[Groups].[GroupID]"), m_GroupID);
	RFX_Double(pFX, _T("[Groups].[GroupRate]"), m_GroupRate);
	RFX_Double(pFX, _T("[Groups].[GroupStart]"), m_GroupStart);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGroupsSet diagnostics

#ifdef _DEBUG
void CGroupsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CGroupsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
