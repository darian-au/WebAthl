// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SeriesSet.h"
#include "GroupsSet.h"
#include "EventTypeSet.h"

#include "EventETypLocSet.h"
#include "SeriesSeasonSet.h"
#include "SecurityPersonSeriesSet.h"

#include "CountResultSet.h"

///////////////////////////////////////////////////////////////////////
// Series

void CWebAthlExtension::SeriesMenu(CHttpServerContext* pCtxt,
								   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain | CModule::SeriesAdd) )
	{
		auth.m_strHeading = "Series";
		auth.m_strBackLink = CPage::SeriesMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "1");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SeriesSelectForm, "Maintain Series", 1, CPage::SeriesMaintainMenu);

		if(auth.HasPermission(CModule::SeriesAdd))
		{
			html.WritePageMenuItem(CPage::SeriesAddForm, "Add Series", 0);
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Edit Series", 1, CPage::SeriesEditForm);
		}

		if(auth.HasPermission(CModule::Location))
		{
			html.WritePageMenuItem(CPage::LocationAddForm, "Add Location", 0);
			html.WritePageMenuItem(CPage::LocationSelectForm, "Edit Location", 1, CPage::LocationEditForm);
		}

		if(auth.HasPermission(CModule::EventType))
		{
			html.WritePageMenuItem(CPage::EventTypeAddForm, "Add Event Type", 0);
			html.WritePageMenuItem(CPage::EventTypeSelectForm, "Edit Event Type", 1, CPage::EventTypeEditForm);
		}

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SeriesAddForm(CHttpServerContext* pCtxt,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesAdd) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SeriesMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		html.StartForm("Series", CPage::SeriesAddExecute);

		html.NonEditInt("Series ID", 0);
		html.HiddenInt("SeriesID", 0);

		html.EditTextBoxLarge("Series Description", "SeriesDescription", "");
		html.HorizontalRule();

//		html.RadioButton("Handicap", "Handicapped", "Handicapped", "1", "1");
//		html.RadioButton("", "Not Handicapped", "Handicapped", "0", "");
//		html.HorizontalRule();
//
//		html.RadioButton("Age Category", "Veteran", "AgeCategory", "V", "V");
//		html.RadioButton("", "Junior", "AgeCategory", "J", "");
//		html.RadioButton("", "Open", "AgeCategory", "O", "");
//		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SeriesAddExecute(CHttpServerContext* pCtxt,
								  LPTSTR szSeriesID,
								  LPTSTR szSeriesDescription,
//								  LPTSTR szHandicapped,
//								  LPTSTR szAgeCategory,
								  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesAdd) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SeriesMenu, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Series" );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !prop.IsLicensed( ) )
			{
				rsSeries.SetCountMessage( _T("Maximum Series Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
				//rsSeries.SetCountWhereClause( _T("") );
				rsSeries.HasMaxCountReached( TRUE );
			}

			rsSeries.AddNew( );

			if(_tcslen(szSeriesDescription) > 0) 
				rsSeries.m_SeriesDescription = szSeriesDescription;
			else
				rsSeries.SetFieldNull( &rsSeries.m_SeriesDescription, TRUE );

//			rsSeries.m_Handicapped = atoi(szHandicapped);
//			rsSeries.m_AgeCategory = szAgeCategory;


			if( !rsSeries.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rsSeries.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Series, <B>");
				html << _T(szSeriesDescription);
				html << _T("</B><BR>\r\n");
			}
			rsSeries.Close( );


			if( auth.m_iPersonID > 0)
			{
				strSQL.Format( "SELECT * FROM Series WHERE SeriesDescription = '%s' ", szSeriesDescription );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				// add the SeriesID to SecurityPersonSeries
				strSQL.Format( "SELECT * FROM SecurityPersonSeries WHERE PersonID = %d", auth.m_iPersonID );
				CSecurityPersonSeriesSet rsSecurity( &db );
				rsSecurity.Open(CRecordset::dynaset, strSQL );

				rsSecurity.AddNew( );

				rsSecurity.m_PersonID = auth.m_iPersonID;
				rsSecurity.m_SeriesID = rsSeries.m_SeriesID;


				if( !rsSecurity.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsSecurity.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Series, <B>");
					html << _T(CConvert::itoa(rsSeries.m_SeriesID));
					html << _T("</B> to Person, <B>");
					html << _T(CConvert::itoa(auth.m_iPersonID));
					html << _T("</B><BR>\r\n");
				}
				rsSeries.Close( );
				rsSecurity.Close( );
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

void CWebAthlExtension::SeriesMaintainMenu(CHttpServerContext* pCtxt,
									   LPTSTR szSeriesID,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strBackLink = CPage::SeriesMaintainMenu;

		CString strSeriesID;

		if ( !_tcscmp(szSeriesID, "none") )
			strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		else
			strSeriesID = szSeriesID;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::SeriesID, strSeriesID);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SeriesMenu, "Series Menu", 0);

		if( auth.HasPermission(CModule::Rules) )
			html.WritePageMenuItem(CPage::RulesMenu, "Rules", 1, strSeriesID);

		if( auth.HasPermission(CModule::Groups) )
			html.WritePageMenuItem(CPage::GroupsEditSelectForm, "Groups", 1, strSeriesID);

		if( auth.HasPermission(CModule::Event) )
		{
			html.WritePageMenuItem(CPage::EventAddForm, "Add Event", 1, strSeriesID);
			html.WritePageMenuItem(CPage::EventSelectForm, "Edit Event", 1, CPage::EventEditForm);
		}

		html.WritePageMenuItem(CPage::SeriesSetFirstEventForm, "Set First Event For Season", 0);

		if( auth.HasPermission(CModule::Utilities) )
		{
			html.WritePageMenuItem(CPage::SeriesSetNextEventForm, "Set Next Event For Processing", 0);
		}

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

//			CString strHandicapped;

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s ORDER BY SeriesDescription", strSeriesID );
			CSeriesSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
			

			html.StartForm("Series", "");

			html.NonEditInt("Series ID", rs.m_SeriesID);
			html.HiddenInt("SeriesID", rs.m_SeriesID);

			html.NonEditText("Series Description", rs.m_SeriesDescription);
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

void CWebAthlExtension::SeriesEditForm(CHttpServerContext* pCtxt,
									   LPTSTR szSeriesID,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesAdd) )
	{
		CString strSeriesID;

		if ( !_tcscmp(szSeriesID, "none") )
			strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		else
			strSeriesID = szSeriesID;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::SeriesID, strSeriesID);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SeriesMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

//			CString strHandicapped;

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s ORDER BY SeriesDescription", strSeriesID );
			CSeriesSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
			

			html.StartForm("Series", CPage::SeriesEditExecute);

			html.NonEditInt("Series ID", rs.m_SeriesID);
			html.HiddenInt("SeriesID", rs.m_SeriesID);

			html.EditTextBoxLarge("Series Description", "SeriesDescription", rs.m_SeriesDescription);
			html.HorizontalRule();

//			html.RadioButton("Handicap", "Handicapped", "Handicapped", "1", CConvert::itoa(rs.m_Handicapped));
//			html.RadioButton("", "Not Handicapped", "Handicapped", "0", strHandicapped);
//			html.HorizontalRule();
//
//			html.RadioButton("Age Category", "Veteran", "AgeCategory", "V", rs.m_AgeCategory);
//			html.RadioButton("", "Junior", "AgeCategory", "J", rs.m_AgeCategory);
//			html.RadioButton("", "Open", "AgeCategory", "O", rs.m_AgeCategory);
//			html.HorizontalRule();

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

void CWebAthlExtension::SeriesEditExecute(CHttpServerContext* pCtxt,
								   LPTSTR szSeriesID,
								   LPTSTR szSeriesDescription,
//								   LPTSTR szHandicapped,
//								   LPTSTR szAgeCategory,
								   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesAdd) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SeriesMenu, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s ", szSeriesID );
			CSeriesSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				if(_tcslen(szSeriesDescription) > 0) 
					rs.m_SeriesDescription = szSeriesDescription;
				else
					rs.SetFieldNull( &rs.m_SeriesDescription, TRUE );

//				rs.m_Handicapped = atoi(szHandicapped);
//				rs.m_AgeCategory = szAgeCategory;

	
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Series, <B>");
					html << _T(szSeriesDescription);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Series, <B>");
				html << _T(szSeriesDescription);
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

void CWebAthlExtension::SeriesSetFirstEventForm(CHttpServerContext* pCtxt,
										   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

		auth.m_strFrwdLink = CPage::SeriesSetFirstEventExecute;

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

			strSQL.Format( html.GetSelectEventBoxDetails(atoi(strSeriesID), 0, 0) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );


			strSQL.Format( "SELECT * FROM SeriesSeason WHERE SeriesID = %s", strSeriesID);
			CSeriesSeasonSet rsSeason( &db );
			rsSeason.Open(CRecordset::dynaset, strSQL );

			int iFirstEventForSeason = 0;
			int iEventsInSeason = 0;

			if( !rsSeason.IsEOF( ) )
			{
				iFirstEventForSeason = rsSeason.m_FirstEventForSeason;
				iEventsInSeason = rsSeason.m_EventsInSeason;
			}

			if( !rsEvent.IsEOF( ) )
			{
				html.StartForm("First Event For Season", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", strSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, iFirstEventForSeason, NULL);

				html.EditIntBox("Events to Look Back", "EventsInSeason", iEventsInSeason);

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Save);

				html.EndForm();

				html << _T("<p>Note: <b>Events to Look Back</b> is used during Processing to determine a History List of Participants.  Set this value to Zero if you do not want to generate a History List.</p>\r\n");
			}
			else
			{
				html << _T("No Events Available\r\n");
			}

			rsSeason.Close( );
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

void CWebAthlExtension::SeriesSetFirstEventExecute(CHttpServerContext* pCtxt,
									   LPTSTR szSeriesID,
									   LPTSTR szEventID,
									   LPTSTR szEventsInSeason,
									   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
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

			CSeriesSeasonSet rs( &db );
			strSQL.Format( "SELECT * FROM SeriesSeason WHERE SeriesID = %s ", szSeriesID );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				rs.m_SeriesID = atoi(szSeriesID);
				rs.m_FirstEventForSeason = atoi(szEventID);
				rs.m_EventsInSeason = atoi(szEventsInSeason);

				if( rs.IsFieldNull( &rs.m_NextEventForProcess ) )
				{
					//Find the first EventNo in the Series
					CCountResultSet rsEvent( &db );
					strSQL.Format( "SELECT EventID AS Total FROM Event WHERE SeriesID = %s AND EventNo = 1", szSeriesID );
					rsEvent.Open(CRecordset::dynaset, strSQL );

					int iEventNo = 1;

					if( !rsEvent.IsEOF() && !rsEvent.IsFieldNull( &rsEvent.m_Total ) )
						iEventNo = rsEvent.m_Total;

					rsEvent.Close( );

					rs.m_NextEventForProcess = iEventNo;
				}
	
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("First Event for Season Reset <BR>\r\n");
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

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SeriesSetNextEventForm(CHttpServerContext* pCtxt,
											  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

		auth.m_strFrwdLink = CPage::SeriesSetNextEventExecute;

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

			strSQL.Format( html.GetSelectEventBoxDetails(atoi(strSeriesID), 0, 0) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );


			strSQL.Format( "SELECT * FROM SeriesSeason WHERE SeriesID = %s", strSeriesID);
			CSeriesSeasonSet rsSeason( &db );
			rsSeason.Open(CRecordset::dynaset, strSQL );

			int iNextEventForProcess = 0;

			if( !rsSeason.IsEOF( ) )
				if( !rsSeason.IsFieldNull( &rsSeason.m_NextEventForProcess ) )
					iNextEventForProcess = rsSeason.m_NextEventForProcess;

			if( !rsEvent.IsEOF( ) )
			{
				html.StartForm("Next Event For Processing", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", strSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, iNextEventForProcess, "none");
				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Save);

				html.EndForm();
			}
			else
			{
				html << _T("No Events Available\r\n");
			}

			rsSeason.Close( );
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

void CWebAthlExtension::SeriesSetNextEventExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szEventID,
										  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
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

			CSeriesSeasonSet rs( &db );
			strSQL.Format( "SELECT * FROM SeriesSeason WHERE SeriesID = %s ", szSeriesID );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				rs.m_SeriesID = atoi(szSeriesID);

				if(atoi(szEventID) > 0) 
					rs.m_NextEventForProcess = atoi(szEventID);
				else
					rs.SetFieldNull( &rs.m_NextEventForProcess, TRUE );
	
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Next Event For Processing Reset <BR>\r\n");
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

		html.EndPage();
		html.EndContent();
	}
}

