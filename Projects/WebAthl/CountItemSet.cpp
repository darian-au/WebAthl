// CountItemSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "CountItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountItemSet

IMPLEMENT_DYNAMIC(CCountItemSet, CRecordsetEx)

CCountItemSet::CCountItemSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CCountItemSet)
	m_Total = 0;
	m_Details = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CCountItemSet::GetDefaultConnect()
{
	return _T("");
}

CString CCountItemSet::GetDefaultSQL()
{
	return _T("");
}

void CCountItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCountItemSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Total]"), m_Total);
	RFX_Text(pFX, _T("[Details]"), m_Details);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCountItemSet diagnostics

#ifdef _DEBUG
void CCountItemSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CCountItemSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
