#if !defined(AFX_WORLDSTANDARDSET_H__017F2681_5E15_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_WORLDSTANDARDSET_H__017F2681_5E15_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WorldStandardSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorldStandardSet recordset

class CWorldStandardSet : public CRecordsetEx
{
public:
	CWorldStandardSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CWorldStandardSet)

// Field/Param Data
	//{{AFX_FIELD(CWorldStandardSet, CRecordsetEx)
	long	m_EventTypeID;
	long	m_AgeGroup;
	CString	m_Sex;
	CString	m_AgeCategory;
	CString	m_RecCategory;
	long	m_PerfHOUR;
	long	m_PerfMIN;
	double	m_PerfSEC;
	double	m_PerfFactor;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorldStandardSet)
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

#endif // !defined(AFX_WORLDSTANDARDSET_H__017F2681_5E15_11D2_839B_00400548A44F__INCLUDED_)
