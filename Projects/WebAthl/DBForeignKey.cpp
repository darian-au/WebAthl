// CDBForeignKey.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "DBForeignKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DBForeignKey

/////////////////////////////////////////////////////////////////////////////
// Constructor

CDBForeignKey::CDBForeignKey( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CDBForeignKey::~CDBForeignKey( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CDBForeignKey::GetName()
{
	return CDBForeignKey::GetName(m_dwItemEnum);
}

UINT CDBForeignKey::GetId()
{
	return CDBForeignKey::GetId(m_dwItemEnum);
}

UINT CDBForeignKey::GetIdDrop()
{
	return CDBForeignKey::GetIdDrop(m_dwItemEnum);
}


CString CDBForeignKey::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBForeignKey::Event :
			return "Event";
			break;
		case CDBForeignKey::EventRecord :
			return "EventRecord";
			break;
//		case CDBForeignKey::EventType :
//			return "EventType";
//			break;
		case CDBForeignKey::Financial :
			return "Financial";
			break;
		case CDBForeignKey::Groups :
			return "Groups";
			break;
//		case CDBForeignKey::Location :
//			return "Location";
//			break;
//		case CDBForeignKey::Organisation :
//			return "Organisation";
//			break;
		case CDBForeignKey::ParticipantForSeries :
			return "ParticipantForSeries";
			break;
//		case CDBForeignKey::Person :
//			return "Person";
//			break;
		case CDBForeignKey::PersonComments :
			return "PersonComments";
			break;
		case CDBForeignKey::PostResults :
			return "PostResults";
			break;
		case CDBForeignKey::PreResults :
			return "PreResults";
			break;
//		case CDBForeignKey::RegistrationType :
//			return "RegistrationType";
//			break;
		case CDBForeignKey::Results :
			return "Results";
			break;
		case CDBForeignKey::Roster :
			return "Roster";
			break;
//		case CDBForeignKey::RosterDescriptions :
//			return "RosterDescriptions";
//			break;
		case CDBForeignKey::Rules :
			return "Rules";
			break;
		case CDBForeignKey::RuleSubType :
			return "RuleSubType";
			break;
//		case CDBForeignKey::RuleType :
//			return "RuleType";
//			break;
		case CDBForeignKey::SecurityPerson :
			return "SecurityPerson";
			break;
		case CDBForeignKey::SecurityPersonSeries :
			return "SecurityPersonSeries";
			break;
//		case CDBForeignKey::SecurityRole :
//			return "SecurityRole";
//			break;
		case CDBForeignKey::SeriesSeason :
			return "SeriesSeason";
			break;
//		case CDBForeignKey::Series :
//			return "Series";
//			break;
		case CDBForeignKey::WorldStandard :
			return "WorldStandard";
			break;
		default :
			return "";
			break;
	}

}


UINT CDBForeignKey::GetId(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBForeignKey::Event :
			return IDS_SQL_FK_CR_EVENT;
			break;
		case CDBForeignKey::EventRecord :
			return IDS_SQL_FK_CR_EVENTRECORD;
			break;
//		case CDBForeignKey::EventType :
//			return IDS_SQL_FK_CR_EVENTTYPE;
//			break;
		case CDBForeignKey::Financial :
			return IDS_SQL_FK_CR_FINANCIAL;
			break;
		case CDBForeignKey::Groups :
			return IDS_SQL_FK_CR_GROUPS;
			break;
//		case CDBForeignKey::Location :
//			return IDS_SQL_FK_CR_LOCATION;
//			break;
//		case CDBForeignKey::Organisation :
//			return IDS_SQL_FK_CR_ORGANISATION;
//			break;
		case CDBForeignKey::ParticipantForSeries :
			return IDS_SQL_FK_CR_PARTICIPANTFORSERIES;
			break;
//		case CDBForeignKey::Person :
//			return IDS_SQL_FK_CR_PERSON;
//			break;
		case CDBForeignKey::PersonComments :
			return IDS_SQL_FK_CR_PERSONCOMMENTS;
			break;
		case CDBForeignKey::PostResults :
			return IDS_SQL_FK_CR_POSTRESULTS;
			break;
		case CDBForeignKey::PreResults :
			return IDS_SQL_FK_CR_PRERESULTS;
			break;
//		case CDBForeignKey::RegistrationType :
//			return IDS_SQL_FK_CR_REGISTRATIONTYPE;
//			break;
		case CDBForeignKey::Results :
			return IDS_SQL_FK_CR_RESULTS;
			break;
		case CDBForeignKey::Roster :
			return IDS_SQL_FK_CR_ROSTER;
			break;
//		case CDBForeignKey::RosterDescriptions :
//			return IDS_SQL_FK_CR_ROSTERDESCRIPTIONS;
//			break;
		case CDBForeignKey::Rules :
			return IDS_SQL_FK_CR_RULES;
			break;
		case CDBForeignKey::RuleSubType :
			return IDS_SQL_FK_CR_RULESUBTYPE;
			break;
//		case CDBForeignKey::RuleType :
//			return IDS_SQL_FK_CR_RULETYPE;
//			break;
		case CDBForeignKey::SecurityPerson :
			return IDS_SQL_FK_CR_SECURITYPERSON;
			break;
		case CDBForeignKey::SecurityPersonSeries :
			return IDS_SQL_FK_CR_SECURITYPERSONSERIES;
			break;
//		case CDBForeignKey::SecurityRole :
//			return IDS_SQL_FK_CR_SECURITYROLE;
//			break;
		case CDBForeignKey::SeriesSeason :
			return IDS_SQL_FK_CR_SERIESSEASON;
			break;
//		case CDBForeignKey::Series :
//			return IDS_SQL_FK_CR_SERIES;
//			break;
		case CDBForeignKey::WorldStandard :
			return IDS_SQL_FK_CR_WORLDSTANDARD;
			break;
		default :
			return 0;
			break;
	}

}

UINT CDBForeignKey::GetIdDrop(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBForeignKey::Event :
			return IDS_SQL_FK_DR_EVENT;
			break;
		case CDBForeignKey::EventRecord :
			return IDS_SQL_FK_DR_EVENTRECORD;
			break;
//		case CDBForeignKey::EventType :
//			return IDS_SQL_FK_DR_EVENTTYPE;
//			break;
		case CDBForeignKey::Financial :
			return IDS_SQL_FK_DR_FINANCIAL;
			break;
		case CDBForeignKey::Groups :
			return IDS_SQL_FK_DR_GROUPS;
			break;
//		case CDBForeignKey::Location :
//			return IDS_SQL_FK_DR_LOCATION;
//			break;
//		case CDBForeignKey::Organisation :
//			return IDS_SQL_FK_DR_ORGANISATION;
//			break;
		case CDBForeignKey::ParticipantForSeries :
			return IDS_SQL_FK_DR_PARTICIPANTFORSERIES;
			break;
//		case CDBForeignKey::Person :
//			return IDS_SQL_FK_DR_PERSON;
//			break;
		case CDBForeignKey::PersonComments :
			return IDS_SQL_FK_DR_PERSONCOMMENTS;
			break;
		case CDBForeignKey::PostResults :
			return IDS_SQL_FK_DR_POSTRESULTS;
			break;
		case CDBForeignKey::PreResults :
			return IDS_SQL_FK_DR_PRERESULTS;
			break;
//		case CDBForeignKey::RegistrationType :
//			return IDS_SQL_FK_DR_REGISTRATIONTYPE;
//			break;
		case CDBForeignKey::Results :
			return IDS_SQL_FK_DR_RESULTS;
			break;
		case CDBForeignKey::Roster :
			return IDS_SQL_FK_DR_ROSTER;
			break;
//		case CDBForeignKey::RosterDescriptions :
//			return IDS_SQL_FK_DR_ROSTERDESCRIPTIONS;
//			break;
		case CDBForeignKey::Rules :
			return IDS_SQL_FK_DR_RULES;
			break;
		case CDBForeignKey::RuleSubType :
			return IDS_SQL_FK_DR_RULESUBTYPE;
			break;
//		case CDBForeignKey::RuleType :
//			return IDS_SQL_FK_DR_RULETYPE;
//			break;
		case CDBForeignKey::SecurityPerson :
			return IDS_SQL_FK_DR_SECURITYPERSON;
			break;
		case CDBForeignKey::SecurityPersonSeries :
			return IDS_SQL_FK_DR_SECURITYPERSONSERIES;
			break;
//		case CDBForeignKey::SecurityRole :
//			return IDS_SQL_FK_DR_SECURITYROLE;
//			break;
		case CDBForeignKey::SeriesSeason :
			return IDS_SQL_FK_DR_SERIESSEASON;
			break;
//		case CDBForeignKey::Series :
//			return IDS_SQL_FK_DR_SERIES;
//			break;
		case CDBForeignKey::WorldStandard :
			return IDS_SQL_FK_DR_WORLDSTANDARD;
			break;
		default :
			return 0;
			break;
	}

}

