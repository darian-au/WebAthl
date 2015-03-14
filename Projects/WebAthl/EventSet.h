#if !defined(AFX_EVENTSET_H__664046E3_5AB3_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_EVENTSET_H__664046E3_5AB3_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EventSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventSet recordset

class CEventSet : public CRecordsetEx
{
public:
	CEventSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventSet)

// Field/Param Data
	//{{AFX_FIELD(CEventSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_EventNo;
	long	m_EventID;
	long	m_LocationID;
	long	m_EventTypeID;
	long	m_DateDAY;
	long	m_DateMONTH;
	long	m_DateYEAR;
	long	m_PreEntryOpen;
	long	m_DateAgeDAY;
	long	m_DateAgeMONTH;
	long	m_DateAgeYEAR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventSet)
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

#endif // !defined(AFX_EVENTSET_H__664046E3_5AB3_11D2_839B_00400548A44F__INCLUDED_)
