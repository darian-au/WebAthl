#if !defined(AFX_ROSTERSET_H__D663AA44_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_ROSTERSET_H__D663AA44_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RosterSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRosterSet recordset

class CRosterSet : public CRecordsetEx
{
public:
	CRosterSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRosterSet)

// Field/Param Data
	//{{AFX_FIELD(CRosterSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_PersonID;
	long	m_TaskID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRosterSet)
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

#endif // !defined(AFX_ROSTERSET_H__D663AA44_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
