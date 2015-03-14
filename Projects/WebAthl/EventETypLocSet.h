#if !defined(AFX_EVENTETYPLOCSET_H__1678B6CA_5AC6_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_EVENTETYPLOCSET_H__1678B6CA_5AC6_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EventETypLocSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventETypLocSet recordset

class CEventETypLocSet : public CRecordsetEx
{
public:
	CEventETypLocSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEventETypLocSet)

// Field/Param Data
	//{{AFX_FIELD(CEventETypLocSet, CRecordsetEx)
	long	m_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_AgeCategory;

	long	m_Event_SeriesID;
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

	long	m_EventType_EventTypeID;
	CString	m_EventDescription;
	long	m_Timed;
	double	m_EventLength;

	long	m_Location_LocationID;
	CString	m_LocationDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventETypLocSet)
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

#endif // !defined(AFX_EVENTETYPLOCSET_H__1678B6CA_5AC6_11D2_839B_00400548A44F__INCLUDED_)
