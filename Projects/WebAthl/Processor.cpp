// CProcessor.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "Processor.h"

#include "SeriesSet.h"
#include "EventSet.h"
#include "EventETypLocSet.h"
#include "EventTypeSet.h"
#include "LocationSet.h"
#include "ResultsSet.h"
#include "ResultsPostResultsSet.h"

#include "GroupsSet.h"

#include "RulesSet.h"
#include "RulesJoinSet.h"

#include "PersonSet.h"
#include "ParticipantForSeriesSet.h"
#include "ResultsWorldStandardSet.h"
#include "ResultsEventTypeSet.h"
#include "ConsistencyAgeGroupSet.h"
#include "EventRecordSet.h"
#include "FinancialRegistrationSet.h"

#include "CountResultSet.h"
#include "IntegerSet.h"
#include "DoubleSet.h"
#include "CountItemSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Processor

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CProcessor::CProcessor( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CProcessor::~CProcessor( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

BOOL CProcessor::CanProcess(CHtmlWriter* pHtml, 
							LPCTSTR szConnect, 
							int iSeriesID, 
							int iEventID)
{
	BOOL bCanProcess = TRUE;

	try
	{
		CDatabase db;
		db.OpenEx( szConnect, CDatabase::noOdbcDialog );

		// Series Count
		CSeriesSet rsSeries( &db );
		rsSeries.Open(CRecordset::dynaset, "SELECT * FROM Series" );

		rsSeries.SetCountMessage( _T("Maximum Series Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
		rsSeries.HasMaxCountReached( );

		rsSeries.Close( );


		// Event Count on Series
		CEventSet rsEvent( &db );
		rsEvent.Open(CRecordset::dynaset, "SELECT * FROM Event" );

		CString strWhereClause;
		strWhereClause.Format("WHERE SeriesID = %d", iSeriesID);

		rsEvent.SetCountMessage( _T("Maximum Event Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
		rsEvent.SetCountWhereClause( strWhereClause );
		rsEvent.HasMaxCountReached( );

		rsEvent.Close( );


		// Person Count
		CPersonSet rsPerson( &db );
		rsPerson.Open(CRecordset::dynaset, "SELECT * FROM Person" );

		rsPerson.SetCountMessage( _T("Maximum Person Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
		rsPerson.HasMaxCountReached( );

		rsPerson.Close( );

		db.Close( );
	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		bCanProcess = FALSE;

		pEx->Delete();
	}

	return bCanProcess;
}

void CProcessor::ShowProcessMessage(CHtmlWriter* pHtml,
									DWORD dwProc, int iSeriesID, int iEventID)
{
	CString strOutput;

	if( iEventID > 0 )
	{
		strOutput.Format( "<B>%s</B>. (SeriesID <B>%d</B>, EventID <B>%d</B>)", 
			CProcess::GetName(dwProc), iSeriesID, iEventID ); 
	}
	else
	{
		strOutput.Format( "<B>%s</B>. (SeriesID <B>%d</B>)", 
			CProcess::GetName(dwProc), iSeriesID ); 
	}
	*pHtml << _T(strOutput);
	*pHtml << _T("</BR>\r\n");
}

void CProcessor::ShowResultMessage(CHtmlWriter* pHtml,
								   int iCount, CString strComment)
{
	*pHtml << _T("<B>");
	*pHtml << CConvert::itoa(iCount);
	*pHtml << _T("</B> updated.");

	if( strComment.GetLength( ) > 0 )
	{
		*pHtml << _T(" (");
		*pHtml << _T(strComment);
		*pHtml << _T(") ");
	}

	*pHtml << _T("<BR>\r\n");
}

BOOL CProcessor::Execute(CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
						 DWORD dwProc, int iSeriesID, int iEventID)
{
	*pHtml << _T("<LI>");
	ShowProcessMessage(pHtml, dwProc, iSeriesID, iEventID);

	switch(dwProc)
	{
		case CProcess::ClearNewGroup:
			ExecuteClearNewGroup(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::LockOut:
			ExecuteLockOut(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::ReSetEligibility: 
			ExecuteReSetEligibility(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetEligibilityXMore: 
			ExecuteSetEligibilityXMore(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::RebuildParticipantForSeries: 
			ExecuteRebuildParticipantForSeries(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetDivisionEligibility:
			ExecuteSetDivisionEligibility(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetGroupsEligibility: 
			ExecuteSetGroupsEligibility(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::PadPreResults: 
			ExecutePadPreResults(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;
		
		case CProcess::ClosePreEntry : 
			ExecuteClosePreEntry(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::PadPostResults: 
			ExecutePadPostResults(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetPointScore: 
			ExecuteSetPointScore(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetOverAllPlace: 
			ExecuteSetOverAllPlace(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

//		case CProcess::SetMiscResults: 
//			ExecuteSetMiscResults(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
//			break;

		case CProcess::SetNetPerformance: 
			ExecuteSetNetPerformance(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;
		case CProcess::SetPercentile: 
			ExecuteSetPercentile(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;
		case CProcess::SetPoints: 
			ExecuteSetPoints(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;
		case CProcess::SetEventRate: 
			ExecuteSetEventRate(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;



		case CProcess::SetWorldStandards: 
			ExecuteSetWorldStandards(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetConsistencyEventsRate: 
			ExecuteSetConsistencyEventsRate(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetConsistencyAgeStandard: 
			ExecuteSetConsistencyAgeStandard(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetConsistencyAgeGroup: 
			ExecuteSetConsistencyAgeGroup(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetEventsForSeason :
			ExecuteSetEventsForSeason(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetEventsForSeries :
			ExecuteSetEventsForSeries(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::ReGroup: 
			ExecuteReGroup(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::RebuildClubRecords: 
			ExecuteRebuildClubRecords(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetFinancialEligibility: 
			ExecuteSetFinancialEligibility(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;

		case CProcess::SetSeriesFinancialEligibility:
			ExecuteSetSeriesFinancialEligibility(pHtml, szConnect, dwTimeOut, dwProc, iSeriesID, iEventID);
			break;
	}

	*pHtml << _T("</LI>");

	return TRUE;
}



BOOL CProcessor::ExecuteClearNewGroup(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				strSQL.Format( "UPDATE Results SET NewGroupId = NULL , NewGroupMessage = NULL WHERE SeriesID = %d AND EventID = %d ", iSeriesID, iEventID );
				db.ExecuteSQL( strSQL );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			CCountResultSet rsCount( &db );

			strSQL.Format( "SELECT COUNT(*) FROM Results WHERE NewGroupId IS NULL AND SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
			rsCount.Open(CRecordset::forwardOnly, strSQL );

			ShowResultMessage(pHtml, rsCount.m_Total, "");

			rsCount.Close( );

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteLockOut(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				// Find the next Event

				int iNextEventID;

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_NEXTEVENT);
				strSQL.Format(strSQLtmp,
					_T( CConvert::itoa(iSeriesID) ),
					_T( CConvert::itoa(iSeriesID) ),
					_T( CConvert::itoa(iEventID) )  );

				CEventSet rsNextEvent( &db );

				rsNextEvent.Open(CRecordset::dynaset, strSQL );
				iNextEventID = rsNextEvent.m_EventID;
				rsNextEvent.Close( );
							
				// Set the next Event
				strSQL.Format( "UPDATE SeriesSeason SET NextEventForProcess = %d WHERE SeriesID = %d ", iNextEventID, iSeriesID);
				db.ExecuteSQL( strSQL );

				*pHtml << _T("Post-Event Processing is now locked out on EventID : <B>");
				*pHtml << _T( CConvert::itoa(iEventID) );
				*pHtml << _T("</B><BR>\r\n");

				*pHtml << _T("Next EventID set to: <B>");
				*pHtml << _T(CConvert::itoa(iNextEventID));
				*pHtml << _T("</B><BR>\r\n");

			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteReSetEligibility(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				strSQL.Format( "UPDATE ParticipantForSeries SET	EligibilityForEvent = 'Y' WHERE SeriesID = %d ", iSeriesID ); 
				db.ExecuteSQL( strSQL );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			CCountResultSet rsCount( &db );

			strSQL.Format( "SELECT COUNT(*) FROM ParticipantForSeries WHERE EligibilityForEvent = 'Y' AND SeriesID = %d ", iSeriesID);
			rsCount.Open(CRecordset::forwardOnly, strSQL );

			ShowResultMessage(pHtml, rsCount.m_Total, "");

			rsCount.Close( );

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetEligibilityXMore(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				CDatabase dbUpdate;
		
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				int iEventNo;
				int iPrevEventNo;
				int iEventsNeeded;
				int iEventCount;
				int iLastXEvents;
				int iRules;

				int iEventCountLow;
				int iEventCountHigh;

				// get the EventNo (of the Previous Event) from the EventID
				CEventSet rsEvent( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_PREVEVENT);
				strSQL.Format( strSQLtmp, iSeriesID, iSeriesID, iEventID );
				rsEvent.Open(CRecordset::forwardOnly, strSQL );

				iPrevEventNo = rsEvent.m_EventNo;
				rsEvent.Close( );


				// get the EventNo from the EventID
				strSQL.Format( "SELECT * FROM Event WHERE EventID = %d AND SeriesID = %d", iEventID, iSeriesID);
				rsEvent.Open(CRecordset::forwardOnly, strSQL );

				iEventNo = rsEvent.m_EventNo;
				rsEvent.Close( );


				// count the number of rules to get EventsNeeded
				CCountResultSet rsCount( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iEventsNeeded = rsCount.m_Total;
				iRules = rsCount.m_Total;
				rsCount.Close( );


				// find the max rule to get LastXEvents
				//CCountResultSet rsCount( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" MAX(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iLastXEvents = rsCount.m_Total;
				rsCount.Close( );



				// reset Eligibility with the first iEventsNeeded (rule count)
				strSQL.Format( "UPDATE ParticipantForSeries SET	EligibilityForEvent = '%d' WHERE SeriesID = %d", iEventsNeeded, iSeriesID ); 
				try
				{
					dbUpdate.ExecuteSQL( strSQL );
				}
				catch (CDBException* pEx)
				{
					*pHtml << pEx;

					pEx->Delete();
				}



				// get all the rules
				CRulesSet rsRules( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" Rules.* ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				strSQL += " ORDER BY Rules.Law ";
				rsRules.Open(CRecordset::forwardOnly, strSQL );

				iEventCount = 0;

				CString strElig = " ";

				// 1st pass

				while( !rsRules.IsEOF( ) )
				{
					iEventCountLow = iEventCount ;//+1;

					iEventCount = rsRules.m_Law;
					iEventsNeeded = iEventsNeeded -1;

					iEventCountHigh = iEventCount -1;

					CString strRange = "";

					if(iEventsNeeded > 0)
					{
						strRange +=     _T(" BETWEEN ") ;
						strRange += CConvert::itoa(iEventCountLow);
						strRange +=     _T(" AND ") ;
						strRange += CConvert::itoa(iEventCountHigh);
						strRange +=     _T(" ");
					}
					else
					{
						strRange +=     _T(" >= ") ;
						strRange += CConvert::itoa(iEventCountLow);
						strRange +=     _T(" ");
					}

					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEELIGIBILITYXMORE);
					strSQL.Format( strSQLtmp, iEventsNeeded, iSeriesID, iSeriesID, iEventNo, iLastXEvents, iPrevEventNo, strElig, strRange );

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					rsRules.MoveNext();
				}

				rsRules.Close( );



				// 2nd pass

				strElig = _T(" AND ParticipantForSeries.EligibilityForEvent <> '0' ");

				iEventsNeeded = 0;

				for( int i = iRules ; i > 0 ; i-- )
				{
					CString strRange = "";

					strRange +=     _T(" = ") ;
					strRange += CConvert::itoa(i);
					strRange +=     _T(" ");


					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEELIGIBILITYXMORE);
					strSQL.Format( strSQLtmp, iEventsNeeded, iSeriesID, iSeriesID, iEventNo, iRules, iPrevEventNo, strElig, strRange );

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iEventsNeeded++;
				}


				// set Eligibility from EventsNeeded == 0 to 'Y'
				strSQL.Format( "UPDATE ParticipantForSeries SET	EligibilityForEvent = 'Y' WHERE SeriesID = %d AND EligibilityForEvent = '0'", iSeriesID ); 
				try
				{
					dbUpdate.ExecuteSQL( strSQL );
				}
				catch (CDBException* pEx)
				{
					*pHtml << pEx;

					pEx->Delete();
				}

				dbUpdate.Close( );



				CCountItemSet rsItem( &db );

				strSQL.Format( "SELECT COUNT(*) AS Total, EligibilityForEvent AS Details FROM ParticipantForSeries WHERE SeriesID = %d GROUP BY EligibilityForEvent ORDER BY EligibilityForEvent ", iSeriesID);
				rsItem.Open(CRecordset::forwardOnly, strSQL );

				while( !rsItem.IsEOF( ) )
				{
					if( atoi(rsItem.m_Details) || !rsItem.m_Details.Compare("Y") )
					{
						CString strComment;
						strComment += _T("Eligible = '");
						strComment += _T(rsItem.m_Details);
						strComment += _T("'");

						ShowResultMessage(pHtml, rsItem.m_Total, strComment);
					}
					rsItem.MoveNext();
				}
				rsItem.Close( );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteRebuildParticipantForSeries(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				strSQL.Format( "DELETE FROM ParticipantForSeries WHERE SeriesID = %d", iSeriesID ); 
				db.ExecuteSQL( strSQL );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			try
			{
				int iEventNo;

				CEventSet rsEvent( &db );

				strSQL.Format( "SELECT * FROM Event WHERE EventID = %d AND SeriesID = %d", iEventID, iSeriesID);

				rsEvent.Open(CRecordset::forwardOnly, strSQL );
				iEventNo = rsEvent.m_EventNo;
				rsEvent.Close( );


				// this pass uses people who have been re-grouped in the last event
				// ie they have a NewGroupID <> NULL AND NewGroupID <> 0
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPARTICIPANTFORSERIES);
				strSQL.Format(strSQLtmp,
					"NewGroupID",
					'Y',
					iSeriesID,
					iSeriesID,
					iEventNo,
					iSeriesID,
					"r.NewGroupID IS NOT NULL AND r.NewGroupID > 0"
					);
				db.ExecuteSQL( strSQL );

				// this pass uses people who have not been re-grouped in the last event
				// ie they have a NewGroupID == NULL OR NewGroupID == 0
				strSQL.Format(strSQLtmp,
					"GroupIDSupposedTo",
					'Y',
					iSeriesID,
					iSeriesID,
					iEventNo,
					iSeriesID,
					"r.NewGroupID IS NULL OR r.NewGroupID < 1"
					);
				db.ExecuteSQL( strSQL );

			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			CCountResultSet rsCount( &db );

			strSQL.Format( "SELECT COUNT(*) FROM ParticipantForSeries WHERE SeriesID = %d ", iSeriesID);
			rsCount.Open(CRecordset::forwardOnly, strSQL );

			ShowResultMessage(pHtml, rsCount.m_Total, "");

			rsCount.Close( );

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetDivisionEligibility(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );
			
			try
			{
				int iSkipProcess;
				int iTimed;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// count the number of rules to get Eligible Regardless of Division
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Processing), 
					CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfDivision) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iSkipProcess = rsCount.m_Total;
				rsCount.Close( );

				if( iSkipProcess )
				{
					*pHtml << _T("Skipping Process <B>");
					*pHtml << _T(CProcess::GetName(dwProc));
					*pHtml << _T("</B> due to <B>");
					*pHtml << _T(CRuleType::GetName(CRuleType::Processing));
					*pHtml << _T("</B> Rule <B>");
					*pHtml << _T(CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfDivision));
					*pHtml << _T("</B>.<BR>\r\n");
				}
				else
				{
					// get Timed
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
					strSQL.Format(strSQLtmp, iSeriesID, iEventID );
					rsCount.Open(CRecordset::forwardOnly, strSQL );
					iTimed = rsCount.m_Total;
					rsCount.Close( );

					switch( iTimed ) 
					{
						case 1 : // Long Distance
						{

							CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEELIGIBILITYDIVISION);
							strSQL.Format(strSQLtmp, iSeriesID, iEventID, iSeriesID, iEventID );
							db.ExecuteSQL( strSQL );
						}
						break;
						case 0 : // Jump or Throw
						{
							// Do Nothing, Division is not counted for eligibility
						}
						break;
						case 2 : // Sprint
						{
							// Do Nothing, Division is not counted for eligibility
						}
						break;
					}

					strSQL.Format( "SELECT COUNT(*) FROM Results WHERE Eligible = 'D' AND SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					ShowResultMessage(pHtml, rsCount.m_Total, "Eligible = 'D'");

					rsCount.Close( );
				}
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetGroupsEligibility(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iSkipProcess;

				CCountResultSet rsCount( &db );

				// count the number of rules to get Eligible Regardless of Group
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Processing), 
					CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfGroup) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iSkipProcess = rsCount.m_Total;
				rsCount.Close( );

				if( iSkipProcess )
				{
					*pHtml << _T("Skipping Process <B>");
					*pHtml << _T(CProcess::GetName(dwProc));
					*pHtml << _T("</B> due to <B>");
					*pHtml << _T(CRuleType::GetName(CRuleType::Processing));
					*pHtml << _T("</B> Rule <B>");
					*pHtml << _T(CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfGroup));
					*pHtml << _T("</B>.<BR>\r\n");
				}
				else
				{
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEELIGIBILITYGROUPS);
					strSQL.Format(strSQLtmp, iSeriesID, iEventID, iSeriesID, iEventID );
					db.ExecuteSQL( strSQL );
				}

				strSQL.Format( "SELECT COUNT(*) FROM Results WHERE Eligible = 'G' AND SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				ShowResultMessage(pHtml, rsCount.m_Total, "Eligible = 'G'");

				rsCount.Close( );
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecutePadPreResults(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iEventsNeeded;
				char cDefaultElig;

				// count the number of rules to get EventsNeeded
				CCountResultSet rsCount( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iEventsNeeded = rsCount.m_Total;
				rsCount.Close( );

				// set the default Elig based on the rules
				if( iEventsNeeded < 1 )
					cDefaultElig = 'Y';
				else
					cDefaultElig = 'X';

				// insert into ParticipantForSeries if the person is not there
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPFSPRERESULTS);
				strSQL.Format(strSQLtmp, cDefaultElig, iSeriesID, iSeriesID, iEventID );
				db.ExecuteSQL( strSQL );

				// clear the results for the insert
				strSQL.Format( "DELETE FROM Results WHERE EventID = %d AND SeriesID = %d", iEventID, iSeriesID);
				db.ExecuteSQL( strSQL );

				// insert into results
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPRERESULTS);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				db.ExecuteSQL( strSQL );
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			CCountResultSet rsCount( &db );

			strSQL.Format( "SELECT COUNT(*) FROM Results WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
			rsCount.Open(CRecordset::forwardOnly, strSQL );

			ShowResultMessage(pHtml, rsCount.m_Total, "");

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

BOOL CProcessor::ExecuteClosePreEntry(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				strSQL.Format( "UPDATE Event SET PreEntryOpen = 0 WHERE SeriesID = %d AND EventID = %d ", iSeriesID, iEventID ); 
				db.ExecuteSQL( strSQL );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			//ShowResultMessage(pHtml, 1, "Pre-Event Entry Closed From Members and Public");

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecutePadPostResults(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iEventsNeeded;
				char cDefaultElig;

				// count the number of rules to get EventsNeeded
				CCountResultSet rsCount( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iEventsNeeded = rsCount.m_Total;
				rsCount.Close( );

				// set the default Elig based on the rules
				if( iEventsNeeded < 1 )
					cDefaultElig = 'Y';
				else
					cDefaultElig = 'X';


				// insert into ParticipantForSeries if the person is not there
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPFSPOSTRESULTS);
				strSQL.Format(strSQLtmp, cDefaultElig, iSeriesID, iSeriesID, iEventID );
				db.ExecuteSQL( strSQL );

				// remove results that were inserted from pre-event entries, but did not run
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_DELETERESULTSPREEVENTNOPOSTEVENT);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID, iSeriesID, iEventID);
				db.ExecuteSQL( strSQL );

				// clear the results for the insert
				strSQL.Format( "DELETE FROM Results WHERE EventID = %d AND SeriesID = %d", iEventID, iSeriesID);
				db.ExecuteSQL( strSQL );

				// insert into results
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPOSTRESULTS);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				db.ExecuteSQL( strSQL );
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}

			CCountResultSet rsCount( &db );

			strSQL.Format( "SELECT COUNT(*) FROM Results WHERE SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
			rsCount.Open(CRecordset::forwardOnly, strSQL );

			ShowResultMessage(pHtml, rsCount.m_Total, "");

			rsCount.Close( );

			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetPointScore(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{

				CDatabase dbUpdate;
		
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );


				int iFirstEventNo;
				int iEventsNeeded;
				int iEventsToCount;
				char cDefaultElig;

				CCountResultSet rsCount( &db );

				// get the EventNo of the FirstEventForSeason
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETFIRSTEVENTFORSEASON);
				strSQL.Format(strSQLtmp, iSeriesID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iFirstEventNo = rsCount.m_Total;
				rsCount.Close( );

				// count the number of rules to get EventsNeeded
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iEventsNeeded = rsCount.m_Total;
				rsCount.Close( );

				// set the default Elig based on the rules
				if( iEventsNeeded < 1 )
					cDefaultElig = 'Y';
				else
					cDefaultElig = 'X';

				// insert into ParticipantForSeries if the person is not there
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTPFSPOINTSCORE);
				strSQL.Format(strSQLtmp, cDefaultElig, iSeriesID, iSeriesID, iFirstEventNo );
				db.ExecuteSQL( strSQL );

				// get EventsToCount for points
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" Rules.Law AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Pointscore), 
					CRuleSubType::GetName(CRuleSubType::PointscoreEventsToCountForPoints) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				iEventsToCount = rsCount.m_Total;
				rsCount.Close( );


				CResultsSet rs( &db );

				// get the List of Pointscores for each person
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETLISTPOINTSCORES);
				strSQL.Format(strSQLtmp, iSeriesID, iFirstEventNo );
				rs.Open(CRecordset::forwardOnly, strSQL );


				int iPointScoreCount = 0;

				// for each person, calculate their pointscores

				int accPersonId = 0;
				int iPersonID = 0;
				int iPoints = 0;

				if( !rs.IsEOF( ) )
				{
					accPersonId = rs.m_PersonID;
					iPersonID = rs.m_PersonID;
					iPoints = rs.m_Points;
				}

				while( !rs.IsEOF( ) )
				{
					// Get the best x Events for the Person

					int iEventCounter = 0;

					int accGrossPoints = 0 ;
					int accNetPoints = 0 ;
					int accLowPoints = 0 ;


					while( !rs.IsEOF( ) && (accPersonId == iPersonID) )
					{
						if ( iEventCounter < iEventsToCount )
						{
							accGrossPoints += iPoints;
							accNetPoints   += iPoints;
							accLowPoints    = iPoints;
						}
						if (iEventCounter >= iEventsToCount)
						{
							accGrossPoints += iPoints;
						}

						rs.MoveNext( );

						if( !rs.IsEOF( ) )
						{
							iPersonID = rs.m_PersonID;
							iPoints = rs.m_Points;
						}
						iEventCounter++;
					}

					// update the Participants PointScore details
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEPOINTSCORES);
					strSQL.Format(strSQLtmp, accGrossPoints, accNetPoints, accLowPoints, iSeriesID, accPersonId );

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}


					if( !rs.IsEOF( ) )
					{
						accPersonId = rs.m_PersonID;
					}

					iPointScoreCount++;

				}
				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iPointScoreCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetOverAllPlace(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				int iPlaceByDivision;
				CString strOrder;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

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


				if( iTimed > 0) // Long Distance, // Sprint
				{
					strOrder.Format("ASC");
				}
				else // Jump or Throw
				{
					strOrder.Format("DESC");
				}


				CResultsSet rs( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTRESULTSORDERBYGROSSPERF);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrder, strOrder, strOrder );
				rs.Open(CRecordset::forwardOnly, strSQL );


				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEOVERALLPLACE);

				int iPlaceCount = 0;

				while( !rs.IsEOF( ) )
				{
					iPlaceCount++;

					int iPlace;

					if( iPlaceByDivision > 0 )
						iPlace = rs.m_Place;
					else
						iPlace = iPlaceCount;

					strSQL.Format(strSQLtmp, iPlace, rs.m_SeriesID, rs.m_EventID, rs.m_PersonID );

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					rs.MoveNext( );
				}
				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iPlaceCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

/*
BOOL CProcessor::ExecuteSetMiscResults(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				int iPlaceByDivision;
				int iMaxPoints;
				int iMinPoints;
				int iPointscale;
				int iDivisions;
				int iParticipantCount;
				int iPointScoreRules;
				double dEventLength;

				CDoubleSet rsDouble( &db );

				// get Event Length
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTLENGTH);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsDouble.Open(CRecordset::forwardOnly, strSQL );
				dEventLength = rsDouble.m_Val;
				rsDouble.Close( );


				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

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

				// get PointScoreRules
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULETYPE);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Pointscore) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iPointScoreRules = rsCount.m_Total;
				rsCount.Close( );

				if( iPointScoreRules > 0)
				{
					// get MaxPoints
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscoreMaximumPoints) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iMaxPoints = 100;
					else
						iMaxPoints = rsCount.m_Total;

					rsCount.Close( );

					// get MinPoints
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscoreMinimumPoints) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iMinPoints = 0;
					else
						iMinPoints = rsCount.m_Total;
					
					rsCount.Close( );

					// get Pointscale
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscorePointscale) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iPointscale = iMaxPoints;
					else
						iPointscale = rsCount.m_Total;

					rsCount.Close( );
				}

				// get Divisions
				strSQL.Format( "SELECT MAX(DivisionActual) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d ", 
					iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iDivisions = rsCount.m_Total;
				rsCount.Close( );

				// get ParticipantCount
				strSQL.Format( "SELECT MAX(OverallPlace) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d ",
					iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iParticipantCount = rsCount.m_Total;
				rsCount.Close( );


				CString strOrderBy;

				if( iPlaceByDivision > 0 )
				{
					strOrderBy = " ORDER BY Results.DivisionActual, Results.OverallPlace, Results.Place ";
				}
				else
				{
					strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";
				}


				CResultsSet rs( &db );

				strSQLtmp = _T("SELECT * FROM Results WHERE SeriesID = %d AND EventID = %d %s");

				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iMiscCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				int iDivision = 0;

				int iLastPlace = 0;
				int iPoint = iMaxPoints;
				int iOldPoint = iPoint;

				int iLastGrossPerfHOUR = 0;
				int iLastGrossPerfMIN = 0;
				double dLastGrossPerfSEC = 0.0;

				while( !rs.IsEOF( ) )
				{
					double dGrossPerfSEC;
					double dNetPerfSEC;

					int iNetPerformanceHOUR;
					int iNetPerformanceMIN;
					double dNetPerformanceSEC;

					int iPoints;
					int iPercentile;
					double dEventRate;

					// Reset Counters for PlaceByDivision ( Calc Points )

					if( iPlaceByDivision > 0 )
					{
						if( iDivision != rs.m_DivisionActual )
						{
							iDivision = rs.m_DivisionActual;

							iLastPlace = 0;
							iPoint = iMaxPoints;
							iOldPoint = iPoint;

							CCountResultSet rsCount( &dbUpdate );

							// get ParticipantCount for Division
							strSQL.Format( "SELECT MAX(OverallPlace) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d AND Results.DivisionActual = %d ",
								iSeriesID, iEventID, iDivision );
							rsCount.Open(CRecordset::forwardOnly, strSQL );
							iParticipantCount = rsCount.m_Total;
							rsCount.Close( );
						}
					}

					dGrossPerfSEC = CCalculate::GetSeconds(
						rs.m_GrossPerformanceHOUR,
						rs.m_GrossPerformanceMIN,
						rs.m_GrossPerformanceSEC
					);

					// Calculate NetPerformance

					dNetPerfSEC = CCalculate::GetNetPerformance(
						iTimed,
						rs.m_GroupStartActual,
						rs.m_GrossPerformanceHOUR,
						rs.m_GrossPerformanceMIN,
						rs.m_GrossPerformanceSEC
					);

					iNetPerformanceHOUR = CCalculate::GetHoursPart(dNetPerfSEC);
					iNetPerformanceMIN = CCalculate::GetMinutesPart(dNetPerfSEC);
					dNetPerformanceSEC = CCalculate::GetSecondsPart(dNetPerfSEC);

					// Calculate Percentile

					iPercentile = CCalculate::GetPercentile(rs.m_OverallPlace, iParticipantCount);

					// Calculate EventRate
				
					if( iTimed == 1 )  // Long Distance
					{
						dEventRate = CCalculate::GetEventRateLongDistance(dEventLength, dNetPerfSEC);
					}
					else if( iTimed == 0 )  // Jump or Throw
					{
						dEventRate = CCalculate::GetEventRateJumpThrow(dEventLength, dGrossPerfSEC);
					}
					else if( iTimed == 2 )  // Sprint
					{
						dEventRate = CCalculate::GetEventRateSprint(dEventLength, dGrossPerfSEC, rs.m_GroupStartActual);
					}

					// Calculate Points

					if( iPointScoreRules > 0)
					{
						bool bSamePlaceDone = false;

						int iPointDecValue;

						if( !rs.m_Eligible.Compare("Y") ) // Eligible
						{
							if( rs.m_Place != iLastPlace )
							{
								iPoints = iPoint;

								iPointDecValue = CCalculate::GetPointDecrementValue(iPoint, iPointscale);

								iOldPoint = iPoint;

								if( iPoint > iMinPoints )
									iPoint = iPoint - iPointDecValue;
								else
									iPoint = iMinPoints;
							}
							else // same place
							{
								if( iPlaceByDivision > 0 ) // Overall-Place by Division
								{
									iPoints = iOldPoint;
								}
								else // Overall-Place by Place
								{

									iPoints = iPoint;

									iPointDecValue = CCalculate::GetPointDecrementValue(iPoint, iPointscale);

									if( iPoint > iMinPoints )
										iPoint = iPoint - iPointDecValue;
									else
										iPoint = iMinPoints;

								}
								bSamePlaceDone = true;
							}

							if( iPlaceByDivision == 0 ) // Overall-Place by Place
							{
								if( rs.m_GrossPerformanceHOUR == iLastGrossPerfHOUR &&
									rs.m_GrossPerformanceMIN == iLastGrossPerfMIN &&
									rs.m_GrossPerformanceSEC == dLastGrossPerfSEC )
								{
									if( bSamePlaceDone ) // Same Performance
									{
										iPoints = iOldPoint + iPointDecValue;
									}
									else // Same Performance AND Same Place
									{
										iPoints = iOldPoint;
									}

								}

								iLastGrossPerfHOUR = rs.m_GrossPerformanceHOUR;
								iLastGrossPerfMIN = rs.m_GrossPerformanceMIN;
								dLastGrossPerfSEC = rs.m_GrossPerformanceSEC;

							}

							iLastPlace = rs.m_Place;
						}
						else // not Eligible
						{
							iPoints = 0;
						}

					}
					else
					{
						iPoints = 0;
					}

					// Update Results

					strSQL = "";

					strSQL +=     _T("UPDATE Results ");

					strSQL +=     _T("SET Results.NetPerformanceHOUR = ");
					strSQL += CConvert::itoa(iNetPerformanceHOUR);
					strSQL +=     _T(", ");
					strSQL +=     _T("Results.NetPerformanceMIN = ");
					strSQL += CConvert::itoa(iNetPerformanceMIN);
					strSQL +=     _T(", ");
					strSQL +=     _T("Results.NetPerformanceSEC = ");
					strSQL += CConvert::dtoa(dNetPerformanceSEC,7);
					strSQL +=     _T(", ");

					strSQL +=     _T("Results.Percentile = ");
					strSQL += CConvert::itoa(iPercentile);
					strSQL +=     _T(", ");

					//if( iPointScoreRules > 0)
					//{
						strSQL +=     _T("Results.Points = ");
						strSQL += CConvert::itoa(iPoints);
						strSQL +=     _T(", ");
					//}

					strSQL +=     _T("Results.EventRate = ");
					strSQL += CConvert::dtoa(dEventRate,7);
					strSQL +=     _T(" ");

					strSQL +=     _T("WHERE Results.SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.EventID = ");
					strSQL += CConvert::itoa(iEventID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.PersonID = ");
					strSQL += CConvert::itoa(rs.m_PersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iMiscCount++;

					rs.MoveNext( );
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iMiscCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}
*/

BOOL CProcessor::ExecuteSetNetPerformance(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );


				CString strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";

				CResultsSet rs( &db );

				strSQLtmp = _T("SELECT * FROM Results WHERE SeriesID = %d AND EventID = %d %s");

				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iNetPerformanceCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					double dNetPerfSEC;

					int iNetPerformanceHOUR;
					int iNetPerformanceMIN;
					double dNetPerformanceSEC;

					// Calculate NetPerformance

					dNetPerfSEC = CCalculate::GetNetPerformance(
						iTimed,
						rs.m_GroupStartActual,
						rs.m_GrossPerformanceHOUR,
						rs.m_GrossPerformanceMIN,
						rs.m_GrossPerformanceSEC
					);

					if(iTimed == 0) // Jump or Throw
					{
						iNetPerformanceHOUR = 0;
						iNetPerformanceMIN = 0;
						dNetPerformanceSEC = dNetPerfSEC;
					}
					else
					{
						iNetPerformanceHOUR = CCalculate::GetHoursPart(dNetPerfSEC);
						iNetPerformanceMIN = CCalculate::GetMinutesPart(dNetPerfSEC);
						dNetPerformanceSEC = CCalculate::GetSecondsPart(dNetPerfSEC);
					}

					// Update Results

					strSQL = "";

					strSQL +=     _T("UPDATE Results ");

					strSQL +=     _T("SET Results.NetPerformanceHOUR = ");
					strSQL += CConvert::itoa(iNetPerformanceHOUR);
					strSQL +=     _T(", ");
					strSQL +=     _T("Results.NetPerformanceMIN = ");
					strSQL += CConvert::itoa(iNetPerformanceMIN);
					strSQL +=     _T(", ");
					strSQL +=     _T("Results.NetPerformanceSEC = ");
					strSQL += CConvert::dtoa(dNetPerformanceSEC,7);
					strSQL +=     _T(" ");

					strSQL +=     _T("WHERE Results.SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.EventID = ");
					strSQL += CConvert::itoa(iEventID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.PersonID = ");
					strSQL += CConvert::itoa(rs.m_PersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iNetPerformanceCount++;

					rs.MoveNext( );
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iNetPerformanceCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

BOOL CProcessor::ExecuteSetPercentile(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				int iParticipantCount;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

				// get ParticipantCount
				strSQL.Format( "SELECT MAX(OverallPlace) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d ",
					iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iParticipantCount = rsCount.m_Total;
				rsCount.Close( );

				CString strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";

				CResultsSet rs( &db );

				strSQLtmp = _T("SELECT * FROM Results WHERE SeriesID = %d AND EventID = %d %s");

				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iPercentileCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					int iPercentile;

					// Calculate Percentile

					iPercentile = CCalculate::GetPercentile(rs.m_OverallPlace, iParticipantCount);

					// Update Results

					strSQL = "";

					strSQL +=     _T("UPDATE Results ");

					strSQL +=     _T("SET Results.Percentile = ");
					strSQL += CConvert::itoa(iPercentile);
					strSQL +=     _T(" ");

					strSQL +=     _T("WHERE Results.SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.EventID = ");
					strSQL += CConvert::itoa(iEventID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.PersonID = ");
					strSQL += CConvert::itoa(rs.m_PersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iPercentileCount++;

					rs.MoveNext( );
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iPercentileCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

BOOL CProcessor::ExecuteSetPoints(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				int iPlaceByDivision;
				int iMaxPoints;
				int iMinPoints;
				int iPointscale;
				int iDivisions;
				int iParticipantCount;
				int iPointScoreRules;


				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

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

				// get PointScoreRules
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULETYPE);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Pointscore) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iPointScoreRules = rsCount.m_Total;
				rsCount.Close( );

				if( iPointScoreRules > 0)
				{
					// get MaxPoints
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscoreMaximumPoints) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iMaxPoints = 100;
					else
						iMaxPoints = rsCount.m_Total;

					rsCount.Close( );

					// get MinPoints
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscoreMinimumPoints) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iMinPoints = 0;
					else
						iMinPoints = rsCount.m_Total;
					
					rsCount.Close( );

					// get Pointscale
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
					strSQL.Format( strSQLtmp, 
						" Rules.Law AS Total ", 
						iSeriesID, 
						CRuleType::GetName(CRuleType::Pointscore), 
						CRuleSubType::GetName(CRuleSubType::PointscorePointscale) );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
						iPointscale = iMaxPoints;
					else
						iPointscale = rsCount.m_Total;

					rsCount.Close( );
				}

				// get Divisions
				strSQL.Format( "SELECT MAX(DivisionActual) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d ", 
					iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iDivisions = rsCount.m_Total;
				rsCount.Close( );

				// get ParticipantCount
				strSQL.Format( "SELECT MAX(OverallPlace) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d ",
					iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iParticipantCount = rsCount.m_Total;
				rsCount.Close( );


				CString strOrderBy;

				if( iPlaceByDivision > 0 )
				{
					strOrderBy = " ORDER BY Results.DivisionActual, Results.OverallPlace, Results.Place ";
				}
				else
				{
					strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";
				}


				CResultsPostResultsSet rs( &db );

				strSQLtmp = _T("SELECT * FROM Results, PostResults WHERE Results.SeriesID = PostResults.SeriesID AND Results.EventID = PostResults.EventID AND Results.PersonID = PostResults.PersonID AND Results.SeriesID = %d AND Results.EventID = %d %s");

				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iPointsCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				int iDivision = 0;

				int iLastPlace = 0;
				int iPoint = iMaxPoints;
				int iOldPoints = iMaxPoints;

				int iLastGrossPerfHOUR = 0;
				int iLastGrossPerfMIN = 0;
				double dLastGrossPerfSEC = 0.0;

				bool bSamePlaceDone = false;

				while( !rs.IsEOF( ) )
				{
					int iPoints;

					// Reset Counters for PlaceByDivision ( Calc Points )

					if( iPlaceByDivision > 0 )
					{
						if( iDivision != rs.m_DivisionActual )
						{
							iDivision = rs.m_DivisionActual;

							iLastPlace = 0;
							iPoint = iMaxPoints;
							iOldPoints = iMaxPoints;

							CCountResultSet rsCount( &dbUpdate );

							// get ParticipantCount for Division
							strSQL.Format( "SELECT MAX(OverallPlace) AS Total FROM Results WHERE SeriesID = %d AND EventID = %d AND Results.DivisionActual = %d ",
								iSeriesID, iEventID, iDivision );
							rsCount.Open(CRecordset::forwardOnly, strSQL );
							iParticipantCount = rsCount.m_Total;
							rsCount.Close( );
						}
					}

					// Calculate Points

					if( iPointScoreRules > 0)
					{
						int iPointDecValue = CCalculate::GetPointDecrementValue(iPoint, iPointscale);

						if( !rs.m_Eligible.Compare("Y") ) // Eligible
						{
							if( rs.m_Place != iLastPlace )
							{
								iPoints = iPoint;

								if( iPoint > iMinPoints )
									iPoint = iPoint - iPointDecValue;
								else
									iPoint = iMinPoints;
							}
							else // same place
							{
								//if( iPlaceByDivision > 0 ) // Overall-Place by Division
								//{
								//	iPoints = iOldPoints;
								//}
								//else // Overall-Place by Place
								{
									iPoints = iPoint;

									if( iPoint > iMinPoints )
										iPoint = iPoint - iPointDecValue;
									else
										iPoint = iMinPoints;

								}
								bSamePlaceDone = true;
							}

							//if( iPlaceByDivision == 0 ) // Overall-Place by Place
							{
								if( rs.m_GrossPerformanceHOUR == iLastGrossPerfHOUR &&
									rs.m_GrossPerformanceMIN == iLastGrossPerfMIN &&
									rs.m_GrossPerformanceSEC == dLastGrossPerfSEC )
								{
									if( bSamePlaceDone ) // Same Performance AND Same Place
									{
										iPoints = iOldPoints;

										// SamePlace used, reset the value
										bSamePlaceDone = false;
									}
									else // Same Performance
									{
										iPoints = iPoint + iPointDecValue;
									}
							
								}
							
							}

							iLastGrossPerfHOUR = rs.m_GrossPerformanceHOUR;
							iLastGrossPerfMIN = rs.m_GrossPerformanceMIN;
							dLastGrossPerfSEC = rs.m_GrossPerformanceSEC;

							iLastPlace = rs.m_Place;
						}
						else // not Eligible
						{
							iPoints = 0;
						}

					}
					else if( !rs.IsFieldNull( &rs.m_Post_Points ) )
					{
						iPoints = rs.m_Post_Points;
					}
					else
					{
						iPoints = 0;
					}

					if( iPoints > iMinPoints )
						iOldPoints = iPoints;

					// Update Results

					strSQL = "";

					strSQL +=     _T("UPDATE Results ");

					//if( iPointScoreRules > 0)
					//{
						strSQL +=     _T("SET Results.Points = ");
						strSQL += CConvert::itoa(iPoints);
						strSQL +=     _T(" ");
					//}

					strSQL +=     _T("WHERE Results.SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.EventID = ");
					strSQL += CConvert::itoa(iEventID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.PersonID = ");
					strSQL += CConvert::itoa(rs.m_PersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iPointsCount++;

					rs.MoveNext( );
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iPointsCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

BOOL CProcessor::ExecuteSetEventRate(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				double dEventLength;

				CDoubleSet rsDouble( &db );

				// get Event Length
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTLENGTH);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsDouble.Open(CRecordset::forwardOnly, strSQL );
				dEventLength = rsDouble.m_Val;
				rsDouble.Close( );


				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );


				CString strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";

				CResultsSet rs( &db );

				strSQLtmp = _T("SELECT * FROM Results WHERE SeriesID = %d AND EventID = %d %s");

				strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iEventRateCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					double dGrossPerfSEC;
					double dNetPerfSEC;

					double dEventRate;

					dGrossPerfSEC = CCalculate::GetSeconds(
						rs.m_GrossPerformanceHOUR,
						rs.m_GrossPerformanceMIN,
						rs.m_GrossPerformanceSEC
					);

					// Calculate NetPerformance

					dNetPerfSEC = CCalculate::GetNetPerformance(
						iTimed,
						rs.m_GroupStartActual,
						rs.m_GrossPerformanceHOUR,
						rs.m_GrossPerformanceMIN,
						rs.m_GrossPerformanceSEC
					);

					// Calculate EventRate
				
					if( iTimed == 1 )  // Long Distance
					{
						dEventRate = CCalculate::GetEventRateLongDistance(dEventLength, dNetPerfSEC);
					}
					else if( iTimed == 0 )  // Jump or Throw
					{
						dEventRate = CCalculate::GetEventRateJumpThrow(dEventLength, dNetPerfSEC);
					}
					else if( iTimed == 2 )  // Sprint
					{
						dEventRate = CCalculate::GetEventRateSprint(dEventLength, dGrossPerfSEC, rs.m_GroupStartActual);
					}

					// Update Results

					strSQL = "";

					strSQL +=     _T("UPDATE Results ");

					strSQL +=     _T("SET Results.EventRate = ");
					strSQL += CConvert::dtoa(dEventRate,7);
					strSQL +=     _T(" ");

					strSQL +=     _T("WHERE Results.SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.EventID = ");
					strSQL += CConvert::itoa(iEventID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND Results.PersonID = ");
					strSQL += CConvert::itoa(rs.m_PersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					iEventRateCount++;

					rs.MoveNext( );
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iEventRateCount, "");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetWorldStandards(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				int iIsItWava;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

				// get IsItWava
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_ISITWAVA);
				strSQL.Format( strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iIsItWava = rsCount.m_Total;
				rsCount.Close( );


				if( iIsItWava > 0 )
				{
					CString strOrderBy = " ORDER BY Results.OverallPlace, Results.Place ";

					CResultsWorldStandardSet rs( &db );

					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETWAVARESULTS);

					strSQL.Format(strSQLtmp, iSeriesID, iEventID, strOrderBy );
					rs.Open(CRecordset::forwardOnly, strSQL );

					int iWorldStandardCount = 0;

					CDatabase dbUpdate;
					dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

					while( !rs.IsEOF( ) )
					{
						double dNetPerfSEC;
						double dWSPerfSEC;

						double dWorldStandard;

						// Calculate NetPerformance

						dNetPerfSEC = CCalculate::GetNetPerformance(
							iTimed,
							rs.m_GroupStartActual,
							rs.m_GrossPerformanceHOUR,
							rs.m_GrossPerformanceMIN,
							rs.m_GrossPerformanceSEC
						);

						// Calculate WorldStandard

						if( iIsItWava > 0 )
						{
							if(iTimed > 0) // Long Distance // Sprint
							{
								dWSPerfSEC = CCalculate::GetSeconds(
									rs.m_PerfHOUR,
									rs.m_PerfMIN,
									rs.m_PerfSEC
								);

								dWorldStandard = (dWSPerfSEC / dNetPerfSEC) * 100.0;
							}
							else // Jump or Throw
							{
								dWSPerfSEC = rs.m_PerfSEC;

								dWorldStandard = (dNetPerfSEC / dWSPerfSEC) * 100.0;
							}
						}


						// Update Results

						strSQL = "";

						strSQL +=     _T("UPDATE Results ");

						strSQL +=     _T("SET Results.WorldStandard = ");
						strSQL += CConvert::dtoa(dWorldStandard,7);
						strSQL +=     _T(" ");

						strSQL +=     _T("WHERE Results.SeriesID = ");
						strSQL += CConvert::itoa(iSeriesID);
						strSQL +=     _T(" ");
						strSQL +=     _T("AND Results.EventID = ");
						strSQL += CConvert::itoa(iEventID);
						strSQL +=     _T(" ");
						strSQL +=     _T("AND Results.PersonID = ");
						strSQL += CConvert::itoa(rs.m_PersonID);
						strSQL +=     _T(" ");

						try
						{
							dbUpdate.ExecuteSQL( strSQL );
						}
						catch (CDBException* pEx)
						{
							*pHtml << pEx;

							pEx->Delete();
						}

						rs.MoveNext( );

						iWorldStandardCount++;
					}

					dbUpdate.Close( );
					rs.Close( );

					ShowResultMessage(pHtml, iWorldStandardCount, "");
				}
				else
				{
					*pHtml << _T("No Age Standards on this Event.<BR>\r\n");
				}
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetConsistencyEventsRate(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		// Process split off from SetConsistencyRate

		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
//				int iTimed;
				int iEventsNeeded;
				int iEventsToCount;
				int iFirstEventNo;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				// NO, BAD!
				// cant get Timed from the EventID, because the EventID
				// doesn't exist for this process, ie it is a 
				// ParticipantForSeries process


				// count the number of rules to get EventsNeeded
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iEventsNeeded = rsCount.m_Total;
				rsCount.Close( );

				// get the EventNo of the FirstEventForSeason
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETFIRSTEVENTFORSEASON);
				strSQL.Format(strSQLtmp, iSeriesID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iFirstEventNo = rsCount.m_Total;
				rsCount.Close( );

				// get Events to qualify for Consistency
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" Rules.Law AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Consistency), 
					CRuleSubType::GetName(CRuleSubType::ConsistencyEventsToQualify) );
				rsCount.Open(CRecordset::dynaset, strSQL );
				iEventsToCount = rsCount.m_Total;
				rsCount.Close( );

				CResultsEventTypeSet rs( &db );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETCONSISTENCYRESULTS);
				strSQL.Format(strSQLtmp, iSeriesID, iFirstEventNo, _T(" , Results.EventRate ASC") );

				rs.Open(CRecordset::forwardOnly, strSQL );

				int iConsistencyRateCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					int iAccEventCount = 0;

					int iAccNetPerformanceHOUR = 0;
					int iAccNetPerformanceMIN = 0;
					double dAccNetPerformanceSEC = 0.0;

					double dAccEventLength = 0.0;
					double dAccWorldStandard = 0.0;

					double dConsistencyEventsRate;
					double dConsistencyAgeStandard;

					bool bEventTypeTimedChanged = false;

					// Get the best x Events for the Person

					int iAccPersonID = rs.m_PersonID;

					int iTimed = rs.m_Timed;

					while( (iAccPersonID == rs.m_PersonID) && !rs.IsEOF( ) )
					{
						if( iAccEventCount < iEventsToCount )
						{
							if( iTimed != rs.m_Timed )
								bEventTypeTimedChanged = true;

							iAccNetPerformanceHOUR += rs.m_NetPerformanceHOUR;
							iAccNetPerformanceMIN += rs.m_NetPerformanceMIN;
							dAccNetPerformanceSEC += rs.m_NetPerformanceSEC;

							dAccEventLength += rs.m_EventLength;

							if( !rs.IsFieldNull( &rs.m_WorldStandard ) )
								dAccWorldStandard += rs.m_WorldStandard;

							iAccEventCount++;
						}

						rs.MoveNext( );
					}

					// Calculate their Consistency Event Rate based 
					// on their best x Events

					if( (iAccEventCount > 0) && (iEventsToCount > 0) )
					{
						if( !bEventTypeTimedChanged )
						{
							dConsistencyAgeStandard = dAccWorldStandard / (double)iAccEventCount;

							if( iTimed == 1 ) // Long Distance
							{
								double dAccNetPerfSEC;

								dAccNetPerfSEC = CCalculate::GetSeconds(
									iAccNetPerformanceHOUR,
									iAccNetPerformanceMIN,
									dAccNetPerformanceSEC
								);

								dConsistencyEventsRate = CCalculate::GetEventRateLongDistance(dAccEventLength, dAccNetPerfSEC);
							}
							else // Jump or Throw // Sprint
							{
								dConsistencyEventsRate = dConsistencyAgeStandard; // dAccWorldStandard / (double)iAccEventCount;
							}

							// Update ParticipantForSeries with newly
							// calced ConsistencyEventRate for the Person

							strSQL = "";

							strSQL +=     _T("UPDATE ParticipantForSeries ");

							//strSQL +=     _T("SET ConsistencyAgeStandard = ");
							//strSQL += CConvert::dtoa(dConsistencyAgeStandard, 7);
							//strSQL +=     _T(", ");

							strSQL +=     _T("SET ConsistencyEventsRate = ");
							strSQL += CConvert::dtoa(dConsistencyEventsRate, 7);
							strSQL +=     _T(" ");

							strSQL +=     _T("WHERE SeriesID = ");
							strSQL += CConvert::itoa(iSeriesID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND PersonID = ");
							strSQL += CConvert::itoa(iAccPersonID);
							strSQL +=     _T(" ");

							try
							{
								dbUpdate.ExecuteSQL( strSQL );
							}
							catch (CDBException* pEx)
							{
								*pHtml << pEx;

								pEx->Delete();
							}

							iConsistencyRateCount++;
						}
						else
						{
							*pHtml << _T("Cannot calculate a Consistency Rate for Person : <B>");
							*pHtml << _T(CConvert::itoa(iAccPersonID));
							*pHtml << _T("</B> because they competed in a combination of <B>Event Types</B> : <B>Long Distance</B> / <B>Jump, Throw or Points</B> / <B>Sprint</B>.");
							*pHtml << _T("<BR>\r\n");
						}
					}
					else
					{
						rs.MoveNext( );
					}
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iConsistencyRateCount, "");
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetConsistencyAgeStandard(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		// Process split off from SetConsistencyRate

		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
//				int iTimed;
				int iEventsNeeded;
				int iEventsToCount;
				int iFirstEventNo;

				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				// NO, BAD!
				// cant get Timed from the EventID, because the EventID
				// doesn't exist for this process, ie it is a 
				// ParticipantForSeries process


				// count the number of rules to get EventsNeeded
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Eligibility), 
					CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iEventsNeeded = rsCount.m_Total;
				rsCount.Close( );

				// get the EventNo of the FirstEventForSeason
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETFIRSTEVENTFORSEASON);
				strSQL.Format(strSQLtmp, iSeriesID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iFirstEventNo = rsCount.m_Total;
				rsCount.Close( );

				// get Events to qualify for Consistency
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" Rules.Law AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Consistency), 
					CRuleSubType::GetName(CRuleSubType::ConsistencyEventsToQualify) );
				rsCount.Open(CRecordset::dynaset, strSQL );
				iEventsToCount = rsCount.m_Total;
				rsCount.Close( );

				CResultsEventTypeSet rs( &db );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETCONSISTENCYRESULTS);
				strSQL.Format(strSQLtmp, iSeriesID, iFirstEventNo, _T(" , Results.WorldStandard DESC") );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iConsistencyRateCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					int iAccEventCount = 0;

					int iAccNetPerformanceHOUR = 0;
					int iAccNetPerformanceMIN = 0;
					double dAccNetPerformanceSEC = 0.0;

					double dAccEventLength = 0.0;
					double dAccWorldStandard = 0.0;

					double dConsistencyEventsRate;
					double dConsistencyAgeStandard;

					bool bEventTypeTimedChanged = false;

					// Get the best x Events for the Person

					int iAccPersonID = rs.m_PersonID;

					int iTimed = rs.m_Timed;

					while( (iAccPersonID == rs.m_PersonID) && !rs.IsEOF( ) )
					{
						if( iAccEventCount < iEventsToCount )
						{
							if( iTimed != rs.m_Timed )
								bEventTypeTimedChanged = true;

							iAccNetPerformanceHOUR += rs.m_NetPerformanceHOUR;
							iAccNetPerformanceMIN += rs.m_NetPerformanceMIN;
							dAccNetPerformanceSEC += rs.m_NetPerformanceSEC;

							dAccEventLength += rs.m_EventLength;

							if( !rs.IsFieldNull( &rs.m_WorldStandard ) )
								dAccWorldStandard += rs.m_WorldStandard;

							iAccEventCount++;
						}

						rs.MoveNext( );
					}

					// Calculate their Consistency Event Rate based 
					// on their best x Events

					if( (iAccEventCount > 0) && (iEventsToCount > 0) )
					{
						if( !bEventTypeTimedChanged )
						{
							dConsistencyAgeStandard = dAccWorldStandard / (double)iAccEventCount;

							if( iTimed == 1 ) // Long Distance
							{
								double dAccNetPerfSEC;

								dAccNetPerfSEC = CCalculate::GetSeconds(
									iAccNetPerformanceHOUR,
									iAccNetPerformanceMIN,
									dAccNetPerformanceSEC
								);

								dConsistencyEventsRate = CCalculate::GetEventRateLongDistance(dAccEventLength, dAccNetPerfSEC);
							}
							else // Jump or Throw // Sprint
							{
								dConsistencyEventsRate = dConsistencyAgeStandard; // dAccWorldStandard / (double)iAccEventCount;
							}

							// Update ParticipantForSeries with newly
							// calced ConsistencyEventRate for the Person

							strSQL = "";

							strSQL +=     _T("UPDATE ParticipantForSeries ");

							//strSQL +=     _T("SET ConsistencyEventsRate = ");
							//strSQL += CConvert::dtoa(dConsistencyEventsRate, 7);
							//strSQL +=     _T(", ");

							strSQL +=     _T(" SET ConsistencyAgeStandard = ");
							strSQL += CConvert::dtoa(dConsistencyAgeStandard, 7);
							strSQL +=     _T(" ");

							strSQL +=     _T("WHERE SeriesID = ");
							strSQL += CConvert::itoa(iSeriesID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND PersonID = ");
							strSQL += CConvert::itoa(iAccPersonID);
							strSQL +=     _T(" ");

							try
							{
								dbUpdate.ExecuteSQL( strSQL );
							}
							catch (CDBException* pEx)
							{
								*pHtml << pEx;

								pEx->Delete();
							}

							iConsistencyRateCount++;
						}
						else
						{
							*pHtml << _T("Cannot calculate a Consistency Rate for Person : <B>");
							*pHtml << _T(CConvert::itoa(iAccPersonID));
							*pHtml << _T("</B> because they competed in a combination of <B>Event Types</B> : <B>Long Distance</B> / <B>Jump, Throw or Points</B> / <B>Sprint</B>.");
							*pHtml << _T("<BR>\r\n");
						}
					}
					else
					{
						rs.MoveNext( );
					}
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iConsistencyRateCount, "");
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetConsistencyAgeGroup(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iEventsNoAgeChange;
				bool bEventsNoAgeChangeIsNull = false;

				CCountResultSet rsCount( &db );

				// get EventsNoAgeChange from rules
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" Rules.Law AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Consistency), 
					CRuleSubType::GetName(CRuleSubType::ConsistencyEventsBeforeAgegroupChange) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				if( rsCount.IsEOF( ) )
				{
					bEventsNoAgeChangeIsNull = true;
				}
				else
				{
					if( rsCount.IsFieldNull( &rsCount.m_Total ) )
					{
						bEventsNoAgeChangeIsNull = true;
					}
					else
					{
						iEventsNoAgeChange = rsCount.m_Total;
					}
				}
				rsCount.Close( );


				CConsistencyAgeGroupSet rs( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETCONSISTENCYAGEGROUP);
				strSQL.Format( strSQLtmp, iSeriesID );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iConsistencyAgeGroupCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				CIntegerSet rsAge( &dbUpdate );

				CString strSQLAgeGroup;
				CString strSQLCountAgeGroup;

				CUtil::LoadLongResource(strSQLAgeGroup, IDS_SQL_GETAGEGROUP);
				CUtil::LoadLongResource(strSQLCountAgeGroup, IDS_SQL_GETAGEGROUP);
				strSQLCountAgeGroup += " AND Results.AgeGroup = %d ";

				while( !rs.IsEOF( ) )
				{
					int iPersonID = rs.m_PersonID;

					int iConsistencyEventsCurrent;
					int iConsistencyEventsOlder;
					int iConsistencyAgeGroup;

					if( !bEventsNoAgeChangeIsNull )
					{
						int iMINAgeGroup = rs.m_MinAgeGroup;
						int iMAXAgeGroup = rs.m_MaxAgeGroup;

						int iCountMINAgeGroup = rs.m_EventsForSeason;
						int iCountMAXAgeGroup = rs.m_EventsForSeason;

						if( iMAXAgeGroup == iMINAgeGroup )
						{
							// These people are NOT changing AgeGroup in the Season

							iConsistencyEventsCurrent = iCountMINAgeGroup;
							iConsistencyEventsOlder = 0;
							iConsistencyAgeGroup = iMINAgeGroup;
						}
						else
						{
							// These people ARE changing AgeGroup in the Season

							// get the Min AgeGroup in the Season
							strSQL.Format( strSQLAgeGroup, " MIN(Results.AgeGroup) AS Val ", iSeriesID, iPersonID );
							rsAge.Open(CRecordset::forwardOnly, strSQL );
							iMINAgeGroup = rsAge.m_Val;
							rsAge.Close( );

							// count the Min AgeGroup in the Season
							strSQL.Format( strSQLCountAgeGroup, " COUNT(Results.AgeGroup) AS Val ", iSeriesID, iPersonID, iMINAgeGroup );
							rsAge.Open(CRecordset::forwardOnly, strSQL );
							iCountMINAgeGroup = rsAge.m_Val;
							rsAge.Close( );

							// get the Max AgeGroup in the Season
							strSQL.Format( strSQLAgeGroup, " MAX(Results.AgeGroup) AS Val ", iSeriesID, iPersonID );
							rsAge.Open(CRecordset::forwardOnly, strSQL );
							iMAXAgeGroup = rsAge.m_Val;
							rsAge.Close( );

							// count the Max AgeGroup in the Season
							strSQL.Format( strSQLCountAgeGroup, " COUNT(Results.AgeGroup) AS Val ", iSeriesID, iPersonID, iMAXAgeGroup );
							rsAge.Open(CRecordset::forwardOnly, strSQL );
							iCountMAXAgeGroup = rsAge.m_Val;
							rsAge.Close( );

							if( iCountMAXAgeGroup >= iEventsNoAgeChange )
							{
								// These people HAVE run enough Events in their
								// new AgeGroup

								iConsistencyEventsCurrent = iCountMINAgeGroup + iCountMAXAgeGroup;
								iConsistencyEventsOlder = 0;
								iConsistencyAgeGroup = iMAXAgeGroup;
							}
							else
							{
								// These people have NOT run enough Events in their
								// new AgeGroup

								iConsistencyEventsCurrent = iCountMINAgeGroup;
								iConsistencyEventsOlder = iCountMAXAgeGroup;
								iConsistencyAgeGroup = iMINAgeGroup;
							}
						}

					}
					else
					{
						// No Consistency Rules

						// Set to same 
						// as if they weren't changing AgeGroups regardless

						iConsistencyEventsCurrent = rs.m_EventsForSeason;
						iConsistencyEventsOlder = 0;
						iConsistencyAgeGroup = rs.m_MaxAgeGroup;
					}

					strSQL = "";

					strSQL +=     _T("UPDATE ParticipantForSeries ");

					strSQL +=     _T("SET ConsistencyEventsCurrent = ");
					strSQL += CConvert::itoa(iConsistencyEventsCurrent);
					strSQL +=     _T(", ");
					strSQL +=     _T("ConsistencyEventsOlder = ");
					strSQL += CConvert::itoa(iConsistencyEventsOlder);

					// Seperate Process SetEventsForSeason

					//strSQL +=     _T(", ");
					//strSQL +=     _T("EventsForSeason = ");
					//strSQL += CConvert::itoa(iConsistencyEventsOlder + iConsistencyEventsCurrent);

					strSQL +=     _T(", ");
					strSQL +=     _T("ConsistencyAgeGroup = ");
					strSQL += CConvert::itoa(iConsistencyAgeGroup);
					strSQL +=     _T(" ");

					strSQL +=     _T("WHERE SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND PersonID = ");
					strSQL += CConvert::itoa(iPersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					rs.MoveNext( );

					iConsistencyAgeGroupCount++;
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iConsistencyAgeGroupCount, "");
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}

BOOL CProcessor::ExecuteSetEventsForSeason(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{

				CConsistencyAgeGroupSet rs( &db );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETCONSISTENCYAGEGROUP);
				strSQL.Format( strSQLtmp, iSeriesID );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iEventsForSeasonCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					int iPersonID = rs.m_PersonID;
					int iEventsForSeason = rs.m_EventsForSeason;

					strSQL = "";

					strSQL +=     _T("UPDATE ParticipantForSeries ");

					strSQL +=     _T("SET EventsForSeason = ");
					strSQL += CConvert::itoa(iEventsForSeason);

					strSQL +=     _T("WHERE SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND PersonID = ");
					strSQL += CConvert::itoa(iPersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					rs.MoveNext( );

					iEventsForSeasonCount++;
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iEventsForSeasonCount, "");
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetEventsForSeries(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{

				CConsistencyAgeGroupSet rs( &db );
				strSQLtmp = _T("SELECT Results.PersonID , NULL AS MinAgeGroup , NULL AS MaxAgeGroup , NULL AS EventsForSeason , COUNT(Results.PersonID) AS EventsForSeries FROM ParticipantForSeries , Results WHERE ParticipantForSeries.SeriesID = Results.SeriesID AND ParticipantForSeries.PersonID = Results.PersonID AND Results.SeriesID = %d GROUP BY Results.PersonID ORDER BY Results.PersonID");
				strSQL.Format( strSQLtmp, iSeriesID );
				rs.Open(CRecordset::forwardOnly, strSQL );

				int iEventsForSeriesCount = 0;

				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				while( !rs.IsEOF( ) )
				{
					int iPersonID = rs.m_PersonID;
					int iEventsForSeries = rs.m_EventsForSeries;

					strSQL = "";

					strSQL +=     _T("UPDATE ParticipantForSeries ");

					strSQL +=     _T("SET EventsForSeries = ");
					strSQL += CConvert::itoa(iEventsForSeries);

					strSQL +=     _T("WHERE SeriesID = ");
					strSQL += CConvert::itoa(iSeriesID);
					strSQL +=     _T(" ");
					strSQL +=     _T("AND PersonID = ");
					strSQL += CConvert::itoa(iPersonID);
					strSQL +=     _T(" ");

					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}

					rs.MoveNext( );

					iEventsForSeriesCount++;
				}

				dbUpdate.Close( );
				rs.Close( );

				ShowResultMessage(pHtml, iEventsForSeriesCount, "");
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteReGroup(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;

				int iPersonID = 0;

				// for ReGroup Calculation
				int iDivisionActual;
				double dEventRate;
				double dGroupStartActual;
				int iGrossPerformanceHOUR;
				int iGrossPerformanceMIN;
				double dGrossPerformanceSEC;
				int iNetPerformanceHOUR;
				int iNetPerformanceMIN;
				double dNetPerformanceSEC;

				int iPercentileSize;
				int iPercentile[MAX_RULE_REGROUP];

				int iLawUp;
				int iLawDn;
				int iCountUpRules;
				int iCountDnRules;
				int iEventCount;
				int iNewGroupID;
				bool bReGroupedPerson;

				CString strUpRuleSubTypeDescription;
				CString strDnRuleSubTypeDescription;
				CString strNewGroupMessage;


				// Timed = 1 -> Long Distance
				// Timed = 0 -> Jump or Throw
				// Timed = 2 -> Sprint

				CCountResultSet rsCount( &db );

				// get Timed
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTTIMED);
				strSQL.Format(strSQLtmp, iSeriesID, iEventID );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iTimed = rsCount.m_Total;
				rsCount.Close( );

				// Count Up Rules
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULESUBTYPE);
				strSQL.Format(strSQLtmp, 
					" COUNT(Rules.Law) ", 
					iSeriesID, 
					CRuleSubType::GetName(CRuleSubType::RegroupEventsAbovePercentile) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iCountUpRules = rsCount.m_Total;
				rsCount.Close( );

				// Count Down Rules
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULESUBTYPE);
				strSQL.Format(strSQLtmp, 
					" COUNT(Rules.Law) ", 
					iSeriesID, 
					CRuleSubType::GetName(CRuleSubType::RegroupEventsBelowPercentile) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iCountDnRules = rsCount.m_Total;
				rsCount.Close( );


				CDatabase dbRules;
				dbRules.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				// Get All Up Rules
				CRulesJoinSet rsUpRules( &dbRules );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULESUBTYPE);
				strSQLtmp += _T(" ORDER BY Rules.Law ASC "); 
				strSQL.Format(strSQLtmp, 
					" Rules.*, RuleType.*, RuleSubType.* ", 
					iSeriesID, 
					CRuleSubType::GetName(CRuleSubType::RegroupEventsAbovePercentile) );
				rsUpRules.Open(CRecordset::dynaset, strSQL );
				strUpRuleSubTypeDescription = rsUpRules.m_RuleSubTypeDescription;


				// Get All Down Rules
				CRulesJoinSet rsDnRules( &dbRules );
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULESUBTYPE);
				strSQLtmp += _T(" ORDER BY Rules.Law DESC ");
				strSQL.Format(strSQLtmp, 
					" Rules.*, RuleType.*, RuleSubType.* ", 
					iSeriesID, 
					CRuleSubType::GetName(CRuleSubType::RegroupEventsBelowPercentile) );
				rsDnRules.Open(CRecordset::dynaset, strSQL );
				strDnRuleSubTypeDescription = rsDnRules.m_RuleSubTypeDescription;


				if( !rsUpRules.IsEOF( ) || !rsDnRules.IsEOF( ) )
				{
					int iReGroupUpCount = 0;
					int iReGroupDnCount = 0;

					CDatabase dbUpdate;
					dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );


					CResultsSet rs( &db );
					strSQL.Format( "SELECT * FROM Results WHERE SeriesID = %d AND EventID <= %d AND PersonID IN (SELECT PersonID FROM Results WHERE SeriesID = %d AND EventID = %d ) ORDER BY PersonID, EventID DESC", iSeriesID, iEventID, iSeriesID, iEventID );
					rs.Open(CRecordset::forwardOnly, strSQL );

					while( !rs.IsEOF( ) )
					{
						if( iPersonID != rs.m_PersonID )
						{
							iEventCount = 0;
							bReGroupedPerson = false;
							iPercentileSize = 0;

							iPersonID = rs.m_PersonID;

							// for ReGroup Calculation
							iDivisionActual = rs.m_DivisionActual;
							dEventRate = rs.m_EventRate;
							dGroupStartActual = rs.m_GroupStartActual;
							iGrossPerformanceHOUR = rs.m_GrossPerformanceHOUR;
							iGrossPerformanceMIN = rs.m_GrossPerformanceMIN;
							dGrossPerformanceSEC = rs.m_GrossPerformanceSEC;
							iNetPerformanceHOUR = rs.m_NetPerformanceHOUR;
							iNetPerformanceMIN = rs.m_NetPerformanceMIN;
							dNetPerformanceSEC = rs.m_NetPerformanceSEC;


							if( iCountUpRules > 0 )
								rsUpRules.MoveFirst( );

							if( iCountDnRules > 0 )
								rsDnRules.MoveFirst( );
						}

						if( ((rsUpRules.IsEOF( ) || rsUpRules.IsBOF( ))  && 
							 (rsDnRules.IsEOF( ) || rsDnRules.IsBOF( ))) || 
							bReGroupedPerson )
						{
							rs.MoveNext( );
							continue;
						}

						iPercentileSize++;
						iEventCount++;

						iPercentile[iPercentileSize -1] = rs.m_Percentile;

						if( !rsUpRules.IsEOF( ) && !rsUpRules.IsBOF( ) )
							iLawUp = rsUpRules.m_Law;

						if( !rsDnRules.IsEOF( ) && !rsDnRules.IsBOF( ))
							iLawDn = rsDnRules.m_Law;


						bool bDoUpReGroup = true;

						if( (iCountUpRules > 0) && 
							!rsUpRules.IsEOF( ) && !rsUpRules.IsBOF( ) )
						{
							for( int i = 0 ; i < iPercentileSize ; i++ )
							{
								if( bDoUpReGroup )
								{
									bDoUpReGroup = (iPercentile[i] <= iLawUp) ;
								}
							}
						}
						else
							bDoUpReGroup = false;


						bool bDoDnReGroup = true;

						if( (iCountDnRules > 0) && 
							!rsDnRules.IsEOF( ) && !rsDnRules.IsBOF( ))
						{
							for( int i = 0 ; i < iPercentileSize ; i++ )
							{
								if( bDoDnReGroup )
								{
									bDoDnReGroup = (iPercentile[i] > iLawDn) ;
								}
							}
						}
						else
							bDoDnReGroup = false;

						if( bDoUpReGroup || bDoDnReGroup )
						{
							if( bDoUpReGroup )
								strNewGroupMessage.Format("%d %s %d%%", 
									iEventCount, strUpRuleSubTypeDescription, iLawUp) ;

							if( bDoDnReGroup )
								strNewGroupMessage.Format("%d %s %d%%", 
									iEventCount, strDnRuleSubTypeDescription, iLawDn) ;


							iNewGroupID = GetNewGroupID(pHtml,
														&dbUpdate,
														iSeriesID,
														iEventID,
														iPersonID,
														iTimed,
														iDivisionActual,
														dEventRate,
														dGroupStartActual,
														iGrossPerformanceHOUR,
														iGrossPerformanceMIN,
														dGrossPerformanceSEC,
														iNetPerformanceHOUR,
														iNetPerformanceMIN,
														dNetPerformanceSEC);

							strSQL = "";

							strSQL +=     _T("UPDATE Results ");

							strSQL +=     _T("SET ");

							strSQL +=     _T("NewGroupID = ");
							strSQL += (iNewGroupID > 0) ? CConvert::itoa(iNewGroupID) : _T("NULL");
							strSQL +=     _T(", ");
							
							strSQL +=     _T("NewGroupMessage = '");
							strSQL +=     _T(strNewGroupMessage);
							strSQL +=     _T("' ");

							strSQL +=     _T("WHERE SeriesID = ");
							strSQL += CConvert::itoa(iSeriesID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND EventID = ");
							strSQL += CConvert::itoa(iEventID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND PersonID = ");
							strSQL += CConvert::itoa(iPersonID);
							strSQL +=     _T(" ");

							bReGroupedPerson = true;

							try
							{
								dbUpdate.ExecuteSQL( strSQL );
							}
							catch (CDBException* pEx)
							{
								*pHtml << pEx;

								pEx->Delete();
							}

							if( bDoUpReGroup )
								iReGroupUpCount++;

							if( bDoDnReGroup )
								iReGroupDnCount++;
						}

						if( !rsUpRules.IsEOF( ) && !rsUpRules.IsBOF( ) )
							rsUpRules.MoveNext( );

						if( !rsDnRules.IsEOF( ) && !rsDnRules.IsBOF( ) )
							rsDnRules.MoveNext( );

						rs.MoveNext( );
					}

					rs.Close( );
					dbUpdate.Close( );

					if( iReGroupUpCount )
						ShowResultMessage(pHtml, iReGroupUpCount, "Up");

					if( iReGroupDnCount )
						ShowResultMessage(pHtml, iReGroupDnCount, "Down");
				}
				else
				{
					// No ReGrouping Rules, check for
					// Manual Override For ReGroup From Post Results.

					int iReGroupCount = 0;

					CDatabase dbUpdate;
					dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );


					CResultsPostResultsSet rs( &db );
					strSQL.Format( "SELECT * FROM Results, PostResults WHERE Results.SeriesID = PostResults.SeriesID AND Results.EventID = PostResults.EventID AND Results.PersonID = PostResults.PersonID AND Results.SeriesID = %d AND Results.EventID = %d", iSeriesID, iEventID );
					rs.Open(CRecordset::forwardOnly, strSQL );

					while( !rs.IsEOF( ) )
					{
						if( !rs.IsFieldNull(&rs.m_Post_NewGroupID) ||
							!rs.IsFieldNull(&rs.m_Post_NewGroupMessage) )
						{
							iPersonID = rs.m_PersonID;

							if( !rs.IsFieldNull(&rs.m_Post_NewGroupID) )
								iNewGroupID = rs.m_Post_NewGroupID;
							else
								iNewGroupID = 0;

							if( !rs.IsFieldNull(&rs.m_Post_NewGroupMessage) )
								strNewGroupMessage = rs.m_Post_NewGroupMessage;
							else
								strNewGroupMessage = "";


							strSQL = "";

							strSQL +=     _T("UPDATE Results ");

							strSQL +=     _T("SET ");

							strSQL +=     _T("NewGroupID = ");
							strSQL += (iNewGroupID > 0) ? CConvert::itoa(iNewGroupID) : _T("NULL");
							strSQL +=     _T(", ");

							strSQL +=     _T("NewGroupMessage = '");
							strSQL +=     _T(strNewGroupMessage);
							strSQL +=     _T("' ");

							strSQL +=     _T("WHERE SeriesID = ");
							strSQL += CConvert::itoa(iSeriesID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND EventID = ");
							strSQL += CConvert::itoa(iEventID);
							strSQL +=     _T(" ");
							strSQL +=     _T("AND PersonID = ");
							strSQL += CConvert::itoa(iPersonID);
							strSQL +=     _T(" ");

							try
							{
								dbUpdate.ExecuteSQL( strSQL );
							}
							catch (CDBException* pEx)
							{
								*pHtml << pEx;

								pEx->Delete();
							}

							iReGroupCount++;
						}

						rs.MoveNext( );
					}

					rs.Close( );
					dbUpdate.Close( );

					if( iReGroupCount )
						ShowResultMessage(pHtml, iReGroupCount, "");
					else
						*pHtml << _T("No ReGrouping Rules.<BR>\r\n");
				}

				rsUpRules.Close( );
				rsDnRules.Close( );
				dbRules.Close( );
			}

			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteRebuildClubRecords(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				int iTimed;
				CString strOrder;


				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );


				// Create Temporary Table EventRecordTable
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_CR_EVENTRECORDTEMP);
				strSQL.Format( strSQLtmp );
				try
				{
					dbUpdate.ExecuteSQL( strSQL );
				}
				catch (CDBException* pEx)
				{
					*pHtml << pEx;

					pEx->Delete();
				}


				// Clear the EventRecord Table
				strSQL.Format( "DELETE FROM EventRecord WHERE SeriesID = %d ", iSeriesID );
				dbUpdate.ExecuteSQL( strSQL );


				CHttpServerProperties prop = CHttpServerProperties( pHtml );

				int nMaxJunior = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
				int nMinVeteran = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
				int nJuniorGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
				int nVeteranGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

				CString strAgeCategory;

				for( iTimed = 0 ; iTimed < 3 ; iTimed++ )
				{
					int iCounter = 0;

					// Clear the Temporary EventRecordTemp Table
					strSQL.Format( "DELETE FROM EventRecordTemp WHERE SeriesID = %d ", iSeriesID );
					try
					{
						dbUpdate.ExecuteSQL( strSQL );
					}
					catch (CDBException* pEx)
					{
						*pHtml << pEx;

						pEx->Delete();
					}


					// Timed = 1 -> Long Distance
					// Timed = 0 -> Jump or Throw
					// Timed = 2 -> Sprint

					if( iTimed > 0 ) // Long Distance // Sprint
					{
						strOrder.Format("MIN");
					}
					else // Jump or Throw
					{
						strOrder.Format("MAX");
					}

					// Get all the Best Performances for the Series
					CEventRecordSet rs( &db );
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETEVENTRECORD);
					strSQL.Format( strSQLtmp, strOrder, iTimed, iSeriesID );
					rs.Open(CRecordset::forwardOnly, strSQL );


					// Insert the Best Performances into the Temporary Table
					strSQLtmp = _T("INSERT INTO EventRecordTemp VALUES( %d , %d , %d , %d , '%s' , %d , '%c' , %d , %d , %d , %f )");

					while( !rs.IsEOF( ) )
					{
						CCalculate::GroupAge(rs.m_AgeGroup, strAgeCategory, &prop,
							nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);

						if( !strAgeCategory.Compare( CRecordsetEx::m_szNull ) ||
							strAgeCategory.GetLength() < 1 )
						{
							strAgeCategory = _T("Open");
						}

						strSQL.Format( strSQLtmp, 
							rs.m_SeriesID,
							rs.m_LocationID,
							0,	// EventID
							rs.m_EventTypeID,
							rs.m_Sex,
							rs.m_AgeGroup,
							strAgeCategory[0],
							0,	// PersonID
							CCalculate::GetHoursPart(rs.m_ClubPerformanceSEC),
							CCalculate::GetMinutesPart(rs.m_ClubPerformanceSEC),
							CCalculate::GetSecondsPart(rs.m_ClubPerformanceSEC) );

						try
						{
							dbUpdate.ExecuteSQL( strSQL );
						}
						catch (CDBException* pEx)
						{
							*pHtml << pEx;

							pEx->Delete();
						}

						rs.MoveNext( );
					}
					rs.Close( );

					// Copy the Best Performances from the Temporary Table
					// into the EventRecord Table, including the EventID, and PersonID
					// with duplicate Best Performances, ie Equal Performance.
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_INSERTEVENTRECORD);
					strSQL.Format( strSQLtmp, iTimed, iSeriesID );
					rs.Open(CRecordset::forwardOnly, strSQL );


					// Insert the Best Performances into the EventRecord
					strSQLtmp = _T("INSERT INTO EventRecord VALUES( %d , %d , %d , %d , '%s' , %d , '%s' , %d , %d , %d , %f )");

					while( !rs.IsEOF( ) )
					{
						strSQL.Format( strSQLtmp, 
							rs.m_SeriesID,
							rs.m_LocationID,
							rs.m_EventID,
							rs.m_EventTypeID,
							rs.m_Sex,
							rs.m_AgeGroup,
							rs.m_AgeCategory,
							rs.m_PersonID,
							rs.m_ClubPerformanceHOUR,
							rs.m_ClubPerformanceMIN,
							rs.m_ClubPerformanceSEC );

						try
						{
							dbUpdate.ExecuteSQL( strSQL );
							iCounter++;
						}
						catch (CDBException* pEx)
						{
							// Any exceptions caught will most likely be:
							// The same Person, in the same AgeGroup/AgeCategory has
							// equalled their own record at the same Location in
							// the same EventType. We don't want this duplicate!
							*pHtml << pEx;

							pEx->Delete();
						}

						rs.MoveNext( );
					}
					rs.Close( );

					switch( iTimed )
					{
						case 1: // Long Distance
						{
							if( iCounter > 0)
							{
								ShowResultMessage(pHtml, iCounter, "Long Distance");
							}
							break;
						}
						case 0: // Jump or Throw
						{
							if( iCounter > 0)
							{
								ShowResultMessage(pHtml, iCounter, "Jump, Throw or Points");
							}
							break;
						}
						case 2: // Sprint
						{
							if( iCounter > 0)
							{
								ShowResultMessage(pHtml, iCounter, "Sprint");
							}
							break;
						}
					}

				}

				// Drop the Temporary Table
				strSQL.Format( "DROP TABLE EventRecordTemp" );
				try
				{
					dbUpdate.ExecuteSQL( strSQL );
				}
				catch (CDBException* pEx)
				{
					*pHtml << pEx;

					pEx->Delete();
				}

				dbUpdate.Close( );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetFinancialEligibility(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				int iSkipProcess;

				CCountResultSet rsCount( &db );

				// count the number of rules to get Eligible Regardless of Financial
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Processing), 
					CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfFinancial) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iSkipProcess = rsCount.m_Total;
				rsCount.Close( );

				if( iSkipProcess )
				{
					*pHtml << _T("Skipping Process <B>");
					*pHtml << _T(CProcess::GetName(dwProc));
					*pHtml << _T("</B> due to <B>");
					*pHtml << _T(CRuleType::GetName(CRuleType::Processing));
					*pHtml << _T("</B> Rule <B>");
					*pHtml << _T(CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfFinancial));
					*pHtml << _T("</B>.<BR>\r\n");
				}
				else
				{
					COleDateTime someday;

					CEventSet rsEvent( &db );
					strSQL.Format( "SELECT * FROM Event WHERE EventID = %d AND SeriesID = %d", iEventID, iSeriesID);
					rsEvent.Open(CRecordset::forwardOnly, strSQL );

					someday.SetDateTime( rsEvent.m_DateYEAR, rsEvent.m_DateMONTH, rsEvent.m_DateDAY, 1, 1, 1 );

					rsEvent.Close( );


					CFinancialRegistrationSet rs( &db );

					int iPersonCount = 0;
					CString strPersonFinancialList;
					strPersonFinancialList = _T("");

					// get the list of people who are financial
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETFINANCIALRESULTS);
					strSQL.Format( strSQLtmp, iSeriesID, iEventID );
					rs.Open(CRecordset::forwardOnly, strSQL );

					while( !rs.IsEOF( ) )
					{
						if( CCalculate::Current(someday, rs.m_Year, rs.m_MonthStart, rs.m_MonthStop) )
						{
							if( iPersonCount == 0 )
								strPersonFinancialList += _T(" ( ");
							else
								strPersonFinancialList += _T(" , ");

							strPersonFinancialList += _T( CConvert::itoa(rs.m_PersonID) );

							iPersonCount++;
						}

						rs.MoveNext( );
					}
					strPersonFinancialList += _T(" ) ");

					rs.Close( );

					if( iPersonCount > 0 )
					{
						strSQLtmp  = _T("");

						strSQLtmp += _T("UPDATE Results ");
						strSQLtmp += _T(" SET Results.Eligible = 'F' ");
						strSQLtmp += _T(" WHERE Results.SeriesID = %d ");
						strSQLtmp += _T(" AND Results.EventID = %d ");
						strSQLtmp += _T(" AND Results.PersonID NOT IN %s ");

						strSQL.Format(strSQLtmp, iSeriesID, iEventID, strPersonFinancialList );

						try
						{
							dbUpdate.ExecuteSQL( strSQL );
						}
						catch (CDBException* pEx)
						{
							*pHtml << pEx;

							pEx->Delete();
						}
					}
				}
				dbUpdate.Close( );


				strSQL.Format( "SELECT COUNT(*) FROM Results WHERE Eligible = 'F' AND SeriesID = %d AND EventID = %d", iSeriesID, iEventID);
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				ShowResultMessage(pHtml, rsCount.m_Total, "Eligible = 'F'");

				rsCount.Close( );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}


BOOL CProcessor::ExecuteSetSeriesFinancialEligibility(
					CHtmlWriter* pHtml, LPCTSTR szConnect, DWORD dwTimeOut,
					DWORD dwProc, int iSeriesID, int iEventID)
{
		try
		{
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;

			db.SetLoginTimeout( dwTimeOut );
			db.SetQueryTimeout( dwTimeOut );

			db.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

			try
			{
				CDatabase dbUpdate;
				dbUpdate.OpenEx( _T( szConnect ), CDatabase::noOdbcDialog );

				int iSkipProcess;

				CCountResultSet rsCount( &db );

				// count the number of rules to get Eligible Regardless of Financial
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETRULES);
				strSQL.Format( strSQLtmp, 
					" COUNT(Rules.Law) AS Total ", 
					iSeriesID, 
					CRuleType::GetName(CRuleType::Processing), 
					CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfFinancial) );
				rsCount.Open(CRecordset::forwardOnly, strSQL );
				iSkipProcess = rsCount.m_Total;
				rsCount.Close( );

				if( iSkipProcess )
				{
					*pHtml << _T("Skipping Process <B>");
					*pHtml << _T(CProcess::GetName(dwProc));
					*pHtml << _T("</B> due to <B>");
					*pHtml << _T(CRuleType::GetName(CRuleType::Processing));
					*pHtml << _T("</B> Rule <B>");
					*pHtml << _T(CRuleSubType::GetName(CRuleSubType::ProcessingEligibleRegardlessOfFinancial));
					*pHtml << _T("</B>.<BR>\r\n");
				}
				else
				{
					COleDateTime someday;

					someday = COleDateTime::GetCurrentTime();


					CFinancialRegistrationSet rs( &db );

					int iPersonCount = 0;
					CString strPersonFinancialList;
					strPersonFinancialList = _T("");

					// get the list of people who are financial
					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETFINANCIALPARTICIPANTFORSERIES);
					strSQL.Format( strSQLtmp, iSeriesID, iEventID );
					rs.Open(CRecordset::forwardOnly, strSQL );

					while( !rs.IsEOF( ) )
					{
						if( CCalculate::Current(someday, rs.m_Year, rs.m_MonthStart, rs.m_MonthStop) )
						{
							if( iPersonCount == 0 )
								strPersonFinancialList += _T(" ( ");
							else
								strPersonFinancialList += _T(" , ");

							strPersonFinancialList += _T( CConvert::itoa(rs.m_PersonID) );

							iPersonCount++;
						}

						rs.MoveNext( );
					}
					strPersonFinancialList += _T(" ) ");

					rs.Close( );

					if( iPersonCount > 0 )
					{
						strSQLtmp  = _T("");

						strSQLtmp += _T("UPDATE ParticipantForSeries ");
						strSQLtmp += _T(" SET ParticipantForSeries.EligibilityForEvent = 'F' ");
						strSQLtmp += _T(" WHERE ParticipantForSeries.SeriesID = %d ");
						strSQLtmp += _T(" AND ParticipantForSeries.PersonID NOT IN %s ");

						strSQL.Format(strSQLtmp, iSeriesID, strPersonFinancialList );

						try
						{
							dbUpdate.ExecuteSQL( strSQL );
						}
						catch (CDBException* pEx)
						{
							*pHtml << pEx;

							pEx->Delete();
						}
					}
				}
				dbUpdate.Close( );


				strSQL.Format( "SELECT COUNT(*) FROM ParticipantForSeries WHERE EligibilityForEvent = 'F' AND SeriesID = %d ", iSeriesID);
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				ShowResultMessage(pHtml, rsCount.m_Total, "Eligible = 'F'");

				rsCount.Close( );
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		return TRUE;
}






int CProcessor::GetNewGroupID(CHtmlWriter* pHtml,
							 CDatabase* pdb,
							 int iSeriesID,
							 int iEventID,
							 int iPersonID,
							 int iTimed,
							 int iDivisionActual,
							 double dEventRate,
							 double dGroupStartActual,
							 int iGrossPerformanceHOUR,
							 int iGrossPerformanceMIN,
							 double dGrossPerformanceSEC,
							 int iNetPerformanceHOUR,
							 int iNetPerformanceMIN,
							 double dNetPerformanceSEC)
{
	CString strSQL;
	CString strSQLtmp;
	int iNewGroupID = 0;

	double dGrossPerfSEC = CCalculate::GetSeconds(
		iGrossPerformanceHOUR,
		iGrossPerformanceMIN,
		dGrossPerformanceSEC
	);

	double dNetPerfSEC = CCalculate::GetSeconds(
		iNetPerformanceHOUR,
		iNetPerformanceMIN,
		dNetPerformanceSEC
	);

	double dGroupStartSEC = CCalculate::GetSeconds(dGroupStartActual);

	double d50PercPerfSEC; 
	double dNewGroupStartSEC;
	double dNewGroupStart;

	try
	{
		strSQLtmp  = _T("SELECT Groups.GroupID FROM Event, EventType, Groups WHERE EventType.EventTypeID = Groups.EventTypeID AND Event.SeriesID = Groups.SeriesID AND Event.EventTypeID = EventType.EventTypeID AND Event.EventTypeID = Groups.EventTypeID AND Groups.SeriesID = %d AND Event.EventID = %d ");

		if(iTimed == 1) // Long Distance
		{
			CResultsSet rs( &(*pdb) );
			strSQL.Format("SELECT * FROM Results WHERE DivisionActual = %d AND SeriesID = %d AND EventID = %d AND Percentile >= 50 ORDER BY Percentile ASC ",
				iDivisionActual, iSeriesID, iEventID );
			rs.Open(CRecordset::forwardOnly, strSQL );

			if( iTimed == 1 ) // Long Distance
			{
				d50PercPerfSEC = CCalculate::GetSeconds(
					rs.m_GrossPerformanceHOUR,
					rs.m_GrossPerformanceMIN,
					rs.m_GrossPerformanceSEC
				);
			}
			else // Jump or Throw // Sprint
			{
				d50PercPerfSEC = CCalculate::GetSeconds(
					rs.m_NetPerformanceHOUR,
					rs.m_NetPerformanceMIN,
					rs.m_NetPerformanceSEC
				);
			}
			rs.Close( );

			dNewGroupStartSEC = dGroupStartSEC + (d50PercPerfSEC - dGrossPerfSEC);
			dNewGroupStart = CCalculate::GetMinSec(dNewGroupStartSEC);

			strSQLtmp += _T(" AND Groups.GroupStart > %f ORDER BY Groups.GroupStart ASC ");

			strSQL.Format(strSQLtmp, 
				iSeriesID, 
				iEventID,
				dNewGroupStart);
		}
		else if(iTimed == 0) // Jump or Throw 
		{
			strSQLtmp += _T(" AND Groups.GroupRate > %f ORDER BY Groups.GroupRate ASC ");

			strSQL.Format(strSQLtmp, 
				iSeriesID, 
				iEventID,
				dEventRate);
		}
		else if(iTimed == 2) // Sprint
		{
			strSQLtmp += _T(" AND Groups.GroupRate < %f ORDER BY Groups.GroupRate DESC ");

			strSQL.Format(strSQLtmp, 
				iSeriesID, 
				iEventID,
				dEventRate);
		}

		CIntegerSet rs( &(*pdb) );
		rs.Open(CRecordset::forwardOnly, strSQL );
		iNewGroupID = rs.m_Val;
		rs.Close( );

	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		pEx->Delete();
	}

	return iNewGroupID;
}



