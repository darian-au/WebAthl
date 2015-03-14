// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SeriesSet.h"
#include "GroupsSet.h"
#include "EventTypeSet.h"

#include "SeriesSeasonSet.h"

///////////////////////////////////////////////////////////////////////
// SeriesSelect

void CWebAthlExtension::SeriesSelectForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit,
										 LPTSTR szInit,
										 LPTSTR szInit1,
										 LPTSTR szInit2)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SelectSeries) )
	{
		// put the following line in your code to enable 
		//  Secured SelectSeries
		//AddHeader(pCtxt, setCookie(CHtmlKey::IsSecured, "1"));

		// put the following line in your code to disable 
		//  Secured SelectSeries
		//AddHeader(pCtxt, setCookie(CHtmlKey::IsSecured, "0"));

		BOOL bIsSecured = atoi(html.GetCookie(CHtmlKey::IsSecured));

		if( auth.m_iRoleID == CAuthenticator::m_iDboRoleId )
		{
			bIsSecured = 0;
		}

		// if iSecured then use iSecured to restrict the 
		// list of Series to select from
		
		auth.m_strFrwdLink = szInit;


		html.SetContent();
		if( !_tcscmp(szInit1, "Pre-Event") )
		{
		    html.SetCookie(CHtmlKey::ResultsEntry, "Pre");
		}
		else if( !_tcscmp(szInit1, "Post-Event") )
		{
		    html.SetCookie(CHtmlKey::ResultsEntry, "Post");
		}
		else if( !_tcscmp(szInit1, "Roster") && !_tcscmp(szInit, CPage::RosterSelectEventForm) )
		{
			auth.m_strHeading = "Event Roster";
		    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
		}
		else if( !_tcscmp(szInit1, CPage::ProcessingForm) && !_tcscmp(szInit, CPage::ProcessingForm) )
		{
			auth.m_strHeading = "Processing";
		    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
		}
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

			CSeriesSet rsSeries( &db );

			if( !_tcscmp(szInit2, CModule::GetName(CModule::OpenPreEntry)) )
			{
				strSQL.Format( "SELECT DISTINCT Series.* FROM Series, Event WHERE Series.SeriesID = Event.SeriesID AND Event.PreEntryOpen > 0 ORDER BY SeriesDescription" );
			}
			else if( !_tcscmp(szInit, CPage::SecurityAssignSeriesExecute) && atoi(szInit1) )
			{
				strSQL.Format( "SELECT * FROM Series WHERE SeriesID NOT IN ( SELECT SeriesID FROM SecurityPersonSeries WHERE SecurityPersonSeries.PersonID = %i ) ORDER BY SeriesDescription", atoi(szInit1) );
			}
			else if( bIsSecured )
			{
				strSQL.Format( "SELECT Series.* FROM Series, SecurityPersonSeries WHERE SecurityPersonSeries.PersonID = %i AND Series.SeriesID = SecurityPersonSeries.SeriesID ORDER BY Series.SeriesDescription", auth.m_iPersonID );
			}
			else
			{
				strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			}

			//html << szInit << _T("<BR><BR>\r\n");
			//html << szInit1 << _T("<BR><BR>\r\n");
			//html << szInit2 << _T("<BR><BR>\r\n");
			//html << strSQL << _T("<BR><BR>\r\n");

			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select a Series\r\n");

				html.StartForm("Series", auth.m_strFrwdLink);
				
				html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Series Available\r\n");
			}

			rsSeries.Close( );
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


