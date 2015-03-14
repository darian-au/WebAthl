// DupPersonSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "DupPersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDupPersonSet

IMPLEMENT_DYNAMIC(CDupPersonSet, CRecordsetEx)

CDupPersonSet::CDupPersonSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CDupPersonSet)
	m_PersonID = 0;
	m_Val = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CDupPersonSet::GetDefaultConnect()
{
	return _T("");
}

CString CDupPersonSet::GetDefaultSQL()
{
	return _T("");
}

void CDupPersonSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDupPersonSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[Val]"), m_Val);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDupPersonSet diagnostics

#ifdef _DEBUG
void CDupPersonSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CDupPersonSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
