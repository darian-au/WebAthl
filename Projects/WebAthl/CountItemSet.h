#if !defined(AFX_COUNTITEMSET_H__INCLUDED_)
#define AFX_COUNTITEMSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CountItemSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountItemSet recordset

class CCountItemSet : public CRecordsetEx
{
public:
	CCountItemSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCountItemSet)

// Field/Param Data
	//{{AFX_FIELD(CCountItemSet, CRecordsetEx)
	long	m_Total;
	CString	m_Details;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountItemSet)
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

#endif // !defined(AFX_COUNTITEMSET_H__INCLUDED_)
