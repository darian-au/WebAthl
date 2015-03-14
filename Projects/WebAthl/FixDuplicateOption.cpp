// CFixDuplicateOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "FixDuplicateOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FixDuplicateOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CFixDuplicateOption::CFixDuplicateOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CFixDuplicateOption::~CFixDuplicateOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CFixDuplicateOption::GetName()
{
	return CFixDuplicateOption::GetName(m_dwItemEnum);
}

DWORD CFixDuplicateOption::GetDefaultSelect()
{
	return CFixDuplicateOption::GetDefaultSelect(m_dwItemEnum);
}

CString CFixDuplicateOption::GetDescription()
{
	return CFixDuplicateOption::GetDescription(m_dwItemEnum);
}

BOOL CFixDuplicateOption::GetHidden()
{
	return CFixDuplicateOption::GetHidden(m_dwItemEnum);
}

CString CFixDuplicateOption::GetDescription(DWORD dwItem)
{

	switch( dwItem )
	{
//		case CFixDuplicateOption::DeleteOptions :
//			return "Options";
//			break;
		case CFixDuplicateOption::DeletePersonComments :
			return "Comments";
			break;
		case CFixDuplicateOption::DeleteRoster :
			return "Roster";
			break;
		case CFixDuplicateOption::DeleteEventRecord :
			return "Event Records";
			break;
		case CFixDuplicateOption::DeleteParticipantForSeries :
			return "Participant Details For Series";
			break;
		case CFixDuplicateOption::DeleteResults :
			return "Results";
			break;
		case CFixDuplicateOption::DeletePostResults :
			return "Post-Event Results";
			break;
		case CFixDuplicateOption::DeletePreResults :
			return "Pre-Event Results";
			break;
		case CFixDuplicateOption::DeleteFinancial :
			return "Financial";
			break;
//		case CFixDuplicateOption::DeleteSecurityGroup :
		case CFixDuplicateOption::DeleteSecurityPerson :
		case CFixDuplicateOption::DeleteSecurityPersonSeries :
			return "Security";
			break;
		default :
			return "";
			break;
	}

}


DWORD CFixDuplicateOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
//		case CFixDuplicateOption::DeleteOptions :
		case CFixDuplicateOption::DeleteEventRecord :
		case CFixDuplicateOption::DeleteParticipantForSeries :
		case CFixDuplicateOption::DeleteFinancial :
//		case CFixDuplicateOption::DeleteSecurityGroup :
		case CFixDuplicateOption::DeleteSecurityPerson :
		case CFixDuplicateOption::DeleteSecurityPersonSeries :
			return dwItem;
			break;

		case CFixDuplicateOption::DeletePersonComments :
		case CFixDuplicateOption::DeleteRoster :
		case CFixDuplicateOption::DeleteResults :
		case CFixDuplicateOption::DeletePostResults :
		case CFixDuplicateOption::DeletePreResults :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}


CString CFixDuplicateOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
//		case CFixDuplicateOption::DeleteOptions :
//			return "Options";
//			break;
		case CFixDuplicateOption::DeletePersonComments :
			return "PersonComments";
			break;
		case CFixDuplicateOption::DeleteRoster :
			return "Roster";
			break;
		case CFixDuplicateOption::DeleteEventRecord :
			return "EventRecord";
			break;
		case CFixDuplicateOption::DeleteParticipantForSeries :
			return "ParticipantForSeries";
			break;
		case CFixDuplicateOption::DeleteResults :
			return "Results";
			break;
		case CFixDuplicateOption::DeletePostResults :
			return "PostResults";
			break;
		case CFixDuplicateOption::DeletePreResults :
			return "PreResults";
			break;
		case CFixDuplicateOption::DeleteFinancial :
			return "Financial";
			break;
//		case CFixDuplicateOption::DeleteSecurityGroup :
//			return "SecurityGroup";
//			break;
		case CFixDuplicateOption::DeleteSecurityPerson :
			return "SecurityPerson";
			break;
		case CFixDuplicateOption::DeleteSecurityPersonSeries :
			return "SecurityPersonSeries";
			break;
		default :
			return "";
			break;
	}

}

BOOL CFixDuplicateOption::GetHidden(DWORD dwItem)
{

	switch( dwItem )
	{
//		case CFixDuplicateOption::DeleteOptions :
		case CFixDuplicateOption::DeletePersonComments :
		case CFixDuplicateOption::DeleteRoster :
		case CFixDuplicateOption::DeleteEventRecord :
		case CFixDuplicateOption::DeleteParticipantForSeries :
		case CFixDuplicateOption::DeleteResults :
		case CFixDuplicateOption::DeletePostResults :
		case CFixDuplicateOption::DeletePreResults :
		case CFixDuplicateOption::DeleteFinancial :
//		case CFixDuplicateOption::DeleteSecurityGroup :
		case CFixDuplicateOption::DeleteSecurityPerson :
			return TRUE;
			break;

		case CFixDuplicateOption::DeleteSecurityPersonSeries :
			return FALSE;
			break;

		default :
			return FALSE;
			break;
	}

}


