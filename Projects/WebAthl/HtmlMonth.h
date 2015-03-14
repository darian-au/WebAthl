#if !defined(AFX_HTMLMONTH_H__INCLUDED_)
#define AFX_HTMLMONTH_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CHtmlMonth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlMonth

class CHtmlMonth
{

	public:

		// Constructor
		CHtmlMonth( );	
		CHtmlMonth( int nMonth );	

		// Destructor
		//~CHtmlMonth( );

		// Member functions
		virtual void Empty( );
		virtual void Select( int nMonth );

		// Static functions
		static CString GetName(int nMonth);

		// Static variables
		static LPCTSTR m_szSelected;

		// Member variables
		CString m_strJan;
		CString m_strFeb;
		CString m_strMar;
		CString m_strApr;
		CString m_strMay;
		CString m_strJun;
		CString m_strJul;
		CString m_strAug;
		CString m_strSep;
		CString m_strOct;
		CString m_strNov;
		CString m_strDec;

	private:

		// Member variables
};

#endif // !defined(AFX_HTMLMONTH_H__INCLUDED_)
