#if !defined(AFX_SECURITYROLESET_H__INCLUDED_)
#define AFX_SECURITYROLESET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SecurityRoleSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecurityRoleSet recordset

class CSecurityRoleSet : public CRecordsetEx
{
public:
	CSecurityRoleSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSecurityRoleSet)

// Field/Param Data
	//{{AFX_FIELD(CSecurityRoleSet, CRecordsetEx)
	long	m_RoleID;
	CString	m_RoleName;
	long	m_Permission;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecurityRoleSet)
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

#endif // !defined(AFX_SECURITYROLESET_H__INCLUDED_)
