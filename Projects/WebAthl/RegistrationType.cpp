// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "EventTypeSet.h"

#include "RegistrationTypeSet.h"

///////////////////////////////////////////////////////////////////////
// RegistrationType

void CWebAthlExtension::RegistrationTypeSelectForm(CHttpServerContext* pCtxt,
												   LPTSTR szSubmit,
												   LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RegistrationType) )
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


			CRegistrationTypeSet rs( &db );

			strSQL.Format( "SELECT * FROM RegistrationType ORDER BY RegistrationDescription" );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html << _T("Select a Registration Type\r\n");

				html.StartForm("Registration Type", auth.m_strFrwdLink);

				html.StartSelectBox("Registration Type", "RegistrationTypeID");
				while( !rs.IsEOF( ) )
				{
					html.AddSelectBox(rs.m_RegistrationDescription, CConvert::itoa(rs.m_RegistrationTypeID), "");
					rs.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Registration Types Available\r\n");
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

void CWebAthlExtension::RegistrationTypeEditForm(CHttpServerContext* pCtxt,
												 LPTSTR szRegistrationTypeID,
												 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RegistrationType) )
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

			int iRegTypeID = atoi(szRegistrationTypeID);

			strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %s ", szRegistrationTypeID );
			CRegistrationTypeSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
				
			if( !rs.IsEOF( ) || !iRegTypeID )
			{
				html.StartForm("Registration Type", CPage::RegistrationTypeEditExecute);

				if( iRegTypeID )
				{
					html.NonEditInt("Registration Type ID", rs.m_RegistrationTypeID);
					html.HiddenInt("RegistrationTypeID", rs.m_RegistrationTypeID);

					html.EditTextBoxLarge("Registration Description", "RegistrationDescription", rs.m_RegistrationDescription);
					html.HorizontalRule();

					html.MonthBox("Start of Season", "MonthStart", rs.m_MonthStart);
					html.MonthBox("End of Season", "MonthStop", rs.m_MonthStop);
					html.HorizontalRule();

					html.ResetButton();
					html.SubmitButton(CHtmlKey::Save);
//					html.SubmitButton(CHtmlKey::Delete);
				}
				else // New RegTypeID == 0
				{
					html.NonEditInt("Registration Type ID", 0);
					html.HiddenInt("RegistrationTypeID", 0);

					html.EditTextBoxLarge("Registration Description", "RegistrationDescription", "");
					html.HorizontalRule();

					html.MonthBox("Start of Season", "MonthStart", 0);
					html.MonthBox("End of Season", "MonthStop", 0);
					html.HorizontalRule();

					html.ResetButton();
					html.SubmitButton(CHtmlKey::Add);
				}

				html.EndForm();
			}
			else
			{
				html << _T("No Event Types<BR>\r\n");
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

void CWebAthlExtension::RegistrationTypeEditExecute(CHttpServerContext* pCtxt,
											 LPTSTR szRegistrationTypeID,
											 LPTSTR szRegistrationDescription,
											 LPTSTR szMonthStart,
											 LPTSTR szMonthStop,
											 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RegistrationType) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Registration Type Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %s ", szRegistrationTypeID );
			CRegistrationTypeSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if ( !_tcscmp( szSubmit, CHtmlKey::Save ) || !_tcscmp( szSubmit, CHtmlKey::Add ) )
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				if(_tcslen(szRegistrationDescription) > 0) 
					rs.m_RegistrationDescription = szRegistrationDescription;
				else
					rs.SetFieldNull( &rs.m_RegistrationDescription, TRUE );

				rs.m_MonthStart = atoi(szMonthStart);
				rs.m_MonthStop = atoi(szMonthStop);

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					if ( !_tcscmp( szSubmit, CHtmlKey::Add ) )
						html << _T("Added Registration Type, <B>");
					else
						html << _T("Modified Registration Type, <B>");

					html << _T(szRegistrationDescription);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Registration Type, <B>");
				html << _T(szRegistrationDescription);
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