// CAuthenticator.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HttpServerProperties.h"
#include "HttpServerVariableEx.h"
#include "HtmlWriter.h"
#include "CryptByteArray.h"
#include "Module.h"
#include "Authenticator.h"

#include "Calculate.h"

#include "ValidateSet.h"
#include "FinancialSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Authenticator

int CAuthenticator::m_iDboRoleId = -1;
LPCTSTR CAuthenticator::m_szDboName = _T("dbo");

LPCTSTR CAuthenticator::m_szGuestUser = _T("Web_User");
LPCTSTR CAuthenticator::m_szMemberRole = _T("Member");

int CAuthenticator::m_iMinPwdLen = 8;

/////////////////////////////////////////////////////////////////////////////
// Constructor

CAuthenticator::CAuthenticator( CHtmlWriter* pHtml )
{
	m_pHtml = pHtml;

	m_iRoleID = FALSE;
	m_iPersonID = -1;
	m_iPermission = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CAuthenticator::~CAuthenticator( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

void CAuthenticator::AccessDeniedPage()
{
	m_pHtml->SetContent( );
	m_pHtml->EndHeader( );

	m_pHtml->WritePageTitle( m_strOrgName );
	m_pHtml->WritePageMenu( m_strLoginName, m_strOrgName);
	m_pHtml->WritePageMenuItem( CPage::DefaultEntry, "Exit", 0 );
	m_pHtml->EndMenu( );

	*m_pHtml << _T("Access Denied<BR>\r\n");

	m_pHtml->EndPage( );
	m_pHtml->EndContent( );
}

void CAuthenticator::GetCookies()
{
	m_strBackLink.Format(m_pHtml->GetCookie(CHtmlKey::BackLink));
	m_strFrwdLink.Format(m_pHtml->GetCookie(CHtmlKey::FrwdLink));

	m_strHeading.Format(m_pHtml->GetCookie(CHtmlKey::Heading));
	m_strOrgName.Format(m_pHtml->GetCookie(CHtmlKey::OrgName));
	//m_strLoginName.Format(m_pHtml->GetCookie(CHtmlKey::LoginName));
}

int CAuthenticator::ValidateLogin(LPCTSTR szLoginName, LPCTSTR szHexPwd)
{
	CHttpServerProperties prop = CHttpServerProperties( m_pHtml );

	GetCookies();
	m_strLoginName.Format(szLoginName);

	m_iRoleID = FALSE;


	CString strCookiePwd;

	CCryptByteArray* cbaPwd = new CCryptByteArray( );
	cbaPwd->SetHexString( szHexPwd );
	cbaPwd->Init(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Password),
				 atoi(prop.GetEx(CHtmlKey::Cryptography,CHtmlKey::Enabled)) );
	cbaPwd->DeCrypt( );

	strCookiePwd = cbaPwd->GetString( );


	if( !m_strLoginName.CompareNoCase( prop.GetEx(CHtmlKey::ODBC,CHtmlKey::UID) ) &&
		!strCookiePwd.Compare( prop.GetEx(CHtmlKey::ODBC,CHtmlKey::PWD) )   )
	{
		m_strUserName = CAuthenticator::m_szDboName;
		m_strRoleName = CAuthenticator::m_szDboName;

		m_iPersonID = 0;

		m_iRoleID = CAuthenticator::m_iDboRoleId;

		m_iPermission = 0xffffffff;

		return m_iRoleID;
	}
	
	CString strConnect = prop.GetDefaultConnect( );

	try
	{
		CString strSQL;
		CString strSQLtmp;

		CDatabase db;
	
		db.OpenEx( strConnect, CDatabase::noOdbcDialog );

		CValidateSet rs( &db );

		strSQLtmp += _T("SELECT Person.*, SecurityPerson.*, SecurityRole.* ");
		strSQLtmp += _T(" FROM Person, SecurityPerson, SecurityRole ");
		strSQLtmp += _T(" WHERE SecurityPerson.RoleID = SecurityRole.RoleID ");
		strSQLtmp += _T(" AND SecurityPerson.PersonID = Person.PersonID ");
		strSQLtmp += _T(" AND SecurityPerson.LoginName = '%s' ");
		
		strSQL.Format(strSQLtmp, szLoginName);
		rs.Open(CRecordset::forwardOnly, strSQL );

		if( !rs.IsEOF( ) )
		{
			CString strPwd;
			cbaPwd->Set( rs.m_Password );
			cbaPwd->DeCrypt( );
			strPwd = cbaPwd->GetString( );

			if( !_tcscmp(szLoginName, CAuthenticator::m_szGuestUser) )
			{
				m_iRoleID = rs.m_RoleID;
				m_strUserName.Format("%s %s", rs.m_FirstName, rs.m_LastName);
				m_strRoleName.Format("%s", rs.m_RoleName);
				m_iPersonID = 0;
				m_iPermission = rs.IsFieldNull( &rs.m_Permission ) ? 0 : rs.m_Permission;
			}
			else if( !strPwd.Compare(strCookiePwd) )
			{
				m_iRoleID = rs.m_RoleID;
				m_strUserName.Format("%s %s", rs.m_FirstName, rs.m_LastName);
				m_strRoleName.Format("%s", rs.m_RoleName);
				m_iPersonID = rs.m_PersonID;
				m_iPermission = rs.IsFieldNull( &rs.m_Permission ) ? 0 : rs.m_Permission;
			}
			else
			{
				m_strError.Format("Invalid Login Name or Password");
			}
		}
		else
		{
			m_strError.Format("Invalid Login Name or Password");
		}
		rs.Close( );
		
		if( m_iRoleID )
		{
			if( !m_strRoleName.Compare(CAuthenticator::m_szMemberRole) )
			{
				strSQL.Format( "SELECT * FROM Financial WHERE PersonID = %d ORDER BY Year DESC", m_iPersonID );
				CFinancialSet rsFinc( &db );
				rsFinc.Open(CRecordset::forwardOnly, strSQL );

				if( !rsFinc.IsEOF( ) )
				{
					if( !CCalculate::Current( rsFinc.m_Year, rsFinc.m_RegistrationTypeID, strConnect ) )
					{
						m_iRoleID = FALSE;
						m_strError.Format("Membership Lapsed");
					}
				}
				else
				{
					m_iRoleID = FALSE;
					m_strError.Format("Membership Invalid");
				}
				rsFinc.Close( );
			}
		}

		BOOL bUserAccessEnabled = atoi(prop.GetEx(CHtmlKey::UserAccess,CHtmlKey::Enabled));

		if( m_iRoleID )
		{
			if( !bUserAccessEnabled && !HasPermission(CModule::Security) )
			{
				m_iRoleID = FALSE;
				m_strError.Format("The System Administrator has Disabled User Access at this time to perform System Maintenance.<BR>\r\nPlease try again later.");
			}
		}

		db.Close( );
	}
	catch (CDBException* pEx)
	{
		m_iRoleID = FALSE;
		m_strError = pEx->m_strError;

		pEx->Delete();
	}

	delete cbaPwd;

	return m_iRoleID;
}

BOOL CAuthenticator::CheckPermission(DWORD dwModules)
{
	BOOL bPermission = FALSE;

	CString strHexPwd = m_pHtml->GetCookie(CHtmlKey::Password);
	CString strLoginName = m_pHtml->GetCookie(CHtmlKey::LoginName);

	m_iRoleID = ValidateLogin(strLoginName, strHexPwd);

	bPermission = HasPermission(dwModules);

	if( !bPermission || !m_iRoleID )
	{
		AccessDeniedPage();
	}

	return (bPermission && m_iRoleID);
}

BOOL CAuthenticator::HasPermission(DWORD dwModules)
{
	BOOL bPermission = FALSE;

	if( dwModules == CModule::none )
	{
		return TRUE;
	}

	CModule module;
	DWORD dwModuleEnum = module.Enumerator( );
	while( module.GetNext( &dwModuleEnum ) )
	{
		if( (dwModuleEnum & dwModules) == dwModuleEnum )
		{
			bPermission |= (BOOL)CModule::IsMember(m_iPermission, dwModuleEnum);
		}
	}

	return bPermission;
}
