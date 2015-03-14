// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "RosterDescriptionsSet.h"

///////////////////////////////////////////////////////////////////////
// RosterDescriptions

void CWebAthlExtension::RosterDescriptionsSelectForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit,
											 LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RosterDescriptions) )
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

			strSQL.Format( "SELECT * FROM RosterDescriptions ORDER BY TaskDescription" );
			CRosterDescriptionsSet rsRos( &db );
			rsRos.Open(CRecordset::dynaset, strSQL );

			if( !rsRos.IsEOF( ) )
			{
				html << _T("Select a Task\r\n");

				html.StartForm("Roster Descriptions", auth.m_strFrwdLink);

				html.StartSelectBox("Task", "TaskID");
				while( !rsRos.IsEOF( ) )
				{
					html.AddSelectBox(rsRos.m_TaskDescription, CConvert::itoa(rsRos.m_TaskID), "");
					rsRos.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Task Descriptions Available\r\n");
			}

			rsRos.Close( );
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

void CWebAthlExtension::RosterDescriptionsAddForm(CHttpServerContext* pCtxt,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RosterDescriptions) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();


		html.StartForm("Roster Descriptions", CPage::RosterDescriptionsAddExecute);

		html.NonEditInt("Task ID", 0);
		html.HiddenInt("TaskID", 0);

		html.EditTextBoxLarge("Task", "TaskDescription", "");
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::RosterDescriptionsAddExecute(CHttpServerContext* pCtxt,
									  LPTSTR szTaskID,
									  LPTSTR szTaskDescription,
									  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RosterDescriptions) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Roster Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;


			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM RosterDescriptions" );
			CRosterDescriptionsSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

	
			rs.AddNew( );

			if(_tcslen(szTaskDescription) > 0) 
				rs.m_TaskDescription = szTaskDescription;
			else
				rs.SetFieldNull( &rs.m_TaskDescription, TRUE );

	
			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Task, <B>");
				html << _T(szTaskDescription);
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

void CWebAthlExtension::RosterDescriptionsEditForm(CHttpServerContext* pCtxt,
										   LPTSTR szTaskID,
										   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RosterDescriptions) )
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

			CRosterDescriptionsSet rs( &db );
			strSQL.Format( "SELECT * FROM RosterDescriptions WHERE TaskID = %s", szTaskID );
			rs.Open(CRecordset::dynaset, strSQL );
				
			if( !rs.IsEOF( ) )
			{
				html.StartForm("Roster Descriptions", CPage::RosterDescriptionsEditExecute);

				html.NonEditInt("Task ID", rs.m_TaskID);
				html.HiddenInt("TaskID", rs.m_TaskID);

				html.EditTextBoxLarge("Task Description", "TaskDescription", rs.m_TaskDescription);
				html.HorizontalRule();

				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);
//				html.SubmitButton(CHtmlKey::Delete);

				html.EndForm();
			}
			else
			{
				html << _T("No Roster Descriptions Available<BR>\r\n");
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

void CWebAthlExtension::RosterDescriptionsEditExecute(CHttpServerContext* pCtxt,
									   LPTSTR szTaskID,
									   LPTSTR szTaskDescription,
									   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::RosterDescriptions) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Roster Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM RosterDescriptions WHERE TaskID = %s ", szTaskID );
			CRosterDescriptionsSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				if(_tcslen(szTaskDescription) > 0) 
					rs.m_TaskDescription = szTaskDescription;
				else
					rs.SetFieldNull( &rs.m_TaskDescription, TRUE );

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Task, <B>");
					html << _T(szTaskDescription);
					html << _T("</B><BR>\r\n");
				}
			}

			if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Task, <B>");
				html << _T(szTaskDescription);
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