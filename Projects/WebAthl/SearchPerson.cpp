// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "PersonSet.h"
#include "SecurityPersonSet.h"

///////////////////////////////////////////////////////////////////////
// SearchPerson

void CWebAthlExtension::SearchPersonForm(CHttpServerContext* pCtxt,
										 LPTSTR szInit,
										 LPTSTR szInit1,
										 LPTSTR szInit2,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::SearchPerson) )
	{
		auth.m_strFrwdLink = szInit;

		html.SetContent();

		if( _tcslen(szInit1) > 0 )
		    html.SetCookie(CHtmlKey::FrwdLink, szInit1);

	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		html.StartForm("Search Person", CPage::SearchPersonSelectForm);

		html.HiddenText("Init", szInit);

		if( _tcslen(szInit2) > 0 )
			html.HiddenText("Duplicate", szInit2);

		int nNull;
		CRecordsetEx::GetNullItem(&nNull);

		html.EditIntBox("Person ID", "PersonID", nNull);
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

		html.RadioButton("Sex", "Male", "Sex", "M", "");
		html.RadioButton("", "Female", "Sex", "W", "");
		html.HorizontalRule();

		html.ResetButton();
		html.SubmitButton(CHtmlKey::Search);

		html.EndForm();

		html << _T("<p>Note: When searching by Name, you may enter any sequence of characters contained within that name. E.g. Searching with Last Name '<B>cot</B>' may result with persons whose last name is '<B>Scott</B>' or '<B>Northcott</B>'.</p>\r\n");

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::SearchPersonSelectForm(CHttpServerContext* pCtxt,
									 LPTSTR szInit,
									 LPTSTR szDuplicate,
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

	if( auth.CheckPermission(CModule::SearchPerson) )
	{
		auth.m_strFrwdLink = szInit;

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();

		BOOL bSearchIsValid = CPersonSearcher::IsSearchValid(
									&html, 
									&prop,
									szPersonID,
									szLastName,
									szFirstName,
									szMiddleName,
									szDobDAY,
									szDobMONTH,
									szDobYEAR,
									szSex);

		if( bSearchIsValid )
		{
			CString strSQL = CPersonSearcher::GetDefaultSQL(
								szPersonID,
								szLastName,
								szFirstName,
								szMiddleName,
								szAddress1,
								szAddress2,
								szTown,
								szState,
								szCountry,
								szPostCode,
								szPhoneHm,
								szPhoneWk,
								szFax,
								szMobile,
								szEmail,
								szDobDAY,
								szDobMONTH,
								szDobYEAR,
								szSex,
								szContactPersonID);

			//html << _T("<BR><BR>\r\n");
			//html << _T(strSQL);
			//html << _T("<BR><BR>\r\n");

			try
			{
				CString strConnect = prop.GetDefaultConnect();

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				CPersonSet rs( &db );
				rs.Open(CRecordset::dynaset, strSQL );

				if( !rs.IsEOF( ) )
				{
					html.StartForm("Search Results", auth.m_strFrwdLink);

					html.SelectPersonBox("Name", "PersonID", &rs, 0, NULL);

					if(_tcslen(szDuplicate) > 0 )
					{
						rs.MoveFirst( );
						html.SelectPersonBox("Duplicate Name", "dupPersonID", &rs, 0, NULL);
					}
					
					html.HorizontalRule();
					html.SubmitButton(CHtmlKey::Select);
					html.EndForm();
				}
				else
				{
					html << _T("No Search Results Matching your Query<BR>\r\n");

					html.StartForm("", CPage::PersonAddForm);

					html.HiddenText("Init", auth.m_strFrwdLink);
					html.NonEditText("Would you like to Add a Person?", html.InLineInput("submit","Submit",CHtmlKey::Add,0,"") );

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
		}

		html.EndPage();
		html.EndContent();
	}
}









