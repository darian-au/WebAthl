#if !defined(AFX_AGEGROUPRANKINGSET_H__INCLUDED_)
#define AFX_AGEGROUPRANKINGSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AgeGroupRankingSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAgeGroupRankingSet recordset

class CAgeGroupRankingSet : public CRecordsetEx
{
public:
	CAgeGroupRankingSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAgeGroupRankingSet)

// Field/Param Data
	//{{AFX_FIELD(CAgeGroupRankingSet, CRecordsetEx)
	long	m_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_AgeCategory;

	long	m_LocationID;
	CString	m_LocationDescription;

	long	m_EventTypeID;
	CString	m_EventDescription;
	long	m_Timed;
	double	m_EventLength;

	long	m_Results_SeriesID;
	long	m_Results_EventID;
	long	m_Results_PersonID;
	long	m_DivisionActual;
	long	m_AgeGroup;
	long	m_GroupIDActual;
	double	m_GroupStartActual;
	long	m_NewGroupID;
	CString	m_NewGroupMessage;
	long	m_GrossPerformanceHOUR;
	long	m_GrossPerformanceMIN;
	double	m_GrossPerformanceSEC;
	long	m_NetPerformanceHOUR;
	long	m_NetPerformanceMIN;
	double	m_NetPerformanceSEC;
	long	m_Place;
	long	m_OverallPlace;
	long	m_Percentile;
	long	m_Points;
	CString	m_Eligible;
	double	m_EventRate;
	double	m_GroupRateActual;
	CString	m_ChestNumber;
	double	m_WorldStandard;
	long	m_GroupIDSupposedTo;
	long	m_DivisionSupposedTo;
	long	m_OrgID;

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

	long	m_Event_SeriesID;
	long	m_EventNo;
	long	m_EventID;
	long	m_Event_LocationID;
	long	m_Event_EventTypeID;
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
	//{{AFX_VIRTUAL(CAgeGroupRankingSet)
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

#endif // !defined(AFX_AGEGROUPRANKINGSET_H__INCLUDED_)
