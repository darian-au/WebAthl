// CBitMaskEnum.cpp : implementation file
//

#include "stdafx.h"

#include "BitMaskEnum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BitMaskEnum

/////////////////////////////////////////////////////////////////////////////
// Constructor

CBitMaskEnum::CBitMaskEnum(DWORD dwItemMax)
{
	m_dwItemEnum = CBitMaskEnum::none;

	// Only Required for Reverse Enumeration
	m_dwItemMax = dwItemMax;
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CBitMaskEnum::~CBitMaskEnum( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

DWORD CBitMaskEnum::Enumerator(BOOL bReverse)
{
	if( bReverse )
	{
		m_dwItemFirst = m_dwItemMax;
		m_dwItemLast = CBitMaskEnum::Min;
	}
	else
	{
		m_dwItemFirst = CBitMaskEnum::Min;
		m_dwItemLast = m_dwItemMax;
	}

	m_dwItemEnum = CBitMaskEnum::none;

	return m_dwItemEnum;
}

BOOL CBitMaskEnum::GetNext(DWORD* dwItem)
{
	if( (m_dwItemEnum | CBitMaskEnum::none) == CBitMaskEnum::none )
	{
		m_dwItemEnum = m_dwItemFirst;

		if( dwItem != NULL )
		{
			*dwItem = m_dwItemEnum;
		}

		return TRUE;
	}
	else if( (m_dwItemEnum & m_dwItemLast) == m_dwItemLast )
	{
		m_dwItemEnum = CBitMaskEnum::none;
		return FALSE;
	}
	else
	{
		if( m_dwItemFirst > m_dwItemLast ) // bReverse
		{
			m_dwItemEnum >>= 0x1;
		}
		else
		{
			m_dwItemEnum <<= 0x1;
		}

		if( GetName().IsEmpty() )
		{
			m_dwItemEnum = CBitMaskEnum::none;
			return FALSE;
		}

		if( dwItem != NULL )
		{
			*dwItem = m_dwItemEnum;
		}

		return TRUE;
	}
}

DWORD CBitMaskEnum::FindByName( LPCTSTR szName )
{
	DWORD dwEnum = Enumerator( );
	while( GetNext( &dwEnum ) )
	{
		if( GetName().Compare(szName) == 0 )
		{
			return dwEnum;
		}
	}

	return CBitMaskEnum::none;
}


bool CBitMaskEnum::IsMember(DWORD dwGroup)
{
	return IsMember(m_dwItemEnum, dwGroup);
}

bool CBitMaskEnum::IsMember(DWORD dwItem, DWORD dwGroup)
{
	return ( (dwItem & dwGroup) == dwGroup );
}


CString CBitMaskEnum::GetName(DWORD dwItem)
{
	return "";
}



CString CBitMaskEnum::GetName()
{
	return CBitMaskEnum::GetName(m_dwItemEnum);
}

