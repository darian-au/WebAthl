// CPage.cpp : implementation file
//

#include "stdafx.h"

#include "Page.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Page

LPCTSTR CPage::Default = _T("Default");
LPCTSTR CPage::DefaultEntry = _T("DefaultEntry");
LPCTSTR CPage::DefaultLoginForm = _T("DefaultLoginForm");
LPCTSTR CPage::DefaultLoginExecute = _T("DefaultLoginExecute");
LPCTSTR CPage::DefaultMenu = _T("DefaultMenu");

LPCTSTR CPage::DefaultODBCSetupForm = _T("DefaultODBCSetupForm");
LPCTSTR CPage::DefaultODBCSetupExecute = _T("DefaultODBCSetupExecute");


LPCTSTR CPage::EventSelectForm = _T("EventSelectForm");
LPCTSTR CPage::EventAddForm = _T("EventAddForm");
LPCTSTR CPage::EventAddExecute = _T("EventAddExecute");
LPCTSTR CPage::EventEditForm = _T("EventEditForm");
LPCTSTR CPage::EventEditExecute = _T("EventEditExecute");

LPCTSTR CPage::EventTypeMenu = _T("EventTypeMenu");
LPCTSTR CPage::EventTypeSelectForm = _T("EventTypeSelectForm");
LPCTSTR CPage::EventTypeAddForm = _T("EventTypeAddForm");
LPCTSTR CPage::EventTypeAddExecute = _T("EventTypeAddExecute");
LPCTSTR CPage::EventTypeEditForm = _T("EventTypeEditForm");
LPCTSTR CPage::EventTypeEditExecute = _T("EventTypeEditExecute");

LPCTSTR CPage::FinancialMenu = _T("FinancialMenu");
LPCTSTR CPage::FinancialAddForm = _T("FinancialAddForm");
LPCTSTR CPage::FinancialEditForm = _T("FinancialEditForm");
LPCTSTR CPage::FinancialAddExecute = _T("FinancialAddExecute");
LPCTSTR CPage::FinancialEditExecute = _T("FinancialEditExecute");

LPCTSTR CPage::SearchPersonForm = _T("SearchPersonForm");
LPCTSTR CPage::SearchPersonSelectForm = _T("SearchPersonSelectForm");

LPCTSTR CPage::GroupsEditSelectForm = _T("GroupsEditSelectForm");
LPCTSTR CPage::GroupsEditForm = _T("GroupsEditForm");
LPCTSTR CPage::GroupsEditExecute = _T("GroupsEditExecute");

LPCTSTR CPage::LicenseForm = _T("LicenseForm");
LPCTSTR CPage::LicenseExecute = _T("LicenseExecute");

LPCTSTR CPage::LocationMenu = _T("LocationMenu");
LPCTSTR CPage::LocationSelectForm = _T("LocationSelectForm");
LPCTSTR CPage::LocationAddForm = _T("LocationAddForm");
LPCTSTR CPage::LocationAddExecute = _T("LocationAddExecute");
LPCTSTR CPage::LocationEditForm = _T("LocationEditForm");
LPCTSTR CPage::LocationEditExecute = _T("LocationEditExecute");

LPCTSTR CPage::MaintenanceMenu = _T("MaintenanceMenu");
LPCTSTR CPage::MaintenanceMaintainDatabaseForm = _T("MaintenanceMaintainDatabaseForm");
LPCTSTR CPage::MaintenanceMaintainDatabaseExecute = _T("MaintenanceMaintainDatabaseExecute");
LPCTSTR CPage::MaintenanceSetFolderForm = _T("MaintenanceSetFolderForm");
LPCTSTR CPage::MaintenanceSetFolderExecute = _T("MaintenanceSetFolderExecute");
LPCTSTR CPage::MaintenanceDisableUsersForm = _T("MaintenanceDisableUsersForm");
LPCTSTR CPage::MaintenanceDisableUsersExecute = _T("MaintenanceDisableUsersExecute");
LPCTSTR CPage::MaintenanceCryptPasswordsForm = _T("MaintenanceCryptPasswordsForm");
LPCTSTR CPage::MaintenanceCryptPasswordsExecute = _T("MaintenanceCryptPasswordsExecute");

LPCTSTR CPage::OptionsMenu = _T("OptionsMenu");
LPCTSTR CPage::OptionsAppearanceForm = _T("OptionsAppearanceForm");
LPCTSTR CPage::OptionsAppearanceExecute = _T("OptionsAppearanceExecute");
LPCTSTR CPage::OptionsNavigationForm = _T("OptionsNavigationForm");
LPCTSTR CPage::OptionsNavigationExecute = _T("OptionsNavigationExecute");
LPCTSTR CPage::OptionsAgeGroupsForm = _T("OptionsAgeGroupsForm");
LPCTSTR CPage::OptionsAgeGroupsExecute = _T("OptionsAgeGroupsExecute");
LPCTSTR CPage::OptionsPersonSearchForm = _T("OptionsPersonSearchForm");
LPCTSTR CPage::OptionsPersonSearchExecute = _T("OptionsPersonSearchExecute");
LPCTSTR CPage::OptionsProcessingForm = _T("OptionsProcessingForm");
LPCTSTR CPage::OptionsProcessingExecute = _T("OptionsProcessingExecute");
LPCTSTR CPage::OptionsCryptographyForm = _T("OptionsCryptographyForm");
LPCTSTR CPage::OptionsCryptographyExecute = _T("OptionsCryptographyExecute");
LPCTSTR CPage::OptionsODBCSetupForm = _T("OptionsODBCSetupForm");

LPCTSTR CPage::OrganisationMenu = _T("OrganisationMenu");
LPCTSTR CPage::OrganisationSelectForm = _T("OrganisationSelectForm");
LPCTSTR CPage::OrganisationAddForm = _T("OrganisationAddForm");
LPCTSTR CPage::OrganisationAddExecute = _T("OrganisationAddExecute");
LPCTSTR CPage::OrganisationEditForm = _T("OrganisationEditForm");
LPCTSTR CPage::OrganisationEditExecute = _T("OrganisationEditExecute");
LPCTSTR CPage::OrganisationViewForm = _T("OrganisationViewForm");

LPCTSTR CPage::PersonMenu = _T("PersonMenu");
LPCTSTR CPage::PersonEditForm = _T("PersonEditForm");
LPCTSTR CPage::PersonEditExecute = _T("PersonEditExecute");
LPCTSTR CPage::PersonAddForm = _T("PersonAddForm");
LPCTSTR CPage::PersonAddExecute = _T("PersonAddExecute");
LPCTSTR CPage::PersonViewForm = _T("PersonViewForm");
LPCTSTR CPage::PersonCommentAddExecute = _T("PersonCommentAddExecute");
LPCTSTR CPage::PersonCommentEditExecute = _T("PersonCommentEditExecute");
LPCTSTR CPage::PersonChangePasswordForm = _T("PersonChangePasswordForm");
LPCTSTR CPage::PersonChangePasswordExecute = _T("PersonChangePasswordExecute");

LPCTSTR CPage::ProcessingForm = _T("ProcessingForm");
LPCTSTR CPage::ProcessingExecute = _T("ProcessingExecute");

LPCTSTR CPage::RegistrationTypeMenu = _T("RegistrationTypeMenu");
LPCTSTR CPage::RegistrationTypeSelectForm = _T("RegistrationTypeSelectForm");
LPCTSTR CPage::RegistrationTypeEditForm = _T("RegistrationTypeEditForm");
LPCTSTR CPage::RegistrationTypeEditExecute = _T("RegistrationTypeEditExecute");

LPCTSTR CPage::ReportsMenu = _T("ReportsMenu");
LPCTSTR CPage::ReportsRulesExecute = _T("ReportsRulesExecute");
LPCTSTR CPage::ReportsResultsForm = _T("ReportsResultsForm");
LPCTSTR CPage::ReportsResultsExecute = _T("ReportsResultsExecute");
LPCTSTR CPage::ReportsAwardsForm = _T("ReportsAwardsForm");
LPCTSTR CPage::ReportsAwardsExecute = _T("ReportsAwardsExecute");
LPCTSTR CPage::ReportsEventTallyForm = _T("ReportsEventTallyForm");
LPCTSTR CPage::ReportsEventTallyExecute = _T("ReportsEventTallyExecute");
LPCTSTR CPage::ReportsClubRecordsForm = _T("ReportsClubRecordsForm");
LPCTSTR CPage::ReportsClubRecordsExecute = _T("ReportsClubRecordsExecute");
LPCTSTR CPage::ReportsParticipantHistoryForm = _T("ReportsParticipantHistoryForm");
LPCTSTR CPage::ReportsParticipantHistoryExecute = _T("ReportsParticipantHistoryExecute");
LPCTSTR CPage::ReportsFinancialHistoryForm = _T("ReportsFinancialHistoryForm");
LPCTSTR CPage::ReportsFinancialHistoryExecute = _T("ReportsFinancialHistoryExecute");
LPCTSTR CPage::ReportsPersonForm = _T("ReportsPersonForm");
LPCTSTR CPage::ReportsPersonExecute = _T("ReportsPersonExecute");
LPCTSTR CPage::ReportsRosterForm = _T("ReportsRosterForm");
LPCTSTR CPage::ReportsRosterExecute = _T("ReportsRosterExecute");
LPCTSTR CPage::ReportsGroupsListForm = _T("ReportsGroupsListForm");
LPCTSTR CPage::ReportsGroupsListExecute = _T("ReportsGroupsListExecute");
//LPCTSTR CPage::ReportsEligibilityForm = _T("ReportsEligibilityForm");
//LPCTSTR CPage::ReportsEligibilityExecute = _T("ReportsEligibilityExecute");
LPCTSTR CPage::ReportsAgeGroupRankingForm = _T("ReportsAgeGroupRankingForm");
LPCTSTR CPage::ReportsAgeGroupRankingExecute = _T("ReportsAgeGroupRankingExecute");
LPCTSTR CPage::ReportsSeriesStatisticsForm = _T("ReportsSeriesStatisticsForm");
LPCTSTR CPage::ReportsSeriesStatisticsExecute = _T("ReportsSeriesStatisticsExecute");
LPCTSTR CPage::ReportsCustomForm = _T("ReportsCustomForm");
LPCTSTR CPage::ReportsCustomExecute = _T("ReportsCustomExecute");
LPCTSTR CPage::ReportsResultsBySeriesForm = _T("ReportsResultsBySeriesForm");
LPCTSTR CPage::ReportsResultsBySeriesExecute = _T("ReportsResultsBySeriesExecute");
LPCTSTR CPage::ReportsEventCalendarForm = _T("ReportsEventCalendarForm");;
LPCTSTR CPage::ReportsEventCalendarExecute = _T("ReportsEventCalendarExecute");

LPCTSTR CPage::ResultsEntryMenu = _T("ResultsEntryMenu");
LPCTSTR CPage::ResultsEntryPrePostMenu = _T("ResultsEntryPrePostMenu");
LPCTSTR CPage::ResultsEntrySelectEventForm = _T("ResultsEntrySelectEventForm");
LPCTSTR CPage::ResultsEntryAddForm = _T("ResultsEntryAddForm");
LPCTSTR CPage::ResultsEntryAddExecute = _T("ResultsEntryAddExecute");
LPCTSTR CPage::ResultsEntryEditForm = _T("ResultsEntryEditForm");
LPCTSTR CPage::ResultsEntryEditExecute = _T("ResultsEntryEditExecute");
LPCTSTR CPage::ResultsEntryQuickAddForm = _T("ResultsEntryQuickAddForm");
LPCTSTR CPage::ResultsEntryQuickAddExecute = _T("ResultsEntryQuickAddExecute");
LPCTSTR CPage::ResultsEntryBulkAddForm = _T("ResultsEntryBulkAddForm");
LPCTSTR CPage::ResultsEntryBulkAddExecute = _T("ResultsEntryBulkAddExecute");
LPCTSTR CPage::ResultsEntrySelectDivisionForm = _T("ResultsEntrySelectDivisionForm");
LPCTSTR CPage::ResultsEntryReportForm = _T("ResultsEntryReportForm");
LPCTSTR CPage::ResultsEntryDeleteForm = _T("ResultsEntryDeleteForm");

LPCTSTR CPage::RosterMenu = _T("RosterMenu");
LPCTSTR CPage::RosterMaintainMenu = _T("RosterMaintainMenu");
LPCTSTR CPage::RosterSelectEventForm = _T("RosterSelectEventForm");
LPCTSTR CPage::RosterAddExecute = _T("RosterAddExecute");
LPCTSTR CPage::RosterEditExecute = _T("RosterEditExecute");
LPCTSTR CPage::RosterDeleteForm = _T("RosterDeleteForm");
LPCTSTR CPage::RosterDeleteExecute = _T("RosterDeleteExecute");

LPCTSTR CPage::RosterDescriptionsSelectForm = _T("RosterDescriptionsSelectForm");
LPCTSTR CPage::RosterDescriptionsAddForm = _T("RosterDescriptionsAddForm");
LPCTSTR CPage::RosterDescriptionsAddExecute = _T("RosterDescriptionsAddExecute");
LPCTSTR CPage::RosterDescriptionsEditForm = _T("RosterDescriptionsEditForm");
LPCTSTR CPage::RosterDescriptionsEditExecute = _T("RosterDescriptionsEditExecute");

LPCTSTR CPage::RulesMenu = _T("RulesMenu");
LPCTSTR CPage::RulesAddExecute = _T("RulesAddExecute");
LPCTSTR CPage::RulesEditExecute = _T("RulesEditExecute");
LPCTSTR CPage::RulesSetTypesExecute = _T("RulesSetTypesExecute");

LPCTSTR CPage::SecurityMenu = _T("SecurityMenu");
LPCTSTR CPage::SecurityAssignLoginForm = _T("SecurityAssignLoginForm");
LPCTSTR CPage::SecurityAssignLoginExecute = _T("SecurityAssignLoginExecute");
LPCTSTR CPage::SecurityGrantRoleForm = _T("SecurityGrantRoleForm");
LPCTSTR CPage::SecurityGrantRoleExecute = _T("SecurityGrantRoleExecute");
LPCTSTR CPage::SecurityRevokeRoleForm = _T("SecurityRevokeRoleForm");
LPCTSTR CPage::SecurityRevokeRoleExecute = _T("SecurityRevokeRoleExecute");
LPCTSTR CPage::SecurityRoleAllocatePermissionForm = _T("SecurityRoleAllocatePermissionForm");
LPCTSTR CPage::SecurityRoleAllocatePermissionExecute = _T("SecurityRoleAllocatePermissionExecute");
LPCTSTR CPage::SecurityRoleEditForm = _T("SecurityRoleEditForm");
LPCTSTR CPage::SecurityRoleEditExecute = _T("SecurityRoleEditExecute");
LPCTSTR CPage::SecurityRoleSelectForm = _T("SecurityRoleSelectForm");
LPCTSTR CPage::SecurityAssignSeriesForm = _T("SecurityAssignSeriesForm");
LPCTSTR CPage::SecurityAssignSeriesExecute = _T("SecurityAssignSeriesExecute");

LPCTSTR CPage::SeriesMenu = _T("SeriesMenu");
LPCTSTR CPage::SeriesMaintainMenu = _T("SeriesMaintainMenu");
LPCTSTR CPage::SeriesSelectForm = _T("SeriesSelectForm");
LPCTSTR CPage::SeriesAddForm = _T("SeriesAddForm");
LPCTSTR CPage::SeriesAddExecute = _T("SeriesAddExecute");
LPCTSTR CPage::SeriesEditForm = _T("SeriesEditForm");
LPCTSTR CPage::SeriesEditExecute = _T("SeriesEditExecute");
LPCTSTR CPage::SeriesSetFirstEventForm = _T("SeriesSetFirstEventForm");
LPCTSTR CPage::SeriesSetFirstEventExecute = _T("SeriesSetFirstEventExecute");
LPCTSTR CPage::SeriesSetNextEventForm = _T("SeriesSetNextEventForm");
LPCTSTR CPage::SeriesSetNextEventExecute = _T("SeriesSetNextEventExecute");


LPCTSTR CPage::UtilitiesMenu = _T("UtilitiesMenu");
LPCTSTR CPage::UtilitiesSetEligibilitySelectGroupForm = _T("UtilitiesSetEligibilitySelectGroupForm");
LPCTSTR CPage::UtilitiesSetEligibilityByGroupForm = _T("UtilitiesSetEligibilityByGroupForm");
LPCTSTR CPage::UtilitiesSetEligibilityByGroupExecute = _T("UtilitiesSetEligibilityByGroupExecute");
LPCTSTR CPage::UtilitiesSplitDivisionForm = _T("UtilitiesSplitDivisionForm");
LPCTSTR CPage::UtilitiesSplitDivisionExecute = _T("UtilitiesSplitDivisionExecute");
LPCTSTR CPage::UtilitiesSplitDivisionByAgeGroupForm = _T("UtilitiesSplitDivisionByAgeGroupForm");
LPCTSTR CPage::UtilitiesSplitDivisionByAgeGroupExecute = _T("UtilitiesSplitDivisionByAgeGroupExecute");
LPCTSTR CPage::UtilitiesChangeSelectSeriesForm = _T("UtilitiesChangeSelectSeriesForm");
LPCTSTR CPage::UtilitiesChangeForm = _T("UtilitiesChangeForm");
LPCTSTR CPage::UtilitiesChangeExecute = _T("UtilitiesChangeExecute");
LPCTSTR CPage::UtilitiesRebuildAgeGroupsForm = _T("UtilitiesRebuildAgeGroupsForm");
LPCTSTR CPage::UtilitiesRebuildAgeGroupsExecute = _T("UtilitiesRebuildAgeGroupsExecute");
LPCTSTR CPage::UtilitiesFixDuplicatePersonForm = _T("UtilitiesFixDuplicatePersonForm");
LPCTSTR CPage::UtilitiesFixDuplicatePersonExecute = _T("UtilitiesFixDuplicatePersonExecute");
LPCTSTR CPage::UtilitiesBulkAdjustForm = _T("UtilitiesBulkAdjustForm");
LPCTSTR CPage::UtilitiesBulkAdjustExecute = _T("UtilitiesBulkAdjustExecute");
LPCTSTR CPage::UtilitiesDeleteResultsForm = _T("UtilitiesDeleteResultsForm");
LPCTSTR CPage::UtilitiesDeleteResultsExecute = _T("UtilitiesDeleteResultsExecute");

LPCTSTR CPage::WorldStandardMenu = _T("WorldStandardMenu");
LPCTSTR CPage::WorldStandardSelectForm = _T("WorldStandardSelectForm");
LPCTSTR CPage::WorldStandardEditForm = _T("WorldStandardEditForm");
LPCTSTR CPage::WorldStandardEditExecute = _T("WorldStandardEditExecute");


/////////////////////////////////////////////////////////////////////////////
// Constructor

//CPage::CPage( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CPage::~CPage( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

