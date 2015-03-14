// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "PersonSet.h"
#include "SecurityPersonSet.h"
#include "SecurityRoleSet.h"
#include "SecurityPersonSeriesSet.h"
#include "SeriesSet.h"

///////////////////////////////////////////////////////////////////////
// Security

void CWebAthlExtension::SecurityMenu(CHttpServerContext* pCtxt,
								 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
		auth.m_strHeading = "Security";
		auth.m_strBackLink = CPage::SecurityMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::IsSecured, "0");
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::SecurityRoleEditForm, "Add Security Role", 0);
		html.WritePageMenuItem(CPage::SecurityRoleSelectForm, "Edit Security Role", 1, CPage::SecurityRoleEditForm);

		html.WritePageMenuItem(CPage::SecurityRoleSelectForm, "Allocate Permissions to Role", 1, CPage::SecurityRoleAllocatePermissionForm);

		html.WritePageMenuItem(CPage::SearchPersonForm, "Assign Login to User", 1, CPage::SecurityAssignLoginForm);

		html.WritePageMenuItem(CPage::SearchPersonForm, "Grant User Access to Role", 1, CPage::SecurityGrantRoleForm);
		html.WritePageMenuItem(CPage::SecurityRoleSelectForm, "Revoke User Access from Role", 1, CPage::SecurityRevokeRoleForm);

		html.WritePageMenuItem(CPage::SearchPersonForm, "Assign Series to User", 1, CPage::SecurityAssignSeriesForm);

		html.EndMenu();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SecurityRoleSelectForm(CHttpServerContext* pCtxt,
												LPTSTR szSubmit,
												LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
		auth.m_strFrwdLink = szInit;

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


			CSecurityRoleSet rs( &db );

			strSQL.Format( "SELECT * FROM SecurityRole" );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html << _T("Select a Security Role\r\n");

				html.StartForm("Security", auth.m_strFrwdLink);
				html.StartSelectBox("Group Name", "RoleID");
				while( !rs.IsEOF( ) )
				{
					html.AddSelectBox(rs.m_RoleName, CConvert::itoa(rs.m_RoleID), "");
					rs.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Security Roles Available\r\n");
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

void CWebAthlExtension::SecurityRoleAllocatePermissionForm(CHttpServerContext* pCtxt,
														   LPTSTR szRoleID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{

			CString strSQL;
			CString strConnect = prop.GetDefaultConnect();

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleID = %s", szRoleID );
			CSecurityRoleSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF( ) )
			{
				html << _T("Select Permissions to Allocate to the Security Role\r\n");

				html.StartForm("Security", CPage::SecurityRoleAllocatePermissionExecute);

				html.NonEditText("Security Role", rs.m_RoleName);
				html.HiddenInt("RoleID", rs.m_RoleID);

				html.HorizontalRule();

				CModule enumList;
				DWORD dwEnum = enumList.Enumerator( );
				while( enumList.GetNext( &dwEnum ) )
				{
					DWORD dwIsMember = 0;

					if( !rs.IsFieldNull( &rs.m_Permission )        &&
						CModule::IsMember(rs.m_Permission, dwEnum) )
					{
						dwIsMember = dwEnum;
					}

					html.CheckBox(enumList.GetLabel(), enumList.GetName(), "Permission", 
						CConvert::dwtoa(dwEnum), 
						CConvert::dwtoa(dwIsMember) );
				}

				html.HorizontalRule();
				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);

				html.EndForm();
			}
			else
			{
				html << _T("No Security Roles Available\r\n");
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

void CWebAthlExtension::SecurityRoleAllocatePermissionExecute(CHttpServerContext* pCtxt,
															  LPTSTR szRoleID,
															  LPTSTR szPermission,
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
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			DWORD dwPermission = CCSV::GetBitMask(szPermission, CWebAthlExtension::chIsapiDelimiter);
			int iRoleID = atoi(szRoleID);

			CSecurityRoleSet rs( &db );
			strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleID = %d", iRoleID);
			rs.Open(CRecordset::dynaset, strSQL );

			if( !rs.IsEOF() )
			{
				rs.Edit( );

				rs.m_Permission = dwPermission;

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Security Role, <B>");
					html << _T(rs.m_RoleName);
					html << _T("</B> Permission <B>");
					html << _T(CConvert::dwtoxa(rs.m_Permission));
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

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SecurityRoleEditForm(CHttpServerContext* pCtxt,
											 LPTSTR szRoleID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CSecurityRoleSet rs( &db );
			strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleID = %s", szRoleID );
			rs.Open(CRecordset::dynaset, strSQL );
				
			html.StartForm("Security", CPage::SecurityRoleEditExecute);

			html.NonEditInt("Role ID", rs.m_RoleID);
			html.HiddenInt("RoleID", rs.m_RoleID);
			html.HorizontalRule();
			html.EditTextBoxLarge("Security Role Name", "RoleName", rs.m_RoleName);
			html.HorizontalRule();
			html.ResetButton();

			if( atoi(szRoleID) > 0 )
			{
				html.SubmitButton(CHtmlKey::Save);
				html.SubmitButton(CHtmlKey::Delete);
			}
			else
			{
				html.SubmitButton(CHtmlKey::Add);
			}

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

void CWebAthlExtension::SecurityRoleEditExecute(CHttpServerContext* pCtxt,
												LPTSTR szRoleID,
												LPTSTR szRoleName,
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
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CSecurityRoleSet rs( &db );
			strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleID = %s ", szRoleID );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !_tcscmp(szSubmit, CHtmlKey::Save) )
			{
				rs.Edit( );

				if(_tcslen(szRoleName) > 0) 
					rs.m_RoleName = szRoleName;
				else
					rs.SetFieldNull( &rs.m_RoleName, TRUE );

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Security Role, <B>");
					html << _T(szRoleName);
					html << _T("</B><BR>\r\n");
				}
			}
			else if( !_tcscmp(szSubmit, CHtmlKey::Delete) )
			{
				rs.Delete( );

				html << _T("Deleted Security Role, <B>");
				html << _T(szRoleName);
				html << _T("</B><BR>\r\n");
			}
			else if( !_tcscmp(szSubmit, CHtmlKey::Add) )
			{
				rs.AddNew( );

				if( _tcslen(szRoleName) > 0 ) 
					rs.m_RoleName = szRoleName;
				else
					rs.SetFieldNull( &rs.m_RoleName, TRUE );
			
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Security Role, <B>");
					html << _T(szRoleName);
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

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SecurityAssignLoginForm(CHttpServerContext* pCtxt,
										 LPTSTR szPersonID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );
			CSecurityPersonSet rsSecPer( &db );
			rsSecPer.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
			CPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			CString strPersonName;
			if( rsPerson.m_FirstName.IsEmpty( ) )
				strPersonName.Format("%s", rsPerson.m_LastName);
			else
				strPersonName.Format("%s, %s", rsPerson.m_LastName, rsPerson.m_FirstName);

			html << _T("Please supply a password with a minimum length of ");
			html << _T(CConvert::itoa(CAuthenticator::m_iMinPwdLen));
			html << _T(" characters.<BR>\r\n");

			BOOL bIsGuest = !_tcscmp(rsPerson.m_LastName, CAuthenticator::m_szGuestUser);

			if ( !rsSecPer.IsEOF( ) )
			{
				html.StartForm("Security", CPage::SecurityAssignLoginExecute);
				html.NonEditInt("Person ID", rsPerson.m_PersonID);
				html.HiddenInt("PersonID", rsPerson.m_PersonID);
				html.NonEditText("Name", strPersonName);
				html.HorizontalRule();

				if( !bIsGuest )
				{
					html.EditTextBoxSmall("Login Name", "LoginName", rsSecPer.m_LoginName);
					html.PasswordBox("Password", "Password", "");
					html.PasswordBox("Confirm Password", "cPassword", "");
				}
				else
				{
					html.NonEditText("Login Name", rsSecPer.m_LoginName);
					html.HiddenText("LoginName", rsSecPer.m_LoginName);
					html.NonEditText("Password", "");
					html.HiddenText("Password", "");
					html.HiddenText("cPassword", "");
				}
			}
			else 
			{
				CString strAutoLoginName;
				CString strAutoPassword;

				if( bIsGuest )
				{
					strAutoLoginName.Format(CAuthenticator::m_szGuestUser);
				}
				else if( !rsPerson.IsFieldNull( &rsPerson.m_FirstName ) &&
						 !rsPerson.IsFieldNull( &rsPerson.m_LastName ) )
				{
					strAutoLoginName.Format("%c%c%d",
						rsPerson.m_FirstName.GetAt(0),
						rsPerson.m_LastName.GetAt(0),
						rsPerson.m_PersonID);
					strAutoLoginName.MakeLower( );
				}
				else
				{
					html << _T("<BR>\r\n<B>Warning</B>: This Person is missing either a First or Last Name.  An Automatic Login Name connot be generated.<BR>\r\n");
				}

				if( !rsPerson.IsFieldNull( &rsPerson.m_dobDAY ) &&
					!rsPerson.IsFieldNull( &rsPerson.m_dobMONTH ) &&
					!rsPerson.IsFieldNull( &rsPerson.m_dobYEAR ) &&
					!bIsGuest)
				{
					strAutoPassword.Format("%s%s%s",
						CConvert::itoa(rsPerson.m_dobDAY, 2),
						CConvert::itoa(rsPerson.m_dobMONTH, 2),
						CConvert::itoa(rsPerson.m_dobYEAR));

					html << _T("<BR>\r\nAn Automatic Password has been generated from the Date Of Birth.<BR>\r\n");
				}
				else if( !bIsGuest )
				{
					html << _T("<BR>\r\n<B>Warning</B>: This Person has no Date Of Birth.  An Automatic Password connot be generated.<BR>\r\n");
				}

				html.StartForm("Security", CPage::SecurityAssignLoginExecute);
				html.NonEditInt("Person ID", rsPerson.m_PersonID);
				html.HiddenInt("PersonID", rsPerson.m_PersonID);
				html.NonEditText("Name", strPersonName);
				html.HorizontalRule();


				if( !bIsGuest )
				{
					html.EditTextBoxSmall("Login Name", "LoginName", strAutoLoginName);
					html.PasswordBox("Password", "Password", strAutoPassword);
					html.PasswordBox("Confirm Password", "cPassword", strAutoPassword);
				}
				else
				{
					html.NonEditText("Login Name", strAutoLoginName);
					html.HiddenText("LoginName", strAutoLoginName);
					html.NonEditText("Password", strAutoPassword);
					html.HiddenText("Password", strAutoPassword);
					html.HiddenText("cPassword", strAutoPassword);
				}
			}

			html.HorizontalRule();
			html.ResetButton();
			html.SubmitButton(CHtmlKey::Save);

			if ( !rsSecPer.IsEOF( ) )
			{
				html.SubmitButton(CHtmlKey::Delete);
			}

			html.EndForm();

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

void CWebAthlExtension::SecurityAssignLoginExecute(CHttpServerContext* pCtxt,
								    LPTSTR szPersonID,
								    LPTSTR szLoginName,
								    LPTSTR szPassword,
								    LPTSTR szConfirmPassword,
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
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);
		html.EndMenu();

		BOOL bIsDelete = !_tcscmp(szSubmit, CHtmlKey::Delete);
		BOOL bIsGuest = !_tcscmp(szLoginName, CAuthenticator.m_szGuestUser);

		if( _tcscmp(szPassword, szConfirmPassword) && !bIsDelete && !bIsGuest)
		{
			html << _T("Passwords not Consistent<BR>\r\n");
		}
		else if( (_tcslen(szPassword) < CAuthenticator::m_iMinPwdLen) && !bIsDelete && !bIsGuest)
		{
			html << _T("Password must have a minimum length of ");
			html << _T(CConvert::itoa(CAuthenticator::m_iMinPwdLen));
			html << _T(" characters.<BR>\r\n");
			html << _T("Please supply a longer password.<BR>\r\n");
		}
		else
		{
			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );
				CSecurityPersonSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				if( bIsDelete )
				{
					rs.Delete( );
					html << _T("Deleted Login for, <B>");
					html << _T(szLoginName);
					html << _T("</B><BR>\r\n");
				}
				else
				{
					bool bNew;

					if ( !rs.IsEOF( ) )
					{
						rs.Edit( );
						bNew = false;
					}
					else
					{
						rs.AddNew( );
						bNew = true;
					}

					CCryptByteArray* cbaPwd = new CCryptByteArray( );

					cbaPwd->Init(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
								 atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

					rs.m_PersonID = atoi(szPersonID);
					rs.m_LoginName = szLoginName;
					if( !bIsGuest )
					{
						cbaPwd->Set( szPassword );
						cbaPwd->EnCrypt( );
						
						cbaPwd->Copy( &(rs.m_Password) );
					}
					else
					{
						rs.SetFieldNull( &rs.m_Password );
					}


					if( !rs.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
					if( !rs.Update( ) )
						html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
					else
					{
						if(bNew)
							html << _T("Added Login for, <B>");
						else
							html << _T("Modified Login for, <B>");

						html << _T(szLoginName);
						html << _T("</B><BR>\r\n");
					}

					delete cbaPwd;
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

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SecurityGrantRoleForm(CHttpServerContext* pCtxt,
											   LPTSTR szPersonID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );
			CSecurityPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			if ( !rsPerson.IsEOF( ) )
			{
				CSecurityRoleSet rs( &db );

				strSQL.Format( "SELECT * FROM SecurityRole" );
				rs.Open(CRecordset::dynaset, strSQL );

				if( !rs.IsEOF( ) )
				{
					html << _T("Select a Security Role to Allocate the Person to\r\n");

					html.StartForm("Security", CPage::SecurityGrantRoleExecute);
					html.HiddenText("PersonID", szPersonID);
					html.StartSelectBox("Role Name", "RoleID");
					while( !rs.IsEOF( ) )
					{
						html.AddSelectBox(rs.m_RoleName, CConvert::itoa(rs.m_RoleID), CConvert::itoa(rsPerson.m_RoleID));
						rs.MoveNext( );
					}
					html.EndSelectBox();

					html.HorizontalRule();
					html.SubmitButton(CHtmlKey::Select);

					html.EndForm();
				}
				else
				{
					html << _T("No Security Roles Available\r\n");
				}

				rs.Close( );
			}
			else
			{
				html << _T("Please go back to the Security Menu and Assign this person a Login First : <B>");
				html << _T(szPersonID);
				html << _T("</B><BR>\r\n");
			}
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

void CWebAthlExtension::SecurityGrantRoleExecute(CHttpServerContext* pCtxt,
												 LPTSTR szPersonID,
												 LPTSTR szRoleID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

	
			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );
			CSecurityPersonSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );


			if ( !rs.IsEOF( ) )
			{
				rs.Edit( );
			}
			else
			{
				rs.AddNew( );
				rs.m_PersonID = atoi(szPersonID);
			}

			rs.m_RoleID = atoi(szRoleID);

		
			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Set Security on Person, <B>");
				html << _T(szPersonID);
				html << _T("</B> for Security Role, <B>");
				html << _T(szRoleID);
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

void CWebAthlExtension::SecurityRevokeRoleForm(CHttpServerContext* pCtxt,
											   LPTSTR szRoleID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CString strRoleName;

			strSQL.Format( "SELECT * FROM SecurityRole WHERE RoleID = %s", szRoleID );
			CSecurityRoleSet rsRole( &db );
			rsRole.Open(CRecordset::forwardOnly, strSQL );

			strRoleName = rsRole.m_RoleName;
			
			rsRole.Close( );

			strSQL.Format( "SELECT Person.* FROM Person, SecurityPerson WHERE Person.PersonID = SecurityPerson.PersonID AND SecurityPerson.RoleID = %s ORDER BY Person.LastName, Person.FirstName", szRoleID );
			CPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			if( !rsPerson.IsEOF( ) )
			{
				html << _T("Select a Person to Revoke from <B>");
				html << _T(strRoleName);
				html << _T("</B>\r\n");

				html.StartForm("Security", CPage::SecurityRevokeRoleExecute);
				html.HiddenText("RoleID", szRoleID);

				html.StartSelectBox("Person", "PersonID");

				while( !rsPerson.IsEOF( ) )
				{
					CString strPersonName;

					if( rsPerson.m_FirstName.IsEmpty( ) )
						strPersonName.Format("%s", rsPerson.m_LastName);
					else
						strPersonName.Format("%s, %s", rsPerson.m_LastName, rsPerson.m_FirstName);


					html.AddSelectBox(strPersonName, CConvert::itoa(rsPerson.m_PersonID), "");

					rsPerson.MoveNext( );					
				}
				html.EndSelectBox();
				
				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Revoke);

				html.EndForm();
			}
			else
			{
				html << _T("No People Assigned to Security Role <B>");
				html << _T(strRoleName);
				html << _T("</B>\r\n");
			}

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

void CWebAthlExtension::SecurityRevokeRoleExecute(CHttpServerContext* pCtxt,
												  LPTSTR szRoleID,
												  LPTSTR szPersonID,
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
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s AND RoleID = %s", szPersonID, szRoleID );
			CSecurityPersonSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );


			if ( !rs.IsEOF( ) )
			{
				rs.Edit( );

				rs.SetFieldNull( &rs.m_RoleID );


				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Revoked the Person, <B>");
					html << _T(szPersonID);
					html << _T("</B> from Security Role, <B>");
					html << _T(szRoleID);
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

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SecurityAssignSeriesForm(CHttpServerContext* pCtxt,
										 LPTSTR szPersonID,
									     LPTSTR szSeriesID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
		CString strPersonID;
		if( _tcslen(szPersonID) > 0 ) 
		{
			strPersonID = szPersonID;
		}
		else
		{
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		}
		
		int iSeriesID = 0;
		if( _tcslen(szSeriesID) > 0 ) 
		{
			iSeriesID = atoi(szSeriesID);
		}

		auth.m_strBackLink = CPage::SecurityAssignSeriesForm;

		html.SetContent();
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.SetCookie(CHtmlKey::PersonID, strPersonID);
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SecurityMenu, "Security Menu", 0);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", strPersonID );
			CSecurityPersonSet rsSecPer( &db );
			rsSecPer.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", strPersonID );
			CPersonSet rsPerson( &db );
			rsPerson.Open(CRecordset::dynaset, strSQL );

			strSQL.Format( "SELECT Series.* FROM Series, SecurityPersonSeries WHERE SecurityPersonSeries.PersonID = %s AND Series.SeriesID = SecurityPersonSeries.SeriesID ORDER BY Series.SeriesDescription", strPersonID );
			CSeriesSet rsSeries( &db );
			rsSeries.Open(CRecordset::dynaset, strSQL );


			CString strPersonName;
			if( rsPerson.m_FirstName.IsEmpty( ) )
				strPersonName.Format("%s", rsPerson.m_LastName);
			else
				strPersonName.Format("%s, %s", rsPerson.m_LastName, rsPerson.m_FirstName);


			if ( !rsSecPer.IsEOF( ) )
			{
				html.WritePageMenuItem(CPage::SeriesSelectForm, "Add Series", 2, CPage::SecurityAssignSeriesExecute, CConvert::itoa(rsPerson.m_PersonID) );
				html.EndMenu();

				html.StartForm("Series Security Assignment", CPage::SecurityAssignSeriesExecute);
				html.NonEditInt("Person ID", rsPerson.m_PersonID);
				html.NonEditText("Name", strPersonName);
				html.HorizontalRule();

				if ( !rsSeries.IsEOF( ) )
				{
					html.SelectSeriesBox("Series", "SeriesID", &rsSeries, 0, NULL);
					html.HorizontalRule();
					html.SubmitButton(CHtmlKey::Remove);
				}
				else
				{
					html.NonEditText("Series", "None Assigned");
				}
				html.EndForm();
			}
			else
			{
				html.EndMenu();

				html << _T("Please go back to the Security Menu and Assign this person a Login First : <B>");
				html << _T(strPersonID);
				html << _T(" ; ");
				html << _T(strPersonName);
				html << _T("</B><BR>\r\n");
			}

			rsPerson.Close( );
			rsSecPer.Close( );
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

void CWebAthlExtension::SecurityAssignSeriesExecute(CHttpServerContext* pCtxt,
									 LPTSTR szSeriesID,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Security) )
	{
		CString strPersonID = html.GetCookie(CHtmlKey::PersonID);
		
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::SecurityAssignSeriesForm, "Assign Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			if( !_tcscmp(CHtmlKey::Remove, szSubmit) ) 
			{
				// remove the SeriesID from SecurityPersonSeries
				strSQL.Format( "SELECT * FROM SecurityPersonSeries WHERE PersonID = %s AND SeriesID = %s", strPersonID, szSeriesID );
				CSecurityPersonSeriesSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.Delete( );

				html << _T("Removed Series, <B>");
				html << _T(szSeriesID);
				html << _T("</B> from Person, <B>");
				html << _T(strPersonID);
				html << _T("</B><BR>\r\n");

				rs.Close( );
			}
			else
			{
				// add the SeriesID to SecurityPersonSeries
				strSQL.Format( "SELECT * FROM SecurityPersonSeries WHERE PersonID = %s", strPersonID );
				CSecurityPersonSeriesSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				rs.AddNew( );

				rs.m_PersonID = atoi(strPersonID);
				rs.m_SeriesID = atoi(szSeriesID);

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Added Series, <B>");
					html << _T(szSeriesID);
					html << _T("</B> to Person, <B>");
					html << _T(strPersonID);
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


