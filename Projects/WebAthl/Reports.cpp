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
#include "ResultsSet.h"

#include "GroupsSet.h"
#include "OrganisationSet.h"
#include "RegistrationTypeSet.h"

#include "ClubRecordsSet.h"
#include "ParticipantHistorySet.h"

#include "SeriesPersonPFSOrgSet.h"

#include "EventTallySet.h"
#include "PersonSet.h"
#include "FinancialSet.h"
#include "ResultsOrgSet.h"

#include "PreResultsSet.h"
#include "PostResultsSet.h"
#include "ParticipantForSeriesSet.h"

#include "CountResultSet.h"
#include "IntegerSet.h"

#include "GroupsReportSet.h"
#include "RosterNamesSet.h"
#include "PersonFinancialSet.h"
#include "RulesSet.h"
#include "RuleTypeSet.h"
#include "RuleSubTypeSet.h"

#include "AgeGroupRankingSet.h"
#include "SeriesStatisticsSet.h"
#include "StringSet.h"

#include "PersonFinancialCommentsSet.h"

///////////////////////////////////////////////////////////////////////
// Reports

void CWebAthlExtension::ReportsMenu(CHttpServerContext* pCtxt,
								LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strHeading = "Reports";
		auth.m_strBackLink = CPage::ReportsMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "0");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SeriesSelectForm, "Results", 1, CPage::ReportsResultsForm);
		html.WritePageMenuItem(CPage::ReportsAwardsForm, "Awards", 0);
		html.WritePageMenuItem(CPage::ReportsEventTallyForm, "Event Tally", 0);
		html.WritePageMenuItem(CPage::ReportsClubRecordsForm, "Club Records", 0);

		if( auth.HasPermission(CModule::Person) )
			if( auth.m_iPersonID > 0 )
				html.WritePageMenuItem(CPage::ReportsParticipantHistoryForm, "Your Participant History", 0);

		if( auth.HasPermission(CModule::ViewPerson | CModule::EditPerson) )
			html.WritePageMenuItem(CPage::SearchPersonForm, "Participant History", 1, CPage::ReportsParticipantHistoryForm);

		if( auth.HasPermission(CModule::Person) )
			if( auth.m_iPersonID > 0 )
				html.WritePageMenuItem(CPage::ReportsFinancialHistoryForm, "Your Financial History", 0);

		if( auth.HasPermission(CModule::Financial) )
			html.WritePageMenuItem(CPage::SearchPersonForm, "Financial History", 1, CPage::ReportsFinancialHistoryForm);

		if( auth.HasPermission(CModule::ViewPerson | CModule::EditPerson | CModule::Financial) )
			html.WritePageMenuItem(CPage::ReportsPersonForm, "Person Details", 0);

		html.WritePageMenuItem(CPage::SeriesSelectForm, "Event Roster", 1, CPage::ReportsRosterForm);
		html.WritePageMenuItem(CPage::SeriesSelectForm, "Groups List", 1, CPage::ReportsGroupsListForm);
//		html.WritePageMenuItem(CPage::SeriesSelectForm, "Eligibility List", 1, CPage::ReportsEligibilityForm);
		html.WritePageMenuItem(CPage::SeriesSelectForm, "Rules", 1, CPage::ReportsRulesExecute);

		html.WritePageMenuItem(CPage::ReportsAgeGroupRankingForm, "Age Group Ranking", 0 );
		html.WritePageMenuItem(CPage::SeriesSelectForm, "Series Statistics", 1, CPage::ReportsSeriesStatisticsForm);

		// Series Manager Access
		if( auth.HasPermission(CModule::SeriesMaintain) )
			html.WritePageMenuItem(CPage::ReportsResultsBySeriesForm, "Results By Series", 0 );

		html.WritePageMenuItem(CPage::ReportsEventCalendarForm, "Event Calendar", 0 );

		if( auth.HasPermission(CModule::Security) )
			html.WritePageMenuItem(CPage::ReportsCustomForm, "Design a Custom Report", 0);

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ReportsClubRecordsForm(CHttpServerContext* pCtxt,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsClubRecordsExecute;

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

			CSeriesSet rsSeries( &db );

			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select a Series\r\n");

				html.StartForm("Club Records", auth.m_strFrwdLink);

				html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
				html.HorizontalRule();

				html.CheckBox("Sex", "Male", "SexMale", "1", "1");
				html.CheckBox("", "Female", "SexFemale", "1", "0");
				html.HorizontalRule();

				html.CheckBox(
					"Age Group",
					" " + html.InLineInput("text","AgeGroup", "0", 5,""),
					"UseAgeGroup",
					"1",
					"1");

				html.HorizontalRule();

				html.CheckBox("Order By", "Location", "OrderByLocation", "1", "1");
				html.CheckBox("", "Event Type", "OrderByEventDescription", "1", "1");
				html.CheckBox("", "Date", "OrderByDate", "1", "1");
				html.CheckBox("", "AgeGroup", "OrderByAgeGroup", "1", "1");
				html.CheckBox("", "Sex", "OrderBySex", "1", "1");

				html.RadioButton("", "Name Ascending", "OrderByNameDesc",	"0", "0");
				html.RadioButton("", "Name Descending","OrderByNameDesc",	"1", "0");

				html.HorizontalRule();

				CReportClubRecordsOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}

				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsClubRecordsExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szSexMale,
										  LPTSTR szSexFemale,
										  LPTSTR szUseAgeGroup,
										  LPTSTR szAgeGroup,
										  LPTSTR szOrderByLocation,
										  LPTSTR szOrderByEventDescription,
										  LPTSTR szOrderByDate,
										  LPTSTR szOrderByAgeGroup,
										  LPTSTR szOrderBySex,
										  LPTSTR szOrderByNameDesc,
										  LPTSTR szOption,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iSexMale				= atoi(szSexMale);
		int iSexFemale				= atoi(szSexFemale);
		int iUseAgeGroup			= atoi(szUseAgeGroup);
		int iAgeGroup				= atoi(szAgeGroup);

		int iDisDate				= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayDate);
		int iDisEventNo				= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayEventNo);
		int iDisLocationDescription	= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayLocationDescription);
		int iDisEventDescription	= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayEventDescription);
		int iDisPersonID			= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayPersonID);
		int iDisLastName			= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayLastName);
		int iDisFirstName			= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayFirstName);
		int iDisSexAgeGroup			= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplaySexAgeGroup);
		int iDisClubPerformance		= CReportClubRecordsOption::IsMember( dwOption, CReportClubRecordsOption::DisplayClubPerformance);

		int iOrderByLocation		= atoi(szOrderByLocation);
		int iOrderByEventDescription = atoi(szOrderByEventDescription);
		int iOrderByDate			= atoi(szOrderByDate);
		int iOrderByAgeGroup		= atoi(szOrderByAgeGroup);
		int iOrderBySex				= atoi(szOrderBySex);
		int iOrderByNameDesc		= atoi(szOrderByNameDesc);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CClubRecordsSet rs( &db );

			CUtil::LoadLongResource(strSQL, IDS_SQL_CLUBRECORDS);

			strSQLtmp.Format(" AND ( EventRecord.SeriesID = %s ) ", _T(szSeriesID));
			strSQL += strSQLtmp;

			if( iSexMale && iSexFemale )
			{
			}
			else if( iSexMale )
			{
				strSQLtmp.Format(" AND ( EventRecord.Sex = '%s' ) ", _T("M"));
				strSQL += strSQLtmp;
			}
			else if( iSexFemale )
			{
				strSQLtmp.Format(" AND ( EventRecord.Sex = '%s' ) ", _T("W"));
				strSQL += strSQLtmp;
			}
			else
			{
				strSQLtmp.Format(" AND ( EventRecord.Sex = NULL ) ");
				strSQL += strSQLtmp;
			}

			if( iUseAgeGroup )
			{
				if( iAgeGroup > -1 )
				{
					strSQLtmp.Format(" AND ( EventRecord.AgeGroup = %d ) ", iAgeGroup);
					strSQL += strSQLtmp;
				}
			}

			strSQL += _T( " ORDER BY " );

			// ORDER BY clause :
			if(iOrderByLocation)
				strSQL += _T( " Location.LocationDescription , " );

			if(iOrderByEventDescription)
				strSQL += _T( " EventType.EventDescription , " );

			if(iOrderByDate)
				strSQL += _T( " Event.DateYEAR , Event.DateMONTH , Event.DateDAY , " );

			if(iOrderByAgeGroup)
				strSQL += _T( " EventRecord.AgeGroup , " );

			if(iOrderBySex)
				strSQL += _T( " EventRecord.Sex , " );

			if(iOrderByNameDesc)
				strSQL += _T( " Person.LastName DESC, Person.FirstName DESC, Person.MiddleName DESC " );
			else
				strSQL += _T( " Person.LastName ASC, Person.FirstName ASC, Person.MiddleName ASC " );

			//html << _T(strSQL);
			
			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Club Records");

				html.StartForm(strTitle, "");
				html.NonEditText("Series", rs.m_SeriesDescription );
				html.EndForm();

				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisDate)
					strColumn->Add( "Date" );

				if(iDisEventNo)
					strColumn->Add( "EventNo" );

				if(iDisLocationDescription)
					strColumn->Add( "Location" );

				if(iDisEventDescription)
					strColumn->Add( "Event" );

				if(iDisPersonID)
					strColumn->Add( "PersonID" );

				if(iDisLastName)
					strColumn->Add( "LastName" );

				if(iDisFirstName)
					strColumn->Add( "FirstName" );

				if(iDisSexAgeGroup)
					strColumn->Add( "AgeGroup" );

				if(iDisClubPerformance)
					strColumn->Add( "Performance" );


				html.HtmlTable(strColumn);

				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );

				while( !rs.IsEOF( ) )
				{
					if(iDisDate)
						strColumn->Add( _T( CFormat::FormatDate(rs.m_DateDAY, rs.m_DateMONTH,rs.m_DateYEAR)) );

					if(iDisEventNo)
						strColumn->Add( CConvert::itoa(rs.m_EventNo) );

					if(iDisLocationDescription)
						strColumn->Add( _T(rs.m_LocationDescription) );

					if(iDisEventDescription)
						strColumn->Add( _T(rs.m_EventDescription) );

					if(iDisPersonID)
						strColumn->Add( _T( CConvert::itoa(rs.m_PersonID) ) );

					if(iDisLastName)
						strColumn->Add( _T(rs.m_LastName) );

					if(iDisFirstName)
						strColumn->Add( _T(rs.m_FirstName) );

					if(iDisSexAgeGroup)
						strColumn->Add( _T(rs.m_Sex) + CConvert::itoa(rs.m_AgeGroup) );

					if(iDisClubPerformance)
						strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
												   rs.m_ClubPerformanceHOUR, 
												   rs.m_ClubPerformanceMIN,
												   rs.m_ClubPerformanceSEC) ));

					html.HtmlTable(strColumn);

					strColumn->RemoveAll( );

					rs.MoveNext( );
				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsParticipantHistoryForm(CHttpServerContext* pCtxt,
													 LPTSTR szPersonID,
													 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::ViewPerson | CModule::EditPerson) )
	{
		CString strPersonID;
		if( !_tcscmp(szPersonID, "none" ) )
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

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


			strSQLtmp += _T("SELECT DISTINCT Series.* ") ;
			strSQLtmp += _T(" FROM Results, Series ") ;
			strSQLtmp += _T(" WHERE Series.SeriesID = Results.SeriesID ") ;
			strSQLtmp += _T(" AND ( Results.SeriesID > 0 ) ") ;
			strSQLtmp += _T(" AND ( Results.PersonID = %s ) ") ;
			strSQLtmp += _T(" ORDER BY Series.SeriesDescription ") ;

			CSeriesSet rs( &db );
			strSQL.Format( strSQLtmp, _T(strPersonID) );
			rs.Open(CRecordset::dynaset, strSQL );


			CPersonSet rsPerson( &db );
			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", strPersonID );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html.StartForm("Participant History", CPage::ReportsParticipantHistoryExecute);

				html.NonEditText("Name", rsPerson.m_LastName + ", " + rsPerson.m_FirstName);				
				html.HorizontalRule();

				html.HiddenText("PersonID", strPersonID);

				html.SelectSeriesBox("Filter By Series", "SeriesID", &rs, 0, "(all)");
				html.HorizontalRule();

				html.RadioButton("Order By", "Series", "OrderBy", "0", "0");
				html.RadioButton("", "Event Type", "OrderBy", "1", "0");
				html.RadioButton("", "Location", "OrderBy", "2", "0");
				html.HorizontalRule();

				CReportParticipantHistoryOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}

				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
			}

			rsPerson.Close( );
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

void CWebAthlExtension::ReportsParticipantHistoryExecute(CHttpServerContext* pCtxt,
												 LPTSTR szPersonID,
												 LPTSTR szSeriesID,
												 LPTSTR szOrderBy,
												 LPTSTR szOption,
												 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::ViewPerson | CModule::EditPerson) )
	{
		CString strPersonID;

		if( !_tcscmp(szPersonID, "none" ) )
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iPersonID				= atoi(strPersonID);
		int iSeriesID				= atoi(szSeriesID);
		int iOrderBy				= atoi(szOrderBy);

		int iDisSeriesDescription	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplaySeriesDescription );
		int iDisEventNo				= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayEventNo);
		int iDisDate				= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayDate);
		int iDisLocationDescription	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayLocationDescription);
		int iDisEventDescription	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayEventDescription);
		int iDisDivisionActual		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayDivisionActual);
		int iDisAgeGroup			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayAgeGroup);
		int iDisGroupIDActual		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayGroupIDActual);
		int iDisGroupStartActual	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayGroupStartActual);
		int iDisNewGroupID			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayNewGroupID);
		int iDisNewGroupMessage		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayNewGroupMessage);
		int iDisGrossPerformance	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayGrossPerformance);
		int iDisNetPerformance		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayNetPerformance);
		int iDisPlace				= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayPlace);
		int iDisOverallPlace		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayOverallPlace);
		int iDisPercentile			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayPercentile);
		int iDisPoints				= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayPoints);
		int iDisEligible			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayEligible);
		int iDisEventRate			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayEventRate);
		int iDisGroupRateActual		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayGroupRateActual);
		int iDisChestNumber			= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayChestNumber);
		int iDisWorldStandard		= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayWorldStandard);
		int iDisGroupIDSupposedTo	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayGroupIDSupposedTo);
		int iDisDivisionSupposedTo	= CReportParticipantHistoryOption::IsMember( dwOption, CReportParticipantHistoryOption::DisplayDivisionSupposedTo);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CParticipantHistorySet rs( &db );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_PARTICIPANTHISTORY);

			if( iSeriesID > 0 )
			{
				strSQLtmp += " AND Results.SeriesID = ";
				strSQLtmp += _T(szSeriesID);
				strSQLtmp += " ";
			}

			strSQLtmp += " ORDER BY ";

			if( iOrderBy == 0)
				strSQLtmp += " Series.SeriesDescription, ";
			if( iOrderBy == 1)
				strSQLtmp += " EventType.EventDescription, ";
			if( iOrderBy == 2)
				strSQLtmp += " Location.LocationDescription, ";

			strSQLtmp += " Event.DateYEAR DESC, Event.DateMONTH DESC, Event.DateDAY DESC ";


			strSQL.Format(strSQLtmp, _T(strPersonID));

			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Participant History For: ");

				if( atoi(szSeriesID) > 0 )
				{
					strTitle += " Series : ";
					strTitle += rs.m_SeriesDescription;
					strTitle += " ; ";
				}

				strTitle += CConvert::itoa(rs.m_PersonID) + " ; " + rs.m_FirstName + " " + rs.m_LastName;

				html.StartForm(strTitle, "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisSeriesDescription)		strColumn->Add( "Series" );
				if(iDisEventNo)					strColumn->Add( "EventNo" );
				if(iDisDate)					strColumn->Add( "Date" );
				if(iDisLocationDescription)		strColumn->Add( "Location" );
				if(iDisEventDescription)		strColumn->Add( "Event" );
				if(iDisAgeGroup)				strColumn->Add( "AgeGroup" );
				if(iDisDivisionActual)			strColumn->Add( "DivActual" );
				if(iDisDivisionSupposedTo)		strColumn->Add( "Div" );
				if(iDisGroupIDActual)			strColumn->Add( "GroupAct" );
				if(iDisGroupIDSupposedTo)		strColumn->Add( "Group" );
				if(iDisGroupStartActual)		strColumn->Add( "GroupStart" );
				if(iDisGrossPerformance)		strColumn->Add( "GrossPerformance" );
				if(iDisNetPerformance)			strColumn->Add( "NetPerformance" );
				if(iDisPlace)					strColumn->Add( "Place" );
				if(iDisOverallPlace)			strColumn->Add( "OverallPlace" );
				if(iDisPercentile)				strColumn->Add( "Percentile" );
				if(iDisPoints)					strColumn->Add( "Points" );
				if(iDisEligible)				strColumn->Add( "Eligible" );
				if(iDisEventRate)				strColumn->Add( "EventRate" );
				if(iDisGroupRateActual)			strColumn->Add( "GroupRateActual" );
				if(iDisChestNumber)				strColumn->Add( "ChestNumber" );
				if(iDisWorldStandard)			strColumn->Add( "AgeStandard" );
				if(iDisNewGroupMessage)			strColumn->Add( "Comment" );
				if(iDisNewGroupID)				strColumn->Add( "NewGroup" );

				if( strColumn->GetSize( ) )
				{
					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					CString strNewGroupID;

					strColumn->RemoveAll( );

					while( !rs.IsEOF( ) )
					{
						if( (rs.m_NewGroupID > 0) && !rs.IsFieldNull( &rs.m_NewGroupID ) )
							strNewGroupID.Format(CConvert::itoa(rs.m_NewGroupID));
						else
							strNewGroupID.Format("");

						
						if(iDisSeriesDescription)
							strColumn->Add( _T(rs.m_SeriesDescription) );

						if(iDisEventNo)
							strColumn->Add( _T(CConvert::itoa(rs.m_EventNo)) );

						if(iDisDate)
							strColumn->Add( _T( CFormat::FormatDate(rs.m_DateDAY, rs.m_DateMONTH,rs.m_DateYEAR)) );

						if(iDisLocationDescription)	
							strColumn->Add( _T(rs.m_LocationDescription) );

						if(iDisEventDescription)		
							strColumn->Add( _T(rs.m_EventDescription) );

						if(iDisAgeGroup)			
							strColumn->Add( _T(CConvert::itoa(rs.m_AgeGroup)) );

						if(iDisDivisionActual)		
							strColumn->Add( _T(CConvert::itoa(rs.m_DivisionActual)) );

						if(iDisDivisionSupposedTo)	
							strColumn->Add( _T(CConvert::itoa(rs.m_DivisionSupposedTo)) );

						if(iDisGroupIDActual)		
							strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDActual)) );

						if(iDisGroupIDSupposedTo)	
							strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDSupposedTo)) );

						if(iDisGroupStartActual)	
							strColumn->Add( _T(CConvert::dtoa(rs.m_GroupStartActual)) );

						if(iDisGrossPerformance)	
							strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
													   rs.m_GrossPerformanceHOUR, 
													   rs.m_GrossPerformanceMIN,
													   rs.m_GrossPerformanceSEC) ));

						if(iDisNetPerformance)		
							strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
													   rs.m_NetPerformanceHOUR, 
													   rs.m_NetPerformanceMIN,
													   rs.m_NetPerformanceSEC) ));

						if(iDisPlace)			
							strColumn->Add( _T(CConvert::itoa(rs.m_Place)) );
							
						if(iDisOverallPlace)		
							strColumn->Add( _T(CConvert::itoa(rs.m_OverallPlace)) );

						if(iDisPercentile)			
							strColumn->Add( _T(CConvert::itoa(rs.m_Percentile)) );

						if(iDisPoints)				
							strColumn->Add( _T(CConvert::itoa(rs.m_Points)) );

						if(iDisEligible)			
							strColumn->Add( _T(rs.m_Eligible) );

						if(iDisEventRate)			
							strColumn->Add( _T(CConvert::dtoa(rs.m_EventRate)) );

						if(iDisGroupRateActual)		
							strColumn->Add( _T(CConvert::dtoa(rs.m_GroupRateActual)) );

						if(iDisChestNumber)			
							strColumn->Add( _T(rs.m_ChestNumber) );

						if(iDisWorldStandard)		
							strColumn->Add( _T(CConvert::dtoa(rs.m_WorldStandard)) );

						if(iDisNewGroupMessage)		
							strColumn->Add( _T(rs.m_NewGroupMessage));

						if(iDisNewGroupID)		
							strColumn->Add( _T(strNewGroupID) );



						html.HtmlTable(strColumn);

						rs.MoveNext( );

						strColumn->RemoveAll( );
					}

				}

				strColumn->FreeExtra( );
				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsEventTallyForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsEventTallyExecute;

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


			CSeriesSet rsSeries( &db );

			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select the Series' to Tally Events\r\n");

				html.StartForm("Event Tally", auth.m_strFrwdLink);
				
				html.HorizontalRule();

				if( !rsSeries.IsEOF( ) )
				{
					html.CheckBox("Series", 
						rsSeries.m_SeriesDescription, 
						"SeriesIDList", 
						CConvert::itoa(rsSeries.m_SeriesID), 
						CConvert::itoa(rsSeries.m_SeriesID));

					rsSeries.MoveNext( );
				}

				while( !rsSeries.IsEOF( ) )
				{
					html.CheckBox("", 
						rsSeries.m_SeriesDescription, 
						"SeriesIDList", 
						CConvert::itoa(rsSeries.m_SeriesID), 
						"0");
					rsSeries.MoveNext( );
				}

				html.HorizontalRule();

				html.EditIntBox("Tally Range Top", "TallyTop", 999);
				html.EditIntBox("Bottom", "TallyBot", 10);
				html.HorizontalRule();

				html.RadioButton("Start Tally Using", "All Events", "UseAllEvents", "1", "1");
				html.RadioButton("", "First Event for Season", "UseAllEvents", "0", "1");

				html.RadioButton("", "Event Date Range", "UseAllEvents", "2", "1");
				html.DateBox("From", "EventDateFrom", -365);
				html.DateBox("To", "EventDateTo");

				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsEventTallyExecute(CHttpServerContext* pCtxt,
										 LPTSTR szSeriesIDList,
										 LPTSTR szTallyTop,
										 LPTSTR szTallyBot,
										 LPTSTR szUseAllEvents,
										 LPTSTR szEventDateFromDAY,
										 LPTSTR szEventDateFromMONTH,
										 LPTSTR szEventDateFromYEAR,
									 	 LPTSTR szEventDateToDAY,
										 LPTSTR szEventDateToMONTH,
										 LPTSTR szEventDateToYEAR,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		CString strSQLSeries;

		int iORflag = 0;
		int iUseAllEvents = atoi(szUseAllEvents);

		CString strSeriesIDList = szSeriesIDList;

		CStringArray* strItems = new CStringArray();

		CCSV csv(CWebAthlExtension::chIsapiDelimiter);
		csv.GetItems(strItems, &strSeriesIDList);


		// maps key-value pairs.
		// this map, maps an int key to an CPoint(int x, int y) value.
		CMap<int,int,CPoint,CPoint>* pMap;
		CString strError;


		if( iUseAllEvents == 2 ) // EventDateRange
		{
			COleDateTime dateEventFrom( 
				atoi(szEventDateFromYEAR),
				atoi(szEventDateFromMONTH),
				atoi(szEventDateFromDAY),
				0, 0, 0
			);

			COleDateTime dateEventTo( 
				atoi(szEventDateToYEAR),
				atoi(szEventDateToMONTH),
				atoi(szEventDateToDAY),
				0, 0, 0
			);

			if( dateEventFrom.GetStatus() == COleDateTime::valid && 
				dateEventTo.GetStatus()   == COleDateTime::valid    )
			{
				CString strConnect = prop.GetDefaultConnect();

				pMap = CUtil::FindEventsBetweenDates(strConnect, dateEventFrom, dateEventTo, strItems, &strError);
			}
			else
			{
				strError = _T("Invalid Event Date");
			}

		}

		// For EventDateRange
		CString strSQLBetween = _T(" ( Results.SeriesID = %d AND Event.EventNo BETWEEN %d AND %d ) ");

		for( int nIndex = 0; nIndex < strItems->GetSize( ) ; nIndex++ )
		{
			CString strSeriesID = strItems->GetAt(nIndex);
			int iSeriesID = atoi(strSeriesID);

			if( iSeriesID > 0 )
			{
				if( !iORflag )
					iORflag = 1;
				else
					strSQLSeries += _T(" OR ");

				if( iUseAllEvents == 0 ) // FirstEventForSeason
				{
					strSQLSeries += _T(" ( Results.SeriesID = ");
					strSQLSeries += _T(strSeriesID);
					strSQLSeries += _T(" AND Results.EventID >= ( ");
					strSQLSeries += _T(" SELECT SeriesSeason.FirstEventForSeason ");
					strSQLSeries += _T(" FROM   SeriesSeason ");
					strSQLSeries += _T(" WHERE  SeriesID = ");
					strSQLSeries += _T(strSeriesID);
					strSQLSeries += _T("   ) ");
					strSQLSeries += _T(" ) ");
				}
				else if( iUseAllEvents == 1 ) // AllEvents
				{
					strSQLSeries += _T(" ( Results.SeriesID = ");
					strSQLSeries += _T(strSeriesID);
					strSQLSeries += _T(" ) ");
				}
				else if( iUseAllEvents == 2 ) // EventDateRange
				{
					CString strSQLBetweenTmp;
					CPoint ptEventNo;

					if( pMap != NULL && pMap->Lookup( iSeriesID, ptEventNo ) )
					{
						strSQLBetweenTmp.Format(strSQLBetween, 
							iSeriesID, ptEventNo.x, ptEventNo.y);

						strSQLSeries += strSQLBetweenTmp;
					}

				}

			}
		}

		if( pMap != NULL && iUseAllEvents == 2 ) // EventDateRange
			delete pMap;

		if( !strSQLSeries.IsEmpty() )
		{

			if( strError.IsEmpty() )
			{

				try
				{
					CString strConnect = prop.GetDefaultConnect();
					CString strSQL;
					CString strSQLtmp;

					CDatabase db;
					db.OpenEx( strConnect, CDatabase::noOdbcDialog );


					CEventTallySet rs( &db );

					CUtil::LoadLongResource(strSQLtmp, IDS_SQL_EVENTTALLY);
					strSQL.Format(strSQLtmp,
						_T(strSQLSeries),
						_T(szTallyBot),
						_T(szTallyTop));

					//html << strSQL;

					rs.Open(CRecordset::forwardOnly, strSQL );

					if( !rs.IsEOF( ) )
					{
						CString strEventTally;

						strEventTally.Format("Event Tally");

						if( iUseAllEvents == 0 ) // FirstEventForSeason
						{
							strEventTally += _T(" -> From First Event for Season");
						}
						else if( iUseAllEvents == 1 ) // AllEvents
						{
							strEventTally += _T(" -> All Events");
						}
						else if( iUseAllEvents == 2 ) // EventDateRange
						{
							strEventTally += _T(" -> Event Date Range");
						}

						CString* strRow = csv.GetCSVRow(strItems);

						CDatabase dbSeries;
						dbSeries.OpenEx( strConnect, CDatabase::noOdbcDialog );

						html.StartForm(strEventTally, "");

						if( iUseAllEvents == 2 ) // EventDateRange
						{
							html.NonEditDateBox("From",
												atoi(szEventDateFromDAY),
												atoi(szEventDateFromMONTH),
												atoi(szEventDateFromYEAR));

							html.NonEditDateBox("To",
												atoi(szEventDateToDAY),
												atoi(szEventDateToMONTH),
												atoi(szEventDateToYEAR));
						}

						CSeriesSet rsSeries( &dbSeries );
						strSQL.Format("SELECT * FROM Series WHERE SeriesID IN ( %s ) ORDER BY SeriesDescription", *strRow);
						rsSeries.Open(CRecordset::forwardOnly, strSQL );

						while( !rsSeries.IsEOF( ) )
						{
							html.NonEditText("", rsSeries.m_SeriesDescription);

							rsSeries.MoveNext( );
						}

						rsSeries.Close( );

						html.EndForm();

						dbSeries.Close( );

						delete strRow;


						html.StartForm("", "");

						CStringArray* strColumn;
						strColumn = new CStringArray;

						strColumn->Add( "PersonID" );
						strColumn->Add( "Name" );
						strColumn->Add( "Event Tally" );

						html.HtmlTable(strColumn);

						html.HorizontalRule(strColumn->GetSize( ) );

						strColumn->RemoveAll( );

						while( !rs.IsEOF( ) )
						{
							strColumn->Add( _T(CConvert::itoa(rs.m_PersonID)) );
							strColumn->Add( _T(rs.m_FirstName) + " " +
										 _T(rs.m_LastName) );
							strColumn->Add( _T(CConvert::itoa(rs.m_EventTally)) );

							html.HtmlTable(strColumn);

							strColumn->RemoveAll( );

							rs.MoveNext( );
						}

						strColumn->FreeExtra( );
						delete strColumn;

						html.EndForm();
					}
					else
					{
						html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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
				html << _T( strError ) ;
			}

		}
		else
		{
			html << _T("No Series Selected to Tally");
		}

		delete strItems;

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ReportsResultsExecute(CHttpServerContext* pCtxt,
									  LPTSTR szSeriesID,
									  LPTSTR szEventID,
									  LPTSTR szOrderByDivision,
									  LPTSTR szOption,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisDivisionAct			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayDivisionAct);
		int iDisDivision			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayDivision);
		int iDisOverallPlace		= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayOverallPlace);
		int iDisPlace				= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayPlace);
		int iDisPersonID			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayPersonID);
		int iDisFirstName			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayFirstName);
		int iDisLastName			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayLastName);
		int iDisAgeGroup			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayAgeGroup);
		int iDisGroup				= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayGroup);
		int iDisGroupAct			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayGroupAct);
		int iDisGroupStart			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayGroupStart);
		int iDisGrossPerformance	= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayGrossPerformance);
		int iDisNetPerformance		= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayNetPerformance);
		int iDisEventRate			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayEventRate);
		int iDisGroupRate			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayGroupRate);
		int iDisWAVA				= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayWAVA);
		int iDisPoints				= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayPoints);
		int iDisPercentile			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayPercentile);
		int iDisEligible			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayEligible);
		int iDisNewGroupMsg			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayNewGroupMsg);
		int iDisNewGroup			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayNewGroup);
		int iDisOrganisation		= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayOrganisation);
		int iDisChestNumber			= CReportResultsOption::IsMember( dwOption, CReportResultsOption::DisplayChestNumber);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQLtmp;
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CResultsOrgSet rs( &db );

			CUtil::LoadLongResource(strSQL, IDS_SQL_RESULTSORG);

			strSQLtmp.Format(
				_T(" WHERE ((Results.SeriesID = %s) AND (Results.EventID = %s)) "),
				_T(szSeriesID),
				_T(szEventID));

			strSQL += strSQLtmp;

			if(atoi(szOrderByDivision))
				strSQL += _T(" ORDER BY Results.DivisionActual, Results.OverallPlace ");
			else
				strSQL += _T(" ORDER BY Results.OverallPlace, Results.DivisionActual ");

			//html << _T(strSQL);


			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Results");

				html.StartForm(strTitle, "");


				html.NonEditText("Series", rs.m_SeriesDescription );
				html.NonEditEvent(
					"Event", 
					rs.m_EventNo,
					rs.m_LocationDescription,
					rs.m_EventDescription );

				html.NonEditDateBox(
					"Date",
					rs.m_DateDAY,
					rs.m_DateMONTH,
					rs.m_DateYEAR);


				strSQL.Format( "SELECT COUNT(*) AS Total FROM Results WHERE SeriesID = %s AND EventID = %s", szSeriesID, szEventID );

				CDatabase dbCount;
				dbCount.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CCountResultSet rsCount( &dbCount );
				rsCount.Open(CRecordset::forwardOnly, strSQL );

				html.NonEditInt("Participants", rsCount.m_Total );

				html.EndForm();

				rsCount.Close( );
				dbCount.Close( );


				CString strNewGroupID;


				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisDivisionAct)			strColumn->Add( "DivAct" );
				if(iDisDivision)			strColumn->Add( "Div" );
				if(iDisOverallPlace)		strColumn->Add( "OverallPlace" );
				if(iDisPlace)				strColumn->Add( "Place" );
				if(iDisPersonID)			strColumn->Add( "PersonID" );
				if(iDisFirstName)			strColumn->Add( "FistName" );
				if(iDisLastName)			strColumn->Add( "LastName" );
				if(iDisAgeGroup)			strColumn->Add( "AgeGroup" );
				if(iDisGroup)				strColumn->Add( "Group" );
				if(iDisGroupAct)			strColumn->Add( "GroupAct" );
				if(iDisGroupStart)			strColumn->Add( "GroupStart" );
				if(iDisGrossPerformance)	strColumn->Add( "GrossPerformance" ); 
				if(iDisNetPerformance)		strColumn->Add( "NetPerformance" );    
				if(iDisEventRate)			strColumn->Add( "EventRate" );
				if(iDisGroupRate)			strColumn->Add( "GroupRate" );
				if(iDisWAVA)				strColumn->Add( "AgeStandard" );
				if(iDisPoints)				strColumn->Add( "Points" );
				if(iDisPercentile)			strColumn->Add( "Percentile" );
				if(iDisEligible)			strColumn->Add( "Eligible" );
				if(iDisNewGroupMsg)			strColumn->Add( "Comment" );
				if(iDisNewGroup)			strColumn->Add( "NewGroup" );
				if(iDisOrganisation)		strColumn->Add( "Organisation" );
				if(iDisChestNumber)			strColumn->Add( "ChestNumber" );

				if( strColumn->GetSize( ) )
				{
					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					while( !rs.IsEOF( ) )
					{

						if( rs.IsFieldNull( &rs.m_NewGroupID ) && !rs.m_NewGroupMessage.Compare("") )
							strNewGroupID.Format("");
						else
							strNewGroupID.Format(CConvert::itoa(rs.m_NewGroupID));



						if(iDisDivisionAct)	
							strColumn->Add( _T(CConvert::itoa(rs.m_DivisionActual)) );
						if(iDisDivision)	
							strColumn->Add( _T(CConvert::itoa(rs.m_DivisionSupposedTo)) );
						if(iDisOverallPlace)	
							strColumn->Add( _T(CConvert::itoa(rs.m_OverallPlace)) );
						if(iDisPlace)		
							strColumn->Add( _T(CConvert::itoa(rs.m_Place)) );
						if(iDisPersonID)	
							strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );

						if(iDisFirstName)	
							strColumn->Add( _T(rs.m_FirstName) );
						if(iDisLastName)	
							strColumn->Add( _T(rs.m_LastName) );

						if(iDisAgeGroup)	
							strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(rs.m_AgeGroup)) );

						if(iDisGroup)		
							strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDSupposedTo)) );
						if(iDisGroupAct)		
							strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDActual)) );

						if(iDisGroupStart)		
							strColumn->Add( _T(CConvert::dtoa(rs.m_GroupStartActual)) );

						if(iDisGrossPerformance)
							strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
													   rs.m_GrossPerformanceHOUR, 
													   rs.m_GrossPerformanceMIN,
													   rs.m_GrossPerformanceSEC) ));

						if(iDisNetPerformance)	
							strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
													   rs.m_NetPerformanceHOUR, 
													   rs.m_NetPerformanceMIN,
													   rs.m_NetPerformanceSEC) ));

						if(iDisEventRate)	
							strColumn->Add( _T(CConvert::dtoa(rs.m_EventRate)) );
						if(iDisGroupRate)	
							strColumn->Add( _T(CConvert::dtoa(rs.m_GroupRate)) );

						if(iDisWAVA)		
							strColumn->Add( _T(CConvert::dtoa(rs.m_WorldStandard)) );
						
						if(iDisPoints)		
							strColumn->Add( _T(CConvert::itoa(rs.m_Points)) );
						if(iDisPercentile)	
							strColumn->Add( _T(CConvert::itoa(rs.m_Percentile)) );
						if(iDisEligible)	
							strColumn->Add( _T(rs.m_Eligible) );

						if(iDisNewGroupMsg)		
							strColumn->Add( _T(rs.m_NewGroupMessage));
						if(iDisNewGroup)	
							strColumn->Add( _T( "<p align=\"right\">" + strNewGroupID ) );

						if(iDisOrganisation)	
							strColumn->Add( _T(rs.m_OrgName));

						if(iDisChestNumber)	
							strColumn->Add( _T(rs.m_ChestNumber));

						html.HtmlTable(strColumn);

						rs.MoveNext( );

						strColumn->RemoveAll( );

					}

				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T("No Results Available\r\n");
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

void CWebAthlExtension::ReportsResultsForm(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsResultsExecute;

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
				CString strEvent;
				CString strOrderByDivision;

				int iMaxDiv;

				strSQL.Format( "SELECT MAX(DivisionActual) AS Val FROM Results WHERE SeriesID = %s", szSeriesID );

				CIntegerSet rsMaxDiv( &db );
				rsMaxDiv.Open(CRecordset::dynaset, strSQL );

				if( rsMaxDiv.IsEOF( ) || rsMaxDiv.IsFieldNull( &rsMaxDiv.m_Val ) )
					iMaxDiv = 0;
				else
					iMaxDiv = rsMaxDiv.m_Val;

				rsMaxDiv.Close( );


				html << _T("Select an Event\r\n");

				html.StartForm("Results", auth.m_strFrwdLink);

				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, -1, NULL);
				html.HorizontalRule();

				if(iMaxDiv > 1)
					strOrderByDivision.Format("%d", 1); 
				else
					strOrderByDivision.Format("%d", 0); 

				html.RadioButton("Order By", 
								 "Overall-Place", 
								 "OrderByDivision", 
								 "0",
								 strOrderByDivision);

				html.RadioButton("", 
								 "Division", 
								 "OrderByDivision", 
								 "1",
								 strOrderByDivision);

				html.HorizontalRule();


				CReportResultsOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsGroupsListExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szEventID,
										  LPTSTR szEventsMin,
										  LPTSTR szEligible,
										  LPTSTR szDivision,
										  LPTSTR szGroup,
										  LPTSTR szSex,
										  LPTSTR szAgeGroup,
										  LPTSTR szPoints,
										  LPTSTR szNameDesc,
										  LPTSTR szOption,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisPersonID			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayPersonID);
		int iDisLastName			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayLastName);
		int iDisFirstName			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayFirstName);
		int iDisSexAgeGroup			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplaySexAgeGroup);
		int iDisDivisionSupposedTo	= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayDivisionSupposedTo);
		int iDisGroupIDSupposedTo	= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayGroupIDSupposedTo);
		int iDisEventsForSeason		= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayEventsForSeason);
		int iDisEventsForSeries		= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayEventsForSeries);
		int iDisNetPoints			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayNetPoints);
		int iDisEligibilityForEvent	= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayEligibilityForEvent);
		int iDisGroupStart			= CReportGroupsListOption::IsMember( dwOption, CReportGroupsListOption::DisplayGroupStart);

		int iDivision	= atoi(szDivision);
		int iGroup		= atoi(szGroup);
		int iSex		= atoi(szSex);
		int iAgeGroup	= atoi(szAgeGroup);
		int iPoints		= atoi(szPoints);
		int iNameDesc	= atoi(szNameDesc);

		int iEventsMin	= atoi(szEventsMin);
		int iEligible	= atoi(szEligible);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CGroupsReportSet rs( &db );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GROUPSREPORT);
			strSQL.Format(strSQLtmp, _T(szSeriesID), _T(szEventID));

			if(iEventsMin > 0)
			{
				strSQL += _T(" AND ( ParticipantForSeries.ConsistencyEventsCurrent >= ");
				strSQL += _T(CConvert::itoa(iEventsMin));
				strSQL += _T(" ) ");
			}
			if(iEligible)
			{
				strSQL += _T(" AND ( ParticipantForSeries.EligibilityForEvent = '");
				strSQL += _T("Y");
				strSQL += _T("' ) ");
			}

			strSQL += _T( " ORDER BY " );

			// ORDER BY clause :
			if(iDivision)
				strSQL += _T( " ParticipantForSeries.DivisionSupposedTo , " );
			if(iGroup)
				strSQL += _T( " ParticipantForSeries.GroupIDSupposedTo , " );
			if(iSex)
				strSQL += _T( " Person.Sex , " );
			if(iAgeGroup)
				strSQL += _T( " ParticipantForSeries.ConsistencyAgeGroup , " );
			if(iPoints)
				strSQL += _T( " ParticipantForSeries.NetPoints DESC, " );
			if(iNameDesc)
				strSQL += _T( " Person.LastName DESC, Person.FirstName DESC, Person.MiddleName DESC " );
			else
				strSQL += _T( " Person.LastName ASC, Person.FirstName ASC, Person.MiddleName ASC " );


			//html << _T(strSQL);

			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Groups List");

				html.StartForm(strTitle, "");


				html.NonEditText("Series", rs.m_Series_SeriesDescription );
				html.NonEditEvent(
					"Event", 
					rs.m_Event_EventNo,
					rs.m_Location_LocationDescription,
					rs.m_EventType_EventDescription );

				html.NonEditDateBox(
					"Date",
					rs.m_Event_DateDAY,
					rs.m_Event_DateMONTH,
					rs.m_Event_DateYEAR);


				html.EndForm();


				CString strAgeCategory;
				int iAgeGroup;


				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisPersonID)			strColumn->Add( "PersonID" );
				if(iDisLastName)			strColumn->Add( "LastName" );
				if(iDisFirstName)			strColumn->Add( "FirstName" );
				if(iDisSexAgeGroup)			strColumn->Add( "AgeGroup" );
				if(iDisDivisionSupposedTo)	strColumn->Add( "Division" );
				if(iDisGroupIDSupposedTo)	strColumn->Add( "Group" );
				if(iDisEventsForSeason)		strColumn->Add( "SeasonEvents" );
				if(iDisEventsForSeries)		strColumn->Add( "SeriesEvents" );
				if(iDisNetPoints)			strColumn->Add( "Points" );
				if(iDisEligibilityForEvent)	strColumn->Add( "Elig" );
				if(iDisGroupStart)			strColumn->Add( "GroupStart" );

				html.HtmlTable(strColumn);
				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );


				while( !rs.IsEOF( ) )
				{
					int nDateAgeDAY = rs.m_Event_DateAgeDAY;
					int nDateAgeMONTH = rs.m_Event_DateAgeMONTH;
					int nDateAgeYEAR = rs.m_Event_DateAgeYEAR;

					if( rs.IsFieldNull( &rs.m_Event_DateAgeDAY ) ||
						rs.IsFieldNull( &rs.m_Event_DateAgeMONTH ) ||
						rs.IsFieldNull( &rs.m_Event_DateAgeYEAR ) || 
						rs.m_Event_DateAgeDAY == 0 ||
						rs.m_Event_DateAgeMONTH == 0 ||
						rs.m_Event_DateAgeYEAR == 0 ) 
					{
						nDateAgeDAY = rs.m_Event_DateDAY;
						nDateAgeMONTH = rs.m_Event_DateMONTH;
						nDateAgeYEAR = rs.m_Event_DateYEAR;
					}


					iAgeGroup = CCalculate::GroupAge(
										CCalculate::YearDiff(rs.m_Person_dobDAY,
												 rs.m_Person_dobMONTH,
												 rs.m_Person_dobYEAR,
												 nDateAgeDAY,
												 nDateAgeMONTH,
												 nDateAgeYEAR),
										strAgeCategory,
										&prop);

					if(iDisPersonID)
						strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );

					if(iDisLastName)
						strColumn->Add( _T(rs.m_Person_LastName) );

					if(iDisFirstName)
						strColumn->Add( _T(rs.m_Person_FirstName) );

					if(iDisSexAgeGroup)
						strColumn->Add( _T(rs.m_Person_Sex) + _T(CConvert::itoa(iAgeGroup)) );

					if(iDisDivisionSupposedTo)
						strColumn->Add( _T(CConvert::itoa(rs.m_PFS_DivisionSupposedTo)) );

					if(iDisGroupIDSupposedTo)
						strColumn->Add( _T(CConvert::itoa(rs.m_PFS_GroupIDSupposedTo)) );

					if(iDisEventsForSeason)
						strColumn->Add( _T(CConvert::itoa(rs.m_PFS_EventsForSeason)) );

					if(iDisEventsForSeries)
						strColumn->Add( _T(CConvert::itoa(rs.m_PFS_EventsForSeries)) );

					if(iDisNetPoints)
						strColumn->Add( _T(CConvert::itoa(rs.m_PFS_NetPoints)) );

					if(iDisEligibilityForEvent)
						strColumn->Add( _T(rs.m_PFS_EligibilityForEvent) );

					if(iDisGroupStart)
						strColumn->Add( _T(CConvert::dtoa(rs.m_Groups_GroupStart)) );

					html.HtmlTable(strColumn);

					rs.MoveNext( );

					strColumn->RemoveAll( );
				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T("No Results Available\r\n");
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

void CWebAthlExtension::ReportsGroupsListForm(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsGroupsListExecute;

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
				CString strEvent;

				html << _T("Select an Event\r\n");

				html.StartForm("Groups List", auth.m_strFrwdLink);

				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, -1, NULL);
				html.HorizontalRule();


				int nNull;
				CRecordsetEx::GetNullItem(&nNull);

				html.EditIntBox("Minimum Number of Events", "EventsMin", nNull);
				html.HorizontalRule();

				html.CheckBox( "Eligible", "Yes", "Eligible", "1", "0");
				html.HorizontalRule();

				html.CheckBox("Order By", "Division", "Division", "1", "0");
				html.CheckBox("",         "Group",    "Group",    "1", "0");
				html.CheckBox("",         "Sex",      "Sex",      "1", "0");
				html.CheckBox("",         "Points",   "Points",   "1", "0");

				html.RadioButton("", "Name Ascending", "NameDesc",	"0", "0");
				html.RadioButton("", "Name Descending","NameDesc",	"1", "0");

				html.HorizontalRule();

				CReportGroupsListOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

/*
void CWebAthlExtension::ReportsEligibilityExecute(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szEventID,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CString strSQLtmp;

			CGroupsReportSet rs( &db );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GROUPSREPORT);
			strSQL.Format(strSQLtmp, _T(szSeriesID), _T(szEventID));	

			strSQL += _T(" AND ( ParticipantForSeries.EligibilityForEvent = 'Y' ) ");

			strSQL += _T(" ORDER BY Person.LastName, Person.FirstName, Person.MiddleName");

			//html << _T(strSQL);

			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Eligibility List");

				html.StartForm(strTitle, "");


				html.NonEditText("Series", rs.m_Series_SeriesDescription );
				html.NonEditEvent(
					"Event", 
					rs.m_Event_EventNo,
					rs.m_Location_LocationDescription,
					rs.m_EventType_EventDescription );

				html.NonEditDateBox(
					"Date",
					rs.m_Event_DateDAY,
					rs.m_Event_DateMONTH,
					rs.m_Event_DateYEAR);


				html.EndForm();


				CString strAgeCategory;
				int iAgeGroup;


				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				strColumn->Add( "PersonID" );
				strColumn->Add( "Name" );
				strColumn->Add( "Group" );
				strColumn->Add( "Handicap" );
				strColumn->Add( "AgeGroup" );
				strColumn->Add( "Elig" );
				strColumn->Add( "Points" );
				strColumn->Add( "Events" );
				strColumn->Add( "Division" );

				html.HtmlTable(strColumn);
				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );


				while( !rs.IsEOF( ) )
				{

					iAgeGroup = CCalculate::GroupAge(
										CCalculate::YearDiff(rs.m_Person_dobDAY,
												 rs.m_Person_dobMONTH,
												 rs.m_Person_dobYEAR,
												 rs.m_Event_DateDAY,
												 rs.m_Event_DateMONTH,
												 rs.m_Event_DateYEAR),
										strAgeCategory,
										&prop);


					strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );

					strColumn->Add( _T(rs.m_Person_LastName) + ", " +
								 _T(rs.m_Person_FirstName) );

					strColumn->Add( _T(CConvert::itoa(rs.m_PFS_GroupIDSupposedTo)) );
					strColumn->Add( _T(CConvert::dtoa(rs.m_Groups_GroupStart)) );

					strColumn->Add( _T(rs.m_Person_Sex) + _T(CConvert::itoa(iAgeGroup)) );

					strColumn->Add( _T(rs.m_PFS_EligibilityForEvent) );
					strColumn->Add( _T(CConvert::itoa(rs.m_PFS_NetPoints)) );
					strColumn->Add( _T(CConvert::itoa(rs.m_PFS_EventsForSeason)) );

					strColumn->Add( _T(CConvert::itoa(rs.m_PFS_DivisionSupposedTo)) );

					html.HtmlTable(strColumn);

					rs.MoveNext( );

					strColumn->RemoveAll( );

				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T("No Results Available\r\n");
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
*/

/*
void CWebAthlExtension::ReportsEligibilityForm(CHttpServerContext* pCtxt,
												  LPTSTR szSeriesID,
												  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsEligibilityExecute;

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
				CString strEvent;

				html << _T("Select an Event\r\n");

				html.StartForm("Eligibility List", auth.m_strFrwdLink);

				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, -1, NULL);
				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

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
*/

void CWebAthlExtension::ReportsRosterForm(CHttpServerContext* pCtxt,
										 LPTSTR szSeriesID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsRosterExecute;

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
				CString strEvent;

				html << _T("Select an Event\r\n");

				html.StartForm("Event Roster", auth.m_strFrwdLink);

				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event", "EventID", &rsEvent, -1, NULL);
				html.HorizontalRule();

				html.CheckBox("Order By", "Task Description", "OrderByTask", "1", "0");
				html.RadioButton("", "Name Ascending", "NameDesc",	"0", "0");
				html.RadioButton("", "Name Descending","NameDesc",	"1", "0");
				html.HorizontalRule();

				CReportRosterOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					if( auth.HasPermission(enumList.GetPermission()) )
					{
						html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
							CConvert::dwtoa(dwEnum), 
							CConvert::dwtoa(enumList.GetDefaultSelect()) );
					}
				}
				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsRosterExecute(CHttpServerContext* pCtxt,
									 LPTSTR szSeriesID,
									 LPTSTR szEventID,
									 LPTSTR szOrderByTask,
									 LPTSTR szNameDesc,
									 LPTSTR szOption,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisTaskDescription			= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayTaskDescription);
		int iDisPersonID				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayPersonID);
		int iDisLastName				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayLastName);
		int iDisFirstName				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayFirstName);
		int iDisMiddleName				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayMiddleName);
		int iDisSexAgeGroup				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplaySexAgeGroup);
		int iDisDOB						= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayDOB);
		int iDisAddress					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayAddress);
		int iDisTown					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayTown);
		int iDisState					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayState);
		int iDisPostCode				= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayPostCode);
		int iDisCountry					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayCountry);
		int iDisPhoneHm					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayPhoneHm);
		int iDisPhoneWk					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayPhoneWk);
		int iDisFax						= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayFax);
		int iDisMobile					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayMobile);
		int iDisEmail					= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayEmail);
		int iDisContactPersonID			= CReportRosterOption::IsMember( dwOption, CReportRosterOption::DisplayContactPersonID);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( html.GetNonEditEventBoxDetails(atoi(szEventID)) );

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


			strSQLtmp.Empty();

			strSQLtmp += _T("SELECT Roster.*, RosterDescriptions.*, Person.* ");
			strSQLtmp += _T(" FROM Roster, RosterDescriptions, Person ");
			strSQLtmp += _T(" WHERE EventID = %s ");
			strSQLtmp += _T(" AND Roster.PersonID = Person.PersonID ");
			strSQLtmp += _T(" AND Roster.TaskID = RosterDescriptions.TaskID ");
			strSQLtmp += _T(" ORDER BY " );

			strSQL.Format(strSQLtmp, szEventID );

			if(atoi(szOrderByTask))
			{
				strSQL += " RosterDescriptions.TaskDescription, ";
			}
			if(atoi(szNameDesc))
			{
				strSQL += " Person.LastName DESC, Person.FirstName DESC, Person.MiddleName DESC";
			}
			else
			{
				strSQL += " Person.LastName ASC, Person.FirstName ASC, Person.MiddleName ASC";
			}


			CRosterNamesSet rs( &db );
			rs.Open(CRecordset::forwardOnly, strSQL );



			if( !rs.IsEOF( ) )
			{
				CString strAgeCategory;
				int iAgeGroup;

				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisTaskDescription)
					strColumn->Add( "Task" );
				if(iDisPersonID)
					strColumn->Add( "PersonID" );
				if(iDisLastName)
					strColumn->Add( "LastName" );
				if(iDisFirstName)
					strColumn->Add( "FirstName" );
				if(iDisMiddleName)
					strColumn->Add( "MiddleName" );
				if(iDisSexAgeGroup)
					strColumn->Add( "AgeGroup" );
				if(iDisDOB)
					strColumn->Add( "Date of Birth" );
				if(iDisAddress)
				{
					strColumn->Add( "Address" );
					strColumn->Add( "" );
				}
				if(iDisTown)
					strColumn->Add( "Town" );
				if(iDisState)
					strColumn->Add( "State" );
				if(iDisPostCode)
					strColumn->Add( "PostCode" );
				if(iDisCountry)
					strColumn->Add( "Country" );
				if(iDisPhoneHm)
					strColumn->Add( "PhoneHm" );
				if(iDisPhoneWk)
					strColumn->Add( "PhoneWk" );
				if(iDisFax)
					strColumn->Add( "Fax" );
				if(iDisMobile)
					strColumn->Add( "Mobile" );
				if(iDisEmail)
					strColumn->Add( "Email" );
				if(iDisContactPersonID)
					strColumn->Add( "ContactID" );

				html.HtmlTable(strColumn);
				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );


				while( !rs.IsEOF( ) )
				{
					if(iDisTaskDescription)
						strColumn->Add( _T(rs.m_TaskDescription) );
					if(iDisPersonID)
						strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );
					if(iDisLastName)
						strColumn->Add( _T(rs.m_LastName) );
					if(iDisFirstName)
						strColumn->Add( _T(rs.m_FirstName) );
					if(iDisMiddleName)
						strColumn->Add( _T(rs.m_MiddleName) );
					if(iDisSexAgeGroup)
					{
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

						iAgeGroup = CCalculate::GroupAge(
											CCalculate::YearDiff(rs.m_dobDAY,
													 rs.m_dobMONTH,
													 rs.m_dobYEAR,
													 nDateAgeDAY,
													 nDateAgeMONTH,
													 nDateAgeYEAR),
											strAgeCategory,
											&prop);

						strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(iAgeGroup)) );
					}
					if(iDisDOB)
						strColumn->Add( _T( CFormat::FormatDate(rs.m_dobDAY, rs.m_dobMONTH,rs.m_dobYEAR)) );
					if(iDisAddress)
					{
						strColumn->Add( _T(rs.m_Address1) );
						strColumn->Add( _T(rs.m_Address2) );
					}
					if(iDisTown)
						strColumn->Add( _T(rs.m_Town) );
					if(iDisState)
						strColumn->Add( _T(rs.m_State) );
					if(iDisPostCode)
						strColumn->Add( _T(rs.m_PostCode) );
					if(iDisCountry)
						strColumn->Add( _T(rs.m_Country) );
					if(iDisPhoneHm)
						strColumn->Add( _T(rs.m_PhoneHm) );
					if(iDisPhoneWk)
						strColumn->Add( _T(rs.m_PhoneWk) );
					if(iDisFax)
						strColumn->Add( _T(rs.m_Fax) );
					if(iDisMobile)
						strColumn->Add( _T(rs.m_Mobile) );
					if(iDisEmail)
						strColumn->Add( _T(rs.m_email) );
					if(iDisContactPersonID)
						strColumn->Add( _T(CConvert::itoa(rs.m_ContactPersonID)) );


					html.HtmlTable(strColumn);

					rs.MoveNext( );

					strColumn->RemoveAll( );

				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T("No Roster Available\r\n");
			}
			rsSeries.Close( );
			rsEvent.Close( );

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

void CWebAthlExtension::ReportsPersonForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ViewPerson | CModule::EditPerson | CModule::Financial) )
	{
		auth.m_strFrwdLink = CPage::ReportsPersonExecute;

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

			CSeriesSet rsSeries( &db );
			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			COrganisationSet rsOrg( &db );
			strSQL.Format( "SELECT * FROM Organisation ORDER BY OrgName" );
			rsOrg.Open(CRecordset::dynaset, strSQL );

			CRegistrationTypeSet rsRegType( &db );
			strSQL.Format( "SELECT * FROM RegistrationType " );
			rsRegType.Open(CRecordset::dynaset, strSQL );

			CStringSet rsComments( &db );
			strSQL.Format( "SELECT DISTINCT Type AS Val FROM PersonComments ORDER BY Val" );
			rsComments.Open(CRecordset::dynaset, strSQL );


			COleDateTime t = COleDateTime::GetCurrentTime();

			html.StartForm("Person Details", auth.m_strFrwdLink);

			html.HRuleAlign(6,6,0);
			html.MultiFormHeader("Filter By :","Filter into the Report Everyone who :");
			html.MultiFormComment("( i.e., Filter out Everyone who is not : )" );

			if( auth.HasPermission(CModule::Financial) )
			{
				html.HRuleAlign(6,5,0);
				html.MultiFormCheckBox("", "Financial", "Financial", "1", "1", "" );
				html.MultiFormComment("Has Financial Status :" );
				html.MultiFormRadioButton("", "Currently Financial", "optFinancial", "1", "1" );
				html.MultiFormRadioButton("", "Has Ever Been Financial", "optFinancial", "2", "1" );
				html.MultiFormRadioButton("", "Is/Was Financial During :", "optFinancial", "3", "1" );
				html.MultiFormEditIntBox("", "Financial Year", "optFinancialYear", t.GetYear( ) );

				html.HRuleAlign(6,5,0);
				html.MultiFormCheckBox("", "Registration Type", "RegistrationType", "1", "0", "" );
				html.MultiFormComment("Has Registration Type :" );
				if( !rsRegType.IsEOF( ) )
				{
					html.MultiFormStartSelectBox("", "Registration Type", "optRegTypeID");
					while( !rsRegType.IsEOF( ) )
					{
						html.AddSelectBox(rsRegType.m_RegistrationDescription, CConvert::itoa(rsRegType.m_RegistrationTypeID), "" );
						rsRegType.MoveNext( );
					}
					html.EndSelectBox();
				}
			}

			if( !rsSeries.IsEOF( ) )
			{
				html.HRuleAlign(6,5,0);
				html.MultiFormCheckBox("", "Series", "Series", "1", "1", "" );
				html.MultiFormComment("Has Recently Participated in :" );
				html.MultiFormStartSelectBox( "", "Series", "optSeriesID");
				while( !rsSeries.IsEOF( ) )
				{
					html.AddSelectBox(rsSeries.m_SeriesDescription, CConvert::itoa(rsSeries.m_SeriesID), "");
					rsSeries.MoveNext( );
				}
				html.EndSelectBox();
			}

			html.HRuleAlign(6,5,0);
			html.MultiFormCheckBox("", "Age Group", "AgeGroup", "1", "0", "" );
			html.MultiFormComment("Has Current Age Group in :" );
			html.MultiFormEditIntBox("", "Age Group", "optAgeGroup", 0 );

			if( auth.HasPermission(CModule::ViewPerson | CModule::EditPerson) )
			{
				html.HRuleAlign(6,5,0);
				html.MultiFormCheckBox("", "Birthday", "Birthday", "1", "0", "" );
				html.MultiFormComment("Has Birthday During :" );
				html.MultiFormStartSelectBox("", "Month", "optMonth");
				for(int m = 1; m < 13 ; m++ )
				{
					html.AddSelectBox(CHtmlMonth::GetName(m), CConvert::itoa(m), CConvert::itoa(t.GetMonth( )));
				}
				html.EndSelectBox();
			}

			if( auth.HasPermission(CModule::Financial) )
			{
				html.HRuleAlign(6,5,0);
				html.MultiFormCheckBox("", "Mail List", "MailList", "1", "1", "" );
				html.MultiFormComment("Has MailList Status :" );
				html.MultiFormRadioButton("", "On Mailing List", "optMailList", "1", "1" );
				html.MultiFormRadioButton("", "Not on Mailing List", "optMailList", "2", "1" );

				if( !rsOrg.IsEOF( ) )
				{
					html.HRuleAlign(6,5,0);
					html.MultiFormCheckBox( "", "Organisation", "Organisation", "1", "0", "" );
					html.MultiFormComment( "Belongs to Organisation :" );
					html.MultiFormStartSelectBox( "", "Organisation", "optOrgID");
					while( !rsOrg.IsEOF( ) )
					{
						html.AddSelectBox( rsOrg.m_OrgName, CConvert::itoa(rsOrg.m_OrgID), "");
						rsOrg.MoveNext( );
					}
					html.EndSelectBox();
				}

				if( !rsComments.IsEOF( ) )
				{
					html.HRuleAlign(6,5,0);
					html.MultiFormCheckBox( "", "Comments", "Comments", "1", "0", "" );
					html.MultiFormComment( "Has a Comment of Type :" );
					html.MultiFormStartSelectBox( "", "Comment Type", "optPersonCommentsType");
					while( !rsComments.IsEOF( ) )
					{
						html.AddSelectBox( rsComments.m_Val, rsComments.m_Val, "");
						rsComments.MoveNext( );
					}
					html.EndSelectBox();
				}
			}

			html.HRuleAlign(6,6,0);
			html.MultiFormHeader( "Display :","Include the following columns on the Report : (if applicable)");

			CReportPersonOption enumList;
			DWORD dwEnum = enumList.Enumerator( );
			while( enumList.GetNext( &dwEnum ) )
			{
				if( auth.HasPermission(enumList.GetPermission()) )
				{
					html.MultiFormCheckBox(
						enumList.GetLabel(), 
						enumList.GetName(), 
						"Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()),
						enumList.GetDescription());
				}
			}

			html.HRuleAlign(6,6,0);
			html.SubmitButton(CHtmlKey::Run);

			html.EndForm();

			rsComments.Close( );
			rsRegType.Close( );
			rsOrg.Close( );
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

void CWebAthlExtension::ReportsPersonExecute(CHttpServerContext* pCtxt,
									 LPTSTR szFinancial,
									 LPTSTR szOptFinancial,
									 LPTSTR szOptFinancialYear,
									 LPTSTR szRegistrationType,
									 LPTSTR szOptRegTypeID,
									 LPTSTR szSeries,
									 LPTSTR szOptSeriesID,
									 LPTSTR szAgeGroup,
									 LPTSTR szOptAgeGroup,
									 LPTSTR szBirthday,
									 LPTSTR szOptMonth,
									 LPTSTR szMailList,
									 LPTSTR szOptMailList,
									 LPTSTR szOrganisation,
									 LPTSTR szOptOrgID,
									 LPTSTR szComments,
									 LPTSTR szOptPersonCommentsType,
									 LPTSTR szOption,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ViewPerson | CModule::EditPerson | CModule::Financial) )
	{
		CString strAgeCategory;
		CString strSeriesDescription;
		CString strOrganisation;
		CString strRegistrationType;

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iPersonID					= 0;
		int iFinancial					= atoi(szFinancial);
		int iOptFinancial				= atoi(szOptFinancial);
		int iOptFinancialYear			= atoi(szOptFinancialYear);
		int iRegistrationType			= atoi(szRegistrationType);
		int iOptRegTypeID				= atoi(szOptRegTypeID);
		int iSeries						= atoi(szSeries);
		int iOptSeriesID				= atoi(szOptSeriesID);
		int iAgeGroup					= atoi(szAgeGroup);
		int iOptAgeGroup				= CCalculate::GroupAge(atoi(szOptAgeGroup), strAgeCategory, &prop);
		int iBirthday					= atoi(szBirthday);
		int iOptMonth					= atoi(szOptMonth);
		int iMailList					= atoi(szMailList);
		int iOptMailList				= atoi(szOptMailList);
		int iOrganisation				= atoi(szOrganisation);
		int iOptOrgID					= atoi(szOptOrgID);
		int iComments					= atoi(szComments);

		int iDisPersonID				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayPersonID);
		int iDisLastName				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayLastName);
		int iDisFirstName				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayFirstName);
		int iDisMiddleName				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayMiddleName);
		int iDisAgeGroup				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayAgeGroup);
		int iDisDOB						= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayDOB);
		int iDisAddress					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayAddress);
		int iDisTown					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayTown);
		int iDisState					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayState);
		int iDisPostCode				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayPostCode);
		int iDisCountry					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayCountry);
		int iDisPhoneHm					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayPhoneHm);
		int iDisPhoneWk					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayPhoneWk);
		int iDisFax						= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayFax);
		int iDisMobile					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayMobile);
		int iDisEmail					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayEmail);
		int iDisContactPersonID			= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayContactPersonID);
		int iDisDateRenewed				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayDateRenewed);
		int iDisYear					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayYear);
		int iDisRegistrationID			= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayRegistrationID);
		int iDisRegistrationTypeID		= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayRegistrationTypeID);
		int iDisMonthStartStop			= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayMonthStartStop);
		int iDisMailListFlag			= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayMailListFlag);
		int iDisOrgName					= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayOrgName);
		int iDisComments				= CReportPersonOption::IsMember( dwOption, CReportPersonOption::DisplayComments);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		if(iFinancial || iSeries || iAgeGroup || iBirthday || iMailList || iOrganisation || iRegistrationType || iComments)
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CPersonFinancialCommentsSet rs( &db );

				COleDateTime today = COleDateTime::GetCurrentTime();

				if(iSeries)
				{
					CSeriesSet rsSeries( &db );
					strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s ", szOptSeriesID );
					rsSeries.Open(CRecordset::dynaset, strSQL );

					strSeriesDescription.Format("%s", rsSeries.m_SeriesDescription);
					rsSeries.Close( );
				}
				if(iOrganisation)
				{
					COrganisationSet rsOrg( &db );
					strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = %s ", szOptOrgID );
					rsOrg.Open(CRecordset::dynaset, strSQL );

					strOrganisation.Format("%s", rsOrg.m_OrgName);
					rsOrg.Close( );
				}
				if(iRegistrationType)
				{
					CRegistrationTypeSet rsRegType( &db );
					strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %s ", szOptRegTypeID );
					rsRegType.Open(CRecordset::dynaset, strSQL );

					strRegistrationType.Format("%s", rsRegType.m_RegistrationDescription);
					rsRegType.Close( );
				}

				strSQL.Format("SELECT Person.* , PersonComments.* ");
				if(iFinancial || iMailList || iOrganisation || iRegistrationType)
				{
					strSQL += (  ", Financial.* ");
					strSQL += (  ", RegistrationType.* ");
					strSQL += (  ", Organisation.* ");
				}

				
				strSQL += (  " FROM ");
				if(iSeries)
				{
					strSQL += ( " ParticipantForSeries INNER JOIN ( " );
				}
				if(iFinancial || iMailList || iOrganisation || iRegistrationType)
				{
					strSQL += ( " Organisation INNER JOIN ( " );
					strSQL += ( " RegistrationType INNER JOIN ( " );
					strSQL += ( " Financial INNER JOIN ( " );
				}
				strSQL += ( " Person LEFT JOIN PersonComments ON Person.PersonID = PersonComments.PersonID " );
				if(iFinancial || iMailList || iOrganisation || iRegistrationType)
				{
					strSQL += ( " ) ON Financial.PersonID = Person.PersonID " );
					strSQL += ( " ) ON RegistrationType.RegistrationTypeID = Financial.RegistrationTypeID " );
					strSQL += ( " ) ON Organisation.OrgID = Financial.OrgID " );
				}
				if(iSeries)
				{
					strSQL += ( " ) ON ParticipantForSeries.PersonID = Person.PersonID " );
				}
			
/*				
				strSQL += (  " FROM Person ");
				if(iFinancial || iMailList || iOrganisation || iRegistrationType)
				{
					strSQL += (  ", Financial ");
					strSQL += (  ", RegistrationType ");
					strSQL += (  ", Organisation ");
				}
				if(iSeries)
				{
					strSQL += (  ", ParticipantForSeries " );
				}
*/
				strSQL += (  " WHERE 1=1 ");
/*
				if(iFinancial || iMailList || iOrganisation || iRegistrationType)
				{
					strSQL += (  " AND Financial.PersonID = Person.PersonID ");
					strSQL += (  " AND Financial.RegistrationTypeID = RegistrationType.RegistrationTypeID ");
					strSQL += (  " AND Financial.OrgID = Organisation.OrgID ");
				}
				if(iSeries)
				{
					strSQL += (  " AND ParticipantForSeries.PersonID = Person.PersonID ");
				}
*/
				if(iRegistrationType)
				{
					strSQL += (  " AND Financial.RegistrationTypeID = ");
					strSQL += (  szOptRegTypeID );
					strSQL += (  " " );
				}
				if(iSeries)
				{
					strSQL += (  " AND ParticipantForSeries.SeriesID = ");
					strSQL += (  szOptSeriesID );
					strSQL += (  " " );
				}
				if(iBirthday)
				{
					strSQL += (  " AND Person.dobMONTH = ");
					strSQL += (  szOptMonth );
					strSQL += (  " " );
				}
				if(iMailList)
				{
					strSQL += (  " AND Financial.MailListFlag ");
					if( iOptMailList == 1 )
					{
						strSQL += (  " = 1 ");
					}
					else
					{
						strSQL += (  " <> 1 ");
					}
				}
				if(iOrganisation)
				{
					strSQL += (  " AND Financial.OrgID = ");
					strSQL += (  szOptOrgID );
					strSQL += (  " " );
				}
				if(iComments)
				{
					strSQL += (  " AND PersonComments.Type = '");
					strSQL += (  szOptPersonCommentsType );
					strSQL += (  "' " );
				}

				strSQL += (  " ORDER BY ");
				if(iBirthday)
				{
					strSQL += (  " Person.dobDAY, " );
					strSQL += (  " Person.dobMONTH, " );
				}
				strSQL += (  " Person.LastName, ");
				strSQL += (  " Person.FirstName, ");
				strSQL += (  " Person.PersonID ");
				if(iFinancial)
				{
					strSQL += (  ", Financial.Year DESC ");
				}

				rs.Open(CRecordset::forwardOnly, strSQL );

				//html << _T(strSQL);

				if( !rs.IsEOF( ) )
				{
					CString strTitle;
					strTitle.Format("Person Details: ");

					if(iFinancial)
					{
						strTitle += "Financial->";
						if(iOptFinancial == 1)
						{
							strTitle += "Current; ";
						}
						else if(iOptFinancial == 2)
						{
							strTitle += "Any; ";
						}
						else if(iOptFinancial == 3)
						{
							strTitle += "Year=";
							strTitle += szOptFinancialYear;
							strTitle += "; ";
						}
					}
					if(iRegistrationType)
					{
						strTitle += "RegistrationType->";
						strTitle += strRegistrationType;
						strTitle += "; ";
					}
					if(iSeries)
					{
						strTitle += "Series->";
						strTitle += strSeriesDescription;
						strTitle += "; ";
					}
					if(iAgeGroup)
					{
						strTitle += "AgeGroup->";
						strTitle += CConvert::itoa(iOptAgeGroup);
						strTitle += "; ";
					}
					if(iBirthday)
					{
						strTitle += "Birthday->";
						strTitle += CHtmlMonth::GetName(iOptMonth);
						strTitle += "; ";
					}
					if(iMailList)
					{
						strTitle += "MailList->";
						if(iOptMailList == 1)
						{
							strTitle += "Yes; ";
						}
						else
						{
							strTitle += "No; ";
						}
					}
					if(iOrganisation)
					{
						strTitle += "Organisation->";
						strTitle += strOrganisation;
						strTitle += "; ";
					}
					if( iComments )
					{
						strTitle += "CommentType->";
						strTitle += szOptPersonCommentsType;
						strTitle += "; ";
					}

					html.StartForm(strTitle, "");

					CStringArray* strColumn;
					strColumn = new CStringArray;

					if( iDisPersonID )
						strColumn->Add( "PersonID" );
					if( iDisLastName )
						strColumn->Add( "LastName" );
					if( iDisFirstName )
						strColumn->Add( "FirstName" );
					if( iDisMiddleName )
						strColumn->Add( "MiddleName" );
					if( iDisAgeGroup )
						strColumn->Add( "AgeGroup" );
					if( iDisDOB )
						strColumn->Add( "Date of Birth" );
					if( iDisAddress )
					{
						strColumn->Add( "Address" );
						strColumn->Add( "" );
					}
					if( iDisTown )
						strColumn->Add( "Town" );
					if( iDisState )
						strColumn->Add( "State" );
					if( iDisPostCode )
						strColumn->Add( "PostCode" );
					if( iDisCountry )
						strColumn->Add( "Country" );
					if( iDisPhoneHm )
						strColumn->Add( "PhoneHm" );
					if( iDisPhoneWk )
						strColumn->Add( "PhoneWk" );
					if( iDisFax )
						strColumn->Add( "Fax" );
					if( iDisMobile )
						strColumn->Add( "Mobile" );
					if( iDisEmail )
						strColumn->Add( "Email" );
					if( iDisContactPersonID )
						strColumn->Add( "ContactID" );

					if(iFinancial || iMailList || iOrganisation || iRegistrationType)
					{
						if( iDisDateRenewed )
							strColumn->Add( "Renewal Date" );
						if( iDisYear )
							strColumn->Add( "Year Valid" );
						if( iDisRegistrationID )
							strColumn->Add( "Registration ID" );
						if( iDisRegistrationTypeID )
							strColumn->Add( "Registration Type" );
						if( iDisMonthStartStop )
							strColumn->Add( "Registration Range" );
						if( iDisMailListFlag )
							strColumn->Add( "Mail List" );
						if( iDisOrgName )
							strColumn->Add( "Organisation" );
					}
					if( iComments )
					{
						if( iDisComments )
							strColumn->Add( CString("Comment ") + szOptPersonCommentsType );
					}


					html.HtmlTable(strColumn);

					html.HorizontalRule(strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					CString strMsg;

					int iEndMonthAgeGroup;
					int iTodayAgeGroup;

					int	iCalcAgeD = 1;
					int	iCalcAgeM = iOptMonth + 1;	// calculate the age based on the last 
													// day of the month
					int	iCalcAgeY = today.GetYear( );

					if (iCalcAgeM > 12)
					{
						iCalcAgeM = 1;
						iCalcAgeY++;
					}




					while( !rs.IsEOF( ) )
					{
						if(iPersonID == rs.m_PersonID)
						{
							// When duplicate PersonIDs arrive, only use the 1st one.
							// Becuase we ORDER BY Financial.Year, the 1st duplicate
							// has the latest Year.

							// So do nothing

							rs.MoveNext( );
							continue;
						}

						iPersonID = rs.m_PersonID;



						iEndMonthAgeGroup = CCalculate::GroupAge(
											CCalculate::YearDiff(rs.m_dobDAY,
													 rs.m_dobMONTH,
													 rs.m_dobYEAR,
													 iCalcAgeD,
													 iCalcAgeM,
													 iCalcAgeY),
											strAgeCategory,
											&prop);

						iTodayAgeGroup = CCalculate::GroupAge(
											CCalculate::YearDiff(rs.m_dobDAY,
													 rs.m_dobMONTH,
													 rs.m_dobYEAR,
													 today.GetDay( ),
													 today.GetMonth( ),
													 today.GetYear( )),
											strAgeCategory,
											&prop);

						if(iFinancial)
						{
							COleDateTime someday;

							if( iOptFinancial == 1 )	// current in year today.Year
							{
								someday = today;
							}

							if( iOptFinancial == 3 )	// current in year iOptFinancialYear
							{
								int dMonth = today.GetMonth( );

								if( (rs.m_MonthStart > 0) && (rs.m_MonthStart < 13) )
								{
									dMonth = rs.m_MonthStart;
								}
								someday.SetDateTime( iOptFinancialYear, dMonth, 1, 1, 1, 1 );
							}

							if( (iOptFinancial == 1) || (iOptFinancial == 3) )	
							{
								if( 1 != CCalculate::Current( someday, rs.m_Year, rs.m_MonthStart, rs.m_MonthStop) )
								{
									// This occurance of the Person is not financial,
									// but there might be another occurance of the same
									// person who is. So don't display, but flag person
									// for display on next iteraion
									iPersonID = 0;
									rs.MoveNext( );
									continue;
								}
							}


						}

						if(iAgeGroup)
						{
							if( iTodayAgeGroup != iOptAgeGroup )
							{
								rs.MoveNext( );
								continue;
							}
						}



						if( iDisPersonID )
							strColumn->Add( _T(CConvert::itoa(rs.m_PersonID) ));
						if( iDisLastName )
							strColumn->Add( _T(rs.m_LastName));
						if( iDisFirstName )
							strColumn->Add( _T(rs.m_FirstName));
						if( iDisMiddleName )
							strColumn->Add( _T(rs.m_MiddleName));
						if( iDisAgeGroup )
							strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(iTodayAgeGroup) ));
						if( iDisDOB )
							strColumn->Add( _T( CFormat::FormatDate(rs.m_dobDAY, rs.m_dobMONTH,rs.m_dobYEAR)) );
						if( iDisAddress )
						{
							strColumn->Add( _T(rs.m_Address1) );
							strColumn->Add( _T(rs.m_Address2) );
						}
						if( iDisTown )
							strColumn->Add( _T(rs.m_Town) );
						if( iDisState )
							strColumn->Add( _T(rs.m_State) );
						if( iDisPostCode )
							strColumn->Add( _T(rs.m_PostCode) );
						if( iDisCountry )
							strColumn->Add( _T(rs.m_Country) );
						if( iDisPhoneHm )
							strColumn->Add( _T(rs.m_PhoneHm) );
						if( iDisPhoneWk )
							strColumn->Add( _T(rs.m_PhoneWk) );
						if( iDisFax )
							strColumn->Add( _T(rs.m_Fax) );
						if( iDisMobile )
							strColumn->Add( _T(rs.m_Mobile) );
						if( iDisEmail )
							strColumn->Add( _T(rs.m_email) );
						if( iDisContactPersonID )
							strColumn->Add( _T(CConvert::itoa(rs.m_ContactPersonID) ));
							
						if(iFinancial || iMailList || iOrganisation || iRegistrationType)
						{
							if( iDisDateRenewed )
								strColumn->Add( _T( CFormat::FormatDate(rs.m_DateRenewedDAY, rs.m_DateRenewedMONTH,rs.m_DateRenewedYEAR)) );
							if( iDisYear )
								strColumn->Add( _T( CConvert::itoa(rs.m_Year)) );
							if( iDisRegistrationID )
								strColumn->Add( _T( CConvert::itoa(rs.m_RegistrationID)) );
							if( iDisRegistrationTypeID )
							{
								strColumn->Add( _T( rs.m_RegistrationDescription ) );
							}
							if(iDisMonthStartStop)		
								strColumn->Add( _T( CFormat::FormatRegistration( rs.m_Year, rs.m_MonthStart, rs.m_MonthStop, "") ) );

							if( iDisMailListFlag )
							{
								switch( rs.m_MailListFlag )
								{
								case 1 : strMsg.Format("Yes"); break;
								case 0 : strMsg.Format("No"); break;
								}
								strColumn->Add( _T( strMsg ) );
							}
							if( iDisOrgName )
							{
								strColumn->Add( _T( rs.m_OrgName ) );
							}
						}
						if( iComments )
						{
							if( iDisComments )
							{
								strColumn->Add( _T( rs.m_Comments_Comment ) );
							}
						}

						html.HtmlTable(strColumn);

						strColumn->RemoveAll( );



						rs.MoveNext( );
					}

					strColumn->FreeExtra( );
					delete strColumn;

					html.EndForm();
				}
				else
				{
					html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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
			html << _T("No Filters Selected<BR>\r\n");
		}
		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ReportsFinancialHistoryForm(CHttpServerContext* pCtxt,
												   LPTSTR szPersonID,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::Financial) )
	{
		CString strPersonID;

		if( !_tcscmp(szPersonID, "none" ) )
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

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

			CPersonFinancialSet rs( &db );



			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_FINANCIALHISTORY);

			strSQL.Format(strSQLtmp, _T(strPersonID));

			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html.StartForm("Financial History", CPage::ReportsFinancialHistoryExecute);

				html.HiddenText("PersonID", strPersonID);

				html.NonEditText("Name", rs.m_LastName + ", " + rs.m_FirstName);				
				html.HorizontalRule();

				CReportFinancialHistoryOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsFinancialHistoryExecute(CHttpServerContext* pCtxt,
											   LPTSTR szPersonID,
											   LPTSTR szOption,
											   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::Financial) )
	{
		CString strPersonID;

		if( !_tcscmp(szPersonID, "none" ) )
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisDateRenewed				= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayDateRenewed);
		int iDisYear					= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayYear);
		int iDisRegistrationID			= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayRegistrationID);
		int iDisRegistrationDescription	= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayRegistrationDescription);
		int iDisMonthStopStart			= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayMonthStopStart);
		int iDisMailListFlag			= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayMailListFlag);
		int iDisOrgName					= CReportFinancialHistoryOption::IsMember( dwOption, CReportFinancialHistoryOption::DisplayOrgName);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CPersonFinancialSet rs( &db );



			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_FINANCIALHISTORY);

			strSQL.Format(strSQLtmp, _T(strPersonID));

			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Financial History For: ");

				strTitle = strTitle + CConvert::itoa(rs.m_PersonID) + " " + rs.m_FirstName + " " + rs.m_LastName;

				html.StartForm(strTitle, "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if(iDisDateRenewed)				strColumn->Add( "Renewal Date" );
				if(iDisYear)					strColumn->Add( "Year Valid" );
				if(iDisRegistrationID)			strColumn->Add( "Registration ID" );
				if(iDisRegistrationDescription)	strColumn->Add( "Registration Type" );
				if(iDisMonthStopStart)			strColumn->Add( "Registration Range" );
				if(iDisMailListFlag)			strColumn->Add( "Mail List" );
				if(iDisOrgName)					strColumn->Add( "Organisation" );


				if( strColumn->GetSize( ) )
				{

					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					CString strMsg;

					strColumn->RemoveAll( );

					while( !rs.IsEOF( ) )
					{

						if(iDisDateRenewed)	
							strColumn->Add( _T( CFormat::FormatDate(rs.m_DateRenewedDAY, rs.m_DateRenewedMONTH,rs.m_DateRenewedYEAR)) );

						if(iDisYear)			
							strColumn->Add( _T( CConvert::itoa(rs.m_Year)) );

						if(iDisRegistrationID)	
							strColumn->Add( _T( CConvert::itoa(rs.m_RegistrationID)) );

						if(iDisRegistrationDescription)	
							strColumn->Add( _T( rs.m_RegistrationDescription ) );

						if(iDisMonthStopStart)		
							strColumn->Add( _T( CFormat::FormatRegistration( rs.m_Year, rs.m_MonthStart, rs.m_MonthStop, "") ) );

						if(iDisMailListFlag)		
						{
							switch( rs.m_MailListFlag )
							{
							case 1 : strMsg.Format("Yes"); break;
							case 0 : strMsg.Format("No"); break;
							}
							strColumn->Add( _T( strMsg ) );
						}

						if(iDisOrgName)				
							strColumn->Add( _T( rs.m_OrgName ) );

						html.HtmlTable(strColumn);

						rs.MoveNext( );

						strColumn->RemoveAll( );
					}
				}

				strColumn->FreeExtra( );
				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsRulesExecute(CHttpServerContext* pCtxt,
									LPTSTR szSeriesID,
									LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

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


//			if(rsSeries.m_Handicapped)
//			{
				CString strTitle;
				strTitle.Format("Rules: ");

				strTitle = strTitle + rsSeries.m_SeriesDescription;

				html.StartForm( strTitle, "");


				strSQL.Format( "SELECT * FROM RuleType ORDER BY RuleTypeDescription");
				CRuleTypeSet rsRuleType( &db );
				rsRuleType.Open(CRecordset::dynaset, strSQL );

				CStringArray* strColumn;
				strColumn = new CStringArray;

				while( !rsRuleType.IsEOF( ) )
				{

					strSQL.Format( "SELECT COUNT(*) AS Total FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d ", szSeriesID, rsRuleType.m_RuleTypeID);
					CCountResultSet rsCount( &db );
					rsCount.Open(CRecordset::dynaset, strSQL );

					strSQL.Format( "SELECT MAX(Law) AS Total FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d ", szSeriesID, rsRuleType.m_RuleTypeID);
					CCountResultSet rsMax( &db );
					rsMax.Open(CRecordset::dynaset, strSQL );

					strSQL.Format( "SELECT * FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d ORDER BY Law", szSeriesID, rsRuleType.m_RuleTypeID);
					CRulesSet rsRules( &db );
					rsRules.Open(CRecordset::dynaset, strSQL );

					if( !rsRules.IsEOF( ) )
					{

						int iSubRuleMax = 0;
						int iSubRuleCount = 0;
						CString strSubRuleCount;

						strColumn->Add( "" );
						strColumn->Add( "" );
						strColumn->Add( "Rule" );
						strColumn->Add( "" );
						strColumn->Add( "" );


						html.EmptyHorizontalRule( strColumn->GetSize( ) );
						html.HeadingHRule( strColumn->GetSize( ), (CConvert::itoa(rsCount.m_Total) + " " + rsRuleType.m_RuleTypeDescription + " Rules") );

						html.HtmlTable(strColumn);
						html.HorizontalRule( strColumn->GetSize( ) );

						strColumn->RemoveAll( );


						while( !rsRules.IsEOF( ) )
						{
							strSQL.Format( "SELECT * FROM RuleSubType WHERE RuleTypeID = %d AND RuleSubTypeID = %d ORDER BY RuleSubTypeDescription", rsRuleType.m_RuleTypeID, rsRules.m_RuleSubTypeID);
							CRuleSubTypeSet rsRuleSubType( &db );
							rsRuleSubType.Open(CRecordset::dynaset, strSQL );


							// If the previous SubRule has not changed, 
							//    then either increment or decrement depending on the RuleSubType
							//
							if( !_tcscmp( rsRuleSubType.m_RuleSubTypeDescription, strSubRuleCount ) )
							{
								if( !_tcscmp( strSubRuleCount, CRuleSubType::GetName(CRuleSubType::RegroupEventsBelowPercentile) ) ||
									!_tcscmp( strSubRuleCount, CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted    ) ) )
								{
									iSubRuleCount--;
								}
								else
								{
									iSubRuleCount++;
									iSubRuleMax = iSubRuleCount;
								}
							}
							// If it has changed, and it is a RuleSubType that needs to be decremented
							//    then get the count of that RuleSubType
							//
							else if( !_tcscmp( rsRuleSubType.m_RuleSubTypeDescription, CRuleSubType::GetName(CRuleSubType::RegroupEventsBelowPercentile) ) ||
								     !_tcscmp( rsRuleSubType.m_RuleSubTypeDescription, CRuleSubType::GetName(CRuleSubType::EligibilityEventsCompleted    ) ) )
							{
								strSQL.Format( "SELECT COUNT(*) AS Total FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d AND RuleSubTypeID = %d ", szSeriesID, rsRuleType.m_RuleTypeID, rsRules.m_RuleSubTypeID);
								CCountResultSet rsCountEventBelow( &db );
								rsCountEventBelow.Open(CRecordset::dynaset, strSQL );

								strSubRuleCount.Format(rsRuleSubType.m_RuleSubTypeDescription);
								iSubRuleCount = rsCountEventBelow.m_Total;

								rsCountEventBelow.Close( );

								iSubRuleMax = iSubRuleCount;
							}
							// If it has changed, and it is a RuleSubType that needs to be incremented
							//    then set the count to 1
							//
							else
							{
								strSubRuleCount.Format(rsRuleSubType.m_RuleSubTypeDescription);
								iSubRuleCount = 1;

								iSubRuleMax = iSubRuleCount;
							}


							if( !rsRuleSubType.IsEOF( ) )
							{
								if( !_tcscmp( rsRuleType.m_RuleTypeDescription, CRuleType::GetName(CRuleType::Regroup)) 	)
								{
									strColumn->Add( "" );
									strColumn->Add( CConvert::itoa(iSubRuleCount) );
									strColumn->Add( rsRuleSubType.m_RuleSubTypeDescription );
									strColumn->Add( CConvert::itoa(rsRules.m_Law) );
									strColumn->Add( "" );
								}
								else if( !_tcscmp( rsRuleType.m_RuleTypeDescription, CRuleType::GetName(CRuleType::Eligibility)) )
								{
									// new rule message (count down)
									//
									if( iSubRuleMax == iSubRuleCount )
									{
										strColumn->Add( "" );
										strColumn->Add( CConvert::itoa(0) );
										strColumn->Add( " of last " + CConvert::itoa(rsMax.m_Total) + " Events Participated" );
										strColumn->Add( CConvert::itoa(iSubRuleCount) );
										strColumn->Add( "More Needed" );

										iSubRuleCount--;

										html.HtmlTable(strColumn);
										strColumn->RemoveAll( );
									}

									strColumn->Add( "Less than" );
									strColumn->Add( CConvert::itoa(rsRules.m_Law) );
									strColumn->Add( " of last " + CConvert::itoa(rsMax.m_Total) + " Events Participated" );
									strColumn->Add( CConvert::itoa(iSubRuleCount) );
									strColumn->Add( "More Needed" );
									

									// comment out the 2 lines above :
									// !_tcscmp( ... , ... CRuleSubType::EligibilityEventsCompleted )
									// to show the old rule.

									// old rule message (count up)
									//
									//strColumn->Add( "" );
									//strColumn->Add( CConvert::itoa(rsRules.m_Law) );
									//strColumn->Add( " of last " + CConvert::itoa(rsMax.m_Total) + " " + rsRuleSubType.m_RuleSubTypeDescription );
									//strColumn->Add( CConvert::itoa(iSubRuleCount) );
									//strColumn->Add( "More Needed" );
								}
								else if( !_tcscmp( rsRuleType.m_RuleTypeDescription, CRuleType::GetName(CRuleType::Processing)) )
								{
									strColumn->Add( "" );
									strColumn->Add( "" );
									strColumn->Add( rsRuleSubType.m_RuleSubTypeDescription );
									strColumn->Add( "" );
									strColumn->Add( "" );
								}
								else
								{
									strColumn->Add( "" );
									strColumn->Add( "" );
									strColumn->Add( rsRuleSubType.m_RuleSubTypeDescription );
									strColumn->Add( CConvert::itoa(rsRules.m_Law) );
									strColumn->Add( "" );
								}
							}
							else
							{
								strColumn->Add( "" );
								strColumn->Add( "" );
								strColumn->Add( "Incomplete Rule" );
								strColumn->Add( CConvert::itoa(rsRules.m_Law) );
								strColumn->Add( "" );
							}

							html.HtmlTable(strColumn);
							strColumn->RemoveAll( );

							rsRules.MoveNext( );

							rsRuleSubType.Close( );

						}

					}
					rsMax.Close( );
					rsCount.Close( );
					rsRules.Close( );
					rsRuleType.MoveNext( );
				}

				html.EndForm();

				delete strColumn;

				rsRuleType.Close( );
//			}
//			else
//			{
//				html << _T("This Series is not Handicapped.  Handicapping Rules have no effect.");
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

void CWebAthlExtension::ReportsAwardsForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsAwardsExecute;

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

			CSeriesSet rsSeries( &db );

			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select a Series\r\n");

				html.StartForm("Awards", auth.m_strFrwdLink);

				html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
				html.HorizontalRule();

				html.EditIntBox("Minimum Number of Events", "EventsMin", 1);
//				html.NonEditText("Note:", "</strong><em><small>For a Consistency Report, the Minimum</small></em><strong>");
//				html.NonEditText("",      "</strong><em><small>Events is filtered on 'Consistency</small></em><strong>");
//				html.NonEditText("",      "</strong><em><small>Events Current', while a Pointscore</small></em><strong>");
//				html.NonEditText("",      "</strong><em><small>Report is filtered on 'Events For Season'</small></em><strong>");
				html.HorizontalRule();

				html.CheckBox("Order By", "Organisation", "Organisation", "1", "0");
				html.CheckBox("", "Division", "Division", "1", "0");
				html.CheckBox("", "Sex",		"Sex",		"1", "0");
				html.CheckBox("", "AgeGroup", "AgeGroup", "1", "0");
				html.HorizontalRule();

				html.RadioButton("", "Consistency Events Rate","OrderBy",	"0", "0");
				html.RadioButton("", "Consistency Age Standard", "OrderBy",	"2", "0");
				html.RadioButton("", "Net Points", "OrderBy",	"1", "0");
				html.RadioButton("", "Ascending", "Desc",	"0", "0");
				html.RadioButton("", "Descending","Desc",	"1", "0");
				html.HorizontalRule();

				CReportAwardsOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsAwardsExecute(CHttpServerContext* pCtxt,
									 LPTSTR szSeriesID,
									 LPTSTR szEventsMin,
									 LPTSTR szOrganisation,
									 LPTSTR szDivision,
									 LPTSTR szSex,
									 LPTSTR szAgeGroup,
									 LPTSTR szOrderBy,
									 LPTSTR szDesc,
									 LPTSTR szOption,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iOrganisation	= atoi(szOrganisation);
		int iDivision		= atoi(szDivision);
		int iSex			= atoi(szSex);
		int iAgeGroup		= atoi(szAgeGroup);
		int iOrderBy		= atoi(szOrderBy);
		int iDesc			= atoi(szDesc);

		int iDisPersonID					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayPersonID);
		int iDisLastName					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayLastName);
		int iDisFirstName					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayFirstName);
		int iDisSexAgeGroup					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplaySexAgeGroup);
		int iDisDivisionSupposedTo			= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayDivisionSupposedTo);
		int iDisGroupIDSupposedTo			= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayGroupIDSupposedTo);
		int iDisEventsForSeason				= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayEventsForSeason);
		int iDisEventsForSeries				= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayEventsForSeries);
		int iDisConsistencyAgeGroup			= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayConsistencyAgeGroup);
		int iDisConsistencyEventsCurrent	= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayConsistencyEventsCurrent);
		int iDisConsistencyEventsOlder		= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayConsistencyEventsOlder);
		int iDisConsistencyEventsRate		= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayConsistencyEventsRate);
		int iDisConsistencyAgeStandard		= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayConsistencyAgeStandard);
		int iDisGrossPoints					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayGrossPoints);
		int iDisNetPoints					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayNetPoints);
		int iDisLowPoints					= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayLowPoints);
		int iDisEligibilityForEvent			= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayEligibilityForEvent);
		int iDisOrgName						= CReportAwardsOption::IsMember( dwOption, CReportAwardsOption::DisplayOrgName);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CSeriesPersonPFSOrgSet rs( &db );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_AWARDS);
			strSQL.Format(strSQLtmp,
				_T(szSeriesID));


			//if( iOrderBy == 0 )	// Rate
			//{
			//	strSQL += _T( " AND (ParticipantForSeries.ConsistencyEventsCurrent > 0 ) " );
			//	strSQL += _T( " AND (ParticipantForSeries.ConsistencyEventsCurrent >= " );
			//	strSQL += _T( szEventsMin );
			//	strSQL += _T( " ) " );
			//}
			//else if( iOrderBy == 1 ) // Net Points
			//{
				strSQL += _T( " AND (ParticipantForSeries.EventsForSeason > 0 ) " );
				strSQL += _T( " AND (ParticipantForSeries.EventsForSeason >= " );
				strSQL += _T( szEventsMin );
				strSQL += _T( " ) " );
			//}


			// ORDER BY clause :
			strSQL += _T( " ORDER BY " );

			if(iOrganisation)
				strSQL += _T( " Organisation.OrgName , " );
			if(iDivision)
				strSQL += _T( " ParticipantForSeries.DivisionSupposedTo , " );
			if(iSex)
				strSQL += _T( " Person.Sex , " );
			if(iAgeGroup)
				strSQL += _T( " ParticipantForSeries.ConsistencyAgeGroup , " );

			if( iOrderBy == 0 )	// Consistency Events Rate
			{
				if(iDesc)
					strSQL += _T( " ParticipantForSeries.ConsistencyEventsRate DESC " );
				else
					strSQL += _T( " ParticipantForSeries.ConsistencyEventsRate ASC " );
			}
			else if( iOrderBy == 1 ) // Net Points
			{
				if(iDesc)
					strSQL += _T( " ParticipantForSeries.NetPoints DESC " );
				else
					strSQL += _T( " ParticipantForSeries.NetPoints ASC " );
			}
			else if( iOrderBy == 2 ) // Consistency Age Standard
			{
				if(iDesc)
					strSQL += _T( " ParticipantForSeries.ConsistencyAgeStandard DESC " );
				else
					strSQL += _T( " ParticipantForSeries.ConsistencyAgeStandard ASC " );
			}

			//html << _T( strSQL );

			rs.Open(CRecordset::forwardOnly, strSQL );

			CString strAgeCategory;
			int iAgeGroup;
			COleDateTime t = COleDateTime::GetCurrentTime();

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Awards: ");

				strTitle = strTitle + rs.m_SeriesDescription;

				html.StartForm(strTitle, "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				if( iDisPersonID )
					strColumn->Add( "PersonID" );
				if( iDisLastName )
					strColumn->Add( "LastName" );
				if( iDisFirstName )
					strColumn->Add( "FirstName" );
				if( iDisSexAgeGroup )
					strColumn->Add( "AgeGroup" );
				if( iDisDivisionSupposedTo )
					strColumn->Add( "Division" );
				if( iDisGroupIDSupposedTo )
					strColumn->Add( "Group" );
				if( iDisEventsForSeason )
					strColumn->Add( "SeasonEvents" );
				if( iDisEventsForSeries )
					strColumn->Add( "SeriesEvents" );
				if( iDisConsistencyAgeGroup )
					strColumn->Add( "AgeGroup" );
				if( iDisConsistencyEventsCurrent )
					strColumn->Add( "EventsCurrent" );
				if( iDisConsistencyEventsOlder )
					strColumn->Add( "EventsOlder" );
				if( iDisConsistencyEventsRate )
					strColumn->Add( "Rate" );
				if( iDisConsistencyAgeStandard )
					strColumn->Add( "AgeStandard" );
				if( iDisGrossPoints	)
					strColumn->Add( "GrossPoints" );
				if( iDisNetPoints )
					strColumn->Add( "NetPoints" );
				if( iDisLowPoints )
					strColumn->Add( "LowPoints" );
				if( iDisEligibilityForEvent )
					strColumn->Add( "Eligibility" );
				if( iDisOrgName )
					strColumn->Add( "Organisation" );

				if( strColumn->GetSize( ) )
				{

					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					while( !rs.IsEOF( ) )
					{
						iAgeGroup = CCalculate::GroupAge(
											CCalculate::YearDiff(rs.m_dobDAY,
													 rs.m_dobMONTH,
													 rs.m_dobYEAR,
													 t.GetDay( ),
													 t.GetMonth( ),
													 t.GetYear( )),
											strAgeCategory,
											&prop);

						if( iDisPersonID )
							strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );

						if( iDisLastName )
							strColumn->Add( _T(rs.m_LastName) );

						if( iDisFirstName )
							strColumn->Add( _T(rs.m_FirstName) );

						if( iDisSexAgeGroup )
							strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(iAgeGroup)) );

						if( iDisDivisionSupposedTo )
							strColumn->Add( _T(CConvert::itoa(rs.m_DivisionSupposedTo)) );

						if( iDisGroupIDSupposedTo )
							strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDSupposedTo)) );

						if( iDisEventsForSeason )
							strColumn->Add( _T(CConvert::itoa(rs.m_EventsForSeason)) );

						if( iDisEventsForSeries )
							strColumn->Add( _T(CConvert::itoa(rs.m_EventsForSeries)) );

						if( iDisConsistencyAgeGroup )
							strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(rs.m_ConsistencyAgeGroup)) );

						if( iDisConsistencyEventsCurrent )
							strColumn->Add( _T(CConvert::itoa(rs.m_ConsistencyEventsCurrent)) );

						if( iDisConsistencyEventsOlder )
							strColumn->Add( _T(CConvert::itoa(rs.m_ConsistencyEventsOlder)) );

						if( iDisConsistencyEventsRate )
							strColumn->Add( _T(CConvert::dtoa(rs.m_ConsistencyEventsRate)) );

						if( iDisConsistencyAgeStandard )
							strColumn->Add( _T(CConvert::dtoa(rs.m_ConsistencyAgeStandard)) );

						if( iDisGrossPoints	)
							strColumn->Add( _T(CConvert::itoa(rs.m_GrossPoints)) );

						if( iDisNetPoints )
							strColumn->Add( _T(CConvert::itoa(rs.m_NetPoints)) );

						if( iDisLowPoints )
							strColumn->Add( _T(CConvert::itoa(rs.m_LowPoints)) );

						if( iDisEligibilityForEvent )
							strColumn->Add( _T(rs.m_EligibilityForEvent) );

						if( iDisOrgName )
							strColumn->Add( _T(rs.m_OrgName) );






						html.HtmlTable(strColumn);

						rs.MoveNext( );

						strColumn->RemoveAll( );

					}
				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsCustomForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		html << _T("Enter an SQL SELECT query to generate your custom report.<BR>\r\n");

		html.StartForm("Custom Report Query", CPage::ReportsCustomExecute);

		html.HorizontalRule();
		html.TextArea("SQL Query", "CustomQuery", 10, 50);

		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Run);

		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ReportsCustomExecute(CHttpServerContext* pCtxt,
									 LPTSTR szCustomQuery,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CRecordsetEx rs( &db );
			strSQLtmp = szCustomQuery;

			strSQL = strSQLtmp.SpanExcluding(";");

			rs.Open(CRecordset::forwardOnly, strSQL );


			if( !rs.IsEOF( ) )
			{
				CString str;

				CStringArray* strColumnNames;
				CStringArray* strRow;
				strRow = new CStringArray;


				strColumnNames = rs.GetColumnNames( );
				str = rs.GetTableName( );

				if( str.IsEmpty( ) )
				{
					str.Format("Custom Query" );
				}
				else
				{
					str.Format("Custom Query : %s", rs.GetTableName( ) );
				}

				html.StartForm(str, "");

				html.HtmlTable(strColumnNames);
				html.HorizontalRule( strColumnNames->GetSize( ) );


				while( !rs.IsEOF( ) )
				{
					html.HtmlTable(rs.GetRow( strRow ));
					rs.MoveNext( );
				}

				str.Format( "(<B>%d</B> row(s) fetched)", rs.GetRecordCount( ) );

				strRow->RemoveAll( );
				strRow->Add( _T( str ) );
				html.HtmlTable(strRow);
				strRow->RemoveAll( );

				strRow->FreeExtra( );
				delete strRow;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsAgeGroupRankingForm(CHttpServerContext* pCtxt,
												   LPTSTR szSeriesID,
												   LPTSTR szLocationID,
												   LPTSTR szEventTypeID,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsAgeGroupRankingExecute;

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

			int iSeriesID =  atoi(szSeriesID);
			int iLocationID = atoi(szLocationID);
			int iEventTypeID = atoi(szEventTypeID);

			CSeriesSet rsSeries( &db );
			if( iSeriesID )
				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %d", iSeriesID );
			else
				strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );

			rsSeries.Open(CRecordset::dynaset, strSQL );

			CLocationSet rsLoc( &db );
			if( iSeriesID && iLocationID )
				strSQL.Format( "SELECT * FROM Location WHERE LocationID = %d", iLocationID );
			else
				strSQL.Format( "SELECT DISTINCT Location.* FROM Location , Event WHERE Event.LocationID = Location.LocationID AND Event.SeriesID = %d ORDER BY LocationDescription", iSeriesID );
			rsLoc.Open(CRecordset::dynaset, strSQL );

			CEventTypeSet rsEvntTyp( &db );
			if( iSeriesID && iLocationID && iEventTypeID )
				strSQL.Format( "SELECT * FROM EventType WHERE EventTypeID = %d", iEventTypeID );
			else
				strSQL.Format( "SELECT DISTINCT EventType.* FROM EventType , Event , Location WHERE Event.EventTypeID = EventType.EventTypeID AND Event.LocationID = Location.LocationID AND Event.SeriesID = %d AND Location.LocationID = %d ORDER BY EventDescription", iSeriesID, iLocationID );



			rsEvntTyp.Open(CRecordset::dynaset, strSQL );

			if( ( !rsSeries.IsEOF( )  && !iSeriesID && !iLocationID && !iEventTypeID ) ||
				( !rsLoc.IsEOF( )     &&  iSeriesID && !iLocationID && !iEventTypeID ) || 
				( !rsEvntTyp.IsEOF( ) &&  iSeriesID &&  iLocationID && !iEventTypeID ) ||
				(                         iSeriesID &&  iLocationID &&  iEventTypeID ) )
			{
				html << _T("Select a Series, Location and Event Type\r\n");

				if( iSeriesID && iLocationID )
					html.StartForm("Age Group Ranking", auth.m_strFrwdLink);
				else
					html.StartForm("Age Group Ranking", CPage::ReportsAgeGroupRankingForm);
				
				if( iSeriesID )
				{
					html.HiddenInt("SeriesID", iSeriesID);
					html.NonEditText("Series", rsSeries.m_SeriesDescription);
				}
				else
				{
					html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
				}

				if( iSeriesID )
				{
					if( iLocationID )
					{
						html.HiddenInt("LocationID", iLocationID);
						html.NonEditText("Location", rsLoc.m_LocationDescription);
					}
					else
					{
						html.StartSelectBox("Location", "LocationID");
						while( !rsLoc.IsEOF( ) )
						{
							html.AddSelectBox(rsLoc.m_LocationDescription, CConvert::itoa(rsLoc.m_LocationID), "");
							rsLoc.MoveNext( );
						}
						html.EndSelectBox();
					}
				}
				else
				{
					html.HiddenInt("LocationID", 0);
					//html.NonEditText("Location", "");
				}

				if( iSeriesID && iLocationID )
				{
					if( iEventTypeID )
					{
						html.HiddenInt("EventTypeID", iEventTypeID);
						html.NonEditText("Event Type", rsEvntTyp.m_EventDescription);
					}
					else
					{
						html.StartSelectBox("Event Type", "EventTypeID");
						while( !rsEvntTyp.IsEOF( ) )
						{
							html.AddSelectBox(rsEvntTyp.m_EventDescription, CConvert::itoa(rsEvntTyp.m_EventTypeID), "");
							rsEvntTyp.MoveNext( );
						}
						html.EndSelectBox();
					}
				}
				else
				{
					html.HiddenInt("EventTypeID", 0);
					//html.NonEditText("Event Type", "");
				}
				
				html.HorizontalRule();

				if( iSeriesID && iLocationID )
					html.SubmitButton(CHtmlKey::Run);
				else
					html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Series, Locations or Event Types Available\r\n");
			}
			rsEvntTyp.Close( );
			rsLoc.Close( );
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

void CWebAthlExtension::ReportsAgeGroupRankingExecute(CHttpServerContext* pCtxt,
													 LPTSTR szSeriesID,
													 LPTSTR szLocationID,
													 LPTSTR szEventTypeID,
													 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CAgeGroupRankingSet rs( &db );
			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_AGEGROUPRANKING);
			strSQL.Format(strSQLtmp, _T(szSeriesID), _T(szLocationID), _T(szEventTypeID) );
			
			rs.Open(CRecordset::forwardOnly, strSQL );

			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Age Group Ranking");

				html.StartForm(strTitle, "");

				html.NonEditText("Series", rs.m_SeriesDescription );
				html.NonEditText("Location", rs.m_LocationDescription );
				html.NonEditText("Event Type", rs.m_EventDescription );

				html.EndForm();


				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				strColumn->Add( "Rank" );
				strColumn->Add( "EventNo" );
				strColumn->Add( "Date" );
				strColumn->Add( "AgeGroup" );
				strColumn->Add( "PersonID" );
				strColumn->Add( "LastName" );
				strColumn->Add( "FirstName" );
				strColumn->Add( "NetPerformance" );

				html.HtmlTable(strColumn);

				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );


				int nCurrentAgeGroup = 0;

				// maps key-value pairs.
				// this map, maps an int key to an int value.
				CMap<int,int,int,int> map;

				int nCurrentPersonCount = 0;

				int nRank = 0;

				while( !rs.IsEOF( ) )
				{
					if(nCurrentAgeGroup != rs.m_AgeGroup)
					{
						nCurrentAgeGroup = rs.m_AgeGroup;
						map.RemoveAll( );

						nRank = 0;
					}

					if( map.Lookup( rs.m_PersonID, nCurrentPersonCount ) )
					{
						// person in the map
						map.SetAt( rs.m_PersonID, nCurrentPersonCount++ );
					}
					else
					{
						// new person (not in the map)
						map.SetAt( rs.m_PersonID, 1 );


						strColumn->Add( CConvert::itoa(++nRank) );

						strColumn->Add( CConvert::itoa(rs.m_EventNo) );

						strColumn->Add( _T( CFormat::FormatDate(rs.m_DateDAY, rs.m_DateMONTH, rs.m_DateYEAR)) );

						strColumn->Add( rs.m_Sex + CConvert::itoa(rs.m_AgeGroup) );
						strColumn->Add( CConvert::itoa(rs.m_PersonID) );
						strColumn->Add( rs.m_LastName );
						strColumn->Add( rs.m_FirstName );

						strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
												   rs.m_NetPerformanceHOUR, 
												   rs.m_NetPerformanceMIN,
												   rs.m_NetPerformanceSEC) ));

						html.HtmlTable(strColumn);

						strColumn->RemoveAll( );
					}

					rs.MoveNext( );
				}

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsSeriesStatisticsForm(CHttpServerContext* pCtxt,
												   LPTSTR szSeriesID,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsSeriesStatisticsExecute;

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
				html << _T("Select a Lower and Upper Event bound to calculate statistics between\r\n");

				html.StartForm("Series Statistics", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", szSeriesID);

				html.SelectEventBox("Event From", "EventIDFrom", &rsEvent, -1, NULL);
				rsEvent.MoveFirst( );

				html.SelectEventBox("Event To", "EventIDTo", &rsEvent, -1, NULL);

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsSeriesStatisticsExecute(CHttpServerContext* pCtxt,
													 LPTSTR szSeriesID,
													 LPTSTR szEventIDFrom,
													 LPTSTR szEventIDTo,
													 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CSeriesStatisticsSet rs( &db );
			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_SERIESSTATISTICS);
			strSQL.Format(strSQLtmp, _T(szSeriesID), _T(szEventIDFrom), _T(szEventIDTo) );
			rs.Open(CRecordset::forwardOnly, strSQL );


			if( !rs.IsEOF( ) )
			{
				CString strTitle;
				strTitle.Format("Series Statistics");

				html.StartForm(strTitle, "");


				CDatabase dbHeading;
				dbHeading.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CSeriesSet rsSeries( &dbHeading );
				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s ", szSeriesID );
				rsSeries.Open(CRecordset::forwardOnly, strSQL );
				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				rsSeries.Close( );


				CEventETypLocSet rsEvent( &dbHeading );

				strSQL.Format( html.GetNonEditEventBoxDetails(atoi(szEventIDFrom)) );
				rsEvent.Open(CRecordset::forwardOnly, strSQL );

				html.NonEditEvent("Event From", rsEvent.m_EventNo, 
					rsEvent.m_LocationDescription, rsEvent.m_EventDescription);
				html.NonEditDateBox("Date", 
					rsEvent.m_DateDAY, rsEvent.m_DateMONTH, rsEvent.m_DateYEAR);

				rsEvent.Close( );


				strSQL.Format( html.GetNonEditEventBoxDetails(atoi(szEventIDTo)) );
				rsEvent.Open(CRecordset::forwardOnly, strSQL );

				html.NonEditEvent("Event To", rsEvent.m_EventNo, 
					rsEvent.m_LocationDescription, rsEvent.m_EventDescription);
				html.NonEditDateBox("Date", 
					rsEvent.m_DateDAY, rsEvent.m_DateMONTH, rsEvent.m_DateYEAR);

				rsEvent.Close( );

				dbHeading.Close( );


				html.EndForm();



				html.StartForm("", "");

				CStringArray* strColumn;
				strColumn = new CStringArray;

				strColumn->Add( "AgeGroup" );
				strColumn->Add( "Men" );
				strColumn->Add( "Women" );
				strColumn->Add( "Total" );

				html.HtmlTable(strColumn, 1);

				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );


				int nCurrentAgeGroup = -1;

				// maps key-value pairs.
				// this map, maps a TCHAR key to an int value.
				CMap<TCHAR,TCHAR,int,int> mapAgeGroup;
				CMap<TCHAR,TCHAR,int,int> mapTotal;

				int nCurrentMenCount = 0;
				int nCurrentWomanCount = 0;
				int nCurrentTotalCount = 0;

				int nMenTotal = 0;
				int nWomanTotal = 0;
				int nTotalTotal = 0;

				while( !rs.IsEOF( ) )
				{
					if(nCurrentAgeGroup != rs.m_AgeGroup)
					{
						if( nCurrentAgeGroup > -1 )
						{
							// agegroup totals
							mapAgeGroup.Lookup( _T('M'), nCurrentMenCount );
							mapAgeGroup.Lookup( _T('W'), nCurrentWomanCount );

							nCurrentTotalCount = nCurrentMenCount + nCurrentWomanCount;

							strColumn->Add( CConvert::itoa(nCurrentAgeGroup) );
							strColumn->Add( CConvert::itoa(nCurrentMenCount) );
							strColumn->Add( CConvert::itoa(nCurrentWomanCount) );
							strColumn->Add( CConvert::itoa(nCurrentTotalCount) );

							html.HtmlTable(strColumn, 1);

							strColumn->RemoveAll( );


							// cumalative totals
							mapTotal.Lookup( _T('M'), nMenTotal );
							mapTotal.Lookup( _T('W'), nWomanTotal );

							nMenTotal += nCurrentMenCount;
							nWomanTotal += nCurrentWomanCount;

							mapTotal.SetAt( _T('M'), nMenTotal );
							mapTotal.SetAt( _T('W'), nWomanTotal );
						}

						nCurrentAgeGroup = rs.m_AgeGroup;
						mapAgeGroup.RemoveAll( );

						mapAgeGroup.SetAt( _T('M'), 0 );
						mapAgeGroup.SetAt( _T('W'), 0 );
					}

					mapAgeGroup.SetAt( rs.m_Sex.GetAt(0), rs.m_Total );

					rs.MoveNext( );
				}

				if( nCurrentAgeGroup > -1 )
				{
					// agegroup totals
					mapAgeGroup.Lookup( _T('M'), nCurrentMenCount );
					mapAgeGroup.Lookup( _T('W'), nCurrentWomanCount );

					nCurrentTotalCount = nCurrentMenCount + nCurrentWomanCount;

					strColumn->Add( CConvert::itoa(nCurrentAgeGroup) );
					strColumn->Add( CConvert::itoa(nCurrentMenCount) );
					strColumn->Add( CConvert::itoa(nCurrentWomanCount) );
					strColumn->Add( CConvert::itoa(nCurrentTotalCount) );

					html.HtmlTable(strColumn, 1);

					strColumn->RemoveAll( );


					// cumalative totals
					mapTotal.Lookup( _T('M'), nMenTotal );
					mapTotal.Lookup( _T('W'), nWomanTotal );

					nMenTotal += nCurrentMenCount;
					nWomanTotal += nCurrentWomanCount;

					mapTotal.SetAt( _T('M'), nMenTotal );
					mapTotal.SetAt( _T('W'), nWomanTotal );
				}


				if( mapTotal.Lookup( _T('M'), nMenTotal ) &&
					mapTotal.Lookup( _T('W'), nWomanTotal ) )
				{
					nTotalTotal = nMenTotal + nWomanTotal;

					strColumn->Add( "Totals" );
					strColumn->Add( CConvert::itoa(nMenTotal) );
					strColumn->Add( CConvert::itoa(nWomanTotal) );
					strColumn->Add( CConvert::itoa(nTotalTotal) );

					html.HorizontalRule(strColumn->GetSize( ) );
					html.HtmlTable(strColumn, 1);

					strColumn->RemoveAll( );

					double dMenPercent = 100.0 * ((double)nMenTotal / (double)nTotalTotal);
					double dWomanPercent = 100.0 * ((double)nWomanTotal / (double)nTotalTotal);
					double dTotalPercent = 100.0 * ((double)nTotalTotal / (double)nTotalTotal);

					strColumn->Add( "%" );
					strColumn->Add( CConvert::dtoa(dMenPercent, 1) );
					strColumn->Add( CConvert::dtoa(dWomanPercent, 1) );
					strColumn->Add( CConvert::dtoa(dTotalPercent, 1) );

					html.HtmlTable(strColumn, 1);

					strColumn->RemoveAll( );
				}

				mapAgeGroup.RemoveAll( );
				mapTotal.RemoveAll( );

				delete strColumn;

				html.EndForm();
			}
			else
			{
				html << _T(CRecordsetEx::m_szMsgEmptyRecordset);
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

void CWebAthlExtension::ReportsResultsBySeriesForm(CHttpServerContext* pCtxt,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::ReportsResultsBySeriesExecute;

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


			CSeriesSet rsSeries( &db );

			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select the Series' for Results.<BR>\r\n");

				html << _T("<BR>\r\n<B>Warning</B>: Be very selective of the Dates you choose and the Series you join as some combinations will generate very large lists.<BR>\r\n");

				html.StartForm("Results By Series", auth.m_strFrwdLink);
				
				html.NonEditText("Event Date", "");
				html.DateBox("From", "EventDateFrom");
				html.DateBox("To", "EventDateTo");
				html.HorizontalRule();

				if( !rsSeries.IsEOF( ) )
				{
					html.CheckBox("Series", 
						rsSeries.m_SeriesDescription, 
						"SeriesIDList", 
						CConvert::itoa(rsSeries.m_SeriesID), 
						CConvert::itoa(rsSeries.m_SeriesID));

					rsSeries.MoveNext( );
				}

				while( !rsSeries.IsEOF( ) )
				{
					html.CheckBox("", 
						rsSeries.m_SeriesDescription, 
						"SeriesIDList", 
						CConvert::itoa(rsSeries.m_SeriesID), 
						"0");

					rsSeries.MoveNext( );
				}

				html.HorizontalRule();

				html.RadioButton("Order By", 
								 "Overall-Place", 
								 "OrderByDivision", 
								 "0",
								 "0");

				html.RadioButton("", 
								 "Division", 
								 "OrderByDivision", 
								 "1",
								 "0");

				html.HorizontalRule();

				CReportResultsBySeriesOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(enumList.GetDefaultSelect()) );
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

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

void CWebAthlExtension::ReportsResultsBySeriesExecute(CHttpServerContext* pCtxt,
													  LPTSTR szEventDateFromDAY,
													  LPTSTR szEventDateFromMONTH,
													  LPTSTR szEventDateFromYEAR,
													  LPTSTR szEventDateToDAY,
													  LPTSTR szEventDateToMONTH,
													  LPTSTR szEventDateToYEAR,
													  LPTSTR szSeriesIDList,
													  LPTSTR szOrderByDivision,
													  LPTSTR szOption,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();


		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisSeriesDesc			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplaySeriesDesc);
		int iDisEventNo				= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayEventNo);
		int iDisLocationDesc		= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayLocationDesc);
		int iDisEventDesc			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayEventDesc);
		int iDisEventDate			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayEventDate);
		int iDisDivisionAct			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayDivisionAct);
		int iDisDivision			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayDivision);
		int iDisOverallPlace		= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayOverallPlace);
		int iDisPlace				= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayPlace);
		int iDisPersonID			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayPersonID);
		int iDisFirstName			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayFirstName);
		int iDisLastName			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayLastName);
		int iDisAgeGroup			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayAgeGroup);
		int iDisGroup				= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayGroup);
		int iDisGroupAct			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayGroupAct);
		int iDisGroupStart			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayGroupStart);
		int iDisGrossPerformance	= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayGrossPerformance);
		int iDisNetPerformance		= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayNetPerformance);
		int iDisEventRate			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayEventRate);
		int iDisGroupRate			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayGroupRate);
		int iDisWAVA				= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayWAVA);
		int iDisPoints				= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayPoints);
		int iDisPercentile			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayPercentile);
		int iDisEligible			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayEligible);
		int iDisNewGroupMsg			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayNewGroupMsg);
		int iDisNewGroup			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayNewGroup);
		int iDisOrganisation		= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayOrganisation);
		int iDisChestNumber			= CReportResultsBySeriesOption::IsMember( dwOption, CReportResultsBySeriesOption::DisplayChestNumber);


		COleDateTime dateEventFrom( 
			atoi(szEventDateFromYEAR),
			atoi(szEventDateFromMONTH),
			atoi(szEventDateFromDAY),
			0, 0, 0
		);

		COleDateTime dateEventTo( 
			atoi(szEventDateToYEAR),
			atoi(szEventDateToMONTH),
			atoi(szEventDateToDAY),
			0, 0, 0
		);

		if( dateEventFrom.GetStatus() == COleDateTime::valid && 
			dateEventTo.GetStatus()   == COleDateTime::valid    )
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strError;

			CString strSeriesIDList = szSeriesIDList;

			CStringArray* strItems = new CStringArray();

			CCSV csv(CWebAthlExtension::chIsapiDelimiter);
			csv.GetItems(strItems, &strSeriesIDList);


			// maps key-value pairs.
			// this map, maps an int key to an CPoint(int x, int y) value.
			CMap<int,int,CPoint,CPoint>* pMap;
			pMap = CUtil::FindEventsBetweenDates(strConnect, dateEventFrom, dateEventTo, strItems, &strError);


			if( pMap != NULL && pMap->GetStartPosition() != NULL )
			{

				try
				{
					//CString strConnect = prop.GetDefaultConnect();
					CString strSQLtmp;
					CString strSQL;

					CDatabase db;
					db.OpenEx( strConnect, CDatabase::noOdbcDialog );


					CResultsOrgSet rs( &db );

					CUtil::LoadLongResource(strSQL, IDS_SQL_RESULTSORG);


					CString strSQLBetween = _T(" ( Results.SeriesID = %d AND Event.EventNo BETWEEN %d AND %d ) ");


					POSITION pos = pMap->GetStartPosition();
					int nKeySeriesID;
					CPoint ptEventNo;

					int iORflag = 0;

					while( pos != NULL )
					{
						pMap->GetNextAssoc( pos, nKeySeriesID, ptEventNo );

						strSQLtmp.Format(strSQLBetween, 
							nKeySeriesID, ptEventNo.x, ptEventNo.y);

						if( !iORflag )
						{
							strSQL += " WHERE ";
							iORflag = 1;
						}
						else
						{
							strSQL += " OR ";
						}

						strSQL += strSQLtmp;
					}


					if(atoi(szOrderByDivision))
						strSQL += _T(" ORDER BY Series.SeriesDescription, Event.EventNo, Results.DivisionActual, Results.OverallPlace ");
					else
						strSQL += _T(" ORDER BY Series.SeriesDescription, Event.EventNo, Results.OverallPlace, Results.DivisionActual ");

					//html << _T(strSQL) << _T("<BR>\r\n");


					rs.Open(CRecordset::forwardOnly, strSQL );

					if( !rs.IsEOF( ) )
					{
						CString strTitle;
						strTitle.Format("Results By Series");


						CString* strRow = csv.GetCSVRow(strItems);

						CDatabase dbSeries;
						dbSeries.OpenEx( strConnect, CDatabase::noOdbcDialog );

						html.StartForm(strTitle, "");

						CString strEventBetween;

						strEventBetween.Format( _T("%s </strong>to<strong> %s"), 
							CFormat::FormatDate(
								atoi(szEventDateFromDAY),
								atoi(szEventDateFromMONTH),
								atoi(szEventDateFromYEAR)),
							CFormat::FormatDate(
								atoi(szEventDateToDAY),
								atoi(szEventDateToMONTH),
								atoi(szEventDateToYEAR)) );


						html.NonEditText("Event Date", strEventBetween);


						CSeriesSet rsSeries( &dbSeries );
						strSQL.Format("SELECT * FROM Series WHERE SeriesID IN ( %s ) ORDER BY SeriesDescription", *strRow);
						rsSeries.Open(CRecordset::forwardOnly, strSQL );

						while( !rsSeries.IsEOF( ) )
						{
							html.NonEditText("Series", rsSeries.m_SeriesDescription);

							if( pMap->Lookup( rsSeries.m_SeriesID , ptEventNo ) )
							{
								strEventBetween.Format( _T("%d </strong>to<strong> %d"), ptEventNo.x, ptEventNo.y);
								html.NonEditText("Event", strEventBetween);
							}

							rsSeries.MoveNext( );
						}

						rsSeries.Close( );

						html.EndForm();

						dbSeries.Close( );

						delete strRow;




						CString strNewGroupID;


						html.StartForm("", "");

						CStringArray* strColumn;
						strColumn = new CStringArray;

						if(iDisSeriesDesc)			strColumn->Add( "Series" );
						if(iDisEventNo)				strColumn->Add( "Event No" );
						if(iDisLocationDesc)		strColumn->Add( "Location" );
						if(iDisEventDesc)			strColumn->Add( "Event" );
						if(iDisEventDate)			strColumn->Add( "Date" );
						if(iDisDivisionAct)			strColumn->Add( "DivAct" );
						if(iDisDivision)			strColumn->Add( "Div" );
						if(iDisOverallPlace)		strColumn->Add( "OverallPlace" );
						if(iDisPlace)				strColumn->Add( "Place" );
						if(iDisPersonID)			strColumn->Add( "PersonID" );
						if(iDisFirstName)			strColumn->Add( "FistName" );
						if(iDisLastName)			strColumn->Add( "LastName" );
						if(iDisAgeGroup)			strColumn->Add( "AgeGroup" );
						if(iDisGroup)				strColumn->Add( "Group" );
						if(iDisGroupAct)			strColumn->Add( "GroupAct" );
						if(iDisGroupStart)			strColumn->Add( "GroupStart" );
						if(iDisGrossPerformance)	strColumn->Add( "GrossPerformance" ); 
						if(iDisNetPerformance)		strColumn->Add( "NetPerformance" );    
						if(iDisEventRate)			strColumn->Add( "EventRate" );
						if(iDisGroupRate)			strColumn->Add( "GroupRate" );
						if(iDisWAVA)				strColumn->Add( "AgeStandard" );
						if(iDisPoints)				strColumn->Add( "Points" );
						if(iDisPercentile)			strColumn->Add( "Percentile" );
						if(iDisEligible)			strColumn->Add( "Eligible" );
						if(iDisNewGroupMsg)			strColumn->Add( "Comment" );
						if(iDisNewGroup)			strColumn->Add( "NewGroup" );
						if(iDisOrganisation)		strColumn->Add( "Organisation" );
						if(iDisChestNumber)			strColumn->Add( "ChestNumber" );

						if( strColumn->GetSize( ) )
						{
							html.HtmlTable(strColumn);
							html.HorizontalRule(strColumn->GetSize( ) );

							strColumn->RemoveAll( );

							while( !rs.IsEOF( ) )
							{

								if( rs.IsFieldNull( &rs.m_NewGroupID ) && !rs.m_NewGroupMessage.Compare("") )
									strNewGroupID.Format("");
								else
									strNewGroupID.Format(CConvert::itoa(rs.m_NewGroupID));


								if(iDisSeriesDesc)	
									strColumn->Add( _T(rs.m_SeriesDescription) );
								if(iDisEventNo)	
									strColumn->Add( _T(CConvert::itoa(rs.m_EventNo)) );
								if(iDisLocationDesc)	
									strColumn->Add( _T(rs.m_LocationDescription) );
								if(iDisEventDesc)	
									strColumn->Add( _T(rs.m_EventDescription) );
								if(iDisEventDate)	
									strColumn->Add( _T(CFormat::FormatDate(
																rs.m_DateDAY,
																rs.m_DateMONTH,
																rs.m_DateYEAR)) );

								if(iDisDivisionAct)	
									strColumn->Add( _T(CConvert::itoa(rs.m_DivisionActual)) );
								if(iDisDivision)	
									strColumn->Add( _T(CConvert::itoa(rs.m_DivisionSupposedTo)) );
								if(iDisOverallPlace)	
									strColumn->Add( _T(CConvert::itoa(rs.m_OverallPlace)) );
								if(iDisPlace)		
									strColumn->Add( _T(CConvert::itoa(rs.m_Place)) );
								if(iDisPersonID)	
									strColumn->Add( _T(CConvert::itoa(rs.m_Person_PersonID)) );

								if(iDisFirstName)	
									strColumn->Add( _T(rs.m_FirstName) );
								if(iDisLastName)	
									strColumn->Add( _T(rs.m_LastName) );

								if(iDisAgeGroup)	
									strColumn->Add( _T(rs.m_Sex) + _T(CConvert::itoa(rs.m_AgeGroup)) );

								if(iDisGroup)		
									strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDSupposedTo)) );
								if(iDisGroupAct)		
									strColumn->Add( _T(CConvert::itoa(rs.m_GroupIDActual)) );

								if(iDisGroupStart)		
									strColumn->Add( _T(CConvert::dtoa(rs.m_GroupStartActual)) );

								if(iDisGrossPerformance)
									strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
																rs.m_GrossPerformanceHOUR, 
																rs.m_GrossPerformanceMIN,
																rs.m_GrossPerformanceSEC) ));

								if(iDisNetPerformance)	
									strColumn->Add( _T(CFormat::FormatPerf(rs.m_Timed,
																rs.m_NetPerformanceHOUR, 
																rs.m_NetPerformanceMIN,
																rs.m_NetPerformanceSEC) ));

								if(iDisEventRate)	
									strColumn->Add( _T(CConvert::dtoa(rs.m_EventRate)) );
								if(iDisGroupRate)	
									strColumn->Add( _T(CConvert::dtoa(rs.m_GroupRate)) );

								if(iDisWAVA)		
									strColumn->Add( _T(CConvert::dtoa(rs.m_WorldStandard)) );
								
								if(iDisPoints)		
									strColumn->Add( _T(CConvert::itoa(rs.m_Points)) );
								if(iDisPercentile)	
									strColumn->Add( _T(CConvert::itoa(rs.m_Percentile)) );
								if(iDisEligible)	
									strColumn->Add( _T(rs.m_Eligible) );

								if(iDisNewGroupMsg)		
									strColumn->Add( _T(rs.m_NewGroupMessage));
								if(iDisNewGroup)	
									strColumn->Add( _T( "<p align=\"right\">" + strNewGroupID ) );

								if(iDisOrganisation)	
									strColumn->Add( _T(rs.m_OrgName));

								if(iDisChestNumber)	
									strColumn->Add( _T(rs.m_ChestNumber));

								html.HtmlTable(strColumn);

								rs.MoveNext( );

								strColumn->RemoveAll( );

							}

						}

						delete strColumn;

						html.EndForm();
					}
					else
					{
						html << _T("No Results Available\r\n");
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
				html << _T( (( pMap == NULL ) ? strError : "No Series Selected" )) ;
			}

			if( pMap != NULL )
				delete pMap;

			delete strItems;
		}
		else
		{
			html << _T("Invalid Event Date");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::ReportsEventCalendarForm(CHttpServerContext* pCtxt,
												 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
		auth.m_strFrwdLink = CPage::ReportsEventCalendarExecute;

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


			CSeriesSet rsSeries( &db );
			strSQL.Format( "SELECT * FROM Series ORDER BY SeriesDescription" );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			CLocationSet rsLoc( &db );
			strSQL.Format( "SELECT * FROM Location ORDER BY LocationDescription" );
			rsLoc.Open(CRecordset::dynaset, strSQL );

			CEventTypeSet rsEvntTyp( &db );
			strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
			rsEvntTyp.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				if( !rsLoc.IsEOF( ) )
				{
					if( !rsEvntTyp.IsEOF( ) )
					{
						html << _T("Select a range of Dates for the Event Calendar.<BR>\r\n");

						html.StartForm("Event Calendar", auth.m_strFrwdLink);
						
						html.NonEditText("Event Date", "");
						html.DateBox("From", "EventDateFrom");
						html.DateBox("To", "EventDateTo", 31);
						html.HorizontalRule();

						html.NonEditText("Filter By", "");

						html.StartSelectBox("Series", "SeriesID");
						html.AddSelectBox("(all)", "0", "0");
						while( !rsSeries.IsEOF( ) )
						{
							html.AddSelectBox(rsSeries.m_SeriesDescription, CConvert::itoa(rsSeries.m_SeriesID), "0");
							rsSeries.MoveNext( );
						}
						html.EndSelectBox();

						html.StartSelectBox("Location", "LocationID");
						html.AddSelectBox("(all)", "0", "0");
						while( !rsLoc.IsEOF( ) )
						{
							html.AddSelectBox(rsLoc.m_LocationDescription, CConvert::itoa(rsLoc.m_LocationID), "0");
							rsLoc.MoveNext( );
						}
						html.EndSelectBox();

						html.StartSelectBox("Event Type", "EventTypeID");
						html.AddSelectBox("(all)", "0", "0");
						while( !rsEvntTyp.IsEOF( ) )
						{
							html.AddSelectBox(rsEvntTyp.m_EventDescription, CConvert::itoa(rsEvntTyp.m_EventTypeID), "0");
							rsEvntTyp.MoveNext( );
						}
						html.EndSelectBox();


						html.HorizontalRule();

						html.CheckBox("Order By", "Event Date", "OrderByEventDate", "1", "1");
						html.RadioButton("", "Ascending", "OrderDescending", "0", "0");
						html.RadioButton("", "Descending","OrderDescending", "1", "0");

						html.CheckBox("", "Series", "OrderBySeries", "1", "1");
						html.CheckBox("", "Event Number", "OrderByEventNo", "1", "1");
						html.CheckBox("", "Location", "OrderByLocation", "1", "1");
						html.CheckBox("", "Event Type", "OrderByEventType", "1", "1");


						html.HorizontalRule();


						CReportEventCalendarOption enumList;
						DWORD dwEnum = enumList.Enumerator( );
						while( enumList.GetNext( &dwEnum ) )
						{
							html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Option", 
								CConvert::dwtoa(dwEnum), 
								CConvert::dwtoa(enumList.GetDefaultSelect()) );
						}
						html.HorizontalRule();

						html.SubmitButton(CHtmlKey::Run);

						html.EndForm();

					}
					else
					{
						html << _T("No EventTypes Available\r\n");
					}
				}
				else
				{
					html << _T("No Locations Available\r\n");
				}
			}
			else
			{
				html << _T("No Series Available\r\n");
			}

			rsLoc.Close( );
			rsEvntTyp.Close( );
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

void CWebAthlExtension::ReportsEventCalendarExecute(CHttpServerContext* pCtxt,
													LPTSTR szEventDateFromDAY,
													LPTSTR szEventDateFromMONTH,
													LPTSTR szEventDateFromYEAR,
													LPTSTR szEventDateToDAY,
													LPTSTR szEventDateToMONTH,
													LPTSTR szEventDateToYEAR,
													LPTSTR szSeriesID, 
													LPTSTR szLocationID, 
													LPTSTR szEventTypeID,
													LPTSTR szOrderByEventDate,
													LPTSTR szOrderDescending,
													LPTSTR szOrderBySeries,
													LPTSTR szOrderByEventNo,
													LPTSTR szOrderByLocation,
													LPTSTR szOrderByEventType,
													LPTSTR szOption,
													LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Reports) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Reports Menu", 0);

		html.EndMenu();


		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		int iDisSeriesDesc	 = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplaySeriesDesc);
		int iDisEventNo		 = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplayEventNo);
		int iDisLocationDesc = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplayLocationDesc);
		int iDisEventDesc	 = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplayEventDesc);
		int iDisEventDate	 = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplayEventDate);
		int iDisPreEntryOpen = CReportEventCalendarOption::IsMember( dwOption, CReportEventCalendarOption::DisplayPreEntryOpen);


		COleDateTime dateEventFrom( 
			atoi(szEventDateFromYEAR),
			atoi(szEventDateFromMONTH),
			atoi(szEventDateFromDAY),
			0, 0, 0
		);

		COleDateTime dateEventTo( 
			atoi(szEventDateToYEAR),
			atoi(szEventDateToMONTH),
			atoi(szEventDateToDAY),
			0, 0, 0
		);

		if( dateEventFrom.GetStatus() == COleDateTime::valid && 
			dateEventTo.GetStatus()   == COleDateTime::valid    )
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strError;

			CString strSeriesIDList;
			
			CStringArray* strItems = new CStringArray();

			CCSV csv(CWebAthlExtension::chIsapiDelimiter);

			try
			{
				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				if( atoi(szSeriesID) )
				{
					strSeriesIDList = szSeriesID;
					csv.GetItems(strItems, &strSeriesIDList);
				}
				else
				{
					CUtil::GetIntegerItems(&db, "SELECT SeriesID FROM Series", strItems);
					csv.GetCSVRow(strItems, &strSeriesIDList);
				}

				db.Close( );
			}
			catch (CDBException* pEx)
			{
				html << pEx;

				pEx->Delete();
			}


			// maps key-value pairs.
			// this map, maps an int key to an CPoint(int x, int y) value.
			CMap<int,int,CPoint,CPoint>* pMap;
			pMap = CUtil::FindEventsBetweenDates(strConnect, dateEventFrom, dateEventTo, strItems, &strError);


			if( pMap != NULL && pMap->GetStartPosition() != NULL )
			{
				try
				{
					//CString strConnect = prop.GetDefaultConnect();
					CString strSQLtmp;
					CString strSQL;

					CDatabase db;
					db.OpenEx( strConnect, CDatabase::noOdbcDialog );


					CEventETypLocSet rs( &db );

					strSQL += _T("SELECT Series.*, Event.*, EventType.*, Location.* ");
					strSQL += _T(" FROM Series, Event, EventType, Location ");
					strSQL += _T(" WHERE Series.SeriesID = Event.SeriesID ");
					strSQL += _T(" AND EventType.EventTypeID = Event.EventTypeID ");
					strSQL += _T(" AND Location.LocationID = Event.LocationID ");

					if( atoi(szLocationID) )
					{
						strSQL += _T(" AND Location.LocationID = ");
						strSQL += _T(szLocationID);
						strSQL += _T(" ");
					}

					if( atoi(szEventTypeID) )
					{
						strSQL += _T(" AND EventType.EventTypeID = ");
						strSQL += _T(szEventTypeID);
						strSQL += _T(" ");
					}

					CString strSQLBetween = _T(" ( Series.SeriesID = %d AND Event.EventNo BETWEEN %d AND %d ) ");


					POSITION pos = pMap->GetStartPosition();
					int nKeySeriesID;
					CPoint ptEventNo;

					int iORflag = 0;

					while( pos != NULL )
					{
						pMap->GetNextAssoc( pos, nKeySeriesID, ptEventNo );

						strSQLtmp.Format(strSQLBetween, 
							nKeySeriesID, ptEventNo.x, ptEventNo.y);

						if( !iORflag )
						{
							strSQL += " AND	( ";
							iORflag = 1;
						}
						else
						{
							strSQL += " OR ";
						}

						strSQL += strSQLtmp;
					}
					strSQL += " ) ";


					int iOrderByEventDate = atoi(szOrderByEventDate);
					int iOrderDescending = atoi(szOrderDescending);
					int iOrderBySeries = atoi(szOrderBySeries);
					int iOrderByEventNo = atoi(szOrderByEventNo);
					int iOrderByLocation = atoi(szOrderByLocation);
					int iOrderByEventType = atoi(szOrderByEventType);

					if( iOrderByEventDate || 
						iOrderBySeries    || 
						iOrderByEventNo   || 
						iOrderByLocation  || 
						iOrderByEventType    )
					{
						CString strDesc;

						if(iOrderDescending) 
							strDesc = _T("DESC");
						else
							strDesc = _T("ASC");

						CString strNextOrder = _T(" ORDER BY ");

						if(iOrderByEventDate)
						{
							strSQL += _T(strNextOrder);
							strNextOrder = _T(",");

							strSQL += _T(" Event.DateYEAR ");
							strSQL += _T(strDesc);

							strSQL += _T(strNextOrder);
							strSQL += _T(" Event.DateMONTH ");
							strSQL += _T(strDesc);

							strSQL += _T(strNextOrder);
							strSQL += _T(" Event.DateDAY ");
							strSQL += _T(strDesc);
						}

						if(iOrderBySeries)
						{
							strSQL += _T(strNextOrder);
							strNextOrder = _T(",");

							strSQL += _T(" Series.SeriesDescription ");
						}

						if(iOrderByEventNo)
						{
							strSQL += _T(strNextOrder);
							strNextOrder = _T(",");

							strSQL += _T(" Event.EventNo ");
						}

						if(iOrderByLocation)
						{
							strSQL += _T(strNextOrder);
							strNextOrder = _T(",");

							strSQL += _T(" Location.LocationDescription ");
						}

						if(iOrderByEventType)
						{
							strSQL += _T(strNextOrder);
							strNextOrder = _T(",");

							strSQL += _T(" EventType.EventDescription ");
						}
					}


					//html << _T(strSQL) << _T("<BR>\r\n");


					rs.Open(CRecordset::forwardOnly, strSQL );

					if( !rs.IsEOF( ) )
					{
						html.StartForm("Event Calendar", "");

						CString strEventBetween;

						strEventBetween.Format( _T("%s </strong>to<strong> %s"), 
							CFormat::FormatDate(
								atoi(szEventDateFromDAY),
								atoi(szEventDateFromMONTH),
								atoi(szEventDateFromYEAR)),
							CFormat::FormatDate(
								atoi(szEventDateToDAY),
								atoi(szEventDateToMONTH),
								atoi(szEventDateToYEAR)) );

						html.NonEditText("Event Date", strEventBetween);

						if( atoi(szSeriesID) )
							html.NonEditText("Series", _T(rs.m_SeriesDescription));
						else
							html.NonEditText("Series", "(all)");

						if( atoi(szLocationID) )
							html.NonEditText("Location", _T(rs.m_LocationDescription));
						else
							html.NonEditText("Location", "(all)");

						if( atoi(szEventTypeID) )
							html.NonEditText("Event Type", _T(rs.m_EventDescription));
						else
							html.NonEditText("Event Type", "(all)");

						html.EndForm();



						CString strPreEntry;

						html.StartForm("", "");

						CStringArray* strColumn;
						strColumn = new CStringArray;

						if(iDisSeriesDesc)			strColumn->Add( "Series" );
						if(iDisEventNo)				strColumn->Add( "Event No" );
						if(iDisLocationDesc)		strColumn->Add( "Location" );
						if(iDisEventDesc)			strColumn->Add( "Event" );
						if(iDisEventDate)			strColumn->Add( "Date" );
						if(iDisPreEntryOpen)		strColumn->Add( "Pre-Entry" );

						if( strColumn->GetSize( ) )
						{
							html.HtmlTable(strColumn);
							html.HorizontalRule(strColumn->GetSize( ) );

							strColumn->RemoveAll( );

							while( !rs.IsEOF( ) )
							{

								if( !rs.IsFieldNull( &rs.m_PreEntryOpen ) && (rs.m_PreEntryOpen > 0) )
									strPreEntry.Format("Open");
								else
									strPreEntry.Format("");


								if(iDisSeriesDesc)	
									strColumn->Add( _T(rs.m_SeriesDescription) );
								if(iDisEventNo)	
									strColumn->Add( _T(CConvert::itoa(rs.m_EventNo)) );
								if(iDisLocationDesc)	
									strColumn->Add( _T(rs.m_LocationDescription) );
								if(iDisEventDesc)	
									strColumn->Add( _T(rs.m_EventDescription) );
								if(iDisEventDate)	
									strColumn->Add( _T(CFormat::FormatDate(
																rs.m_DateDAY,
																rs.m_DateMONTH,
																rs.m_DateYEAR)) );

								if(iDisPreEntryOpen)	
									strColumn->Add( _T(strPreEntry) );

								html.HtmlTable(strColumn);

								rs.MoveNext( );

								strColumn->RemoveAll( );

							}

						}

						delete strColumn;

						html.EndForm();
					}
					else
					{
						html << _T("No Results Available\r\n");
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
				html << _T( (( pMap == NULL ) ? strError : "No Series Selected" )) ;
			}

			if( pMap != NULL )
				delete pMap;

			delete strItems;
		}
		else
		{
			html << _T("Invalid Event Date");
		}

		html.EndPage();
		html.EndContent();
	}
}






