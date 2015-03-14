// CDBTable.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "DBTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DBTable

/////////////////////////////////////////////////////////////////////////////
// Constructor

CDBTable::CDBTable( )
	: CBitMaskEnum(CDBTable::Results)
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CDBTable::~CDBTable( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CDBTable::GetName()
{
	return CDBTable::GetName(m_dwItemEnum);
}

UINT CDBTable::GetId()
{
	return CDBTable::GetId(m_dwItemEnum);
}


CString CDBTable::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBTable::Event :
			return "Event";
			break;
		case CDBTable::EventRecord :
			return "EventRecord";
			break;
		case CDBTable::EventType :
			return "EventType";
			break;
		case CDBTable::Financial :
			return "Financial";
			break;
		case CDBTable::Groups :
			return "Groups";
			break;
		case CDBTable::Location :
			return "Location";
			break;
		case CDBTable::Organisation :
			return "Organisation";
			break;
		case CDBTable::ParticipantForSeries :
			return "ParticipantForSeries";
			break;
		case CDBTable::Person :
			return "Person";
			break;
		case CDBTable::PersonComments :
			return "PersonComments";
			break;
		case CDBTable::PostResults :
			return "PostResults";
			break;
		case CDBTable::PreResults :
			return "PreResults";
			break;
		case CDBTable::RegistrationType :
			return "RegistrationType";
			break;
		case CDBTable::Results :
			return "Results";
			break;
		case CDBTable::Roster :
			return "Roster";
			break;
		case CDBTable::RosterDescriptions :
			return "RosterDescriptions";
			break;
		case CDBTable::Rules :
			return "Rules";
			break;
		case CDBTable::RuleSubType :
			return "RuleSubType";
			break;
		case CDBTable::RuleType :
			return "RuleType";
			break;
		case CDBTable::SecurityPerson :
			return "SecurityPerson";
			break;
		case CDBTable::SecurityPersonSeries :
			return "SecurityPersonSeries";
			break;
		case CDBTable::SecurityRole :
			return "SecurityRole";
			break;
		case CDBTable::SeriesSeason :
			return "SeriesSeason";
			break;
		case CDBTable::Series :
			return "Series";
			break;
		case CDBTable::WorldStandard :
			return "WorldStandard";
			break;
		default :
			return "";
			break;
	}

}


UINT CDBTable::GetId(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBTable::Event :
			return IDS_SQL_CR_EVENT;
			break;
		case CDBTable::EventRecord :
			return IDS_SQL_CR_EVENTRECORD;
			break;
		case CDBTable::EventType :
			return IDS_SQL_CR_EVENTTYPE;
			break;
		case CDBTable::Financial :
			return IDS_SQL_CR_FINANCIAL;
			break;
		case CDBTable::Groups :
			return IDS_SQL_CR_GROUPS;
			break;
		case CDBTable::Location :
			return IDS_SQL_CR_LOCATION;
			break;
		case CDBTable::Organisation :
			return IDS_SQL_CR_ORGANISATION;
			break;
		case CDBTable::ParticipantForSeries :
			return IDS_SQL_CR_PARTICIPANTFORSERIES;
			break;
		case CDBTable::Person :
			return IDS_SQL_CR_PERSON;
			break;
		case CDBTable::PersonComments :
			return IDS_SQL_CR_PERSONCOMMENTS;
			break;
		case CDBTable::PostResults :
			return IDS_SQL_CR_POSTRESULTS;
			break;
		case CDBTable::PreResults :
			return IDS_SQL_CR_PRERESULTS;
			break;
		case CDBTable::RegistrationType :
			return IDS_SQL_CR_REGISTRATIONTYPE;
			break;
		case CDBTable::Results :
			return IDS_SQL_CR_RESULTS;
			break;
		case CDBTable::Roster :
			return IDS_SQL_CR_ROSTER;
			break;
		case CDBTable::RosterDescriptions :
			return IDS_SQL_CR_ROSTERDESCRIPTIONS;
			break;
		case CDBTable::Rules :
			return IDS_SQL_CR_RULES;
			break;
		case CDBTable::RuleSubType :
			return IDS_SQL_CR_RULESUBTYPE;
			break;
		case CDBTable::RuleType :
			return IDS_SQL_CR_RULETYPE;
			break;
		case CDBTable::SecurityPerson :
			return IDS_SQL_CR_SECURITYPERSON;
			break;
		case CDBTable::SecurityPersonSeries :
			return IDS_SQL_CR_SECURITYPERSONSERIES;
			break;
		case CDBTable::SecurityRole :
			return IDS_SQL_CR_SECURITYROLE;
			break;
		case CDBTable::SeriesSeason :
			return IDS_SQL_CR_SERIESSEASON;
			break;
		case CDBTable::Series :
			return IDS_SQL_CR_SERIES;
			break;
		case CDBTable::WorldStandard :
			return IDS_SQL_CR_WORLDSTANDARD;
			break;
		default :
			return 0;
			break;
	}

}


