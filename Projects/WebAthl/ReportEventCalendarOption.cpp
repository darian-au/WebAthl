// CReportEventCalendarOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportEventCalendarOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportEventCalendarOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportEventCalendarOption::CReportEventCalendarOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportEventCalendarOption::~CReportEventCalendarOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportEventCalendarOption::GetName()
{
	return CReportEventCalendarOption::GetName(m_dwItemEnum);
}

DWORD CReportEventCalendarOption::GetDefaultSelect()
{
	return CReportEventCalendarOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportEventCalendarOption::GetLabel()
{
	return CReportEventCalendarOption::GetLabel(m_dwItemEnum);
}


CString CReportEventCalendarOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportEventCalendarOption::DisplaySeriesDesc :
			return "Series Description";
			break;
		case CReportEventCalendarOption::DisplayEventNo :
			return "Event Number";
			break;
		case CReportEventCalendarOption::DisplayLocationDesc :
			return "Location Description";
			break;
		case CReportEventCalendarOption::DisplayEventDesc :
			return "Event Description";
			break;
		case CReportEventCalendarOption::DisplayEventDate :
			return "Event Date";
			break;
		case CReportEventCalendarOption::DisplayPreEntryOpen :
			return "Pre-Entry Status";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportEventCalendarOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportEventCalendarOption::DisplaySeriesDesc :
		case CReportEventCalendarOption::DisplayEventNo :
		case CReportEventCalendarOption::DisplayLocationDesc :
		case CReportEventCalendarOption::DisplayEventDesc :
		case CReportEventCalendarOption::DisplayEventDate :
		case CReportEventCalendarOption::DisplayPreEntryOpen :
			return dwItem;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportEventCalendarOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportEventCalendarOption::DisplaySeriesDesc :
			return "Display";
			break;
		case CReportEventCalendarOption::DisplayEventNo :
		case CReportEventCalendarOption::DisplayLocationDesc :
		case CReportEventCalendarOption::DisplayEventDesc :
		case CReportEventCalendarOption::DisplayEventDate :
		case CReportEventCalendarOption::DisplayPreEntryOpen :
			return "";
			break;
		default :
			return "";
			break;
	}

}
