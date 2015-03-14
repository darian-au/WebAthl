#if !defined(AFX_WEBATHLEXTENSION_H__INCLUDED_)
#define AFX_WEBATHLEXTENSION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CWebAthlExtension.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWebAthlExtension

class CWebAthlExtension : public CHttpServer
{
protected:

	// Static variables
	static TCHAR chIsapiDelimiter;

private:

	//CString m_strQuery;
	//CString m_strCommand;

public:

	CWebAthlExtension();
	//~CWebAthlExtension();

	BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	
	CString CallStatus( int nStatus );

	//PRB: Parse Maps Do Not Handle Multi-select List Boxes
	//ID: Q169109 
	virtual int CallFunction(CHttpServerContext* pCtxt, 
		LPTSTR pszQuery, LPTSTR pszCommand);

	// TODO: Add handlers for your commands here.
	// For example:

	//DumpVars web Page.
	void Dump(CHttpServerContext* pCtxt);

///////////////////////////////////////////////////////////////////////
// Person

	void PersonMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void PersonAddForm(CHttpServerContext* pCtxt,
		LPTSTR szInit,
		LPTSTR szSubmit);
	void PersonAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szInit,
		LPTSTR szPersonID,
		LPTSTR szLastName,
		LPTSTR szFirstName,
		LPTSTR szMiddleName,
		LPTSTR szAddress1,
		LPTSTR szAddress2,
		LPTSTR szTown,
		LPTSTR szState,
		LPTSTR szCountry,
		LPTSTR szPostCode,
		LPTSTR szPhoneHm,
		LPTSTR szPhoneWk,
		LPTSTR szFax,
		LPTSTR szMobile,
		LPTSTR szEmail,
		LPTSTR szDobDAY,
		LPTSTR szDobMONTH,
		LPTSTR szDobYEAR,
		LPTSTR szSex,
		LPTSTR szContactPersonID,
  		LPTSTR szSubmit);

	void PersonViewForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

	void PersonEditForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void PersonEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szLastName,
		LPTSTR szFirstName,
		LPTSTR szMiddleName,
		LPTSTR szAddress1,
		LPTSTR szAddress2,
		LPTSTR szTown,
		LPTSTR szState,
		LPTSTR szPostCode,
		LPTSTR szCountry,
		LPTSTR szPhoneHm,
		LPTSTR szPhoneWk,
		LPTSTR szFax,
		LPTSTR szMobile,
		LPTSTR szEmail,
		LPTSTR szDobDAY,
		LPTSTR szDobMONTH,
		LPTSTR szDobYEAR,
		LPTSTR szSex,
		LPTSTR szContactPersonID,
  		LPTSTR szSubmit);

	void PersonCommentEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szCommentNo,
		LPTSTR szType,
		LPTSTR szComment,
		LPTSTR szSubmit);
	void PersonCommentAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szInit, 
		LPTSTR szSubmit);

	void SearchPersonForm(CHttpServerContext* pCtxt,
		LPTSTR szInit,
		LPTSTR szInit1,
		LPTSTR szInit2,
		LPTSTR szSubmit);
	void SearchPersonSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szInit,
		LPTSTR szDuplicate,
		LPTSTR szPersonID,
		LPTSTR szLastName,
		LPTSTR szFirstName,
		LPTSTR szMiddleName,
		LPTSTR szAddress1,
		LPTSTR szAddress2,
		LPTSTR szTown,
		LPTSTR szState,
		LPTSTR szCountry,
		LPTSTR szPostCode,
		LPTSTR szPhoneHm,
		LPTSTR szPhoneWk,
		LPTSTR szFax,
		LPTSTR szMobile,
		LPTSTR szEmail,
		LPTSTR szDobDAY,
		LPTSTR szDobMONTH,
		LPTSTR szDobYEAR,
		LPTSTR szSex,
		LPTSTR szContactPersonID,
  		LPTSTR szSubmit);

	void PersonChangePasswordForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void PersonChangePasswordExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szOldPassword,
		LPTSTR szNewPassword,
		LPTSTR szConfirmPassword,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Organisation

	void OrganisationMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void OrganisationAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OrganisationAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szOrgID,
		LPTSTR szOrgName,
		LPTSTR szAddress1,
		LPTSTR szAddress2,
		LPTSTR szTown,
		LPTSTR szState,
		LPTSTR szCountry,
		LPTSTR szPostCode,
		LPTSTR szPhone,
		LPTSTR szFax,
		LPTSTR szMobile,
		LPTSTR szEmail,
		LPTSTR szURL,
		LPTSTR szRegistrarPersonID,
		LPTSTR szAdministratorPersonID,
		LPTSTR szSubmit);

	void OrganisationSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void OrganisationViewForm(CHttpServerContext* pCtxt,
		LPTSTR szOrgID,
		LPTSTR szSubmit);

	void OrganisationEditForm(CHttpServerContext* pCtxt,
		LPTSTR szOrgID,
		LPTSTR szSubmit);
	void OrganisationEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szOrgID,
		LPTSTR szOrgName,
		LPTSTR szAddress1,
		LPTSTR szAddress2,
		LPTSTR szTown,
		LPTSTR szState,
		LPTSTR szCountry,
		LPTSTR szPostCode,
		LPTSTR szPhone,
		LPTSTR szFax,
		LPTSTR szMobile,
		LPTSTR szEmail,
		LPTSTR szURL,
		LPTSTR szRegistrarPersonID,
		LPTSTR szAdministratorPersonID,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Security

	void SecurityMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void SecurityRoleSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void SecurityRoleEditForm(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szSubmit);
	void SecurityRoleEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szRoleName,
		LPTSTR szSubmit);

	void SecurityRoleAllocatePermissionForm(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szSubmit);
	void SecurityRoleAllocatePermissionExecute(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szPermission,
		LPTSTR szSubmit);

	void SecurityAssignLoginForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void SecurityAssignLoginExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szLoginName,
		LPTSTR szPassword,
		LPTSTR szConfirmPassword,
		LPTSTR szSubmit);

	void SecurityGrantRoleForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void SecurityGrantRoleExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szRoleID,
		LPTSTR szSubmit);

	void SecurityRevokeRoleForm(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szSubmit);
	void SecurityRevokeRoleExecute(CHttpServerContext* pCtxt,
		LPTSTR szRoleID,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

	void SecurityAssignSeriesForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void SecurityAssignSeriesExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Series

	void SeriesMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void SeriesMaintainMenu(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void SeriesAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void SeriesAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSeriesDescription,
//		LPTSTR szHandicapped,
//		LPTSTR szAgeCategory,
		LPTSTR szSubmit);

	void SeriesSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit,
		LPTSTR szInit1,
		LPTSTR szInit2);
	void SeriesEditForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void SeriesEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSeriesDescription,
//		LPTSTR szHandicapped,
//		LPTSTR szAgeCategory,
		LPTSTR szSubmit);

	void SeriesSetFirstEventForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void SeriesSetFirstEventExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szEventsInSeason,
		LPTSTR szSubmit);

	void SeriesSetNextEventForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void SeriesSetNextEventExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Groups

	void GroupsEditSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void GroupsEditForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szGroups,
		LPTSTR szEventTypeID,
		LPTSTR szSubmit);

	void GroupsEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventTypeID,
		LPTSTR szGroups,
		LPTSTR szGroupRateList,
		LPTSTR szGroupStartList,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Rules

	void RulesMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void RulesEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szRuleID,
		LPTSTR szRuleTypeID,
		LPTSTR szRuleSubTypeID,
		LPTSTR szLaw,
		LPTSTR szSubmit);

	void RulesAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szInit,
		LPTSTR szSubmit);

	void RulesSetTypesExecute(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// EventType

	//void EventTypeMenu(CHttpServerContext* pCtxt,
	//	LPTSTR szSubmit);

	void EventTypeSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void EventTypeAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void EventTypeAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventTypeID,
		LPTSTR szEventDescription,
		LPTSTR szTimed,
		LPTSTR szEventLength,
		LPTSTR szSubmit);

	void EventTypeEditForm(CHttpServerContext* pCtxt,
		LPTSTR szEventTypeID,
		LPTSTR szSubmit);
	void EventTypeEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventTypeID,
		LPTSTR szEventDescription,
		LPTSTR szTimed,
		LPTSTR szEventLength,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// RegistrationType

	//void RegistrationTypeMenu(CHttpServerContext* pCtxt,
	//	LPTSTR szSubmit);

	void RegistrationTypeSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void RegistrationTypeEditForm(CHttpServerContext* pCtxt,
		LPTSTR szRegistrationTypeID,
		LPTSTR szSubmit);
	void RegistrationTypeEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szRegistrationTypeID,
		LPTSTR szRegistrationDescription,
		LPTSTR szMonthStart,
		LPTSTR szMonthStop,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Location

	//void LocationMenu(CHttpServerContext* pCtxt,
	//	LPTSTR szSubmit);

	void LocationSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void LocationAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void LocationAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szLocationID,
		LPTSTR szLocationDescription,
		LPTSTR szSubmit);

	void LocationEditForm(CHttpServerContext* pCtxt,
		LPTSTR szLocationID,
		LPTSTR szSubmit);
	void LocationEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szLocationID,
		LPTSTR szLocationDescription,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Event

	void EventAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void EventAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventID,
		LPTSTR szSeriesID,
		LPTSTR szDateDAY,
		LPTSTR szDateMONTH,
		LPTSTR szDateYEAR,
		LPTSTR szDateAgeDAY,
		LPTSTR szDateAgeMONTH,
		LPTSTR szDateAgeYEAR,
		LPTSTR szEventNo,
		LPTSTR szLocationID,
		LPTSTR szEventTypeID,
		LPTSTR szPreEntryOpen,
		LPTSTR szSubmit);

	void EventSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void EventEditForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);
	void EventEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventID,
		LPTSTR szSeriesID,
		LPTSTR szDateDAY,
		LPTSTR szDateMONTH,
		LPTSTR szDateYEAR,
		LPTSTR szDateAgeDAY,
		LPTSTR szDateAgeMONTH,
		LPTSTR szDateAgeYEAR,
		LPTSTR szEventNo,
		LPTSTR szLocationID,
		LPTSTR szEventTypeID,
		LPTSTR szPreEntryOpen,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Roster Descriptions

	void RosterDescriptionsSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);

	void RosterDescriptionsAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void RosterDescriptionsAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szTaskID,
		LPTSTR szTaskDescription,
		LPTSTR szSubmit);

	void RosterDescriptionsEditForm(CHttpServerContext* pCtxt,
		LPTSTR szLocationID,
		LPTSTR szSubmit);
	void RosterDescriptionsEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szTaskID,
		LPTSTR szTaskDescription,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Roster

	void RosterMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void RosterSelectEventForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void RosterMaintainMenu(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);

	void RosterAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

	void RosterEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventID,
		LPTSTR szSeriesID,
		LPTSTR szTaskIDList,
		LPTSTR szPersonIDList,
		LPTSTR szSubmit);

	void RosterDeleteForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void RosterDeleteExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventID,
		LPTSTR szSeriesID,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Results

	void ResultsEntryPrePostMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void ResultsEntrySelectEventForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void ResultsEntryMenu(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);
	void ResultsEntryAddForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void ResultsEntryAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szPersonID,
		LPTSTR szGrossPerformanceHOUR,
		LPTSTR szGrossPerformanceMIN,
		LPTSTR szGrossPerformanceSEC,
		LPTSTR szPlace,
		LPTSTR szGroupID,
		LPTSTR szDivision,
	    LPTSTR szAgeGroup,
		LPTSTR szChestNumber,
		LPTSTR szPoints,
		LPTSTR szNewGroupID,
		LPTSTR szNewGroupMessage,
		LPTSTR szSubmit);

	void ResultsEntryEditForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void ResultsEntryEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szPersonID,
		LPTSTR szGrossPerformanceHOUR,
		LPTSTR szGrossPerformanceMIN,
		LPTSTR szGrossPerformanceSEC,
		LPTSTR szPlace,
		LPTSTR szGroupID,
		LPTSTR szDivision,
	    LPTSTR szAgeGroup,
		LPTSTR szChestNumber,
		LPTSTR szPoints,
		LPTSTR szNewGroupID,
		LPTSTR szNewGroupMessage,
		LPTSTR szSubmit);

	void ResultsEntryReportForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

//	void ResultsEntrySelectDivisionForm(CHttpServerContext* pCtxt,
//		LPTSTR szSubmit,
//		LPTSTR szInit);

	void ResultsEntryQuickAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void ResultsEntryQuickAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szDivisionList,
		LPTSTR szPlaceList,
		LPTSTR szPersonIDList,
		LPTSTR szAgeGroupList,
		LPTSTR szPerformanceHOURList,
		LPTSTR szPerformanceMINList,
		LPTSTR szPerformanceSECList,
		LPTSTR szGroupIDList,
		LPTSTR szChestNumberList,
		LPTSTR szPointsList,
		LPTSTR szNewGroupIDList,
		LPTSTR szNewGroupMessageList,
		LPTSTR szSubmit);

	void ResultsEntryBulkAddForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
//	void bulkEntry(CHttpServerContext* pCtxt, 
//		void* pVoid, 
//		DWORD dwBytes);

	void ResultsEntryBulkAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szBulkResults,
		LPTSTR szSubmit);

	void ResultsEntryDeleteForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// World Standard

	void WorldStandardMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void WorldStandardSelectForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void WorldStandardEditForm(CHttpServerContext* pCtxt,
		LPTSTR szEventTypeID,
		LPTSTR szAgeCategory,
		LPTSTR szRecCategory,
		LPTSTR szSex,
		LPTSTR szSubmit);

	void WorldStandardEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventTypeID,
		LPTSTR szAgeCategory,
		LPTSTR szRecCategory,
		LPTSTR szSex,
		LPTSTR szAgeGroupList,
		LPTSTR szPerformanceHOURList,
		LPTSTR szPerformanceMINList,
		LPTSTR szPerformanceSECList,
		LPTSTR szFactorList,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Financial

	void FinancialMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void FinancialAddForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void FinancialAddExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szDateRenewedDAY,
		LPTSTR szDateRenewedMONTH,
		LPTSTR szDateRenewedYEAR,
		LPTSTR szMailListFlag,
		LPTSTR szRegistrationTypeID,
		LPTSTR szOrgID,
		LPTSTR szYear,
		LPTSTR szRegistrationID,
		LPTSTR szSubmit);

	void FinancialEditForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void FinancialEditExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szMailListFlag,
		LPTSTR szRegistrationTypeID,
		LPTSTR szOldRegTypeID,
		LPTSTR szOrgID,
		LPTSTR szYear,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Processing

	void ProcessingForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	
	void ProcessingExecute(CHttpServerContext* pCtxt,
		LPTSTR szDwProc,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Utilities

	void UtilitiesMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void UtilitiesChangeSelectSeriesForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);
	void UtilitiesChangeForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesChangeExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSeriesID,
		LPTSTR szGroupIDSupposedTo,
		LPTSTR szDivisionSupposedTo,
		LPTSTR szNewGroupMessage,
		LPTSTR szEligibilityForEvent,
		LPTSTR szSubmit);

	void UtilitiesSetEligibilitySelectGroupForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesSetEligibilityByGroupForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szGroupIDFrom,
		LPTSTR szGroupIDTo,
		LPTSTR szShowParticipants,
		LPTSTR szSubmit);
	void UtilitiesSetEligibilityByGroupExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szGroupIDFrom,
		LPTSTR szGroupIDTo,
		LPTSTR szEligibile,
		LPTSTR szSubmit);

	void UtilitiesBulkAdjustForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesBulkAdjustExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szLowGroup,
		LPTSTR szHighGroup,
		LPTSTR szMultiplier,
		LPTSTR szNewGroupMessage,
		LPTSTR szSubmit);

	void UtilitiesSplitDivisionForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesSplitDivisionExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szLowGroup,
		LPTSTR szHighGroup,
		LPTSTR szDivision,
		LPTSTR szSubmit);

	void UtilitiesSplitDivisionByAgeGroupForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesSplitDivisionByAgeGroupExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szLowGroup,
		LPTSTR szHighGroup,
		LPTSTR szSpecifySex,
		LPTSTR szSex,
		LPTSTR szDivision,
		LPTSTR szSubmit);

	void UtilitiesDeleteResultsForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesDeleteResultsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);

	void UtilitiesFixDuplicatePersonForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szDupPersonID,
		LPTSTR szSubmit);
	void UtilitiesFixDuplicatePersonExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szDupPersonID,
		LPTSTR szDuplicatePerson,
		LPTSTR szLastName,
		LPTSTR szFirstName,
		LPTSTR szOnError,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void UtilitiesRebuildAgeGroupsForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void UtilitiesRebuildAgeGroupsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szResults,
		LPTSTR szDoPreResults,
		LPTSTR szDoPostResults,
		LPTSTR szSubmit);

	void AgeGroupsRebuild(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp,
		LPCTSTR szResultsTable,
		int iSeriesID);

///////////////////////////////////////////////////////////////////////
// Reports

	void ReportsMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void ReportsClubRecordsForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsClubRecordsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSexMale,
		LPTSTR szSexFemale,
		LPTSTR szUseAgeGroup,
		LPTSTR szAgeGroup,
		LPTSTR szOrderByLocation,
		LPTSTR szOrderByEventDescription,
		LPTSTR szOrderByDate,
		LPTSTR szOrderByAgeGroup,
		LPTSTR szOrderBySex,
		LPTSTR szOrderByNameDesc,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsParticipantHistoryForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

	void ReportsParticipantHistoryExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSeriesID,
		LPTSTR szOrderBy,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsFinancialHistoryForm(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szSubmit);

	void ReportsFinancialHistoryExecute(CHttpServerContext* pCtxt,
		LPTSTR szPersonID,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsEventTallyForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsEventTallyExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesIDList,
		LPTSTR szTallyTop,
		LPTSTR szTallyBot,
		LPTSTR szUseAllEvents,
		LPTSTR szEventDateFromDAY,
		LPTSTR szEventDateFromMONTH,
		LPTSTR szEventDateFromYEAR,
		LPTSTR szEventDateToDAY,
		LPTSTR szEventDateToMONTH,
		LPTSTR szEventDateToYEAR,
		LPTSTR szSubmit);

	void ReportsResultsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szOrderByDivision,
		LPTSTR szOption,
		LPTSTR szSubmit);
	void ReportsResultsForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void ReportsGroupsListExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szEventsMin,
		LPTSTR szEligible,
		LPTSTR szDivision,
		LPTSTR szGroup,
		LPTSTR szSex,
		LPTSTR szAgeGroup,
		LPTSTR szPoints,
		LPTSTR szNameDesc,
		LPTSTR szOption,
		LPTSTR szSubmit);
	void ReportsGroupsListForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
/*
	void ReportsEligibilityExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szSubmit);
	void ReportsEligibilityForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
*/
	void ReportsRosterExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventID,
		LPTSTR szOrderByTask,
		LPTSTR szNameDesc,
		LPTSTR szOption,
		LPTSTR szSubmit);
	void ReportsRosterForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void ReportsPersonForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsPersonExecute(CHttpServerContext* pCtxt,
		LPTSTR szFinancial,
		LPTSTR szOptFinancial,
		LPTSTR szOptFinancialYear,
		LPTSTR szRegistrationType,
		LPTSTR szOptRegTypeID,
		LPTSTR szSeries,
		LPTSTR szOptSeriesID,
		LPTSTR szAgeGroup,
		LPTSTR szOptAgeGroup,
		LPTSTR szBirthday,
		LPTSTR szOptMonth,
		LPTSTR szMailList,
		LPTSTR szOptMailList,
		LPTSTR szOrganisation,
		LPTSTR szOptOrgID,
		LPTSTR szComments,
		LPTSTR szOptPersonCommentsType,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsRulesExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);

	void ReportsAwardsForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsAwardsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventsMin,
		LPTSTR szOrganisation,
		LPTSTR szDivision,
		LPTSTR szSex,
		LPTSTR szAgeGroup,
		LPTSTR szOrderBy,
		LPTSTR szDesc,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsCustomForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsCustomExecute(CHttpServerContext* pCtxt,
		LPTSTR szCustomQuery,
		LPTSTR szSubmit);

	void ReportsAgeGroupRankingForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szLocationID,
		LPTSTR szEventTypeID,
		LPTSTR szSubmit);
	void ReportsAgeGroupRankingExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szLocationID,
		LPTSTR szEventTypeID,
		LPTSTR szSubmit);

	void ReportsSeriesStatisticsForm(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szSubmit);
	void ReportsSeriesStatisticsExecute(CHttpServerContext* pCtxt,
		LPTSTR szSeriesID,
		LPTSTR szEventIDFrom,
		LPTSTR szEventIDTo,
		LPTSTR szSubmit);

	void ReportsResultsBySeriesForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsResultsBySeriesExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventDateFromDAY,
		LPTSTR szEventDateFromMONTH,
		LPTSTR szEventDateFromYEAR,
		LPTSTR szEventDateToDAY,
		LPTSTR szEventDateToMONTH,
		LPTSTR szEventDateToYEAR,
		LPTSTR szSeriesIDList,
		LPTSTR szOrderByDivision,
		LPTSTR szOption,
		LPTSTR szSubmit);

	void ReportsEventCalendarForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void ReportsEventCalendarExecute(CHttpServerContext* pCtxt,
		LPTSTR szEventDateFromDAY,
		LPTSTR szEventDateFromMONTH,
		LPTSTR szEventDateFromYEAR,
		LPTSTR szEventDateToDAY,
		LPTSTR szEventDateToMONTH,
		LPTSTR szEventDateToYEAR,
		LPTSTR szSeriesID, 
		LPTSTR szLocationID, 
		LPTSTR szEventTypeID,
		LPTSTR szOrderByEventDate,
		LPTSTR szOrderDescending,
		LPTSTR szOrderBySeries,
		LPTSTR szOrderByEventNo,
		LPTSTR szOrderByLocation,
		LPTSTR szOrderByEventType,
		LPTSTR szOption,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Options

	void OptionsMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void OptionsODBCSetupForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void OptionsAgeGroupsForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OptionsAgeGroupsExecute(CHttpServerContext* pCtxt,
		LPTSTR szMaxJunior,
		LPTSTR szJuniorGroup,
		LPTSTR szMinVeteran,
		LPTSTR szVeteranGroup,
		LPTSTR szNullDoB, 
		LPTSTR szSubmit);

	void OptionsProcessingForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OptionsProcessingExecute(CHttpServerContext* pCtxt,
		LPTSTR szTimeOut,
		LPTSTR szSubmit);

	void OptionsAppearanceForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OptionsAppearanceExecute(CHttpServerContext* pCtxt,
		LPTSTR szStyleSheet,
		LPTSTR szFont,
		LPTSTR szBackgroundColor,
		LPTSTR szMenuColor,
		LPTSTR szBackgroundImage,
		LPTSTR szMenuImage,
		LPTSTR szLogo,
		LPTSTR szSubmit);
	
	void OptionsCryptographyForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OptionsCryptographyExecute(CHttpServerContext* pCtxt,
		LPTSTR szEnabled,
		LPTSTR szSubmit);

	void OptionsNavigationForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void OptionsNavigationExecute(CHttpServerContext* pCtxt,
		LPTSTR szExitURL,
		LPTSTR szSubmit);

	void OptionsPersonSearchForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void OptionsPersonSearchExecute(CHttpServerContext* pCtxt,
		LPTSTR szLastName,
		LPTSTR szFirstName,
		LPTSTR szMiddleName,
		LPTSTR szDateOfBirth,
		LPTSTR szSex,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Maintenance

	void MaintenanceMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

	void CreateTablesExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp,
		DWORD dwTable);
	void CreateViewsExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp,
		DWORD dwView);
	//void CreateStoredProceduresExecute(CHtmlWriter* pHtml,
	//	CHttpServerProperties* pProp,
	//	DWORD dwStoredProcedure);

	void CreateForeignKeysExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp,
		DWORD dwCreate,
		DWORD dwTable);

	void BulkCopyExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp,
		DWORD dwImport,
		DWORD dwTable);

	void MaintenanceSetFolderForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void MaintenanceSetFolderExecute(CHttpServerContext* pCtxt,
		LPTSTR szBackupFolder,
		LPTSTR szSubmit);

	void EncryptPasswordsExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp);
	void DecryptPasswordsExecute(CHtmlWriter* pHtml,
		CHttpServerProperties* pProp);

	void MaintenanceCryptPasswordsForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void MaintenanceCryptPasswordsExecute(CHttpServerContext* pCtxt,
		LPTSTR szDecrypt,
		LPTSTR szSubmit);

	void MaintenanceDisableUsersForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void MaintenanceDisableUsersExecute(CHttpServerContext* pCtxt,
		LPTSTR szEnabled,
		LPTSTR szSubmit);

	void MaintenanceMaintainDatabaseForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit,
		LPTSTR szInit);
	void MaintenanceMaintainDatabaseExecute(CHttpServerContext* pCtxt,
		LPTSTR szItemList,
		LPTSTR szItems,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Login

	void DefaultLoginForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void DefaultLoginExecute(CHttpServerContext* pCtxt,
		LPTSTR szLoginName,
		LPTSTR szPassword,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Entry Menu

	void DefaultEntry(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Start Menu

	void DefaultMenu(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// Default Page

	void Default(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void DefaultODBCSetupForm(CHttpServerContext* pCtxt,
		LPTSTR szSubmit);
	void DefaultODBCSetupExecute(CHttpServerContext* pCtxt,
		LPTSTR szURL,
		LPTSTR szServer,
		LPTSTR szUID,
		LPTSTR szPWD,
		LPTSTR szDatabase,
		LPTSTR szDriver,
		LPTSTR szDSN,
		LPTSTR szSubmit);

///////////////////////////////////////////////////////////////////////
// License

	void LicenseForm(CHttpServerContext* pCtxt, 
		LPTSTR szSubmit);
 	void LicenseExecute(CHttpServerContext* pCtxt,
		LPTSTR szRegNo,
		LPTSTR szRegName,
		LPTSTR szRegKey,
		LPTSTR szSubmit);


	DECLARE_PARSE_MAP()
};

#endif // !defined(AFX_WEBATHLEXTENSION_H__INCLUDED_)