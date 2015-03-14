#if !defined(AFX_HTTPSERVERPROPERTIES_H__INCLUDED_)
#define AFX_HTTPSERVERPROPERTIES_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HttpServerProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHttpServerProperties

class CHttpServerProperties : public CProperties
{

	public:

		// Constructor
		CHttpServerProperties( 
			CHttpServerVariable* pSrvVar, 
			LPCTSTR szCompany = CHttpServerProperties::m_szDefaultCompany, 
			LPCTSTR szProgram = CHttpServerProperties::m_szDefaultProgram );

		// Destructor
		//~CHttpServerProperties( );

		// Member functions
		virtual CString Get( LPCTSTR szSection, LPCTSTR szKey );
		virtual CString GetEx(LPCTSTR szSection, LPCTSTR szKey );

		virtual BOOL SetEx( );

		BOOL CanSet( );

		BOOL IsEmpty( LPCTSTR szValue );
		BOOL IsEmpty( LPCTSTR szSection, LPCTSTR szKey );

		CString GetDefaultConnect( );

		BOOL SetDefaultConnect( LPCTSTR szServer,
								LPCTSTR szUID,
								LPCTSTR szPWD,
								LPCTSTR szDatabase,
								LPCTSTR szDriver,
								LPCTSTR szDSN );

		BOOL IsLicensed(LPTSTR szKeyMsg = NULL);
		int GetLicense( LPTSTR szKeyMsg = NULL );
		int SetLicense( LPCTSTR szRegNo, 
						LPCTSTR szRegName, 
						LPCTSTR szKey, 
						LPTSTR szKeyMsg = NULL );


		// Static functions

		// Static variables
		static LPCTSTR m_szDefaultCompany;
		static LPCTSTR m_szDefaultProgram;
		static LPCTSTR m_szEmptyValue;


	private:

		// Member variables
		CHttpServerVariable* m_pSrvVar;
};

#endif // !defined(AFX_HTTPSERVERPROPERTIES_H__INCLUDED_)
