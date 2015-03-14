// CReportClubRecordsOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportClubRecordsOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportClubRecordsOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportClubRecordsOption::CReportClubRecordsOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportClubRecordsOption::~CReportClubRecordsOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportClubRecordsOption::GetName()
{
	return CReportClubRecordsOption::GetName(m_dwItemEnum);
}

DWORD CReportClubRecordsOption::GetDefaultSelect()
{
	return CReportClubRecordsOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportClubRecordsOption::GetLabel()
{
	return CReportClubRecordsOption::GetLabel(m_dwItemEnum);
}


CString CReportClubRecordsOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportClubRecordsOption::DisplayDate :
			return "Date";
			break;
		case CReportClubRecordsOption::DisplayEventNo :
			return "Event Number";
			break;
		case CReportClubRecordsOption::DisplayLocationDescription :
			return "Location";
			break;
		case CReportClubRecordsOption::DisplayEventDescription :
			return "Event";
			break;
		case CReportClubRecordsOption::DisplayPersonID :
			return "PersonID";
			break;
		case CReportClubRecordsOption::DisplayLastName :
			return "LastName";
			break;
		case CReportClubRecordsOption::DisplayFirstName :
			return "FirstName";
			break;
		case CReportClubRecordsOption::DisplaySexAgeGroup :
			return "AgeGroup";
			break;
		case CReportClubRecordsOption::DisplayClubPerformance :
			return "Performance";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportClubRecordsOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportClubRecordsOption::DisplayDate :
		case CReportClubRecordsOption::DisplayEventNo :
		case CReportClubRecordsOption::DisplayLocationDescription :
		case CReportClubRecordsOption::DisplayEventDescription :
		case CReportClubRecordsOption::DisplayPersonID :
		case CReportClubRecordsOption::DisplayLastName :
		case CReportClubRecordsOption::DisplayFirstName :
		case CReportClubRecordsOption::DisplaySexAgeGroup :
		case CReportClubRecordsOption::DisplayClubPerformance :

			return dwItem;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportClubRecordsOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportClubRecordsOption::DisplayDate :
			return "Display";
			break;
		case CReportClubRecordsOption::DisplayEventNo :
		case CReportClubRecordsOption::DisplayLocationDescription :
		case CReportClubRecordsOption::DisplayEventDescription :
		case CReportClubRecordsOption::DisplayPersonID :
		case CReportClubRecordsOption::DisplayLastName :
		case CReportClubRecordsOption::DisplayFirstName :
		case CReportClubRecordsOption::DisplaySexAgeGroup :
		case CReportClubRecordsOption::DisplayClubPerformance :
			return "";
			break;
		default :
			return "";
			break;
	}

}
