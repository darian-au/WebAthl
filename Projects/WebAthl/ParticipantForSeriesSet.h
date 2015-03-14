#if !defined(AFX_PARTICIPANTFORSERIESSET_H__D663AA40_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_PARTICIPANTFORSERIESSET_H__D663AA40_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ParticipantForSeriesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParticipantForSeriesSet recordset

class CParticipantForSeriesSet : public CRecordsetEx
{
public:
	CParticipantForSeriesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CParticipantForSeriesSet)

// Field/Param Data
	//{{AFX_FIELD(CParticipantForSeriesSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_PersonID;
	long	m_GroupIDSupposedTo;
	long	m_DivisionSupposedTo;
	long	m_ConsistencyAgeGroup;
	long	m_ConsistencyEventsCurrent;
	long	m_ConsistencyEventsOlder;
	double	m_ConsistencyEventsRate;
	long	m_EventsForSeason;
	long	m_GrossPoints;
	long	m_LowPoints;
	long	m_NetPoints;
	CString	m_EligibilityForEvent;
	long	m_OrgID;
	long	m_EventsForSeries;
	double	m_ConsistencyAgeStandard;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParticipantForSeriesSet)
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

#endif // !defined(AFX_PARTICIPANTFORSERIESSET_H__D663AA40_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
