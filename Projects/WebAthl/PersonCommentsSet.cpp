// PersonCommentsSet.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"

#include "PersonCommentsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonCommentsSet

IMPLEMENT_DYNAMIC(CPersonCommentsSet, CRecordsetEx)

CPersonCommentsSet::CPersonCommentsSet(CDatabase* pdb)
	: CRecordsetEx(pdb)
{
	//{{AFX_FIELD_INIT(CPersonCommentsSet)
	m_PersonID = 0;
	m_CommentNo = 0;
	m_Type = _T("");
	m_Comment = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPersonCommentsSet::GetDefaultConnect()
{
	return _T("");
}

CString CPersonCommentsSet::GetDefaultSQL()
{
	return _T("[PersonComments]");
}

void CPersonCommentsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonCommentsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PersonComments].[PersonID]"), m_PersonID);
	RFX_Long(pFX, _T("[PersonComments].[CommentNo]"), m_CommentNo);
	RFX_Text(pFX, _T("[PersonComments].[Type]"), m_Type);
	RFX_Text(pFX, _T("[PersonComments].[Comment]"), m_Comment);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPersonCommentsSet diagnostics

#ifdef _DEBUG
void CPersonCommentsSet::AssertValid() const
{
	CRecordsetEx::AssertValid();
}

void CPersonCommentsSet::Dump(CDumpContext& dc) const
{
	CRecordsetEx::Dump(dc);
}
#endif //_DEBUG
