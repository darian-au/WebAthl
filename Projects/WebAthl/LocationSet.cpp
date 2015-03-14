// LocationSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "LocationSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocationSet

IMPLEMENT_DYNAMIC(CLocationSet, CRecordsetEx)

CLocationSet::CLocationSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CLocationSet)
	m_LocationID = 0;
	m_LocationDescription = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;

	m_strIdentityColumn = _T("LocationID");
	m_nIdentityColumn = &m_LocationID;
}


CString CLocationSet::GetDefaultConnect()
{
	return _T("");
}

CString CLocationSet::GetDefaultSQL()
{
	return _T("[Location]");
}

void CLocationSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLocationSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Location].[LocationID]"), m_LocationID);
	RFX_Text(pFX, _T("[Location].[LocationDescription]"), m_LocationDescription);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLocationSet diagnostics

#ifdef _DEBUG
void CLocationSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CLocationSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
