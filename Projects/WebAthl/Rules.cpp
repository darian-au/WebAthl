// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SeriesSet.h"
#include "CountResultSet.h"

#include "RulesSet.h"
#include "RuleSubTypeSet.h"
#include "RuleTypeSet.h"

///////////////////////////////////////////////////////////////////////
// Rules

void CWebAthlExtension::RulesMenu(CHttpServerContext* pCtxt,
										LPTSTR szSubmit,
										LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Rules) )
	{
		CString strSeriesID = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

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


//			if(rsSeries.m_Handicapped)
//			{
				if( auth.HasPermission(CModule::Security) )
					html.WritePageMenuItem(CPage::RulesSetTypesExecute, "Set Rule Types", 0);


				CCountResultSet rsCount( &db );

				strSQLtmp.Empty();

				strSQLtmp += _T("SELECT COUNT(*) AS Total ");
				strSQLtmp += _T(" FROM RuleType, RuleSubType ");
				strSQLtmp += _T(" WHERE RuleType.RuleTypeID = RuleSubType.RuleTypeID ");
				strSQLtmp += _T(" AND RuleType.RuleTypeDescription = '%s' ");

				CString strMenuItem;

				CRuleType ruleType;
				DWORD dwEnum = ruleType.Enumerator( );
				while( ruleType.GetNext( &dwEnum ) )
				{
					strSQL.Format( strSQLtmp, ruleType.GetName() );
					rsCount.Open(CRecordset::forwardOnly, strSQL );

					if( rsCount.m_Total )
					{
						strMenuItem.Format("Add %s Rule", ruleType.GetName());
						html.WritePageMenuItem(CPage::RulesAddExecute, strMenuItem, 1, ruleType.GetName());
					}
					rsCount.Close( );
				}

				html.EndMenu();

	
				strSQL.Format( "SELECT * FROM RuleType ORDER BY RuleTypeDescription");
				CRuleTypeSet rsRuleType( &db );
				rsRuleType.Open(CRecordset::dynaset, strSQL );

				while( !rsRuleType.IsEOF( ) )
				{
					strSQL.Format( "SELECT COUNT(*) AS Total FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d ", strSeriesID, rsRuleType.m_RuleTypeID);
					CCountResultSet rsCount( &db );
					rsCount.Open(CRecordset::dynaset, strSQL );

					strSQL.Format( "SELECT * FROM Rules WHERE SeriesID = %s AND RuleTypeID = %d ORDER BY Law", strSeriesID, rsRuleType.m_RuleTypeID);
					CRulesSet rsRules( &db );
					rsRules.Open(CRecordset::dynaset, strSQL );

					if( !rsRules.IsEOF( ) )
					{
						strSQL.Format( "SELECT * FROM RuleSubType WHERE RuleTypeID = %d ORDER BY RuleSubTypeDescription", rsRuleType.m_RuleTypeID);
						CRuleSubTypeSet rsRuleSubType( &db );
						rsRuleSubType.Open(CRecordset::dynaset, strSQL );

						html.TableHeader( (CConvert::itoa(rsCount.m_Total) + " " + rsRuleType.m_RuleTypeDescription + " Rules"));

						html.RulesHeader("RuleID","","Rule Sub Type","Rule","","");

						while( !rsRules.IsEOF( ) )
						{
							html.StartInLineForm("", CPage::RulesEditExecute );
							html.RuleTypeSel(
								"SeriesID",
								strSeriesID,
								"RuleID",
								rsRules.m_RuleID,			
								"RuleTypeID",
								rsRules.m_RuleTypeID,
								"");

							html.RuleSubTypeSel("RuleSubTypeID");

							if( !rsRuleSubType.IsEOF( ) )
							{
								html.AddSelectBox("","0",CConvert::itoa(rsRules.m_RuleSubTypeID));

								while( !rsRuleSubType.IsEOF( ) )
								{
									html.AddSelectBox(
  										rsRuleSubType.m_RuleSubTypeDescription,
										CConvert::itoa(rsRuleSubType.m_RuleSubTypeID),
										CConvert::itoa(rsRules.m_RuleSubTypeID));

									rsRuleSubType.MoveNext( );
								}
								rsRuleSubType.MoveFirst( );
							}
							else
								html.AddSelectBox("No Rule SubTypes Available","0","0");

							html.RuleSubmit("Law",rsRules.m_Law,CHtmlKey::Save,CHtmlKey::Delete);
							html.EndInLineForm();

							rsRules.MoveNext( );
						}
						html.TableFooter();

						rsRuleSubType.Close( );
					}
					rsCount.Close( );
					rsRules.Close( );
					rsRuleType.MoveNext( );
				}
				rsRuleType.Close( );
//			}
//			else
//			{
//				html.EndMenu();
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

void CWebAthlExtension::RulesEditExecute(CHttpServerContext* pCtxt,
								 LPTSTR szSeriesID,
								 LPTSTR szRuleID,
								 LPTSTR szRuleTypeID,
								 LPTSTR szRuleSubTypeID,
								 LPTSTR szLaw,
								 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Rules) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RulesMenu, "Rules Menu", 1, strSeriesID);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM RuleType WHERE RuleTypeID = %s ", szRuleTypeID);
			CRuleTypeSet rsType( &db );
			rsType.Open(CRecordset::dynaset, strSQL );
			
			CString strRuleType = rsType.m_RuleTypeDescription;
			rsType.Close( );


			strSQL.Format( "SELECT * FROM Rules WHERE SeriesID = %s AND RuleID = %s ", szSeriesID, szRuleID );
			CRulesSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				rs.m_SeriesID = atoi(szSeriesID);
				rs.m_RuleTypeID = atoi(szRuleTypeID);
				rs.m_RuleSubTypeID = atoi(szRuleSubTypeID);
				rs.m_Law = atoi(szLaw);

		
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Rule, <B>");
					html << _T(strRuleType);
					html << _T("</B><BR>\r\n");
				}
			}

			if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Rule, <B>");
				html << _T(strRuleType);
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

void CWebAthlExtension::RulesAddExecute(CHttpServerContext* pCtxt,
								LPTSTR szInit, 
								LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Rules) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);
		CString strRuleType = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RulesMenu, "Rules Menu", 1, strSeriesID);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
			CString strSQLtmp;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );



			strSQL.Format( "SELECT * FROM RuleType WHERE RuleTypeDescription = '%s' ", strRuleType);
			CRuleTypeSet rsRuleType( &db );
			rsRuleType.Open(CRecordset::forwardOnly, strSQL );
			
			int iRuleTypeID = rsRuleType.m_RuleTypeID;

			rsRuleType.Close( );

			strSQLtmp += _T("SELECT %s ");
			strSQLtmp += _T("FROM Rules, RuleType ");
			strSQLtmp += _T("WHERE	RuleType.RuleTypeID = Rules.RuleTypeID ");
			strSQLtmp += _T("AND (Rules.SeriesID = %d ) ");
			strSQLtmp += _T("AND (RuleType.RuleTypeDescription = '%s' ) ");

			strSQL.Format( strSQLtmp, " COUNT(*) AS Total ", atoi(strSeriesID), strRuleType );

			CCountResultSet rsCount( &db );
			rsCount.Open(CRecordset::forwardOnly, strSQL );
			int iRuleCount = rsCount.m_Total;
			rsCount.Close( );


			CRuleType ruleType;
			DWORD dwCode = ruleType.FindByName(strRuleType);

			if( iRuleCount < CRuleType::GetMax(dwCode) )
			{
				strSQL.Format( "SELECT * FROM Rules");
				CRulesSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.AddNew( );

				rs.m_SeriesID = atoi(strSeriesID);
				rs.m_RuleTypeID = iRuleTypeID;
				rs.m_RuleSubTypeID = 0;
				rs.m_Law = 0;
		
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Rule, <B>");
					html << _T(CRuleType::GetName(dwCode));
					html << _T("</B><BR>\r\n");
				}

				rs.Close( );
			}
			else
			{
				html << _T("Maximum <B>");
				html << _T(strRuleType);
				html << _T("</B> Rules Count Reached.<BR>\r\n");
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

void CWebAthlExtension::RulesSetTypesExecute(CHttpServerContext* pCtxt,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
		CString strSeriesID = html.GetCookie(CHtmlKey::SeriesID);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::RulesMenu, "Rules Menu", 1, strSeriesID);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			DWORD dwEnum;

			CRuleType ruleType;
			dwEnum = ruleType.Enumerator( );
			while( ruleType.GetNext( &dwEnum ) )
			{
				strSQL.Format( "SELECT * FROM RuleType WHERE RuleTypeDescription = '%s'", ruleType.GetName() );
				CRuleTypeSet rsRuleType( &db );
				rsRuleType.Open(CRecordset::dynaset, strSQL );

				if( rsRuleType.IsEOF( ) )
					rsRuleType.AddNew( );
				else
					rsRuleType.Edit( );


				rsRuleType.m_RuleTypeDescription = ruleType.GetName();

		
				if( !rsRuleType.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsRuleType.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Set Rule, <B>");
					html << _T(ruleType.GetName());
					html << _T("</B><BR>\r\n");
				}

				rsRuleType.Close( );
			}



			CRuleSubType ruleSubType;
			dwEnum = ruleSubType.Enumerator( );
			while( ruleSubType.GetNext( &dwEnum ) )
			{
				strSQL.Format( "SELECT * FROM RuleType WHERE RuleTypeDescription = '%s' ", CRuleType::GetName(ruleSubType.GetTypeCode()) );
				CRuleTypeSet rsType( &db );
				rsType.Open(CRecordset::dynaset, strSQL );
			
				int iRuleTypeID = rsType.m_RuleTypeID;

				rsType.Close( );


				strSQL.Format( "SELECT * FROM RuleSubType WHERE RuleSubTypeDescription = '%s'", ruleSubType.GetName() );
				CRuleSubTypeSet rsRuleSubType( &db );
				rsRuleSubType.Open(CRecordset::dynaset, strSQL );

				if( rsRuleSubType.IsEOF( ) )
					rsRuleSubType.AddNew( );
				else
					rsRuleSubType.Edit( );


				rsRuleSubType.m_RuleSubTypeDescription = ruleSubType.GetName();
				rsRuleSubType.m_RuleTypeID = iRuleTypeID;

		
				if( !rsRuleSubType.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsRuleSubType.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Set Rule, <B>");
					html << _T(CRuleType::GetName(ruleSubType.GetTypeCode()));
					html << _T("</B> : <B>");
					html << _T(ruleSubType.GetName());
					html << _T("</B><BR>\r\n");
				}

				rsRuleSubType.Close( );
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



