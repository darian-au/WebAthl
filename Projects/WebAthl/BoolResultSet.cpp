// BoolResultSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "BoolResultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoolResultSet

IMPLEMENT_DYNAMIC(CBoolResultSet, CRecordsetEx)

CBoolResultSet::CBoolResultSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CBoolResultSet)
	m_Result = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CBoolResultSet::GetDefaultConnect()
{
	return _T("");
}

CString CBoolResultSet::GetDefaultSQL()
{
	return _T("");
}

void CBoolResultSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBoolResultSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Result]"), m_Result);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBoolResultSet diagnostics

#ifdef _DEBUG
void CBoolResultSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CBoolResultSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
