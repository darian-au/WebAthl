// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SeriesSet.h"
#include "EventSet.h"
#include "EventETypLocSet.h"
#include "EventTypeSet.h"
#include "LocationSet.h"

#include "GroupsSet.h"
#include "ResultsSet.h"

#include "QuickReportSet.h"
#include "PreResultsSet.h"
#include "PostResultsSet.h"
#include "PersonSet.h"
#include "ParticipantForSeriesSet.h"

#include "CountResultSet.h"
#include "BoolResultSet.h"

///////////////////////////////////////////////////////////////////////
// ResultsEntry

void CWebAthlExtension::ResultsEntryPrePostMenu(CHttpServerContext* pCtxt,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		auth.m_strHeading = "Event Results Entry";
		auth.m_strBackLink = CPage::ResultsEntryPrePostMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "1");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
		html.SetCookie(CHtmlKey::IsResultsEntry, "1");
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SeriesSelectForm, "Pre-Event Entries", 2, CPage::ResultsEntrySelectEventForm, "Pre-Event");
		html.WritePageMenuItem(CPage::SeriesSelectForm, "Post-Event Results", 2, CPage::ResultsEntrySelectEventForm, "Post-Event");

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ResultsEntrySelectEventForm(CHttpServerContext* pCtxt,
												    LPTSTR szSeriesID,
												    LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry | CModule::OpenPreEntry) )
	{
		BOOL bIsResultsEntry = atoi(html.GetCookie(CHtmlKey::IsResultsEntry));

		if( bIsResultsEntry && !auth.HasPermission(CModule::ResultsEntry) )
		{
			bIsResultsEntry = FALSE;
		}

		auth.m_strFrwdLink = CPage::ResultsEntryMenu;

		html.SetContent();
		html.SetCookie(CHtmlKey::IsResultsEntry, CConvert::itoa(bIsResultsEntry));
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

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_EVENTFORPROCESSING);
			strSQL.Format(strSQLtmp,
				_T(szSeriesID));

			CEventETypLocSet rsCurrentEvent( &db );
			rsCurrentEvent.Open(CRecordset::dynaset, strSQL );
			
			if( !rsCurrentEvent.IsEOF( ) )
			{
				strSQL.Format( html.GetSelectEventBoxDetails(atoi(szSeriesID), rsCurrentEvent.m_EventID, 0, !bIsResultsEntry) );

				CEventETypLocSet rsEvent( &db );
				rsEvent.Open(CRecordset::dynaset, strSQL );

				if( !rsEvent.IsEOF( ) )
				{
					html.StartForm("Event", auth.m_strFrwdLink);
					html.HiddenText("SeriesID", szSeriesID);

					html.SelectEventBox("Event", "EventID", &rsEvent, 0, NULL);
					html.HorizontalRule();
					html.SubmitButton(CHtmlKey::Select);
	
					html.EndForm();
				}
				else
				{
					html << _T("No Events Available for Results Entry.<BR><BR>\r\n");
					html << _T("If Results Entry is required, please contact your System Administrator to configure an Event for Results Entry.<BR>\r\n");
				}

				rsEvent.Close( );
			}
			else
			{
				html << _T("No Events Available for Results Entry.<BR><BR>\r\n");
				html << _T("If Results Entry is required, please contact your System Administrator to configure an Event for Results Entry.<BR>\r\n");
			}
			rsCurrentEvent.Close( );
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

void CWebAthlExtension::ResultsEntryMenu(CHttpServerContext* pCtxt,
										 LPTSTR szSeriesID,
										 LPTSTR szEventID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry | CModule::OpenPreEntry) )
	{
		BOOL bIsResultsEntry = atoi(html.GetCookie(CHtmlKey::IsResultsEntry));

		if( bIsResultsEntry )
		{
			auth.m_strBackLink = CPage::ResultsEntryMenu;
		}

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

		CString strSeriesID;
		CString strEventID;

		if(!_tcscmp(szSeriesID, "none"))
			strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		else
			strSeriesID = szSeriesID;

		if(!_tcscmp(szEventID, "none"))
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

		if( bIsResultsEntry )
		{
			html.WritePageMenuItem(CPage::ResultsEntryPrePostMenu, CHtmlKey::Cancel, 0);
		}
		else
		{
			html.WritePageMenuItem(CPage::DefaultMenu, CHtmlKey::Cancel, 0);
		}


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

			strSQL.Format( "SELECT * FROM Groups WHERE SeriesID = %d AND EventTypeID = %d", rsEvent.m_SeriesID, rsEvent.m_EventTypeID );
			CGroupsSet rsGroups( &db );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if(	!rsGroups.IsEOF( ) )
			{
				if( bIsResultsEntry && auth.HasPermission(CModule::ResultsEntry))
				{
					html.WritePageMenuItem(CPage::SearchPersonForm, (iPreEvent ? ("Add Event Entry") : ("Add Event Result")), 1, CPage::ResultsEntryAddForm);
					html.WritePageMenuItem(CPage::SearchPersonForm, (iPreEvent ? ("Edit/Delete Event Entry") : ("Edit/Delete Event Result")), 1, CPage::ResultsEntryEditForm);
					//html.WritePageMenuItem(CPage::ResultsEntrySelectDivisionForm, (iPreEvent ? ("Quick Add Event Entries") : ("Quick Add Event Results")), 1, CPage::ResultsEntryQuickAddForm);
					//html.WritePageMenuItem(CPage::ResultsEntrySelectDivisionForm, (iPreEvent ? ("Bulk Add Event Entries") : ("Bulk Add Event Results")), 1, CPage::ResultsEntryBulkAddForm);
					html.WritePageMenuItem(CPage::ResultsEntryQuickAddForm, (iPreEvent ? ("Quick Add Event Entries") : ("Quick Add Event Results")), 0);
					html.WritePageMenuItem(CPage::ResultsEntryBulkAddForm, (iPreEvent ? ("Bulk Add Event Entries") : ("Bulk Add Event Results")), 0);
					html.WritePageMenuItem(CPage::ResultsEntryReportForm, "Report", 0);
					html.WritePageMenuItem(CPage::ResultsEntryDeleteForm, (iPreEvent ? ("Bulk Delete Event Entries") : ("Bulk Delete Event Results")), 0);
				}
				else
				{
					if( auth.m_iPersonID > 0 )
					{
						html.WritePageMenuItem(CPage::ResultsEntryAddForm, "Add Your Event Entry", 0);
					}
					else
					{
						html.WritePageMenuItem(CPage::SearchPersonForm, "Add Event Entry", 1, CPage::ResultsEntryAddForm);
					}
				}

				html.EndMenu();
		
				html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), "");

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

				if(iPreEvent)
					strSQL.Format( "SELECT COUNT(*) AS Total FROM PreResults WHERE SeriesID = %s AND EventID = %s", strSeriesID, strEventID );
				else
					strSQL.Format( "SELECT COUNT(*) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s", strSeriesID, strEventID );

				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html.NonEditInt("Participants", rsCount.m_Total );

				html.EndForm();

				rsCount.Close( );
			}
			else 
			{
				html.EndMenu();

				html << _T("No Groups Assigned to this Event Type");
			}

			rsGroups.Close( );
			rsEvent.Close( );
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

void CWebAthlExtension::ResultsEntryAddForm(CHttpServerContext* pCtxt,
										    LPTSTR szPersonID,
										    LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry | CModule::OpenPreEntry) )
	{
		BOOL bIsResultsEntry = atoi(html.GetCookie(CHtmlKey::IsResultsEntry));

		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

		int iPersonID = atoi(szPersonID);

		if( iPersonID < 0 )
			iPersonID = auth.m_iPersonID;

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

		CString strPerformace;
		if(iPreEvent)
			strPerformace.Format("Expected Performace");
		else
			strPerformace.Format("Performace");

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

			CCountResultSet rsGroups( &db );
			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", strSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", strSeriesID );
				CSeriesSet rsSeries( &db );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				strSQL.Format( html.GetNonEditEventBoxDetails(atoi(strEventID)) );

				CEventETypLocSet rsEvent( &db );
				rsEvent.Open(CRecordset::dynaset, strSQL );

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %d", iPersonID );
				CPersonSet rsPerson( &db );
				rsPerson.Open(CRecordset::dynaset, strSQL );

				CString strChestNo;
				int iDivision = 1;

				if(iPreEvent)
					strSQL.Format( "SELECT MAX(DivisionSupposedTo) AS Total FROM PreResults WHERE SeriesID = %s AND EventID = %s ", strSeriesID, strEventID );
				else
					strSQL.Format( "SELECT MAX(DivisionActual) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s ", strSeriesID, strEventID );

				CCountResultSet rsDiv( &db );
				rsDiv.Open(CRecordset::dynaset, strSQL );

				if( !rsDiv.IsFieldNull( &rsDiv.m_Total ) )
				{
					iDivision = rsDiv.m_Total;
				}
				rsDiv.Close( );

				int iGroup = 1;

				CString strAgeCategory;

				int nDateAgeDAY = rsEvent.m_DateAgeDAY;
				int nDateAgeMONTH = rsEvent.m_DateAgeMONTH;
				int nDateAgeYEAR = rsEvent.m_DateAgeYEAR;

				if( rsEvent.IsFieldNull( &rsEvent.m_DateAgeDAY ) ||
					rsEvent.IsFieldNull( &rsEvent.m_DateAgeMONTH ) ||
					rsEvent.IsFieldNull( &rsEvent.m_DateAgeYEAR ) ||
					rsEvent.m_DateAgeDAY == 0 ||
					rsEvent.m_DateAgeMONTH == 0 ||
					rsEvent.m_DateAgeYEAR == 0 ) 
				{
					nDateAgeDAY = rsEvent.m_DateDAY;
					nDateAgeMONTH = rsEvent.m_DateMONTH;
					nDateAgeYEAR = rsEvent.m_DateYEAR;
				}

				int iAgeGroup = CCalculate::GroupAge( 
										CCalculate::YearDiff(
												rsPerson.m_dobDAY,
												rsPerson.m_dobMONTH,
												rsPerson.m_dobYEAR,
												nDateAgeDAY,
												nDateAgeMONTH,
												nDateAgeYEAR),
										strAgeCategory, 
										&prop);

				if( iPreEvent )
				{
					strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND PersonID = %d", strSeriesID, iPersonID );
					CParticipantForSeriesSet rsPforS( &db );
					rsPforS.Open(CRecordset::dynaset, strSQL );

					if(!rsPforS.IsEOF( ) )
					{
						iDivision = rsPforS.m_DivisionSupposedTo;
						iGroup = rsPforS.m_GroupIDSupposedTo;
					}
					rsPforS.Close( );
				}
				else // postEvent //
				{
					strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %s AND EventID = %s AND PersonID = %d", strSeriesID, strEventID, iPersonID );
					CPreResultsSet rsPreRes( &db );
					rsPreRes.Open(CRecordset::dynaset, strSQL );

					if(!rsPreRes.IsEOF( ) )
					{
						strChestNo = rsPreRes.m_ChestNumber;
						iDivision = rsPreRes.m_DivisionSupposedTo;
						iGroup = rsPreRes.m_GroupIDSupposedTo;
						iAgeGroup = rsPreRes.m_AgeGroup;
					}
					else
					{
						strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND PersonID = %d", strSeriesID, iPersonID );
						CParticipantForSeriesSet rsPforS( &db );
						rsPforS.Open(CRecordset::dynaset, strSQL );

						if(!rsPforS.IsEOF( ) )
						{
							iDivision = rsPforS.m_DivisionSupposedTo;
							iGroup = rsPforS.m_GroupIDSupposedTo;
						}
						rsPforS.Close( );
					}
					rsPreRes.Close( );
				}


				html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), CPage::ResultsEntryAddExecute);

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				html.HiddenText("SeriesID", strSeriesID);

				html.NonEditEvent( 
					"Event", 
					rsEvent.m_EventNo,
					rsEvent.m_LocationDescription,
					rsEvent.m_EventDescription );

				html.HiddenText("EventID", strEventID);

				html.NonEditDateBox(
					"Date",
					rsEvent.m_DateDAY,
					rsEvent.m_DateMONTH,
					rsEvent.m_DateYEAR);

				html.HorizontalRule();

				html.NonEditText("Participant",
					(rsPerson.m_LastName + ", " + rsPerson.m_FirstName) );

				html.HiddenInt("PersonID", iPersonID);

				html.NonEditText("AgeCategory", strAgeCategory );

				if(rsEvent.m_Timed > 0)
				{
					html.TimeBox(strPerformace, "GrossPerformance", 0, 0, 0);
				}
				else
				{
					html.HiddenInt("GrossPerformanceHOUR", 0);
					html.HiddenInt("GrossPerformanceMIN", 0);
					html.EditFloatBox(strPerformace, "GrossPerformanceSEC", 0);
				}

				if(iPreEvent)
				{
					html.HiddenInt("Place", 0);
				}
				else
				{
					int iPlaceCounter = 1;

					strSQL.Format( "SELECT MAX(Place) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s AND DivisionActual = %d ", strSeriesID, strEventID, iDivision );
					CCountResultSet rsPlace( &db );
					rsPlace.Open(CRecordset::dynaset, strSQL );

					if( !rsPlace.IsFieldNull( &rsPlace.m_Total ) )
					{
						iPlaceCounter = rsPlace.m_Total +1;
					}
					rsPlace.Close( );
					
					html.EditIntBox("Place", "Place", iPlaceCounter );
				}


				//html.EditIntBox("Group", "GroupID", iGroup);
				html.StartSelectBox("Group", "GroupID");
				for( int g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iGroup) );
				}
				html.EndSelectBox();

				html.EditIntBox("Division", "Division", iDivision);				
				html.EditIntBox("Age Group", "AgeGroup", iAgeGroup);				

				html.EditTextBoxLarge("Chest Number", "ChestNumber", strChestNo);

				if( iPreEvent )
				{
					html.HiddenInt("Points", 0);

					html.HiddenInt("NewGroupID", 0);
					html.HiddenText("NewGroupMessage", "");
				}
				else
				{
					html.HorizontalRule();
					html.EditIntBox("Points", "Points", 0);				

					//html.EditIntBox("New Group", "NewGroupID", 0);				
					html.StartSelectBox("New Group", "NewGroupID");
					for( int g = 0 ; g <= rsGroups.m_Total ; g++ )
					{
						html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(0) );
					}
					html.EndSelectBox();

					html.EditTextBoxLarge("Comment", "NewGroupMessage", "");
				}


				html.HorizontalRule();
				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);

				html.EndForm();

				rsSeries.Close( );
				rsEvent.Close( );
				rsPerson.Close( );
			}
			else
			{
				html << _T("No Groups Available\r\n");
			}
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

void CWebAthlExtension::ResultsEntryAddExecute(CHttpServerContext* pCtxt,
											   LPTSTR szSeriesID,
											   LPTSTR szEventID,
											   LPTSTR szPersonID,
											   LPTSTR szGrossPerformanceHOUR,
											   LPTSTR szGrossPerformanceMIN,
											   LPTSTR szGrossPerformanceSEC,
											   LPTSTR szPlace,
											   LPTSTR szGroupID,
											   LPTSTR szDivision,
											   LPTSTR szAgeGroup,
											   LPTSTR szChestNumber,
											   LPTSTR szPoints,
											   LPTSTR szNewGroupID,
											   LPTSTR szNewGroupMessage,
											   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry | CModule::OpenPreEntry) )
	{
		BOOL bIsResultsEntry = atoi(html.GetCookie(CHtmlKey::IsResultsEntry));

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		if( bIsResultsEntry )
			html.WritePageMenuItem(auth.m_strBackLink, "Results Menu", 0);
		else
			html.WritePageMenuItem(auth.m_strBackLink, "Main Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			if(iPreEvent)
			{
				strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = 0" );
				CPreResultsSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.AddNew( );

				rs.m_SeriesID = atoi(szSeriesID);
				rs.m_EventID = atoi(szEventID);
				rs.m_PersonID = atoi(szPersonID);
				//rs.m_Place = atoi(szPlace);
				rs.m_GrossPerformanceHOUR = atoi(szGrossPerformanceHOUR);
				rs.m_GrossPerformanceMIN = atoi(szGrossPerformanceMIN);
				rs.m_GrossPerformanceSEC = atof(szGrossPerformanceSEC);
				rs.m_GroupIDSupposedTo = atoi(szGroupID);
				rs.m_DivisionSupposedTo = atoi(szDivision);
				if( _tcslen(szAgeGroup) > 0 )
					rs.m_AgeGroup = atoi(szAgeGroup);
				if( _tcslen(szChestNumber) )
					rs.m_ChestNumber = szChestNumber;

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Result for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}

				rs.Close( );
			}
			else // postEvent //
			{
				strSQL.Format( "SELECT * FROM PostResults WHERE SeriesID = 0" );
				CPostResultsSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.AddNew( );

				rs.m_SeriesID = atoi(szSeriesID);
				rs.m_EventID = atoi(szEventID);
				rs.m_PersonID = atoi(szPersonID);
				rs.m_Place = atoi(szPlace);
				rs.m_GrossPerformanceHOUR = atoi(szGrossPerformanceHOUR);
				rs.m_GrossPerformanceMIN = atoi(szGrossPerformanceMIN);
				rs.m_GrossPerformanceSEC = atof(szGrossPerformanceSEC);
				rs.m_GroupIDActual = atoi(szGroupID);
				rs.m_DivisionActual = atoi(szDivision);
				if( _tcslen(szAgeGroup) > 0 )
					rs.m_AgeGroup = atoi(szAgeGroup);
				if( _tcslen(szChestNumber) > 0 )
					rs.m_ChestNumber = szChestNumber;

				if( atoi(szPoints) )
					rs.m_Points = atoi(szPoints);

				if( atoi(szNewGroupID) )
					rs.m_NewGroupID = atoi(szNewGroupID);

				if( _tcslen(szNewGroupMessage) > 0 )
					rs.m_NewGroupMessage = szNewGroupMessage;

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Result for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}

				rs.Close( );
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

void CWebAthlExtension::ResultsEntryEditForm(CHttpServerContext* pCtxt,
											 LPTSTR szPersonID,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

		CString strPerformace;
		if(iPreEvent)
			strPerformace.Format("Expeced Performace");
		else
			strPerformace.Format("Performace");


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

			CCountResultSet rsGroups( &db );
			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", strSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", strSeriesID );
				CSeriesSet rsSeries( &db );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				strSQL.Format( html.GetNonEditEventBoxDetails(atoi(strEventID)) );

				CEventETypLocSet rsEvent( &db );
				rsEvent.Open(CRecordset::dynaset, strSQL );

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s", szPersonID );
				CPersonSet rsPerson( &db );
				rsPerson.Open(CRecordset::dynaset, strSQL );

				CString strChestNo;
				int iDivision = 0;
				int iGroup = 0;
				int iPerformanceHOUR = 0;
				int iPerformanceMIN = 0;
				double dPerformanceSEC = 0;
				int iPlace = 0;

				int iAgeGroup = 0;

				int iNewGroupID = 0;
				int iPoints = 0;
				CString strNewGroupMessage;


				BOOL bFound = FALSE;

				if(iPreEvent)
				{
					strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %s AND EventID = %s AND PersonID = %s", strSeriesID, strEventID, szPersonID );
					CPreResultsSet rsResults( &db );
					rsResults.Open(CRecordset::dynaset, strSQL );

					if(!rsResults.IsEOF( ) )
					{
						bFound = TRUE;
						strChestNo = rsResults.m_ChestNumber;
						iDivision = rsResults.m_DivisionSupposedTo;
						iGroup = rsResults.m_GroupIDSupposedTo;
						iPerformanceHOUR = rsResults.m_GrossPerformanceHOUR;
						iPerformanceMIN = rsResults.m_GrossPerformanceMIN;
						dPerformanceSEC = rsResults.m_GrossPerformanceSEC;
						iPlace = rsResults.m_Place;
						iAgeGroup = rsResults.m_AgeGroup;
					}
					rsResults.Close( );
				}
				else
				{
					strSQL.Format( "SELECT * FROM PostResults WHERE SeriesID = %s AND EventID = %s AND PersonID = %s", strSeriesID, strEventID, szPersonID );
					CPostResultsSet rsResults( &db );
					rsResults.Open(CRecordset::dynaset, strSQL );

					if(!rsResults.IsEOF( ) )
					{
						bFound = TRUE;
						strChestNo = rsResults.m_ChestNumber;
						iDivision = rsResults.m_DivisionActual;
						iGroup = rsResults.m_GroupIDActual;
						iPerformanceHOUR = rsResults.m_GrossPerformanceHOUR;
						iPerformanceMIN = rsResults.m_GrossPerformanceMIN;
						dPerformanceSEC = rsResults.m_GrossPerformanceSEC;
						iPlace = rsResults.m_Place;
						iAgeGroup = rsResults.m_AgeGroup;

						iPoints = rsResults.m_Points;
						iNewGroupID = rsResults.m_NewGroupID;
						strNewGroupMessage = rsResults.m_NewGroupMessage;
					}
					rsResults.Close( );
				}

				html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), CPage::ResultsEntryEditExecute);

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				html.HiddenText("SeriesID", strSeriesID);

				html.NonEditEvent(
					"Event", 
					rsEvent.m_EventNo,
					rsEvent.m_LocationDescription,
					rsEvent.m_EventDescription );

				html.HiddenText("EventID", strEventID);

				html.NonEditDateBox(
					"Date",
					rsEvent.m_DateDAY,
					rsEvent.m_DateMONTH,
					rsEvent.m_DateYEAR);

				html.HorizontalRule();

				html.NonEditText("Participant",
					(rsPerson.m_LastName + ", " + rsPerson.m_FirstName) );

				html.HiddenText("PersonID", szPersonID);

				if(bFound)
				{
					if(rsEvent.m_Timed > 0)
					{
						html.TimeBox(strPerformace, "GrossPerformance",
							iPerformanceHOUR,
							iPerformanceMIN,
							dPerformanceSEC);
					}
					else
					{
						html.HiddenInt("GrossPerformanceHOUR", iPerformanceHOUR);
						html.HiddenInt("GrossPerformanceMIN", iPerformanceMIN);
						html.EditFloatBox(strPerformace, "GrossPerformanceSEC", dPerformanceSEC);
					}

					if(iPreEvent)
						html.HiddenInt("Place", iPlace);
					else
						html.EditIntBox("Place", "Place", iPlace);

					//html.EditIntBox("Group", "GroupID", iGroup);
					html.StartSelectBox("Group", "GroupID");
					for( int g = 1 ; g <= rsGroups.m_Total ; g++ )
					{
						html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iGroup) );
					}
					html.EndSelectBox();

					html.EditIntBox("Division", "Division", iDivision);	

					html.EditIntBox("Age Group", "AgeGroup", iAgeGroup);				

					html.EditTextBoxLarge("Chest Number", "ChestNumber", strChestNo);

					if( iPreEvent )
					{
						html.HiddenInt("Points", iPoints);

						html.HiddenInt("NewGroupID", iNewGroupID);
						html.HiddenText("NewGroupMessage", strNewGroupMessage);
					}
					else
					{
						html.HorizontalRule();
						html.EditIntBox("Points", "Points", iPoints);				

						//html.EditIntBox("New Group", "NewGroupID", iNewGroupID);
						html.StartSelectBox("New Group", "NewGroupID");
						for( int g = 0 ; g <= rsGroups.m_Total ; g++ )
						{
							html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iNewGroupID) );
						}
						html.EndSelectBox();

						html.EditTextBoxLarge("Comment", "NewGroupMessage", strNewGroupMessage);
					}

					html.HorizontalRule();
					html.ResetButton();
					html.SubmitButton(CHtmlKey::Save);
					html.SubmitButton(CHtmlKey::Delete);
				}
				else
				{
					html.NonEditText("" ,"Participant not Found");
				}
				html.EndForm();

				rsSeries.Close( );
				rsEvent.Close( );
				rsPerson.Close( );
			}
			else
			{
				html << _T("No Groups Available\r\n");
			}
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

void CWebAthlExtension::ResultsEntryEditExecute(CHttpServerContext* pCtxt,
												LPTSTR szSeriesID,
												LPTSTR szEventID,
												LPTSTR szPersonID,
												LPTSTR szGrossPerformanceHOUR,
												LPTSTR szGrossPerformanceMIN,
												LPTSTR szGrossPerformanceSEC,
												LPTSTR szPlace,
												LPTSTR szGroupID,
												LPTSTR szDivision,
												LPTSTR szAgeGroup,
												LPTSTR szChestNumber,
												LPTSTR szPoints,
												LPTSTR szNewGroupID,
												LPTSTR szNewGroupMessage,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Results Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			if(iPreEvent)
			{
				strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %s AND EventID = %s AND PersonID = %s", szSeriesID, szEventID, szPersonID );
				CPreResultsSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				if (!_tcscmp( szSubmit, CHtmlKey::Save ))
				{
					rs.Edit( );

					rs.m_SeriesID = atoi(szSeriesID);
					rs.m_EventID = atoi(szEventID);
					rs.m_PersonID = atoi(szPersonID);
//					rs.m_Place = atoi(szPlace);
					rs.m_GrossPerformanceHOUR = atoi(szGrossPerformanceHOUR);
					rs.m_GrossPerformanceMIN = atoi(szGrossPerformanceMIN);
					rs.m_GrossPerformanceSEC = atof(szGrossPerformanceSEC);
					rs.m_GroupIDSupposedTo = atoi(szGroupID);
					rs.m_DivisionSupposedTo = atoi(szDivision);
					rs.m_AgeGroup = atoi(szAgeGroup);
					if( _tcslen(szChestNumber) )
						rs.m_ChestNumber = szChestNumber;
					else
						rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

					if( !rs.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
					if( !rs.Update( ) )
						html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
					else
					{
						html << _T("Modified Result for Person, <B>");
						html << _T(szPersonID);
						html << _T("</B><BR>\r\n");
					}
				}
				else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
				{
					rs.Delete( );
					html << _T("Deleted Result for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}
				rs.Close( );
			}
			else // postEvent
			{
				strSQL.Format( "SELECT * FROM PostResults WHERE SeriesID = %s AND EventID = %s AND PersonID = %s", szSeriesID, szEventID, szPersonID );
				CPostResultsSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				if (!_tcscmp( szSubmit, CHtmlKey::Save ))
				{
					rs.Edit( );

					rs.m_SeriesID = atoi(szSeriesID);
					rs.m_EventID = atoi(szEventID);
					rs.m_PersonID = atoi(szPersonID);
					rs.m_Place = atoi(szPlace);
					rs.m_GrossPerformanceHOUR = atoi(szGrossPerformanceHOUR);
					rs.m_GrossPerformanceMIN = atoi(szGrossPerformanceMIN);
					rs.m_GrossPerformanceSEC = atof(szGrossPerformanceSEC);
					rs.m_GroupIDActual = atoi(szGroupID);
					rs.m_DivisionActual = atoi(szDivision);
					rs.m_AgeGroup = atoi(szAgeGroup);
					if( _tcslen(szChestNumber) )
						rs.m_ChestNumber = szChestNumber;
					else
						rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

					if( atoi(szPoints) )
						rs.m_Points = atoi(szPoints);
					else
						rs.SetFieldNull( &rs.m_Points, TRUE );

					if( atoi(szNewGroupID) )
						rs.m_NewGroupID = atoi(szNewGroupID);
					else
						rs.SetFieldNull( &rs.m_NewGroupID, TRUE );

					if( _tcslen(szNewGroupMessage) > 0 )
						rs.m_NewGroupMessage = szNewGroupMessage;
					else
						rs.SetFieldNull( &rs.m_NewGroupMessage, TRUE );

					if( !rs.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
					if( !rs.Update( ) )
						html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
					else
					{
						html << _T("Modified Result for Person, <B>");
						html << _T(szPersonID);
						html << _T("</B><BR>\r\n");
					}
				}
				else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
				{
					rs.Delete( );
					html << _T("Deleted Result for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}
				rs.Close( );
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

void CWebAthlExtension::ResultsEntryReportForm(CHttpServerContext* pCtxt,
											   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

		auth.m_strFrwdLink.Empty();

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

			int iTimed;

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", strSeriesID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( html.GetNonEditEventBoxDetails(atoi(strEventID)) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );

			html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), "");

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

			iTimed = rsEvent.m_Timed ;

			if(iPreEvent)
				strSQL.Format( "SELECT COUNT(*) AS Total FROM PreResults WHERE SeriesID = %s AND EventID = %s", strSeriesID, strEventID );
			else
				strSQL.Format( "SELECT COUNT(*) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s", strSeriesID, strEventID );

			CCountResultSet rsCount( &db );
			rsCount.Open(CRecordset::dynaset, strSQL );

			html.NonEditInt("Participants", rsCount.m_Total );

			rsCount.Close( );
			rsEvent.Close( );
			rsSeries.Close( );

			html.EndForm();




			if(iPreEvent)
			{
				CString strSQLSort;
				if(iTimed)
					strSQLSort.Format(" , GrossPerformanceHOUR ASC, GrossPerformanceMIN ASC, GrossPerformanceSEC ASC ");
				else
					strSQLSort.Format(" , GrossPerformanceSEC DESC ");

				CQuickReportSet rsResults( &db );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETQUICKREPORT);

				strSQL.Format( strSQLtmp, strSeriesID, strEventID );

				strSQL += strSQLSort;

				rsResults.Open(CRecordset::dynaset, strSQL );

				if( !rsResults.IsEOF( ) )
				{
					html.StartForm( (strResultsEntry + " Event Report"), auth.m_strFrwdLink);

					CStringArray* strColumn;
					strColumn = new CStringArray;

					strColumn->Add( "Division" );
					strColumn->Add( "PersonID" );
					strColumn->Add( "Name" );
					strColumn->Add( "AgeGroup" );
					strColumn->Add( "Performance" );
					strColumn->Add( "Group" );
					strColumn->Add( "ChestNumber" );

					html.HtmlTable(strColumn);
					html.HorizontalRule( strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					while( !rsResults.IsEOF( ) )
					{
						strColumn->Add( _T(CConvert::itoa(rsResults.m_Division)) );
						strColumn->Add( _T(CConvert::itoa(rsResults.m_PersonID)) );
						strColumn->Add( _T(rsResults.m_LastName + ", " + rsResults.m_FirstName) );
						strColumn->Add( _T(rsResults.m_Sex + CConvert::itoa(rsResults.m_AgeGroup)) );

						strColumn->Add( _T(CFormat::FormatPerf(iTimed,
												   rsResults.m_GrossPerformanceHOUR, 
												   rsResults.m_GrossPerformanceMIN,
												   rsResults.m_GrossPerformanceSEC) ));

						strColumn->Add( _T( "<p align=\"right\">" + CConvert::itoa(rsResults.m_GroupID) ) );
						strColumn->Add( _T( "<p align=\"right\">" + rsResults.m_ChestNumber) );

						html.HtmlTable(strColumn);

						rsResults.MoveNext( );

						strColumn->RemoveAll( );
					}

					delete strColumn;

					html.EndForm();
				}
				else
				{
					html << _T("No Results Available\r\n");
				}

				rsResults.Close( );
			}
			else // post Event // 
			{
				CString strSQLSort;
				if(iTimed)
					strSQLSort.Format(" , GrossPerformanceHOUR ASC, GrossPerformanceMIN ASC, GrossPerformanceSEC ASC ");
				else
					strSQLSort.Format(" , GrossPerformanceSEC DESC ");

				strSQLSort += _T(" , Place ");

				CQuickReportSet rsResults( &db );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETQUICKPOSTREPORT);

				strSQL.Format( strSQLtmp, strSeriesID, strEventID );

				strSQL += strSQLSort;

				rsResults.Open(CRecordset::dynaset, strSQL );

				if( !rsResults.IsEOF( ) )
				{
					html.StartForm( (strResultsEntry + " Event Report"), auth.m_strFrwdLink);

					CStringArray* strColumn;
					strColumn = new CStringArray;

					strColumn->Add( "Division" );
					strColumn->Add( "Place" );
					strColumn->Add( "PersonID" );
					strColumn->Add( "Name" );
					strColumn->Add( "AgeGroup" );
					strColumn->Add( "Performance" );
					strColumn->Add( "Group" );
					strColumn->Add( "ChestNumber" );
					strColumn->Add( "Points" );
					strColumn->Add( "NewGroupID" );
					strColumn->Add( "NewGroupMessage" );

					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					while( !rsResults.IsEOF( ) )
					{
						strColumn->Add( _T(CConvert::itoa(rsResults.m_Division)) );
						strColumn->Add( _T(CConvert::itoa(rsResults.m_Place)) );
						strColumn->Add( _T(CConvert::itoa(rsResults.m_PersonID)) );
						strColumn->Add( _T(rsResults.m_LastName + ", " + rsResults.m_FirstName) );
						strColumn->Add( _T(rsResults.m_Sex + CConvert::itoa(rsResults.m_AgeGroup)) );

						strColumn->Add( _T(CFormat::FormatPerf(iTimed,
												   rsResults.m_GrossPerformanceHOUR, 
												   rsResults.m_GrossPerformanceMIN,
												   rsResults.m_GrossPerformanceSEC) ));

						strColumn->Add( _T( "<p align=\"right\">" + CConvert::itoa(rsResults.m_GroupID) ) );
						strColumn->Add( _T( "<p align=\"right\">" + rsResults.m_ChestNumber) );

						strColumn->Add( _T( "<p align=\"right\">" + CConvert::itoa(rsResults.m_Points) ) );
						strColumn->Add( _T( "<p align=\"right\">" + CConvert::itoa(rsResults.m_NewGroupID) ) );
						strColumn->Add( _T( rsResults.m_NewGroupMessage ) );

						html.HtmlTable(strColumn);

						rsResults.MoveNext( );

						strColumn->RemoveAll( );
					}

					delete strColumn;

					html.EndForm();
				}
				else
				{
					html << _T("No Results Available\r\n");
				}

				rsResults.Close( );
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

#define MAX_PLACES 10

void CWebAthlExtension::ResultsEntryQuickAddForm(CHttpServerContext* pCtxt,
											     LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);

		int iPreEvent = _tcscmp("Post", strResultsEntry);

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


			int iTimed;
			strSQL.Format( "SELECT EventType.Timed AS Result FROM Event, EventType WHERE Event.EventID = %s AND Event.EventTypeID = EventType.EventTypeID", strEventID );

			CBoolResultSet rsBool( &db );
			rsBool.Open(CRecordset::dynaset, strSQL );

			if(!rsBool.IsEOF() && !rsBool.IsFieldNull(&rsBool.m_Result) )
			{
				iTimed = rsBool.m_Result;
			}

			rsBool.Close( );


			CCountResultSet rsMax( &db );

			int iDivision = 1;
			{
				if(iPreEvent)
					strSQL.Format( "SELECT MAX(DivisionSupposedTo) AS Total FROM PreResults WHERE SeriesID = %s AND EventID = %s ", strSeriesID, strEventID );
				else
					strSQL.Format( "SELECT MAX(DivisionActual) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s ", strSeriesID, strEventID );

				rsMax.Open(CRecordset::dynaset, strSQL );

				if( !rsMax.IsFieldNull( &rsMax.m_Total ) )
				{
					iDivision = rsMax.m_Total;
				}
				rsMax.Close( );
			}

			int iPlace = 0;
			if(!iPreEvent)
			{
				strSQL.Format( "SELECT MAX(Place) AS Total FROM PostResults WHERE SeriesID = %s AND EventID = %s AND DivisionActual = ( SELECT MAX(DivisionActual) FROM PostResults WHERE SeriesID = %s AND EventID = %s ) ", strSeriesID, strEventID, strSeriesID, strEventID );
				rsMax.Open(CRecordset::dynaset, strSQL );

				if( !rsMax.IsFieldNull( &rsMax.m_Total ) )
				{
					iPlace = rsMax.m_Total;
				}
				rsMax.Close( );
			}

			html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), CPage::ResultsEntryQuickAddExecute);
			html.HiddenText("SeriesID", strSeriesID);
			html.HiddenText("EventID", strEventID);

			html.ResultsEntryTableHeader(
				iPreEvent,
				"Division",
				(iPreEvent ? "" : "Place"),
				"PersonID",
				"AgeGroup",
				(iPreEvent ? "Expected Performance" : "Performance"),
				"Group",
				"Chest Number",
				(iPreEvent ? "" : "Points"),
				(iPreEvent ? "" : "NewGroup"),
				(iPreEvent ? "" : "NewGroupMessage"));

			for( int i = 1; i <= MAX_PLACES ; i++ )
			{
				if(!iPreEvent)
					iPlace++;

				html.ResultsEntryTable(iTimed, iPreEvent, iDivision, iPlace, 0, 0, 0, 0, 0.0, 0, "", 0, 0, "");
			}

			html.HorizontalRule(10);
			html.SubmitButton(CHtmlKey::Save, 10);

			html.EndForm();

			db.Close( );

			html << _T("<p>Note: An Empty <B>Division</B> or a Division of <B>0</B> will attempt to auto-select that Person's Division. ")
				 << _T("Failure to auto-select will result in that Person being assigned to Division <B>1</B>. ")
				 << _T("A non-zero Division will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: An Empty <B>AgeGroup</B> or a AgeGroup of <B>0</B> will attempt to auto-select that Person's AgeGroup. ")
				 << _T("Failure to auto-select will result in that Person being assigned to AgeGroup <B>")
				 << prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::NullDoB)
				 << _T("</B>. ")
				 << _T("A non-zero AgeGroup will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: An Empty <B>Group</B> or a Group of <B>0</B> will attempt to auto-select that Person's Group. ")
				 << _T("Failure to auto-select will result in that Person being assigned to Group <B>1</B>. ")
				 << _T("A non-zero Group will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: <B>Points</B> will only be Processed if there are no <B>Pointscore</B> Rules for the Series.</p>\r\n");

			html << _T("<p>Note: <B>NewGroup</B> and <B>NewGroupMessage</B> will only be Processed if there are no <B>Regroup</B> Rules for the Series.</p>\r\n");
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

void CWebAthlExtension::ResultsEntryQuickAddExecute(CHttpServerContext* pCtxt,
												    LPTSTR szSeriesID,
												    LPTSTR szEventID,
												    LPTSTR szDivisionList,
												    LPTSTR szPlaceList,
												    LPTSTR szPersonIDList,
												    LPTSTR szAgeGroupList,
												    LPTSTR szPerformanceHOURList,
												    LPTSTR szPerformanceMINList,
												    LPTSTR szPerformanceSECList,
												    LPTSTR szGroupIDList,
												    LPTSTR szChestNumberList,
												    LPTSTR szPointsList,
												    LPTSTR szNewGroupIDList,
												    LPTSTR szNewGroupMessageList,
												    LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Results Menu", 0);

		html.EndMenu();


		CString strDivisionList = CString(szDivisionList);
		CStringArray* strDivisionItems = new CStringArray();

		CString strPlaceList = CString(szPlaceList);
		CStringArray* strPlaceItems = new CStringArray();

		CString strPersonIDList = CString(szPersonIDList);
		CStringArray* strPersonIDItems = new CStringArray();

		CString strAgeGroupList = CString(szAgeGroupList);
		CStringArray* strAgeGroupItems = new CStringArray();

		CString strPerformanceHOURList = CString(szPerformanceHOURList);
		CStringArray* strPerformanceHOURItems = new CStringArray();

		CString strPerformanceMINList = CString(szPerformanceMINList);
		CStringArray* strPerformanceMINItems = new CStringArray();

		CString strPerformanceSECList = CString(szPerformanceSECList);
		CStringArray* strPerformanceSECItems = new CStringArray();

		CString strGroupIDList = CString(szGroupIDList);
		CStringArray* strGroupIDItems = new CStringArray();

		CString strChestNumberList = CString(szChestNumberList);
		CStringArray* strChestNumberItems = new CStringArray();

		CString strPointsList = CString(szPointsList);
		CStringArray* strPointsItems = new CStringArray();

		CString strNewGroupIDList = CString(szNewGroupIDList);
		CStringArray* strNewGroupIDItems = new CStringArray();

		CString strNewGroupMessageList = CString(szNewGroupMessageList);
		CStringArray* strNewGroupMessageItems = new CStringArray();

		CCSV csv(CWebAthlExtension::chIsapiDelimiter);

		csv.GetItems(strDivisionItems, &strDivisionList);
		csv.GetItems(strPlaceItems, &strPlaceList);
		csv.GetItems(strPersonIDItems, &strPersonIDList);
		csv.GetItems(strAgeGroupItems, &strAgeGroupList);
		csv.GetItems(strPerformanceHOURItems, &strPerformanceHOURList);
		csv.GetItems(strPerformanceMINItems, &strPerformanceMINList);
		csv.GetItems(strPerformanceSECItems, &strPerformanceSECList);
		csv.GetItems(strGroupIDItems, &strGroupIDList);
		csv.GetItems(strChestNumberItems, &strChestNumberList);
		csv.GetItems(strPointsItems, &strPointsList);
		csv.GetItems(strNewGroupIDItems, &strNewGroupIDList);
		csv.GetItems(strNewGroupMessageItems, &strNewGroupMessageList);

		int nPlaceItems = strPlaceItems->GetSize( );
		int nDivisionItems = strDivisionItems->GetSize( );
		int nPersonIDItems = strPersonIDItems->GetSize( );
		int nAgeGroupItems = strAgeGroupItems->GetSize( );
		int nPerformanceHOURItems = strPerformanceHOURItems->GetSize( );
		int nPerformanceMINItems = strPerformanceMINItems->GetSize( );
		int nPerformanceSECItems = strPerformanceSECItems->GetSize( );
		int nGroupIDItems = strGroupIDItems->GetSize( );
		int nChestNumberItems = strChestNumberItems->GetSize( );
		int nPointsItems = strPointsItems->GetSize( );
		int nNewGroupIDItems = strNewGroupIDItems->GetSize( );
		int nNewGroupMessageItems = strNewGroupMessageItems->GetSize( );


		if( (nDivisionItems == nPlaceItems) && 
			(nDivisionItems == nPersonIDItems) && 
			(nDivisionItems == nAgeGroupItems) && 
			(nDivisionItems == nPerformanceHOURItems) &&  
			(nDivisionItems == nPerformanceMINItems) &&  
			(nDivisionItems == nPerformanceSECItems) &&  
			(nDivisionItems == nGroupIDItems) &&  
			(nDivisionItems == nChestNumberItems) &&
			(nDivisionItems == nPointsItems) &&  
			(nDivisionItems == nNewGroupIDItems) &&  
			(nDivisionItems == nNewGroupMessageItems)   
		)
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				int iTimed;
				strSQL.Format( "SELECT EventType.Timed AS Result FROM Event, EventType WHERE Event.EventID = %s AND Event.EventTypeID = EventType.EventTypeID", szEventID );

				CBoolResultSet rsBool( &db );
				rsBool.Open(CRecordset::dynaset, strSQL );

				if(!rsBool.IsEOF() && !rsBool.IsFieldNull(&rsBool.m_Result) )
				{
					iTimed = rsBool.m_Result;
				}
				
				rsBool.Close( );

				int iSeriesID = atoi(szSeriesID);
				int iEventID = atoi(szEventID);

				for( int nIndex = 0; nIndex < nPlaceItems ; nIndex++ )
				{
					CString strDivision = strDivisionItems->GetAt(nIndex);
					int iDivision = atoi(strDivision);

					CString strPlace = strPlaceItems->GetAt(nIndex);
					int iPlace = atoi(strPlace);

					CString strPersonID = strPersonIDItems->GetAt(nIndex);
					int iPersonID = atoi(strPersonID);

					CString strAgeGroup = strAgeGroupItems->GetAt(nIndex);
					int iAgeGroup = atoi(strAgeGroup);

					CString strPerformanceHOUR = strPerformanceHOURItems->GetAt(nIndex);
					int iGrossPerformanceHOUR = atoi(strPerformanceHOUR);

					CString strPerformanceMIN = strPerformanceMINItems->GetAt(nIndex);
					int iGrossPerformanceMIN = atoi(strPerformanceMIN);

					CString strPerformanceSEC = strPerformanceSECItems->GetAt(nIndex);
					double dGrossPerformanceSEC = atof(strPerformanceSEC);

					CString strGroupID = strGroupIDItems->GetAt(nIndex);
					int iGroupID = atoi(strGroupID);

					CString strChestNumber = strChestNumberItems->GetAt(nIndex);

					CString strPoints = strPointsItems->GetAt(nIndex);
					int iPoints = atoi(strPoints);

					CString strNewGroupID = strNewGroupIDItems->GetAt(nIndex);
					int iNewGroupID = atoi(strNewGroupID);

					CString strNewGroupMessage = strNewGroupMessageItems->GetAt(nIndex);

					try
					{
						strSQL.Format( "SELECT * FROM Person WHERE PersonID = %d", iPersonID );
						CPersonSet rsPerson( &db );
						rsPerson.Open(CRecordset::dynaset, strSQL );

						if( !rsPerson.IsEOF( ) )
						{
							if( iAgeGroup < 1 )
							{
								strSQL.Format( "SELECT * FROM Event WHERE EventID = %d ", iEventID );
								CEventSet rsEvent( &db );
								rsEvent.Open(CRecordset::dynaset, strSQL );

								int nDateAgeDAY = rsEvent.m_DateAgeDAY;
								int nDateAgeMONTH = rsEvent.m_DateAgeMONTH;
								int nDateAgeYEAR = rsEvent.m_DateAgeYEAR;

								if( rsEvent.IsFieldNull( &rsEvent.m_DateAgeDAY ) ||
									rsEvent.IsFieldNull( &rsEvent.m_DateAgeMONTH ) ||
									rsEvent.IsFieldNull( &rsEvent.m_DateAgeYEAR ) ||
									rsEvent.m_DateAgeDAY == 0 ||
									rsEvent.m_DateAgeMONTH == 0 ||
									rsEvent.m_DateAgeYEAR == 0 ) 
								{
									nDateAgeDAY = rsEvent.m_DateDAY;
									nDateAgeMONTH = rsEvent.m_DateMONTH;
									nDateAgeYEAR = rsEvent.m_DateYEAR;
								}

								CString strAgeCategory;
								iAgeGroup = CCalculate::GroupAge(
												CCalculate::YearDiff(rsPerson.m_dobDAY,
														 rsPerson.m_dobMONTH,
														 rsPerson.m_dobYEAR,
														 nDateAgeDAY,
														 nDateAgeMONTH,
														 nDateAgeYEAR),
												strAgeCategory,
												&prop);
								rsEvent.Close( );
							}

							if( iGroupID < 1 || iDivision < 1 )
							{
								if(iPreEvent)
								{
									strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %d AND PersonID = %d", iSeriesID, iPersonID );
									CParticipantForSeriesSet rsPforS( &db );
									rsPforS.Open(CRecordset::dynaset, strSQL );

									if(!rsPforS.IsEOF( ) )
									{
										if( iDivision < 1 )
											iDivision = rsPforS.m_DivisionSupposedTo;

										if( iGroupID < 1 )
											iGroupID = rsPforS.m_GroupIDSupposedTo;
									}
									rsPforS.Close( );
								}
								else // postEvent //
								{
									strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d", iSeriesID, iEventID, iPersonID );
									CPreResultsSet rsPreRes( &db );
									rsPreRes.Open(CRecordset::dynaset, strSQL );

									if(!rsPreRes.IsEOF( ) )
									{
										//strChestNo = rsPreRes.m_ChestNumber;

										if( iDivision < 1 )
											iDivision = rsPreRes.m_DivisionSupposedTo;

										if( iGroupID < 1 )
											iGroupID = rsPreRes.m_GroupIDSupposedTo;
									}
									else
									{
										strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %d AND PersonID = %d", iSeriesID, iPersonID );
										CParticipantForSeriesSet rsPforS( &db );
										rsPforS.Open(CRecordset::dynaset, strSQL );

										if(!rsPforS.IsEOF( ) )
										{
											if( iDivision < 1 )
												iDivision = rsPforS.m_DivisionSupposedTo;

											if( iGroupID < 1 )
												iGroupID = rsPforS.m_GroupIDSupposedTo;
										}
										rsPforS.Close( );
									}
									rsPreRes.Close( );
								}
							}

							if( iGroupID < 1 )
								iGroupID = 1;

							if( iDivision < 1 )
								iDivision = 1;


							if(iPreEvent)
							{
								strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d ", iSeriesID, iEventID, iPersonID );
								CPreResultsSet rs( &db );
								rs.Open(CRecordset::dynaset, strSQL );

								bool bEdit;

								if( rs.IsEOF( ) )
								{
									rs.AddNew( );
									bEdit = false;
								}
								else
								{
									rs.Edit( );
									bEdit = true;
								}

								rs.m_SeriesID = iSeriesID;
								rs.m_EventID = iEventID;
								rs.m_PersonID = iPersonID;
								//rs.m_Place = iPlace;
								rs.m_GrossPerformanceHOUR = iGrossPerformanceHOUR;
								rs.m_GrossPerformanceMIN = iGrossPerformanceMIN;
								rs.m_GrossPerformanceSEC = dGrossPerformanceSEC;
								rs.m_GroupIDSupposedTo = iGroupID;
								rs.m_DivisionSupposedTo = iDivision;
								rs.m_AgeGroup = iAgeGroup;
								if( !strChestNumber.IsEmpty() )
									rs.m_ChestNumber = strChestNumber;
								else
									rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

								if( !rs.CanUpdate( ) )
									html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
								if( !rs.Update( ) )
									html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
								else
								{
									if( bEdit )
										html << _T("<B><I>Modified</I></B> Result for Person, <B>");
									else
										html << _T("<B><I>Added</I></B> Result for Person, <B>");

									html << CConvert::itoa(iPersonID) << _T("</B> ");

									html << CConvert::itoa(iDivision) << _T(" ");
									//html << CConvert::itoa(iPlace) << _T(" ");

									html << CConvert::itoa(iPersonID) << _T(" ");
									html << CConvert::itoa(iAgeGroup) << _T(" ");

									html << _T( CFormat::FormatPerf(iTimed, iGrossPerformanceHOUR, iGrossPerformanceMIN, dGrossPerformanceSEC) ) << _T(" ");

									html << CConvert::itoa(iGroupID) << _T(" ");
									html << strChestNumber << _T(" ");

									//html << CConvert::itoa(iPoints) << _T(" ");
									//html << CConvert::itoa(iNewGroupID) << _T(" ");
									//html << strNewGroupMessage << _T(" ");

									html << _T("<BR>\r\n");
								}
								rs.Close( );
							}
							else // postEvent //
							{
								strSQL.Format( "SELECT * FROM PostResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d ", iSeriesID, iEventID, iPersonID );
								CPostResultsSet rs( &db );
								rs.Open(CRecordset::dynaset, strSQL );

								bool bEdit;

								if( rs.IsEOF( ) )
								{
									rs.AddNew( );
									bEdit = false;
								}
								else
								{
									rs.Edit( );
									bEdit = true;
								}

								rs.m_SeriesID = iSeriesID;
								rs.m_EventID = iEventID;
								rs.m_PersonID = iPersonID;
								rs.m_Place = iPlace;
								rs.m_GrossPerformanceHOUR = iGrossPerformanceHOUR;
								rs.m_GrossPerformanceMIN = iGrossPerformanceMIN;
								rs.m_GrossPerformanceSEC = dGrossPerformanceSEC;
								rs.m_GroupIDActual = iGroupID;
								rs.m_DivisionActual = iDivision;
								rs.m_AgeGroup = iAgeGroup;
								if( !strChestNumber.IsEmpty() )
									rs.m_ChestNumber = strChestNumber;
								else
									rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

								if( iPoints > 0 )
									rs.m_Points = iPoints;
								else
									rs.SetFieldNull( &rs.m_Points, TRUE );

								if( iNewGroupID > 0  )
									rs.m_NewGroupID = iNewGroupID;
								else
									rs.SetFieldNull( &rs.m_NewGroupID, TRUE );

								if( _tcslen(strNewGroupMessage) > 0 )
									rs.m_NewGroupMessage = strNewGroupMessage;
								else
									rs.SetFieldNull( &rs.m_NewGroupMessage, TRUE );

								if( !rs.CanUpdate( ) )
									html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
								if( !rs.Update( ) )
									html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
								else
								{
									if( bEdit )
										html << _T("<B><I>Modified</I></B> Result for Person, <B>");
									else
										html << _T("<B><I>Added</I></B> Result for Person, <B>");

									html << CConvert::itoa(iPersonID) << _T("</B> ");

									html << CConvert::itoa(iDivision) << _T(" ");
									html << CConvert::itoa(iPlace) << _T(" ");

									html << CConvert::itoa(iPersonID) << _T(" ");
									html << CConvert::itoa(iAgeGroup) << _T(" ");

									html << _T( CFormat::FormatPerf(iTimed, iGrossPerformanceHOUR, iGrossPerformanceMIN, dGrossPerformanceSEC) ) << _T(" ");

									html << CConvert::itoa(iGroupID) << _T(" ");
									html << strChestNumber << _T(" ");

									html << CConvert::itoa(iPoints) << _T(" ");
									html << CConvert::itoa(iNewGroupID) << _T(" ");
									html << strNewGroupMessage << _T(" ");

									html << _T("<BR>\r\n");
								}

								rs.Close( );
							}
						}
						else
						{
							html << _T("Invalid Person, <B>");
							html << _T(CConvert::itoa(iPersonID));
							html << _T("</B><BR>\r\n");
						}
						rsPerson.Close( );
					}
					catch (CDBException* pEx)
					{
						html << pEx;
					}
				}
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
			html << _T("nDivisionItems does no match nPlaceItems, nPersonIDItems, nAgeGroupItems, nPerformanceHOURItems, nPerformanceMINItems, nPerformanceSECItems, nGroupIDItems, nChestNumberItems, nPointsItems, nNewGroupIDItems, nNewGroupMessageItems<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ResultsEntryBulkAddForm(CHttpServerContext* pCtxt,
											    LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);

		int iPreEvent = _tcscmp("Post", strResultsEntry);

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

			int iTimed;
			strSQL.Format( "SELECT EventType.Timed AS Result FROM Event, EventType WHERE Event.EventID = %s AND Event.EventTypeID = EventType.EventTypeID", strEventID );

			CBoolResultSet rsBool( &db );
			rsBool.Open(CRecordset::dynaset, strSQL );

			if(!rsBool.IsEOF() && !rsBool.IsFieldNull(&rsBool.m_Result) )
			{
				iTimed = rsBool.m_Result;
			}
			
			rsBool.Close( );


			CString strCSVHeading;
			CString strCSVExample1;
			CString strCSVExample2;

			CStringArray* strCSVHeadingItems;
			strCSVHeadingItems = new CStringArray();

			CStringArray* strCSVExample1Items;
			strCSVExample1Items = new CStringArray();

			CStringArray* strCSVExample2Items;
			strCSVExample2Items = new CStringArray();

			CCSV csv(",", "\"");

			strCSVHeadingItems->Add("Division");
			strCSVExample1Items->Add("1");
			strCSVExample2Items->Add("1");

			if( !iPreEvent )
			{
				strCSVHeadingItems->Add("Place");
				strCSVExample1Items->Add("1");
				strCSVExample2Items->Add("2");
			}

			strCSVHeadingItems->Add("PersonID");
			strCSVExample1Items->Add("1057");
			strCSVExample2Items->Add("2704");

			strCSVHeadingItems->Add("AgeGroup");
			strCSVExample1Items->Add("55");
			strCSVExample2Items->Add("50");

			strCSVHeadingItems->Add( CFormat::FormatPerf(iTimed, "HH", "MM", "SS.SS", "Perf") );
			strCSVExample1Items->Add( CFormat::FormatPerf(iTimed, 0, 45, 47.78));
			strCSVExample2Items->Add( CFormat::FormatPerf(iTimed, 0, 46, 3.14));

			strCSVHeadingItems->Add("GroupID");
			strCSVExample1Items->Add("27");
			strCSVExample2Items->Add("11");

			strCSVHeadingItems->Add("ChestNo");
			strCSVExample1Items->Add("cb1057x");
			strCSVExample2Items->Add("rt2704x");

			if( !iPreEvent )
			{
				strCSVHeadingItems->Add("Points");
				strCSVExample1Items->Add("100");
				strCSVExample2Items->Add("99");

				strCSVHeadingItems->Add("NewGroupID");
				strCSVExample1Items->Add("25");
				strCSVExample2Items->Add("13");

				strCSVHeadingItems->Add("NewGroupMessage");
				strCSVExample1Items->Add("Handicappers Discretion");
				strCSVExample2Items->Add("Handicappers Discretion");
			}

			csv.GetCSVRow(strCSVHeadingItems, &strCSVHeading);
			strCSVHeadingItems->RemoveAll( );

			csv.GetCSVRow(strCSVExample1Items, &strCSVExample1);
			strCSVExample1Items->RemoveAll( );

			csv.GetCSVRow(strCSVExample2Items, &strCSVExample2);
			strCSVExample2Items->RemoveAll( );


			html << _T("Enter in the Results in <i>Comma Separated Value</i> (CSV) format, i.e.:<BR>\r\n<BR>\r\n");
			html << _T("<pre>") << strCSVHeading << _T("</pre>\r\n");
			html << _T("Ensure that the First Row Contains Column Names. e.g.:<BR>\r\n<BR>\r\n");
			html << _T("<pre>") << strCSVHeading  << _T("\r\n");
			html <<                strCSVExample1 << _T("\r\n");
			html <<                strCSVExample2 << _T("</pre>\r\n");

			html.StartForm( strResultsEntry + (iPreEvent ? (" Event Entries") : (" Event Results")), CPage::ResultsEntryBulkAddExecute);
			html.HiddenText("SeriesID", strSeriesID);
			html.HiddenText("EventID", strEventID);

			html.HorizontalRule();
			html.TextArea("Results", "BulkResults", 10, 95, (strCSVHeading + "\r\n\r\n") );

			html.HorizontalRule();
			html.SubmitButton(CHtmlKey::Save);

			html.EndForm();

			delete strCSVHeadingItems;
			delete strCSVExample1Items;
			delete strCSVExample2Items;

			db.Close( );

			html << _T("<p>Note: An Empty <B>Division</B> or a Division of <B>0</B> will attempt to auto-select that Person's Division. ")
				 << _T("Failure to auto-select will result in that Person being assigned to Division <B>1</B>. ")
				 << _T("A non-zero Division will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: An Empty <B>AgeGroup</B> or a AgeGroup of <B>0</B> will attempt to auto-select that Person's AgeGroup. ")
				 << _T("Failure to auto-select will result in that Person being assigned to AgeGroup <B>")
				 << prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::NullDoB)
				 << _T("</B>. ")
				 << _T("A non-zero AgeGroup will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: An Empty <B>Group</B> or a Group of <B>0</B> will attempt to auto-select that Person's Group. ")
				 << _T("Failure to auto-select will result in that Person being assigned to Group <B>1</B>. ")
				 << _T("A non-zero Group will override the auto-selection.</p>\r\n");

			html << _T("<p>Note: <B>Points</B> will only be Processed if there are no <B>Pointscore</B> Rules for the Series.</p>\r\n");

			html << _T("<p>Note: <B>NewGroup</B> and <B>NewGroupMessage</B> will only be Processed if there are no <B>Regroup</B> Rules for the Series.</p>\r\n");
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

//void CWebAthlExtension::BulkEntry(CHttpServerContext* pCtxt, void* pVoid, DWORD dwBytes)
void CWebAthlExtension::ResultsEntryBulkAddExecute(CHttpServerContext* pCtxt,
												   LPTSTR szSeriesID,
												   LPTSTR szEventID,
												   LPTSTR szBulkResults,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Results Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			int iTimed;
			strSQL.Format( "SELECT EventType.Timed AS Result FROM Event, EventType WHERE Event.EventID = %s AND Event.EventTypeID = EventType.EventTypeID", szEventID );

			CBoolResultSet rsBool( &db );
			rsBool.Open(CRecordset::dynaset, strSQL );

			if(!rsBool.IsEOF() && !rsBool.IsFieldNull(&rsBool.m_Result) )
			{
				iTimed = rsBool.m_Result;
			}
			
			rsBool.Close( );


			CString strLine;

			CStringArray* strItems;
			strItems = new CStringArray();

			CStringLine* strTable = new CStringLine(szBulkResults);

			CCSV csv(",:", "\"");

			CString strDivision;
			CString strPlace;
			CString strPersonID;
			CString strAgeGroup;
			CString strPerformanceHOUR;
			CString strPerformanceMIN;
			CString strPerformanceSEC;
			CString strGroupID;
			CString strChestNumber;
			CString strPoints;
			CString strNewGroupID;
			CString strNewGroupMessage;

			int nDivisionIndex = -1;
			int nPlaceIndex = -1;
			int nPersonIDIndex = -1;
			int nAgeGroupIndex = -1;
			int nPerformanceHOURIndex = -1;
			int nPerformanceMINIndex = -1;
			int nPerformanceSECIndex = -1;
			int nGroupIDIndex = -1;
			int nChestNumberIndex = -1;
			int nPointsIndex = -1;
			int nNewGroupIDIndex = -1;
			int nNewGroupMessageIndex = -1;

			// First Row Contains Column Names
			if( strTable->GetLine(strLine) )
			{
				csv.GetItems(strItems, &strLine);

				CString strItem;

				for( int nIndex = 0 ; nIndex < strItems->GetSize( ) ; nIndex++ )
				{
					strItem = strItems->GetAt( nIndex );
					strItem.TrimLeft( _T("\t ") );
					strItem.TrimRight( _T("\t ") );

					if( strItem.CompareNoCase( "Division" ) == 0 )
					{
						nDivisionIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Div" ) == 0 )
					{
						nDivisionIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Place" ) == 0 )
					{
						nPlaceIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "PersonID" ) == 0 )
					{
						nPersonIDIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "AgeGroup" ) == 0 )
					{
						nAgeGroupIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Age" ) == 0 )
					{
						nAgeGroupIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "HH" ) == 0 )
					{
						nPerformanceHOURIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "HOUR" ) == 0 )
					{
						nPerformanceHOURIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "MM" ) == 0 )
					{
						nPerformanceMINIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "MIN" ) == 0 )
					{
						nPerformanceMINIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "SS.SS" ) == 0 )
					{
						nPerformanceSECIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "SS" ) == 0 )
					{
						nPerformanceSECIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "SEC" ) == 0 )
					{
						nPerformanceSECIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Performance" ) == 0 )
					{
						nPerformanceSECIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Perf" ) == 0 )
					{
						nPerformanceSECIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "GroupID" ) == 0 )
					{
						nGroupIDIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "ChestNumber" ) == 0 )
					{
						nChestNumberIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "ChestNo" ) == 0 )
					{
						nChestNumberIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Points" ) == 0 )
					{
						nPointsIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "NewGroupID" ) == 0 )
					{
						nNewGroupIDIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "NewGroupMessage" ) == 0 )
					{
						nNewGroupMessageIndex = nIndex;
					}
					else if( strItem.CompareNoCase( "Message" ) == 0 )
					{
						nNewGroupMessageIndex = nIndex;
					}
				}

				strItems->RemoveAll( );
				csv.SetRecordCount( );
			}

			if( nDivisionIndex > -1        || 
				nPlaceIndex > -1           || 
				nPersonIDIndex > -1        || 
				nAgeGroupIndex > -1        || 
				nPerformanceHOURIndex > -1 || 
				nPerformanceMINIndex > -1  || 
				nPerformanceSECIndex > -1  || 
				nGroupIDIndex > -1         || 
				nChestNumberIndex > -1     || 
				nPointsIndex > -1          || 
				nNewGroupIDIndex > -1      || 
				nNewGroupMessageIndex > -1 )  
			{

				while( strTable->GetLine(strLine) )
				{
					//html << _T("Line [") << strLine << _T("]<BR>\r\n");

					csv.GetItems(strItems, &strLine);

					//html << _T("Items [") ;
					//for( int nIndex = 0 ; nIndex < strItems->GetSize( ) ; nIndex++ )
					//	html << strItems->GetAt( nIndex ) << _T("^");
					//html << _T("]<BR>\r\n");


					if( nDivisionIndex > -1 && strItems->GetSize( ) > nDivisionIndex )
						strDivision = strItems->GetAt( nDivisionIndex );
					else
						strDivision.Empty( );

					if( nPlaceIndex > -1 && strItems->GetSize( ) > nPlaceIndex )
						strPlace = strItems->GetAt( nPlaceIndex );
					else
						strPlace.Empty( );

					if( nPersonIDIndex > -1 && strItems->GetSize( ) > nPersonIDIndex )
						strPersonID = strItems->GetAt( nPersonIDIndex );
					else
						strPersonID = _T("0");

					if( nAgeGroupIndex > -1 && strItems->GetSize( ) > nAgeGroupIndex )
						strAgeGroup = strItems->GetAt( nAgeGroupIndex );
					else
						strAgeGroup.Empty( );

					if( nPerformanceHOURIndex > -1 && strItems->GetSize( ) > nPerformanceHOURIndex )
						strPerformanceHOUR = strItems->GetAt( nPerformanceHOURIndex );
					else
						strPerformanceHOUR.Empty( );

					if( nPerformanceMINIndex > -1 && strItems->GetSize( ) > nPerformanceMINIndex )
						strPerformanceMIN = strItems->GetAt( nPerformanceMINIndex );
					else
						strPerformanceMIN.Empty( );

					if( nPerformanceSECIndex > -1 && strItems->GetSize( ) > nPerformanceSECIndex )
						strPerformanceSEC = strItems->GetAt( nPerformanceSECIndex );
					else
						strPerformanceSEC.Empty( );

					if( nGroupIDIndex > -1 && strItems->GetSize( ) > nGroupIDIndex )
						strGroupID = strItems->GetAt( nGroupIDIndex );
					else
						strGroupID.Empty( );

					if( nChestNumberIndex > -1 && strItems->GetSize( ) > nChestNumberIndex )
						strChestNumber = strItems->GetAt( nChestNumberIndex );
					else
						strChestNumber.Empty( );

					if( nPointsIndex > -1 && strItems->GetSize( ) > nPointsIndex )
						strPoints = strItems->GetAt( nPointsIndex );
					else
						strPoints.Empty( );

					if( nNewGroupIDIndex > -1 && strItems->GetSize( ) > nNewGroupIDIndex )
						strNewGroupID = strItems->GetAt( nNewGroupIDIndex );
					else
						strNewGroupID.Empty( );

					if( nNewGroupMessageIndex > -1 && strItems->GetSize( ) > nNewGroupMessageIndex )
						strNewGroupMessage = strItems->GetAt( nNewGroupMessageIndex );
					else
						strNewGroupMessage.Empty( );

					strItems->RemoveAll( );


					try
					{
						strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s", strPersonID );
						CPersonSet rsPerson( &db );
						rsPerson.Open(CRecordset::dynaset, strSQL );

						if( !rsPerson.IsEOF( ) )
						{

							int iSeriesID = atoi(szSeriesID);
							int iEventID = atoi(szEventID);

							int iDivision = atoi(strDivision);
							int iPlace = atoi(strPlace);
							int iPersonID = atoi(strPersonID);
							int iAgeGroup = atoi(strAgeGroup);
							int iGrossPerformanceHOUR = atoi(strPerformanceHOUR);
							int iGrossPerformanceMIN = atoi(strPerformanceMIN);
							double dGrossPerformanceSEC = atof(strPerformanceSEC);
							int iGroupID = atoi(strGroupID);
							int iPoints = atoi(strPoints);
							int iNewGroupID = atoi(strNewGroupID);

							if( iAgeGroup < 1 )
							{
								strSQL.Format( "SELECT * FROM Event WHERE EventID = %s ", szEventID );
								CEventSet rsEvent( &db );
								rsEvent.Open(CRecordset::dynaset, strSQL );

								int nDateAgeDAY = rsEvent.m_DateAgeDAY;
								int nDateAgeMONTH = rsEvent.m_DateAgeMONTH;
								int nDateAgeYEAR = rsEvent.m_DateAgeYEAR;

								if( rsEvent.IsFieldNull( &rsEvent.m_DateAgeDAY ) ||
									rsEvent.IsFieldNull( &rsEvent.m_DateAgeMONTH ) ||
									rsEvent.IsFieldNull( &rsEvent.m_DateAgeYEAR ) ||
									rsEvent.m_DateAgeDAY == 0 ||
									rsEvent.m_DateAgeMONTH == 0 ||
									rsEvent.m_DateAgeYEAR == 0 ) 
								{
									nDateAgeDAY = rsEvent.m_DateDAY;
									nDateAgeMONTH = rsEvent.m_DateMONTH;
									nDateAgeYEAR = rsEvent.m_DateYEAR;
								}

								CString strAgeCategory;
								iAgeGroup = CCalculate::GroupAge(
												CCalculate::YearDiff(rsPerson.m_dobDAY,
														 rsPerson.m_dobMONTH,
														 rsPerson.m_dobYEAR,
														 nDateAgeDAY,
														 nDateAgeMONTH,
														 nDateAgeYEAR),
												strAgeCategory,
												&prop);
								rsEvent.Close( );
							}

							if( iGroupID < 1 || iDivision < 1 )
							{
								if(iPreEvent)
								{
									strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %d AND PersonID = %d", iSeriesID, iPersonID );
									CParticipantForSeriesSet rsPforS( &db );
									rsPforS.Open(CRecordset::dynaset, strSQL );

									if(!rsPforS.IsEOF( ) )
									{
										if( iDivision < 1 )
											iDivision = rsPforS.m_DivisionSupposedTo;

										if( iGroupID < 1 )
											iGroupID = rsPforS.m_GroupIDSupposedTo;
									}
									rsPforS.Close( );
								}
								else // postEvent //
								{
									strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d", iSeriesID, iEventID, iPersonID );
									CPreResultsSet rsPreRes( &db );
									rsPreRes.Open(CRecordset::dynaset, strSQL );

									if(!rsPreRes.IsEOF( ) )
									{
										//strChestNo = rsPreRes.m_ChestNumber;

										if( iDivision < 1 )
											iDivision = rsPreRes.m_DivisionSupposedTo;

										if( iGroupID < 1 )
											iGroupID = rsPreRes.m_GroupIDSupposedTo;
									}
									else
									{
										strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %d AND PersonID = %d", iSeriesID, iPersonID );
										CParticipantForSeriesSet rsPforS( &db );
										rsPforS.Open(CRecordset::dynaset, strSQL );

										if(!rsPforS.IsEOF( ) )
										{
											if( iDivision < 1 )
												iDivision = rsPforS.m_DivisionSupposedTo;

											if( iGroupID < 1 )
												iGroupID = rsPforS.m_GroupIDSupposedTo;
										}
										rsPforS.Close( );
									}
									rsPreRes.Close( );
								}
							}

							if( iGroupID < 1 )
								iGroupID = 1;

							if( iDivision < 1 )
								iDivision = 1;


							if( iPreEvent )
							{
								strSQL.Format( "SELECT * FROM PreResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d ", iSeriesID, iEventID, iPersonID );
								CPreResultsSet rs( &db );
								rs.Open(CRecordset::dynaset, strSQL );

								bool bEdit;

								if( rs.IsEOF( ) )
								{
									rs.AddNew( );
									bEdit = false;
								}
								else
								{
									rs.Edit( );
									bEdit = true;
								}

								rs.m_SeriesID = iSeriesID;
								rs.m_EventID = iEventID;
								rs.m_PersonID = iPersonID;
								//rs.m_Place = iPlace;
								rs.m_GrossPerformanceHOUR = iGrossPerformanceHOUR;
								rs.m_GrossPerformanceMIN = iGrossPerformanceMIN;
								rs.m_GrossPerformanceSEC = dGrossPerformanceSEC;
								rs.m_GroupIDSupposedTo = iGroupID;
								rs.m_DivisionSupposedTo = iDivision;
								rs.m_AgeGroup = iAgeGroup;
								if( _tcslen(strChestNumber) > 0 )
									rs.m_ChestNumber = strChestNumber;
								else
									rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

								if( !rs.CanUpdate( ) )
									html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
								if( !rs.Update( ) )
									html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
								else
								{
									if( bEdit )
										html << _T("<B><I>Modified</I></B> Result for Person, <B>");
									else
										html << _T("<B><I>Added</I></B> Result for Person, <B>");

									html << CConvert::itoa(iPersonID) << _T("</B> ");

									html << CConvert::itoa(iDivision) << _T(" ");
									//html << CConvert::itoa(iPlace) << _T(" ");

									html << CConvert::itoa(iPersonID) << _T(" ");
									html << CConvert::itoa(iAgeGroup) << _T(" ");

									html << _T( CFormat::FormatPerf(iTimed, iGrossPerformanceHOUR, iGrossPerformanceMIN, dGrossPerformanceSEC) ) << _T(" ");

									html << CConvert::itoa(iGroupID) << _T(" ");
									html << strChestNumber << _T(" ");

									//html << CConvert::itoa(iPoints) << _T(" ");
									//html << CConvert::itoa(iNewGroupID) << _T(" ");
									//html << strNewGroupMessage << _T(" ");

									html << _T("<BR>\r\n");
								}

								rs.Close( );

							}
							else // PostEvent //
							{
								strSQL.Format( "SELECT * FROM PostResults WHERE SeriesID = %d AND EventID = %d AND PersonID = %d ", iSeriesID, iEventID, iPersonID );
								CPostResultsSet rs( &db );
								rs.Open(CRecordset::dynaset, strSQL );

								bool bEdit;

								if( rs.IsEOF( ) )
								{
									rs.AddNew( );
									bEdit = false;
								}
								else
								{
									rs.Edit( );
									bEdit = true;
								}

								rs.m_SeriesID = iSeriesID;
								rs.m_EventID = iEventID;
								rs.m_PersonID = iPersonID;
								rs.m_Place = iPlace;
								rs.m_GrossPerformanceHOUR = iGrossPerformanceHOUR;
								rs.m_GrossPerformanceMIN = iGrossPerformanceMIN;
								rs.m_GrossPerformanceSEC = dGrossPerformanceSEC;
								rs.m_GroupIDActual = iGroupID;
								rs.m_DivisionActual = iDivision;
								rs.m_AgeGroup = iAgeGroup;
								if( _tcslen(strChestNumber) > 0 )
									rs.m_ChestNumber = strChestNumber;
								else
									rs.SetFieldNull( &rs.m_ChestNumber, TRUE );

								if( iPoints )
									rs.m_Points = iPoints;
								else
									rs.SetFieldNull( &rs.m_Points, TRUE );

								if( iNewGroupID )
									rs.m_NewGroupID = iNewGroupID;
								else
									rs.SetFieldNull( &rs.m_NewGroupID, TRUE );

								if( _tcslen(strNewGroupMessage) > 0 )
									rs.m_NewGroupMessage = strNewGroupMessage;
								else
									rs.SetFieldNull( &rs.m_NewGroupMessage, TRUE );

								if( !rs.CanUpdate( ) )
									html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
								if( !rs.Update( ) )
									html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
								else
								{
									if( bEdit )
										html << _T("<B><I>Modified</I></B> Result for Person, <B>");
									else
										html << _T("<B><I>Added</I></B> Result for Person, <B>");

									html << CConvert::itoa(iPersonID) << _T("</B> ");

									html << CConvert::itoa(iDivision) << _T(" ");
									html << CConvert::itoa(iPlace) << _T(" ");

									html << CConvert::itoa(iPersonID) << _T(" ");
									html << CConvert::itoa(iAgeGroup) << _T(" ");

									html << _T( CFormat::FormatPerf(iTimed, iGrossPerformanceHOUR, iGrossPerformanceMIN, dGrossPerformanceSEC) ) << _T(" ");

									html << CConvert::itoa(iGroupID) << _T(" ");
									html << strChestNumber << _T(" ");

									html << CConvert::itoa(iPoints) << _T(" ");
									html << CConvert::itoa(iNewGroupID) << _T(" ");
									html << strNewGroupMessage << _T(" ");

									html << _T("<BR>\r\n");
								}
								rs.Close( );
							}
						}
						else
						{
							html << _T("Invalid Person <B>");
							html << _T(strPersonID);
							html << _T("</B> on Row <B>");
							html << csv.GetRecordCount( );
							html << _T("</B><BR>\r\n");

							csv.SetRecordCount( true );
						}
						rsPerson.Close( );
					}
					catch (CDBException* pEx)
					{
						html << pEx;

						pEx->Delete();

						html << _T("Invalid Row <B>");
						html << csv.GetRecordCount();
						html << _T("</B><BR>\r\n");

						csv.SetRecordCount( true );
					}
				}

			}
			else
			{
				html << _T("First Row Must Contain Column Names.<BR>\r\n");
			}

			html << "(<B>" 
				 << csv.GetRecordCount( true ) 
				 << "</B> row(s) affected)<BR>\r\n" ;

			delete strItems;

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

void CWebAthlExtension::ResultsEntryDeleteForm(CHttpServerContext* pCtxt,
											   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ResultsEntry) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

		CString strResultsTable;
		if( iPreEvent )
			strResultsTable.Format("PreResults");
		else
			strResultsTable.Format("PostResults");

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		if(_tcscmp(szSubmit,CHtmlKey::Delete))
			html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		else
			html.WritePageMenuItem(auth.m_strBackLink, "Results Menu", 0);

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


			strSQL.Format( html.GetNonEditEventBoxDetails(atoi(strEventID)) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );


			html.StartForm( (iPreEvent ? ("Delete Event Entries") : ("Delete Event Results")), "");


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

			if(_tcscmp(szSubmit,CHtmlKey::Delete))
			{
				strSQL.Format( "SELECT COUNT(*) AS Total FROM %s WHERE SeriesID = %s AND EventID = %s", strResultsTable, strSeriesID, strEventID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html.NonEditInt("Participants", rsCount.m_Total );
				html.EndForm();

				html.StartForm("", CPage::ResultsEntryDeleteForm);

				CString strMsg;
				strMsg.Format("Deleting <B>%s</B> Participants", CConvert::itoa(rsCount.m_Total));

				html.NonEditText(strMsg, "" );
				html.NonEditText("Are you Sure?", html.InLineInput("submit","Submit",CHtmlKey::Delete,0,"") );

				//html.SubmitButton(CHtmlKey::Delete);

				html.EndForm();

				rsCount.Close( );
			}
			else
			{
				html.EndForm();

				strSQL.Format( "SELECT COUNT(*) AS Total FROM %s WHERE SeriesID = %s AND EventID = %s", strResultsTable, strSeriesID, strEventID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html << _T("Deleting <B>");
				html << _T( CConvert::itoa(rsCount.m_Total) );
				html << _T("</B> Participants.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("<BR>\r\n");

				rsCount.Close( );


				strSQL.Format( "DELETE FROM %s WHERE SeriesID = %s AND EventID = %s", strResultsTable, strSeriesID, strEventID ); 
				db.ExecuteSQL( strSQL );


				strSQL.Format( "SELECT COUNT(*) AS Total FROM %s WHERE SeriesID = %s AND EventID = %s", strResultsTable, strSeriesID, strEventID );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html << _T("Participant Count is now <B>");
				html << _T( CConvert::itoa(rsCount.m_Total) );
				html << _T("</B> Participants.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("<BR>\r\n");

				rsCount.Close( );
			}

			rsEvent.Close( );
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




