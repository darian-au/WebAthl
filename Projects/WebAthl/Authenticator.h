#if !defined(AFX_AUTHENTICATOR_H__INCLUDED_)
#define AFX_AUTHENTICATOR_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CAuthenticator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuthenticator

class CAuthenticator
{

	public:

		// Constructor
		CAuthenticator( CHtmlWriter* pHtml );	

		// Destructor
		//~CAuthenticator( );

		// Member functions
		void AccessDeniedPage();

		void GetCookies();
		int ValidateLogin(LPCTSTR szLoginName, LPCTSTR szHexPwd);

		BOOL CheckPermission(DWORD dwModules);

		BOOL HasPermission(DWORD dwModules);

		// Static functions

		// Static variables
		static int m_iDboRoleId;
		static LPCTSTR m_szDboName;

		static LPCTSTR m_szGuestUser;
		static LPCTSTR m_szMemberRole;

		static int m_iMinPwdLen;

		// Member variables
		CString m_strHeading;
		CString m_strOrgName;
		CString m_strUserName;
		CString m_strLoginName;
		CString m_strRoleName;

		CString m_strBackLink;
		CString m_strFrwdLink;

		int m_iRoleID;
		int m_iPersonID;
		int m_iPermission;

		CString m_strError;

	private:

		// Member functions

		// Member variables
		CHtmlWriter* m_pHtml;

};

#endif // !defined(AFX_AUTHENTICATOR_H__INCLUDED_)
