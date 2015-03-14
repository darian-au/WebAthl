// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "OrganisationSet.h"
#include "PersonSet.h"
#include "CountResultSet.h"
#include "SecurityPersonSet.h"

#define UNKNOWN_ORG "[Unknown Organisation]"

///////////////////////////////////////////////////////////////////////////////////////		int j;
// Dump Page

void CWebAthlExtension::Dump(CHttpServerContext* pCtxt)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );

    html.SetContent();
    html.EndHeader();

	html.WritePageTitle();

	html << _T("<body>\r\n");
	html << _T("<h1>Server Variables</h1>\r\n");
	html << _T("<hr>\r\n");

	html.PrintServerVariables();

	html.EndContent( );
}

///////////////////////////////////////////////////////////////////////////////////////		int j;
// Default

void CWebAthlExtension::Default(CHttpServerContext* pCtxt,
								LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );

	CString strConnect = prop.GetDefaultConnect( );

	CString strError;
	BOOL nStatus = CRecordsetEx::TestConnect(strConnect, &strError);

    html.SetContent();
	html.SetCookie(CHtmlKey::LoginName, CAuthenticator::m_szGuestUser);
	html.SetCookie(CHtmlKey::Password, "");
    html.EndHeader();

	html.WritePageTitle();

	if( !nStatus )
	{
		if( prop.CanSet( ) )
		{
			html.DefaultPage("Setup", CPage::DefaultODBCSetupForm);
			html << _T("Database Error : ") << _T(strError) << _T("<BR>\r\n");
		}
		else
		{
			html.DefaultPage("Setup", CPage::Default);
			html << _T("Database Error : ") << _T(strError) << _T("<BR>\r\n") << _T("<BR>\r\n");;
			html << _T("<B>WARNING</B>: This Web Server does not have sufficient privileges to modify the System Registry.") << _T("<BR>\r\n");;
			html << _T("Please configure the Web Server to have these privileges before attempting to configure the Database settings (as settings are stored in the Registry).") << _T("<BR>\r\n");
		}
	}
	else
	{
		html.DefaultPage("Start", CPage::DefaultEntry);
	}


	html.EndContent( );
}

///////////////////////////////////////////////////////////////////////////////////////	
// Setup

void CWebAthlExtension::DefaultODBCSetupForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );

	CString strLink = html.GetFileName( );
	CString strDefaultPage;

	CString strBuildNo;
	CString strBuildDate;
	CString strReleaseNo;


	CString strConnect = prop.GetDefaultConnect( );

	CString strError;
	BOOL nStatus = CRecordsetEx::TestConnect(strConnect, &strError);

	if ( nStatus )
	{
		Default(pCtxt, "");
	}
	else
	{
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle();

		html.WritePageMenu("", "Setup");
		html.EndMenu();

		html.ODBCSetupForm(CPage::DefaultODBCSetupExecute);

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::DefaultODBCSetupExecute(CHttpServerContext* pCtxt,
								  LPTSTR szURL,
								  LPTSTR szServer,
								  LPTSTR szUID,
								  LPTSTR szPWD,
								  LPTSTR szDatabase,
								  LPTSTR szDriver,
								  LPTSTR szDSN,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );

	CString strLink = html.GetFileName( );

	html.SetContent();
	html.EndHeader();

	html.WritePageTitle();

	CString strNewConnect = CRecordsetEx::GetDefaultConnect( szServer, szUID, szPWD, szDatabase, szDriver, szDSN, FALSE );

	CString strError;
	BOOL nStatus = CRecordsetEx::TestConnect(strNewConnect, &strError);

	if ( nStatus )
	{
		html.WritePageMenu("", "Setup");
		html.WritePageMenuItem(CPage::DefaultEntry, "Start", 0);
		html.EndMenu();

		html << _T("Configuration Tested Successful.<BR>\r\n<BR>\r\n");

		prop.SetDefaultConnect( szServer, szUID, szPWD, szDatabase, szDriver, szDSN );
		
		if( !strNewConnect.Compare( prop.GetDefaultConnect( ) ) )
		{
			html << _T("Configuration Saved and Validated.<BR>\r\n");
		}
		else
		{
			html << _T("Error Validating Configuration.<BR>\r\n");
		}
	}
	else
	{
		html.WritePageMenu("", "Setup");

		if( !CRecordsetEx::TestConnect(prop.GetDefaultConnect( ), NULL) )
		{
			html.WritePageMenuItem(CPage::DefaultODBCSetupForm, "Setup", 0);
		}
		else
		{
			html.WritePageMenuItem(CPage::DefaultEntry, "Start", 0);
		}

		html.EndMenu();

		html << _T("Bad Configuration.<BR>\r\n<BR>\r\n");
		html << _T(strError) << _T("<BR>\r\n");
	}

	html.EndPage();
	html.EndContent();
}

///////////////////////////////////////////////////////////////////////////////////////		int j;
// Entry

void CWebAthlExtension::DefaultEntry(CHttpServerContext* pCtxt,
							  LPTSTR Submit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );

	CString strOrgName;

	try
	{
		CString strConnect = prop.GetDefaultConnect( );
		CString strSQL;
		
		CDatabase db;
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );

		strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = (SELECT MIN(OrgID) FROM Organisation)" );
		COrganisationSet rs( &db );
		rs.Open(CRecordset::forwardOnly, strSQL );

		if ( !rs.IsEOF( ) )
		{
			if (_tcscmp( rs.m_OrgName, ""))
			{
				strOrgName = rs.m_OrgName;
			}
			else
			{
				strOrgName = UNKNOWN_ORG;
			}
		}
		else
		{
			strOrgName = UNKNOWN_ORG;
		}

		rs.Close( );
		db.Close( );
	}
	catch (CDBException* pEx)
	{
		pEx->m_strError;
		strOrgName = UNKNOWN_ORG;

		pEx->Delete();
	}

	CString strExitURL = prop.GetEx(CHtmlKey::Navigation,CHtmlKey::ExitURL);

    html.SetContent();
    html.SetCookie(CHtmlKey::LoginName, CAuthenticator::m_szGuestUser);
    html.SetCookie(CHtmlKey::Password, "");
	html.SetCookie(CHtmlKey::PersonID, CConvert::itoa(-1));
    html.SetCookie(CHtmlKey::OrgName, strOrgName);
    html.SetCookie(CHtmlKey::Heading, strOrgName);
    html.EndHeader();

	html.WritePageTitle(strOrgName);

	html.WritePageMenu(CAuthenticator::m_szGuestUser, strOrgName);
	html.WritePageMenuItem(CPage::DefaultMenu, "Guest", 0);
	html.WritePageMenuItem(CPage::DefaultLoginForm, "Members", 0);

	if( !strExitURL.IsEmpty( ) )
		html.WritePageMenuItem(strExitURL, "Exit", 0);

	html.EndMenu();

	html << _T("To View Publication Reports, enter the Guest Area<BR>\r\n");
	html << _T("<BR>\r\n");
	html << _T("To Enter the System, enter the Members Area<BR>\r\n");

	html.EndPage();
	html.EndContent();

}

///////////////////////////////////////////////////////////////////////
// Login

void CWebAthlExtension::DefaultLoginForm(CHttpServerContext* pCtxt,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	
	CString strLoginName = html.GetCookie(CHtmlKey::LoginName);
	CString strOrgName = html.GetCookie(CHtmlKey::OrgName);
	
    html.SetContent();
    html.EndHeader();

	html.WritePageTitle(strOrgName);
	html.WritePageMenu(strLoginName, strOrgName);

	html.WritePageMenuItem(CPage::DefaultEntry, CHtmlKey::Cancel, 0);
	html.EndMenu();

	html.StartForm("Login", CPage::DefaultLoginExecute);
	html.EditTextBoxSmall("Login Name", "LoginName", "");
	html.PasswordBox("Password", "Password", "");
	html.SubmitButton(CHtmlKey::Login);
	html.EndForm();

	html.EndPage();
	html.EndContent();
}


void CWebAthlExtension::DefaultLoginExecute(CHttpServerContext* pCtxt,
							  LPTSTR szLoginName,
							  LPTSTR szPassword,
							  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );


	CString strPwd;

	CCryptByteArray* cbaPwd = new CCryptByteArray( );

	cbaPwd->Init(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
				 atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

	cbaPwd->Set( szPassword );
	cbaPwd->EnCrypt( );

	strPwd = cbaPwd->GetHexString( );

	if(auth.ValidateLogin(szLoginName, strPwd))
	{
		html.SetContent();
	    html.SetCookie(CHtmlKey::LoginName, auth.m_strLoginName);
	    html.SetCookie(CHtmlKey::Password, strPwd);
		html.SetCookie(CHtmlKey::PersonID, CConvert::itoa(auth.m_iPersonID));
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);
		html.EndMenu();

		CString strOutput;
		strOutput.Format("User '%s' Logged On, Security Role %d : '%s'<BR>\r\n", auth.m_strUserName, auth.m_iRoleID, auth.m_strRoleName);
		html << _T(strOutput);

		BOOL bUserAccessEnabled = atoi(prop.GetEx(CHtmlKey::UserAccess,CHtmlKey::Enabled));
		if( !bUserAccessEnabled )
		{
			html << _T("<BR>\r\nAn Administrator has Disabled User Access.  Do you intend to perform System Maintenance?<BR>\r\n");
		}

	}
	else
	{
		// invalid login

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strLoginName, auth.m_strOrgName);
		html.WritePageMenuItem(CPage::DefaultEntry, CHtmlKey::Cancel, 0);
		html.EndMenu();

		html << _T(auth.m_strError) << _T("<BR>\r\n");
	}

	delete cbaPwd;

	html.EndPage();
	html.EndContent();
}



///////////////////////////////////////////////////////////////////////
// Menu

void CWebAthlExtension::DefaultMenu(CHttpServerContext* pCtxt,
							  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::none) )
	{
		auth.m_strHeading = "Main Menu";

		html.SetContent();
		html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
		html.SetCookie(CHtmlKey::IsSecured, "1");
		html.SetCookie(CHtmlKey::BackLink, CPage::DefaultMenu);
		html.SetCookie(CHtmlKey::IsUtil, "0");
		html.SetCookie(CHtmlKey::IsOptions, "0");
		html.SetCookie(CHtmlKey::IsResultsEntry, "0");
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultEntry, "Log Off", 0);

		try
		{
			CString strConnect = prop.GetDefaultConnect();

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			if(auth.HasPermission(CModule::Reports) )
				html.WritePageMenuItem(CPage::ReportsMenu,"Reports", 0);

			if(auth.HasPermission(CModule::ResultsEntry))
				html.WritePageMenuItem(CPage::ResultsEntryPrePostMenu,"Event Results Entry", 0);

			if(auth.HasPermission(CModule::OpenPreEntry))
				if( CUtil::Count( &db, _T( "SELECT COUNT(*) AS Total FROM Event WHERE PreEntryOpen > 0 " ) ) )
					html.WritePageMenuItem(CPage::SeriesSelectForm, "Open Pre-Event Entry", 3, CPage::ResultsEntrySelectEventForm, "Pre-Event", CModule::GetName(CModule::OpenPreEntry) );

			if(auth.HasPermission(CModule::Processing))
				html.WritePageMenuItem(CPage::SeriesSelectForm,"Results Processing", 2, CPage::ProcessingForm, CPage::ProcessingForm);

			if(auth.HasPermission(CModule::Financial))
				html.WritePageMenuItem(CPage::FinancialMenu,"Financial", 0);

			//if(auth.HasPermission(CModule::RegistrationType))
			//	html.WritePageMenuItem(CPage::RegistrationTypeMenu,"Registration Type", 0);

			if(auth.HasPermission(CModule::Person | CModule::EditPerson | CModule::ViewPerson))
				html.WritePageMenuItem(CPage::PersonMenu,"Person", 0);

			if(auth.HasPermission(CModule::SeriesMaintain | CModule::SeriesAdd))
				html.WritePageMenuItem(CPage::SeriesMenu,"Series", 0);

			//if(auth.HasPermission(CModule::Location))
			//	html.WritePageMenuItem(CPage::LocationMenu,"Location", 0);

			//if(auth.HasPermission(CModule::EventType))
			//	html.WritePageMenuItem(CPage::EventTypeMenu,"Event Type", 0);

			if(auth.HasPermission(CModule::Roster))
				html.WritePageMenuItem(CPage::RosterMenu,"Event Roster", 0);

			//if(auth.HasPermission(CModule::Roster))
			//	html.WritePageMenuItem(CPage::SeriesSelectForm,"Roster", 2, CPage::RosterSelectEventForm, "Roster");

			//if(auth.HasPermission(CModule::RosterDescriptions))
			//	html.WritePageMenuItem(CPage::RosterDescriptionsMenu,"Roster Descriptions", 0);

			if(auth.HasPermission(CModule::WorldStandards))
				html.WritePageMenuItem(CPage::WorldStandardMenu,"Age Standards", 0);

			if(auth.HasPermission(CModule::Organisation))
				html.WritePageMenuItem(CPage::OrganisationMenu,"Organisation", 0);

			if(auth.HasPermission(CModule::Utilities | CModule::SeriesMaintain) )
				html.WritePageMenuItem(CPage::UtilitiesMenu,"Utilities", 0);

			if( auth.HasPermission(CModule::Security))
				html.WritePageMenuItem(CPage::SecurityMenu,"Security", 0);

			if(auth.HasPermission(CModule::Options) )
				html.WritePageMenuItem(CPage::OptionsMenu,"Options", 0);

			if(auth.HasPermission(CModule::Maintenance))
				html.WritePageMenuItem(CPage::MaintenanceMenu,"Maintenance", 0);

			if( !prop.IsLicensed() )
				if(auth.HasPermission(CModule::Security))
					html.WritePageMenuItem(CPage::LicenseForm,"License", 0);

			db.Close( );

			html.EndMenu();
		}
		catch (CDBException* pEx)
		{
			html.EndMenu();
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

