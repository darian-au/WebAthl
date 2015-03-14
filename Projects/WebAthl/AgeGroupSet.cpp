// AgeGroupSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "AgeGroupSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgeGroupSet

IMPLEMENT_DYNAMIC(CAgeGroupSet, CRecordsetEx)

CAgeGroupSet::CAgeGroupSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CAgeGroupSet)
	m_SeriesID = 0;
	m_EventID = 0;
	m_PersonID = 0;
	m_AgeGroup = 0;
	m_DateDAY = 0;
	m_DateMONTH = 0;
	m_DateYEAR = 0;
	m_DateAgeDAY = 0;
	m_DateAgeMONTH = 0;
	m_DateAgeYEAR = 0;
	m_dobDAY = 0;
	m_dobMONTH = 0;
	m_dobYEAR = 0;

	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CAgeGroupSet::GetDefaultConnect()
{
	return _T("");
}

CString CAgeGroupSet::GetDefaultSQL()
{
	return _T("[Results],[Event],[Person]");
}

void CAgeGroupSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAgeGroupSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Results].[SeriesID]"), m_SeriesID);
	RFX_Long(pFX, _T("[Results].[EventID]"), m_EventID);
	RFX_Long(pFX, _T("[Results].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[Results].[AgeGroup]"), m_AgeGroup);

	RFX_Long(pFX, _T("[Event].[DateDAY]"), m_DateDAY);
	RFX_Long(pFX, _T("[Event].[DateMONTH]"), m_DateMONTH);
	RFX_Long(pFX, _T("[Event].[DateYEAR]"), m_DateYEAR);
	RFX_Long(pFX, _T("[Event].[DateAgeDAY]"), m_DateAgeDAY);
	RFX_Long(pFX, _T("[Event].[DateAgeMONTH]"), m_DateAgeMONTH);
	RFX_Long(pFX, _T("[Event].[DateAgeYEAR]"), m_DateAgeYEAR);

	RFX_Long(pFX, _T("[Person].[dobDAY]"), m_dobDAY);
	RFX_Long(pFX, _T("[Person].[dobMONTH]"), m_dobMONTH);
	RFX_Long(pFX, _T("[Person].[dobYEAR]"), m_dobYEAR);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAgeGroupSet diagnostics

#ifdef _DEBUG
void CAgeGroupSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CAgeGroupSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
