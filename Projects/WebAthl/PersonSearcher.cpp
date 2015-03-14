// PersonSearcher.cpp : implementation file
//

#include "stdafx.h"

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "HttpServerVariableEx.h"
#include "HttpServerProperties.h"
#include "HtmlWriter.h"

#include "PersonSearcher.h"

#include "CSV.h"
#include "Convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonSearcher

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CPersonSearcher::CPersonSearcher( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CPersonSearcher::~CPersonSearcher( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

BOOL CPersonSearcher::IsSearchValid(CHtmlWriter* pHtml, 
									CHttpServerProperties* pProp,
									LPTSTR szPersonID,
									LPTSTR szLastName,
									LPTSTR szFirstName,
									LPTSTR szMiddleName,
									LPTSTR szDobDAY,
									LPTSTR szDobMONTH,
									LPTSTR szDobYEAR,
									LPTSTR szSex)
{
	if( atoi(szPersonID) > 0 )
	{
		return TRUE;
	}
	else
	{
		BOOL bSearchIsValid = FALSE;

		int nLastNameLen = _tcslen(szLastName);
		int nFirstNameLen = _tcslen(szFirstName);
		int nMiddleNameLen = _tcslen(szMiddleName);
		int nDobDAY = atoi(szDobDAY);
		int nDobMONTH = atoi(szDobMONTH);
		int nDobYEAR = atoi(szDobYEAR);
		int nSexLen = _tcslen(szSex);

		CString strLastNameList = pProp->GetEx(CHtmlKey::PersonSearch,CHtmlKey::LastName);
		CString strFirstNameList = pProp->GetEx(CHtmlKey::PersonSearch,CHtmlKey::FirstName);
		CString strMiddleNameList = pProp->GetEx(CHtmlKey::PersonSearch,CHtmlKey::MiddleName);
		CString strDateOfBirthList = pProp->GetEx(CHtmlKey::PersonSearch,CHtmlKey::DateOfBirth);
		CString strSexList = pProp->GetEx(CHtmlKey::PersonSearch,CHtmlKey::Sex);

		int nLastName;
		int nFirstName;
		int nMiddleName;
		int nDateOfBirth;
		int nSex;

		CStringArray* strLastNameItems = new CStringArray();
		CStringArray* strFirstNameItems = new CStringArray();
		CStringArray* strMiddleNameItems = new CStringArray();
		CStringArray* strDateOfBirthItems = new CStringArray();
		CStringArray* strSexItems = new CStringArray();

		CCSV csv;

		csv.GetItems(strLastNameItems, &strLastNameList);
		csv.GetItems(strFirstNameItems, &strFirstNameList);
		csv.GetItems(strMiddleNameItems, &strMiddleNameList);
		csv.GetItems(strDateOfBirthItems, &strDateOfBirthList);
		csv.GetItems(strSexItems, &strSexList);

		int nLastNameItems = strLastNameItems->GetSize( );
		int nFirstNameItems = strFirstNameItems->GetSize( );
		int nMiddleNameItems = strMiddleNameItems->GetSize( );
		int nDateOfBirthItems = strDateOfBirthItems->GetSize( );
		int nSexItems = strSexItems->GetSize( );

		int nMaxNameItems = CUtil::Max(5,   nLastNameItems, 
											nFirstNameItems, 
											nMiddleNameItems, 
											nDateOfBirthItems, 
											nSexItems);

		int nIndex = 0;

		for( nIndex = 0 ; nIndex < nMaxNameItems ; nIndex++ )
		{
			nLastName = ( nIndex < nLastNameItems ) ? atoi(strLastNameItems->GetAt(nIndex)) : 0 ;
			nFirstName = ( nIndex < nFirstNameItems ) ? atoi(strFirstNameItems->GetAt(nIndex)) : 0 ;
			nMiddleName = ( nIndex < nMiddleNameItems ) ? atoi(strMiddleNameItems->GetAt(nIndex)) : 0 ;
			nDateOfBirth = ( nIndex < nDateOfBirthItems ) ? atoi(strDateOfBirthItems->GetAt(nIndex)) : 0 ;
			nSex = ( nIndex < nSexItems ) ? atoi(strSexItems->GetAt(nIndex)) : 0 ;

			if( ( nLastNameLen   < nLastName    ) || 
				( nFirstNameLen  < nFirstName   ) || 
				( nMiddleNameLen < nMiddleName  ) || 
				( nDobDAY        < nDateOfBirth ) ||
				( nDobMONTH      < nDateOfBirth ) || 
				( nDobYEAR       < nDateOfBirth ) || 
				( nSexLen        < nSex         )  )  
			{
				bSearchIsValid = FALSE;
			}
			else
			{
				bSearchIsValid = TRUE;
				break;
			}
		}

		if( !bSearchIsValid )
		{
			*pHtml << _T("<P>Not Enough Search Information Entered.</P>\r\n");
			*pHtml << _T("<P>Please Provide :</P>\r\n");

			*pHtml << _T("<UL>\r\n");
			*pHtml << _T("<LI>A Numeric 'PersonID'</LI>\r\n");
			*pHtml << _T("</UL>\r\n");

			for( nIndex = 0 ; nIndex < nMaxNameItems ; nIndex++ )
			{
				nLastName = ( nIndex < nLastNameItems ) ? atoi(strLastNameItems->GetAt(nIndex)) : 0 ;
				nFirstName = ( nIndex < nFirstNameItems ) ? atoi(strFirstNameItems->GetAt(nIndex)) : 0 ;
				nMiddleName = ( nIndex < nMiddleNameItems ) ? atoi(strMiddleNameItems->GetAt(nIndex)) : 0 ;
				nDateOfBirth = ( nIndex < nDateOfBirthItems ) ? atoi(strDateOfBirthItems->GetAt(nIndex)) : 0 ;
				nSex = ( nIndex < nSexItems ) ? atoi(strSexItems->GetAt(nIndex)) : 0 ;


				if( nLastName || nFirstName || nMiddleName || nDateOfBirth || nSex )
				{
					*pHtml << _T("<P>OR</P>\r\n");

					*pHtml << _T("<UL>\r\n");

					if( nLastName )
						*pHtml << _T("<LI>")
							   << _T(CConvert::itoa(nLastName))
							   << _T(" Characters in the 'Last Name' ")
							   << _T("</LI>\r\n");

					if( nFirstName )
						*pHtml << _T("<LI>")
							   << _T(CConvert::itoa(nFirstName))
							   << _T(" Characters in the 'First Name' ")
							   << _T("</LI>\r\n"); 

					if( nMiddleName )
						*pHtml << _T("<LI>")
							   << _T(CConvert::itoa(nMiddleName))
							   << _T(" Characters in the 'Middle Name' ")
							   << _T("</LI>\r\n"); 

					if( nDateOfBirth )
						*pHtml << _T("<LI>")
							   << _T("A Valid 'Date of Birth' ")
							   << _T("</LI>\r\n"); 

					if( nSex )
						*pHtml << _T("<LI>")
							   << _T("A Choice of 'Sex' ")
							   << _T("</LI>\r\n"); 

					*pHtml << _T("</UL>\r\n");
				}
			}
		}

		delete strLastNameItems;
		delete strFirstNameItems;
		delete strMiddleNameItems;
		delete strDateOfBirthItems;
		delete strSexItems;

		return bSearchIsValid;
	}
}

CString CPersonSearcher::GetDefaultSQL(LPTSTR szPersonID,
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
									   LPTSTR szContactPersonID)
{
	CString strSQL;

	if( atoi(szPersonID) > 0 )
	{
		strSQL.Format( "SELECT * FROM Person WHERE PersonID = %s ORDER BY LastName, FirstName ", szPersonID );
	}
	else 
	{
		strSQL.Format( "SELECT * FROM Person " );

		bool bWhereClauseUsed = FALSE;

		if (( (_tcslen( szLastName ) > 0) ))
		{
			CString strLastName = szLastName;
			strLastName.Replace("'", "''");

			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" LastName LIKE '%");
			strSQL += _T(strLastName);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szFirstName ) > 0) ))
		{
			CString strFirstName = szFirstName;
			strFirstName.Replace("'", "''");

			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" FirstName LIKE '%");
			strSQL += _T(strFirstName);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szMiddleName ) > 0) ))
		{
			CString strMiddleName = szMiddleName;
			strMiddleName.Replace("'", "''");

			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" MiddleName LIKE '%");
			strSQL += _T(strMiddleName);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szAddress1 ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Address1 LIKE '%");
			strSQL += _T(szAddress1);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szAddress2 ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Address2 LIKE '%");
			strSQL += _T(szAddress2);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szTown ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Town LIKE '%");
			strSQL += _T(szTown);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szState ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" State LIKE '%");
			strSQL += _T(szState);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szCountry ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Country LIKE '%");
			strSQL += _T(szCountry);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szPostCode ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" PostCode LIKE '%");
			strSQL += _T(szPostCode);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szPhoneHm ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" PhoneHm LIKE '%");
			strSQL += _T(szPhoneHm);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szPhoneWk ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" PhoneWk LIKE '%");
			strSQL += _T(szPhoneWk);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szFax ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Fax LIKE '%");
			strSQL += _T(szFax);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szMobile ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Mobile LIKE '%");
			strSQL += _T(szMobile);
			strSQL += _T("%'");
		}

		if (( (_tcslen( szEmail ) > 0) ))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" email LIKE '%");
			strSQL += _T(szEmail);
			strSQL += _T("%'");
		}

		if ( atoi(szDobDAY) > 0 )
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" dobDAY = ");
			strSQL += _T(szDobDAY);
			strSQL += _T(" ");
		}

		if ( atoi(szDobMONTH) > 0 )
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" dobMONTH = ");
			strSQL += _T(szDobMONTH);
			strSQL += _T(" ");
		}

		if ( atoi(szDobYEAR) > 0 )
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" dobYEAR = ");
			strSQL += _T(szDobYEAR);
			strSQL += _T(" ");
		}

		if ( (_tcslen( szSex ) > 0))
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" Sex LIKE '%");
			strSQL += _T(szSex);
			strSQL += _T("%'");
		}

		if ( atoi(szContactPersonID) > 0 )
		{
			if( bWhereClauseUsed )
				strSQL += _T(" AND ");
			else
			{
				strSQL += _T(" WHERE ");
				bWhereClauseUsed = TRUE;
			}

			strSQL += _T(" ContactPersonID = ");
			strSQL += _T(szContactPersonID);
			strSQL += _T(" ");
		}

		strSQL += _T(" ORDER BY LastName, FirstName ");
	}

	return strSQL;
}









