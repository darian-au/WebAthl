// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "EventTypeSet.h"

///////////////////////////////////////////////////////////////////////
// EentType

void CWebAthlExtension::EventTypeSelectForm(CHttpServerContext* pCtxt,
											LPTSTR szSubmit,
											LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::EventType) )
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

			CEventTypeSet rsEvntTyp( &db );

			strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
			rsEvntTyp.Open(CRecordset::dynaset, strSQL );

			if( !rsEvntTyp.IsEOF( ) )
			{
				html << _T("Select an Event Type\r\n");

				html.StartForm("Event Type", auth.m_strFrwdLink);

				html.StartSelectBox("Event Type", "EventTypeID");
				while( !rsEvntTyp.IsEOF( ) )
				{
					html.AddSelectBox(rsEvntTyp.m_EventDescription, CConvert::itoa(rsEvntTyp.m_EventTypeID), "");
					rsEvntTyp.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Event Types Available\r\n");
			}

			rsEvntTyp.Close( );
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

void CWebAthlExtension::EventTypeAddForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::EventType) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();


		html.StartForm("Event Type", CPage::EventTypeAddExecute);

		html.NonEditInt("Event Type ID", 0);
		html.HiddenInt("EventTypeID", 0);

		html.EditTextBoxLarge("Event Description", "EventDescription", "");
		html.HorizontalRule();

		html.RadioButton("Event Type", "Long Distance", "Timed", "1", "1");
		html.RadioButton("", "Jump, Throw or Points", "Timed", "0", "");
		html.RadioButton("", "Sprint", "Timed", "2", "");
		html.HorizontalRule();

		html.NonEditText("Note:", "</strong><em><small>For Jumps, Throws or Points:, Set the</small></em><strong>");
		html.NonEditText("",      "</strong><em><small>Event Length to a reasonable,</small></em><strong>");
		html.NonEditText("",      "</strong><em><small>but unachievable performance. I.e.</small></em><strong>");
		html.NonEditText("",      "</strong><em><small>a World Standard Perfomance.</small></em><strong>");

		html.EditFloatBox("Event Length (metres)", "EventLength", 0);
		html.HorizontalRule();

		html.ResetButton();
		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::EventTypeAddExecute(CHttpServerContext* pCtxt,
									 LPTSTR szEventTypeID,
									 LPTSTR szEventDescription,
									 LPTSTR szTimed,
									 LPTSTR szEventLength,
									 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::EventType) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM EventType" );
			CEventTypeSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			rs.AddNew( );

			if(_tcslen(szEventDescription) > 0) 
				rs.m_EventDescription = szEventDescription;
			else
				rs.SetFieldNull( &rs.m_EventDescription, TRUE );

			rs.m_Timed = atoi(szTimed);
			rs.m_EventLength = atof(szEventLength);


			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Event Type, <B>");
				html << _T(szEventDescription);
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

void CWebAthlExtension::EventTypeEditForm(CHttpServerContext* pCtxt,
										  LPTSTR szEventTypeID,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::EventType) )
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

			strSQL.Format( "SELECT * FROM EventType WHERE EventTypeID = %s", szEventTypeID );
			CEventTypeSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
				
			if( !rs.IsEOF( ) )
			{
				html.StartForm("Event Type", CPage::EventTypeEditExecute);

				html.NonEditInt("Event Type ID", rs.m_EventTypeID);
				html.HiddenInt("EventTypeID", rs.m_EventTypeID);

				html.EditTextBoxLarge("Event Description", "EventDescription", rs.m_EventDescription);
				html.HorizontalRule();

				CString strTimed = CConvert::itoa(rs.m_Timed);

				html.RadioButton("Event Type", "Long Distance", "Timed", "1", strTimed);
				html.RadioButton("", "Jump, Throw or Points", "Timed", "0", strTimed);
				html.RadioButton("", "Sprint", "Timed", "2", strTimed);
				html.HorizontalRule();

				html.NonEditText("Note:", "</strong><em><small>For Jumps, Throws or Points:, Set the</small></em><strong>");
				html.NonEditText("",      "</strong><em><small>Event Length to a reasonable,</small></em><strong>");
				html.NonEditText("",      "</strong><em><small>but unachievable performance. I.e.</small></em><strong>");
				html.NonEditText("",      "</strong><em><small>a World Standard Perfomance.</small></em><strong>");
				html.EditFloatBox("Event Length (metres)", "EventLength", rs.m_EventLength);
				html.HorizontalRule();

				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);
//				html.SubmitButton(CHtmlKey::Delete);

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

void CWebAthlExtension::EventTypeEditExecute(CHttpServerContext* pCtxt,
									  LPTSTR szEventTypeID,
									  LPTSTR szEventDescription,
									  LPTSTR szTimed,
									  LPTSTR szEventLength,
									  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::EventType) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM EventType WHERE EventTypeID = %s ", szEventTypeID );
			CEventTypeSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				if(_tcslen(szEventDescription) > 0) 
					rs.m_EventDescription = szEventDescription;
				else
					rs.SetFieldNull( &rs.m_EventDescription, TRUE );

				rs.m_Timed = atoi(szTimed);
				rs.m_EventLength = atof(szEventLength);

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Event Type, <B>");
					html << _T(szEventDescription);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Event Type, <B>");
				html << _T(szEventDescription);
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
