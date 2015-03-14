// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "OrganisationSet.h"

///////////////////////////////////////////////////////////////////////
// Organisation

void CWebAthlExtension::OrganisationMenu(CHttpServerContext* pCtxt,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
		auth.m_strHeading = "Organisation";
		auth.m_strBackLink = CPage::OrganisationMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::OrganisationAddForm, "Add Organisation", 0);
		html.WritePageMenuItem(CPage::OrganisationSelectForm, "Edit Organisation", 1, CPage::OrganisationEditForm);
		html.WritePageMenuItem(CPage::OrganisationSelectForm, "View Organisation", 1, CPage::OrganisationViewForm);

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationSelectForm(CHttpServerContext* pCtxt,
											   LPTSTR szSubmit,
											   LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
		auth.m_strFrwdLink = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			COrganisationSet rs( &db );
			strSQL.Format( "SELECT * FROM Organisation ORDER BY OrgName" );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html << _T("Select an Organisation\r\n");

				html.StartForm("Organisation", auth.m_strFrwdLink);

				html.StartSelectBox("Organisation", "OrgID");
				while( !rs.IsEOF( ) )
				{
					html.AddSelectBox(rs.m_OrgName, CConvert::itoa(rs.m_OrgID), "");
					rs.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Organisations Available\r\n");
			}

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationAddForm(CHttpServerContext* pCtxt,
											LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();


		html.StartForm("Organisation", CPage::OrganisationAddExecute);

		html.NonEditInt("Organisation ID", 0);
		html.HiddenInt("OrgID", 0);

		html.EditTextBoxLarge("Organisation Name", "OrgName", "");
		html.HorizontalRule();
		html.EditTextBoxLarge("Address", "Address1", "");
		html.EditTextBoxLarge("", "Address2", "");
		html.EditTextBoxSmall("Town", "Town", "");
		html.EditTextBoxSmall("State", "State", "");
		html.EditTextBoxSmall("Country", "Country", "");
		html.EditTextBoxSmall("PostCode", "PostCode", "");

		html.HorizontalRule();
		html.EditTextBoxSmall("Phone", "Phone", "");
		html.EditTextBoxSmall("Fax", "Fax", "");
		html.EditTextBoxSmall("Mobile", "Mobile", "");
		html.EditTextBoxLarge("e-mail", "email", "");
		html.EditTextBoxLarge("URL", "URL", "");
		html.HorizontalRule();

		html.EditIntBox("Registrar Person ID", "RegistrarPersonID", 0);
		html.EditIntBox("Administrator Person ID", "AdministratorPersonID", 0);

		html.HorizontalRule();
		html.ResetButton();
		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationAddExecute(CHttpServerContext* pCtxt,
										LPTSTR szOrgID,
										LPTSTR szOrgName,
										LPTSTR szAddress1,
										LPTSTR szAddress2,
										LPTSTR szTown,
										LPTSTR szState,
										LPTSTR szCountry,
										LPTSTR szPostCode,
										LPTSTR szPhone,
										LPTSTR szFax,
										LPTSTR szMobile,
										LPTSTR szEmail,
										LPTSTR szURL,
										LPTSTR szRegistrarPersonID,
										LPTSTR szAdministratorPersonID,
										LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Organisation Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			COrganisationSet rs( &db );
			strSQL.Format( "SELECT * FROM Organisation" );
			rs.Open(CRecordset::dynaset, strSQL );

	
			rs.AddNew( );

			if(_tcslen(szOrgName) > 0) 
				rs.m_OrgName = szOrgName;
			else
				rs.SetFieldNull( &rs.m_OrgName, TRUE );

			if(_tcslen(szAddress1) > 0) 
				rs.m_Address1 = szAddress1;
			else
				rs.SetFieldNull( &rs.m_Address1, TRUE );

			if(_tcslen(szAddress2) > 0) 
				rs.m_Address2 = szAddress2;
			else
				rs.SetFieldNull( &rs.m_Address2, TRUE );

			if(_tcslen(szTown) > 0) 
				rs.m_Town = szTown;
			else
				rs.SetFieldNull( &rs.m_Town, TRUE );

			if(_tcslen(szState) > 0) 
				rs.m_State = szState;
			else
				rs.SetFieldNull( &rs.m_State, TRUE );

			if(_tcslen(szCountry) > 0) 
				rs.m_Country = szCountry;
			else
				rs.SetFieldNull( &rs.m_Country, TRUE );

			if(_tcslen(szPostCode) > 0) 
				rs.m_PostCode = szPostCode;
			else
				rs.SetFieldNull( &rs.m_PostCode, TRUE );

			if(_tcslen(szPhone) > 0) 
				rs.m_Phone = szPhone;
			else
				rs.SetFieldNull( &rs.m_Phone, TRUE );

			if(_tcslen(szFax) > 0) 
				rs.m_Fax = szFax;
			else
				rs.SetFieldNull( &rs.m_Fax, TRUE );

			if(_tcslen(szMobile) > 0) 
				rs.m_Mobile = szMobile;
			else
				rs.SetFieldNull( &rs.m_Mobile, TRUE );

			if(_tcslen(szEmail) > 0) 
				rs.m_email = szEmail;
			else
				rs.SetFieldNull( &rs.m_email, TRUE );

			if(_tcslen(szURL) > 0) 
				rs.m_URL = szURL;
			else
				rs.SetFieldNull( &rs.m_URL, TRUE );

			rs.m_RegistrarPersonID = atoi(szRegistrarPersonID);
			rs.m_AdministratorPersonID = atoi(szAdministratorPersonID);


			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Organisation, <B>");
				html << _T(szOrgName);
				html << _T("</B><BR>\r\n");
			}

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationEditForm(CHttpServerContext* pCtxt,
											 LPTSTR szOrgID,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = %s", szOrgID );
			COrganisationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
				

			html.StartForm("Organisation", CPage::OrganisationEditExecute);

			html.NonEditInt("Organisation ID", rs.m_OrgID);
			html.HiddenInt("OrgID", rs.m_OrgID);

			html.EditTextBoxLarge("Organisation Name", "OrgName", rs.m_OrgName);
			html.HorizontalRule();
			html.EditTextBoxLarge("Address", "Address1", rs.m_Address1);
			html.EditTextBoxLarge("", "Address2", rs.m_Address2);
			html.EditTextBoxSmall("Town", "Town", rs.m_Town);
			html.EditTextBoxSmall("State", "State", rs.m_State);
			html.EditTextBoxSmall("Country", "Country", rs.m_Country);
			html.EditTextBoxSmall("PostCode", "PostCode", rs.m_PostCode);

			html.HorizontalRule();
			html.EditTextBoxSmall("Phone", "Phone", rs.m_Phone);
			html.EditTextBoxSmall("Fax", "Fax", rs.m_Fax);
			html.EditTextBoxSmall("Mobile", "Mobile", rs.m_Mobile);
			html.EditTextBoxLarge("e-mail", "email", rs.m_email);
			html.EditTextBoxLarge("URL", "URL", rs.m_URL);
			html.HorizontalRule();
	
			html.EditIntBox("Registrar Person ID", "RegistrarPersonID", rs.m_RegistrarPersonID);
			html.EditIntBox("Administrator Person ID", "AdministratorPersonID", rs.m_AdministratorPersonID);

			html.HorizontalRule();
			html.ResetButton();
			html.SubmitButton(CHtmlKey::Save);
//			html.SubmitButton(CHtmlKey::Delete);

			html.EndForm();

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationEditExecute(CHttpServerContext* pCtxt,
										 LPTSTR szOrgID,
										 LPTSTR szOrgName,
										 LPTSTR szAddress1,
										 LPTSTR szAddress2,
										 LPTSTR szTown,
										 LPTSTR szState,
										 LPTSTR szCountry,
										 LPTSTR szPostCode,
										 LPTSTR szPhone,
										 LPTSTR szFax,
										 LPTSTR szMobile,
										 LPTSTR szEmail,
										 LPTSTR szURL,
										 LPTSTR szRegistrarPersonID,
										 LPTSTR szAdministratorPersonID,
										 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Organisation Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = %s ", szOrgID );
			COrganisationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );


			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				if(_tcslen(szOrgName) > 0) 
					rs.m_OrgName = szOrgName;
				else
					rs.SetFieldNull( &rs.m_OrgName, TRUE );

				if(_tcslen(szAddress1) > 0) 
					rs.m_Address1 = szAddress1;
				else
					rs.SetFieldNull( &rs.m_Address1, TRUE );

				if(_tcslen(szAddress2) > 0) 
					rs.m_Address2 = szAddress2;
				else
					rs.SetFieldNull( &rs.m_Address2, TRUE );

				if(_tcslen(szTown) > 0) 
					rs.m_Town = szTown;
				else
					rs.SetFieldNull( &rs.m_Town, TRUE );

				if(_tcslen(szState) > 0) 
					rs.m_State = szState;
				else
					rs.SetFieldNull( &rs.m_State, TRUE );

				if(_tcslen(szCountry) > 0) 
					rs.m_Country = szCountry;
				else
					rs.SetFieldNull( &rs.m_Country, TRUE );

				if(_tcslen(szPostCode) > 0) 
					rs.m_PostCode = szPostCode;
				else
					rs.SetFieldNull( &rs.m_PostCode, TRUE );

				if(_tcslen(szPhone) > 0) 
					rs.m_Phone = szPhone;
				else
					rs.SetFieldNull( &rs.m_Phone, TRUE );

				if(_tcslen(szFax) > 0) 
					rs.m_Fax = szFax;
				else
					rs.SetFieldNull( &rs.m_Fax, TRUE );

				if(_tcslen(szMobile) > 0) 
					rs.m_Mobile = szMobile;
				else
					rs.SetFieldNull( &rs.m_Mobile, TRUE );

				if(_tcslen(szEmail) > 0) 
					rs.m_email = szEmail;
				else
					rs.SetFieldNull( &rs.m_email, TRUE );

				if(_tcslen(szURL) > 0) 
					rs.m_URL = szURL;
				else
					rs.SetFieldNull( &rs.m_URL, TRUE );

				rs.m_RegistrarPersonID = atoi(szRegistrarPersonID);
				rs.m_AdministratorPersonID = atoi(szAdministratorPersonID);

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Organisation, <B>");
					html << _T(szOrgName);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleteed Organisation, <B>");
				html << _T(szOrgName);
				html << _T("</B><BR>\r\n");
			}

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OrganisationViewForm(CHttpServerContext* pCtxt,
											 LPTSTR szOrgID,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Organisation) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = %s", szOrgID );
			COrganisationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
				

			html.StartForm("Organisation", "");

			html.NonEditInt("Organisation ID", rs.m_OrgID);
			html.NonEditText("Organisation Name", rs.m_OrgName);

			html.HorizontalRule();
			html.NonEditText("Address", rs.m_Address1);
			html.NonEditText("", rs.m_Address2);
			html.NonEditText("Town", rs.m_Town);
			html.NonEditText("State", rs.m_State);
			html.NonEditText("Country", rs.m_Country);
			html.NonEditText("PostCode", rs.m_PostCode);

			html.HorizontalRule();
			html.NonEditText("Phone", rs.m_Phone);
			html.NonEditText("Fax", rs.m_Fax);
			html.NonEditText("Mobile", rs.m_Mobile);
			html.NonEditText("e-mail", rs.m_email);
			html.NonEditText("URL", rs.m_URL);

			html.HorizontalRule();
			html.NonEditInt("Registrar Person ID", rs.m_RegistrarPersonID);
			html.NonEditInt("Administrator Person ID", rs.m_AdministratorPersonID);

			html.EndForm();

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;

			pEx->Delete();
		}

		html.EndPage();
		html.EndContent();
	}
}

