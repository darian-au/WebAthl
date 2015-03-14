// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "WorldStandardSet.h"
#include "EventTypeSet.h"

///////////////////////////////////////////////////////////////////////
// WorldStandard

void CWebAthlExtension::WorldStandardMenu(CHttpServerContext* pCtxt,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::WorldStandards) )
	{
		auth.m_strHeading = "Age Standards";
		auth.m_strBackLink = CPage::WorldStandardMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::WorldStandardSelectForm, "Edit Standard", 0);

		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::WorldStandardSelectForm(CHttpServerContext* pCtxt,
										   LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::WorldStandards) )
	{
		auth.m_strFrwdLink = CPage::WorldStandardEditForm;

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

			CEventTypeSet rsEvent( &db );

			strSQL.Format( "SELECT * FROM EventType ORDER BY EventDescription" );
			rsEvent.Open(CRecordset::dynaset, strSQL );

			if( !rsEvent.IsEOF( ) )
			{
				html << _T("Select an Event Type and Record Category\r\n");

				html.StartForm("Age Standards", auth.m_strFrwdLink);

				html.StartSelectBox("Event", "EventTypeID");
				while( !rsEvent.IsEOF( ) )
				{
					html.AddSelectBox(
						rsEvent.m_EventDescription,
						CConvert::itoa(rsEvent.m_EventTypeID), "");
					rsEvent.MoveNext( );
				}
				html.EndSelectBox();
				html.HorizontalRule();

				html.StartSelectBox("Age Category", "AgeCategory");
				html.AddSelectBox("Veteran", "V", "");
				html.AddSelectBox("Junior", "J", "");
				html.AddSelectBox("Open", "O", "");
				html.EndSelectBox();

				html.StartSelectBox("Record Category", "RecCategory");
				html.AddSelectBox("Standards", "D", "");
				html.AddSelectBox("State", "S", "");
				html.AddSelectBox("National", "N", "");
				html.AddSelectBox("World", "W", "");
				html.EndSelectBox();

				html.StartSelectBox("Sex", "Sex");
				html.AddSelectBox("Male", "M", "");
				html.AddSelectBox("Female", "W", "");
				html.EndSelectBox();

				html.HorizontalRule();
				html.SubmitButton(CHtmlKey::Select);

				html.EndForm();
			}
			else
			{
				html << _T("No Event Types Available\r\n");
			}

			rsEvent.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			html << pEx;
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::WorldStandardEditForm(CHttpServerContext* pCtxt,
										 LPTSTR szEventTypeID,
										 LPTSTR szAgeCategory,
										 LPTSTR szRecCategory,
										 LPTSTR szSex,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::WorldStandards) )
	{
		auth.m_strFrwdLink = CPage::WorldStandardEditExecute;


		int iMaxJunior = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MaxJunior));
		int iMinVeteran = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::MinVeteran));
		int iJuniorGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::JuniorGroup));
		int iVeteranGroup = atoi(prop.GetEx(CHtmlKey::AgeGroup,CHtmlKey::VeteranGroup));

		int iTblStart = 0;
		int iTblStop = 0;
		int iTblInc = 1;

		char chAgeCat = szAgeCategory[0];
		switch (chAgeCat)
		{
			case 'V' : 
				iTblStart = iMinVeteran;
				iTblStop  = 100;
				iTblInc   = iVeteranGroup;
				break;
			case 'J' : 
				iTblStart = iJuniorGroup;
				iTblStop  = iMaxJunior + iJuniorGroup;
				iTblInc   = iJuniorGroup;
				break;
		}

		CString strTitle;
		CString strRecordCategory;

		char chRecCat = szRecCategory[0];
		switch (chRecCat)
		{
			case 'D' : 
				strRecordCategory = "Standard";
				strTitle = "Age Standards";
				break;
			case 'S' :
				strRecordCategory = "State";
				strTitle = "State Records";
				break;
			case 'N' :
				strRecordCategory = "National";
				strTitle = "National Records";
				break;
			case 'W' :
				strRecordCategory = "World";
				strTitle = "World Records";
				break;
		}


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

			int iTimed = 1;

			strSQL.Format( "SELECT * FROM EventType WHERE EventTypeID = %s", szEventTypeID );
			CEventTypeSet rsEvent( &db );
			rsEvent.Open(CRecordset::dynaset, strSQL );

			if( !rsEvent.IsEOF( ) )
			{
				strTitle += ", " + rsEvent.m_EventDescription;
				iTimed = rsEvent.m_Timed;
			}
			rsEvent.Close( );


			CString strFactID = "";
			if(chRecCat == 'D')
				strFactID = "Factor";


			html.StartForm(strTitle, auth.m_strFrwdLink);
			html.StandardTableHeader(
				"AgeGroup",
				(strRecordCategory + " Performance"),
				strFactID);

			html.HiddenText("EventTypeID", szEventTypeID);
			html.HiddenText("AgeCategory", szAgeCategory);
			html.HiddenText("RecCategory", szRecCategory);
			html.HiddenText("Sex", szSex);

//			int tID = 1;
			for( int iAge = iTblStart; iAge < iTblStop +1 ; (iAge = iAge + iTblInc) )
			{
//				int iFactID = 0;
//				if(chRecCat == 'D')
//					iFactID = tID;

				strSQL.Format( "SELECT * FROM WorldStandard WHERE EventTypeID = %s AND AgeCategory = '%s' AND RecCategory = '%s' AND Sex = '%s' AND AgeGroup = %d ",
					szEventTypeID, szAgeCategory, szRecCategory, szSex, iAge );

				CWorldStandardSet rsStd( &db );
				rsStd.Open(CRecordset::dynaset, strSQL );

				html.HiddenInt("AgeGroupList", iAge);

				CString strAge;

				if(iAge)
					strAge.Format(szSex + CConvert::itoa(iAge));
				else
					strAge = szSex;


				if(iTimed)
					html.StandardTimeTable(
						strAge,
						//tID,
						rsStd.m_PerfHOUR,
						//tID,
						rsStd.m_PerfMIN,
						//tID,
						rsStd.m_PerfSEC,
						(chRecCat == 'D' ? 1 : 0),
						rsStd.m_PerfFactor);
				else
					html.StandardDistTable(
						strAge,
						//tID,
						rsStd.m_PerfSEC,
						(chRecCat == 'D' ? 1 : 0),
						rsStd.m_PerfFactor);

				rsStd.Close( );

				//tID++;
			}

			html.HorizontalRule();
			html.SubmitButton(CHtmlKey::Save);

			html.EndForm();

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

void CWebAthlExtension::WorldStandardEditExecute(CHttpServerContext* pCtxt,
									 LPTSTR szEventTypeID,
									 LPTSTR szAgeCategory,
									 LPTSTR szRecCategory,
									 LPTSTR szSex,
									 LPTSTR szAgeGroupList,
									 LPTSTR szPerformanceHOURList,
									 LPTSTR szPerformanceMINList,
									 LPTSTR szPerformanceSECList,
									 LPTSTR szFactorList,
									 LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::WorldStandards) )
	{
		CString strResultsEntry = html.GetCookie(CHtmlKey::ResultsEntry);
		int iPreEvent = _tcscmp("Post", strResultsEntry);

	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Standards Menu", 0);

		html.EndMenu();

		CString strAgeGroupList = CString(szAgeGroupList);
		CStringArray* strAgeGroupItems = new CStringArray();

		CString strPerformanceHOURList = CString(szPerformanceHOURList);
		CStringArray* strPerformanceHOURItems = new CStringArray();

		CString strPerformanceMINList = CString(szPerformanceMINList);
		CStringArray* strPerformanceMINItems = new CStringArray();

		CString strPerformanceSECList = CString(szPerformanceSECList);
		CStringArray* strPerformanceSECItems = new CStringArray();

		CString strFactorList = CString(szFactorList);
		CStringArray* strFactorItems = new CStringArray();

		CCSV csv(CWebAthlExtension::chIsapiDelimiter);

		csv.GetItems(strAgeGroupItems, &strAgeGroupList);
		csv.GetItems(strPerformanceHOURItems, &strPerformanceHOURList);
		csv.GetItems(strPerformanceMINItems, &strPerformanceMINList);
		csv.GetItems(strPerformanceSECItems, &strPerformanceSECList);
		csv.GetItems(strFactorItems, &strFactorList);

		int nAgeGroupItems = strAgeGroupItems->GetSize( );
		int nPerformanceHOURItems = strPerformanceHOURItems->GetSize( );
		int nPerformanceMINItems = strPerformanceMINItems->GetSize( );
		int nPerformanceSECItems = strPerformanceSECItems->GetSize( );
		int nFactorItems = strFactorItems->GetSize( );


		if( (nAgeGroupItems == nPerformanceHOURItems) && 
			(nAgeGroupItems == nPerformanceMINItems) && 
			(nAgeGroupItems == nPerformanceSECItems) && 
			(nAgeGroupItems == nFactorItems) 
		)
		{
			int iEventTypeID = atoi(szEventTypeID);
			char chRecCategory = szRecCategory[0];
			char chAgeCategory = szAgeCategory[0];
			char chSex = szSex[0];

			CString strRecordCategory;
			switch (chRecCategory)
			{
				case 'D' : 
					strRecordCategory.Format("Standard");
					break;
				case 'S' :
					strRecordCategory.Format("State");
					break;
				case 'N' :
					strRecordCategory.Format("National");
					break;
				case 'W' :
					strRecordCategory.Format("World");
					break;
			}

			try
			{
				CString strConnect = prop.GetDefaultConnect();
				CString strSQL;

				CDatabase db;
				db.OpenEx( strConnect, CDatabase::noOdbcDialog );


				for( int nIndex = 0; nIndex < nAgeGroupItems ; nIndex++ )
				{
					CString strAgeGroup = strAgeGroupItems->GetAt(nIndex);
					int iAgeGroup = atoi(strAgeGroup);

					CString strPerformanceHOUR = strPerformanceHOURItems->GetAt(nIndex);
					int iPerformanceHOUR = atoi(strPerformanceHOUR);

					CString strPerformanceMIN = strPerformanceMINItems->GetAt(nIndex);
					int iPerformanceMIN = atoi(strPerformanceMIN);

					CString strPerformanceSEC = strPerformanceSECItems->GetAt(nIndex);
					double dPerformanceSEC = atof(strPerformanceSEC);

					CString strFactor = strFactorItems->GetAt(nIndex);
					double dFactor = atof(strFactor);

					if( (iPerformanceHOUR > 0)   ||
						(iPerformanceMIN > 0)    ||
						(dPerformanceSEC > 0)    ||
						(dFactor > 0)		)
					{
						strSQL.Format( "SELECT * FROM WorldStandard WHERE EventTypeID = %d AND AgeCategory = '%c' AND RecCategory = '%c' AND Sex = '%c' AND AgeGroup = %d ", 
							iEventTypeID, chAgeCategory, chRecCategory, chSex, iAgeGroup );

						CWorldStandardSet rsStd( &db );
						rsStd.Open(CRecordset::dynaset, strSQL );

						if( rsStd.IsEOF( ) )
							rsStd.AddNew( );
						else
							rsStd.Edit( );

						rsStd.m_PerfHOUR = iPerformanceHOUR;
						rsStd.m_PerfMIN = iPerformanceMIN;
						rsStd.m_PerfSEC = dPerformanceSEC;
						rsStd.m_PerfFactor = dFactor;
						rsStd.m_AgeGroup = iAgeGroup;

						rsStd.m_EventTypeID = iEventTypeID;
						rsStd.m_AgeCategory = szAgeCategory;
						rsStd.m_RecCategory = szRecCategory;
						rsStd.m_Sex = szSex;

						if( !rsStd.CanUpdate( ) )
							html << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
						if( !rsStd.Update( ) )
							html << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
						else
						{
							html << _T("Modified, <B>");
							html << _T(strRecordCategory);
							html << _T(" ");
							html << _T(szSex);
							html << _T(CConvert::itoa(iAgeGroup));
							html << _T("</B><BR>\r\n");
						}
						rsStd.Close( );
					}
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
			html << _T("nAgeGroupItems does no match nPerformanceHOURItems, nPerformanceMINItems, nPerformanceSECItems, nFactorItems<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}


