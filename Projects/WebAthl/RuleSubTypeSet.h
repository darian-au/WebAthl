#if !defined(AFX_RULESUBTYPESET_H__1802AD06_5C85_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_RULESUBTYPESET_H__1802AD06_5C85_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RuleSubTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleSubTypeSet recordset

class CRuleSubTypeSet : public CRecordsetEx
{
public:
	CRuleSubTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRuleSubTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CRuleSubTypeSet, CRecordsetEx)
	long	m_RuleTypeID;
	long	m_RuleSubTypeID;
	CString	m_RuleSubTypeDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleSubTypeSet)
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

#endif // !defined(AFX_RULESUBTYPESET_H__1802AD06_5C85_11D2_839B_00400548A44F__INCLUDED_)
