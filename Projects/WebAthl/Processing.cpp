// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "Processor.h"

#include "EventETypLocSet.h"
#include "CountResultSet.h"
#include "SeriesSet.h"

///////////////////////////////////////////////////////////////////////
// Processing

void CWebAthlExtension::ProcessingForm(CHttpServerContext* pCtxt,
								   LPTSTR szSeriesID,
								   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Processing) )
	{
		auth.m_strFrwdLink = CPage::ProcessingExecute;

		BOOL bIsUtil = atoi(html.GetCookie(CHtmlKey::IsUtil));

		int iSeriesID;
		DWORD dwProc;

		if( !_tcscmp(szSeriesID, "none") )
		{
			iSeriesID = atoi(html.GetCookie(CHtmlKey::SeriesID));
			dwProc = atol(html.GetCookie(CHtmlKey::DWProc));
		}
		else
		{
			iSeriesID = atoi(szSeriesID);
			dwProc = CProcess::PostEventProcessAll;
		}

		int iEventID = 0;

		int iTimed;
		// Timed = 1 -> Long Distance
		// Timed = 0 -> Jump or Throw
		// Timed = 2 -> Sprint

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CEventETypLocSet rsCurrentEvent( &db );
			// get the EventId for processing
			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_EVENTFORPROCESSING);
			strSQL.Format(strSQLtmp, CConvert::itoa(iSeriesID));
			rsCurrentEvent.Open(CRecordset::forwardOnly, strSQL );
			if( !rsCurrentEvent.IsEOF( ) )
			{
				iEventID = rsCurrentEvent.m_EventID;
			}
			rsCurrentEvent.Close( );


			CCountResultSet rsCount( &db );
			// get Timed
			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
			strSQL.Format(strSQLtmp, iSeriesID, iEventID );
			rsCount.Open(CRecordset::forwardOnly, strSQL );
			iTimed = rsCount.m_Total;
			rsCount.Close( );

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html.SetContent();
			html.EndHeader();

			html.WritePageTitle(auth.m_strOrgName);
			html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

			html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);
			html.EndMenu();

			html << pEx;

			html.EndPage();
			html.EndContent();

			pEx->Delete();

			return;
		}

		html.SetContent();
		html.SetCookie(CHtmlKey::BackLink, CPage::ProcessingForm);
		html.SetCookie(CHtmlKey::SeriesID, CConvert::itoa(iSeriesID));
		html.SetCookie(CHtmlKey::EventID, CConvert::itoa(iEventID));
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		if ( bIsUtil )
		{
			html.WritePageMenuItem(CPage::UtilitiesMenu, CHtmlKey::Cancel, 0);
		}
		else
		{
			html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);
		}

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			if( iEventID != 0 )
			{
				int iPreResultsCount = 0;
				int iPostResultsCount = 0;
				int iResultsCount = 0;

				CCountResultSet rsCount( &db );

				strSQL.Format( "SELECT COUNT(*) AS Total FROM PreResults WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iPreResultsCount = rsCount.m_Total;
				rsCount.Close( );

				strSQL.Format( "SELECT COUNT(*) AS Total FROM PostResults WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iPostResultsCount = rsCount.m_Total;
				rsCount.Close( );

				strSQL.Format( "SELECT COUNT(*) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iResultsCount = rsCount.m_Total;
				rsCount.Close( );

			
		



				html.StartForm("Processing", auth.m_strFrwdLink);


				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %d", iSeriesID );
				CSeriesSet rsSeries( &db );
				rsSeries.Open(CRecordset::forwardOnly, strSQL );

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				html.HorizontalRule();
				rsSeries.Close( );

				strSQL.Format( html.GetNonEditEventBoxDetails(iEventID) );

				CEventETypLocSet rsEvent( &db );
				rsEvent.Open(CRecordset::forwardOnly, strSQL );

			
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

				rsEvent.Close( );

				switch(iTimed)
				{
					case 0 : // Jump or Throw
						html.NonEditText("Event Type", "Jump, Throw or Points") ;
						break;
					case 1 : //Long Distance
						html.NonEditText("Event Type", "Long Distance") ;
						break;
					case 2 : //	Sprint
						html.NonEditText("Event Type", "Sprint") ;
						break;
				}

				if(iPreResultsCount > 0)
					html.NonEditInt("Pre-Event Entries",iPreResultsCount) ;
				if(iPostResultsCount > 0)
					html.NonEditInt("Post-Event Entries", iPostResultsCount) ;
				if(iResultsCount > 0)
					html.NonEditInt("Processed Entries", iResultsCount) ;

				if( ((iPreResultsCount <= 0) && (iPostResultsCount <= 0)) ||
					((iResultsCount <= 0))								   )
					html.NonEditText("Processing", "Pre-Event") ;
				if(iPostResultsCount > 0)
					html.NonEditText("Processing", "Post-Event ") ;

				html.HorizontalRule();






				bool bAdmin = false;

				if( auth.HasPermission(CModule::Utilities) && bIsUtil )
				{
					bAdmin = true;
				}

				html.StartSelectBox("Process", "dwProc");

				CProcess proc;
				DWORD dwEnum = proc.Enumerator();
				while( proc.GetNext( &dwEnum ) )
				{
					bool bAddItem = false;

					// Insert Pre-Event Entries
					if( iPreResultsCount > 0 )	 
					{
						if( proc.IsMember(CProcessGroup::PreResults) )
						{
							bAddItem = true;
						}
					}

					// Post-Event Processing
					if(iPostResultsCount > 0) 
					{
						if( proc.IsMember(CProcessGroup::PostEvent) )
						{
							bAddItem = true;
						}

						// Lock Out
						if( iResultsCount == iPostResultsCount )
						{
							if( proc.IsMember(CProcessGroup::LockOut) )
							{
								bAddItem = true;
							}
						}
					}
					
					// Pre-Event Processing
					if( ((iPreResultsCount <= 0) && (iPostResultsCount <= 0)) ||
						 ((iResultsCount <= 0))  )	 
					{
						if( proc.IsMember(CProcessGroup::PreEvent) )
						{
							bAddItem = true;
						}
					}

					// Club Records
					if( proc.IsMember(CProcessGroup::ClubRecords) )
					{
						bAddItem = true;
					}


					// Admin Processes
					if( proc.IsMember(CProcessGroup::Admin) )
					{
						if( !bAdmin )
						{
							bAddItem = false;
						}
					}

					if( bAddItem )
					{
						html.AddSelectBox(
							proc.GetName(), 
							CConvert::dwtoa(dwEnum), 
							CConvert::dwtoa(dwProc));
					}

				}
				html.EndSelectBox();

				html.HorizontalRule();




				int iPlaceByDivision;

				// count the number of rules to get Set Overall-Place By Division
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Processing), 
					CRuleSubType::GetName(CRuleSubType::ProcessingSetOverallPlaceByDivision) );

				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iPlaceByDivision = rsCount.m_Total;
				rsCount.Close( );


				if( iPlaceByDivision > 0 )
				{
					html.NonEditText("Set Overall-Place", "By Division");
				}
				else
				{
					html.NonEditText("Set Overall-Place", "By Place");
				}



				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();
			}
			else
			{
				html << _T("No Events Available for Processing.<BR><BR>\r\n");
				html << _T("If Processing is required, please contact your System Administrator to configure an Event for Processing.<BR>\r\n");
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

void CWebAthlExtension::ProcessingExecute(CHttpServerContext* pCtxt,
										  LPTSTR szDwProc,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Processing) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strEventID = html.GetCookie(CHtmlKey::EventID);

		auth.m_strFrwdLink.Empty();

		DWORD dwProc = atol(szDwProc);

	    html.SetContent();
		html.SetCookie(CHtmlKey::DWProc, szDwProc);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Processing Menu", 0);
		html.EndMenu();

		int iSeriesID = atoi(strSeriesID);
		int iEventID = atoi(strEventID);

		CString strConnect = prop.GetDefaultConnect();
		DWORD dwSeconds = atoi(prop.GetEx(CHtmlKey::Processing,CHtmlKey::TimeOut));

		BOOL bCanProcess = TRUE;

		if( !prop.IsLicensed( ) )
		{
			bCanProcess = CProcessor::CanProcess(&html, strConnect, iSeriesID, iEventID );
		}

		if( bCanProcess )
		{
			html << _T("<UL>");
			switch(dwProc)
			{
				case CProcess::PostEventProcessAll :
				{
					CProcess proc;
					DWORD dwEnum = proc.Enumerator();
					while( proc.GetNext( &dwEnum ) )
					{
						if( proc.IsMember(CProcessGroup::PostEvent) )
						{
							if( proc.IsMember(CProcessGroup::PreEvent) )
							{
								// Cant use an EventID in a dual process
								CProcessor::Execute(&html, strConnect, dwSeconds, dwEnum, iSeriesID, 0 );
							}
							else
							{
								CProcessor::Execute(&html, strConnect, dwSeconds, dwEnum, iSeriesID, iEventID );
							}
						}
					}
					break;
				}
				case CProcess::PreEventProcessAll :
				{
					CProcess proc;
					DWORD dwEnum = proc.Enumerator();
					while( proc.GetNext( &dwEnum ) )
					{
						if( proc.IsMember(CProcessGroup::PreEvent) )
						{
							if( proc.IsMember(CProcessGroup::PostEvent) )
							{
								// Cant use an EventID in a dual process
								CProcessor::Execute(&html, strConnect, dwSeconds, dwEnum, iSeriesID, 0 );
							}
							else
							{
								CProcessor::Execute(&html, strConnect, dwSeconds, dwEnum, iSeriesID, iEventID );
							}
						}
					}
					break;
				}
				default:
				{
					CProcessor::Execute(&html, strConnect, dwSeconds, dwProc, iSeriesID, iEventID );
					break;
				}
			}
			html << _T("</UL>");
		}

		html.EndPage();
		html.EndContent();
	}
}






