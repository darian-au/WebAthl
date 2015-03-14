#if !defined(AFX_CONSISTENCYAGEGROUPSET_H__INCLUDED_)
#define AFX_CONSISTENCYAGEGROUPSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConsistencyAgeGroupSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConsistencyAgeGroupSet recordset

class CConsistencyAgeGroupSet : public CRecordsetEx
{
public:
	CConsistencyAgeGroupSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CConsistencyAgeGroupSet)

// Field/Param Data
	//{{AFX_FIELD(CConsistencyAgeGroupSet, CRecordsetEx)
	long	m_PersonID;
	long	m_MinAgeGroup;
	long	m_MaxAgeGroup;
	long	m_EventsForSeason;
	long	m_EventsForSeries;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsistencyAgeGroupSet)
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

#endif // !defined(AFX_CONSISTENCYAGEGROUPSET_H__INCLUDED_)
