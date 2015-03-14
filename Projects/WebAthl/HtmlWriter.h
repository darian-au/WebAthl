#if !defined(AFX_HTMLWRITER_H__INCLUDED_)
#define AFX_HTMLWRITER_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HtmlWriter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlWriter

class CHtmlWriter : public CHttpServerVariableEx
{

	public:

		// Constructor
		CHtmlWriter( CHttpServerContext* pCtxt , CHttpServer* pSrv );

		// Destructor
		//~CHtmlWriter( );

		// Static functions

	private:

		// Member variables
		//CHttpServerProperties* m_pProp;

	public:

		// Member functions

		void StartForm(
			LPCTSTR szHeading,
			LPCTSTR szAction);

		void StartInLineForm(
			LPCTSTR szHeading,
			LPCTSTR szAction);

		void EndForm();

		void EndInLineForm();

		void RadioButton(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName,
			LPCTSTR szVarValue,
			LPCTSTR szButtonData);

		void TableHeader(
			LPCTSTR szTitle);

		void RulesHeader(
			LPCTSTR szLabel1,
			LPCTSTR szLabel2,
			LPCTSTR szLabel3,
			LPCTSTR szLabel4,
			LPCTSTR szLabel5,
			LPCTSTR szLabel6);

		void TableFooter();

		void RuleTypeSel(
			LPCTSTR szHiddenName,
			LPCTSTR szHiddenValue,
			LPCTSTR szRuleID,
			int nRuleID,
			LPCTSTR szVarName,
			int nVarValue,
			LPCTSTR szLabel);

		void RuleSubTypeSel(
			LPCTSTR sszVarName);

		void RuleSubmit(
			LPCTSTR szVarName,
			int     nVarValue,
			LPCTSTR szVarNameS1,
			LPCTSTR szVarNameS2);

		void GroupsTable(
			int    nGroupID, 
			double dGroupRate,
			double dGroupStart);

		void GroupsTableHeader(
			LPCTSTR szGroupID,
			LPCTSTR szGroupRate,
			LPCTSTR szGroupStart);

		void ResultsEntryTable(
			int nTimed,
			BOOL bPreEvent,
			int nDivision,
			int nPlace,
			int nPersonID,
			int nAgeGroup,
			int nPerfHOUR,
			int nPerfMIN,
			double dPerfSEC,
			int nGroupID,
			LPCTSTR szChestNo,
			int nPoints,
			int nNewGroupID,
			LPCTSTR szNewGroupMessage);

		void ResultsEntryTableHeader(
			BOOL bPreEvent,
			LPCTSTR szDivision,
			LPCTSTR szPlace,
			LPCTSTR szPerson,
			LPCTSTR szAgeGroup,
			LPCTSTR szPerformance,
			LPCTSTR szGroup,
			LPCTSTR szChestNumber,
			LPCTSTR szPoints,
			LPCTSTR szNewGroup,
			LPCTSTR szNewGroupMessage);

		void StandardTimeTable(
			LPCTSTR szAgeGroup,
			int   nVarValuepHOUR,
			int   nVarValuepMIN,
			double dVarValuepSEC,
			int   nVarFactName,
			double dVarFactValue);

		void StandardDistTable(
			LPCTSTR szAgeGroup,
			double nVarValuepSEC,
			int   nVarFactName,
			double dVarFactValue);

		void StandardTableHeader(
			LPCTSTR szAgeGroup,
			LPCTSTR szRecCategory,
			LPCTSTR szFactor);

		void RosterTable(
			LPCTSTR szLabel1,
			LPCTSTR szLabel2);

		void StartRoster(
			LPCTSTR szVarName);

		void EndRoster(
			LPCTSTR szLabel);


		void StartSelectBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName);

		void StartListBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int nHeight,
			BOOL bMultiple);

		void AddSelectBox(
  			LPCTSTR szLabel,
			LPCTSTR szVarValue,
			LPCTSTR szButtonData);

		void EndSelectBox();

		void CheckBox(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName,
			LPCTSTR szVarValue,
			LPCTSTR szButtonData);

		void TimeBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int   nVarValueHOUR,
			int   nVarValueMIN,
			double dVarValueSEC);

		void MonthBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int   nVarValueMONTH);

		void DateBox(LPCTSTR szTitle, LPCTSTR szVarName, long lDaysFromToday);

		void DateBox(LPCTSTR szTitle, LPCTSTR szVarName);

		void DateBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int   nVarValueDAY,
			int   nVarValueMONTH,
			int   nVarValueYEAR);

		void NonEditDateBox(
			LPCTSTR szTitle,
			int   nVarValueDAY,
			int   nVarValueMONTH,
			int   nVarValueYEAR);

		void SubmitButton(
			LPCTSTR szVarValue,
			int nColspan = 6);

		void ResetButton(int nColspan = 6);

		void HiddenFloat(
			LPCTSTR szVarName,
			double dVarValue);

		void HiddenInt(
			LPCTSTR szVarName,
			int   nVarValue);

		void HiddenText(
			LPCTSTR szVarName,
			LPCTSTR szVarValue);

		void PasswordBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			LPCTSTR szVarValue);

		void EditTextBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			LPCTSTR szVarValue, 
			int nSize);

		void EditTextBoxLarge(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			LPCTSTR szVarValue);

		void EditTextBoxSmall(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			LPCTSTR szVarValue);

		void EditIntBox(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int   nVarValue);

		void EditFloatBox(
			LPCTSTR szTitle,
			LPCTSTR szvarName,
			double dVarValue);

		void NonEditText(
			LPCTSTR szTitle,
			LPCTSTR szVarValue);

		void NonEditInt(
			LPCTSTR szTitle,
			int   nVarValue);

		void NonEditFloat(
			LPCTSTR szTitle,
			double dVarValue);


		void WritePageTitle(
			LPCTSTR szAddOn = "");

		void WritePageMenu(
			LPCTSTR szMenu,
			LPCTSTR szHeading);

		void WritePageMenuItem(
			LPCTSTR szLink,
			LPCTSTR szName,
			int nInitNum,
			...);

		void EndMenu();

		void EndPage();

		void HtmlTable(CStringArray* strColumn);
		void HtmlTable(CStringArray* strColumn, int nAlign);

		void HorizontalRule(int nColspan = 6);
		void EmptyHorizontalRule(int nColspan = 6);

		void HeadingHRule(
			int nColspan,
			LPCTSTR szTitle);

		void TextArea(
			LPCTSTR szTitle,
			LPCTSTR szVarName,
			int nRows,
			int nCols,
			LPCTSTR szVarValue = "");

		void HRuleAlign(
			int nCols,
			int nColspan,
			BOOL bLeftalign);

		void MultiFormHeader(
			LPCTSTR szTitle,
			LPCTSTR szComment);

		void MultiFormCheckBox(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName,
			LPCTSTR szVarValue,
			LPCTSTR szButtonData,
			LPCTSTR szComment);

		void MultiFormRadioButton(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName,
			LPCTSTR szVarValue,
			LPCTSTR szButtonData);

		void MultiFormStartSelectBox(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName);

		void MultiFormEditIntBox(
			LPCTSTR szTitle,
			LPCTSTR szLabel,
			LPCTSTR szVarName,
			int   nVarValue);

		void MultiFormComment(
			LPCTSTR szComment);

		CString InLineInput(
			LPCTSTR szType,
			LPCTSTR szVarName,
			LPCTSTR szVarValue,
			int		nSize,
			LPCTSTR szButtonData);

		int SelectEventBox( 
			LPCTSTR szTitle, 
			LPCTSTR szVarName,
			CRecordset* rs,
			int iSelectedEventID,
			LPCTSTR szIncludeNone);
			// If iSelectedEventID < 0 :
			// Assume that EventNo order by Descending, and
			// that EventNo is in Date Order. Then pick the first event
			// that has a date less than or equal to todays date.

		int SelectSeriesBox( 
			LPCTSTR szTitle, 
			LPCTSTR szVarName,
			CRecordset* rs,
			int iSelectedSeriesID,
			LPCTSTR szIncludeNone);

		int SelectPersonBox( 
			LPCTSTR szTitle, 
			LPCTSTR szVarName,
			CRecordset* rs,
			int iSelectedPersonID,
			LPCTSTR szIncludeNone);

		CString GetSelectEventBoxDetails(
			int iSeriesID,
			int iMinimumEventID,
			int iOrderDescending);

		CString GetSelectEventBoxDetails(
			int iSeriesID,
			int iMinimumEventID,
			int iOrderDescending,
			int iOpenPreEntry);

		void NonEditEvent( 
			LPCTSTR szTitle, 
			int nEventNo,
			LPCTSTR szLocationDescription,
			LPCTSTR szEventDescription);

		CString GetNonEditEventBoxDetails(
			int iEventID);

		void ODBCSetupForm(LPCTSTR szPostTo);

		CString GetMFCIsapiCommand(LPCTSTR szAction);
		CString GetAction(LPCTSTR szAction);

		void DefaultPage(LPCTSTR szButton, LPCTSTR szAction);

		};

#endif // !defined(AFX_HTMLWRITER_H__INCLUDED_)
