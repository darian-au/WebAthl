// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"


///////////////////////////////////////////////////////////////////////////////////////
// License

void CWebAthlExtension::LicenseForm(CHttpServerContext* pCtxt, LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Security) )
	{
		auth.m_strHeading = "License";

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Cancel", 0);

		html.EndMenu();

		html << _T("Please enter your License details <B>Exactly</B> as they were provided to you.\r\n");

		html.StartForm("License", CPage::LicenseExecute);

		html.EditTextBoxLarge("License No","RegNo", "");
		html.EditTextBoxLarge("License Name","RegName", "");
		html.EditTextBoxLarge("License Key","RegKey", "");
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}
 
void CWebAthlExtension::LicenseExecute(CHttpServerContext* pCtxt,
									   LPTSTR szRegNo,
									   LPTSTR szRegName,
									   LPTSTR szRegKey,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Security) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.EndMenu();


		TCHAR szKeyMsg[4000];
		prop.SetLicense( szRegNo, szRegName, szRegKey, szKeyMsg );

		html << _T(szKeyMsg) << _T("<BR><BR>\r\n") ; 

		html << _T("License No : <B>") << _T(szRegNo) << _T("</B><BR>\r\n") ; 
		html << _T("License Name : <B>") << _T(szRegName) << _T("</B><BR>\r\n") ; 
		html << _T("License Key : <B>") << _T(szRegKey) << _T("</B><BR>\r\n") ; 


		html.EndPage();
		html.EndContent();
	}
}

