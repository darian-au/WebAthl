#if !defined(AFX_INTEGERSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_INTEGERSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IntegerSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntegerSet recordset

class CIntegerSet : public CRecordsetEx
{
public:
	CIntegerSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CIntegerSet)

// Field/Param Data
	//{{AFX_FIELD(CIntegerSet, CRecordsetEx)
	long	m_Val;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntegerSet)
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

#endif // !defined(AFX_INTEGERSET_H__9FB95661_5B84_11D2_839B_00400548A44F__INCLUDED_)
