#if !defined(AFX_RESULTSORGSET_H__FE95CBC1_1323_11D4_982D_00400548A44F__INCLUDED_)
#define AFX_RESULTSORGSET_H__FE95CBC1_1323_11D4_982D_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultsOrgSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultsOrgSet recordset

class CResultsOrgSet : public CRecordsetEx
{
public:
	CResultsOrgSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CResultsOrgSet)

// Field/Param Data
	//{{AFX_FIELD(CResultsOrgSet, CRecordsetEx)
	long	m_Event_SeriesID;
	long	m_EventNo;
	long	m_Event_EventID;
	long	m_Event_LocationID;
	long	m_Event_EventTypeID;
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

	long	m_Groups_SeriesID;
	long	m_Groups_EventTypeID;
	long	m_GroupID;
	double	m_GroupRate;
	double	m_GroupStart;

	long	m_Location_LocationID;
	CString	m_LocationDescription;

	long	m_Organisation_OrgID;
	CString	m_OrgName;
	CString	m_Organisation_Address1;
	CString	m_Organisation_Address2;
	CString	m_Organisation_Town;
	CString	m_Organisation_State;
	CString	m_Organisation_Country;
	CString	m_Organisation_PostCode;
	CString	m_Phone;
	CString	m_Organisation_Fax;
	CString	m_Organisation_Mobile;
	CString	m_Organisation_email;
	CString	m_URL;
	long	m_RegistrarPersonID;
	long	m_AdministratorPersonID;

	long	m_Person_PersonID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_MiddleName;
	long	m_dobDAY;
	long	m_dobMONTH;
	long	m_dobYEAR;
	CString	m_Sex;
	CString	m_Person_Address1;
	CString	m_Person_Address2;
	CString	m_Person_Town;
	CString	m_Person_State;
	CString	m_Person_Country;
	CString	m_Person_PostCode;
	CString	m_PhoneHm;
	CString	m_PhoneWk;
	CString	m_Person_Fax;
	CString	m_Person_Mobile;
	CString	m_Person_email;
	long	m_ContactPersonID;

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
	long	m_Results_OrgID;

	long	m_Series_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_AgeCategory;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsOrgSet)
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

#endif // !defined(AFX_RESULTSORGSET_H__FE95CBC1_1323_11D4_982D_00400548A44F__INCLUDED_)
