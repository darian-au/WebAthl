#if !defined(AFX_PAGE_H__INCLUDED_)
#define AFX_PAGE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage

class CPage
{

	public:

		// Constructor
		//CPage( );	

		// Destructor
		//~CPage( );

		// Member functions

		// Static functions

		// Member variables

		// Static variables

		static LPCTSTR Default;
		static LPCTSTR DefaultEntry;
		static LPCTSTR DefaultLoginForm;
		static LPCTSTR DefaultLoginExecute;
		static LPCTSTR DefaultMenu;

		static LPCTSTR DefaultODBCSetupForm;
		static LPCTSTR DefaultODBCSetupExecute;


		static LPCTSTR EventSelectForm;
		static LPCTSTR EventAddForm;
		static LPCTSTR EventAddExecute;
		static LPCTSTR EventEditForm;
		static LPCTSTR EventEditExecute;

		static LPCTSTR EventTypeMenu;
		static LPCTSTR EventTypeSelectForm;
		static LPCTSTR EventTypeAddForm;
		static LPCTSTR EventTypeAddExecute;
		static LPCTSTR EventTypeEditForm;
		static LPCTSTR EventTypeEditExecute;

		static LPCTSTR FinancialMenu;
		static LPCTSTR FinancialAddForm;
		static LPCTSTR FinancialAddExecute;
		static LPCTSTR FinancialEditForm;
		static LPCTSTR FinancialEditExecute;

		static LPCTSTR SearchPersonForm;
		static LPCTSTR SearchPersonSelectForm;

		static LPCTSTR GroupsEditSelectForm;
		static LPCTSTR GroupsEditForm;
		static LPCTSTR GroupsEditExecute;

		static LPCTSTR LicenseForm;
		static LPCTSTR LicenseExecute;

		static LPCTSTR LocationMenu;
		static LPCTSTR LocationSelectForm;
		static LPCTSTR LocationAddForm;
		static LPCTSTR LocationEditForm;
		static LPCTSTR LocationAddExecute;
		static LPCTSTR LocationEditExecute;

		static LPCTSTR MaintenanceMenu;
		static LPCTSTR MaintenanceMaintainDatabaseForm;
		static LPCTSTR MaintenanceMaintainDatabaseExecute;
		static LPCTSTR MaintenanceSetFolderForm;
		static LPCTSTR MaintenanceSetFolderExecute;
		static LPCTSTR MaintenanceDisableUsersForm;
		static LPCTSTR MaintenanceDisableUsersExecute;
		static LPCTSTR MaintenanceCryptPasswordsForm;
		static LPCTSTR MaintenanceCryptPasswordsExecute;

		static LPCTSTR OptionsMenu;
		static LPCTSTR OptionsAppearanceForm;
		static LPCTSTR OptionsAppearanceExecute;
		static LPCTSTR OptionsNavigationForm;
		static LPCTSTR OptionsNavigationExecute;
		static LPCTSTR OptionsAgeGroupsForm;
		static LPCTSTR OptionsAgeGroupsExecute;
		static LPCTSTR OptionsPersonSearchForm;
		static LPCTSTR OptionsPersonSearchExecute;
		static LPCTSTR OptionsProcessingForm;
		static LPCTSTR OptionsProcessingExecute;
		static LPCTSTR OptionsCryptographyForm;
		static LPCTSTR OptionsCryptographyExecute;
		static LPCTSTR OptionsODBCSetupForm;

		static LPCTSTR OrganisationMenu;
		static LPCTSTR OrganisationSelectForm;
		static LPCTSTR OrganisationAddForm;
		static LPCTSTR OrganisationAddExecute;
		static LPCTSTR OrganisationEditForm;
		static LPCTSTR OrganisationEditExecute;
		static LPCTSTR OrganisationViewForm;

		static LPCTSTR PersonMenu;
		static LPCTSTR PersonEditForm;
		static LPCTSTR PersonEditExecute;
		static LPCTSTR PersonAddForm;
		static LPCTSTR PersonAddExecute;
		static LPCTSTR PersonViewForm;
		static LPCTSTR PersonCommentAddExecute;
		static LPCTSTR PersonCommentEditExecute;
		static LPCTSTR PersonChangePasswordForm;
		static LPCTSTR PersonChangePasswordExecute;

		static LPCTSTR ProcessingForm;
		static LPCTSTR ProcessingExecute;

		static LPCTSTR RegistrationTypeMenu;
		static LPCTSTR RegistrationTypeSelectForm;
		static LPCTSTR RegistrationTypeEditForm;
		static LPCTSTR RegistrationTypeEditExecute;

		static LPCTSTR ResultsEntryMenu;
		static LPCTSTR ResultsEntryPrePostMenu;
		static LPCTSTR ResultsEntrySelectEventForm;
		static LPCTSTR ResultsEntryAddForm;
		static LPCTSTR ResultsEntryAddExecute;
		static LPCTSTR ResultsEntryEditForm;
		static LPCTSTR ResultsEntryEditExecute;
		static LPCTSTR ResultsEntryQuickAddForm;
		static LPCTSTR ResultsEntryQuickAddExecute;
		static LPCTSTR ResultsEntryBulkAddForm;
		static LPCTSTR ResultsEntryBulkAddExecute;
		static LPCTSTR ResultsEntrySelectDivisionForm;
		static LPCTSTR ResultsEntryReportForm;
		static LPCTSTR ResultsEntryDeleteForm;

		static LPCTSTR ReportsMenu;
		static LPCTSTR ReportsRulesExecute;
		static LPCTSTR ReportsResultsForm;
		static LPCTSTR ReportsResultsExecute;
		static LPCTSTR ReportsAwardsForm;
		static LPCTSTR ReportsAwardsExecute;
		static LPCTSTR ReportsEventTallyForm;
		static LPCTSTR ReportsEventTallyExecute;
		static LPCTSTR ReportsClubRecordsForm;
		static LPCTSTR ReportsClubRecordsExecute;
		static LPCTSTR ReportsParticipantHistoryForm;
		static LPCTSTR ReportsParticipantHistoryExecute;
		static LPCTSTR ReportsFinancialHistoryForm;
		static LPCTSTR ReportsFinancialHistoryExecute;
		static LPCTSTR ReportsPersonForm;
		static LPCTSTR ReportsPersonExecute;
		static LPCTSTR ReportsRosterForm;
		static LPCTSTR ReportsRosterExecute;
		static LPCTSTR ReportsGroupsListForm;
		static LPCTSTR ReportsGroupsListExecute;
		//static LPCTSTR ReportsEligibilityForm;
		//static LPCTSTR ReportsEligibilityExecute;
		static LPCTSTR ReportsAgeGroupRankingForm;
		static LPCTSTR ReportsAgeGroupRankingExecute;
		static LPCTSTR ReportsSeriesStatisticsForm;
		static LPCTSTR ReportsSeriesStatisticsExecute;
		static LPCTSTR ReportsCustomForm;
		static LPCTSTR ReportsCustomExecute;
		static LPCTSTR ReportsResultsBySeriesForm;
		static LPCTSTR ReportsResultsBySeriesExecute;
		static LPCTSTR ReportsEventCalendarForm;
		static LPCTSTR ReportsEventCalendarExecute;

		static LPCTSTR RosterMenu;
		static LPCTSTR RosterMaintainMenu;
		static LPCTSTR RosterSelectEventForm;
		static LPCTSTR RosterAddExecute;
		static LPCTSTR RosterEditExecute;
		static LPCTSTR RosterDeleteForm;
		static LPCTSTR RosterDeleteExecute;

		static LPCTSTR RosterDescriptionsSelectForm;
		static LPCTSTR RosterDescriptionsAddForm;
		static LPCTSTR RosterDescriptionsAddExecute;
		static LPCTSTR RosterDescriptionsEditForm;
		static LPCTSTR RosterDescriptionsEditExecute;

		static LPCTSTR RulesMenu;
		static LPCTSTR RulesAddExecute;
		static LPCTSTR RulesEditExecute;
		static LPCTSTR RulesSetTypesExecute;

		static LPCTSTR SecurityMenu;
		static LPCTSTR SecurityAssignLoginForm;
		static LPCTSTR SecurityAssignLoginExecute;
		static LPCTSTR SecurityGrantRoleForm;
		static LPCTSTR SecurityGrantRoleExecute;
		static LPCTSTR SecurityRevokeRoleForm;
		static LPCTSTR SecurityRevokeRoleExecute;
		static LPCTSTR SecurityRoleAllocatePermissionForm;
		static LPCTSTR SecurityRoleAllocatePermissionExecute;
		static LPCTSTR SecurityRoleEditForm;
		static LPCTSTR SecurityRoleEditExecute;
		static LPCTSTR SecurityRoleSelectForm;
		static LPCTSTR SecurityAssignSeriesForm;
		static LPCTSTR SecurityAssignSeriesExecute;

		static LPCTSTR SeriesMenu;
		static LPCTSTR SeriesMaintainMenu;
		static LPCTSTR SeriesSelectForm;
		static LPCTSTR SeriesAddForm;
		static LPCTSTR SeriesAddExecute;
		static LPCTSTR SeriesEditForm;
		static LPCTSTR SeriesEditExecute;
		static LPCTSTR SeriesSetFirstEventForm;
		static LPCTSTR SeriesSetFirstEventExecute;
		static LPCTSTR SeriesSetNextEventForm;
		static LPCTSTR SeriesSetNextEventExecute;

		static LPCTSTR UtilitiesMenu;
		static LPCTSTR UtilitiesSetEligibilitySelectGroupForm;
		static LPCTSTR UtilitiesSetEligibilityByGroupForm;
		static LPCTSTR UtilitiesSetEligibilityByGroupExecute;
		static LPCTSTR UtilitiesSplitDivisionForm;
		static LPCTSTR UtilitiesSplitDivisionExecute;
		static LPCTSTR UtilitiesSplitDivisionByAgeGroupForm;
		static LPCTSTR UtilitiesSplitDivisionByAgeGroupExecute;
		static LPCTSTR UtilitiesChangeSelectSeriesForm;
		static LPCTSTR UtilitiesChangeForm;
		static LPCTSTR UtilitiesChangeExecute;
		static LPCTSTR UtilitiesRebuildAgeGroupsForm;
		static LPCTSTR UtilitiesRebuildAgeGroupsExecute;
		static LPCTSTR UtilitiesFixDuplicatePersonForm;
		static LPCTSTR UtilitiesFixDuplicatePersonExecute;
		static LPCTSTR UtilitiesBulkAdjustForm;
		static LPCTSTR UtilitiesBulkAdjustExecute;
		static LPCTSTR UtilitiesDeleteResultsForm;
		static LPCTSTR UtilitiesDeleteResultsExecute;

		static LPCTSTR WorldStandardMenu;
		static LPCTSTR WorldStandardSelectForm;
		static LPCTSTR WorldStandardEditForm;
		static LPCTSTR WorldStandardEditExecute;

	private:

		// Member variables

};

#endif // !defined(AFX_PAGE_H__INCLUDED_)
