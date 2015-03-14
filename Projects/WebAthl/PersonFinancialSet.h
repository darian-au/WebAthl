#if !defined(AFX_PERSONFINANCIALSET_H__1F8504A2_B626_11D3_839B_00400548A44F__INCLUDED_)
#define AFX_PERSONFINANCIALSET_H__1F8504A2_B626_11D3_839B_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonFinancialSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonFinancialSet recordset

class CPersonFinancialSet : public CRecordsetEx
{
public:
	CPersonFinancialSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonFinancialSet)

// Field/Param Data
	//{{AFX_FIELD(CPersonFinancialSet, CRecordsetEx)
	long	m_PersonID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_MiddleName;
	long	m_dobDAY;
	long	m_dobMONTH;
	long	m_dobYEAR;
	CString	m_Sex;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_Town;
	CString	m_State;
	CString	m_Country;
	CString	m_PostCode;
	CString	m_PhoneHm;
	CString	m_PhoneWk;
	CString	m_Fax;
	CString	m_Mobile;
	CString	m_email;
	long	m_ContactPersonID;

	long	m_Financial_PersonID;
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

	long	m_Organisation_OrgID;
	CString	m_OrgName;
	CString	m_Organisation_Address1;
	CString	m_Organisation_Address2;
	CString	m_Organisation_Town;
	CString	m_Organisation_State;
	CString	m_Organisation_Country;
	CString	m_Organisation_PostCode;
	CString	m_Organisation_Phone;
	CString	m_Organisation_Fax;
	CString	m_Organisation_Mobile;
	CString	m_Organisation_email;
	CString	m_Organisation_URL;
	long	m_Organisation_RegistrarPersonID;
	long	m_Organisation_AdministratorPersonID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonFinancialSet)
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
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONFINANCIALSET_H__1F8504A2_B626_11D3_839B_00400548A44F__INCLUDED_)
