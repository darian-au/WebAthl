// CReportFinancialHistoryOption.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "ReportFinancialHistoryOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportFinancialHistoryOption

/////////////////////////////////////////////////////////////////////////////
// Constructor

CReportFinancialHistoryOption::CReportFinancialHistoryOption( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CReportFinancialHistoryOption::~CReportFinancialHistoryOption( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CReportFinancialHistoryOption::GetName()
{
	return CReportFinancialHistoryOption::GetName(m_dwItemEnum);
}

DWORD CReportFinancialHistoryOption::GetDefaultSelect()
{
	return CReportFinancialHistoryOption::GetDefaultSelect(m_dwItemEnum);
}

CString CReportFinancialHistoryOption::GetLabel()
{
	return CReportFinancialHistoryOption::GetLabel(m_dwItemEnum);
}


CString CReportFinancialHistoryOption::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportFinancialHistoryOption::DisplayDateRenewed :
			return "Renewal Date";
			break;
		case CReportFinancialHistoryOption::DisplayYear :
			return "Year Valid";
			break;
		case CReportFinancialHistoryOption::DisplayRegistrationID :
			return "Registration ID";
			break;
		case CReportFinancialHistoryOption::DisplayRegistrationDescription :
			return "Registration Type";
			break;
		case CReportFinancialHistoryOption::DisplayMonthStopStart :
			return "Registration Range";
			break;
		case CReportFinancialHistoryOption::DisplayMailListFlag :
			return "Mailing List";
			break;
		case CReportFinancialHistoryOption::DisplayOrgName :
			return "Organisation";
			break;
		default :
			return "";
			break;
	}

}


DWORD CReportFinancialHistoryOption::GetDefaultSelect(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportFinancialHistoryOption::DisplayDateRenewed :
		case CReportFinancialHistoryOption::DisplayYear :
		case CReportFinancialHistoryOption::DisplayRegistrationDescription :
		case CReportFinancialHistoryOption::DisplayMonthStopStart :
		case CReportFinancialHistoryOption::DisplayMailListFlag :
			return dwItem;
			break;

		case CReportFinancialHistoryOption::DisplayRegistrationID :
		case CReportFinancialHistoryOption::DisplayOrgName :
			return 0;
			break;

		default :
			return 0;
			break;
	}

}

CString CReportFinancialHistoryOption::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CReportFinancialHistoryOption::DisplayDateRenewed :
			return "Display";
			break;
		case CReportFinancialHistoryOption::DisplayYear :
		case CReportFinancialHistoryOption::DisplayRegistrationDescription :
		case CReportFinancialHistoryOption::DisplayMonthStopStart :
		case CReportFinancialHistoryOption::DisplayMailListFlag :
		case CReportFinancialHistoryOption::DisplayRegistrationID :
		case CReportFinancialHistoryOption::DisplayOrgName :
			return "";
			break;
		default :
			return "";
			break;
	}

}
