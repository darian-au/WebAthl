#if !defined(AFX_BITMASKENUM_H__INCLUDED_)
#define AFX_BITMASKENUM_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CBitMaskEnum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitMaskEnum

class CBitMaskEnum
{

	public:

		// Constructor
		CBitMaskEnum(DWORD dwItemMax = CBitMaskEnum::Max);	

		// Destructor
		//~CBitMaskEnum( );

		// Member functions
		DWORD Enumerator(BOOL bReverse = FALSE);
		BOOL GetNext(DWORD* dwItem = NULL);
		DWORD FindByName( LPCTSTR szName );
		
		virtual bool IsMember(DWORD dwGroup);

		virtual CString GetName();


		// Static functions
		static bool IsMember(DWORD dwItem, DWORD dwGroup);

		static CString GetName(DWORD dwItem);


		// Member variables

		// Static variables
		static enum BitMaskEnumEnum  // bit mask
		{
			none				= 0x00000000,
			Min					= 0x00000001,
			Max					= 0x80000000,
		};

	protected:

		// Member variables
		DWORD m_dwItemEnum;

		DWORD m_dwItemFirst;
		DWORD m_dwItemLast;

		DWORD m_dwItemMax;
};

#endif // !defined(AFX_BITMASKENUM_H__INCLUDED_)
