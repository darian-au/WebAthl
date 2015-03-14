#if !defined(AFX_DOUBLESET_H__INCLUDED_)
#define AFX_DOUBLESET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DoubleSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoubleSet recordset

class CDoubleSet : public CRecordsetEx
{
public:
	CDoubleSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDoubleSet)

// Field/Param Data
	//{{AFX_FIELD(CDoubleSet, CRecordsetEx)
	double	m_Val;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoubleSet)
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

#endif // !defined(AFX_DOUBLESET_H__INCLUDED_)
