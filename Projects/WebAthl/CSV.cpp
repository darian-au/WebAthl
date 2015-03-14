// CCSV.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSV

/////////////////////////////////////////////////////////////////////////////
// Constructor

CCSV::CCSV(TCHAR chFieldTerminator)
{
	Init(chFieldTerminator, NULL);
}

CCSV::CCSV(LPCTSTR szFieldTerminator, LPCTSTR szQuotedIdentifier)
{
	Init(szFieldTerminator, szQuotedIdentifier);
}

void CCSV::Init(CString strFieldTerminator, LPCTSTR szQuotedIdentifier)
{
	m_ch = (char)0xb6; // ¶

	m_szSpecial = "¶¶";

	m_szQuotedIdentifier = szQuotedIdentifier;

	m_strFirstQuotedIdentifier = CString(m_szQuotedIdentifier).Left(1);

	if( !strFieldTerminator.IsEmpty() )
	{
		m_strFieldTerminator = strFieldTerminator;
	}
	else
	{
		m_strFieldTerminator = ",";
	}

	//m_strFieldTerminator = m_szFieldTerminator;
	m_strQuotedIdentifier;

	if( m_szQuotedIdentifier != NULL )
	{
		m_strQuotedIdentifier = m_szQuotedIdentifier;

		m_strDoubleQuotedIdentifier = (CString(m_szQuotedIdentifier[0]) + m_szQuotedIdentifier[0]);

		m_strTripleQuotedIdentifier = (m_strDoubleQuotedIdentifier + m_szQuotedIdentifier[0]);

		m_strFirstTripleQuotedIdentifier = (m_strFieldTerminator[0] + m_strTripleQuotedIdentifier);

		m_strFirstTripleSpecial += m_strFieldTerminator[0];
		m_strFirstTripleSpecial += m_szQuotedIdentifier[0];
		m_strFirstTripleSpecial += m_szSpecial;
	}
	else
	{
		m_strQuotedIdentifier.Empty( );
	}

	SetRecordCount( );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor
//CCSV::~CCSV()
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions
CStringArray* CCSV::GetItems(CStringArray* strItems, CString* strLine)
{
	CString strField;

	int nIndex = 0;
	int nQuotedIndex = -1;
	int nDoubleQuotedIndex = -1;
	int nLen = 0;

	int iFieldCount = 0;

	int iQuoteCount = 0;

	if( m_szQuotedIdentifier != NULL )
	{
		nDoubleQuotedIndex = strLine->Find( m_strDoubleQuotedIdentifier ) ;

		if( nDoubleQuotedIndex > -1 )
		{
			int nTripleQuotedIndex = strLine->Find( m_strTripleQuotedIdentifier ) ;

			if( nTripleQuotedIndex > -1 )
			{
				if( strLine->Left(3).Compare(m_strTripleQuotedIdentifier) == 0 )
				{
					strLine->SetAt(1, m_szSpecial[0]);
					strLine->SetAt(2, m_szSpecial[1]);
				}
				strLine->Replace( m_strFirstTripleQuotedIdentifier, m_strFirstTripleSpecial );
			}
			strLine->Replace( m_strDoubleQuotedIdentifier, m_szSpecial );
		}
	}

//	while( ((nIndex <= nLen) && (nIndex > -1)) || (iQuoteCount > 0) )
	while( (nIndex > -1) || (iQuoteCount > 0) )
	{
		nLen = strLine->GetLength();
		nIndex = strLine->FindOneOf( m_strFieldTerminator ) ;

		if( m_szQuotedIdentifier != NULL )
		{
			nQuotedIndex = strLine->FindOneOf( m_szQuotedIdentifier ) ;
		}


		if( ((nIndex > -1) && (nQuotedIndex > -1) && (nQuotedIndex < nIndex)) ||
			((nIndex <  0) && (nQuotedIndex > -1)) ||
			(iQuoteCount > 0)  
		)
		{
			if( iQuoteCount > 0 )
			{
				strField = strLine->SpanExcluding( m_szQuotedIdentifier );

				*strLine = strLine->Right( nLen - (nQuotedIndex +2) );

				if( nDoubleQuotedIndex > -1 )
					strField.Replace( m_szSpecial, m_szQuotedIdentifier );

				strItems->Add( strField );
				iFieldCount++;

				iQuoteCount--;
			}
			else
			{
				*strLine = strLine->Right( nLen - (nQuotedIndex +1) );

				iQuoteCount++;
			}
		}
		else
		{
			strField = strLine->SpanExcluding( m_strFieldTerminator );

			//if( not comma inside quoted field of last column )
			{
				strItems->Add( strField );
				iFieldCount++;
			}

			if( nIndex > -1 )
				*strLine = strLine->Right( nLen - (nIndex +1) );
		}
	}

	if( iFieldCount )
	{
		m_nRecordCount++;
		m_nSuccessRecordCount++;
	}

	return strItems;
}

LPCTSTR CCSV::GetFieldTerminator()
{	
	return m_strFieldTerminator;	
}

LPCTSTR CCSV::GetQuotedIdentifier()
{	
	return m_szQuotedIdentifier; 
}

CString CCSV::GetDoubleQuotedIdentifier()
{	
	return m_strDoubleQuotedIdentifier; 
}


long CCSV::GetRecordCount(bool bSuccessCount) const
{
	if( bSuccessCount )
		return m_nSuccessRecordCount;
	else
		return m_nRecordCount;
}

void CCSV::SetRecordCount(bool bDecrement)
{
	if( bDecrement )
	{
		//m_nRecordCount--;
		m_nSuccessRecordCount--;
	}
	else
	{
		m_nRecordCount = 0;
		m_nSuccessRecordCount = 0;
	}
}

CString* CCSV::GetCSVRow(CStringArray* strItems, CString* strRow)
{
	CString strValue;

	strRow->Empty();

	int nFields = strItems->GetSize( );

	for(int nIndex = 0; nIndex < nFields ; nIndex++ )
	{
		strValue = strItems->GetAt(nIndex);

		if( strValue.FindOneOf( m_strQuotedIdentifier ) < 0 &&
			strValue.FindOneOf( m_strFieldTerminator )  < 0 )
		{
			*strRow += strValue;
		}
		else
		{
			strValue.Replace(m_strFirstQuotedIdentifier, m_strDoubleQuotedIdentifier);

			*strRow += m_szQuotedIdentifier[0];
			*strRow += strValue;
			*strRow += m_szQuotedIdentifier[0];
		}

		if( nIndex != nFields -1 )
		{
			*strRow += _T( m_strFieldTerminator[0] );
		}
	}

	return strRow;
}


CString CCSV::FormatHtmlItems(CStringArray* strItems, bool bHeading)
{
	CString str;
	CString strHtml;

	strHtml = ("  <tr>\r\n");

	int nFields = strItems->GetSize( );

	for(int nIndex = 0; nIndex < nFields ; nIndex++ )
	{
		if( bHeading )
			str.Format("    <th>%s</th>\r\n", strItems->GetAt(nIndex));
		else
			str.Format("    <td>%s</td>\r\n", strItems->GetAt(nIndex));

		strHtml += str;
	}

	strHtml += ("  </tr>\r\n");

	return strHtml;
}



DWORD CCSV::GetBitMask(CString strDWordLine, TCHAR chFieldTerminator)
{
	CStringArray* strItems = new CStringArray();

	DWORD dwBitMask = 0x0;

	CCSV csv(chFieldTerminator);

	csv.GetItems(strItems, &strDWordLine);

	int nFields = strItems->GetSize( );

	for(int nIndex = 0; nIndex < nFields ; nIndex++ )
	{
		dwBitMask |= atol(strItems->GetAt(nIndex));
	}

	delete strItems;

	return dwBitMask;
}