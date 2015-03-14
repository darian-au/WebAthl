#if !defined(AFX_VALIDATESET_H__6E7F1445_5ED6_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_VALIDATESET_H__6E7F1445_5ED6_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ValidateSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CValidateSet recordset

class CValidateSet : public CRecordsetEx
{
public:
	CValidateSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CValidateSet)

// Field/Param Data
	//{{AFX_FIELD(CValidateSet, CRecordsetEx)
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

	long	m_SecurityPerson_PersonID;
	CString	m_LoginName;
	CByteArray	m_Password;
	long	m_SecurityPerson_RoleID;

	long	m_RoleID;
	CString	m_RoleName;
	long	m_Permission;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidateSet)
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

#endif // !defined(AFX_VALIDATESET_H__6E7F1445_5ED6_11D2_839B_00400548A44F__INCLUDED_)
