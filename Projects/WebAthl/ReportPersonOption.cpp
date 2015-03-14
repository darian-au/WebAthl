// CReportPersonOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "Module.h"
#include "ReportPersonOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportPersonOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportPersonOption::CReportPersonOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportPersonOption::~CReportPersonOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportPersonOption::GetName()
{
	return CReportPersonOption::GetName(m_dwItemEnum);
}

DWORD CReportPersonOption::GetDefaultSelect()
{
	return CReportPersonOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportPersonOption::GetLabel()
{
	return CReportPersonOption::GetLabel(m_dwItemEnum);
}

DWORD CReportPersonOption::GetPermission()
{
	return CReportPersonOption::GetPermission(m_dwItemEnum);
}

CString CReportPersonOption::GetDescription()
{
	return CReportPersonOption::GetDescription(m_dwItemEnum);
}

CString CReportPersonOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportPersonOption::DisplayPersonID :
			return "Person ID";
			break;
		case CReportPersonOption::DisplayLastName :
			return "Last Name";
			break;
		case CReportPersonOption::DisplayFirstName :
			return "First Name";
			break;
		case CReportPersonOption::DisplayMiddleName :
			return "Middle Name";
			break;
		case CReportPersonOption::DisplayAgeGroup :
			return "Sex, Age Group";
			break;
		case CReportPersonOption::DisplayDOB :
			return "DOB";
			break;
		case CReportPersonOption::DisplayAddress :
			return "Address";
			break;
		case CReportPersonOption::DisplayTown :
			return "Town";
			break;
		case CReportPersonOption::DisplayState :
			return "State";
			break;
		case CReportPersonOption::DisplayPostCode :
			return "PostCode";
			break;
		case CReportPersonOption::DisplayCountry :
			return "Country";
			break;
		case CReportPersonOption::DisplayPhoneHm :
			return "Phone Home";
			break;
		case CReportPersonOption::DisplayPhoneWk :
			return "Phone Work";
			break;
		case CReportPersonOption::DisplayFax :
			return "Fax";
			break;
		case CReportPersonOption::DisplayMobile :
			return "Mobile";
			break;
		case CReportPersonOption::DisplayEmail :
			return "E-mail";
			break;
		case CReportPersonOption::DisplayContactPersonID :
			return "Contact ID";
			break;
		case CReportPersonOption::DisplayDateRenewed :
			return "Renewal Date";
			break;
		case CReportPersonOption::DisplayYear :
			return "Year Valid";
			break;
		case CReportPersonOption::DisplayRegistrationID :
			return "Registration ID";
			break;
		case CReportPersonOption::DisplayRegistrationTypeID :
			return "Registration Type";
			break;
		case CReportPersonOption::DisplayMonthStartStop :
			return "Registration Range";
			break;
		case CReportPersonOption::DisplayMailListFlag :
			return "Mail List";
			break;
		case CReportPersonOption::DisplayOrgName :
			return "Organisation";
			break;
		case CReportPersonOption::DisplayComments :
			return "Comments";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportPersonOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportPersonOption::DisplayPersonID :
		case CReportPersonOption::DisplayLastName :
		case CReportPersonOption::DisplayFirstName :
		case CReportPersonOption::DisplayAgeGroup :
		case CReportPersonOption::DisplayDOB :
			return dwItem;
			break;

		case CReportPersonOption::DisplayMiddleName :
		case CReportPersonOption::DisplayAddress :
		case CReportPersonOption::DisplayTown :
		case CReportPersonOption::DisplayState :
		case CReportPersonOption::DisplayPostCode :
		case CReportPersonOption::DisplayCountry :
		case CReportPersonOption::DisplayPhoneHm :
		case CReportPersonOption::DisplayPhoneWk :
		case CReportPersonOption::DisplayFax :
		case CReportPersonOption::DisplayMobile :
		case CReportPersonOption::DisplayEmail :
		case CReportPersonOption::DisplayContactPersonID :
		case CReportPersonOption::DisplayDateRenewed :
		case CReportPersonOption::DisplayYear :
		case CReportPersonOption::DisplayRegistrationID :
		case CReportPersonOption::DisplayRegistrationTypeID :
		case CReportPersonOption::DisplayMonthStartStop :
		case CReportPersonOption::DisplayMailListFlag :
		case CReportPersonOption::DisplayOrgName :
		case CReportPersonOption::DisplayComments :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportPersonOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportPersonOption::DisplayPersonID :
		case CReportPersonOption::DisplayLastName :
		case CReportPersonOption::DisplayFirstName :
		case CReportPersonOption::DisplayMiddleName :
		case CReportPersonOption::DisplayAgeGroup :
		case CReportPersonOption::DisplayDOB :
		case CReportPersonOption::DisplayAddress :
		case CReportPersonOption::DisplayTown :
		case CReportPersonOption::DisplayState :
		case CReportPersonOption::DisplayPostCode :
		case CReportPersonOption::DisplayCountry :
		case CReportPersonOption::DisplayPhoneHm :
		case CReportPersonOption::DisplayPhoneWk :
		case CReportPersonOption::DisplayFax :
		case CReportPersonOption::DisplayMobile :
		case CReportPersonOption::DisplayEmail :
		case CReportPersonOption::DisplayContactPersonID :
		case CReportPersonOption::DisplayDateRenewed :
		case CReportPersonOption::DisplayYear :
		case CReportPersonOption::DisplayRegistrationID :
		case CReportPersonOption::DisplayRegistrationTypeID :
		case CReportPersonOption::DisplayMonthStartStop :
		case CReportPersonOption::DisplayMailListFlag :
		case CReportPersonOption::DisplayOrgName :
		case CReportPersonOption::DisplayComments :
			return "";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportPersonOption::GetPermission(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportPersonOption::DisplayPersonID :
		case CReportPersonOption::DisplayLastName :
		case CReportPersonOption::DisplayFirstName :
		case CReportPersonOption::DisplayAgeGroup :
			return CModule::none;
			break;

		case CReportPersonOption::DisplayMiddleName :
		case CReportPersonOption::DisplayDOB :
		case CReportPersonOption::DisplayAddress :
		case CReportPersonOption::DisplayTown :
		case CReportPersonOption::DisplayState :
		case CReportPersonOption::DisplayPostCode :
		case CReportPersonOption::DisplayCountry :
		case CReportPersonOption::DisplayPhoneHm :
		case CReportPersonOption::DisplayPhoneWk :
		case CReportPersonOption::DisplayFax :
		case CReportPersonOption::DisplayMobile :
		case CReportPersonOption::DisplayEmail :
			return CModule::ViewPerson | CModule::EditPerson;
			break;

		case CReportPersonOption::DisplayContactPersonID :
		case CReportPersonOption::DisplayDateRenewed :
		case CReportPersonOption::DisplayYear :
		case CReportPersonOption::DisplayRegistrationID :
		case CReportPersonOption::DisplayRegistrationTypeID :
		case CReportPersonOption::DisplayMonthStartStop :
		case CReportPersonOption::DisplayMailListFlag :
		case CReportPersonOption::DisplayOrgName :
		case CReportPersonOption::DisplayComments :
			return CModule::Financial;
			break;

		default :
			return 0;
			break;
	}

}



CString CReportPersonOption::GetDescription(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportPersonOption::DisplayPersonID :
			return "Person ID";
			break;
		case CReportPersonOption::DisplayLastName :
			return "Last Name";
			break;
		case CReportPersonOption::DisplayFirstName :
			return "First Name";
			break;
		case CReportPersonOption::DisplayMiddleName :
			return "Middle Name";
			break;
		case CReportPersonOption::DisplayAgeGroup :
			return "Sex and Current Age Group";
			break;
		case CReportPersonOption::DisplayDOB :
			return "Date of Birth";
			break;
		case CReportPersonOption::DisplayAddress :
			return "Address";
			break;
		case CReportPersonOption::DisplayTown :
			return "Town";
			break;
		case CReportPersonOption::DisplayState :
			return "State";
			break;
		case CReportPersonOption::DisplayPostCode :
			return "Post Code";
			break;
		case CReportPersonOption::DisplayCountry :
			return "Country";
			break;
		case CReportPersonOption::DisplayPhoneHm :
			return "Home Phone Number";
			break;
		case CReportPersonOption::DisplayPhoneWk :
			return "Work Phone Number";
			break;
		case CReportPersonOption::DisplayFax :
			return "Fax Number";
			break;
		case CReportPersonOption::DisplayMobile :
			return "Mobile Phone Number";
			break;
		case CReportPersonOption::DisplayEmail :
			return "E-mail Address";
			break;
		case CReportPersonOption::DisplayContactPersonID :
			return "Person ID of Contact Person";
			break;
		case CReportPersonOption::DisplayDateRenewed :
			return "Date when Financial Membership was Renewed";
			break;
		case CReportPersonOption::DisplayYear :
			return "Financial Year that the Membership is/was valid to";
			break;
		case CReportPersonOption::DisplayRegistrationID :
			return "Financial Registration ID";
			break;
		case CReportPersonOption::DisplayRegistrationTypeID :
			return "Type of Financial Membership";
			break;
		case CReportPersonOption::DisplayMonthStartStop :
			return "Period Membership is/was valid";
			break;
		case CReportPersonOption::DisplayMailListFlag :
			return "Mailing List Status";
			break;
		case CReportPersonOption::DisplayOrgName :
			return "Organisation Name";
			break;
		case CReportPersonOption::DisplayComments :
			return "Comment of specified Type";
			break;
		default :
			return "";
			break;
	}

}
