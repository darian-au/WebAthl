// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "EventETypLocSet.h"
#include "EventSet.h"
#include "EventTypeSet.h"
#include "LocationSet.h"
#include "RosterSet.h"
#include "RosterNamesSet.h"
#include "RosterDescriptionsSet.h"
#include "SeriesSet.h"

///////////////////////////////////////////////////////////////////////
// Roster

void CWebAthlExtension::RosterMenu(CHttpServerContext* pCtxt,
								   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
		auth.m_strHeading = "Event Roster";
		auth.m_strBackLink = CPage::RosterMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "1");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SeriesSelectForm,"Maintain Event Roster", 2, CPage::RosterSelectEventForm, "Roster");

		if( auth.HasPermission(CModule::RosterDescriptions) )
		{
			html.WritePageMenuItem(CPage::RosterDescriptionsAddForm, "Add Task", 0);
			html.WritePageMenuItem(CPage::RosterDescriptionsSelectForm, "Edit Task", 1, CPage::RosterDescriptionsEditForm);
		}

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::RosterSelectEventForm(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
		auth.m_strFrwdLink = CPage::RosterMaintainMenu;

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

			strSQL.Format( html.GetSelectEventBoxDetails(atoi(szSeriesID), 0, 1) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );


			if( !rsEvent.IsEOF( ) )
			{
				html.StartForm("Event", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, -1, NULL);
				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Events Available\r\n");
			}

			rsEvent.Close( );
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

void CWebAthlExtension::RosterMaintainMenu(CHttpServerContext* pCtxt,
										 LPTSTR szSeriesID,
										 LPTSTR szEventID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
		auth.m_strBackLink = CPage::RosterMaintainMenu;

		CString strSeriesID;
		if ( !_tcscmp(szSeriesID, "none") )
			strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		else
			strSeriesID = szSeriesID;

		CString strEventID;
		if ( !_tcscmp(szEventID, "none") )
			strEventID = html.GetCookie(CHtmlKey::EventID);
		else
			strEventID = szEventID;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.SetCookie(CHtmlKey::SeriesID, strSeriesID);
	    html.SetCookie(CHtmlKey::EventID, strEventID);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RosterMenu, "Event Roster Menu", 0);

		html.WritePageMenuItem(CPage::SearchPersonForm, "Assign New Person", 1, CPage::RosterAddExecute);
		html.WritePageMenuItem(CPage::RosterDeleteForm, "Remove Person", 1, strEventID);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", strSeriesID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( html.GetNonEditEventBoxDetails(atoi(strEventID)) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );
			
			html.StartForm("Event Roster", "");

			html.NonEditText("Series", rsSeries.m_SeriesDescription );
			html.NonEditEvent( 
				"Event", 
				rsEvent.m_EventNo,
				rsEvent.m_LocationDescription,
				rsEvent.m_EventDescription );

			html.NonEditDateBox(
				"Date",
				rsEvent.m_DateDAY,
				rsEvent.m_DateMONTH,
				rsEvent.m_DateYEAR);

			html.EndForm();

			rsSeries.Close( );
			rsEvent.Close( );


			strSQL.Format( "SELECT * FROM RosterDescriptions" );
			CRosterDescriptionsSet rsRostDesc( &db );
			rsRostDesc.Open(CRecordset::dynaset, strSQL );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETROSTERNAMES);
			strSQL.Format( strSQLtmp, strEventID );

			CRosterNamesSet rsRoster( &db );
			rsRoster.Open(CRecordset::dynaset, strSQL );

			if( !rsRoster.IsEOF( ) )
			{
				html.StartForm("", CPage::RosterEditExecute);
				html.HiddenText("EventID", strEventID);
				html.HiddenText("SeriesID", strSeriesID);
				html.RosterTable("Task", "Person");
				html.HorizontalRule();

				while( !rsRoster.IsEOF( ) )
				{
					html.StartRoster("TaskIDList");			

					if( !rsRostDesc.IsEOF( ) )
					{
						while( !rsRostDesc.IsEOF( ) )
						{
							html.AddSelectBox(
								rsRostDesc.m_TaskDescription,
								CConvert::itoa(rsRostDesc.m_TaskID),
								CConvert::itoa(rsRoster.m_Roster_TaskID));
							rsRostDesc.MoveNext( );
						}
						rsRostDesc.MoveFirst( );
					}
					else
						html.AddSelectBox("No Descriptions available","0","0");

					html.EndRoster( (rsRoster.m_LastName + ", " + rsRoster.m_FirstName));
					html.HiddenInt( "PersonIDList", rsRoster.m_Roster_PersonID);

					rsRoster.MoveNext( );
				}

				html.HorizontalRule();
				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);
				html.EndForm();
			}
			rsRoster.Close( );
			rsRostDesc.Close( );

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

void CWebAthlExtension::RosterAddExecute(CHttpServerContext* pCtxt,
								  LPTSTR szPersonID,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RosterMaintainMenu, "Roster Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM RosterDescriptions" );
			CRosterDescriptionsSet rsRosDesc( &db );
			rsRosDesc.Open(CRecordset::dynaset, strSQL );

			if( !rsRosDesc.IsEOF( ) )
			{
				strSQL.Format( "SELECT * FROM Roster" );
				CRosterSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.AddNew( );

				rs.m_SeriesID = atoi(strSeriesID);
				rs.m_EventID = atoi(strEventID);
				rs.m_PersonID = atoi(szPersonID);
				rs.m_TaskID = rsRosDesc.m_TaskID;

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Person to Roster, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}

				rs.Close( );
			}
			else
			{
				html << _T("Cannot add a Person to the Roster without any Tasks.<BR>\r\n");
				html << _T("Please go to the Roster Descriptions Menu and create a Task.<BR>\r\n");
				html << _T("If you do not have access to create a Task then contact your System Administrator.<BR>\r\n");
			}
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

void CWebAthlExtension::RosterEditExecute(CHttpServerContext* pCtxt,
								   LPTSTR szEventID,
								   LPTSTR szSeriesID,
								   LPTSTR szTaskIDList,
								   LPTSTR szPersonIDList,
								   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RosterMaintainMenu, "Roster Menu", 0);
		html.EndMenu();

		CString strTaskIDList = CString(szTaskIDList);
		CStringArray* strTaskIDItems = new CStringArray();

		CString strPersonIDList = CString(szPersonIDList);
		CStringArray* strPersonIDItems = new CStringArray();

		CCSV csv(CWebAthlExtension::chIsapiDelimiter);

		csv.GetItems(strTaskIDItems, &strTaskIDList);
		csv.GetItems(strPersonIDItems, &strPersonIDList);

		int nTaskIDItems = strTaskIDItems->GetSize( );
		int nPersonIDItems = strPersonIDItems->GetSize( );


		if( nTaskIDItems == nPersonIDItems )
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				int iSeriesID = atoi(szSeriesID);
				int iEventID = atoi(szEventID);

				CRosterSet rs( &db );
				strSQL.Format( "DELETE FROM Roster WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID );

				db.ExecuteSQL( strSQL );
				html << _T("Resetting Roster <BR>\r\n");


				strSQL.Format( "SELECT * FROM Roster WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID );
				rs.Open(CRecordset::dynaset, strSQL );

				if (!_tcscmp( szSubmit, CHtmlKey::Save ))
				{
					for( int nIndex = 0; nIndex < nTaskIDItems ; nIndex++ )
					{
						CString strTaskID = strTaskIDItems->GetAt(nIndex);
						int iTaskID = atoi(strTaskID);

						CString strPersonID = strPersonIDItems->GetAt(nIndex);
						int iPersonID = atoi(strPersonID);


						if( (iTaskID > 0) && (iPersonID > 0) )
						{
							rs.AddNew( );

							rs.m_SeriesID = iSeriesID;
							rs.m_EventID = iEventID;

							rs.m_TaskID = iTaskID;
							rs.m_PersonID = iPersonID;
				
							if( !rs.CanUpdate( ) )
								html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
							if( !rs.Update( ) )
								html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
							else
							{
								html << _T("Modified Person on Roster, <B>");
								html << _T( strPersonID );
								html << _T("</B> with Task <B>");
								html << _T( strTaskID );
								html << _T("</B><BR>\r\n");
							}

							rs.MoveNext( );
						}
					}
				}

				rs.Close( );
				db.Close( );
			}
			catch (CDBException* pEx)
			{
				html << pEx;

				pEx->Delete();
			}
		}
		else
		{
			html << _T("nTaskIDItems does no match nPersonIDItems<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::RosterDeleteForm(CHttpServerContext* pCtxt,
									  LPTSTR szSubmit,
									  LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
	{
		CString strEventID;
		if ( !_tcscmp(szInit, "none") )
			strEventID = html.GetCookie(CHtmlKey::EventID);
		else
			strEventID = szInit;

		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

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
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETROSTERNAMES);

			strSQL.Format( strSQLtmp, strEventID );

			CRosterNamesSet rsRoster( &db );
			rsRoster.Open(CRecordset::dynaset, strSQL );

			if( !rsRoster.IsEOF( ) )
			{
				html.StartForm("Remove Person", CPage::RosterDeleteExecute);
				html.HiddenText("EventID", strEventID);
				html.HiddenText("SeriesID", strSeriesID);

				html.StartSelectBox("Rostered Person", "PersonID" );
				while( !rsRoster.IsEOF( ) )
				{
					html.AddSelectBox(
						(rsRoster.m_LastName + ", " + rsRoster.m_FirstName),
						CConvert::itoa(rsRoster.m_Roster_PersonID),
						"");
					rsRoster.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Delete);
				html.EndForm();
			}
			else
			{
				html << _T("No Person Currently Assigned to this Roster");
			}

			rsRoster.Close( );
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

void CWebAthlExtension::RosterDeleteExecute(CHttpServerContext* pCtxt,
								  LPTSTR szEventID,
								  LPTSTR szSeriesID,
								  LPTSTR szPersonID,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Roster) )
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

			strSQL.Format( "SELECT * FROM Roster WHERE EventID = %s AND SeriesID = %s AND PersonID = %s", 
				szEventID, szSeriesID, szPersonID);

			CRosterSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Person from Roster, <B>");
				html << _T(szPersonID);
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
