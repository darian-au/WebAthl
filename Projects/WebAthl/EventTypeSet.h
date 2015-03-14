#if !defined(AFX_EVENTTYPESET_H__D663AA3B_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_EVENTTYPESET_H__D663AA3B_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EventTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventTypeSet recordset

class CEventTypeSet : public CRecordsetEx
{
public:
	CEventTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CEventTypeSet, CRecordsetEx)
	long	m_EventTypeID;
	CString	m_EventDescription;
	long	m_Timed;
	double	m_EventLength;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventTypeSet)
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

#endif // !defined(AFX_EVENTTYPESET_H__D663AA3B_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
