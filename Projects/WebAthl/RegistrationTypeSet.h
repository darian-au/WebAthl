#if !defined(AFX_REGISTRATIONTYPESET_H__4B0FEBE1_FD97_11D3_982D_00400548A44F__INCLUDED_)
#define AFX_REGISTRATIONTYPESET_H__4B0FEBE1_FD97_11D3_982D_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegistrationTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegistrationTypeSet recordset

class CRegistrationTypeSet : public CRecordsetEx
{
public:
	CRegistrationTypeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRegistrationTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CRegistrationTypeSet, CRecordsetEx)
	long	m_RegistrationTypeID;
	CString	m_RegistrationDescription;
	long	m_MonthStart;
	long	m_MonthStop;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistrationTypeSet)
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

#endif // !defined(AFX_REGISTRATIONTYPESET_H__4B0FEBE1_FD97_11D3_982D_00400548A44F__INCLUDED_)
