#if !defined(AFX_DUPPERSONSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_DUPPERSONSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DupPersonSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDupPersonSet recordset

class CDupPersonSet : public CRecordsetEx
{
public:
	CDupPersonSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDupPersonSet)

// Field/Param Data
	//{{AFX_FIELD(CDupPersonSet, CRecordsetEx)
	long	m_PersonID;
	long	m_Val;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDupPersonSet)
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

#endif // !defined(AFX_DUPPERSONSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_)
