#if !defined(AFX_RESULTSPOSTRESULTSSET_H__INCLUDED_)
#define AFX_RESULTSPOSTRESULTSSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ResultsPostResultsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultsPostResultsSet recordset

class CResultsPostResultsSet : public CRecordsetEx
{
public:
	CResultsPostResultsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CResultsPostResultsSet)

// Field/Param Data
	//{{AFX_FIELD(CResultsPostResultsSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_PersonID;
	long	m_DivisionActual;
	long	m_AgeGroup;
	long	m_GroupIDActual;
	double	m_GroupStartActual;
	long	m_NewGroupID;
	CString	m_NewGroupMessage;
	long	m_GrossPerformanceHOUR;
	long	m_GrossPerformanceMIN;
	double	m_GrossPerformanceSEC;
	long	m_NetPerformanceHOUR;
	long	m_NetPerformanceMIN;
	double	m_NetPerformanceSEC;
	long	m_Place;
	long	m_OverallPlace;
	long	m_Percentile;
	long	m_Points;
	CString	m_Eligible;
	double	m_EventRate;
	double	m_GroupRateActual;
	CString	m_ChestNumber;
	double	m_WorldStandard;
	long	m_GroupIDSupposedTo;
	long	m_DivisionSupposedTo;
	long	m_OrgID;

	long	m_Post_SeriesID;
	long	m_Post_EventID;
	long	m_Post_PersonID;
	long	m_Post_GroupIDActual;
	long	m_Post_DivisionActual;
	long	m_Post_GrossPerformanceHOUR;
	long	m_Post_GrossPerformanceMIN;
	double	m_Post_GrossPerformanceSEC;
	long	m_Post_Place;
	long	m_Post_AgeGroup;
	CString	m_Post_ChestNumber;
	long	m_Post_NewGroupID;
	CString	m_Post_NewGroupMessage;
	long	m_Post_Points;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsPostResultsSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTSPOSTRESULTSSET_H__INCLUDED_)
