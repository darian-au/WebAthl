#if !defined(AFX_ROSTERNAMESSET_H__EC473CC1_5B18_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_ROSTERNAMESSET_H__EC473CC1_5B18_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RosterNamesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRosterNamesSet recordset

class CRosterNamesSet : public CRecordsetEx
{
public:
	CRosterNamesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRosterNamesSet)

// Field/Param Data
	//{{AFX_FIELD(CRosterNamesSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_Roster_PersonID;
	long	m_Roster_TaskID;

	long	m_RosterDescriptions_TaskID;
	CString	m_TaskDescription;

	long	m_Person_PersonID;
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
	//{{AFX_VIRTUAL(CRosterNamesSet)
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

#endif // !defined(AFX_ROSTERNAMESSET_H__EC473CC1_5B18_11D2_839B_00400548A44F__INCLUDED_)
