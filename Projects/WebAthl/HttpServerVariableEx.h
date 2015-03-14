#if !defined(AFX_HTTPSERVERVARIABLEEX_H__INCLUDED_)
#define AFX_HTTPSERVERVARIABLEEX_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HttpServerVariableEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHttpServerVariableEx

class CHttpServerVariableEx : public CHttpServerVariable
{

	public:

		// Constructor
		CHttpServerVariableEx( 
			CHttpServerContext* pCtxt , 
			CHttpServer* pSrv , 
			DWORD dwLen = 10240 );	// Expected length of 
									// all Server Variables combined

		// Destructor
		//~CHttpServerVariableEx( );

		// Member functions
		virtual void AddHeader( LPCTSTR pszString ) const;
		virtual void EndContent( ) const;

		virtual void SetCookie(LPCTSTR szCookieName, LPCTSTR szCookieValue );
		virtual void SetContent(LPCTSTR szContentType = CHttpServerVariableEx::m_szDefaultContentType );
		virtual void EndHeader();

		// Static functions

		// Static variables
		static LPCTSTR m_szDefaultContentType;

	private:

		// Member variables
		CHttpServer* m_pSrv;
};

#endif // !defined(AFX_HTTPSERVERVARIABLEEX_H__INCLUDED_)
