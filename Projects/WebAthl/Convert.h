#if !defined(AFX_CONVERT_H__INCLUDED_)
#define AFX_CONVERT_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CConvert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvert

class CConvert
{

	public:

		// Constructor
		//CConvert( );	

		// Destructor
		//~CConvert( );

		// Member functions

		// Static functions
		static CString dwtoa(DWORD dwItem);
		static CString dwtoxa(DWORD dwItem);

		static CString itoa(int nDigit);
		static CString itoa(int nDigit, int nDigitsLeft);
		//
		//		digitsLeft  : number of digits to the left  of the decimal place

		static CString dtoa(double dDigit);
		static CString dtoa(double dDigit, int nDigitsRight);
		static CString dtoa(double dDigit, int nDigitsRight, int nDigitsLeft);
		static CString dtoa(double dDigit, bool bTimed);
		static CString dtoa(double dDigit, int nDigitsRight, int nDigitsLeft, bool bTimed);
		//
		//		digitsRight : number of digits to the right of the decimal place
		//		digitsLeft  : number of digits to the left  of the decimal place
		//
		//		timed : Digit is treated as a timed (min.sec) value
		//
		//			e.g. dtoa(3.691, 4, 2) == "03.6910"
		//			e.g. dtoa(3.691) == "3.69"
		//			e.g. dtoa(3.691, 2, 0, true) == "4.09"
		//			e.g. dtoa(3.691, true) == "4.09"
		//

		// Static variables

		// Member variables

	private:

		// Member variables
};

#endif // !defined(AFX_CONVERT_H__INCLUDED_)
