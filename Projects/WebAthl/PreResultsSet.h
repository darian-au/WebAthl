#if !defined(AFX_PRERESULTSSET_H__62A576C1_5BCD_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_PRERESULTSSET_H__62A576C1_5BCD_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PreResultsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreResultsSet recordset

class CPreResultsSet : public CRecordsetEx
{
public:
	CPreResultsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPreResultsSet)

// Field/Param Data
	//{{AFX_FIELD(CPreResultsSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_PersonID;
	long	m_GroupIDSupposedTo;
	long	m_DivisionSupposedTo;
	long	m_GrossPerformanceHOUR;
	long	m_GrossPerformanceMIN;
	double	m_GrossPerformanceSEC;
	long	m_Place;
	long	m_AgeGroup;
	CString	m_ChestNumber;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreResultsSet)
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

#endif // !defined(AFX_PRERESULTSSET_H__62A576C1_5BCD_11D2_839B_00400548A44F__INCLUDED_)
