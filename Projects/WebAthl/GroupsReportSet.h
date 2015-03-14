#if !defined(AFX_GROUPSREPORTSET_H__FC5BAB81_2176_11D3_839B_00400548A44F__INCLUDED_)
#define AFX_GROUPSREPORTSET_H__FC5BAB81_2176_11D3_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GroupsReportSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupsReportSet recordset

class CGroupsReportSet : public CRecordsetEx
{
public:
	CGroupsReportSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGroupsReportSet)

// Field/Param Data
	//{{AFX_FIELD(CGroupsReportSet, CRecordsetEx)
	long	m_PFS_SeriesID;
	long	m_PFS_PersonID;
	long	m_PFS_GroupIDSupposedTo;
	long	m_PFS_DivisionSupposedTo;
	long	m_PFS_ConsistencyAgeGroup;
	long	m_PFS_ConsistencyEventsCurrent;
	long	m_PFS_ConsistencyEventsOlder;
	double	m_PFS_ConsistencyEventsRate;
	long	m_PFS_EventsForSeason;
	long	m_PFS_GrossPoints;
	long	m_PFS_LowPoints;
	long	m_PFS_NetPoints;
	CString	m_PFS_EligibilityForEvent;
	long	m_PFS_OrgID;
	long	m_PFS_EventsForSeries;
	double	m_PFS_ConsistencyAgeStandard;

	long	m_Person_PersonID;
	CString	m_Person_LastName;
	CString	m_Person_FirstName;
	CString	m_Person_MiddleName;
	long	m_Person_dobDAY;
	long	m_Person_dobMONTH;
	long	m_Person_dobYEAR;
	CString	m_Person_Sex;
	CString	m_Person_Address1;
	CString	m_Person_Address2;
	CString	m_Person_Town;
	CString	m_Person_State;
	CString	m_Person_Country;
	CString	m_Person_PostCode;
	CString	m_Person_PhoneHm;
	CString	m_Person_PhoneWk;
	CString	m_Person_Fax;
	CString	m_Person_Mobile;
	CString	m_Person_email;
	long	m_Person_ContactPersonID;

	long	m_Groups_SeriesID;
	long	m_Groups_EventTypeID;
	long	m_Groups_GroupID;
	double	m_Groups_GroupRate;
	double	m_Groups_GroupStart;

	long	m_Series_SeriesID;
	CString	m_Series_SeriesDescription;
//	BOOL	m_Series_Handicapped;
//	CString	m_Series_AgeCategory;

	long	m_Event_SeriesID;
	long	m_Event_EventNo;
	long	m_Event_EventID;
	long	m_Event_LocationID;
	long	m_Event_EventTypeID;
	long	m_Event_DateDAY;
	long	m_Event_DateMONTH;
	long	m_Event_DateYEAR;
	long	m_Event_PreEntryOpen;
	long	m_Event_DateAgeDAY;
	long	m_Event_DateAgeMONTH;
	long	m_Event_DateAgeYEAR;

	long	m_EventType_EventTypeID;
	CString	m_EventType_EventDescription;
	long	m_EventType_Timed;
	double	m_EventType_EventLength;

	long	m_Location_LocationID;
	CString	m_Location_LocationDescription;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupsReportSet)
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

#endif // !defined(AFX_GROUPSREPORTSET_H__FC5BAB81_2176_11D3_839B_00400548A44F__INCLUDED_)
