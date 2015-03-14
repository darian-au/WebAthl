#if !defined(AFX_SECURITYPERSONSET_H__D663AA51_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
#define AFX_SECURITYPERSONSET_H__D663AA51_4F84_11D2_A2CF_00400560AE38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SecurityPersonSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSet recordset

class CSecurityPersonSet : public CRecordsetEx
{
public:
	CSecurityPersonSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSecurityPersonSet)

// Field/Param Data
	//{{AFX_FIELD(CSecurityPersonSet, CRecordsetEx)
	long	m_PersonID;
	CString	m_LoginName;
	CByteArray	m_Password;
	long	m_RoleID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecurityPersonSet)
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

#endif // !defined(AFX_SECURITYPERSONSET_H__D663AA51_4F84_11D2_A2CF_00400560AE38__INCLUDED_)
