#if !defined(AFX_PERSONSEARCHER_H__INCLUDED_)
#define AFX_PERSONSEARCHER_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPersonSearcher.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonSearcher

class CPersonSearcher
{

	public:

		// Constructor
		//CPersonSearcher( );	

		// Destructor
		//~CPersonSearcher( );

		// Member functions

		// Static functions
		static CString GetDefaultSQL(
			LPTSTR szPersonID,
			LPTSTR szLastName,
			LPTSTR szFirstName,
			LPTSTR szMiddleName,
			LPTSTR szAddress1,
			LPTSTR szAddress2,
			LPTSTR szTown,
			LPTSTR szState,
			LPTSTR szCountry,
			LPTSTR szPostCode,
			LPTSTR szPhoneHm,
			LPTSTR szPhoneWk,
			LPTSTR szFax,
			LPTSTR szMobile,
			LPTSTR szEmail,
			LPTSTR szDobDAY,
			LPTSTR szDobMONTH,
			LPTSTR szDobYEAR,
			LPTSTR szSex,
			LPTSTR szContactPersonID);

		static BOOL IsSearchValid(
			CHtmlWriter* pHtml, 
			CHttpServerProperties* pProp,
			LPTSTR szPersonID,
			LPTSTR szLastName,
			LPTSTR szFirstName,
			LPTSTR szMiddleName,
			LPTSTR szDobDAY,
			LPTSTR szDobMONTH,
			LPTSTR szDobYEAR,
			LPTSTR szSex);

		// Member variables

		// Static variables

	protected:

		// Member variables
};

#endif // !defined(AFX_PERSONSEARCHER_H__INCLUDED_)
