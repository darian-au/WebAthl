// CReportRosterOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "Module.h"
#include "ReportRosterOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportRosterOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportRosterOption::CReportRosterOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportRosterOption::~CReportRosterOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportRosterOption::GetName()
{
	return CReportRosterOption::GetName(m_dwItemEnum);
}

DWORD CReportRosterOption::GetDefaultSelect()
{
	return CReportRosterOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportRosterOption::GetLabel()
{
	return CReportRosterOption::GetLabel(m_dwItemEnum);
}

DWORD CReportRosterOption::GetPermission()
{
	return CReportRosterOption::GetPermission(m_dwItemEnum);
}

CString CReportRosterOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportRosterOption::DisplayTaskDescription :
			return "Task Description";
			break;
		case CReportRosterOption::DisplayPersonID :
			return "Person ID";
			break;
		case CReportRosterOption::DisplayLastName :
			return "Last Name";
			break;
		case CReportRosterOption::DisplayFirstName :
			return "First Name";
			break;
		case CReportRosterOption::DisplayMiddleName :
			return "Middle Name";
			break;
		case CReportRosterOption::DisplaySexAgeGroup :
			return "AgeGroup";
			break;
		case CReportRosterOption::DisplayDOB :
			return "Date of Birth";
			break;
		case CReportRosterOption::DisplayAddress :
			return "Address";
			break;
		case CReportRosterOption::DisplayTown :
			return "Town";
			break;
		case CReportRosterOption::DisplayState :
			return "State";
			break;
		case CReportRosterOption::DisplayPostCode :
			return "PostCode";
			break;
		case CReportRosterOption::DisplayCountry :
			return "Country";
			break;
		case CReportRosterOption::DisplayPhoneHm :
			return "Phone Home";
			break;
		case CReportRosterOption::DisplayPhoneWk :
			return "Phone Work";
			break;
		case CReportRosterOption::DisplayFax :
			return "Fax";
			break;
		case CReportRosterOption::DisplayMobile :
			return "Mobile";
			break;
		case CReportRosterOption::DisplayEmail :
			return "E-mail";
			break;
		case CReportRosterOption::DisplayContactPersonID :
			return "Contact ID";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportRosterOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportRosterOption::DisplayTaskDescription :
		case CReportRosterOption::DisplayPersonID :
		case CReportRosterOption::DisplayLastName :
		case CReportRosterOption::DisplayFirstName :
		case CReportRosterOption::DisplaySexAgeGroup :
			return dwItem;
			break;

		case CReportRosterOption::DisplayMiddleName :
		case CReportRosterOption::DisplayDOB :
		case CReportRosterOption::DisplayAddress :
		case CReportRosterOption::DisplayTown :
		case CReportRosterOption::DisplayState :
		case CReportRosterOption::DisplayPostCode :
		case CReportRosterOption::DisplayCountry :
		case CReportRosterOption::DisplayPhoneHm :
		case CReportRosterOption::DisplayPhoneWk :
		case CReportRosterOption::DisplayFax :
		case CReportRosterOption::DisplayMobile :
		case CReportRosterOption::DisplayEmail :
		case CReportRosterOption::DisplayContactPersonID :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportRosterOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportRosterOption::DisplayTaskDescription :
			return "Display";
			break;
		case CReportRosterOption::DisplayPersonID :
		case CReportRosterOption::DisplayLastName :
		case CReportRosterOption::DisplayFirstName :
		case CReportRosterOption::DisplayMiddleName :
		case CReportRosterOption::DisplaySexAgeGroup :
		case CReportRosterOption::DisplayDOB :
		case CReportRosterOption::DisplayAddress :
		case CReportRosterOption::DisplayTown :
		case CReportRosterOption::DisplayState :
		case CReportRosterOption::DisplayPostCode :
		case CReportRosterOption::DisplayCountry :
		case CReportRosterOption::DisplayPhoneHm :
		case CReportRosterOption::DisplayPhoneWk :
		case CReportRosterOption::DisplayFax :
		case CReportRosterOption::DisplayMobile :
		case CReportRosterOption::DisplayEmail :
		case CReportRosterOption::DisplayContactPersonID :
			return "";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportRosterOption::GetPermission(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportRosterOption::DisplayTaskDescription :
		case CReportRosterOption::DisplayPersonID :
		case CReportRosterOption::DisplayLastName :
		case CReportRosterOption::DisplayFirstName :
		case CReportRosterOption::DisplayMiddleName :
		case CReportRosterOption::DisplaySexAgeGroup :
			return CModule::none;
			break;

		case CReportRosterOption::DisplayDOB :
		case CReportRosterOption::DisplayAddress :
		case CReportRosterOption::DisplayTown :
		case CReportRosterOption::DisplayState :
		case CReportRosterOption::DisplayPostCode :
		case CReportRosterOption::DisplayCountry :
		case CReportRosterOption::DisplayPhoneHm :
		case CReportRosterOption::DisplayPhoneWk :
		case CReportRosterOption::DisplayFax :
		case CReportRosterOption::DisplayMobile :
		case CReportRosterOption::DisplayEmail :
		case CReportRosterOption::DisplayContactPersonID :
			return CModule::ViewPerson | CModule::EditPerson;
			break;

		default :
			return 0;
			break;
	}

}
