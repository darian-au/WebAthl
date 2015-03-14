#if !defined(AFX_FINANCIALSET_H__D663AA3C_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_FINANCIALSET_H__D663AA3C_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FinancialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinancialSet recordset

class CFinancialSet : public CRecordsetEx
{
public:
	CFinancialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFinancialSet)

// Field/Param Data
	//{{AFX_FIELD(CFinancialSet, CRecordsetEx)
	long	m_PersonID;
	long	m_DateRenewedDAY;
	long	m_DateRenewedMONTH;
	long	m_DateRenewedYEAR;
	long	m_Year;
	long	m_RegistrationID;
	long	m_RegistrationTypeID;
	long	m_MailListFlag;
	long	m_OrgID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinancialSet)
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

#endif // !defined(AFX_FINANCIALSET_H__D663AA3C_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
