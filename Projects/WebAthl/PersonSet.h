#if !defined(AFX_PERSONSET_H__1802AD02_5C85_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_PERSONSET_H__1802AD02_5C85_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PersonSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonSet recordset

class CPersonSet : public CRecordsetEx
{
public:
	CPersonSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonSet)

// Field/Param Data
	//{{AFX_FIELD(CPersonSet, CRecordsetEx)
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
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonSet)
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

#endif // !defined(AFX_PERSONSET_H__1802AD02_5C85_11D2_839B_00400548A44F__INCLUDED_)
