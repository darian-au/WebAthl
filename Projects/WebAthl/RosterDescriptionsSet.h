#if !defined(AFX_ROSTERDESCRIPTIONSSET_H__D663AA46_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_ROSTERDESCRIPTIONSSET_H__D663AA46_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RosterDescriptionsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRosterDescriptionsSet recordset

class CRosterDescriptionsSet : public CRecordsetEx
{
public:
	CRosterDescriptionsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRosterDescriptionsSet)

// Field/Param Data
	//{{AFX_FIELD(CRosterDescriptionsSet, CRecordsetEx)
	long	m_TaskID;
	CString	m_TaskDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRosterDescriptionsSet)
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

#endif // !defined(AFX_ROSTERDESCRIPTIONSSET_H__D663AA46_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
