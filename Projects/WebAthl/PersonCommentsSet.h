#if !defined(AFX_PERSONCOMMENTSSET_H__85EEE761_FCD0_11D3_982D_00400548A44F__INCLUDED_)
#define AFX_PERSONCOMMENTSSET_H__85EEE761_FCD0_11D3_982D_00400548A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonCommentsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonCommentsSet recordset

class CPersonCommentsSet : public CRecordsetEx
{
public:
	CPersonCommentsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonCommentsSet)

// Field/Param Data
	//{{AFX_FIELD(CPersonCommentsSet, CRecordsetEx)
	long	m_PersonID;
	long	m_CommentNo;
	CString	m_Comment;
	CString	m_Type;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonCommentsSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONCOMMENTSSET_H__85EEE761_FCD0_11D3_982D_00400548A44F__INCLUDED_)
