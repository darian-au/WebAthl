#if !defined(AFX_GROUPSSET_H__D663AA3D_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_GROUPSSET_H__D663AA3D_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GroupsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupsSet recordset

class CGroupsSet : public CRecordsetEx
{
public:
	CGroupsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGroupsSet)

// Field/Param Data
	//{{AFX_FIELD(CGroupsSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventTypeID;
	long	m_GroupID;
	double	m_GroupRate;
	double	m_GroupStart;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupsSet)
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

#endif // !defined(AFX_GROUPSSET_H__D663AA3D_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
