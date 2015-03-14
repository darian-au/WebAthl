#if !defined(AFX_LOCATIONSET_H__D663AA3E_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_LOCATIONSET_H__D663AA3E_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LocationSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocationSet recordset

class CLocationSet : public CRecordsetEx
{
public:
	CLocationSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLocationSet)

// Field/Param Data
	//{{AFX_FIELD(CLocationSet, CRecordsetEx)
	long	m_LocationID;
	CString	m_LocationDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocationSet)
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

#endif // !defined(AFX_LOCATIONSET_H__D663AA3E_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
