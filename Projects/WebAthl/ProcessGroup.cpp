// CProcessGroup.cpp : implementation file
//

#include "stdafx.h"

#include "BitMaskEnum.h"
#include "ProcessGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProcessGroup

/////////////////////////////////////////////////////////////////////////////
// Constructor

CProcessGroup::CProcessGroup( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CProcessGroup::~CProcessGroup( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CProcessGroup::GetName()
{
	return CProcessGroup::GetName(m_dwItemEnum);
}


CString CProcessGroup::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CProcessGroup::PreResults :
			return "PreResults";
			break;
		case CProcessGroup::PreEvent :
			return "PreEvent";
			break;
		case CProcessGroup::LockOut :
			return "LockOut";
			break;
		case CProcessGroup::PostEvent :
			return "PostEvent";
			break;
		case CProcessGroup::ClubRecords :
			return "ClubRecords";
			break;
		case CProcessGroup::Admin :
			return "Admin";
			break;
		default :
			return "";
			break;
	}

}
