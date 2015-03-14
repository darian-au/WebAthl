#if !defined(AFX_SERIESSTATISTICSSET_H__INCLUDED_)
#define AFX_SERIESSTATISTICSSET_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeriesStatisticsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeriesStatisticsSet recordset

class CSeriesStatisticsSet : public CRecordsetEx
{
public:
	CSeriesStatisticsSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeriesStatisticsSet)

// Field/Param Data
	//{{AFX_FIELD(CSeriesStatisticsSet, CRecordsetEx)
	long	m_AgeGroup;
	long	m_Total;
	CString	m_Sex;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesStatisticsSet)
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
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESSTATISTICSSET_H__INCLUDED_)
