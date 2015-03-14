#if !defined(AFX_EVENTRECORDSET_H__310179E1_C91A_11D4_982D_00400548A44F__INCLUDED_)
#define AFX_EVENTRECORDSET_H__310179E1_C91A_11D4_982D_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventRecordSet recordset

class CEventRecordSet : public CRecordsetEx
{
public:
	CEventRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CEventRecordSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_LocationID;
	long	m_EventID;
	long	m_EventTypeID;
	CString	m_Sex;
	long	m_AgeGroup;
	CString	m_AgeCategory;
	long	m_PersonID;
	long	m_ClubPerformanceHOUR;
	long	m_ClubPerformanceMIN;
	double	m_ClubPerformanceSEC;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventRecordSet)
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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTRECORDSET_H__310179E1_C91A_11D4_982D_00400548A44F__INCLUDED_)
