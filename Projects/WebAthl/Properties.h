#if !defined(AFX_PROPERTIES_H__INCLUDED_)
#define AFX_PROPERTIES_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Properties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProperties

class CProperties : public CRegistry
{

	public:

		// Constructor
		CProperties( LPCTSTR szCompany, LPCTSTR szProgram, LPCTSTR szProfile );

		// Destructor
		//~CProperties( );

		// Member functions
		virtual CString Get(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue = "");

		virtual CString GetComputerName();
		virtual CString GetWinZipLocation();

		// Static functions

	protected:

		// Constructor
		CProperties( LPCTSTR szCompany, LPCTSTR szProgram );

	private:

		// Member variables
};

#endif // !defined(AFX_PROPERTIES_H__INCLUDED_)
