#if !defined(AFX_HTTPSERVERVARIABLE_H__INCLUDED_)
#define AFX_HTTPSERVERVARIABLE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HttpServerVariable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHttpServerVariable

class CHttpServerVariable
{

	public:

		// Constructor
		CHttpServerVariable( 
			CHttpServerContext* pCtxt , 
			DWORD dwLen = 10240 );	// Expected length of 
									// all Server Variables combined

		// Destructor
		//~CHttpServerVariable( );

		// Member functions
		virtual void PrintServerVariables();
		virtual CString GetVariable(LPCTSTR szVarName);
		virtual CString GetVariableEx(LPCTSTR szVarName);
		virtual CString GetCookie(LPCTSTR szCookieName);

		virtual CString MakeStringSetCookie(LPCTSTR szCookieName, LPCTSTR szCookieValue);
		virtual CString MakeStringSetContent(LPCTSTR szContentType);
		virtual CString MakeStringEndHeader();

		virtual CString GetFileName();
		virtual CString GetPathName();

		// CHtmlStream::operator <<
		// CHttpServerContext::operator <<
		CHttpServerContext& operator<<( LPCTSTR psz );
		CHttpServerContext& operator<<( long int dw );
		CHttpServerContext& operator<<( short int w );
		CHttpServerContext& operator<<( const CHtmlStream& stream );
		CHttpServerContext& operator<<( double d );
		CHttpServerContext& operator<<( float f );
		CHttpServerContext& operator<<( const CLongBinary& blob );
		CHttpServerContext& operator<<( const CByteArray& array );

		CHttpServerContext& operator<<( CDBException* pEx );
		CHttpServerContext& operator<<( CFileException* pEx );
		CHttpServerContext& operator<<( CException* pEx );
		// Static functions

	protected:

		// Member variables
		CHttpServerContext* m_pCtxt;

	private:

		// Member variables
		DWORD m_dwLen;
};

#endif // !defined(AFX_HTTPSERVERVARIABLE_H__INCLUDED_)
