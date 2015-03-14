#if !defined(AFX_RULETYPESET_H__1802AD05_5C85_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_RULETYPESET_H__1802AD05_5C85_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RuleTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleTypeSet recordset

class CRuleTypeSet : public CRecordsetEx
{
public:
	CRuleTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRuleTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CRuleTypeSet, CRecordsetEx)
	long	m_RuleTypeID;
	CString	m_RuleTypeDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleTypeSet)
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

#endif // !defined(AFX_RULETYPESET_H__1802AD05_5C85_11D2_839B_00400548A44F__INCLUDED_)
