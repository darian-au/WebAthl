// QuickReportSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "QuickReportSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuickReportSet

IMPLEMENT_DYNAMIC(CQuickReportSet, CRecordsetEx)

CQuickReportSet::CQuickReportSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CQuickReportSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_GroupID = 0;
	m_Division = 0;
	m_GrossPerformanceHOUR = 0;
	m_GrossPerformanceMIN = 0;
	m_GrossPerformanceSEC = 0.0f;
	m_Place = 0;
	m_AgeGroup = 0;
	m_ChestNumber = _T("");

	m_NewGroupID = 0;
	m_NewGroupMessage = _T("");
	m_Points = 0;

	m_LastName = _T("");
	m_FirstName = _T("");
	m_MiddleName = _T("");
	m_Sex = _T("");
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CQuickReportSet::GetDefaultConnect()
{
	return _T("");
}

CString CQuickReportSet::GetDefaultSQL()
{
	return _T("");
}

void CQuickReportSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CQuickReportSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[GroupID]"), m_GroupID);
	RFX_Long(pFX, _T("[Division]"), m_Division);
	RFX_Long(pFX, _T("[GrossPerformanceHOUR]"), m_GrossPerformanceHOUR);
	RFX_Long(pFX, _T("[GrossPerformanceMIN]"), m_GrossPerformanceMIN);
	RFX_Double(pFX, _T("[GrossPerformanceSEC]"), m_GrossPerformanceSEC);
	RFX_Long(pFX, _T("[Place]"), m_Place);
	RFX_Long(pFX, _T("[AgeGroup]"), m_AgeGroup);
	RFX_Text(pFX, _T("[ChestNumber]"), m_ChestNumber);

	RFX_Long(pFX, _T("[NewGroupID]"), m_NewGroupID);
	RFX_Text(pFX, _T("[NewGroupMessage]"), m_NewGroupMessage);
	RFX_Long(pFX, _T("[Points]"), m_Points);

	RFX_Text(pFX, _T("[Person].[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[Person].[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Person].[MiddleName]"), m_MiddleName);
	RFX_Text(pFX, _T("[Person].[Sex]"), m_Sex);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CQuickReportSet diagnostics

#ifdef _DEBUG
void CQuickReportSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CQuickReportSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
