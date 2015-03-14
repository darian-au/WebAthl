#if !defined(AFX_SERIESSEASONSET_H__C4454AA1_6B8A_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_SERIESSEASONSET_H__C4454AA1_6B8A_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeriesSeasonSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeriesSeasonSet recordset

class CSeriesSeasonSet : public CRecordsetEx
{
public:
	CSeriesSeasonSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeriesSeasonSet)

// Field/Param Data
	//{{AFX_FIELD(CSeriesSeasonSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_FirstEventForSeason;
	long	m_EventsInSeason;
	long	m_NextEventForProcess;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesSeasonSet)
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

#endif // !defined(AFX_SERIESSEASONSET_H__C4454AA1_6B8A_11D2_839B_00400548A44F__INCLUDED_)
