#if !defined(AFX_REGISTRY_H__INCLUDED_)
#define AFX_REGISTRY_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Registry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegistry

class CRegistry
{

	public:

		// Constructor
		CRegistry( LPCTSTR szCompany, LPCTSTR szProgram, LPCTSTR szProfile, DWORD dwLen = 255 );

		// Destructor
		//~CRegistry( );

		// Member functions
		virtual LONG Get(LPCTSTR szSection, LPCTSTR szKey, CString* strValue);
		LONG Set(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue);

		virtual LONG GetComputerName(CString* strValue);
		virtual LONG GetWinZipLocation(CString* strValue);

		// Static functions

	protected:

		// Constructor
		CRegistry( LPCTSTR szCompany, LPCTSTR szProgram, DWORD dwLen = 255 );

		// Member functions
		void SetProfile( LPCTSTR szProfile );

	private:

		// Member variables
		CString m_strCompany;
		CString m_strProgram;
		CString m_strProfile;
		DWORD m_dwLen;	
};

#endif // !defined(AFX_REGISTRY_H__INCLUDED_)
