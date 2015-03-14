#if !defined(AFX_EVENTTALLYSET_H__8BD0C985_6D90_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_EVENTTALLYSET_H__8BD0C985_6D90_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EventTallySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventTallySet recordset

class CEventTallySet : public CRecordsetEx
{
public:
	CEventTallySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventTallySet)

// Field/Param Data
	//{{AFX_FIELD(CEventTallySet, CRecordsetEx)
	long	m_PersonID;
	CString	m_FirstName;
	CString	m_LastName;
	long	m_EventTally;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventTallySet)
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

#endif // !defined(AFX_EVENTTALLYSET_H__8BD0C985_6D90_11D2_839B_00400548A44F__INCLUDED_)
