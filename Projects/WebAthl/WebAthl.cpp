// WebAthl.CPP - Implementation file for your Internet Server
//    WebAthl Extension

#include "stdafx.h"

#include "resource.h"
#include "WebAthl.h"

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CWebAthlExtension, CHttpServer)


	ON_PARSE_COMMAND(Dump, CWebAthlExtension, ITS_EMPTY)	


///////////////////////////////////////////////////////////////////////
// Person

	//Person Menu form
	ON_PARSE_COMMAND(PersonMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//addPerson form
	ON_PARSE_COMMAND(PersonAddForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init Submit")
	//Handle addPerson command
	ON_PARSE_COMMAND(PersonAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init PersonID LastName= FirstName= MiddleName= Address1= Address2= Town= State= Country= PostCode= PhoneHm= PhoneWk= Fax= Mobile= email= dobDAY=0 dobMONTH=0 dobYEAR=0 Sex= ContactPersonID= Submit")

	//viewPerson form
	ON_PARSE_COMMAND(PersonViewForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID=none Submit")

	//editPerson form
	ON_PARSE_COMMAND(PersonEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID=none Submit")
	//Handle editPerson command
	ON_PARSE_COMMAND(PersonEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID LastName= FirstName= MiddleName= Address1= Address2= Town= State= PostCode= Country= PhoneHm= PhoneWk= Fax= Mobile= email= dobDAY=0 dobMONTH=0 dobYEAR=0 Sex= ContactPersonID= Submit")

	//editComment command
	ON_PARSE_COMMAND(PersonCommentEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID CommentNo Type Comment Submit")
	//addComment command
	ON_PARSE_COMMAND(PersonCommentAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init Submit")

	//searchPerson form
	ON_PARSE_COMMAND(SearchPersonForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init Init1= Init2= Submit")
	//Handle searchPerson command
	ON_PARSE_COMMAND(SearchPersonSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init Duplicate= PersonID=0 LastName= FirstName= MiddleName= Address1= Address2= Town= State= Country= PostCode= PhoneHm= PhoneWk= Fax= Mobile= email= dobDAY=0 dobMONTH=0 dobYEAR=0 Sex= ContactPersonID= Submit")

	//change Password form
	ON_PARSE_COMMAND(PersonChangePasswordForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//Handle change Password command
	ON_PARSE_COMMAND(PersonChangePasswordExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID oPassword nPassword cPassword Submit")

///////////////////////////////////////////////////////////////////////
// Organisation

	//Organisation Menu form
	ON_PARSE_COMMAND(OrganisationMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//addOrgForm form
	ON_PARSE_COMMAND(OrganisationAddForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle addOrg command
	ON_PARSE_COMMAND(OrganisationAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("OrgID OrgName Address1 Address2 Town State Country PostCode Phone Fax Mobile email URL RegistrarPersonID AdministratorPersonID Submit")

	//selectOrgForm form
	ON_PARSE_COMMAND(OrganisationSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")

	//viewOrgForm form
	ON_PARSE_COMMAND(OrganisationViewForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("OrgID Submit")

	//editOrgForm form
	ON_PARSE_COMMAND(OrganisationEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("OrgID Submit")
	//Handle editOrg command
	ON_PARSE_COMMAND(OrganisationEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("OrgID OrgName Address1 Address2 Town State Country PostCode Phone Fax Mobile email URL RegistrarPersonID AdministratorPersonID Submit")

///////////////////////////////////////////////////////////////////////
// Security

	//Security Menu form
	ON_PARSE_COMMAND(SecurityMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//selectSecurityGroup form
	ON_PARSE_COMMAND(SecurityRoleSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editSecurityGroup form
	ON_PARSE_COMMAND(SecurityRoleEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID=0 Submit")
	//Handle editSecurityGroup command
	ON_PARSE_COMMAND(SecurityRoleEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID RoleName Submit")

	//Handle AllocateTables command
	ON_PARSE_COMMAND(SecurityRoleAllocatePermissionForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID Submit")
	//Handle updateTableAllocation command
	ON_PARSE_COMMAND(SecurityRoleAllocatePermissionExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID Permission=0 Submit")

	//Assign Login form
	ON_PARSE_COMMAND(SecurityAssignLoginForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//Assign Login form
	ON_PARSE_COMMAND(SecurityAssignLoginExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID LoginName Password cPassword Submit")
	//Select Security form
	ON_PARSE_COMMAND(SecurityGrantRoleForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//Select Security form
	ON_PARSE_COMMAND(SecurityGrantRoleExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID RoleID Submit")
	//Revoke Access
	ON_PARSE_COMMAND(SecurityRevokeRoleForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID Submit")
	//Select Security form
	ON_PARSE_COMMAND(SecurityRevokeRoleExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RoleID PersonID Submit")

	//Assign Series form
	ON_PARSE_COMMAND(SecurityAssignSeriesForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID= SeriesID= Submit")
	//handle Assign Series command
	ON_PARSE_COMMAND(SecurityAssignSeriesExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

	
///////////////////////////////////////////////////////////////////////
// Series

	//Series Menu form
	ON_PARSE_COMMAND(SeriesMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	ON_PARSE_COMMAND(SeriesMaintainMenu, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none Submit")

	//addSeriesForm form
	ON_PARSE_COMMAND(SeriesAddForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle addSeries command
	ON_PARSE_COMMAND(SeriesAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID SeriesDescription Submit")

	//selectSeriesForm form
	ON_PARSE_COMMAND(SeriesSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init Init1=none Init2=none")
	//editSeriesForm form
	ON_PARSE_COMMAND(SeriesEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none Submit")
	//Handle editSeries command
	ON_PARSE_COMMAND(SeriesEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID SeriesDescription Submit")

	//editFirstEventForm form
	ON_PARSE_COMMAND(SeriesSetFirstEventForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle editFirstEventForm command
	ON_PARSE_COMMAND(SeriesSetFirstEventExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID EventsInSeason Submit=0")

	//editLastEventProcForm form
	ON_PARSE_COMMAND(SeriesSetNextEventForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle editLastEventProcForm command
	ON_PARSE_COMMAND(SeriesSetNextEventExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID Submit=0")

///////////////////////////////////////////////////////////////////////
// Groups

	//selectGroupsForm form
	ON_PARSE_COMMAND(GroupsEditSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editGroupsForm form
	ON_PARSE_COMMAND(GroupsEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Groups EventTypeID Submit")
	//editGroups command
	ON_PARSE_COMMAND(GroupsEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventTypeID Groups GroupRateList=0 GroupStartList=0 Submit")

///////////////////////////////////////////////////////////////////////
// Rules

	//selectRules form
	ON_PARSE_COMMAND(RulesMenu, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")

	//Handle editRule command
	ON_PARSE_COMMAND(RulesEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID RuleID RuleTypeID RuleSubTypeID Law Submit")

	//Handle addRule command
	ON_PARSE_COMMAND(RulesAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Init Submit")

	//Handle setRuleTypes command
	ON_PARSE_COMMAND(RulesSetTypesExecute, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

///////////////////////////////////////////////////////////////////////
// EventType

	//EventType Menu form
	//ON_PARSE_COMMAND(EventTypeMenu, CWebAthlExtension, ITS_PSTR)
	//ON_PARSE_COMMAND_PARAMS("Submit")

	//addEventTypeForm form
	ON_PARSE_COMMAND(EventTypeAddForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle addEventType command
	ON_PARSE_COMMAND(EventTypeAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventTypeID EventDescription Timed=0 EventLength=0.0 Submit")

	//selectEventTypeForm form
	ON_PARSE_COMMAND(EventTypeSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editEventTypeForm form
	ON_PARSE_COMMAND(EventTypeEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventTypeID Submit")
	//Handle editEventType command
	ON_PARSE_COMMAND(EventTypeEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventTypeID EventDescription Timed=0 EventLength=0.0 Submit")

///////////////////////////////////////////////////////////////////////
// RegistrationType

	//RegistrationType Menu form
	//ON_PARSE_COMMAND(RegistrationTypeMenu, CWebAthlExtension, ITS_PSTR)
	//ON_PARSE_COMMAND_PARAMS("Submit")

	//selectRegistrationTypeForm form
	ON_PARSE_COMMAND(RegistrationTypeSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editRegistrationTypeForm form
	ON_PARSE_COMMAND(RegistrationTypeEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RegistrationTypeID=0 Submit")
	//Handle editRegistrationType command
	ON_PARSE_COMMAND(RegistrationTypeEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RegistrationTypeID RegistrationDescription MonthStart MonthStop Submit")

///////////////////////////////////////////////////////////////////////
// Location

	//Location Menu form
	//ON_PARSE_COMMAND(LocationMenu, CWebAthlExtension, ITS_PSTR)
	//ON_PARSE_COMMAND_PARAMS("Submit")

	//addLocation form
	ON_PARSE_COMMAND(LocationAddForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle addEventType command
	ON_PARSE_COMMAND(LocationAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("LocationID LocationDescription Submit")

	//selectLocation form
	ON_PARSE_COMMAND(LocationSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editLocation form
	ON_PARSE_COMMAND(LocationEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("LocationID Submit")
	//Handle editLocation command
	ON_PARSE_COMMAND(LocationEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("LocationID LocationDescription Submit")

///////////////////////////////////////////////////////////////////////
// Event

	//addEvent form
	ON_PARSE_COMMAND(EventAddForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//Handle addEvent command
	ON_PARSE_COMMAND(EventAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventID SeriesID DateDAY=0 DateMONTH=0 DateYEAR=0 DateAgeDAY=0 DateAgeMONTH=0 DateAgeYEAR=0 EventNo=0 LocationID=0 EventTypeID=0 PreEntryOpen=0 Submit")

	//selectEvent form
	ON_PARSE_COMMAND(EventSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editEvent form
	ON_PARSE_COMMAND(EventEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none EventID=none Submit")
	//Handle editEvent command
	ON_PARSE_COMMAND(EventEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventID SeriesID DateDAY=0 DateMONTH=0 DateYEAR=0 DateAgeDAY=0 DateAgeMONTH=0 DateAgeYEAR=0 EventNo=0 LocationID=0 EventTypeID=0 PreEntryOpen=0 Submit")

///////////////////////////////////////////////////////////////////////
// Roster Descriptions

	//addLocation form
	ON_PARSE_COMMAND(RosterDescriptionsAddForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle addEventType command
	ON_PARSE_COMMAND(RosterDescriptionsAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("TaskID TaskDescription Submit")

	//selectLocation form
	ON_PARSE_COMMAND(RosterDescriptionsSelectForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//editLocation form
	ON_PARSE_COMMAND(RosterDescriptionsEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("TaskID Submit")
	//Handle editLocation command
	ON_PARSE_COMMAND(RosterDescriptionsEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("TaskID TaskDescription Submit")

///////////////////////////////////////////////////////////////////////
// Roster

	//Location Menu form
	ON_PARSE_COMMAND(RosterMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//Location Menu form
	ON_PARSE_COMMAND(RosterSelectEventForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

	//selectRoster form
	ON_PARSE_COMMAND(RosterMaintainMenu, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none EventID=none Submit")
	//addRoster command
	ON_PARSE_COMMAND(RosterAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")

	//Handle editRoster command
	ON_PARSE_COMMAND(RosterEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventID SeriesID TaskIDList PersonIDList Submit")

	//delete roster form
	ON_PARSE_COMMAND(RosterDeleteForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init=none")
	//delete roster command
	ON_PARSE_COMMAND(RosterDeleteExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventID SeriesID PersonID Submit")

///////////////////////////////////////////////////////////////////////
// Results

	//Results form
	ON_PARSE_COMMAND(ResultsEntryPrePostMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//selectEvent form
	ON_PARSE_COMMAND(ResultsEntrySelectEventForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

	//add Results form
	ON_PARSE_COMMAND(ResultsEntryMenu,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none EventID=none Submit")
	//add Results form
	ON_PARSE_COMMAND(ResultsEntryAddForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID=-1 Submit")
	//add Results command
	ON_PARSE_COMMAND(ResultsEntryAddExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID PersonID GrossPerformanceHOUR GrossPerformanceMIN GrossPerformanceSEC Place GroupID Division AgeGroup ChestNumber Points NewGroupID NewGroupMessage Submit")

	//edit Results form
	ON_PARSE_COMMAND(ResultsEntryEditForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//edit Results command
	ON_PARSE_COMMAND(ResultsEntryEditExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID PersonID GrossPerformanceHOUR GrossPerformanceMIN GrossPerformanceSEC Place GroupID Division AgeGroup ChestNumber Points NewGroupID NewGroupMessage Submit")

	//Results Report
	ON_PARSE_COMMAND(ResultsEntryReportForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//select Division Form
//	ON_PARSE_COMMAND(ResultsEntrySelectDivisionForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
//	ON_PARSE_COMMAND_PARAMS("Submit Init=none")
	//quick Entry Form
	ON_PARSE_COMMAND(ResultsEntryQuickAddForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//quick Entry
	ON_PARSE_COMMAND(ResultsEntryQuickAddExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID DivisionList=0 PlaceList=0 PersonIDList=0 AgeGroupList=0 PerformanceHOURList=0 PerformanceMINList=0 PerformanceSECList=0 GroupIDList=0 ChestNumberList= PointsList=0 NewGroupIDList=0 NewGroupMessageList= Submit")

	//bulk Entry Form
	ON_PARSE_COMMAND(ResultsEntryBulkAddForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//bulk Entry Command
	ON_PARSE_COMMAND(ResultsEntryBulkAddExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID BulkResults Submit")

//	ON_PARSE_COMMAND(bulkEntry,CWebAthlExtension, ITS_RAW)

	//Delete Results Form
	ON_PARSE_COMMAND(ResultsEntryDeleteForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

///////////////////////////////////////////////////////////////////////
// World Standard

	//World Standard Menu
	ON_PARSE_COMMAND(WorldStandardMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//select Standard form
	ON_PARSE_COMMAND(WorldStandardSelectForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//edit Standard form
	ON_PARSE_COMMAND(WorldStandardEditForm,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventTypeID AgeCategory RecCategory Sex Submit")
	//edit Standard command
	ON_PARSE_COMMAND(WorldStandardEditExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventTypeID AgeCategory RecCategory Sex AgeGroupList=0 PerformanceHOURList=0 PerformanceMINList=0 PerformanceSECList=0 FactorList=0 Submit")

///////////////////////////////////////////////////////////////////////
// Financial

	//Financial Menu
	ON_PARSE_COMMAND(FinancialMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//addFinancial form
	ON_PARSE_COMMAND(FinancialAddForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//Handle addFinancial command
	ON_PARSE_COMMAND(FinancialAddExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID DateRenewedDAY DateRenewedMONTH DateRenewedYEAR MailListFlag RegistrationTypeID OrgID Year RegistrationID Submit")

	//editFinancial form
	ON_PARSE_COMMAND(FinancialEditForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//Handle editFinancial command
	ON_PARSE_COMMAND(FinancialEditExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID MailListFlag RegistrationTypeID OldRegTypeID OrgID Year Submit")

///////////////////////////////////////////////////////////////////////
// Processing

	//Processing Main Menu
	ON_PARSE_COMMAND(ProcessingForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=none Submit")

	//Process
	ON_PARSE_COMMAND(ProcessingExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("dwProc Submit")

///////////////////////////////////////////////////////////////////////
// Utilities

	//Utilities Main Menu
	ON_PARSE_COMMAND(UtilitiesMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//Utility Change Group Select Series Form
	ON_PARSE_COMMAND(UtilitiesChangeSelectSeriesForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Submit")
	//Utility Change Group Form
	ON_PARSE_COMMAND(UtilitiesChangeForm,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID SeriesID Submit")
	//handle Utility Change Group command
	ON_PARSE_COMMAND(UtilitiesChangeExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID SeriesID GroupIDSupposedTo= DivisionSupposedTo= NewGroupMessage= EligibilityForEvent= Submit")

	//Utility Set Eligibility Select Group Form
	ON_PARSE_COMMAND(UtilitiesSetEligibilitySelectGroupForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//Utility Set Eligibility Form
	ON_PARSE_COMMAND(UtilitiesSetEligibilityByGroupForm,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID GroupIDfr GroupIDto showParticipants=0 Submit")
	//handle Utility Set Eligibility command
	ON_PARSE_COMMAND(UtilitiesSetEligibilityByGroupExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID GroupIDfr GroupIDto Eligible Submit")

	//Utility Bulk Adjust Form
	ON_PARSE_COMMAND(UtilitiesBulkAdjustForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	////handle Utility Bulk Adjust command.
	ON_PARSE_COMMAND(UtilitiesBulkAdjustExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID LowGroup HighGroup Multiplier NewGroupMessage Submit")

	//Utility Split Division Form
	ON_PARSE_COMMAND(UtilitiesSplitDivisionForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//handle Utility Split Division command.
	ON_PARSE_COMMAND(UtilitiesSplitDivisionExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID LowGroup HighGroup Division Submit")

	//Utility Split Division Form
	ON_PARSE_COMMAND(UtilitiesSplitDivisionByAgeGroupForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//Utility Split Division Command
	ON_PARSE_COMMAND(UtilitiesSplitDivisionByAgeGroupExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=0 LowGroup=0 HighGroup=0 SpecifySex=0 Sex=0 Division=0 Submit")

	//Utility Delete Results Form
	ON_PARSE_COMMAND(UtilitiesDeleteResultsForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//handle Delete Results command.
	ON_PARSE_COMMAND(UtilitiesDeleteResultsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID Submit")

	//fix Duplicate Person form
	ON_PARSE_COMMAND(UtilitiesFixDuplicatePersonForm, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID dupPersonID Submit")
	//fix Duplicate Person command
	ON_PARSE_COMMAND(UtilitiesFixDuplicatePersonExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID dupPersonID DuplicatePerson LastName FirstName OnError Option=0 Submit")

	//util Rebuild AgeGroups form
	ON_PARSE_COMMAND(UtilitiesRebuildAgeGroupsForm, CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//util Rebuild AgeGroups command
	ON_PARSE_COMMAND(UtilitiesRebuildAgeGroupsExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID doResults=0 doPreResults=0 doPostResults=0 Submit")

///////////////////////////////////////////////////////////////////////
// Reports

	//Reports Main Menu
	ON_PARSE_COMMAND(ReportsMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//reportClubRecordsForm
	ON_PARSE_COMMAND(ReportsClubRecordsForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle reportClubRecords
	ON_PARSE_COMMAND(ReportsClubRecordsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID SexMale=0 SexFemale=0 UseAgeGroup=0 AgeGroup= OrderByLocation=0 OrderByEventDescription=0 OrderByDate=0 OrderByAgeGroup=0 OrderBySex=0 OrderByNameDesc=0 Option=0 Submit")

	//reportParticipantForm
	ON_PARSE_COMMAND(ReportsParticipantHistoryForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID=none Submit")
	//Handle reportParticipantHistory
	ON_PARSE_COMMAND(ReportsParticipantHistoryExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID SeriesID OrderBy Option=0 Submit")
	
	//Handle reportFinancialHistoryForm
	ON_PARSE_COMMAND(ReportsFinancialHistoryForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID=none Submit")

	//Handle reportFinancialHistory
	ON_PARSE_COMMAND(ReportsFinancialHistoryExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("PersonID Option=0 Submit")

	//reportEventTallyForm
	ON_PARSE_COMMAND(ReportsEventTallyForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle reportEventTally

	ON_PARSE_COMMAND(ReportsEventTallyExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesIDList=0 TallyTop=999 TallyBot=0 useAllEvents=1 EventDateFromDAY=0 EventDateFromMONTH=0 EventDateFromYEAR=0 EventDateToDAY=0 EventDateToMONTH=0 EventDateToYEAR=0 Submit")

  	//Handle reportresults
	ON_PARSE_COMMAND(ReportsResultsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID OrderByDivision=0 Option=0 Submit")
	
	//reportResultsForm
	ON_PARSE_COMMAND(ReportsResultsForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

  	//Handle reportGroupsAlpha
	ON_PARSE_COMMAND(ReportsGroupsListExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID EventsMin= Eligible=0 Division=0 Group=0 Sex=0 AgeGroup=0 Points=0 NameDesc=0 Option=0 Submit")
	//reportGroupsAlphaForm
	ON_PARSE_COMMAND(ReportsGroupsListForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
/*
  	//Handle reportGroupsAlphaElig
	ON_PARSE_COMMAND(ReportsEligibilityExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID Submit")
	//reportGroupsAlphaEligForm
	ON_PARSE_COMMAND(ReportsEligibilityForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
*/
  	//Handle reportRoster
	ON_PARSE_COMMAND(ReportsRosterExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventID OrderByTask=0 NameDesc=0 Option=0 Submit")
	//reportRosterForm
	ON_PARSE_COMMAND(ReportsRosterForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

	//reportPersonForm
	ON_PARSE_COMMAND(ReportsPersonForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle reportPerson
	ON_PARSE_COMMAND(ReportsPersonExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Financial=0 optFinancial=0 optFinancialYear=0 RegistrationType=0 optRegTypeID=0 Series=0 optSeriesID=0 AgeGroup=0 optAgeGroup=0 Birthday=0 optMonth=0 MailList=0 optMailList=0 Organisation=0 optOrgID=0 Comments=0 optPersonCommentsType= Option=0  Submit")

	//Handle reportRules
	ON_PARSE_COMMAND(ReportsRulesExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")

	//reportAwardsForm
	ON_PARSE_COMMAND(ReportsAwardsForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle reportAwards
	ON_PARSE_COMMAND(ReportsAwardsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventsMin=0 Organisation=0 Division=0 Sex=0 AgeGroup=0 OrderBy=0 Desc=0 Option=0 Submit")

	//reportCustomForm
	ON_PARSE_COMMAND(ReportsCustomForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle reportCustom
	ON_PARSE_COMMAND(ReportsCustomExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("CustomQuery Submit")

	//ReportAgeGroupRankingForm
	ON_PARSE_COMMAND(ReportsAgeGroupRankingForm,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID=0 LocationID=0 EventTypeID=0 Submit")
	//ReportAgeGroupRankingResults
	ON_PARSE_COMMAND(ReportsAgeGroupRankingExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID LocationID EventTypeID Submit")

	//ReportAgeGroupRankingForm
	ON_PARSE_COMMAND(ReportsSeriesStatisticsForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID Submit")
	//ReportAgeGroupRankingResults
	ON_PARSE_COMMAND(ReportsSeriesStatisticsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("SeriesID EventIDFrom EventIDTo Submit")

	//ReportResultsBySeriesForm
	ON_PARSE_COMMAND(ReportsResultsBySeriesForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//ReportResultsBySeriesResults
	ON_PARSE_COMMAND(ReportsResultsBySeriesExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventDateFromDAY=0 EventDateFromMONTH=0 EventDateFromYEAR=0 EventDateToDAY=0 EventDateToMONTH=0 EventDateToYEAR=0 SeriesIDList=0 OrderByDivision=0 Option=0 Submit")

	//ReportsEventCalendarForm
	ON_PARSE_COMMAND(ReportsEventCalendarForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//ReportsEventCalendarExecute
	ON_PARSE_COMMAND(ReportsEventCalendarExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("EventDateFromDAY=0 EventDateFromMONTH=0 EventDateFromYEAR=0 EventDateToDAY=0 EventDateToMONTH=0 EventDateToYEAR=0 SeriesID=0 LocationID=0 EventTypeID=0 OrderByEventDate=0 OrderDescending=0 OrderBySeries=0 OrderByEventNo=0 OrderByLocation=0 OrderByEventType=0 Option=0 Submit")


///////////////////////////////////////////////////////////////////////
// Options

	//Options Main Menu
	ON_PARSE_COMMAND(OptionsMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Options ODBC Setup form
	ON_PARSE_COMMAND(OptionsODBCSetupForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//Options AgeGroup form
	ON_PARSE_COMMAND(OptionsAgeGroupsForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Options AgeGroup command
	ON_PARSE_COMMAND(OptionsAgeGroupsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("MaxJunior JuniorGroup MinVeteran VeteranGroup NullDoB Submit")

	//Options Processing form
	ON_PARSE_COMMAND(OptionsProcessingForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Options Processing command
	ON_PARSE_COMMAND(OptionsProcessingExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("TimeOut Submit")

	//Options Appearance form
	ON_PARSE_COMMAND(OptionsAppearanceForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//HandleOptions Appearance command
	ON_PARSE_COMMAND(OptionsAppearanceExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("StyleSheet Font BackgroundColor MenuColor BackgroundImage MenuImage Logo Submit")

	//Options Crypt form
	ON_PARSE_COMMAND(OptionsCryptographyForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Options Crypt command
	ON_PARSE_COMMAND(OptionsCryptographyExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Enabled=0 Submit")

	//Options ExitURL form
	ON_PARSE_COMMAND(OptionsNavigationForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Options Crypt command
	ON_PARSE_COMMAND(OptionsNavigationExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("ExitURL Submit")

	//Options PersonSearch form
	ON_PARSE_COMMAND(OptionsPersonSearchForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle OPersonSearch command
	ON_PARSE_COMMAND(OptionsPersonSearchExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("LastName=0 FirstName=0 MiddleName=0 DateOfBirth=0 Sex=0 Submit")

///////////////////////////////////////////////////////////////////////
// Maintenance

	//Maintenance Main Menu
	ON_PARSE_COMMAND(MaintenanceMenu,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

	//Maintenance Set Folder Form
	ON_PARSE_COMMAND(MaintenanceSetFolderForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Maintenance Set Folder Command
	ON_PARSE_COMMAND(MaintenanceSetFolderExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("BackupFolder Submit")

	//Maintenance Crypt Passwords Form
	ON_PARSE_COMMAND(MaintenanceCryptPasswordsForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Maintenance Crypt Passwords Command
	ON_PARSE_COMMAND(MaintenanceCryptPasswordsExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Decrypt=0 Submit")

	//Disable Users form
	ON_PARSE_COMMAND(MaintenanceDisableUsersForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Disable Users command
	ON_PARSE_COMMAND(MaintenanceDisableUsersExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Enabled=0 Submit")

	//MaintainDatabaseForm
	ON_PARSE_COMMAND(MaintenanceMaintainDatabaseForm,CWebAthlExtension, ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit Init")
	//MaintainDatabaseExecute
	ON_PARSE_COMMAND(MaintenanceMaintainDatabaseExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("ItemList Items=0 Submit")

///////////////////////////////////////////////////////////////////////
// Login

	//Login form
	ON_PARSE_COMMAND(DefaultLoginForm,CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Login command
	ON_PARSE_COMMAND(DefaultLoginExecute,CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("LoginName Password Submit")

///////////////////////////////////////////////////////////////////////
// Entry Menu

	//Display Entry page
	ON_PARSE_COMMAND(DefaultEntry, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

///////////////////////////////////////////////////////////////////////
// Start Menu

	//Display Start page
	ON_PARSE_COMMAND(DefaultMenu, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")

///////////////////////////////////////////////////////////////////////
// Default Page

	//Display Default page if request is empty.
	//ON_PARSE_COMMAND(Default, CWebAthlExtension, ITS_EMPTY)	
	ON_PARSE_COMMAND(Default, CWebAthlExtension, ITS_PSTR)	
	ON_PARSE_COMMAND_PARAMS("Submit=")
	DEFAULT_PARSE_COMMAND(Default, CWebAthlExtension)
	//Display Setup page
	ON_PARSE_COMMAND(DefaultODBCSetupForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle Setup command
	ON_PARSE_COMMAND(DefaultODBCSetupExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("URL Server UID PWD Database Driver DSN Submit")

///////////////////////////////////////////////////////////////////////
// License

	//Display License page
	ON_PARSE_COMMAND(LicenseForm, CWebAthlExtension, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Submit")
	//Handle License command
	ON_PARSE_COMMAND(LicenseExecute, CWebAthlExtension, ITS_PSTR ITS_PSTR ITS_PSTR ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("RegNo RegName RegKey Submit")


END_PARSE_MAP(CWebAthlExtension)





///////////////////////////////////////////////////////////////////////
// The one and only CWebAthlExtension object

CWebAthlExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CWebAthlExtension implementation

CWebAthlExtension::CWebAthlExtension()
{
}

//CWebAthlExtension::~CWebAthlExtension()
//{
//}

BOOL CWebAthlExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}


///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/


TCHAR CWebAthlExtension::chIsapiDelimiter = ',';

CString CWebAthlExtension::CallStatus( int nStatus )
{
	CString str;

	switch( nStatus )
	{
		case CHttpServer::callOK :
			str = _T("The function call was successful.");
			break;
		case CHttpServer::callParamRequired :
			str = _T("A required parameter was missing.");
			break;
		case CHttpServer::callBadParamCount :
			str = _T("There were too many or too few parameters.");
			break;
		case CHttpServer::callBadCommand :
			str = _T("The command name was not found.");
			break;
		case CHttpServer::callNoStackSpace :
			str = _T("No stack space was available.");
			break;
		case CHttpServer::callNoStream :
			str = _T("No CHtmlStream was available.");
			break;
		case CHttpServer::callMissingQuote :
			str = _T("A parameter had a bad format.");
			break;
		case CHttpServer::callMissingParams :
			str = _T("No parameters were available.");
			break;
		case CHttpServer::callBadParam :
			str = _T("A parameter had a bad format (i.e., only one quote).");
			break;
	}

	return str;
}

int CWebAthlExtension::CallFunction(CHttpServerContext* pCtxt,
									LPTSTR pszQuery, LPTSTR pszCommand)
{
	CString strQuery = CUtil::ParseHttpPostQuery(pszQuery, CWebAthlExtension::chIsapiDelimiter);
	
	LPTSTR szQuery = strQuery.GetBuffer( strQuery.GetLength( ) );

	int nStatus = CHttpServer::callOK ;

//	try
//	{
		nStatus = CHttpServer::CallFunction(pCtxt, szQuery, pszCommand);
//	}
//	catch (...)
//	{
/*
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		html << (LPCTSTR)lpMsgBuf << _T("<BR>\r\n");
		// Free the buffer.
		LocalFree( lpMsgBuf );
*/
//	}

	strQuery.ReleaseBuffer( );


	if( nStatus != CHttpServer::callOK )
	{
		CHtmlWriter html = CHtmlWriter( pCtxt, this );

		html.SetContent();
		html.EndHeader();

		html.WritePageTitle();

		html << _T("<body>\r\n");
		html << _T("<h1>Invalid Request</h1>\r\n");
		html << _T("<hr>\r\n");

		html << _T("Status : <B>[") 
			 << CConvert::itoa( nStatus ) 
			 << _T("] ") 
			 << CallStatus( nStatus ) 
			 << _T("</B><BR><BR>\r\n");

		html << _T("Query : <B>") << pszQuery << _T("</B><BR>\r\n");
		html << _T("Command : <B>") << pszCommand << _T("</B><BR>\r\n");

		html.EndContent( );
	}

//	return nStatus;
	return CHttpServer::callOK;
}

/*
//PRB: Parse Maps Do Not Handle Multi-select List Boxes
//ID: Q169109 

int CWebAthlExtension::CallFunction(CHttpServerContext* pCtxt,
									LPTSTR pszQuery, LPTSTR pszCommand)
{
	m_strQuery = CString(pszQuery);
	m_strCommand = CString(pszCommand);


	LPTSTR queryIn = pszQuery;
	LPTSTR queryOut = new TCHAR[_tcslen(queryIn) + sizeof(TCHAR)];
	LPTSTR pOut = queryOut;
	*pOut = NULL;

	LPTSTR pIn = queryIn;
	// Copy everything till the first ?
	if (_tcschr(pIn, '?'))
	{
		pIn = _tcschr(pIn, '?');
		pIn++;
		memcpy(pOut, queryIn, (pIn - queryIn)); //copy till the ?
		pOut += (pIn - queryIn);
		*pOut = NULL;
	}

	LPTSTR lastParameter = NULL;
	int nLastParameterLen = 0;

	while (pIn && *pIn)
	{
		// Is there a '=' in the input string
		LPTSTR q = _tcschr(pIn, '=');
		if (!q)
		{
			// No. Copy till end of the buffer and break out
			// No more parameter/value pairs.
			_tcscpy(pOut, pIn);
			break;
		}

		int paramLen = (q - pIn);

		// Is the last parameter name the same as the present
		// parameter name?
		if (paramLen &&
			nLastParameterLen == paramLen &&
			_tcsncmp(lastParameter, pIn, nLastParameterLen) == 0)
		{
			// Yes! replace & with , and just copy the value
			// of the parameter.
			q++;
			if (*q)
			{
				LPTSTR r = _tcschr(q, '&');
				*(pOut - 1) = CWebAthlExtension::chIsapiDelimiter;
				//copy the value
				if (r)
				{
					_tcsncpy(pOut, q, (r - q) + 1);
					pOut+=(r - q) + 1;
					pIn = r + 1;
				}
				else
				{
					_tcscpy(pOut, q);
					break;
				}
			}
			else
			{
				*(pOut - 1) = CWebAthlExtension::chIsapiDelimiter;
				*pOut = NULL;
				break;
			}
		}
		else
		{
			nLastParameterLen = paramLen;
			lastParameter = pIn;

			q = _tcschr(pIn, '&');
			if (q)
			{
				if (paramLen)
				{
					_tcsncpy(pOut, pIn, (q - pIn) + 1);
					pOut += (q - pIn) + 1;
				}
				pIn = q + 1;
			}
			else
			{
				if (paramLen)
				{
					_tcscpy(pOut, pIn);
					break;
				}
				else
				{
					if (pOut == queryOut)
						*pOut = NULL;
					else
						*(pOut - 1) = NULL;
					break;
				}
			}
		}
	}

	pszQuery = queryOut;

	int nRet = CHttpServer::CallFunction(pCtxt, pszQuery, pszCommand);

	delete []queryOut;

	return nRet;
} 
*/
