#if !defined(AFX_CSTRINGLINE_H__INCLUDED_)
#define AFX_CSTRINGLINE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StringLine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStringLine

class CStringLine 
{
	public:

		// Constructor
		CStringLine(LPCTSTR sz, LPCTSTR szRowTerminator = "\r\n" );

		// Destructor
		//~CStringLine();

		// Member functions
		BOOL GetLine(CString& strLine);

		long GetRecordCount() const;
		void SetRecordCount();

		LPCTSTR GetRowTerminator();

	private:

		// Member variables
		long m_nRecordCount;
		LPCTSTR m_szRowTerminator;

		CString m_str;
};

#endif // !defined(AFX_CSTRINGLINE_H__INCLUDED_)
