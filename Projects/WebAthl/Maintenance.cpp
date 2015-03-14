// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

#include "SecurityPersonSet.h"

#include "IntegerSet.h"
#include "StringSet.h"

///////////////////////////////////////////////////////////////////////
// Maintenance

void CWebAthlExtension::MaintenanceMenu(CHttpServerContext* pCtxt,
									LPTSTR szSubmit)

{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
		auth.m_strHeading = "Maintenance";
		auth.m_strBackLink = CPage::MaintenanceMenu;

	    html.SetContent();
	    html.SetCookie(CHtmlKey::Heading, auth.m_strHeading);
	    html.SetCookie(CHtmlKey::BackLink, auth.m_strBackLink);
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);

		html.WritePageMenuItem(CPage::DefaultMenu, "Main Menu", 0);

		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::CreateTables), 1, CConvert::dwtoa(CMaintainDatabase::CreateTables));
		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::CreateViews), 1, CConvert::dwtoa(CMaintainDatabase::CreateViews));
		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::CreateForeignKeys), 1, CConvert::dwtoa(CMaintainDatabase::CreateForeignKeys));
		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::DropForeignKeys), 1, CConvert::dwtoa(CMaintainDatabase::DropForeignKeys));
		//html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::CreateStoredProcedures), 1, CConvert::dwtoa(CMaintainDatabase::CreateStoredProcedures));
		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::ExportData), 1, CConvert::dwtoa(CMaintainDatabase::ExportData));
		html.WritePageMenuItem(CPage::MaintenanceMaintainDatabaseForm, CMaintainDatabase::GetName(CMaintainDatabase::ImportData), 1, CConvert::dwtoa(CMaintainDatabase::ImportData));

		html.WritePageMenuItem(CPage::MaintenanceSetFolderForm,	"Set Export/Import Folder", 0);

		html.WritePageMenuItem(CPage::MaintenanceDisableUsersForm, "Set User Access", 0);


		BOOL bCryptEnabled = atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled));

		if(bCryptEnabled)
		{
			html.WritePageMenuItem(CPage::MaintenanceCryptPasswordsForm,	"Encrypt/Decrypt All User Passwords", 0);
		}


		html.EndMenu();

		html.EndPage();
		html.EndContent();
	}
}

///////////////////////////////////////////////////////////////////////
// Create

void CWebAthlExtension::CreateTablesExecute(CHtmlWriter* pHtml,
											CHttpServerProperties* pProp,
											DWORD dwTable)
{
	try
	{
		CString strConnect = pProp->GetDefaultConnect();
		CString strSQL;

		CDatabase db;
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );


		try		// Table Drop
		{
			strSQL.Format("DROP TABLE %s", CDBTable::GetName(dwTable) );
			db.ExecuteSQL( strSQL );

			*pHtml << _T("Table <B>");
			*pHtml << _T( CDBTable::GetName(dwTable) );
			*pHtml << _T("</B> Dropped<BR>\r\n");
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		try		// Table Create
		{
			CUtil::LoadLongResource(strSQL, CDBTable::GetId(dwTable) );
			db.ExecuteSQL( strSQL );

			*pHtml << _T("Table <B>");
			*pHtml << _T( CDBTable::GetName(dwTable) );
			*pHtml << _T("</B> Created<BR>\r\n");
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		db.Close( );
	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		pEx->Delete();
	}
}

void CWebAthlExtension::CreateViewsExecute(CHtmlWriter* pHtml,
										   CHttpServerProperties* pProp,
										   DWORD dwView)
{
	try
	{
		CString strConnect = pProp->GetDefaultConnect();
		CString strSQL;

		CDatabase db;
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );

		try		// View Drop
		{
			strSQL.Format("DROP VIEW %s", CDBView::GetName(dwView) );
			db.ExecuteSQL( strSQL );

			*pHtml << _T("View <B>");
			*pHtml << _T( CDBView::GetName(dwView) );
			*pHtml << _T("</B> Dropped<BR>\r\n");
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		try		// View Create
		{
			CUtil::LoadLongResource(strSQL, CDBView::GetId(dwView) );
			db.ExecuteSQL( strSQL );

			*pHtml << _T("View <B>");
			*pHtml << _T( CDBView::GetName(dwView) );
			*pHtml << _T("</B> Created<BR>\r\n");
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}

		db.Close( );
	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		pEx->Delete();
	}
}

void CWebAthlExtension::CreateForeignKeysExecute(CHtmlWriter* pHtml,
												 CHttpServerProperties* pProp,
												 DWORD dwCreateDrop,
												 DWORD dwTable)
{
	BOOL bDrop = FALSE;
	
	if( CMaintainDatabase::IsMember( dwCreateDrop, CMaintainDatabase::DropForeignKeys) )
	{
		bDrop = TRUE;
	}

	try
	{
		CString strConnect = pProp->GetDefaultConnect();
		CString strSQL;

		CDatabase db;
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );

		if( bDrop )
		{
			try		// Foreign Key Drop
			{
				CUtil::LoadLongResource(strSQL, CDBForeignKey::GetIdDrop(dwTable) );
				db.ExecuteSQL( strSQL );

				*pHtml << _T("Foreign Keys on <B>");
				*pHtml << _T( CDBForeignKey::GetName(dwTable) );
				*pHtml << _T("</B> Dropped<BR>\r\n");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
		}
		else
		{
			try		// Foreign Key Create
			{
				CUtil::LoadLongResource(strSQL, CDBForeignKey::GetId(dwTable) );
				db.ExecuteSQL( strSQL );

				*pHtml << _T("Foreign Keys on <B>");
				*pHtml << _T( CDBForeignKey::GetName(dwTable) );
				*pHtml << _T("</B> Created<BR>\r\n");
			}
			catch (CDBException* pEx)
			{
				*pHtml << pEx;

				pEx->Delete();
			}
		}
		db.Close( );
	}
	catch (CDBException* pEx)
	{
		*pHtml << pEx;

		pEx->Delete();
	}
}

void CWebAthlExtension::BulkCopyExecute(CHtmlWriter* pHtml,
										CHttpServerProperties* pProp,
										DWORD dwImport,
										DWORD dwTable)
{
	if( !pProp->IsEmpty(CHtmlKey::ODBC,CHtmlKey::BackupFolder) && 
		_tcslen(pProp->Get(CHtmlKey::ODBC,CHtmlKey::BackupFolder)) > 0 )
	{
		if( CUtil::CreateFolders(pProp) )
		{
			BOOL bImport = FALSE;
			
			if( CMaintainDatabase::IsMember( dwImport, CMaintainDatabase::ImportData) )
			{
				bImport = TRUE;
			}

			CString strUsername = pProp->Get(CHtmlKey::ODBC, CHtmlKey::UID);
			CString strPassword = pProp->Get(CHtmlKey::ODBC, CHtmlKey::PWD);

			bool bTrustedConnection = false;

			CString strDSN = pProp->Get(CHtmlKey::ODBC, CHtmlKey::DSN);

			CString strServer = pProp->Get(CHtmlKey::ODBC, CHtmlKey::SERVER);
			CString strDatabase = pProp->Get(CHtmlKey::ODBC, CHtmlKey::DATABASE);
			CString strDriver = pProp->Get(CHtmlKey::ODBC, CHtmlKey::DRIVER);

			bool bFirstRowIsColumnNames = true;

			bool bHtml = false;

			CString strQuotedIdentifier = _T("\"");

			CString strFieldTerminator = _T(",");
			//CString strRowTerminator = _T("\n");

			int dRowCountMark = 100;
			bool bRowCountMark = false;

			CString strConfigSQL;


			//if( bImport )
			//{
			//	CreateTablesExecute(pHtml, pProp, dwTable);
			//}

			CString strLogFileName = CUtil::GetFolderLog(pProp) + CDBTable::GetName(dwTable) + _T(".txt");
			CStringStream* strLog = new CStringStream( NULL, strLogFileName );

			CString strErrorFileName = CUtil::GetFolderError(pProp) + CDBTable::GetName(dwTable) + _T(".txt");
			CStringStream* strErr = new CStringStream( NULL, strErrorFileName );

			CString strQueryString = CDBTable::GetName(dwTable);

			CString strOutputFileName;
			CString strInputFileName;

			CString strFileName = CUtil::GetFolderData(pProp) + CDBTable::GetName(dwTable) + _T(".csv");

			if( bImport )
			{
				strInputFileName = strFileName;
				//strConfigSQL = _T("DELETE FROM ") + CDBTable::GetName(dwTable);
			}
			else
			{
				strOutputFileName = strFileName;
			}


			try
			{
				CBulkCopy bulkCopy(	strLog,
									strErr,
									strUsername,
									strPassword,
									bTrustedConnection,
									strDSN,
									strServer,
									strDatabase,
									strDriver,
									bFirstRowIsColumnNames,
									bHtml,
									strQuotedIdentifier,
									strFieldTerminator,
									//szRowTerminator,
									strOutputFileName,
									strInputFileName,
									strQueryString,
									dRowCountMark,
									bRowCountMark,
									strConfigSQL );

				if( bImport )
				{
					bulkCopy.DatabaseCopyIn();
				}
				else
				{
					bulkCopy.DatabaseCopyOut();
				}
				bulkCopy.PrintStatistics();

				long nSuccessRecordCount = bulkCopy.GetSuccessRecordCount();
				long nFailRecordCount = bulkCopy.GetFailRecordCount();

				*pHtml << _T("<P>");
				*pHtml << _T( CMaintainDatabase::GetName(dwImport) );
				*pHtml << _T(" <B>");
				*pHtml << _T( CDBTable::GetName(dwTable) );
				*pHtml << _T("</B> -> ");
				*pHtml << _T( strFileName );
				*pHtml << _T("\r\n");

				*pHtml << _T("<UL>\r\n");

				*pHtml << _T("  <LI><B>");
				*pHtml << _T( CDBTable::GetName(dwTable) );
				*pHtml << _T("</B> (<B>");
				*pHtml <<     nSuccessRecordCount;
				*pHtml << _T("</B> row(s) copied)</LI>\r\n");

				if( nFailRecordCount > 0 )
				{
					*pHtml << _T("  <LI><B>");
					*pHtml << _T( CDBTable::GetName(dwTable) );
					*pHtml << _T("</B> (<B>");
					*pHtml <<     nFailRecordCount;
					*pHtml << _T("</B> row(s) failed) (see log file for details)</LI>\r\n");
				}
				*pHtml << _T("</UL>\r\n</P>\r\n");
			}
			catch (CDBException* pEx)
			{
				*strErr << pEx;
				strErr->Flush();

				*pHtml << pEx;

				pEx->Delete();
			}
			catch( CFileException* pEx )
			{
				*strErr << pEx;
				strErr->Flush();

				*pHtml << pEx;

				pEx->Delete();
			}

			delete strLog;
			delete strErr;
		}
		else
		{
			*pHtml << _T("Unable to Create Export / Import Folder.<BR>\r\n");
			*pHtml << _T(strerror( errno ))
				   << _T(".<BR>\r\n");
		}
	}
	else
	{
		*pHtml << _T("Please Set your Export / Import Folder First.<BR>\r\n");
	}
}

///////////////////////////////////////////////////////////////////////
// Maintenance

void CWebAthlExtension::MaintenanceSetFolderForm(CHttpServerContext* pCtxt,
									  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		html << _T("Select a Folder to store Table Export / Import CSV Files.<BR>\r\n");

		html << _T("<BR>\r\n");
		html << _T("Note: This Folder is Local to the Web Server.<BR>\r\n");
		html << _T("Please ensure that this Folder exists and that the Web Server has <B>write</B> privileges to it.<BR>\r\n");

		CString strFolder = prop.GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder);

		if( prop.IsEmpty(strFolder) )
		{
			strFolder.Empty();
		}


		html.StartForm("Export / Import Folder", CPage::MaintenanceSetFolderExecute);

		html.EditTextBoxLarge("Folder","BackupFolder", strFolder);
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::MaintenanceSetFolderExecute(CHttpServerContext* pCtxt,
								  LPTSTR szBackupFolder,
								  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Maintenance Menu", 0);

		html.EndMenu();

		TCHAR pszFilePath[_MAX_PATH];

		if( _tfullpath( pszFilePath, szBackupFolder, _MAX_PATH ) && 
			_tcslen(szBackupFolder) > 0 )
		{
			LONG nStatus = prop.Set(CHtmlKey::ODBC, CHtmlKey::BackupFolder, pszFilePath );

			if( nStatus == ERROR_SUCCESS )
			{
				if( CUtil::CreateFolders(&prop) )
				{
					html << _T("Export / Import Folder Set to : <BR>\r\n<blockquote><B>");
					html << _T(prop.GetEx(CHtmlKey::ODBC,CHtmlKey::BackupFolder));
					html << _T("</B></blockquote><BR>\r\n");

					html << _T("Table Export / Import CSV Files should be placed in : <BR>\r\n<blockquote><B>");
					html << _T( CUtil::GetFolderData(&prop) );
					html << _T("</B></blockquote><BR>\r\n");

					html << _T("Logs will be stored in : <BR>\r\n<blockquote><B>");
					html << _T( CUtil::GetFolderLog(&prop) );
					html << _T("</B></blockquote><BR>\r\n");

					html << _T("Errors will be stored in : <BR>\r\n<blockquote><B>");
					html << _T( CUtil::GetFolderError(&prop) );
					html << _T("</B></blockquote><BR>\r\n");
				}
				else
				{
					html << _T("Unable to Create Export / Import Folder.<BR>\r\n");
					html << _T(strerror( errno ))
						 << _T(".<BR>\r\n");
				}
			}
			else
			{
				html << _T("Unable to Save Export / Import Folder.<BR>\r\n");
			}
		}
		else
		{
			html << _T("Invalid Folder : <BR>\r\n<blockquote><B>");
			html << _T(szBackupFolder);
			html << _T("</B></blockquote><BR>\r\n");

			html << _T("Please ensure that this Folder exists and that the Web Server has write privileges to it.<BR>\r\n");
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::MaintenanceCryptPasswordsForm(CHttpServerContext* pCtxt,
													  LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Maintenance Menu", 0);

		html.EndMenu();


		html.StartForm("Encrypt / Decrypt User Passwords", CPage::MaintenanceCryptPasswordsExecute);

		html.RadioButton("User Passwords", "Encrypt All", "Decrypt", "0", "0");
		html.RadioButton("",               "Decrypt All", "Decrypt", "1", "0");
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Run);
		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::MaintenanceCryptPasswordsExecute(CHttpServerContext* pCtxt,
														 LPTSTR szDecrypt,
														 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Maintenance Menu", 0);

		html.EndMenu();

		if( atoi(szDecrypt) )
		{
			DecryptPasswordsExecute(&html, &prop);
		}
		else
		{
			EncryptPasswordsExecute(&html, &prop);
		}

		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::EncryptPasswordsExecute(CHtmlWriter* pHtml,
												CHttpServerProperties* pProp)
{
		try
		{
			CString strConnect = pProp->GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );

			CSecurityPersonSet rs( &db );
			strSQL.Format( "SELECT * FROM SecurityPerson" );
			rs.Open(CRecordset::dynaset, strSQL );


			CString strPwd;

			CCryptByteArray* cbaPwd = new CCryptByteArray( );

			cbaPwd->Init( pProp->GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
						  atoi(pProp->GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

			while( !rs.IsEOF( ) )
			{
				cbaPwd->Set( rs.m_Password );

				if( cbaPwd->IsCrypt( ) )
				{
					// Password is encrypted

					*pHtml << _T("Password for Person : <B>");
					*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
					*pHtml << _T("</B> is already Encrypted.<BR>\r\n");
				}
				else
				{
					// Password is not encrypted
					cbaPwd->EnCrypt( );

					if( cbaPwd->GetSuccess( ) )
					{
						rs.Edit( );

						cbaPwd->Copy( &(rs.m_Password) );

						if( !rs.CanUpdate( ) )
							*pHtml << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
						if( !rs.Update( ) )
							*pHtml << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
						else
						{
							*pHtml << _T("Encrypted Password for Person : <B>");
							*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
							*pHtml << _T("</B>.<BR>\r\n");
						}
					}
					else
					{
						*pHtml << _T(cbaPwd->GetString());
						*pHtml << _T(" for Person : <B>");
						*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
						*pHtml << _T("</B>.<BR>\r\n");
					}
				}
				rs.MoveNext( );
			}
			
			delete cbaPwd;

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}
}

void CWebAthlExtension::DecryptPasswordsExecute(CHtmlWriter* pHtml,
												CHttpServerProperties* pProp)
{
		try
		{
			CString strConnect = pProp->GetDefaultConnect();
			CString strSQL;

			CDatabase db;
			db.OpenEx( strConnect, CDatabase::noOdbcDialog );


			CSecurityPersonSet rs( &db );
			strSQL.Format( "SELECT * FROM SecurityPerson" );
			rs.Open(CRecordset::dynaset, strSQL );


			CString strPwd;

			CCryptByteArray* cbaPwd = new CCryptByteArray( );

			cbaPwd->Init( pProp->GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
						  atoi(pProp->GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );

			while( !rs.IsEOF( ) )
			{
				cbaPwd->Set( rs.m_Password );

				if( cbaPwd->IsCrypt( ) )
				{
					// Password is encrypted

					cbaPwd->DeCrypt( );

					if( cbaPwd->GetSuccess( ) )
					{
						rs.Edit( );

						cbaPwd->Copy( &(rs.m_Password) );

						if( !rs.CanUpdate( ) )
							*pHtml << _T(CRecordsetEx::m_szMsgCannotUpdate) << _T("<BR>\r\n");
						if( !rs.Update( ) )
							*pHtml << _T(CRecordsetEx::m_szMsgNotUpdated) << _T("<BR>\r\n");
						else
						{
							*pHtml << _T("Decrypted Password for Person : <B>");
							*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
							*pHtml << _T("</B>.<BR>\r\n");
						}
					}
					else
					{
						*pHtml << _T(cbaPwd->GetString());
						*pHtml << _T(" for Person : <B>");
						*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
						*pHtml << _T("</B>.<BR>\r\n");
					}
				}
				else
				{
					// Password is not encrypted

					*pHtml << _T("Password for Person : <B>");
					*pHtml << _T( CConvert::itoa(rs.m_PersonID) );
					*pHtml << _T("</B> is already Decrypted.<BR>\r\n");
				}
				rs.MoveNext( );
			}
			
			delete cbaPwd;

			rs.Close( );
			db.Close( );
		}
		catch (CDBException* pEx)
		{
			*pHtml << pEx;

			pEx->Delete();
		}
}

void CWebAthlExtension::MaintenanceDisableUsersForm(CHttpServerContext* pCtxt,
										 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		int iEnabled = atoi(prop.GetEx(CHtmlKey::UserAccess, CHtmlKey::Enabled));

		html.StartForm("User Access", CPage::MaintenanceDisableUsersExecute);

		html.CheckBox("User Access", "Enabled", "Enabled", "1", CConvert::itoa(iEnabled));
		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Save);
		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::MaintenanceDisableUsersExecute(CHttpServerContext* pCtxt,
									 LPTSTR szEnabled,
									 LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Maintenance Menu", 0);

		html.EndMenu();

		LONG nStatus = prop.Set(CHtmlKey::UserAccess,CHtmlKey::Enabled, szEnabled );

		if( nStatus == ERROR_SUCCESS )
		{
			html << _T("Settings Saved<BR>\r\n");
			html << _T("<BR>\r\nUser Access : <B>");
			if( atoi( prop.GetEx(CHtmlKey::UserAccess,CHtmlKey::Enabled) )  )
			{
				html << _T("Enabled</B><BR>\r\n");
				html << _T("<BR>\r\nAll User Logins are Enabled.<BR>\r\n");
			}
			else
			{
				html << _T("Disabled</B><BR>\r\n");
				html << _T("<BR>\r\nAll User Logins are Disabled.<BR>\r\n");
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

void CWebAthlExtension::MaintenanceMaintainDatabaseForm(CHttpServerContext* pCtxt,
											 LPTSTR szSubmit,
											 LPTSTR szInit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, CHtmlKey::Cancel, 0);

		html.EndMenu();

		DWORD dwItem = atol(szInit);


		CBitMaskEnum* enumList;
		BOOL bReverse = FALSE;

		switch( dwItem )
		{
			case CMaintainDatabase::CreateViews :
				enumList = new CDBView();
				break;
			case CMaintainDatabase::CreateForeignKeys :
			case CMaintainDatabase::DropForeignKeys :
				enumList = new CDBForeignKey();
				break;
			//case CMaintainDatabase::CreateStoredProcedures :
			//	enumList = new CDBStoredProcedure();
			//	break;
			case CMaintainDatabase::CreateTables :
				enumList = new CDBTable();
				bReverse = TRUE;
				break;
			case CMaintainDatabase::ExportData :
			case CMaintainDatabase::ImportData :
				enumList = new CDBTable();
				break;
			default :
				enumList = new CBitMaskEnum();
				break;
		}

		html << CMaintainDatabase::GetMessage(dwItem);

		html.StartForm(
			CMaintainDatabase::GetName(dwItem), 
			CPage::MaintenanceMaintainDatabaseExecute);

		html.HiddenText("ItemList", szInit);

		html.StartListBox(
			CMaintainDatabase::GetTitle(dwItem),
			"Items", 10, TRUE);

		DWORD dwEnum = enumList->Enumerator( bReverse );
		while( enumList->GetNext( &dwEnum ) )
		{
			html.AddSelectBox(
				enumList->GetName( ), 
				CConvert::dwtoa(dwEnum), 
				"0");
		}
		html.EndSelectBox();

		delete enumList;

		html.HorizontalRule();

		html.SubmitButton(CHtmlKey::Run);
		html.EndForm();


		html.EndPage();
		html.EndContent();
	}
}

void CWebAthlExtension::MaintenanceMaintainDatabaseExecute(CHttpServerContext* pCtxt,
												LPTSTR szItemList,
												LPTSTR szItems,
												LPTSTR szSubmit)
{
	CHtmlWriter html = CHtmlWriter( pCtxt, this );
	CHttpServerProperties prop = CHttpServerProperties( &html );
	CAuthenticator auth = CAuthenticator( &html );

	if( auth.CheckPermission(CModule::Maintenance) )
	{
	    html.SetContent();
	    html.EndHeader();

		html.WritePageTitle(auth.m_strOrgName);
		html.WritePageMenu(auth.m_strUserName, auth.m_strHeading);
		html.WritePageMenuItem(auth.m_strBackLink, "Maintenance Menu", 0);

		html.EndMenu();

		DWORD dwItem = atol(szItemList);
		DWORD dwItems = CCSV::GetBitMask(szItems, CWebAthlExtension::chIsapiDelimiter);

		CBitMaskEnum* enumList;
		BOOL bReverse = FALSE;

		switch( dwItem )
		{
			case CMaintainDatabase::CreateViews :
				enumList = new CDBView();
				break;
			case CMaintainDatabase::CreateForeignKeys :
			case CMaintainDatabase::DropForeignKeys :
				enumList = new CDBForeignKey();
				break;
			//case CMaintainDatabase::CreateStoredProcedures :
			//	enumList = new CDBStoredProcedure();
			//	break;
			case CMaintainDatabase::CreateTables :
				enumList = new CDBTable();
				bReverse = TRUE;
				break;
			case CMaintainDatabase::ExportData :
			case CMaintainDatabase::ImportData :
				enumList = new CDBTable();
				break;
			default :
				enumList = new CBitMaskEnum();
				break;
		}

		DWORD dwEnum = enumList->Enumerator( bReverse );
		while( enumList->GetNext( &dwEnum ) )
		{
			if( enumList->IsMember( dwItems, dwEnum ) )
			{
				switch( dwItem )
				{
					case CMaintainDatabase::CreateTables :
						CreateTablesExecute(&html, &prop, dwEnum);
						break;
					case CMaintainDatabase::CreateViews :
						CreateViewsExecute(&html, &prop, dwEnum);
						break;
					case CMaintainDatabase::CreateForeignKeys :
						CreateForeignKeysExecute(&html, &prop, dwItem, dwEnum);
						break;
					case CMaintainDatabase::DropForeignKeys :
						CreateForeignKeysExecute(&html, &prop, dwItem, dwEnum);
						break;
					//case CMaintainDatabase::CreateStoredProcedures :
					//	CreateStoredProceduresExecute(&html, &prop, dwEnum);
					//	break;
					case CMaintainDatabase::ExportData :
						BulkCopyExecute(&html, &prop, dwItem, dwEnum);
						break;
					case CMaintainDatabase::ImportData :
						BulkCopyExecute(&html, &prop, dwItem, dwEnum);
						break;
				}
			}
		}

		delete enumList;

		html.EndPage();
		html.EndContent();
	}
}
