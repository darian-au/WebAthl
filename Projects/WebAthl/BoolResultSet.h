#if !defined(AFX_BOOLRESULTSET_H__35345F04_5DC9_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_BOOLRESULTSET_H__35345F04_5DC9_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BoolResultSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoolResultSet recordset

class CBoolResultSet : public CRecordsetEx
{
public:
	CBoolResultSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBoolResultSet)

// Field/Param Data
	//{{AFX_FIELD(CBoolResultSet, CRecordsetEx)
	long	m_Result;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoolResultSet)
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

#endif // !defined(AFX_BOOLRESULTSET_H__35345F04_5DC9_11D2_839B_00400548A44F__INCLUDED_)
