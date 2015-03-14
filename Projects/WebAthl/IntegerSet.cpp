// IntegerSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "IntegerSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntegerSet

IMPLEMENT_DYNAMIC(CIntegerSet, CRecordsetEx)

CIntegerSet::CIntegerSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CIntegerSet)
	m_Val = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CIntegerSet::GetDefaultConnect()
{
	return _T("");
}

CString CIntegerSet::GetDefaultSQL()
{
	return _T("");
}

void CIntegerSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CIntegerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Val]"), m_Val);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CIntegerSet diagnostics

#ifdef _DEBUG
void CIntegerSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CIntegerSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
