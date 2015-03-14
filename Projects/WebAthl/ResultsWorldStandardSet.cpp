// ResultsWorldStandardSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "ResultsWorldStandardSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultsWorldStandardSet

IMPLEMENT_DYNAMIC(CResultsWorldStandardSet, CRecordsetEx)

CResultsWorldStandardSet::CResultsWorldStandardSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CResultsWorldStandardSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_DivisionActual = 0;
	m_AgeGroup = 0;
	m_GroupIDActual = 0;
	m_GroupStartActual = 0.0f;
	m_NewGroupID = 0;
	m_NewGroupMessage = _T("");
	m_GrossPerformanceHOUR = 0;
	m_GrossPerformanceMIN = 0;
	m_GrossPerformanceSEC = 0.0f;
	m_NetPerformanceHOUR = 0;
	m_NetPerformanceMIN = 0;
	m_NetPerformanceSEC = 0.0f;
	m_Place = 0;
	m_OverallPlace = 0;
	m_Percentile = 0;
	m_Points = 0;
	m_Eligible = _T("");
	m_EventRate = 0.0f;
	m_GroupRateActual = 0.0f;
	m_ChestNumber = _T("");
	m_WorldStandard = 0.0f;
	m_GroupIDSupposedTo = 0;
	m_DivisionSupposedTo = 0;
	m_OrgID = 0;

	m_PerfHOUR = 0;
	m_PerfMIN = 0;
	m_PerfSEC = 0.0f;

	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CResultsWorldStandardSet::GetDefaultConnect()
{
	return _T("");
}

CString CResultsWorldStandardSet::GetDefaultSQL()
{
	return _T("[Results],[WorldStandard]");
}

void CResultsWorldStandardSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CResultsWorldStandardSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Results].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Results].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Results].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[Results].[DivisionActual]"), m_DivisionActual);
	RFX_Long(pFX, _T("[Results].[AgeGroup]"), m_AgeGroup);
	RFX_Long(pFX, _T("[Results].[GroupIDActual]"), m_GroupIDActual);
	RFX_Double(pFX, _T("[Results].[GroupStartActual]"), m_GroupStartActual);
	RFX_Long(pFX, _T("[Results].[NewGroupID]"), m_NewGroupID);
	RFX_Text(pFX, _T("[Results].[NewGroupMessage]"), m_NewGroupMessage);
	RFX_Long(pFX, _T("[Results].[GrossPerformanceHOUR]"), m_GrossPerformanceHOUR);
	RFX_Long(pFX, _T("[Results].[GrossPerformanceMIN]"), m_GrossPerformanceMIN);
	RFX_Double(pFX, _T("[Results].[GrossPerformanceSEC]"), m_GrossPerformanceSEC);
	RFX_Long(pFX, _T("[Results].[NetPerformanceHOUR]"), m_NetPerformanceHOUR);
	RFX_Long(pFX, _T("[Results].[NetPerformanceMIN]"), m_NetPerformanceMIN);
	RFX_Double(pFX, _T("[Results].[NetPerformanceSEC]"), m_NetPerformanceSEC);
	RFX_Long(pFX, _T("[Results].[Place]"), m_Place);
	RFX_Long(pFX, _T("[Results].[OverallPlace]"), m_OverallPlace);
	RFX_Long(pFX, _T("[Results].[Percentile]"), m_Percentile);
	RFX_Long(pFX, _T("[Results].[Points]"), m_Points);
	RFX_Text(pFX, _T("[Results].[Eligible]"), m_Eligible);
	RFX_Double(pFX, _T("[Results].[EventRate]"), m_EventRate);
	RFX_Double(pFX, _T("[Results].[GroupRateActual]"), m_GroupRateActual);
	RFX_Text(pFX, _T("[Results].[ChestNumber]"), m_ChestNumber);
	RFX_Double(pFX, _T("[Results].[WorldStandard]"), m_WorldStandard);
	RFX_Long(pFX, _T("[Results].[GroupIDSupposedTo]"), m_GroupIDSupposedTo);
	RFX_Long(pFX, _T("[Results].[DivisionSupposedTo]"), m_DivisionSupposedTo);
	RFX_Long(pFX, _T("[Results].[OrgID]"), m_OrgID);

	RFX_Long(pFX, _T("[WorldStandard].[PerfHOUR]"), m_PerfHOUR);
	RFX_Long(pFX, _T("[WorldStandard].[PerfMIN]"), m_PerfMIN);
	RFX_Double(pFX, _T("[WorldStandard].[PerfSEC]"), m_PerfSEC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CResultsWorldStandardSet diagnostics

#ifdef _DEBUG
void CResultsWorldStandardSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CResultsWorldStandardSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
