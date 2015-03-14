// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SecurityPersonSet.h"
#include "SecurityRoleSet.h"

#include "PersonSet.h"
#include "FinancialSet.h"
#include "RegistrationTypeSet.h"
#include "OrganisationSet.h"

///////////////////////////////////////////////////////////////////////
// Financial

void CWebAthlExtension::FinancialMenu(CHttpServerContext* pCtxt,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Financial) )
	{
		auth.m_strHeading = "Financial";
		auth.m_strBackLink = CPage::FinancialMenu;

		html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SearchPersonForm, "Add Financial", 1, CPage::FinancialAddForm);
		html.WritePageMenuItem(CPage::SearchPersonForm, "Edit Financial", 1, CPage::FinancialEditForm);

		if(auth.HasPermission(CModule::RegistrationType))
		{
			html.WritePageMenuItem(CPage::RegistrationTypeEditForm, "Add Registration Type", 0);
			html.WritePageMenuItem(CPage::RegistrationTypeSelectForm, "Edit Registration Type", 1, CPage::RegistrationTypeEditForm);
		}

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::FinancialAddForm(CHttpServerContext* pCtxt,
										 LPTSTR szPersonID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Financial) )
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

			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
			CPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Financial WHERE PersonID = %s ORDER BY Year DESC", szPersonID );
			CFinancialSet rsFinc( &db );
			rsFinc.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM RegistrationType " );
			CRegistrationTypeSet rsRegType( &db );
			rsRegType.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Organisation ORDER BY OrgName " );
			COrganisationSet rsOrg( &db );
			rsOrg.Open(CRecordset::dynaset, strSQL );

			if( !rsPerson.IsFieldNull( &rsPerson.m_dobDAY ) &&
				!rsPerson.IsFieldNull( &rsPerson.m_dobMONTH ) &&
				!rsPerson.IsFieldNull( &rsPerson.m_dobYEAR ) )
			{
				if( !rsPerson.IsFieldNull( &rsPerson.m_FirstName ) &&
					!rsPerson.IsFieldNull( &rsPerson.m_LastName ) )
				{
					if( !rsRegType.IsEOF( ) )
					{
						if( !rsOrg.IsEOF( ) )
						{
							int iOrgID = 0;
							int iRegistrationTypeID = 0;
							int iMailListFlag = 1;

							if( !rsFinc.IsEOF( ) )
							{
								iOrgID = rsFinc.m_OrgID;
								iRegistrationTypeID = rsFinc.m_RegistrationTypeID;
								iMailListFlag = rsFinc.m_MailListFlag;
							}


							html.StartForm("Financial", CPage::FinancialAddExecute);

							html.NonEditText("Name", rsPerson.m_LastName + ", " + rsPerson.m_FirstName);				
							html.HiddenText("PersonID", szPersonID);

							if( !rsFinc.IsEOF( ) )
								html.NonEditInt("Last Renewed", rsFinc.m_Year);
							else
								html.NonEditText("Last Renewed","New Member");				
							html.HorizontalRule();

							html.DateBox("Renewal Date","DateRenewed");

							html.RadioButton("Mailing List", "Yes", "MailListFlag", "1", CConvert::itoa(iMailListFlag) );
							html.RadioButton("", "No", "MailListFlag", "0", CConvert::itoa(iMailListFlag));

							html.StartSelectBox("Registration Type", "RegistrationTypeID");

							while( !rsRegType.IsEOF( ) )
							{
								html.AddSelectBox(rsRegType.m_RegistrationDescription, CConvert::itoa(rsRegType.m_RegistrationTypeID), CConvert::itoa(iRegistrationTypeID) );
								rsRegType.MoveNext( );
							}
							html.EndSelectBox();

							strSQL.Format( "SELECT * FROM Organisation" );
							COrganisationSet rsPrimaryOrg( &db );
							rsPrimaryOrg.Open(CRecordset::dynaset, strSQL );

							if( !rsPrimaryOrg.IsEOF( ) )
							{
								html.NonEditText("Primary Organisation", rsPrimaryOrg.m_OrgName);	
							}
							else
							{
								html.NonEditText("Primary Organisation", "Invalid Organisation");
							}

							rsPrimaryOrg.Close( );

							html.StartSelectBox("Secondary Organisation", "OrgID");

							while( !rsOrg.IsEOF( ) )
							{
								html.AddSelectBox(rsOrg.m_OrgName, CConvert::itoa(rsOrg.m_OrgID), CConvert::itoa(iOrgID) );
								rsOrg.MoveNext( );
							}
							html.EndSelectBox();

							html.EditIntBox("Year Valid", "Year", CCalculate::GetCurrentYear( iRegistrationTypeID, strConnect ));				

							html.EditIntBox("Registration ID", "RegistrationID", atoi(szPersonID));				

							html.HorizontalRule();
							html.SubmitButton(CHtmlKey::Save);
							html.EndForm();
						}
						else
						{
							html << _T("No Organisations Available");
						}
					}
					else
					{
						html << _T("No Registration Types Available");
					}
				}
				else
				{
					html << _T("This Person is missing either a First or Last Name.  A Financial Person must have a First and Last Name." );
				}
			}
			else
			{
				html << _T("This Person does not have a valid Date of Birth.  A Financial Person must have a Date of Birth." );
			}
			
			rsOrg.Close( );
			rsRegType.Close( );
			rsPerson.Close( );
			rsFinc.Close( );

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

void CWebAthlExtension::FinancialAddExecute(CHttpServerContext* pCtxt,
									 LPTSTR szPersonID,
									 LPTSTR szDateRenewedDAY,
									 LPTSTR szDateRenewedMONTH,
									 LPTSTR szDateRenewedYEAR,
									 LPTSTR szMailListFlag,
									 LPTSTR szRegistrationTypeID,
									 LPTSTR szOrgID,
									 LPTSTR szYear,
									 LPTSTR szRegistrationID,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Financial) )
	{
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Financial Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Financial" );
			CFinancialSet rsFinc( &db );
			rsFinc.Open(CRecordset::dynaset, strSQL );

			rsFinc.AddNew( );

			rsFinc.m_PersonID = atoi(szPersonID);
			rsFinc.m_DateRenewedDAY = atoi(szDateRenewedDAY);
			rsFinc.m_DateRenewedMONTH = atoi(szDateRenewedMONTH);
			rsFinc.m_DateRenewedYEAR = atoi(szDateRenewedYEAR);
			rsFinc.m_MailListFlag = atoi(szMailListFlag);
			rsFinc.m_RegistrationTypeID = atoi(szRegistrationTypeID);
			rsFinc.m_Year = atoi(szYear);
			rsFinc.m_RegistrationID = atoi(szRegistrationID);
			rsFinc.m_OrgID = atoi(szOrgID);

		
			if( !rsFinc.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rsFinc.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Financial for Person, <B>");
				html << _T(szPersonID);
				html << _T("</B><BR>\r\n");
			}
			
			rsFinc.Close( );

			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );
			CSecurityPersonSet rsSecPer( &db );
			rsSecPer.Open(CRecordset::dynaset, strSQL );

			if ( rsSecPer.IsEOF( ) )
			{
				rsSecPer.AddNew( );

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
				CPersonSet rsPerson( &db );
				rsPerson.Open(CRecordset::dynaset, strSQL );


				strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleName = '%s' ", CAuthenticator::m_szMemberRole );
				CSecurityRoleSet rsRole( &db );
				rsRole.Open(CRecordset::dynaset, strSQL );

				CString strRoleName;
				int iRoleID = 0;

				if( !rsRole.IsEOF( ) )
				{
					strRoleName = rsRole.m_RoleName;
					iRoleID = rsRole.m_RoleID;
				}

				CString strAutoLoginName;
				CString strAutoPassword;

				CByteArray cbaCyPwd;

				strAutoLoginName.Format("%c%c%d",
					rsPerson.m_FirstName.GetAt(0),
					rsPerson.m_LastName.GetAt(0),
					rsPerson.m_PersonID);
				strAutoLoginName.MakeLower( );

				strAutoPassword.Format("%s%s%s",
					CConvert::itoa(rsPerson.m_dobDAY, 2),
					CConvert::itoa(rsPerson.m_dobMONTH, 2),
					CConvert::itoa(rsPerson.m_dobYEAR));


				CCryptByteArray* cbaPwd = new CCryptByteArray( strAutoPassword );

				cbaPwd->Init(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
							 atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

				cbaPwd->EnCrypt( );

				rsSecPer.m_PersonID = atoi(szPersonID);
				rsSecPer.m_LoginName = strAutoLoginName;

				if( iRoleID )
					rsSecPer.m_RoleID = iRoleID;

				cbaPwd->Copy( &(rsSecPer.m_Password) );

				if( !rsSecPer.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsSecPer.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Set Default Password for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");

					if( iRoleID )
					{
						html << _T("Added Person, <B>");
						html << _T(szPersonID);
						html << _T("</B>");

						html << _T(" to Security Role, <B>");
						html << _T( CAuthenticator::m_szMemberRole );
						html << _T("</B><BR>\r\n");
					}
				}
				rsPerson.Close( );
				rsRole.Close( );
			}
			rsSecPer.Close( );
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

void CWebAthlExtension::FinancialEditForm(CHttpServerContext* pCtxt,
										  LPTSTR szPersonID,
										  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Financial) )
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


			COleDateTime t = COleDateTime::GetCurrentTime();


			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
			CPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Financial WHERE PersonID = %s ORDER BY Year DESC", szPersonID );
			CFinancialSet rsFinc( &db );
			rsFinc.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM RegistrationType " );
			CRegistrationTypeSet rsRegType( &db );
			rsRegType.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Organisation ORDER BY OrgName " );
			COrganisationSet rsOrg( &db );
			rsOrg.Open(CRecordset::dynaset, strSQL );

			if( !rsRegType.IsEOF( ) )
			{
				if( !rsOrg.IsEOF( ) )
				{
					html.StartForm("Financial", CPage::FinancialEditExecute);

					html.NonEditText("Name", rsPerson.m_LastName + ", " + rsPerson.m_FirstName);				
					html.HiddenText("PersonID", szPersonID);
					html.HorizontalRule();

					if( !rsFinc.IsEOF( ) )
					{
						int iFincStatus = CCalculate::Current( rsFinc.m_Year, rsFinc.m_RegistrationTypeID, strConnect );

						if( iFincStatus )
						{
							if( iFincStatus > 1 )
								html.NonEditText("Membership", "Future");				
							else
								html.NonEditText("Membership", "Current");				

							html.NonEditText("", CFormat::FormatRegistration(rsFinc.m_Year, rsFinc.m_RegistrationTypeID, strConnect) );				

							html.HorizontalRule();

							html.NonEditDateBox("Renewal Date",
										   rsFinc.m_DateRenewedDAY,
										   rsFinc.m_DateRenewedMONTH,
										   rsFinc.m_DateRenewedYEAR);

							html.RadioButton("Mailing List", "Yes", "MailListFlag", "1", CConvert::itoa(rsFinc.m_MailListFlag));
							html.RadioButton("", "No", "MailListFlag", "0", CConvert::itoa(rsFinc.m_MailListFlag));

							html.StartSelectBox("Registration Type", "RegistrationTypeID");

							while( !rsRegType.IsEOF( ) )
							{
								html.AddSelectBox(rsRegType.m_RegistrationDescription, CConvert::itoa(rsRegType.m_RegistrationTypeID), CConvert::itoa(rsFinc.m_RegistrationTypeID));
								rsRegType.MoveNext( );
							}

							html.EndSelectBox();
							html.HiddenInt("OldRegTypeID", rsFinc.m_RegistrationTypeID);

							strSQL.Format( "SELECT * FROM Organisation" );
							COrganisationSet rsPrimaryOrg( &db );
							rsPrimaryOrg.Open(CRecordset::dynaset, strSQL );

							if( !rsPrimaryOrg.IsEOF( ) )
							{
								html.NonEditText("Primary Organisation", rsPrimaryOrg.m_OrgName);	
							}
							else
							{
								html.NonEditText("Primary Organisation", "Invalid Organisation");
							}

							rsPrimaryOrg.Close( );

							html.StartSelectBox("Secondary Organisation", "OrgID");

							while( !rsOrg.IsEOF( ) )
							{
								html.AddSelectBox(rsOrg.m_OrgName, CConvert::itoa(rsOrg.m_OrgID), CConvert::itoa(rsFinc.m_OrgID));
								rsOrg.MoveNext( );
							}
							html.EndSelectBox();

							html.NonEditInt("Year Valid", rsFinc.m_Year);
							html.HiddenInt("Year", rsFinc.m_Year);

							html.NonEditInt("Registration ID", rsFinc.m_RegistrationID);

							html.HorizontalRule();
							html.ResetButton();
							html.SubmitButton(CHtmlKey::Save);
							html.SubmitButton(CHtmlKey::Delete);
						}
						else
						{
							html.NonEditText("Membership", "Lapsed");				
							html.NonEditText("", CFormat::FormatRegistration(rsFinc.m_Year, rsFinc.m_RegistrationTypeID, strConnect) );
							html.HorizontalRule();

							html.NonEditDateBox("Renewal Date",
										   rsFinc.m_DateRenewedDAY,
										   rsFinc.m_DateRenewedMONTH,
										   rsFinc.m_DateRenewedYEAR);

							switch( rsFinc.m_MailListFlag )
							{
								case TRUE  : html.NonEditText("Mailing List", "Yes"); 
									break;
								case FALSE : html.NonEditText("Mailing List", "No"); 
									break;
							}
							html.HiddenInt("MailListFlag", rsFinc.m_MailListFlag);

							strSQL.Format( "SELECT * FROM RegistrationType WHERE RegistrationTypeID = %d ", rsFinc.m_RegistrationTypeID );
							CRegistrationTypeSet rsRegType2( &db );
							rsRegType2.Open(CRecordset::dynaset, strSQL );
							

							if( !rsRegType2.IsEOF( ) )
							{
								html.NonEditText("Registration Type", rsRegType2.m_RegistrationDescription);
								html.HiddenInt("RegistrationTypeID", rsFinc.m_RegistrationTypeID);
							}
							else
							{
								html.NonEditText("Registration Type", "Invalid Registration Type");
								html.HiddenInt("RegistrationTypeID", 0);
							}
							html.HiddenInt("OldRegTypeID", rsFinc.m_RegistrationTypeID);

							rsRegType2.Close( );


							strSQL.Format( "SELECT * FROM Organisation" );
							COrganisationSet rsPrimaryOrg( &db );
							rsPrimaryOrg.Open(CRecordset::dynaset, strSQL );

							if( !rsPrimaryOrg.IsEOF( ) )
							{
								html.NonEditText("Primary Organisation", rsPrimaryOrg.m_OrgName);	
							}
							else
							{
								html.NonEditText("Primary Organisation", "Invalid Organisation");
							}

							rsPrimaryOrg.Close( );


							strSQL.Format( "SELECT * FROM Organisation WHERE OrgID = %d ", rsFinc.m_OrgID );
							COrganisationSet rsOrg2( &db );
							rsOrg2.Open(CRecordset::dynaset, strSQL );

							if( !rsOrg2.IsEOF( ) )
							{
								html.NonEditText("Secondary Organisation", rsOrg2.m_OrgName);
								html.HiddenInt("OrgID", rsFinc.m_OrgID);
							}
							else
							{
								html.NonEditText("Secondary Organisation", "Invalid Organisation");
								html.HiddenInt("OrgID", 0);
							}

							rsOrg2.Close( );

							html.NonEditInt("Year Valid", rsFinc.m_Year);
							html.HiddenInt("Year", rsFinc.m_Year);

							html.NonEditInt("Registration ID", rsFinc.m_RegistrationID);

							html.HorizontalRule();
							html.SubmitButton(CHtmlKey::Delete);
						}
					}
					else
					{
						html.NonEditText("", "Has never been Financial");
					}

					html.EndForm();
				}
				else
				{
					html << _T("No Organisations Available");
				}
			}
			else
			{
				html << _T("No Registration Types Available");
			}
			rsOrg.Close( );
			rsRegType.Close( );

			rsFinc.Close( );
			rsPerson.Close( );

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

void CWebAthlExtension::FinancialEditExecute(CHttpServerContext* pCtxt,
									  LPTSTR szPersonID,
									  LPTSTR szMailListFlag,
									  LPTSTR szRegistrationTypeID,
									  LPTSTR szOldRegTypeID,
									  LPTSTR szOrgID,
									  LPTSTR szYear,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Financial) )
	{
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Financial Menu", 0);

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Financial WHERE PersonID = %s AND Year = %s AND RegistrationTypeID = %s", szPersonID, szYear, szOldRegTypeID );
			CFinancialSet rsFinc( &db );
			rsFinc.Open(CRecordset::dynaset, strSQL );

			if( !_tcscmp(szSubmit, CHtmlKey::Save) )
			{
				rsFinc.Edit( );

				rsFinc.m_MailListFlag = atoi(szMailListFlag);
				rsFinc.m_RegistrationTypeID = atoi(szRegistrationTypeID);
				rsFinc.m_OrgID = atoi(szOrgID);
					
				if( !rsFinc.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsFinc.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Financial for Person, <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}
			}
			else if( !_tcscmp(szSubmit, CHtmlKey::Delete) )
			{
				rsFinc.Delete( );
				html << _T("Deleted Financial for Person, <B>");
				html << _T(szPersonID);
				html << _T("</B><BR>\r\n");
			}
			rsFinc.Close( );

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

