// CConvert.cpp : implementation file
//

#include "stdafx.h"

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "Convert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Convert

/////////////////////////////////////////////////////////////////////////////
// Constructor

//CConvert::CConvert( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CConvert::~CConvert( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CConvert::dwtoa(DWORD dwItem)
{
	CString str;

	str.Format("%u", dwItem );

	return str;
}

CString CConvert::dwtoxa(DWORD dwItem)
{
	CString str;

	str.Format("0x%x", dwItem );

	return str;
}

CString CConvert::itoa(int nDigit)
{
	return itoa(nDigit, 0);
}

CString CConvert::itoa(int nDigit, int nDigitsLeft)
{
	CString str;

	if ( !CRecordsetEx::IsItemNull(nDigit) )
	{
		str.Format( "%0*d", nDigitsLeft, nDigit );
	}
	else
	{
		str.Format(CRecordsetEx::m_szNull);
	}

	return str;
}

CString CConvert::dtoa(double dDigit)
{
	return dtoa(dDigit, 2, 0);
}

CString CConvert::dtoa(double dDigit, int nDigitsRight)
{
	return dtoa(dDigit, nDigitsRight, 0);
}

CString CConvert::dtoa(double dDigit, int nDigitsRight, int nDigitsLeft)
{
	return dtoa(dDigit, nDigitsRight, nDigitsLeft, false);
}

CString CConvert::dtoa(double dDigit, bool bTimed)
{
	return dtoa(dDigit, 2, 0, bTimed);
}


CString CConvert::dtoa(double dDigit, int nDigitsRight, int nDigitsLeft, bool bTimed)
//
//		digitsLeft  : number of digits to the left  of the decimal place
//		digitsRight : number of digits to the right of the decimal place
//
//		timed : Digit is treated as a timed (min.sec) value
//
//			e.g. dtoa(3.691, 4, 2) == "03.6910"
//			e.g. dtoa(3.691) == "3.69"
//			e.g. dtoa(3.691, 2, 0, true) == "4.09"
//			e.g. dtoa(3.691, true) == "4.09"
//

{
	CString str;

	int nMinPart;
	double dSecPart;

	double dNum = dDigit;

	if ( !CRecordsetEx::IsItemNull(dDigit) )
	{
		if( bTimed )	
			// Treat Digit as a timed (min.sec) value
		{
			nMinPart = (int)dDigit;
			dSecPart = ((dDigit * 100.0) - nMinPart * 100) / 100.0;

			if ( dSecPart >= 0.595 )
			{
				nMinPart++;
				if ( dSecPart >= 0.600 )
					dSecPart += (-0.600);
				else
					dSecPart = 0.000;

				dNum = ((double)nMinPart + dSecPart) ;
			}
		}

		str.Format( "%0*.*f", (nDigitsLeft + nDigitsRight +1), nDigitsRight, dNum );
	}
	else
	{
		str.Format(CRecordsetEx::m_szNull);
	}

	return str;
}
