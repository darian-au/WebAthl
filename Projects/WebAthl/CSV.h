#if !defined(AFX_CCSV_H__INCLUDED_)
#define AFX_CCSV_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSV.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSV

class CCSV 
{
	public:

		// Constructor
		CCSV(LPCTSTR szFieldTerminator = ",",
			 LPCTSTR szQuotedIdentifier = NULL );

		CCSV(TCHAR chFieldTerminator);

		// Destructor
		//~CCSV();

		// Member functions
		void Init(CString szFieldTerminator,
			 LPCTSTR szQuotedIdentifier );

		CStringArray* GetItems(CStringArray* strItems, CString* strLine);
		CString* GetCSVRow(CStringArray* strItems, CString* strRow = new CString() );

		static CString FormatHtmlItems(CStringArray* strItems, bool bHeading = false);

		long GetRecordCount(bool bSuccessCount = false) const;
		void SetRecordCount(bool bDecrement = false);

		LPCTSTR GetFieldTerminator();
		LPCTSTR GetQuotedIdentifier();
		CString GetDoubleQuotedIdentifier();

		static DWORD GetBitMask(CString strDWordLine, TCHAR chFieldTerminator);

	private:

		// Member variables
		long m_nRecordCount;
		long m_nSuccessRecordCount;

		//LPCTSTR m_szFieldTerminator;
		LPCTSTR m_szQuotedIdentifier;

		CString m_strFieldTerminator;
		CString m_strQuotedIdentifier;

		char	m_ch; 

		LPCTSTR m_szSpecial;

		CString m_strDoubleQuotedIdentifier;
		CString m_strTripleQuotedIdentifier;
	
		CString m_strFirstTripleQuotedIdentifier;
		CString m_strFirstTripleSpecial;

		CString m_strFirstQuotedIdentifier;
};

#endif // !defined(AFX_CCSV_H__INCLUDED_)
