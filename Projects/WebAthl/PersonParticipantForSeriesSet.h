#if !defined(AFX_PERSONPARTICIPANTFORSERIESSET_H__6ED9FB61_268D_11D3_839B_00400548A44F__INCLUDED_)
#define AFX_PERSONPARTICIPANTFORSERIESSET_H__6ED9FB61_268D_11D3_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PersonParticipantForSeriesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonParticipantForSeriesSet recordset

class CPersonParticipantForSeriesSet : public CRecordsetEx
{
public:
	CPersonParticipantForSeriesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonParticipantForSeriesSet)

// Field/Param Data
	//{{AFX_FIELD(CPersonParticipantForSeriesSet, CRecordsetEx)
	long	m_SeriesID;
	long	m_PFS_PersonID;
	long	m_GroupIDSupposedTo;
	long	m_DivisionSupposedTo;
	long	m_ConsistencyAgeGroup;
	long	m_ConsistencyEventsCurrent;
	long	m_ConsistencyEventsOlder;
	double	m_ConsistencyEventsRate;
	long	m_EventsForSeason;
	long	m_GrossPoints;
	long	m_LowPoints;
	long	m_NetPoints;
	CString	m_EligibilityForEvent;
	long	m_OrgID;
	long	m_EventsForSeries;
	double	m_ConsistencyAgeStandard;

	long	m_PersonID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_MiddleName;
	long	m_dobDAY;
	long	m_dobMONTH;
	long	m_dobYEAR;
	CString	m_Sex;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_Town;
	CString	m_State;
	CString	m_Country;
	CString	m_PostCode;
	CString	m_PhoneHm;
	CString	m_PhoneWk;
	CString	m_Fax;
	CString	m_Mobile;
	CString	m_email;
	long	m_ContactPersonID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonParticipantForSeriesSet)
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

#endif // !defined(AFX_PERSONPARTICIPANTFORSERIESSET_H__6ED9FB61_268D_11D3_839B_00400548A44F__INCLUDED_)
