// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "PersonSet.h"
#include "PersonCommentsSet.h"
#include "SecurityPersonSet.h"
#include "CountResultSet.h"

///////////////////////////////////////////////////////////////////////
// Person

void CWebAthlExtension::PersonMenu(CHttpServerContext* pCtxt,
							   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::EditPerson | CModule::ViewPerson) )
	{
		auth.m_strHeading = "Person";
		auth.m_strBackLink = CPage::PersonMenu;

		html.SetContent();
		html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
		html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
		html.SetCookie(CHtmlKey::PersonID, CConvert::itoa(auth.m_iPersonID));
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		if( auth.HasPermission(CModule::EditPerson) )
			html.WritePageMenuItem(CPage::SearchPersonForm, "Edit Person", 1, CPage::PersonEditForm);

		if( auth.HasPermission(CModule::ViewPerson) )
			html.WritePageMenuItem(CPage::SearchPersonForm, "View Person", 1, CPage::PersonViewForm);

		if( auth.m_iPersonID > 0 )
			html.WritePageMenuItem(CPage::PersonEditForm, "Edit Your Person", 0);

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::PersonAddForm(CHttpServerContext* pCtxt,
									  LPTSTR szInit,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SearchPerson | CModule::EditPerson) )
	{
		auth.m_strFrwdLink = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		html.StartForm("Person", CPage::PersonAddExecute);
		html.HiddenText("Init", auth.m_strFrwdLink);

		html.NonEditInt("Person ID", 0);
		html.HiddenInt("PersonID", 0);
		html.HorizontalRule();

		html.EditTextBoxLarge("Last Name", "LastName", "");
		html.EditTextBoxLarge("First Name", "FirstName", "");
		html.EditTextBoxLarge("Middle Name", "MiddleName", "");
		html.HorizontalRule();

//		html.EditTextBoxLarge("Address", "Address1", "");
//		html.EditTextBoxLarge("", "Address2", "");
//		html.EditTextBoxSmall("Town", "Town", "");
//		html.EditTextBoxSmall("State", "State", "");
//		html.EditTextBoxSmall("Country", "Country", "");
//		html.EditTextBoxSmall("PostCode", "PostCode", "");
//		html.HorizontalRule();
//
//		html.EditTextBoxSmall("Phone (Home)", "PhoneHm", "");
//		html.EditTextBoxSmall("Phone (Work)", "PhoneWk", "");
//		html.EditTextBoxSmall("Fax", "Fax", "");
//		html.EditTextBoxSmall("Mobile", "Mobile", "");
//		html.EditTextBoxLarge("e-mail", "email", "");
//		html.HorizontalRule();

		html.DateBox("Date of Birth", "dob", 0, 0, 0);
		html.HorizontalRule();

		html.RadioButton("Sex", "Male", "Sex", "M", "M");
		html.RadioButton("", "Female", "Sex", "W", "M");
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}


//add Person command.
void CWebAthlExtension::PersonAddExecute(CHttpServerContext* pCtxt,
								  LPTSTR szInit,
								  LPTSTR szPersonID,
								  LPTSTR szLastName,
								  LPTSTR szFirstName,
								  LPTSTR szMiddleName,
								  LPTSTR szAddress1,
								  LPTSTR szAddress2,
								  LPTSTR szTown,
								  LPTSTR szState,
								  LPTSTR szCountry,
								  LPTSTR szPostCode,
								  LPTSTR szPhoneHm,
								  LPTSTR szPhoneWk,
								  LPTSTR szFax,
								  LPTSTR szMobile,
								  LPTSTR szEmail,
								  LPTSTR szDobDAY,
								  LPTSTR szDobMONTH,
								  LPTSTR szDobYEAR,
								  LPTSTR szSex,
								  LPTSTR szContactPersonID,
								  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SearchPerson | CModule::EditPerson) )
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

			// We don't want to retrieve any records, so we give a bogusz
			// SQL statement expecting an empty CRecordset
			strSQL.Format( "SELECT * FROM Person WHERE PersonID = 0" );
			CPersonSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if( !prop.IsLicensed( ) )
			{
				rs.SetCountMessage( _T("Maximum Person Count Reached.<BR>\r\nPlease Purchase a License Key.<BR>\r\n") );
				//rs.SetCountWhereClause( _T("") );
				rs.HasMaxCountReached( TRUE );
			}
	
			rs.AddNew( );

			if(_tcslen(szLastName) > 0) 
				rs.m_LastName = szLastName;
			else
				rs.SetFieldNull( &rs.m_LastName, TRUE );

			if(_tcslen(szFirstName) > 0) 
				rs.m_FirstName = szFirstName;	
			else
				rs.SetFieldNull( &rs.m_FirstName, TRUE );

			if(_tcslen(szMiddleName) > 0) 
				rs.m_MiddleName = szMiddleName;
			else
				rs.SetFieldNull( &rs.m_MiddleName, TRUE );

			if(_tcslen(szAddress1) > 0) 
				rs.m_Address1 = szAddress1;
			else
				rs.SetFieldNull( &rs.m_Address1, TRUE );

			if(_tcslen(szAddress2) > 0) 
				rs.m_Address2 = szAddress2;
			else
				rs.SetFieldNull( &rs.m_Address2, TRUE );

			if(_tcslen(szTown) > 0) 
				rs.m_Town = szTown;
			else
				rs.SetFieldNull( &rs.m_Town, TRUE );

			if(_tcslen(szState) > 0) 
				rs.m_State = szState;
			else
				rs.SetFieldNull( &rs.m_State, TRUE );

			if(_tcslen(szCountry) > 0) 
				rs.m_Country = szCountry;
			else
				rs.SetFieldNull( &rs.m_Country, TRUE );

			if(_tcslen(szPostCode) > 0) 
				rs.m_PostCode = szPostCode;
			else
				rs.SetFieldNull( &rs.m_PostCode, TRUE );

			if(_tcslen(szPhoneHm) > 0) 
				rs.m_PhoneHm = szPhoneHm;
			else
				rs.SetFieldNull( &rs.m_PhoneHm, TRUE );

			if(_tcslen(szPhoneWk) > 0) 
				rs.m_PhoneWk = szPhoneWk;
			else
				rs.SetFieldNull( &rs.m_PhoneWk, TRUE );

			if(_tcslen(szFax) > 0) 
				rs.m_Fax = szFax;
			else
				rs.SetFieldNull( &rs.m_Fax, TRUE );

			if(_tcslen(szMobile) > 0) 
				rs.m_Mobile = szMobile;
			else
				rs.SetFieldNull( &rs.m_Mobile, TRUE );

			if(_tcslen(szEmail) > 0) 
				rs.m_email = szEmail;
			else
				rs.SetFieldNull( &rs.m_email, TRUE );

			if( atoi(szDobDAY) > 0 ) 
				rs.m_dobDAY = atoi(szDobDAY);
			else
				rs.SetFieldNull( &rs.m_dobDAY, TRUE );

			if( atoi(szDobMONTH) > 0 ) 
				rs.m_dobMONTH = atoi(szDobMONTH);
			else
				rs.SetFieldNull( &rs.m_dobMONTH, TRUE );

			if( atoi(szDobYEAR) > 0 ) 
				rs.m_dobYEAR = atoi(szDobYEAR);
			else
				rs.SetFieldNull( &rs.m_dobYEAR, TRUE );

			if(_tcslen(szSex) > 0) 
				rs.m_Sex = szSex;
			else
				rs.SetFieldNull( &rs.m_Sex, TRUE );

			if( atoi(szContactPersonID) > 0 ) 
				rs.m_ContactPersonID = atoi(szContactPersonID);
			else
				rs.SetFieldNull( &rs.m_ContactPersonID, TRUE );

		
			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				// For dynasets, new records 
				// are added to the recordset as the last record. 
				rs.MoveLast( );

				html << _T("Added Person, <B>");
				html << _T(CConvert::itoa(rs.m_PersonID));
				html << _T("</B> : <B>");
				html << _T( CFormat::FormatName(rs.m_LastName, rs.m_FirstName, rs.m_MiddleName) );
				html << _T("</B><BR>\r\n");

				html.StartForm("", auth.m_strFrwdLink);
				html.HiddenInt("PersonID", rs.m_PersonID);
				html.NonEditText("New Person Added", html.InLineInput("submit","Submit",CHtmlKey::Continue,0,"") );

				html.EndForm();
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

void CWebAthlExtension::PersonEditForm(CHttpServerContext* pCtxt,
									   LPTSTR szPersonID,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::EditPerson) )
	{
		CString strPersonID;

		if(!_tcscmp(szPersonID, "none"))
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::PersonID, strPersonID);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonMenu, CHtmlKey::Cancel, 0);
		html.WritePageMenuItem(CPage::PersonCommentAddExecute, "Add Comment", 1, strPersonID);

		if( auth.HasPermission(CModule::Person) )
			if( auth.m_iPersonID == atoi(strPersonID) )
				html.WritePageMenuItem(CPage::PersonChangePasswordForm, "Password", 1, strPersonID );

		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

/*
			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s AND LoginName = '%s'", strPersonID, auth.m_strLoginName );

			CSecurityPersonSet rsSecPer( &db );
			rsSecPer.Open(CRecordset::dynaset, strSQL );

			if( !rsSecPer.IsEOF() )
				html.WritePageMenuItem(CPage::PersonChangePasswordForm, "Password", 1, strPersonID );

			rsSecPer.Close( );

			html.EndMenu();
*/

			CPersonSet rs( &db );
			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s", strPersonID );
			rs.Open(CRecordset::dynaset, strSQL );
				

			html.StartForm("Person", CPage::PersonEditExecute);

			html.NonEditInt("Person ID", rs.m_PersonID);
			html.HiddenInt("PersonID", rs.m_PersonID);
			html.HorizontalRule();

			html.EditTextBoxLarge("Last Name", "LastName", rs.m_LastName);
			html.EditTextBoxLarge("First Name", "FirstName", rs.m_FirstName);
			html.EditTextBoxLarge("Middle Name", "MiddleName", rs.m_MiddleName);
			html.HorizontalRule();

			html.EditTextBoxLarge("Address", "Address1", rs.m_Address1);
			html.EditTextBoxLarge("", "Address2", rs.m_Address2);
			html.EditTextBoxSmall("Town", "Town", rs.m_Town);
			html.EditTextBoxSmall("State", "State", rs.m_State);
			html.EditTextBoxSmall("PostCode", "PostCode", rs.m_PostCode);
			html.EditTextBoxSmall("Country", "Country", rs.m_Country);
			html.HorizontalRule();

			html.EditTextBoxSmall("Phone (Home)", "PhoneHm", rs.m_PhoneHm);
			html.EditTextBoxSmall("Phone (Work)", "PhoneWk", rs.m_PhoneWk);
			html.EditTextBoxSmall("Fax", "Fax", rs.m_Fax);
			html.EditTextBoxSmall("Mobile", "Mobile", rs.m_Mobile);
			html.EditTextBoxLarge("e-mail", "email", rs.m_email);
			html.HorizontalRule();

			html.DateBox("Date of Birth", "dob", rs.m_dobDAY, rs.m_dobMONTH, rs.m_dobYEAR);
			html.HorizontalRule();

			html.RadioButton("Sex", "Male", "Sex", "M", rs.m_Sex);
			html.RadioButton("", "Female", "Sex", "W", rs.m_Sex);
			html.HorizontalRule();

			html.EditIntBox("Contact Person ID", "ContactPersonID", rs.m_ContactPersonID);

			int iContactID = 0;
			if( !rs.IsFieldNull( &rs.m_ContactPersonID ) )
				iContactID = rs.m_ContactPersonID;

			html.HorizontalRule();
			html.ResetButton();
			html.SubmitButton(CHtmlKey::Save);
//			html.SubmitButton(CHtmlKey::Delete);

			html.EndForm();

			rs.Close( );

			if( iContactID )
			{
				CString strContact;

				html.StartForm("", CPage::PersonEditForm);

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %d", iContactID );
				rs.Open(CRecordset::dynaset, strSQL );

				if( rs.m_FirstName.IsEmpty( ) )
					strContact.Format("%s", rs.m_LastName);
				else
					strContact.Format("%s, %s", rs.m_LastName, rs.m_FirstName);

				html.NonEditText("Contact", strContact );
				html.NonEditText("", "</strong><em><small>(Partner, Emergency, Guardian or Otherwise)</small></em><strong>" );
			
				html.HiddenInt("PersonID", iContactID);
				html.SubmitButton(CHtmlKey::Contact);
				html.EndForm();

				rs.Close( );
			}



			strSQL.Format( "SELECT * FROM PersonComments WHERE PersonID = %s ORDER BY CommentNo", strPersonID);
			CPersonCommentsSet rsComments( &db );
			rsComments.Open(CRecordset::dynaset, strSQL );

			if( !rsComments.IsEOF( ) )
			{
				strSQL.Format( "SELECT COUNT(*) AS Total FROM PersonComments WHERE PersonID = %s ", strPersonID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html.TableHeader( CConvert::itoa(rsCount.m_Total) + " Comments" );

				CStringArray* strColumn;
				strColumn = new CStringArray;

				strColumn->Add( "No" );
				strColumn->Add( "Type" );
				strColumn->Add( "Comment" );
				strColumn->Add( "" );
				strColumn->Add( "" );

				html.HtmlTable(strColumn);
				html.HorizontalRule(strColumn->GetSize( ) );

				strColumn->RemoveAll( );

				while( !rsComments.IsEOF( ) )
				{
					html.StartInLineForm(_T("Comments" + CConvert::itoa(rsComments.m_CommentNo)), CPage::PersonCommentEditExecute);

					html.HiddenText("PersonID", strPersonID);
					html.HiddenInt("CommentNo", rsComments.m_CommentNo);

					strColumn->Add( CConvert::itoa(rsComments.m_CommentNo) );
					strColumn->Add( html.InLineInput("text","Type",rsComments.m_Type,16,"") );
					strColumn->Add( html.InLineInput("text","Comment",rsComments.m_Comment,30,"") );
					strColumn->Add( html.InLineInput("submit","Submit",CHtmlKey::Save,0,"") );
					strColumn->Add( html.InLineInput("submit","Submit",CHtmlKey::Delete,0,"") );

					html.HtmlTable(strColumn);

					strColumn->RemoveAll( );
					rsComments.MoveNext( );

					html.EndInLineForm();
				}
				html.TableFooter();

				delete strColumn;

				rsCount.Close( );
			}
			rsComments.Close( );
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

void CWebAthlExtension::PersonCommentEditExecute(CHttpServerContext* pCtxt,
									LPTSTR szPersonID,
									LPTSTR szCommentNo,
									LPTSTR szType,
									LPTSTR szComment,
									LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::EditPerson) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonEditForm, "Edit Person", 0);
		html.WritePageMenuItem(CPage::PersonMenu, "Person Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM PersonComments WHERE PersonID = %s AND CommentNo = %s ", szPersonID, szCommentNo);
			CPersonCommentsSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
			

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				if( !rs.IsEOF( ) )
					rs.Edit( );
				else
					rs.AddNew( );

				rs.m_PersonID = atoi(szPersonID);
				rs.m_CommentNo = atoi(szCommentNo);

				if(_tcslen(szComment) > 0) 
					rs.m_Comment = szComment;
				else
					rs.SetFieldNull( &rs.m_Comment, TRUE );

				if(_tcslen(szType) > 0) 
					rs.m_Type = szType;
				else
					rs.SetFieldNull( &rs.m_Type, TRUE );
		
				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Comment <B>");
					html << _T(szCommentNo);
					html << _T("</B>, for Person <B>");
					html << _T(szPersonID);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Comment <B>");
				html << _T(szCommentNo);
				html << _T("</B>, for Person <B>");
				html << _T(szPersonID);
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

void CWebAthlExtension::PersonCommentAddExecute(CHttpServerContext* pCtxt,
								   LPTSTR szInit, 
								   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::EditPerson) )
	{
		CString strPersonID = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonEditForm, "Edit Person", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT MAX(CommentNo) AS Total FROM PersonComments WHERE PersonID = %s", strPersonID);
			CCountResultSet rsCount( &db );
			rsCount.Open(CRecordset::dynaset, strSQL );

			int iCommentNo = 1;

			if( !rsCount.IsEOF( ) && !rsCount.IsFieldNull(&rsCount.m_Total) )
				iCommentNo = rsCount.m_Total +1;

			strSQL.Format( "SELECT * FROM PersonComments WHERE PersonID = %s ", strPersonID);
			CPersonCommentsSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );


			rs.AddNew( );

			rs.m_PersonID = atoi(strPersonID);
			rs.m_CommentNo = iCommentNo;

			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Comment <B>");
				html << _T( CConvert::itoa(iCommentNo));
				html << _T("</B>, for Person <B>");
				html << _T(strPersonID);
				html << _T("</B><BR>\r\n");
			}

			rs.Close( );

			rsCount.Close( );
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

void CWebAthlExtension::PersonViewForm(CHttpServerContext* pCtxt,
									   LPTSTR szPersonID,
									   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::ViewPerson) )
	{
		CString strPersonID;

		if(!_tcscmp(szPersonID, "none"))
			strPersonID = html.GetCookie(CHtmlKey::PersonID);
		else
			strPersonID = szPersonID;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::PersonID, strPersonID);
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonMenu, CHtmlKey::Cancel, 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;
		
			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CPersonSet rs( &db );
			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s", strPersonID );
			rs.Open(CRecordset::dynaset, strSQL );
				

			html.StartForm("Person", "");

			html.NonEditInt("Person ID", rs.m_PersonID);
			html.HorizontalRule();

			html.NonEditText("Last Name", rs.m_LastName);
			html.NonEditText("First Name", rs.m_FirstName);
			html.NonEditText("Middle Name", rs.m_MiddleName);
			html.HorizontalRule();

			html.NonEditText("Address", rs.m_Address1);
			html.NonEditText("", rs.m_Address2);
			html.NonEditText("Town", rs.m_Town);
			html.NonEditText("State", rs.m_State);
			html.NonEditText("PostCode", rs.m_PostCode);
			html.NonEditText("Country", rs.m_Country);
			html.HorizontalRule();

			html.NonEditText("Phone (Home)", rs.m_PhoneHm);
			html.NonEditText("Phone (Work)", rs.m_PhoneWk);
			html.NonEditText("Fax", rs.m_Fax);
			html.NonEditText("Mobile", rs.m_Mobile);
			html.NonEditText("e-mail", rs.m_email);
			html.HorizontalRule();

			html.NonEditDateBox("Date of Birth", rs.m_dobDAY, rs.m_dobMONTH, rs.m_dobYEAR);
			html.HorizontalRule();

			if(!_tcscmp(rs.m_Sex, "M"))
				html.NonEditText("Sex", "Male");
			else if(!_tcscmp(rs.m_Sex, "W"))
				html.NonEditText("Sex", "Female");
			else 
				html.NonEditText("Sex", "");

			html.HorizontalRule();

			html.NonEditText("Contact Person ID", CConvert::itoa(rs.m_ContactPersonID));

			int iContactID = 0;
			if( !rs.IsFieldNull( &rs.m_ContactPersonID ) )
			{
				iContactID = rs.m_ContactPersonID;
			}

			html.HorizontalRule();

			html.EndForm();
			rs.Close( );

			if( iContactID )
			{
				CString strContact;

				html.StartForm("", CPage::PersonViewForm);

				strSQL.Format( "SELECT * FROM Person WHERE PersonID = %d", iContactID );
				rs.Open(CRecordset::dynaset, strSQL );

				if( rs.m_FirstName.IsEmpty( ) )
					strContact.Format("%s", rs.m_LastName);
				else
					strContact.Format("%s, %s", rs.m_LastName, rs.m_FirstName);

				html.NonEditText("Contact", strContact );
				html.NonEditText("", "</strong><em><small>(Partner, Emergency, Guardian or Otherwise)</small></em><strong>" );
			
				html.HiddenInt("PersonID", iContactID);
				html.SubmitButton(CHtmlKey::Contact);
				html.EndForm();

				rs.Close( );
			}

			strSQL.Format( "SELECT * FROM PersonComments WHERE PersonID = %s ORDER BY CommentNo", strPersonID);
			CPersonCommentsSet rsComments( &db );
			rsComments.Open(CRecordset::dynaset, strSQL );

			if( !rsComments.IsEOF( ) )
			{
				strSQL.Format( "SELECT COUNT(*) AS Total FROM PersonComments WHERE PersonID = %s ", strPersonID );
				CCountResultSet rsCount( &db );
				rsCount.Open(CRecordset::dynaset, strSQL );

				html.StartForm(CConvert::itoa(rsCount.m_Total) + " Comments", "");

				rsCount.Close( );

				while( !rsComments.IsEOF( ) )
				{
					html.NonEditText(rsComments.m_Type, rsComments.m_Comment );

					rsComments.MoveNext();
				}

				html.EndForm();
			}
			rsComments.Close( );

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

void CWebAthlExtension::PersonEditExecute(CHttpServerContext* pCtxt,
								  LPTSTR szPersonID,
								  LPTSTR szLastName,
								  LPTSTR szFirstName,
								  LPTSTR szMiddleName,
								  LPTSTR szAddress1,
								  LPTSTR szAddress2,
								  LPTSTR szTown,
								  LPTSTR szState,
								  LPTSTR szPostCode,
								  LPTSTR szCountry,
								  LPTSTR szPhoneHm,
								  LPTSTR szPhoneWk,
								  LPTSTR szFax,
								  LPTSTR szMobile,
								  LPTSTR szEmail,
								  LPTSTR szDobDAY,
								  LPTSTR szDobMONTH,
								  LPTSTR szDobYEAR,
								  LPTSTR szSex,
								  LPTSTR szContactPersonID,
								  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person | CModule::EditPerson) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonEditForm, "Edit Person", 0);
		html.WritePageMenuItem(CPage::PersonMenu, "Person Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ", szPersonID );
			CPersonSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				if(_tcslen(szLastName) > 0) 
					rs.m_LastName = szLastName;
				else
					rs.SetFieldNull( &rs.m_LastName, TRUE );


				if(_tcslen(szFirstName) > 0) 
					rs.m_FirstName = szFirstName;	
				else
					rs.SetFieldNull( &rs.m_FirstName, TRUE );

				if(_tcslen(szMiddleName) > 0) 
					rs.m_MiddleName = szMiddleName;
				else
					rs.SetFieldNull( &rs.m_MiddleName, TRUE );

				if( atoi(szDobDAY) > 0 ) 
					rs.m_dobDAY = atoi(szDobDAY);
				else
					rs.SetFieldNull( &rs.m_dobDAY, TRUE );

				if( atoi(szDobMONTH) > 0 ) 
					rs.m_dobMONTH = atoi(szDobMONTH);
				else
					rs.SetFieldNull( &rs.m_dobMONTH, TRUE );

				if( atoi(szDobYEAR) > 0 ) 
					rs.m_dobYEAR = atoi(szDobYEAR);
				else
					rs.SetFieldNull( &rs.m_dobYEAR, TRUE );

				if(_tcslen(szSex) > 0) 
					rs.m_Sex = szSex;
				else
					rs.SetFieldNull( &rs.m_Sex, TRUE );

				if(_tcslen(szAddress1) > 0) 
					rs.m_Address1 = szAddress1;
				else
					rs.SetFieldNull( &rs.m_Address1, TRUE );

				if(_tcslen(szAddress2) > 0) 
					rs.m_Address2 = szAddress2;
				else
					rs.SetFieldNull( &rs.m_Address2, TRUE );

				if(_tcslen(szTown) > 0) 
					rs.m_Town = szTown;
				else
					rs.SetFieldNull( &rs.m_Town, TRUE );

				if(_tcslen(szState) > 0) 
					rs.m_State = szState;
				else
					rs.SetFieldNull( &rs.m_State, TRUE );

				if(_tcslen(szCountry) > 0) 
					rs.m_Country = szCountry;
				else
					rs.SetFieldNull( &rs.m_Country, TRUE );

				if(_tcslen(szPostCode) > 0) 
					rs.m_PostCode = szPostCode;
				else
					rs.SetFieldNull( &rs.m_PostCode, TRUE );

				if(_tcslen(szPhoneHm) > 0) 
					rs.m_PhoneHm = szPhoneHm;
				else
					rs.SetFieldNull( &rs.m_PhoneHm, TRUE );

				if(_tcslen(szPhoneWk) > 0) 
					rs.m_PhoneWk = szPhoneWk;
				else
					rs.SetFieldNull( &rs.m_PhoneWk, TRUE );

				if(_tcslen(szFax) > 0) 
					rs.m_Fax = szFax;
				else
					rs.SetFieldNull( &rs.m_Fax, TRUE );

				if(_tcslen(szMobile) > 0) 
					rs.m_Mobile = szMobile;
				else
					rs.SetFieldNull( &rs.m_Mobile, TRUE );

				if(_tcslen(szEmail) > 0) 
					rs.m_email = szEmail;
				else
					rs.SetFieldNull( &rs.m_email, TRUE );

				if(atoi(szContactPersonID) > 0) 
					rs.m_ContactPersonID = atoi(szContactPersonID);
				else
					rs.SetFieldNull( &rs.m_ContactPersonID, TRUE );

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Person, <B>");
					html << _T(szFirstName);
					html << _T(" ");
					html << _T(szLastName);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );

				html << _T("Deleted Person, <B>");
				html << _T(szFirstName);
				html << _T(" ");
				html << _T(szLastName);
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

void CWebAthlExtension::PersonChangePasswordForm(CHttpServerContext* pCtxt,
										   LPTSTR szSubmit,
										   LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person) )
	{
		CString strPersonID = szInit;
		
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::PersonEditForm, CHtmlKey::Cancel, 0);
		html.EndMenu();

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

			CString strPersonName;
			if( rsPerson.m_FirstName.IsEmpty( ) )
				strPersonName.Format("%s", rsPerson.m_LastName);
			else
				strPersonName.Format("%s, %s", rsPerson.m_LastName, rsPerson.m_FirstName);

			html << _T("Please supply a password with a minimum length of ");
			html << _T(CConvert::itoa(CAuthenticator::m_iMinPwdLen));
			html << _T(" characters.<BR>\r\n");

			html.StartForm("Security", CPage::PersonChangePasswordExecute);
			html.NonEditInt("Person ID", rsPerson.m_PersonID);
			html.HiddenInt("PersonID", rsPerson.m_PersonID);
			html.NonEditText("Name", strPersonName);
			html.HorizontalRule();

			if ( !rsSecPer.IsEOF( ) )
			{
				html.NonEditText("Login Name", rsSecPer.m_LoginName);
				html.PasswordBox("Old Password", "oPassword", "");
				html.PasswordBox("New Password", "nPassword", "");
				html.PasswordBox("Confirm New Password", "cPassword", "");
			}

			html.HorizontalRule();
			html.ResetButton();
			html.SubmitButton(CHtmlKey::Save);

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

void CWebAthlExtension::PersonChangePasswordExecute(CHttpServerContext* pCtxt,
									   LPTSTR szPersonID,
									   LPTSTR szOldPassword,
									   LPTSTR szNewPassword,
									   LPTSTR szConfirmPassword,
									   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Person) )
	{
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM SecurityPerson WHERE PersonID = %s ", szPersonID );

			CSecurityPersonSet rsSecPer( &db );

			rsSecPer.Open(CRecordset::dynaset, strSQL );

			CCryptByteArray* cbaPwd = new CCryptByteArray( );

			cbaPwd->Init(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
						 atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

			if ( !rsSecPer.IsEOF( ) )
			{
				CString strPwd;

				cbaPwd->Set( rsSecPer.m_Password );
				cbaPwd->DeCrypt( );

				strPwd = cbaPwd->GetString( );

				if( _tcscmp(strPwd, szOldPassword) )
				{
					html.WritePageMenuItem(CPage::PersonEditForm, CHtmlKey::Cancel, 0);
					html.EndMenu();

					html << _T("Invalid old Password<BR>\r\n");
				}
				else if( _tcscmp(szConfirmPassword, szNewPassword) )
				{
					html.WritePageMenuItem(CPage::PersonEditForm, CHtmlKey::Cancel, 0);
					html.EndMenu();

					html << _T("Passwords not Consistent<BR>\r\n");
				}
				else if( _tcslen(szNewPassword) < CAuthenticator::m_iMinPwdLen )
				{
					html.WritePageMenuItem(CPage::PersonEditForm, CHtmlKey::Cancel, 0);
					html.EndMenu();

					html << _T("Password must have a minimum length of ");
					html << _T(CConvert::itoa(CAuthenticator::m_iMinPwdLen));
					html << _T(" characters.<BR>\r\n");
					html << _T("Please supply a longer password.<BR>\r\n");
				}
				else
				{
					html.WritePageMenuItem(CPage::DefaultEntry, CHtmlKey::LogOff, 0);
					html.EndMenu();

					cbaPwd->Set( szNewPassword );
					cbaPwd->EnCrypt( );

					rsSecPer.Edit( );

					cbaPwd->Copy( &(rsSecPer.m_Password) );

					if( !rsSecPer.CanUpdate( ) )
						html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");

					if( !rsSecPer.Update( ) )
					{
						html.StartForm("Security", CPage::PersonEditForm);
						html.NonEditText("Password Not Changed", html.InLineInput("submit","Submit",CHtmlKey::Continue,0,""));
						html.EndForm();
					}
					else
					{
						html.StartForm("Security", CPage::DefaultEntry);
						html.NonEditText("Password Changed", html.InLineInput("submit","Submit",CHtmlKey::LogOff,0,""));
						html.EndForm();
					}
				}

				delete cbaPwd;
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



