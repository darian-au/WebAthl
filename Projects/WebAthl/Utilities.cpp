// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"

#include "WebAthl.h"

#include "ParticipantDetailsSet.h"
#include "SeriesSet.h"
#include "PersonSet.h"

#include "ParticipantForSeriesSet.h"
#include "ResultsParticipantForSeriesSet.h"
#include "CountResultSet.h"

#include "IntegerSet.h"
#include "DupPersonSet.h"
#include "AgeGroupSet.h"

#include "PersonParticipantForSeriesSet.h"
#include "SeriesSeasonSet.h"
#include "ResultsSet.h"
#include "EventETypLocSet.h"

#define MIN_MULTIPLIER 0.55

///////////////////////////////////////////////////////////////////////
// Utilities

void CWebAthlExtension::UtilitiesMenu(CHttpServerContext* pCtxt,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain | CModule::Utilities ) )
	{
		auth.m_strHeading = "Utilities";
		auth.m_strBackLink = CPage::UtilitiesMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "1");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.SetCookie(CHtmlKey::IsUtil, "1");
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		if( auth.HasPermission(CModule::SeriesMaintain) )
		{
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Set Eligibility on Group", 1, CPage::UtilitiesSetEligibilitySelectGroupForm);
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Split Divisions By Handicap Group", 1, CPage::UtilitiesSplitDivisionForm);
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Split Divisions By Age Group", 1, CPage::UtilitiesSplitDivisionByAgeGroupForm);
			html.WritePageMenuItem(CPage::SearchPersonForm, "Change Group", 2, CPage::UtilitiesChangeSelectSeriesForm, CHtmlKey::UtilitiesChangeIsGroup);
			html.WritePageMenuItem(CPage::SearchPersonForm, "Change Eligibility", 2, CPage::UtilitiesChangeSelectSeriesForm, CHtmlKey::UtilitiesChangeIsEligibility);
		}
		if( auth.HasPermission(CModule::Utilities) )
		{
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Rebuild Age Groups", 1, CPage::UtilitiesRebuildAgeGroupsForm);
			html.WritePageMenuItem(CPage::SearchPersonForm, "Fix Duplicate Person", 3, CPage::UtilitiesFixDuplicatePersonForm,"","Duplicate");
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Bulk Adjust Groups", 1, CPage::UtilitiesBulkAdjustForm);
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Delete Results", 1, CPage::UtilitiesDeleteResultsForm);
			html.WritePageMenuItem(CPage::SeriesSelectForm, "Manual Processing", 1, CPage::ProcessingForm);
		}
		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::UtilitiesChangeSelectSeriesForm(CHttpServerContext* pCtxt,
													LPTSTR szPersonID,
													LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesChangeForm;

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

			strSQL.Format( "SELECT Series.* FROM ParticipantForSeries, Series WHERE Series.SeriesID = ParticipantForSeries.SeriesID AND ((ParticipantForSeries.PersonID=%s)) ORDER BY SeriesDescription", szPersonID );
			rsSeries.Open(CRecordset::dynaset, strSQL );

			if( !rsSeries.IsEOF( ) )
			{
				html << _T("Select a Series\r\n");

				html.StartForm("Series", auth.m_strFrwdLink);
				
				html.HiddenText("PersonID", szPersonID);

				html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Series Available for this Person\r\n");
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

void CWebAthlExtension::UtilitiesChangeForm(CHttpServerContext* pCtxt,
											LPTSTR szPersonID,
											LPTSTR szSeriesID,
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
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CCountResultSet rsGroups( &db );
			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", szSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{
				CString strSQLtmp;

				CParticipantDetailsSet rs( &db );

				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GROUPFORPARTICIPANT);

				strSQL.Format(strSQLtmp,
					_T(szPersonID),
					_T(szSeriesID),
					_T(szPersonID),
					_T(szSeriesID));

				rs.Open(CRecordset::dynaset, strSQL );

				COleDateTime t = COleDateTime::GetCurrentTime();

				CString strAgeGroup;
				CString strAgeCategory;
				int iAgeGroup;
				
				if( !rs.IsEOF( ) )
				{
					html.StartForm("Participant Details for Series", CPage::UtilitiesChangeExecute);

					html.HiddenInt("SeriesID", rs.m_SeriesID);
					html.NonEditText("Series", rs.m_SeriesDescription);

					html.NonEditText("Participant's Last Event",
						(CConvert::itoa(rs.m_EventNo) + ": " + rs.m_LocationDescription + ", " + rs.m_EventDescription) );

					html.NonEditDateBox(
						"Date",
						rs.m_DateDAY,
						rs.m_DateMONTH,
						rs.m_DateYEAR);

					html.HorizontalRule();

					html.NonEditInt("Person ID", rs.m_PersonID);
					html.HiddenInt("PersonID", rs.m_PersonID);

					html.NonEditText("LastName", rs.m_LastName);
					html.NonEditText("FirstName", rs.m_FirstName);

					html.NonEditDateBox(
						_T("Date of Birth"),
						rs.m_dobDAY,
						rs.m_dobMONTH,
						rs.m_dobYEAR);


					iAgeGroup = CCalculate::GroupAge(
										CCalculate::YearDiff(rs.m_dobDAY,
												 rs.m_dobMONTH,
												 rs.m_dobYEAR,
												 t.GetDay(),
												 t.GetMonth(),
												 t.GetYear() ),
										strAgeCategory, 
										&prop);

					strAgeGroup.Format("%s%d",rs.m_Sex, iAgeGroup);
					html.NonEditText("AgeGroup", strAgeGroup);

					if(!_tcscmp(auth.m_strFrwdLink, CHtmlKey::UtilitiesChangeIsGroup))
					{
						html.HorizontalRule();

						html.NonEditInt("Handicap Group", rs.m_GroupIDSupposedTo);

						int iNewGroupID;

						if( (rs.m_NewGroupID > 0)  && !rs.IsFieldNull(&rs.m_NewGroupID) )
							iNewGroupID = rs.m_NewGroupID;
						else
							iNewGroupID = rs.m_GroupIDSupposedTo;

						//html.EditIntBox("New Handicap Group","GroupIDSupposedTo",iNewGroupID);
						html.StartSelectBox("New Handicap Group", "GroupIDSupposedTo");
						for( int g = 1 ; g <= rsGroups.m_Total ; g++ )
						{
							html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iNewGroupID) );
						}
						html.EndSelectBox();


						html.EditIntBox("Division","DivisionSupposedTo",rs.m_DivisionSupposedTo);

						if( (_tcslen(rs.m_NewGroupMessage) > 0)  && !rs.IsFieldNull(&rs.m_NewGroupMessage) )
							html.EditTextBoxLarge("Comment", "NewGroupMessage", rs.m_NewGroupMessage);
						else
							html.EditTextBoxLarge("Comment", "NewGroupMessage", "Handicap Review");
					}
					else if(!_tcscmp(auth.m_strFrwdLink, CHtmlKey::UtilitiesChangeIsEligibility))
					{
						html.HorizontalRule();
						html.NonEditText("Eligibility", rs.m_EligibilityForEvent);

						html.HorizontalRule();
						html.RadioButton("Eligibility", "Yes", "EligibilityForEvent", "Y", rs.m_EligibilityForEvent);
						html.RadioButton("", "No", "EligibilityForEvent", "N", rs.m_EligibilityForEvent);
					}

					html.HorizontalRule();

					html.SubmitButton(CHtmlKey::Save);
					html.EndForm();
				}
				else
				{
					html << _T(CRecordsetEx::m_szMsgEmptyRecordset) << _T("<BR>\r\n");
				}

				rs.Close( );
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

void CWebAthlExtension::UtilitiesChangeExecute(CHttpServerContext* pCtxt,
										LPTSTR szPersonID,
										LPTSTR szSeriesID,
										LPTSTR szGroupIDSupposedTo,
										LPTSTR szDivisionSupposedTo,
										LPTSTR szNewGroupMessage,
										LPTSTR szEligibilityForEvent,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			if( !_tcscmp( szSubmit, CHtmlKey::Save ) )
			{
				// update ParticipantForSeries
				strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND PersonID = %s ", szSeriesID, szPersonID );
				CParticipantForSeriesSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.Edit( );

				if( _tcslen( szGroupIDSupposedTo ) > 0 )
					rs.m_GroupIDSupposedTo = atoi(szGroupIDSupposedTo);
				if( _tcslen( szDivisionSupposedTo ) > 0 )
					rs.m_DivisionSupposedTo = atoi(szDivisionSupposedTo);
				if( _tcslen( szEligibilityForEvent ) > 0 )
					rs.m_EligibilityForEvent = _T(szEligibilityForEvent);

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Participant, <B>");
					html << _T(szPersonID);
					if( _tcslen( szGroupIDSupposedTo ) > 0 )
					{
						html << _T("</B>; Group <B>");
						html << _T(szGroupIDSupposedTo);
					}
					if( _tcslen( szDivisionSupposedTo ) > 0)
					{
						html << _T("</B>; Division <B>");
						html << _T(szDivisionSupposedTo);
					}
					if( _tcslen( szEligibilityForEvent ) > 0 )
					{
						html << _T("</B>; Eligibility <B>");
						html << _T(szEligibilityForEvent);
					}
					html << _T("</B><BR>\r\n");
				}
				rs.Close( );

				//update Results
				strSQL.Format( "SELECT * FROM Results WHERE SeriesID = %s AND PersonID = %s ORDER BY EventID DESC", szSeriesID, szPersonID );
				CResultsSet rsResults( &db );
				rsResults.Open(CRecordset::dynaset, strSQL );

				if( !rsResults.IsEOF( ) && !rsResults.IsFieldNull( &rsResults.m_EventID ) )
				{
					if( (_tcslen( szGroupIDSupposedTo ) > 0) || (_tcslen( szNewGroupMessage ) > 0) )
					{
						rsResults.Edit( );

						if( _tcslen( szGroupIDSupposedTo ) > 0 )
							rsResults.m_NewGroupID = atoi(szGroupIDSupposedTo);
						if( _tcslen( szNewGroupMessage ) > 0 )
							rsResults.m_NewGroupMessage = _T(szNewGroupMessage);

						if( !rsResults.CanUpdate( ) )
							html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
						if( !rsResults.Update( ) )
							html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
						else
						{
							html << _T("Modified Result for Person, <B>");
							html << _T(szPersonID);
							html << _T("</B>; Event: <B>");
							html << _T(rsResults.m_EventID);
							if( _tcslen( szGroupIDSupposedTo ) > 0)
							{
								html << _T("</B>; New Group: <B>");
								html << _T(szGroupIDSupposedTo);
							}
							if( _tcslen( szNewGroupMessage ) > 0 )
							{
								html << _T("</B>; Message: <B>");
								html << _T(szNewGroupMessage);
							}
							html << _T("</B><BR>\r\n");
						}
					}
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

void CWebAthlExtension::UtilitiesSetEligibilitySelectGroupForm(CHttpServerContext* pCtxt,
													  LPTSTR szSeriesID,
													  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesSetEligibilityByGroupForm;

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

			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", szSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{
				html << _T("Select a Range of Groups to set Eligibility for\r\n");

				CSeriesSet rsSeries( &db );

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				html.StartForm("Groups", auth.m_strFrwdLink);
				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				
				rsSeries.Close( );
				
				html.HiddenText("SeriesID", szSeriesID);
				html.HorizontalRule();

				int g;

				html.StartSelectBox("From Group", "GroupIDfr");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox(CConvert::itoa(g), CConvert::itoa(g), "");
				}
				html.EndSelectBox();

				html.StartSelectBox("To Group", "GroupIDto");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox(CConvert::itoa(g), CConvert::itoa(g), "");
				}
				html.EndSelectBox();
				html.HorizontalRule();

				html.CheckBox("", "Display Participants", "showParticipants", "1", "1");

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
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

void CWebAthlExtension::UtilitiesSetEligibilityByGroupForm(CHttpServerContext* pCtxt,
											   LPTSTR szSeriesID,
											   LPTSTR szGroupIDFrom,
											   LPTSTR szGroupIDTo,
											   LPTSTR szShowParticipants,
											   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesSetEligibilityByGroupExecute;

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

			CString strSQLtmp;

			CPersonParticipantForSeriesSet rs( &db );

			CUtil::LoadLongResource(strSQLtmp, IDS_SQL_PERSONPARTICIPANT);

			strSQL.Format(strSQLtmp,
				_T(szSeriesID),
				_T(szGroupIDFrom),
				_T(szGroupIDTo));


			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				COleDateTime t = COleDateTime::GetCurrentTime();
				CString strAgeCategory;
				int iAgeGroup;

				CString strGroupDesc;
				
				html << _T("Select a Eligibility\r\n");

				html.StartForm("Eligibility", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", szSeriesID);
				html.HiddenText("GroupIDfr", szGroupIDFrom);
				html.HiddenText("GroupIDto", szGroupIDTo);

				CSeriesSet rsSeries( &db );

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				rsSeries.Close( );

				if( atoi(szGroupIDFrom) == atoi(szGroupIDTo) )
					strGroupDesc.Format(" %s ", szGroupIDFrom);
				else
					strGroupDesc.Format(" %s </strong> to <strong> %s ", szGroupIDFrom, szGroupIDTo);


				html.NonEditText("Set Eligibility on Group", strGroupDesc );


				html.HorizontalRule();
				html.RadioButton("Eligibility", "Eligible", "Eligible", "Y", "Y");
				html.RadioButton("", "Not Eligible", "Eligible", "N", "Y");


				html.HorizontalRule();
				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);

				html.EndForm();



				if( atoi(szShowParticipants) )
				{
					html.StartForm("", "");

					strGroupDesc.Format("<strong>Group %s </strong>", CConvert::itoa(rs.m_GroupIDSupposedTo));

					CStringArray* strColumn;
					strColumn = new CStringArray;

					strColumn->Add( strGroupDesc );
					strColumn->Add( "AgeGroup" );
					strColumn->Add( "Elig" );
					strColumn->Add( "Points" );
					strColumn->Add( "Events" );

					html.EmptyHorizontalRule(strColumn->GetSize( ) );
					html.HtmlTable(strColumn);
					html.HorizontalRule(strColumn->GetSize( ) );

					strColumn->RemoveAll( );

					int iCurrentGroupID = rs.m_GroupIDSupposedTo;

					while( !rs.IsEOF( ) )
					{
						if( iCurrentGroupID != rs.m_GroupIDSupposedTo )
						{
							iCurrentGroupID = rs.m_GroupIDSupposedTo;

							strGroupDesc.Format("<strong>Group %s </strong>", CConvert::itoa(iCurrentGroupID));

							strColumn->Add( strGroupDesc );
							strColumn->Add( "AgeGroup" );
							strColumn->Add( "Elig" );
							strColumn->Add( "Points" );
							strColumn->Add( "Events" );

							html.EmptyHorizontalRule(strColumn->GetSize( ) );
							html.HtmlTable(strColumn);
							html.HorizontalRule(strColumn->GetSize( ) );

							strColumn->RemoveAll( );
						}


						iAgeGroup = CCalculate::GroupAge(
													 CCalculate::YearDiff(rs.m_dobDAY,
													 rs.m_dobMONTH,
													 rs.m_dobYEAR,
													 t.GetDay( ),
													 t.GetMonth( ),
													 t.GetYear( )),
											strAgeCategory,
											&prop);

						strColumn->Add( _T(rs.m_FirstName) + " " +
									 _T(rs.m_LastName) );

						strColumn->Add( _T(rs.m_Sex + CConvert::itoa(iAgeGroup)) );

						strColumn->Add( _T(rs.m_EligibilityForEvent) );
						strColumn->Add( _T(CConvert::itoa(rs.m_NetPoints)) );
						strColumn->Add( _T(CConvert::itoa(rs.m_EventsForSeason)) );


						html.HtmlTable(strColumn);

						rs.MoveNext( );

						strColumn->RemoveAll( );

					}

					delete strColumn;

					html.EndForm();
				}
			}
			else
			{
				html << _T("No Participants in Group\r\n");
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

void CWebAthlExtension::UtilitiesSetEligibilityByGroupExecute(CHttpServerContext* pCtxt,
										   LPTSTR szSeriesID,
										   LPTSTR szGroupIDFrom,
										   LPTSTR szGroupIDTo,
										   LPTSTR szEligible,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND GroupIDSupposedTo >= %s AND GroupIDSupposedTo <= %s ", szSeriesID, szGroupIDFrom, szGroupIDTo );
			CParticipantForSeriesSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				while( !rs.IsEOF( ) )
				{
					rs.Edit( );

					rs.m_EligibilityForEvent = szEligible;

					if( !rs.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
					if( !rs.Update( ) )
						html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
					else
					{
						html << _T("Modified Person, <B>");
						html << _T(rs.m_PersonID);
						html << _T("</B>; Group <B>");
						html << _T(rs.m_GroupIDSupposedTo);
						html << _T("</B>; Eligible <B>");
						html << _T(szEligible);
						html << _T("</B><BR>\r\n");
					}
					rs.MoveNext( );
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

void CWebAthlExtension::UtilitiesBulkAdjustForm(CHttpServerContext* pCtxt,
										   LPTSTR szSeriesID,
										   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesBulkAdjustExecute;

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
			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", szSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{
				int iLowGroup = 0;
				int iHighGroup = 0;

				strSQL.Format( "SELECT MAX(GroupIDSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				CIntegerSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iHighGroup = rs.m_Val;
				rs.Close( );

				strSQL.Format( "SELECT MIN(GroupIDSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				rs.Open(CRecordset::dynaset, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iLowGroup = rs.m_Val;
				rs.Close( );

				html << _T("Please enter a Group Multiplier to Bulk Adjust by.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("This will Regroup all Participants by Multiplying their current Group by this Value.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("<small>Note that a Multiplier of 1.00 will leave Groups Unchanged.</small><BR>\r\n");

				html << _T("<BR>\r\n");
				html << _T("e.g.:\r\n");
				html << _T("<blockquote>\r\n");
				html << _T("    <small><font face=\"Courier New\">With Multiplier = <B>1.05</B></font></small><BR>\r\n");
				html << _T("    <small><font face=\"Courier New\">a Person on Group <B>23</B> will be moved to Group <B>24</B></font></small><BR>\r\n");
				html << _T("    <small><font face=\"Courier New\">a Person on Group <B>47</B> will be moved to Group <B>49</B></font></small><BR>\r\n");
				html << _T("</blockquote>\r\n");

				html.StartForm("Bulk Adjust Groups", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", szSeriesID);

				CSeriesSet rsSeries( &db );

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				rsSeries.Close( );

				html.HorizontalRule();

				int g;

				html.StartSelectBox("From Group", "LowGroup");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iLowGroup) );
				}
				html.EndSelectBox();

				html.StartSelectBox("To Group", "HighGroup");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox(CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iHighGroup) );
				}
				html.EndSelectBox();
				html.HorizontalRule();


				html.EditFloatBox("Group Multiplier", "Multiplier", 1.00);

				html.HorizontalRule();

				html.EditTextBoxLarge("Comment", "NewGroupMessage", "Bulk Adjustment");

				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();

				html << _T("<BR>\r\n");
				html << _T("<B>Warning</B>: <BR>\r\n");
				html << _T("Do not run a Bulk Adjustment on a Series before the latest Event has been Post-Event Processed, Locked-Out and the next Event Pre-Event Processed at least once.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("Bulk Adjusting Groups works by looking at the Participant Details for the Series.  If Pre-Event Processing has not been performed then the Group in the Participant Details for Series will be for the last Event and the Bulk Adjustment Group will be calculated incorrectly for those Participants who are Regrouped during Post-Event Processing.<BR>\r\n");
				html << _T("<BR>\r\n");

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

void CWebAthlExtension::UtilitiesBulkAdjustExecute(CHttpServerContext* pCtxt,
												   LPTSTR szSeriesID,
												   LPTSTR szLowGroup,
												   LPTSTR szHighGroup,
												   LPTSTR szMultiplier,
												   LPTSTR szNewGroupMessage,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

		html.EndMenu();

		if( atof(szMultiplier) > MIN_MULTIPLIER )
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				// Update the GroupIDSupposedTo of all People in ParticipantForSeries
				strSQL.Format( "UPDATE ParticipantForSeries SET GroupIDSupposedTo = ROUND(GroupIDSupposedTo * %s , 0) WHERE SeriesID = %s AND GroupIDSupposedTo >= %s AND GroupIDSupposedTo <= %s ", szMultiplier, szSeriesID, szLowGroup, szHighGroup );
				db.ExecuteSQL( strSQL );

				db.Close( );
			}
			catch (CDBException* pEx)
			{
				html << pEx;

				pEx->Delete();
			}

			// close the connection to allow the transaction 
			// to complete and release any locks

			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;
				CString strSQLtmp;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CDatabase dbUpdate;
				dbUpdate.OpenEx( strConnect, CDatabase::noOdbcDialog );

				// Get the List of People with their NewGroupID
				CUtil::LoadLongResource(strSQLtmp, IDS_SQL_GETPERSONSLATESTEVENT);
				strSQL.Format( strSQLtmp, szSeriesID );
				CResultsParticipantForSeriesSet rs( &db );

				rs.Open(CRecordset::forwardOnly , strSQL );

				int iCounter = 0;

				while( !rs.IsEOF( ) )
				{
					int iSeriesID = rs.m_SeriesID;
					int iEventID = rs.m_EventID;
					int iPersonID = rs.m_PersonID;

					int iOldGroupID;
					CString strNewGroupMessage;

					int iNewGroupID = rs.m_PFS_GroupIDSupposedTo;


					if( rs.IsFieldNull( &rs.m_NewGroupID ) )
						iOldGroupID = rs.m_GroupIDSupposedTo;
					else
						iOldGroupID = rs.m_NewGroupID;


					if( rs.IsFieldNull( &rs.m_NewGroupMessage ) )
						strNewGroupMessage = szNewGroupMessage;
					else
						strNewGroupMessage = rs.m_NewGroupMessage;



					strSQL.Format( "UPDATE Results SET NewGroupID = %d, NewGroupMessage = '%s' WHERE SeriesID = %d AND EventID = %d AND PersonID = %d ",
						iNewGroupID,
						strNewGroupMessage,
						iSeriesID,
						iEventID,
						iPersonID);

					if( iOldGroupID != iNewGroupID )
					{
						try
						{
							dbUpdate.ExecuteSQL( strSQL );
							iCounter++;
						}
						catch (CDBException* pEx)
						{
							html << pEx;

							pEx->Delete();
						}

						html << _T("Person <B>");
						html << _T(CConvert::itoa(iPersonID));
						html << _T("</B>; EventID <B>");
						html << _T(CConvert::itoa(iEventID));
						html << _T("</B> Group <B>");
						html << _T(CConvert::itoa(iOldGroupID));
						html << _T("</B> -> <B>");
						html << _T(CConvert::itoa(iNewGroupID));
						html << _T("</B> Message <B>");
						html << _T(strNewGroupMessage);
						html << _T("</B><BR>\r\n");
					}

					rs.MoveNext( );
				}

				rs.Close( );
				html << _T("<BR>\r\nRows :");
				html << _T(CConvert::itoa(iCounter));
				html << _T("<BR \r\n>");

				dbUpdate.Close( );
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
			html << _T("Multiplier must be greater than ");
			html << _T( CConvert::dtoa(MIN_MULTIPLIER) );
			html << _T("<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::UtilitiesSplitDivisionForm(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesSplitDivisionExecute;

		html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strSQL;
			CString strConnect = prop.GetDefaultConnect();

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			int iLowGroup = 0;
			int iHighGroup = 0;
			int iDivision = 0;

			CCountResultSet rsGroups( &db );

			strSQL.Format( "SELECT MAX(GroupID) AS Total FROM Groups WHERE SeriesID = %s", szSeriesID );
			rsGroups.Open(CRecordset::dynaset, strSQL );

			if( !rsGroups.IsEOF( ) && !rsGroups.IsFieldNull( &rsGroups.m_Total ) )
			{
				strSQL.Format( "SELECT MAX(GroupIDSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				CIntegerSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iHighGroup = rs.m_Val;
				rs.Close( );

				strSQL.Format( "SELECT MIN(GroupIDSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				rs.Open(CRecordset::dynaset, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iLowGroup = rs.m_Val;
				rs.Close( );

				strSQL.Format( "SELECT MAX(DivisionSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				rs.Open(CRecordset::dynaset, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iDivision = rs.m_Val;
				rs.Close( );


				html << _T("Please specify a Range of Handicap Groups, and a Division to Split them into.<BR>\r\n");

				html.StartForm("Split Divisions", auth.m_strFrwdLink);
				CSeriesSet rsSeries( &db );

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
				rsSeries.Open(CRecordset::dynaset, strSQL );

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				
				rsSeries.Close( );
				
				html.HiddenText("SeriesID", szSeriesID);
				html.HorizontalRule();


				int g;

				html.StartSelectBox("From Handicap Group", "LowGroup");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox( CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iLowGroup) );
				}
				html.EndSelectBox();

				html.StartSelectBox("To Handicap Group", "HighGroup");
				for( g = 1 ; g <= rsGroups.m_Total ; g++ )
				{
					html.AddSelectBox(CConvert::itoa(g), CConvert::itoa(g), CConvert::itoa(iHighGroup) );
				}
				html.EndSelectBox();
				html.HorizontalRule();

				html.EditIntBox("Into Division", "Division", iDivision);

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();
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

void CWebAthlExtension::UtilitiesSplitDivisionExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szLowGroup,
										  LPTSTR szHighGroup,
										  LPTSTR szDivision,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			if( atoi(szDivision) > 0 )
			{

				// Update the DivisionSupposedTo of all People in ParticipantForSeries between the specified GroupIDs
				strSQL.Format( "UPDATE ParticipantForSeries SET DivisionSupposedTo = %s WHERE SeriesID = %s AND GroupIDSupposedTo >= %s AND GroupIDSupposedTo <= %s ", szDivision, szSeriesID, szLowGroup, szHighGroup );
				db.ExecuteSQL( strSQL );

				// Get the List of People with their New Division between the specified GroupIDs
				strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND DivisionSupposedTo = %s AND GroupIDSupposedTo >= %s AND GroupIDSupposedTo <= %s ", szSeriesID, szDivision, szLowGroup, szHighGroup );
				CParticipantForSeriesSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				if( !rs.IsEOF( ) )
				{
					while( !rs.IsEOF( ) )
					{
						html << _T("Modified Person, <B>");
						html << _T(CConvert::itoa(rs.m_PersonID));
						html << _T("</B> in Handicap Group <B>");
						html << _T(CConvert::itoa(rs.m_GroupIDSupposedTo));
						html << _T("</B> to Division <B>");
						html << _T(CConvert::itoa(rs.m_DivisionSupposedTo));
						html << _T("</B><BR>\r\n");

						rs.MoveNext( );
					}
				}
				else
				{
					html << _T("No Participants in Group\r\n");
				}
				rs.Close( );
			}
			else
			{
				html << _T("Invalid Division\r\n");
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

void CWebAthlExtension::UtilitiesSplitDivisionByAgeGroupForm(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SeriesMaintain) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesSplitDivisionByAgeGroupExecute;

		html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strSQL;
			CString strConnect = prop.GetDefaultConnect();

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			int nMaxJunior = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
			int nMinVeteran = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
			int nJuniorGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
			int nVeteranGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

			CString strAgeCategory;

			int iLowGroup = 1000;
			int iHighGroup = 0;
			int iDivision = 0;

			CPersonSet rsPerson( &db );

			strSQL.Format( "SELECT Person.* FROM ParticipantForSeries, Person WHERE Person.PersonID = ParticipantForSeries.PersonID AND Person.dobDAY IS NOT NULL AND Person.dobMONTH IS NOT NULL AND Person.dobYEAR IS NOT NULL AND SeriesID = %s ORDER BY Person.dobYEAR , Person.dobMONTH , Person.dobDAY ", szSeriesID );
			rsPerson.Open(CRecordset::forwardOnly, strSQL );

			COleDateTime today = COleDateTime::GetCurrentTime();

			while( !rsPerson.IsEOF( ) )
			{

				int iAgeGroup = CCalculate::GroupAge( 
										CCalculate::YearDiff(
												rsPerson.m_dobDAY,
												rsPerson.m_dobMONTH,
												rsPerson.m_dobYEAR,
												today.GetDay( ),
												today.GetMonth( ),
												today.GetYear( )),
										strAgeCategory, 
										&prop, nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);

				if( iAgeGroup < iLowGroup )
				{
					iLowGroup = iAgeGroup;
				}

				if( iAgeGroup > iHighGroup )
				{
					iHighGroup = iAgeGroup;
				}

				rsPerson.MoveNext( );
			}
			rsPerson.Close( );

			if( iHighGroup > 0 )
			{
				CIntegerSet rs( &db );

				strSQL.Format( "SELECT MAX(DivisionSupposedTo) AS Val FROM ParticipantForSeries WHERE SeriesID = %s ", szSeriesID );
				rs.Open(CRecordset::forwardOnly, strSQL );
				if( !rs.IsEOF( ) && !rs.IsFieldNull( &rs.m_Val ) )
					iDivision = rs.m_Val;
				rs.Close( );


				html << _T("Please specify a Range of Age Groups, and a Division to Split them into.<BR>\r\n");
				html << _T("<BR>Note: People who do not have a valid Date of Birth will no be affected by the Split.<BR>\r\n");

				html.StartForm("Split Divisions", auth.m_strFrwdLink);
				CSeriesSet rsSeries( &db );

				strSQL.Format( "SELECT * FROM Series WHERE SeriesID = %s", szSeriesID );
				rsSeries.Open(CRecordset::forwardOnly, strSQL );

				html.NonEditText("Series", rsSeries.m_SeriesDescription );
				
				rsSeries.Close( );
				
				html.HiddenText("SeriesID", szSeriesID);
				html.HorizontalRule();


				int g;
				int iPreviousAgeGroup;
				
				iPreviousAgeGroup = -1;
				html.StartSelectBox("From Age Group", "LowGroup");
				for( g = iLowGroup ; g <= iHighGroup ; g++ )
				{
					int iAgeGroup = CCalculate::GroupAge( g, strAgeCategory, &prop, nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);

					if( iPreviousAgeGroup != iAgeGroup )
					{
						html.AddSelectBox( CConvert::itoa(iAgeGroup), CConvert::itoa(iAgeGroup), CConvert::itoa(iLowGroup) );
						iPreviousAgeGroup = iAgeGroup;
					}
				}
				html.EndSelectBox();

				iPreviousAgeGroup = -1;
				html.StartSelectBox("To Age Group", "HighGroup");
				for( g = iLowGroup ; g <= iHighGroup ; g++ )
				{
					int iAgeGroup = CCalculate::GroupAge( g, strAgeCategory, &prop, nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);

					if( iPreviousAgeGroup != iAgeGroup )
					{
						html.AddSelectBox( CConvert::itoa(iAgeGroup), CConvert::itoa(iAgeGroup), CConvert::itoa(iHighGroup) );
						iPreviousAgeGroup = iAgeGroup;
					}
				}
				html.EndSelectBox();
				html.HorizontalRule();

				html.CheckBox("Specify Sex", "", "SpecifySex", "1", "0");
				html.RadioButton("Sex", "Male", "Sex", "M", "");
				html.RadioButton("", "Female", "Sex", "W", "");
				html.HorizontalRule();


				html.EditIntBox("Into Division", "Division", iDivision);

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();
			}
			else
			{
				html << _T("No Groups Available\r\n");
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

void CWebAthlExtension::UtilitiesSplitDivisionByAgeGroupExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szLowGroup,
										  LPTSTR szHighGroup,
										  LPTSTR szSpecifySex,
										  LPTSTR szSex,
										  LPTSTR szDivision,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			int nMaxJunior = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
			int nMinVeteran = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
			int nJuniorGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
			int nVeteranGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

			int iLowGroup = atoi(szLowGroup);
			int iHighGroup = atoi(szHighGroup);
			int iSpecifySex = atoi(szSpecifySex);

			CString strAgeCategory;

			// maps key-value pairs.
			// this map, maps an int key to an int value.
			CMap<int,int,int,int> map;

			if( atoi(szDivision) > 0 )
			{
				CPersonSet rsPerson( &db );

				strSQL.Format( "SELECT Person.* FROM ParticipantForSeries, Person WHERE Person.PersonID = ParticipantForSeries.PersonID AND Person.dobDAY IS NOT NULL AND Person.dobMONTH IS NOT NULL AND Person.dobYEAR IS NOT NULL AND SeriesID = %s ORDER BY Person.dobYEAR , Person.dobMONTH , Person.dobDAY ", szSeriesID );
				rsPerson.Open(CRecordset::forwardOnly, strSQL );

				COleDateTime today = COleDateTime::GetCurrentTime();

				CString strPersonIDList;
				int nPersonIDListSize = 0;

				while( !rsPerson.IsEOF( ) )
				{
					bool bAddToList = false;

					int iAgeGroup = CCalculate::GroupAge( 
											CCalculate::YearDiff(
													rsPerson.m_dobDAY,
													rsPerson.m_dobMONTH,
													rsPerson.m_dobYEAR,
													today.GetDay( ),
													today.GetMonth( ),
													today.GetYear( )),
											strAgeCategory, 
											&prop, nMaxJunior, nMinVeteran, nJuniorGroup, nVeteranGroup);

					if( (iAgeGroup >= iLowGroup) && (iAgeGroup <= iHighGroup) )
					{
						if( iSpecifySex )
						{
							if( !_tcscmp(szSex, rsPerson.m_Sex) )
							{
								bAddToList = true;
							}
						}
						else
						{
							bAddToList = true;
						}
					}

					if( bAddToList )
					{
						if( nPersonIDListSize > 0 )
							strPersonIDList += _T(" , ");
						else
							strPersonIDList += _T(" ( ");

						strPersonIDList += CConvert::itoa(rsPerson.m_PersonID);

						nPersonIDListSize++;

						map.SetAt(rsPerson.m_PersonID, iAgeGroup ); 
					}

					rsPerson.MoveNext( );
				}

				if( nPersonIDListSize > 0 )
					strPersonIDList += _T(" ) ");

				rsPerson.Close( );


				if( nPersonIDListSize > 0 )
				{
					// Update the DivisionSupposedTo of all People in ParticipantForSeries between the specified GroupIDs
					strSQL.Format( "UPDATE ParticipantForSeries SET DivisionSupposedTo = %s WHERE SeriesID = %s AND PersonID IN %s ", szDivision, szSeriesID, strPersonIDList );
					db.ExecuteSQL( strSQL );
					//html << strSQL << "<BR>\r\n" ;

					// Get the List of People with their New Division between the specified GroupIDs
					strSQL.Format( "SELECT * FROM ParticipantForSeries WHERE SeriesID = %s AND PersonID IN %s ", szSeriesID, strPersonIDList );
					CParticipantForSeriesSet rs( &db );
					rs.Open(CRecordset::forwardOnly, strSQL );

					if( !rs.IsEOF( ) )
					{
						int iAgeGroup;

						while( !rs.IsEOF( ) )
						{
							html << _T("Modified Person, <B>");
							html << _T(CConvert::itoa(rs.m_PersonID));
							html << _T("</B> in Age Group <B>");

							if( iSpecifySex )
								html << _T(szSex);

							if( map.Lookup( rs.m_PersonID , iAgeGroup ) )
								html << _T(CConvert::itoa(iAgeGroup));
							else
								html << _T(CConvert::itoa(0));

							html << _T("</B> to Division <B>");
							html << _T(CConvert::itoa(rs.m_DivisionSupposedTo));
							html << _T("</B><BR>\r\n");

							rs.MoveNext( );
						}
					}
					else
					{
						html << _T("No Participants in Group\r\n");
					}
					rs.Close( );
				}
				else
				{
					html << _T("No Participants in Group\r\n");
				}
			}
			else
			{
				html << _T("Invalid Division\r\n");
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

void CWebAthlExtension::UtilitiesDeleteResultsForm(CHttpServerContext* pCtxt,
											  LPTSTR szSeriesID,
											  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesDeleteResultsExecute;

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

void CWebAthlExtension::UtilitiesDeleteResultsExecute(CHttpServerContext* pCtxt,
										  LPTSTR szSeriesID,
										  LPTSTR szEventID,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesDeleteResultsExecute;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		if(_tcscmp(szSubmit,CHtmlKey::Delete))
			html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		else
			html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);

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


			strSQL.Format( html.GetNonEditEventBoxDetails(atoi(szEventID)) );

			CEventETypLocSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );


			html.StartForm("Delete Event Results", "");

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
				strSQL.Format( "SELECT COUNT(*) AS Total FROM Results WHERE SeriesID = %s AND EventID = %s", szSeriesID, szEventID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html.NonEditInt("Participants", rsCount.m_Total );

				html.EndForm();

				html.StartForm("", CPage::UtilitiesDeleteResultsExecute);

				html.HiddenText("SeriesID", szSeriesID );
				html.HiddenText("EventID", szEventID );

				CString strMsg;
				strMsg.Format("Deleting <B>%s</B> Participants",CConvert:: itoa(rsCount.m_Total));

				html.NonEditText(strMsg, "" );
				html.NonEditText("Are you Sure?", html.InLineInput("submit","Submit",CHtmlKey::Delete,0,"") );

				html.EndForm();

				rsCount.Close( );
			}
			else
			{
				html.EndForm();

				strSQL.Format( "SELECT COUNT(*) AS Total FROM Results WHERE SeriesID = %s AND EventID = %s", szSeriesID, szEventID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html << _T("Deleting <B>");
				html << _T( CConvert::itoa(rsCount.m_Total) );
				html << _T("</B> Participants.<BR>\r\n");
				html << _T("<BR>\r\n");
				html << _T("<BR>\r\n");

				rsCount.Close( );

				strSQL.Format( "DELETE FROM Results WHERE SeriesID = %s AND EventID = %s", szSeriesID, szEventID ); 
				db.ExecuteSQL( strSQL );

				strSQL.Format( "SELECT COUNT(*) AS Total FROM Results WHERE SeriesID = %s AND EventID = %s", szSeriesID, szEventID );
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

void CWebAthlExtension::UtilitiesFixDuplicatePersonForm(CHttpServerContext* pCtxt,
											   LPTSTR szPersonID,
											   LPTSTR szDupPersonID,
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
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		if( atoi(szPersonID) != atoi(szDupPersonID) )
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				html.StartForm("Fix Duplicate Person", CPage::UtilitiesFixDuplicatePersonExecute);

				CPersonSet rs( &db );

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
				rs.Open(CRecordset::dynaset, strSQL );

				html.NonEditInt("Person ID", rs.m_PersonID);
				html.HiddenInt("PersonID", rs.m_PersonID);

				html.NonEditText("Last Name", rs.m_LastName);
				html.NonEditText("First Name", rs.m_FirstName);
				html.NonEditText("Middle Name", rs.m_MiddleName);

				html.NonEditDateBox("Date of Birth", rs.m_dobDAY, rs.m_dobMONTH, rs.m_dobYEAR);
				html.HorizontalRule();

				rs.Close( );

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szDupPersonID );
				rs.Open(CRecordset::dynaset, strSQL );

				html.NonEditInt("Duplicate Person ID", rs.m_PersonID);
				html.HiddenInt("dupPersonID", rs.m_PersonID);

				html.NonEditText("Last Name", rs.m_LastName);
				html.NonEditText("First Name", rs.m_FirstName);
				html.NonEditText("Middle Name", rs.m_MiddleName);

				html.NonEditDateBox("Date of Birth", rs.m_dobDAY, rs.m_dobMONTH, rs.m_dobYEAR);
				html.HorizontalRule();


				html.RadioButton("Duplicate Person", "Delete", "DuplicatePerson", "Delete", "Rename");
				html.RadioButton("", "Rename To:", "DuplicatePerson", "Rename", "Rename");

				html.EditTextBoxSmall("Last Name", "LastName", "xxxx");
				html.EditTextBoxSmall("First Name", "FirstName", "xxxx");
				html.HorizontalRule();

				html.HiddenText("OnError", "Delete");
				html.NonEditText("On Error", "Delete Duplicate From:");

				CFixDuplicateOption enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					if( enumList.GetHidden() )
					{
						html.CheckBox("", enumList.GetDescription(), "Option", 
							CConvert::dwtoa(dwEnum), 
							CConvert::dwtoa(enumList.GetDefaultSelect()) );
					}
				}
				html.HorizontalRule();

				html.SubmitButton(CHtmlKey::Run);

				html.EndForm();

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
			html << _T("The Specified Duplicate Person <B>");
			html << _T(szDupPersonID);
			html << _T("</B> is the same Person <B>");
			html << _T(szPersonID);
			html << _T("</B>. Unable to Proceed with Duplicate removal.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::UtilitiesFixDuplicatePersonExecute(CHttpServerContext* pCtxt,
										   LPTSTR szPersonID,
										   LPTSTR szDupPersonID,
										   LPTSTR szDuplicatePerson,
										   LPTSTR szLastName,
										   LPTSTR szFirstName,
										   LPTSTR szOnError,
										   LPTSTR szOption,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);
		html.EndMenu();

		DWORD dwOption = CCSV::GetBitMask(szOption, CWebAthlExtension::chIsapiDelimiter);

		if( CFixDuplicateOption::IsMember( dwOption, CFixDuplicateOption::DeleteSecurityPerson ) )
		{
			dwOption |= CFixDuplicateOption::DeleteSecurityPersonSeries;
		}

		if( atoi(szPersonID) != atoi(szDupPersonID) )
		{

			CString strTable;

			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CFixDuplicateOption enumList;
				DWORD dwEnum = enumList.Enumerator( );

				while( enumList.GetNext( &dwEnum ) )
				{
					strTable = enumList.GetName( );

					try
					{
						strSQL.Format( "SELECT COUNT(*) AS Total FROM %s WHERE PersonID = %s ", strTable, szDupPersonID );
						CCountResultSet rsCount( &db );
						rsCount.Open(CRecordset::dynaset, strSQL );

						int iRowsTotal = rsCount.m_Total;

						rsCount.Close( );

						int iMaxCommentNo = 0;

						int iComments = (!strTable.Compare("PersonComments"));

						if( iComments )
						{
							strSQL.Format( "SELECT MAX(CommentNo) AS Total FROM PersonComments WHERE PersonID = %s ", szPersonID );
							rsCount.Open(CRecordset::dynaset, strSQL );

							if ( !rsCount.IsEOF( ) ) 
								if ( !rsCount.IsFieldNull( &rsCount.m_Total ) ) 
									iMaxCommentNo = rsCount.m_Total;

							rsCount.Close( );
						}

						if ( iRowsTotal > 0 ) 
						{
							if( iComments )
								strSQL.Format( "SELECT PersonID, CommentNo AS Val FROM %s WHERE PersonID = %s ", strTable, szDupPersonID );
							else
								strSQL.Format( "SELECT PersonID, PersonID AS Val FROM %s WHERE PersonID = %s ", strTable, szDupPersonID );
							
							CDupPersonSet rs( &db );

							rs.Open(CRecordset::dynaset, strSQL );

							int iPersonID = atoi(szPersonID);

							int iDelOnError = (!_tcscmp( szOnError, "Delete" ));

							int iRowsUpdated = 0;
							int iRowsDeleted = 0;
							int iRowsLeave = 0;

							while( !rs.IsEOF( ) && ((iRowsUpdated + iRowsDeleted + iRowsLeave) < (iRowsTotal)) )
							{

								if( !rs.IsDeleted( ) )
								{

									try
									{
										rs.Edit( );

										rs.m_PersonID = iPersonID;

										if( iComments )
											rs.m_Val += iMaxCommentNo;

										if( !rs.CanUpdate( ) )
											html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
										if( !rs.Update( ) )
										{
											html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
											iRowsUpdated++;
										}
										else
										{
											iRowsUpdated++;
										}
									}
									catch (CDBException* pEx)
									{
										rs.CancelUpdate( );
			
										html << pEx;

										if ( iDelOnError && enumList.IsMember( dwOption, dwEnum ) )
										{
											try
											{
												rs.Delete( );

												iRowsDeleted++;
											}

											catch (CDBException* pEx)
											{
												html << pEx;
												iRowsLeave++;

												pEx->Delete();
											}
										}
										else
										{
											iRowsLeave++;
										}

										pEx->Delete();
									}

								}
								rs.MoveNext( );

							}
							rs.Close( );

							if(iRowsUpdated)
							{
								html << _T("Moved <B>");
								html << _T(CConvert::itoa(iRowsUpdated));
								html << _T("</B> of <B>");
								html << _T(CConvert::itoa(iRowsTotal));
								html << _T("</B> <B>");
								html << _T(strTable);
								html << _T("</B> for Person <B>");
								html << _T(szDupPersonID);
								html << _T("</B> to Person <B>");
								html << _T(szPersonID);
								html << _T("</B><BR>\r\n");
							}

							if(iRowsLeave || iRowsDeleted)
							{
								html << _T("Unable to move <B>");
								html << _T(CConvert::itoa(iRowsLeave + iRowsDeleted));
								html << _T("</B> of <B>");
								html << _T(CConvert::itoa(iRowsTotal));
								html << _T("</B> <B>");
								html << _T(strTable);
								html << _T("</B> for Person <B>");
								html << _T(szDupPersonID);
								html << _T("</B><BR>\r\n");
							}

							if(iRowsDeleted)
							{
								html << _T("Deleted <B>");
								html << _T(CConvert::itoa(iRowsDeleted));
								html << _T("</B> of <B>");
								html << _T(CConvert::itoa(iRowsTotal));
								html << _T("</B> <B>");
								html << _T(strTable);
								html << _T("</B> for Person <B>");
								html << _T(szDupPersonID);
								html << _T("</B><BR>\r\n");
							}

						}

					}
					catch (CDBException* pEx)
					{
						html << pEx;

						pEx->Delete();
					}

				}


				try
				{
					strTable = _T("Person");

					strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szDupPersonID );
					CPersonSet rsPerson( &db );
					rsPerson.Open(CRecordset::dynaset, strSQL );

					if ( !rsPerson.IsEOF( ) )
					{
						if (!_tcscmp( szDuplicatePerson, "Delete" ))
						{
							rsPerson.Delete( );
							html << _T("Deleted Person, <B>");
							html << _T(szDupPersonID);
							html << _T("</B><BR>\r\n");
						}
						else
						{
							rsPerson.Edit( );

							if( _tcslen( szLastName ) > 0 )
								rsPerson.m_LastName = szLastName;
							else
								rsPerson.SetFieldNull( &rsPerson.m_LastName, TRUE );

							if( _tcslen( szFirstName ) > 0 )
								rsPerson.m_FirstName = szFirstName;
							else
								rsPerson.SetFieldNull( &rsPerson.m_FirstName, TRUE );

							rsPerson.SetFieldNull( &rsPerson.m_MiddleName, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_dobDAY, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_dobMONTH, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_dobYEAR, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Sex, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Address1, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Address2, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Town, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_State, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Country, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_PostCode, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_PhoneHm, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_PhoneWk, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Fax, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_Mobile, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_email, TRUE );
							rsPerson.SetFieldNull( &rsPerson.m_ContactPersonID, TRUE );

							if( !rsPerson.CanUpdate( ) )
								html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
							if( !rsPerson.Update( ) )
								html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
							else
							{
								html << _T("Modified Person, <B>");
								html << _T(szDupPersonID);
								html << _T("</B><BR>\r\n");
							}
						}
					}
					rsPerson.Close( );
				}
				catch (CDBException* pEx)
				{
					html << pEx;

					pEx->Delete();
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
			html << _T("The Specified Duplicate Person <B>");
			html << _T(szDupPersonID);
			html << _T("</B> is the same Person <B>");
			html << _T(szPersonID);
			html << _T("</B>. Unable to Proceed with Duplicate removal.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::UtilitiesRebuildAgeGroupsForm(CHttpServerContext* pCtxt,
												 LPTSTR szSeriesID,
												 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Utilities) )
	{
		auth.m_strFrwdLink = CPage::UtilitiesRebuildAgeGroupsExecute;

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

			if( !rsSeries.IsEOF( ) )
			{
				html.StartForm("Rebuild Age Groups", auth.m_strFrwdLink);
				html.HiddenText("SeriesID", szSeriesID);

				html.NonEditText("Series", rsSeries.m_SeriesDescription);				
				html.HorizontalRule();

				html.CheckBox("Tables",	"Results",				"doResults",	"1", "1");
				html.CheckBox("",		"Pre-Event Results",	"doPreResults",	"1", "0");
				html.CheckBox("",		"Post-Event Results",	"doPostResults","1", "0");

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

void CWebAthlExtension::AgeGroupsRebuild(CHtmlWriter* pHtml,
										CHttpServerProperties* pProp,
										LPCTSTR szResultsTable,
										int iSeriesID)
{
	int iMaxJunior = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
	int iMinVeteran = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
	int iJuniorGroup = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
	int iVeteranGroup = atoi(pProp->GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

	try
	{
		CString strConnect = pProp->GetDefaultConnect();
		CString strSQL;
		CString strSQLtmp;

		CDatabase db;
		CDatabase dbUpdate;

		db.OpenEx( strConnect, CDatabase::noOdbcDialog );
		dbUpdate.OpenEx( strConnect, CDatabase::noOdbcDialog );

		int iRowsAffected = 0;

		CUtil::LoadLongResource(strSQLtmp, IDS_SQL_AGEGROUPS);
		strSQL.Format( strSQLtmp, szResultsTable, iSeriesID ); 
		CAgeGroupSet rs( &db );
		rs.Open(CRecordset::forwardOnly, strSQL );

		int iAgeGroup;
		int iAge;
		CString strAgeCategory;
		CString strAgeGroup;

		CUtil::LoadLongResource(strSQLtmp, IDS_SQL_UPDATEAGEGROUPS);

		while( !rs.IsEOF( ) )
		{
			int nDateAgeDAY = rs.m_DateAgeDAY;
			int nDateAgeMONTH = rs.m_DateAgeMONTH;
			int nDateAgeYEAR = rs.m_DateAgeYEAR;

			if( rs.IsFieldNull( &rs.m_DateAgeDAY ) ||
				rs.IsFieldNull( &rs.m_DateAgeMONTH ) ||
				rs.IsFieldNull( &rs.m_DateAgeYEAR ) ||
				rs.m_DateAgeDAY == 0 ||
				rs.m_DateAgeMONTH == 0 ||
				rs.m_DateAgeYEAR == 0 ) 
			{
				nDateAgeDAY = rs.m_DateDAY;
				nDateAgeMONTH = rs.m_DateMONTH;
				nDateAgeYEAR = rs.m_DateYEAR;
			}

			iAge = CCalculate::YearDiff(rs.m_dobDAY,
										rs.m_dobMONTH,
										rs.m_dobYEAR,
										nDateAgeDAY,
										nDateAgeMONTH,
										nDateAgeYEAR);

			iAgeGroup = CCalculate::GroupAge(iAge,
											 strAgeCategory,
											 pProp,
											 iMaxJunior,
											 iMinVeteran,
											 iJuniorGroup,
											 iVeteranGroup);

//			if( (iAgeGroup != rs.m_AgeGroup) && 
//				!(CRecordsetEx::IsItemNull(iAgeGroup) && rs.IsFieldNull( &rs.m_AgeGroup ))   
//			)

//			If DoB exists, AgeGroup is re-calculated,
//			If DoB doesn't exist AND Agegroup doesn't exist, AgeGroup set to Default (999),
//			If DoB doesn't exist AND Agegroup does exist, AgeGroup is not re-calculated.

			if( ( (iAgeGroup != rs.m_AgeGroup) && !CRecordsetEx::IsItemNull( iAge ) ) ||
				( (iAgeGroup != rs.m_AgeGroup) && 
				  CRecordsetEx::IsItemNull( iAge ) && rs.IsFieldNull( &rs.m_AgeGroup ) )
			)
			{
				if( CRecordsetEx::IsItemNull(iAgeGroup) )
					strAgeGroup = CRecordsetEx::m_szNullField;
				else
					strAgeGroup = CConvert::itoa(iAgeGroup);

				strSQL.Format( strSQLtmp, szResultsTable, 
					strAgeGroup,
					rs.m_SeriesID,
					rs.m_EventID,
					rs.m_PersonID ); 

				try
				{
					dbUpdate.ExecuteSQL( strSQL );

					*pHtml << _T( "Updated Person : <B>" );
					*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
					*pHtml << _T( "</B>, in Series : <B>" );
					*pHtml << _T( CConvert::itoa(rs.m_SeriesID) );
					*pHtml << _T( "</B>, on Event : <B>" );
					*pHtml << _T( CConvert::itoa(rs.m_EventID) );
					*pHtml << _T( "</B> from AgeGroup : <B>" );
					*pHtml << _T( CConvert::itoa(rs.m_AgeGroup) );
					*pHtml << _T( "</B> to AgeGroup : <B>" );
					*pHtml << _T( strAgeGroup );
					*pHtml << _T( "</B><BR>\r\n" );

					iRowsAffected++;
				}
				catch (CDBException* pEx)
				{
					*pHtml << pEx;

					pEx->Delete();
				}
			}

			rs.MoveNext( );
		}
		rs.Close( );

		*pHtml << _T( "AgeGroup Update Complete on <B>" );
		*pHtml << _T( szResultsTable );
		*pHtml << _T( "</B> Table.<BR>\r\n(<B>" );
		*pHtml << _T( CConvert::itoa(iRowsAffected) );
		*pHtml << _T( "</B> row(s) affected)<BR>\r\n<BR>\r\n" );

		db.Close( );
		dbUpdate.Close( );
	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		pEx->Delete();
	}
}

void CWebAthlExtension::UtilitiesRebuildAgeGroupsExecute(CHttpServerContext* pCtxt,
											 LPTSTR szSeriesID,
											 LPTSTR szDoResults,
											 LPTSTR szDoPreResults,
											 LPTSTR szDoPostResults,
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
		html.WritePageMenuItem(auth.m_strBackLink, "Utilities Menu", 0);
		html.EndMenu();

		int iDoResults = atoi(szDoResults);
		int iDoPreResults = atoi(szDoPreResults);
		int iDoPostResults = atoi(szDoPostResults);

		if(iDoResults)
		{
			AgeGroupsRebuild(&html, &prop, "Results", atoi(szSeriesID));
		}

		if(iDoPreResults)
		{
			AgeGroupsRebuild(&html, &prop, "PreResults", atoi(szSeriesID));
		}

		if(iDoPostResults)
		{
			AgeGroupsRebuild(&html, &prop, "PostResults", atoi(szSeriesID));
		}

		html.EndPage();
		html.EndContent();
	}
}

