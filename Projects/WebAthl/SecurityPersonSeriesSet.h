#if !defined(AFX_SECURITYPERSONSERIESSET_H__BC02AB61_AB19_11D3_839B_00400548A44F__INCLUDED_)
#define AFX_SECURITYPERSONSERIESSET_H__BC02AB61_AB19_11D3_839B_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SecurityPersonSeriesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecurityPersonSeriesSet recordset

class CSecurityPersonSeriesSet : public CRecordsetEx
{
public:
	CSecurityPersonSeriesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSecurityPersonSeriesSet)

// Field/Param Data
	//{{AFX_FIELD(CSecurityPersonSeriesSet, CRecordsetEx)
	long	m_PersonID;
	long	m_SeriesID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecurityPersonSeriesSet)
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

#endif // !defined(AFX_SECURITYPERSONSERIESSET_H__BC02AB61_AB19_11D3_839B_00400548A44F__INCLUDED_)
