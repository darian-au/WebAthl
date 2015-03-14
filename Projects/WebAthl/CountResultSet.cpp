// CountResultSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "CountResultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountResultSet

IMPLEMENT_DYNAMIC(CCountResultSet, CRecordsetEx)

CCountResultSet::CCountResultSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CCountResultSet)
	m_Total = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CCountResultSet::GetDefaultConnect()
{
	return _T("");
}

CString CCountResultSet::GetDefaultSQL()
{
	return _T("");
}

void CCountResultSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCountResultSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Total]"), m_Total);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCountResultSet diagnostics

#ifdef _DEBUG
void CCountResultSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CCountResultSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
