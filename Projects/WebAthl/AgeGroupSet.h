#if !defined(AFX_AGEGROUPSET_H__INCLUDED_)
#define AFX_AGEGROUPSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AgeGroupSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAgeGroupSet recordset

class CAgeGroupSet : public CRecordsetEx
{
public:
	CAgeGroupSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAgeGroupSet)

// Field/Param Data
	//{{AFX_FIELD(CAgeGroupSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventID;
	long	m_PersonID;
	long	m_AgeGroup;
	long	m_DateDAY;
	long	m_DateMONTH;
	long	m_DateYEAR;
	long	m_DateAgeDAY;
	long	m_DateAgeMONTH;
	long	m_DateAgeYEAR;
	long	m_dobDAY;
	long	m_dobMONTH;
	long	m_dobYEAR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgeGroupSet)
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

#endif // !defined(AFX_AGEGROUPSET_H__INCLUDED_)
