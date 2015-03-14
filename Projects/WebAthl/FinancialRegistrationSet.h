#if !defined(AFX_FINANCIALREGISTRATIONSET_H__INCLUDED_)
#define AFX_FINANCIALREGISTRATIONSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FinancialRegistrationSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinancialRegistrationSet recordset

class CFinancialRegistrationSet : public CRecordsetEx
{
public:
	CFinancialRegistrationSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFinancialRegistrationSet)

// Field/Param Data
	//{{AFX_FIELD(CFinancialRegistrationSet, CRecordsetEx)
	long	m_PersonID;
	long	m_DateRenewedDAY;
	long	m_DateRenewedMONTH;
	long	m_DateRenewedYEAR;
	long	m_Year;
	long	m_RegistrationID;
	long	m_RegistrationTypeID;
	long	m_MailListFlag;
	long	m_OrgID;

	long	m_RegistrationType_RegistrationTypeID;
	CString	m_RegistrationDescription;
	long	m_MonthStart;
	long	m_MonthStop;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinancialRegistrationSet)
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

#endif // !defined(AFX_FINANCIALREGISTRATIONSET_H__INCLUDED_)
