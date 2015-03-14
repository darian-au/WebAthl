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
#include "RosterDescriptionsSet.h"
#include "CountResultSet.h"

///////////////////////////////////////////////////////////////////////
// Event

void CWebAthlExtension::EventSelectForm(CHttpServerContext* pCtxt,
										LPTSTR szSubmit,
										LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Event) )
	{
		auth.m_strFrwdLink = szInit;

		CString strSeriesID;
		strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

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

			strSQL.Format( html.GetSelectEventBoxDetails(atoi(strSeriesID), 0, 1) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );

			if( !rsEvent.IsEOF( ) )
			{
				html.StartForm("Event", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", strSeriesID);

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


void CWebAthlExtension::EventAddForm(CHttpServerContext* pCtxt,
									 LPTSTR szSubmit,
									 LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Event) )
	{
		CString strSeriesID = szInit;

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

			CCountResultSet rsCount( &db );
			strSQL.Format( "SELECT MAX(EventNo) AS Total FROM Event WHERE SeriesID = %s ", strSeriesID );
			rsCount.Open(CRecordset::dynaset, strSQL );

			int iNewEventNo;

			if( rsCount.IsEOF( ) || rsCount.IsFieldNull( &rsCount.m_Total ) )
				iNewEventNo = 1;
			else
				iNewEventNo = rsCount.m_Total + 1;

			rsCount.Close( );

			CLocationSet rsLoc( &db );
			strSQL.Format( "SELECT * FROM Location ORDER BY LocationDescription" );
			rsLoc.Open(CRecordset::dynaset, strSQL );

			CEventTypeSet rsEvntTyp( &db );
			strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
			rsEvntTyp.Open(CRecordset::dynaset, strSQL );

			if( !rsLoc.IsEOF( ) )
			{
				if( !rsEvntTyp.IsEOF( ) )
				{
					html.StartForm("Event", CPage::EventAddExecute);
					html.NonEditInt("Event ID", 0);
					html.NonEditInt("Event Number", iNewEventNo);
					html.HorizontalRule();

					html.HiddenInt("EventID", 0);

					html.HiddenText("SeriesID", strSeriesID);

					int nNull;
					CRecordsetEx::GetNullItem(&nNull);

					html.DateBox("Date","Date");
					html.DateBox("Date For AgeGroup", "DateAge",
						nNull,
						nNull,
						nNull);

					html.HorizontalRule();

					html.HiddenInt("EventNo", iNewEventNo);
					html.StartSelectBox("Location", "LocationID");
					while( !rsLoc.IsEOF( ) )
					{
						html.AddSelectBox(rsLoc.m_LocationDescription, CConvert::itoa(rsLoc.m_LocationID), "");
						rsLoc.MoveNext( );
					}
					html.EndSelectBox();

					html.StartSelectBox("Event Type", "EventTypeID");
					while( !rsEvntTyp.IsEOF( ) )
					{
						html.AddSelectBox(rsEvntTyp.m_EventDescription, CConvert::itoa(rsEvntTyp.m_EventTypeID), "");
						rsEvntTyp.MoveNext( );
					}
					html.EndSelectBox();

					html.HorizontalRule();

					html.CheckBox("Pre-Event Entry", "Open For Public", "PreEntryOpen", "1", "0");

					html.HorizontalRule();

					html.SubmitButton(CHtmlKey::Add);

					html.EndForm();
				}
				else
				{
					html << _T("No EventTypes Available<BR>\r\n");
				}
			}
			else
			{
				html << _T("No Locations Available<BR>\r\n");
			}

			rsLoc.Close( );
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


void CWebAthlExtension::EventAddExecute(CHttpServerContext* pCtxt,
									 LPTSTR szEventID,
									 LPTSTR szSeriesID,
									 LPTSTR szDateDAY,
									 LPTSTR szDateMONTH,
									 LPTSTR szDateYEAR,
									 LPTSTR szDateAgeDAY,
									 LPTSTR szDateAgeMONTH,
									 LPTSTR szDateAgeYEAR,
									 LPTSTR szEventNo,
									 LPTSTR szLocationID,
									 LPTSTR szEventTypeID,
									 LPTSTR szPreEntryOpen,
									 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Event) )
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

			strSQL.Format( "SELECT * FROM Event" );
			CEventSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !prop.IsLicensed( ) )
			{
				CString strWhereClause;
				strWhereClause.Format("WHERE SeriesID = %s", szSeriesID);

				rs.SetCountMessage( _T("Maximum Event Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
				rs.SetCountWhereClause( strWhereClause );
				rs.HasMaxCountReached( TRUE );
			}

			rs.AddNew( );

			rs.m_SeriesID = atoi(szSeriesID);
			rs.m_LocationID = atoi(szLocationID);
			rs.m_EventTypeID = atoi(szEventTypeID);
			rs.m_DateDAY = atoi(szDateDAY);
			rs.m_DateMONTH = atoi(szDateMONTH);
			rs.m_DateYEAR = atoi(szDateYEAR);
			rs.m_DateAgeDAY = atoi(szDateAgeDAY);
			rs.m_DateAgeMONTH = atoi(szDateAgeMONTH);
			rs.m_DateAgeYEAR = atoi(szDateAgeYEAR);
			rs.m_EventNo = atoi(szEventNo);
			rs.m_PreEntryOpen = atoi(szPreEntryOpen);

			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Event, <B>");
				html << _T(szEventNo);
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



void CWebAthlExtension::EventEditForm(CHttpServerContext* pCtxt,
									  LPTSTR szSeriesID,
									  LPTSTR szEventID,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Event) )
	{
		CString strEventID;
		CString strSeriesID;

		if ( !_tcscmp(szEventID, "none") )
			strEventID.Format("%s", html.GetCookie(CHtmlKey::EventID));
		else
			strEventID.Format("%s", szEventID);

		if ( !_tcscmp(szSeriesID, "none") )
			strSeriesID.Format("%s", html.GetCookie(CHtmlKey::SeriesID));
		else
			strSeriesID.Format("%s", szSeriesID);

		html.SetContent();
	    html.SetCookie(CHtmlKey::EventID, strEventID);
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

			CEventSet rsEvent( &db );
			strSQL.Format( "SELECT * FROM Event WHERE EventID = %s", strEventID );
			rsEvent.Open(CRecordset::dynaset, strSQL );

			CLocationSet rsLoc( &db );
			strSQL.Format( "SELECT * FROM Location ORDER BY LocationDescription" );
			rsLoc.Open(CRecordset::dynaset, strSQL );

			CEventTypeSet rsEvntTyp( &db );
			strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
			rsEvntTyp.Open(CRecordset::dynaset, strSQL );

			if( !rsLoc.IsEOF( ) )
			{
				if( !rsEvntTyp.IsEOF( ) )
				{
					html.StartForm("Event", CPage::EventEditExecute);
					html.NonEditInt("Event ID", rsEvent.m_EventID);
					html.NonEditInt("Event Number", rsEvent.m_EventNo);
					html.HorizontalRule();

					html.HiddenInt("EventID", rsEvent.m_EventID);
					html.HiddenInt("SeriesID", rsEvent.m_SeriesID);

					html.DateBox("Date", "Date",
						rsEvent.m_DateDAY,
						rsEvent.m_DateMONTH,
						rsEvent.m_DateYEAR);

					html.DateBox("Date For AgeGroup", "DateAge",
						rsEvent.m_DateAgeDAY,
						rsEvent.m_DateAgeMONTH,
						rsEvent.m_DateAgeYEAR);

					html.HorizontalRule();

					html.HiddenInt("EventNo", rsEvent.m_EventNo);
					html.StartSelectBox("Location", "LocationID");
					while( !rsLoc.IsEOF( ) )
					{
						html.AddSelectBox(rsLoc.m_LocationDescription,
							CConvert::itoa(rsLoc.m_LocationID),
							CConvert::itoa(rsEvent.m_LocationID));
						rsLoc.MoveNext( );
					}
					html.EndSelectBox();

					html.StartSelectBox("Event Type", "EventTypeID");
					while( !rsEvntTyp.IsEOF( ) )
					{
						html.AddSelectBox(rsEvntTyp.m_EventDescription,
							CConvert::itoa(rsEvntTyp.m_EventTypeID),
							CConvert::itoa(rsEvent.m_EventTypeID));
						rsEvntTyp.MoveNext( );
					}
					html.EndSelectBox();

					html.HorizontalRule();

					html.CheckBox("Pre-Event Entry", "Open For Public", "PreEntryOpen", "1", CConvert::itoa(rsEvent.m_PreEntryOpen));

					html.HorizontalRule();

					html.ResetButton();
					html.SubmitButton(CHtmlKey::Save);
//					html.SubmitButton(CHtmlKey::Delete);

					html.EndForm();
				}
				else
				{
					html << _T("No EventTypes Available<BR>\r\n");
				}
			}
			else
			{
				html << _T("No Locations Available<BR>\r\n");
			}

			rsLoc.Close( );
			rsEvntTyp.Close( );
	
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





void CWebAthlExtension::EventEditExecute(CHttpServerContext* pCtxt,
								  LPTSTR szEventID,
								  LPTSTR szSeriesID,
								  LPTSTR szDateDAY,
								  LPTSTR szDateMONTH,
								  LPTSTR szDateYEAR,
								  LPTSTR szDateAgeDAY,
								  LPTSTR szDateAgeMONTH,
								  LPTSTR szDateAgeYEAR,
								  LPTSTR szEventNo,
								  LPTSTR szLocationID,
								  LPTSTR szEventTypeID,
								  LPTSTR szPreEntryOpen,
								  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Event) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strSQL;

			CString strConnect = prop.GetDefaultConnect();

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Event WHERE EventID = %s", szEventID );
			CEventSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				rs.m_LocationID = atoi(szLocationID);
				rs.m_EventTypeID = atoi(szEventTypeID);
				rs.m_DateDAY = atoi(szDateDAY);
				rs.m_DateMONTH = atoi(szDateMONTH);
				rs.m_DateYEAR = atoi(szDateYEAR);
				rs.m_DateAgeDAY = atoi(szDateAgeDAY);
				rs.m_DateAgeMONTH = atoi(szDateAgeMONTH);
				rs.m_DateAgeYEAR = atoi(szDateAgeYEAR);
				rs.m_PreEntryOpen = atoi(szPreEntryOpen);
		
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Event, <B>");
					html << _T(szEventNo);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );
				html << _T("Deleted Event, <B>");
				html << _T(szEventNo);
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

