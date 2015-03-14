// CModule.cpp : implementation file
//

#include "stdafx.h"

#include "BitMaskEnum.h"
#include "Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Module

/////////////////////////////////////////////////////////////////////////////
// Constructor

CModule::CModule( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CModule::~CModule( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CModule::GetName()
{
	return CModule::GetName(m_dwItemEnum);
}

CString CModule::GetLabel()
{
	return CModule::GetLabel(m_dwItemEnum);
}


CString CModule::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CModule::Reports :
			return "Reports";
			break;
		case CModule::Financial :
			return "Financial";
			break;
		case CModule::WorldStandards :
			return "Standards";
			break;
		case CModule::ResultsEntry :
			return "ResultsEntry";
			break;
		case CModule::RosterDescriptions :
			return "RosterDescriptions";
			break;
		case CModule::Roster :
			return "Roster";
			break;
		case CModule::Organisation :
			return "Organisation";
			break;
		case CModule::Person :
			return "Person";
			break;
		case CModule::SearchPerson :
			return "SearchPerson";
			break;
		case CModule::EditPerson :
			return "EditPerson";
			break;
		case CModule::ViewPerson :
			return "ViewPerson";
			break;
		case CModule::Location :
			return "Location";
			break;
		case CModule::EventType :
			return "EventType";
			break;
		case CModule::Event :
			return "Event";
			break;
		case CModule::Processing :
			return "Processing";
			break;
		case CModule::RegistrationType :
			return "RegistrationType";
			break;
		case CModule::SeriesMaintain :
			return "SeriesMaintain";
			break;
		case CModule::SelectSeries :
			return "SelectSeries";
			break;
		case CModule::Security :
			return "Security";
			break;
		case CModule::Groups :
			return "Groups";
			break;
		case CModule::Rules :
			return "Rules";
			break;
		case CModule::OpenPreEntry :
			return "OpenPreEntry";
			break;
		case CModule::SeriesAdd :
			return "SeriesAdd";
			break;
		case CModule::Utilities :
			return "Utilities";
			break;
		case CModule::Options :
			return "Options";
			break;
		case CModule::Maintenance :
			return "Maintenance";
			break;
			
		default :
			return "";
			break;
	}

}

CString CModule::GetLabel(DWORD dwItem)
{

	switch( dwItem )
	{
		case CModule::Reports :
			return "Permissions";
			break;
		case CModule::Financial :
		case CModule::WorldStandards :
		case CModule::ResultsEntry :
		case CModule::RosterDescriptions :
		case CModule::Roster :
		case CModule::Organisation :
		case CModule::Person :
		case CModule::SearchPerson :
		case CModule::EditPerson :
		case CModule::ViewPerson :
		case CModule::Location :
		case CModule::EventType :
		case CModule::Event :
		case CModule::Processing :
		case CModule::RegistrationType :
		case CModule::SeriesMaintain :
		case CModule::SelectSeries :
		case CModule::Security :
		case CModule::Groups :
		case CModule::Rules :
		case CModule::OpenPreEntry :
		case CModule::SeriesAdd :
		case CModule::Utilities :
		case CModule::Options :
		case CModule::Maintenance :
			return "";
			break;

		default :
			return "";
			break;
	}

}
