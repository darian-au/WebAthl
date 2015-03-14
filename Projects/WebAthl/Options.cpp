// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "IntegerSet.h"
#include "StringSet.h"

///////////////////////////////////////////////////////////////////////
// Options

void CWebAthlExtension::OptionsMenu(CHttpServerContext* pCtxt,
									LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
		auth.m_strHeading = "Options";
		auth.m_strBackLink = CPage::OptionsMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.SetCookie(CHtmlKey::IsOptions, "1");
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::OptionsAppearanceForm, "Appearance", 0);
		html.WritePageMenuItem(CPage::OptionsNavigationForm, "Navigation", 0);
		html.WritePageMenuItem(CPage::OptionsAgeGroupsForm, "Age Groups", 0);
		html.WritePageMenuItem(CPage::OptionsPersonSearchForm, "Person Search", 0);
		html.WritePageMenuItem(CPage::OptionsProcessingForm, "Processing", 0);
		html.WritePageMenuItem(CPage::OptionsODBCSetupForm, "ODBC Setup", 0);
		html.WritePageMenuItem(CPage::OptionsCryptographyForm, "Cryptography", 0);

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsODBCSetupForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
		html.SetContent();
		html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);

		html.WritePageMenu(auth.m_strUserName, "Setup");
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		html.ODBCSetupForm(CPage::DefaultODBCSetupExecute);

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsAgeGroupsForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		int iMaxJunior = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
		int iMinVeteran = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
		int iJuniorGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
		int iVeteranGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));
		int iNullDoB = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::NullDoB));

		html.StartForm("Age Groups", CPage::OptionsAgeGroupsExecute);

		html.EditIntBox("Maximum Junior Age","MaxJunior", iMaxJunior);
		html.EditIntBox("Junior Age Grouping","JuniorGroup", iJuniorGroup);
		html.HorizontalRule();
		html.EditIntBox("Minimum Veteran Age","MinVeteran", iMinVeteran);
		html.EditIntBox("Veteran Age Grouping","VeteranGroup", iVeteranGroup);
		html.HorizontalRule();
		html.EditIntBox("Default Age Group on NULL Date of Birth","NullDoB", iNullDoB);
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsAgeGroupsExecute(CHttpServerContext* pCtxt,
												LPTSTR szMaxJunior,
												LPTSTR szJuniorGroup,
												LPTSTR szMinVeteran,
												LPTSTR szVeteranGroup,
												LPTSTR szNullDoB,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

		LONG nStatus = ERROR_SUCCESS;

		nStatus |= prop.Set(CHtmlKey::AgeGroup, CHtmlKey::MaxJunior, szMaxJunior);
		nStatus |= prop.Set(CHtmlKey::AgeGroup, CHtmlKey::JuniorGroup, szJuniorGroup);
		nStatus |= prop.Set(CHtmlKey::AgeGroup, CHtmlKey::MinVeteran, szMinVeteran);
		nStatus |= prop.Set(CHtmlKey::AgeGroup, CHtmlKey::VeteranGroup, szVeteranGroup);
		nStatus |= prop.Set(CHtmlKey::AgeGroup, CHtmlKey::NullDoB, szNullDoB);

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Age Groups Saved<BR>\r\n");
			html << _T("<BR>\r\nMaxJunior : <B>");
			html << _T(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
			html << _T("</B><BR>\r\nJuniorGroup : <B>");
			html << _T(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
			html << _T("</B><BR>\r\nMinVeteran : <B>");
			html << _T(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
			html << _T("</B><BR>\r\nVeteranGroup : <B>");
			html << _T(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));
			html << _T("</B><BR>\r\nNullDoB : <B>");
			html << _T(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::NullDoB));
			html << _T("</B><BR>\r\n");
		}
		else
		{
			html << _T("Unable to Save Settings.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsProcessingForm(CHttpServerContext* pCtxt,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		int iSeconds = atoi(prop.GetEx(CHtmlKey::Processing,CHtmlKey::TimeOut));

		html.StartForm("Processing", CPage::OptionsProcessingExecute);

		html.EditIntBox("Processing Time Out","TimeOut", iSeconds);
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsProcessingExecute(CHttpServerContext* pCtxt,
												 LPTSTR szTimeOut,
												 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

		LONG nStatus = prop.Set(CHtmlKey::Processing, CHtmlKey::TimeOut, szTimeOut);

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Settings Saved<BR>\r\n");
			html << _T("</B><BR>\r\nProcessing TimeOut : <B>");
			html << _T(prop.GetEx(CHtmlKey::Processing,CHtmlKey::TimeOut));
			html << _T("</B><BR>\r\n");
		}
		else
		{
			html << _T("Unable to Save Settings.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsAppearanceForm(CHttpServerContext* pCtxt,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		CString strFont = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Font);
		CString strBackgroundColor = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundColor);
		CString strMenuColor = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuColor);
		CString strBackgroundImage = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundImage);
		CString strMenuImage = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuImage);
		CString strLogo = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Logo);
		CString strStyleSheet = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::StyleSheet);

		html.StartForm("Appearance", CPage::OptionsAppearanceExecute);

		html.EditTextBoxLarge("Cascading Style Sheet ", "StyleSheet", strStyleSheet);
		html.EditTextBoxLarge("Font", "Font", strFont);
		html.EditTextBoxSmall("Background Color", "BackgroundColor", strBackgroundColor);
		html.EditTextBoxSmall("Menu Color", "MenuColor", strMenuColor);
		html.EditTextBoxLarge("Background Image", "BackgroundImage", strBackgroundImage);
		html.EditTextBoxLarge("Menu Image", "MenuImage", strMenuImage);
		html.EditTextBoxLarge("Logo Image", "Logo", strLogo);
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsAppearanceExecute(CHttpServerContext* pCtxt,
												 LPTSTR szStyleSheet,
												 LPTSTR szFont,
												 LPTSTR szBackgroundColor,
												 LPTSTR szMenuColor,
												 LPTSTR szBackgroundImage,
												 LPTSTR szMenuImage,
												 LPTSTR szLogo,
												 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

/*		try
		{
			if(auth.m_iRoleID != auth.m_iDboRoleId)
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );

				COptionsSet rsOptions( &db );
				strSQL.Format( "SELECT * FROM Options WHERE PersonID = %d ", auth.m_iPersonID );
				rsOptions.Open(CRecordset::dynaset, strSQL );

				if( rsOptions.IsEOF( ) )
					rsOptions.AddNew( );
				else
					rsOptions.Edit( );

				rsOptions.m_PersonID = auth.m_iPersonID;

				if(_tcslen(szFont) > 0) 
					rsOptions.m_Font = _T(szFont);
				else
					rsOptions.SetFieldNull( &rsOptions.m_Font, TRUE );

				if(_tcslen(szBgColor) > 0) 
					rsOptions.m_bgColor = _T(szBgColor);
				else
					rsOptions.SetFieldNull( &rsOptions.m_bgColor, TRUE );
				
				if(_tcslen(szMenuColor) > 0) 
					rsOptions.m_menuColor = _T(szMenuColor);
				else
					rsOptions.SetFieldNull( &rsOptions.m_menuColor, TRUE );

				if(_tcslen(szBgPic) > 0) 
					rsOptions.m_bgPic = _T(szBgPic);
				else
					rsOptions.SetFieldNull( &rsOptions.m_bgPic, TRUE );

				if(_tcslen(szMenuPic) > 0) 
					rsOptions.m_menuPic = _T(szMenuPic);
				else
					rsOptions.SetFieldNull( &rsOptions.m_menuPic, TRUE );

				if(_tcslen(szLogo) > 0) 
					rsOptions.m_Logo = _T(szLogo);
				else
					rsOptions.SetFieldNull( &rsOptions.m_Logo, TRUE );

				if(_tcslen(szStyleSheet) > 0) 
					rsOptions.m_StyleSheet = _T(szStyleSheet);
				else
					rsOptions.SetFieldNull( &rsOptions.m_StyleSheet, TRUE );


				if( !rsOptions.CanUpdate( ) )
					html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
				if( !rsOptions.Update( ) )
					html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
				else
				{
					html << _T("Updated Personalised Appearance for : <B>");
					html << _T(auth.m_strUserName);
					html << _T("</B><BR>\r\n");
				}
				rsOptions.Close( );

				html << _T("Appearance Saved<BR>\r\n");

				db.Close( );
			}
			else
*/			{
				LONG nStatus = ERROR_SUCCESS;

				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::StyleSheet,		 szStyleSheet	   );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::Font,			 szFont			   );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::BackgroundColor, szBackgroundColor );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::MenuColor,		 szMenuColor	   );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::BackgroundImage, szBackgroundImage );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::MenuImage,		 szMenuImage	   );
				nStatus |= prop.Set(CHtmlKey::Appearance, CHtmlKey::Logo,			 szLogo			   );

				if( nStatus == ERROR_SUCCESS )
				{
					html << _T("Updated Global Appearance.<BR>\r\n");
					//html << _T("Appearance Saved<BR>\r\n");
				}
				else
				{
					html << _T("Unable to Update Global Appearance.<BR>\r\n");
				}
			}
		
			html << _T("<BR>\r\nStyle Sheet : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::StyleSheet));
			html << _T("</B><BR>\r\nFont : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Font));
			html << _T("</B><BR>\r\nBackground Color : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundColor));
			html << _T("</B><BR>\r\nMenu Color : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuColor));
			html << _T("</B><BR>\r\nBackground Image : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundImage));
			html << _T("</B><BR>\r\nMenu Image : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuImage));
			html << _T("</B><BR>\r\nLogo : <B>");
			html << _T(prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Logo));
			html << _T("</B><BR>\r\n");
/*		}
		catch (CDBException* pEx)
		{
			html << pEx;
			html << _T("Appearance Not Saved<BR>\r\n");

			pEx->Delete();
		}
*/
		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsCryptographyForm(CHttpServerContext* pCtxt,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		int iEnabled = atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled));

		html.StartForm("Cryptography", CPage::OptionsCryptographyExecute);

		html.CheckBox("Password Encryption", "Enabled", "Enabled", "1", CConvert::itoa(iEnabled));
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsCryptographyExecute(CHttpServerContext* pCtxt,
												   LPTSTR szEnabled,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

		LONG nStatus = prop.Set(CHtmlKey::Cryptography, CHtmlKey::Enabled, szEnabled );

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Settings Saved<BR>\r\n");
			html << _T("<BR>\r\nCryptography : <B>");

			if( atoi( prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled) )  )
			{
				html << _T("Enabled</B><BR>\r\n");
				html << _T("<BR>\r\nAll User Login Passwords will be Encrypted.<BR>\r\n");
			}
			else
			{
				html << _T("Disabled</B><BR>\r\n");
				html << _T("<BR>\r\nAll User Login Passwords will <B>NOT</B> be Encrypted.<BR>\r\n");
			}
		}
		else
		{
			html << _T("Unable to Save Settings.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsNavigationForm(CHttpServerContext* pCtxt,
										   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		CString strExitURL = prop.GetEx(CHtmlKey::Navigation,CHtmlKey::ExitURL);

		html.StartForm("Navigation", CPage::OptionsNavigationExecute);

		html.EditTextBoxLarge("Exit URL","ExitURL", strExitURL);
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsNavigationExecute(CHttpServerContext* pCtxt,
											  LPTSTR szExitURL,
											  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

		LONG nStatus = prop.Set(CHtmlKey::Navigation, CHtmlKey::ExitURL, szExitURL);

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Settings Saved<BR>\r\n");
			html << _T("</B><BR>\r\nExit URL : <B>");
			html << _T(prop.GetEx(CHtmlKey::Navigation,CHtmlKey::ExitURL));
			html << _T("</B><BR>\r\n");
		}
		else
		{
			html << _T("Unable to Save Settings.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsPersonSearchForm(CHttpServerContext* pCtxt,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		CString strLastName = prop.GetEx(CHtmlKey::PersonSearch, CHtmlKey::LastName);
		CString strFirstName = prop.GetEx(CHtmlKey::PersonSearch, CHtmlKey::FirstName);
		CString strMiddleName = prop.GetEx(CHtmlKey::PersonSearch, CHtmlKey::MiddleName);
		CString strDateOfBirth = prop.GetEx(CHtmlKey::PersonSearch, CHtmlKey::DateOfBirth);
		CString strSex = prop.GetEx(CHtmlKey::PersonSearch, CHtmlKey::Sex);

		html.StartForm("Person Search", CPage::OptionsPersonSearchExecute);

		html.EditTextBoxSmall("Last Name", "LastName", strLastName);
		html.EditTextBoxSmall("First Name", "FirstName", strFirstName);
		html.EditTextBoxSmall("Middle Name", "MiddleName", strMiddleName);
		html.EditTextBoxSmall("Date Of Birth", "DateOfBirth", strDateOfBirth);
		html.EditTextBoxSmall("Sex", "Sex", strSex);

		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::OptionsPersonSearchExecute(CHttpServerContext* pCtxt,
												   LPTSTR szLastName,
												   LPTSTR szFirstName,
												   LPTSTR szMiddleName,
												   LPTSTR szDateOfBirth,
												   LPTSTR szSex,
												   LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );
		
	if( auth.CheckPermission(CModule::Options) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Options Menu", 0);

		html.EndMenu();

		LONG nStatus = ERROR_SUCCESS;

		nStatus |= prop.Set(CHtmlKey::PersonSearch, CHtmlKey::LastName, szLastName);
		nStatus |= prop.Set(CHtmlKey::PersonSearch, CHtmlKey::FirstName, szFirstName);
		nStatus |= prop.Set(CHtmlKey::PersonSearch, CHtmlKey::MiddleName, szMiddleName);
		nStatus |= prop.Set(CHtmlKey::PersonSearch, CHtmlKey::DateOfBirth, szDateOfBirth);
		nStatus |= prop.Set(CHtmlKey::PersonSearch, CHtmlKey::Sex, szSex);

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Settings Saved<BR>\r\n");
			html << _T("</B><BR>\r\nLast Name : <B>");
			html << _T(prop.GetEx(CHtmlKey::PersonSearch,CHtmlKey::LastName));
			html << _T("</B><BR>\r\nFirst Name : <B>");
			html << _T(prop.GetEx(CHtmlKey::PersonSearch,CHtmlKey::FirstName));
			html << _T("</B><BR>\r\nMiddle Name : <B>");
			html << _T(prop.GetEx(CHtmlKey::PersonSearch,CHtmlKey::MiddleName));
			html << _T("</B><BR>\r\nDate Of Birth : <B>");
			html << _T(prop.GetEx(CHtmlKey::PersonSearch,CHtmlKey::DateOfBirth));
			html << _T("</B><BR>\r\nSex : <B>");
			html << _T(prop.GetEx(CHtmlKey::PersonSearch,CHtmlKey::Sex));
			html << _T("</B><BR>\r\n");
		}
		else
		{
			html << _T("Unable to Save Settings.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}
