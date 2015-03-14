// DoubleSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "DoubleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoubleSet

IMPLEMENT_DYNAMIC(CDoubleSet, CRecordsetEx)

CDoubleSet::CDoubleSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CDoubleSet)
	m_Val = 0.0f;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CDoubleSet::GetDefaultConnect()
{
	return _T("");
}

CString CDoubleSet::GetDefaultSQL()
{
	return _T("");
}

void CDoubleSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDoubleSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[Val]"), m_Val);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDoubleSet diagnostics

#ifdef _DEBUG
void CDoubleSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CDoubleSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
