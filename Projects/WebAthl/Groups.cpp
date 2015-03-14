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
// Groups

#define MAX_GROUPS 100

void CWebAthlExtension::GroupsEditSelectForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit,
										 LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Groups) )
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

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", strSeriesID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

//			if(rsSeries.m_Handicapped)
//			{
				strSQL.Format( "SELECT SeriesID, EventTypeID, MAX(GroupID) AS Groups, GroupRate, GroupStart FROM Groups WHERE SeriesID = %s GROUP BY SeriesID, EventTypeID, GroupRate, GroupStart", strSeriesID );
				CGroupsSet rsGroups( &db );
				rsGroups.Open(CRecordset::dynaset, strSQL );
		
				strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
				CEventTypeSet rsEvntTyp( &db );
				rsEvntTyp.Open(CRecordset::dynaset, strSQL );
				
				if( !rsEvntTyp.IsEOF( ) )
				{
					html.StartForm("Groups", CPage::GroupsEditForm);
					html.HiddenText("SeriesID", strSeriesID);

					if( !rsGroups.IsEOF( ) )
					{
						html.NonEditInt("Groups", rsGroups.m_GroupID);
						html.HiddenInt("Groups", rsGroups.m_GroupID);
					}
					else
						html.EditIntBox("Groups", "Groups", 1);
					
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

				rsGroups.Close( );
				rsEvntTyp.Close( );
//			}
//			else
//			{
//				html << _T("This Series is not Handicapped.  Grouping Rules have no effect.");
//			}

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

void CWebAthlExtension::GroupsEditForm(CHttpServerContext* pCtxt,
									   LPTSTR szSeriesID,
									   LPTSTR szGroups,
									   LPTSTR szEventTypeID,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Groups) )
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

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM EventType WHERE EventTypeID = %s", szEventTypeID );
			CEventTypeSet rsEvntType( &db );
			rsEvntType.Open(CRecordset::dynaset, strSQL );

			CString strTitle;
			strTitle.Format("%s, %s", rsSeries.m_SeriesDescription, rsEvntType.m_EventDescription);
			
			rsSeries.Close( );
			rsEvntType.Close( );
			

			html.StartForm(strTitle, CPage::GroupsEditExecute);
			html.HiddenText("SeriesID", szSeriesID);
			html.HiddenText("EventTypeID", szEventTypeID);
			html.HiddenText("Groups", szGroups);

			strSQL.Format( "SELECT * FROM Groups WHERE SeriesID = %s AND EventTypeID = %s", szSeriesID, szEventTypeID );
			CGroupsSet rsGroups( &db );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			html.GroupsTableHeader("Group", "Rate", "Start" );

			if( !rsGroups.IsEOF( ) )
			{
				while( !rsGroups.IsEOF( ) )
				{
					html.GroupsTable(rsGroups.m_GroupID, rsGroups.m_GroupRate, rsGroups.m_GroupStart );
					rsGroups.MoveNext( );
				}
			}
			else
			{
				int iGroups = atoi(szGroups);
				int i = 1;

				while( (i <= iGroups) && (i < MAX_GROUPS) )
				{
					html.GroupsTable(i++, 0.0, 0.0 );
				}
			}

			html.HorizontalRule();
			html.SubmitButton(CHtmlKey::Save);

			html.EndForm();

			rsGroups.Close( );
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

void CWebAthlExtension::GroupsEditExecute(CHttpServerContext* pCtxt,
								   LPTSTR szSeriesID,
								   LPTSTR szEventTypeID,
								   LPTSTR szGroups,
								   LPTSTR szGroupRateList,
								   LPTSTR szGroupStartList,
								   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Groups) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);

		html.EndMenu();


		CString strGroupRateList = CString(szGroupRateList);
		CStringArray* strGroupRateItems = new CStringArray();

		CString strGroupStartList = CString(szGroupStartList);
		CStringArray* strGroupStartItems = new CStringArray();

		CCSV csv(CWebAthlExtension::chIsapiDelimiter);

		csv.GetItems(strGroupRateItems, &strGroupRateList);
		csv.GetItems(strGroupStartItems, &strGroupStartList);

		int nGroupRateItems = strGroupRateItems->GetSize( );
		int nGroupStartItems = strGroupStartItems->GetSize( );


		if( nGroupRateItems == nGroupStartItems )
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				int iSeriesID = atoi(szSeriesID);
				int iEventTypeID = atoi(szEventTypeID);
				int iGroups = atoi(szGroups);

				CGroupsSet rs( &db );
				strSQL.Format( "DELETE FROM Groups WHERE SeriesID = %d AND EventTypeID = %d", iSeriesID, iEventTypeID );

				db.ExecuteSQL( strSQL );
				html << _T("Resetting Groups <BR>\r\n");

				strSQL.Format( "SELECT * FROM Groups WHERE SeriesID = %d AND EventTypeID = %d ORDER BY GroupID", iSeriesID, iEventTypeID );
				rs.Open(CRecordset::dynaset, strSQL );

				for( int nIndex = 0; nIndex < nGroupRateItems ; nIndex++ )
				{
					CString strGroupRate = strGroupRateItems->GetAt(nIndex);
					double dGroupRate = atof(strGroupRate);

					CString strGroupStart = strGroupStartItems->GetAt(nIndex);
					double dGroupStart = atof(strGroupStart);

					rs.AddNew( );

					rs.m_SeriesID = iSeriesID;
					rs.m_EventTypeID = iEventTypeID;
					rs.m_GroupID = (nIndex + 1);

					rs.m_GroupRate = dGroupRate;
					rs.m_GroupStart = dGroupStart;

					if( !rs.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
					if( !rs.Update( ) )
						html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
					else
					{
						html << _T("Set Group : <B>");
						html << _T( CConvert::itoa(nIndex + 1) );
						html << _T("</B>; Rate <B>");
						html << _T( CConvert::dtoa(dGroupRate) );
						html << _T("</B>; Start <B>");
						html << _T( CConvert::dtoa(dGroupStart) );
						html << _T("</B><BR>\r\n");
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
			html << _T("nGroupRateItems does no match nGroupStartItems<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}



