#if !defined(AFX_FORMAT_H__INCLUDED_)
#define AFX_FORMAT_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormat

class CFormat
{

	public:

		// Constructor
		//CFormat( );	

		// Destructor
		//~CFormat( );

		// Member functions

		// Static functions
		static CString FormatRegistration(int nYearValid, int nRegistrationTypeID, LPCTSTR szConnect);
		static CString FormatRegistration(int nYearValid, int nMonthStart, int nMonthStop, LPCTSTR szRegistrationDescription);
		static CString FormatName(LPCTSTR szLastName, LPCTSTR szFirstName, LPCTSTR szMiddleName);
		static CString FormatDate(int nDateDAY, int nDateMONTH, int nDateYEAR);
		static CString FormatPerf(int nTimed, int nPerfHOUR, int nPerfMIN, double dPerfSEC);
		static CString FormatPerf(int nTimed, LPCTSTR szPerfHOUR, LPCTSTR szPerfMIN, LPCTSTR szPerfSEC, LPCTSTR szPerfJumpThrow = NULL);
		//	Timed = 1 -> Long Distance
		//	Timed = 0 -> Jump or Throw
		//	Timed = 2 -> Sprint

		// Static variables

		// Member variables

	private:

		// Member variables
};

#endif // !defined(AFX_FORMAT_H__INCLUDED_)
