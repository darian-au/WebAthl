// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "LocationSet.h"

///////////////////////////////////////////////////////////////////////
// Location

void CWebAthlExtension::LocationSelectForm(CHttpServerContext* pCtxt,
											LPTSTR szSubmit,
											LPTSTR szInit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Location) )
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


			CLocationSet rsLoc( &db );
			strSQL.Format( "SELECT * FROM Location ORDER BY LocationDescription" );
			rsLoc.Open(CRecordset::dynaset, strSQL );

			if( !rsLoc.IsEOF( ) )
			{
				html << _T("Select a Location\r\n");

				html.StartForm("Location", auth.m_strFrwdLink);

				html.StartSelectBox("Location", "LocationID");
				while( !rsLoc.IsEOF( ) )
				{
					html.AddSelectBox(rsLoc.m_LocationDescription, CConvert::itoa(rsLoc.m_LocationID), "");
					rsLoc.MoveNext( );
				}
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Locations Available\r\n");
			}

			rsLoc.Close( );
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

void CWebAthlExtension::LocationAddForm(CHttpServerContext* pCtxt,
										LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Location) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);
		html.EndMenu();


		html.StartForm("Location", CPage::LocationAddExecute);

		html.NonEditInt("Location ID", 0);
		html.HiddenInt("LocationID", 0);

		html.EditTextBoxLarge("Location", "LocationDescription", "");
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Add);

		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::LocationAddExecute(CHttpServerContext* pCtxt,
									 LPTSTR szLocationID,
									 LPTSTR szLocationDescription,
									 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Location) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			strSQL.Format( "SELECT * FROM Location" );
			CLocationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

	
			rs.AddNew( );

			if(_tcslen(szLocationDescription) > 0) 
				rs.m_LocationDescription = szLocationDescription;
			else
				rs.SetFieldNull( &rs.m_LocationDescription, TRUE );

	
			if( !rs.CanUpdate( ) )
				html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
			if( !rs.Update( ) )
				html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
			else
			{
				html << _T("Added Location, <B>");
				html << _T(szLocationDescription);
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

void CWebAthlExtension::LocationEditForm(CHttpServerContext* pCtxt,
										 LPTSTR szLocationID,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Location) )
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


			strSQL.Format( "SELECT * FROM Location WHERE LocationID = %s", szLocationID );
			CLocationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );
				
			if( !rs.IsEOF( ) )
			{
				html.StartForm("Location", CPage::LocationEditExecute);

				html.NonEditInt("Location ID", rs.m_LocationID);
				html.HiddenInt("LocationID", rs.m_LocationID);

				html.EditTextBoxLarge("Location", "LocationDescription", rs.m_LocationDescription);
				html.HorizontalRule();

				html.ResetButton();
				html.SubmitButton(CHtmlKey::Save);
//				html.SubmitButton(CHtmlKey::Delete);

				html.EndForm();
			}
			else
			{
				html << _T("No Locations Available<BR>\r\n");
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

void CWebAthlExtension::LocationEditExecute(CHttpServerContext* pCtxt,
									  LPTSTR szLocationID,
									  LPTSTR szLocationDescription,
									  LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Location) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Series Menu", 0);
		html.EndMenu();

		try
		{
			CString strConnect = prop.GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			strSQL.Format( "SELECT * FROM Location WHERE LocationID = %s ", szLocationID );
			CLocationSet rs( &db );
			rs.Open(CRecordset::dynaset, strSQL );

			if (!_tcscmp( szSubmit, CHtmlKey::Save ))
			{
				rs.Edit( );

				if(_tcslen(szLocationDescription) > 0) 
					rs.m_LocationDescription = szLocationDescription;
				else
					rs.SetFieldNull( &rs.m_LocationDescription, TRUE );

				if( !rs.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rs.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Modified Location, <B>");
					html << _T(szLocationDescription);
					html << _T("</B><BR>\r\n");
				}
			}
			else if (!_tcscmp( szSubmit, CHtmlKey::Delete ))
			{
				rs.Delete( );
				html << _T("Deleted Location, <B>");
				html << _T(szLocationDescription);
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
