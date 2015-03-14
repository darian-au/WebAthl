#if !defined(AFX_ORGANISATIONSET_H__077C5385_4FBC_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_ORGANISATIONSET_H__077C5385_4FBC_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OrganisationSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrganisationSet recordset

class COrganisationSet : public CRecordsetEx
{
public:
	COrganisationSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COrganisationSet)

// Field/Param Data
	//{{AFX_FIELD(COrganisationSet, CRecordsetEx)
	long	m_OrgID;
	CString	m_OrgName;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_Town;
	CString	m_State;
	CString	m_Country;
	CString	m_PostCode;
	CString	m_Phone;
	CString	m_Fax;
	CString	m_Mobile;
	CString	m_email;
	CString	m_URL;
	long	m_RegistrarPersonID;
	long	m_AdministratorPersonID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrganisationSet)
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

#endif // !defined(AFX_ORGANISATIONSET_H__077C5385_4FBC_11D2_839B_00400548A44F__INCLUDED_)
