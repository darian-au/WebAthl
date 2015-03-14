#if !defined(AFX_CLUBRECORDSSET_H__F431FAC1_6CF1_11D2_839B_00400548A44F__INCLUDED_)
#define AFX_CLUBRECORDSSET_H__F431FAC1_6CF1_11D2_839B_00400548A44F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClubRecordsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClubRecordsSet recordset

class CClubRecordsSet : public CRecordsetEx
{
public:
	CClubRecordsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClubRecordsSet)

// Field/Param Data
	//{{AFX_FIELD(CClubRecordsSet, CRecordsetEx)

	long	m_SeriesID;
	long	m_LocationID;
	long	m_EventID;
	long	m_EventTypeID;
	CString	m_Sex;
	long	m_AgeGroup;
	CString	m_AgeCategory;
	long	m_PersonID;
	long	m_ClubPerformanceHOUR;
	long	m_ClubPerformanceMIN;
	double	m_ClubPerformanceSEC;

	long	m_Series_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_Series_AgeCategory;

	long	m_Location_LocationID;
	CString	m_LocationDescription;

	long	m_EventType_EventTypeID;
	CString	m_EventDescription;
	long	m_Timed;
	double	m_EventLength;

	long	m_Person_PersonID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_MiddleName;
	long	m_dobDAY;
	long	m_dobMONTH;
	long	m_dobYEAR;
	CString	m_Person_Sex;
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

  //}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClubRecordsSet)
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

#endif // !defined(AFX_CLUBRECORDSSET_H__F431FAC1_6CF1_11D2_839B_00400548A44F__INCLUDED_)
