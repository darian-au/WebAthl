// StringSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "StringSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringSet

IMPLEMENT_DYNAMIC(CStringSet, CRecordsetEx)

CStringSet::CStringSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CStringSet)
	m_Val = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CStringSet::GetDefaultConnect()
{
	return _T("");
}

CString CStringSet::GetDefaultSQL()
{
	return _T("");
}

void CStringSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStringSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Val]"), m_Val);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStringSet diagnostics

#ifdef _DEBUG
void CStringSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CStringSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
