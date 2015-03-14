#if !defined(AFX_CBULKCOPY_H__INCLUDED_)
#define AFX_CBULKCOPY_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CBulkCopy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBulkCopy

class CBulkCopy 
{
	public:

	// Constructor
	CBulkCopy(
		CStringStream* strLog,
		CStringStream* strErr,
		LPCTSTR szUsername,
		LPCTSTR szPassword,
		bool bTrustedConnection,
		LPCTSTR szDSN,
		LPCTSTR szServer,
		LPCTSTR szDatabase,
		LPCTSTR szDriver,
		bool bFirstRowIsColumnNames,
		bool bHtml,
		LPCTSTR szQuotedIdentifier,
		LPCTSTR szFieldTerminator,
		//LPCTSTR szRowTerminator,
		LPCTSTR szOutputFileName,
		LPCTSTR szInputFileName,
		LPCTSTR szQueryString,
		int dRowCountMark,
		bool bRowCountMark,
		LPCTSTR szConfigSQL);

	// Destructor
	//~CBulkCopy();

	// Member functions
	long FileCopy();
	long DatabaseCopyOut();
	long DatabaseCopyIn();

	long GetSuccessRecordCount();
	long GetFailRecordCount();

	void PrintStatistics();

	// Member variables

	CStringStream* m_strLog;
	CStringStream* m_strErr;

	private:

	// Member variables

	clock_t m_timeStart;
	clock_t m_timeStop;
	long m_dSuccessRecordCount;
	long m_dFailRecordCount;

	LPCTSTR m_szUsername;
	LPCTSTR m_szPassword;

	bool m_bTrustedConnection;

	LPCTSTR m_szDSN;

	LPCTSTR m_szServer;
	LPCTSTR m_szDatabase;
	LPCTSTR m_szDriver;

	bool m_bFirstRowIsColumnNames;

	bool m_bHtml;

	LPCTSTR m_szQuotedIdentifier;

	LPCTSTR m_szFieldTerminator;
	//LPCTSTR m_szRowTerminator;

	LPCTSTR m_szOutputFileName;
	LPCTSTR m_szInputFileName;

	LPCTSTR m_szQueryString;

	int m_dRowCountMark;
	bool m_bRowCountMark;

	LPCTSTR m_szConfigSQL;
};

#endif // !defined(AFX_CBULKCOPY_H__INCLUDED_)
