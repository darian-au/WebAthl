#if !defined(AFX_QUICKREPORTSET_H__684B4BE6_5BE1_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_QUICKREPORTSET_H__684B4BE6_5BE1_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QuickReportSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuickReportSet recordset

class CQuickReportSet : public CRecordsetEx
{
public:
	CQuickReportSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CQuickReportSet)

// Field/Param Data
	//{{AFX_FIELD(CQuickReportSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_PersonID;
	long	m_GroupID;
	long	m_Division;
	long	m_GrossPerformanceHOUR;
	long	m_GrossPerformanceMIN;
	double	m_GrossPerformanceSEC;
	long	m_Place;
	long	m_AgeGroup;
	CString	m_ChestNumber;

	long	m_NewGroupID;
	CString	m_NewGroupMessage;
	long	m_Points;

	CString	m_LastName;
	CString	m_FirstName;
	CString	m_MiddleName;
	CString	m_Sex;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickReportSet)
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

#endif // !defined(AFX_QUICKREPORTSET_H__684B4BE6_5BE1_11D2_839B_00400548A44F__INCLUDED_)
