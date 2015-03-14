#if !defined(AFX_RULESSET_H__1802AD04_5C85_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_RULESSET_H__1802AD04_5C85_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RulesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRulesSet recordset

class CRulesSet : public CRecordsetEx
{
public:
	CRulesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRulesSet)

// Field/Param Data
	//{{AFX_FIELD(CRulesSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_RuleTypeID;
	long	m_RuleSubTypeID;
	long	m_RuleID;
	long	m_Law;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulesSet)
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

#endif // !defined(AFX_RULESSET_H__1802AD04_5C85_11D2_839B_00400548A44F__INCLUDED_)
