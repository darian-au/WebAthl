#if !defined(AFX_RULESJOINSET_H__INCLUDED_)
#define AFX_RULESJOINSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RulesJoinSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRulesJoinSet recordset

class CRulesJoinSet : public CRecordsetEx
{
public:
	CRulesJoinSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRulesJoinSet)

// Field/Param Data
	//{{AFX_FIELD(CRulesJoinSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_RuleTypeID;
	long	m_RuleSubTypeID;
	long	m_RuleID;
	long	m_Law;

	long	m_RuleType_RuleTypeID;
	CString	m_RuleTypeDescription;

	long	m_RuleSubType_RuleTypeID;
	long	m_RuleSubType_RuleSubTypeID;
	CString	m_RuleSubTypeDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulesJoinSet)
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

#endif // !defined(AFX_RULESJOINSET_H__INCLUDED_)
