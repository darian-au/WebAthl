#if !defined(AFX_SERIESPERSONPFSORGSET_H__INCLUDED_)
#define AFX_SERIESPERSONPFSORGSET_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesPersonPFSOrgSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeriesPersonPFSSet recordset

class CSeriesPersonPFSOrgSet : public CRecordsetEx
{
public:
	CSeriesPersonPFSOrgSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeriesPersonPFSOrgSet)

// Field/Param Data
	//{{AFX_FIELD(CSeriesPersonPFSOrgSet, CRecordsetEx)
	long	m_Series_SeriesID;
	CString	m_SeriesDescription;
//	BOOL	m_Handicapped;
//	CString	m_AgeCategory;

	long	m_Person_PersonID;
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

	long	m_ParticipantForSeries_SeriesID;
	long	m_ParticipantForSeries_PersonID;
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
	long	m_ParticipantForSeries_OrgID;
	long	m_EventsForSeries;
	double	m_ConsistencyAgeStandard;

	long	m_Org_OrgID;
	CString	m_OrgName;
	CString	m_Org_Address1;
	CString	m_Org_Address2;
	CString	m_Org_Town;
	CString	m_Org_State;
	CString	m_Org_Country;
	CString	m_Org_PostCode;
	CString	m_Org_Phone;
	CString	m_Org_Fax;
	CString	m_Org_Mobile;
	CString	m_Org_email;
	CString	m_URL;
	long	m_RegistrarPersonID;
	long	m_AdministratorPersonID;

	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesPersonPFSOrgSet)
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

#endif // !defined(AFX_SERIESPERSONPFSORGSET_H__INCLUDED_)
