#if !defined(AFX_SERIESSET_H__A6864F67_53E2_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_SERIESSET_H__A6864F67_53E2_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeriesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet recordset

class CSeriesSet : public CRecordsetEx
{
public:
	CSeriesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeriesSet)

// Field/Param Data
	//{{AFX_FIELD(CSeriesSet, CRecordsetEx)
	long	m_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_AgeCategory;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesSet)
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

#endif // !defined(AFX_SERIESSET_H__A6864F67_53E2_11D2_839B_00400548A44F__INCLUDED_)
