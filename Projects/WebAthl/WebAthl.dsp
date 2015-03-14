# Microsoft Developer Studio Project File - Name="WebAthl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WebAthl - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WebAthl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WebAthl.mak" CFG="WebAthl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WebAthl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WebAthl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WebAthl - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 advapi32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build
InputPath=.\Release\WebAthl.dll
SOURCE="$(InputPath)"

"build\build.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	build\build.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "WebAthl - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 advapi32.lib /nologo /subsystem:windows /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "WebAthl - Win32 Release"
# Name "WebAthl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "RecordSets Source"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\AgeGroupRankingSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AgeGroupSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BoolResultSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ClubRecordsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsistencyAgeGroupSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CountItemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CountResultSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DupPersonSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventETypLocSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventTallySet.cpp
# End Source File
# Begin Source File

SOURCE=.\EventTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\FinancialRegistrationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\FinancialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupsReportSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\IntegerSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OrganisationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticipantDetailsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticipantForSeriesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticipantHistorySet.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonCommentsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonFinancialCommentsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonFinancialSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonParticipantForSeriesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PostResultsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\PreResultsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\QuickReportSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistrationTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsEventTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsOrgSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsParticipantForSeriesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsPostResultsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsWorldStandardSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterDescriptionsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterNamesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RulesJoinSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RulesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleSubTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleTypeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SecurityPersonSeriesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SecurityPersonSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SecurityRoleSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesPersonPFSOrgSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesSeasonSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesStatisticsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StringSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ValidateSet.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldStandardSet.cpp
# End Source File
# End Group
# Begin Group "Web"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\Default.cpp
# End Source File
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\EventType.cpp
# End Source File
# Begin Source File

SOURCE=.\Financial.cpp
# End Source File
# Begin Source File

SOURCE=.\Groups.cpp
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\Location.cpp
# End Source File
# Begin Source File

SOURCE=.\Maintenance.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\Organisation.cpp
# End Source File
# Begin Source File

SOURCE=.\Person.cpp
# End Source File
# Begin Source File

SOURCE=.\Processing.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistrationType.cpp
# End Source File
# Begin Source File

SOURCE=.\Reports.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\Roster.cpp
# End Source File
# Begin Source File

SOURCE=.\RosterDescriptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Rules.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchPerson.cpp
# End Source File
# Begin Source File

SOURCE=.\Security.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\Series.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldStandard.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Authenticator.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\BitMaskEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\BulkCopy.cpp
# End Source File
# Begin Source File

SOURCE=.\Calculate.cpp
# End Source File
# Begin Source File

SOURCE=.\Convert.cpp
# End Source File
# Begin Source File

SOURCE=.\Crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\CryptByteArray.cpp
# End Source File
# Begin Source File

SOURCE=.\CSV.cpp
# End Source File
# Begin Source File

SOURCE=.\DBForeignKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DBView.cpp
# End Source File
# Begin Source File

SOURCE=.\FixDuplicateOption.cpp
# End Source File
# Begin Source File

SOURCE=.\Format.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlKey.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlMonth.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\HttpServerProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\HttpServerVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\HttpServerVariableEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MaintainDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\MIMECode.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\Page.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonSearcher.cpp
# End Source File
# Begin Source File

SOURCE=.\Process.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\Processor.cpp
# End Source File
# Begin Source File

SOURCE=.\Properties.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordsetEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportAwardsOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportClubRecordsOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEventCalendarOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportFinancialHistoryOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportGroupsListOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportParticipantHistoryOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportPersonOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportResultsBySeriesOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportResultsOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportRosterOption.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleSubType.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleType.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\StringLine.cpp
# End Source File
# Begin Source File

SOURCE=.\StringStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Util.cpp
# End Source File
# Begin Source File

SOURCE=.\WebAthl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "RecordSets Header"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\AgeGroupRankingSet.h
# End Source File
# Begin Source File

SOURCE=.\AgeGroupSet.h
# End Source File
# Begin Source File

SOURCE=.\BoolResultSet.h
# End Source File
# Begin Source File

SOURCE=.\ClubRecordsSet.h
# End Source File
# Begin Source File

SOURCE=.\ConsistencyAgeGroupSet.h
# End Source File
# Begin Source File

SOURCE=.\CountItemSet.h
# End Source File
# Begin Source File

SOURCE=.\CountResultSet.h
# End Source File
# Begin Source File

SOURCE=.\CountRules.h
# End Source File
# Begin Source File

SOURCE=.\DoubleSet.h
# End Source File
# Begin Source File

SOURCE=.\DupPersonSet.h
# End Source File
# Begin Source File

SOURCE=.\EventETypLocSet.h
# End Source File
# Begin Source File

SOURCE=.\EventRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\EventSet.h
# End Source File
# Begin Source File

SOURCE=.\EventTallySet.h
# End Source File
# Begin Source File

SOURCE=.\EventTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\FinancialRegistrationSet.h
# End Source File
# Begin Source File

SOURCE=.\FinancialSet.h
# End Source File
# Begin Source File

SOURCE=.\GroupsReportSet.h
# End Source File
# Begin Source File

SOURCE=.\GroupsSet.h
# End Source File
# Begin Source File

SOURCE=.\IntegerSet.h
# End Source File
# Begin Source File

SOURCE=.\LocationSet.h
# End Source File
# Begin Source File

SOURCE=.\OrganisationSet.h
# End Source File
# Begin Source File

SOURCE=.\ParticipantDetailsSet.h
# End Source File
# Begin Source File

SOURCE=.\ParticipantForSeriesSet.h
# End Source File
# Begin Source File

SOURCE=.\ParticipantHistorySet.h
# End Source File
# Begin Source File

SOURCE=.\PersonCommentsSet.h
# End Source File
# Begin Source File

SOURCE=.\PersonFinancialCommentsSet.h
# End Source File
# Begin Source File

SOURCE=.\PersonFinancialSet.h
# End Source File
# Begin Source File

SOURCE=.\PersonParticipantForSeriesSet.h
# End Source File
# Begin Source File

SOURCE=.\PersonSet.h
# End Source File
# Begin Source File

SOURCE=.\PostResultsSet.h
# End Source File
# Begin Source File

SOURCE=.\PreResultsSet.h
# End Source File
# Begin Source File

SOURCE=.\QuickReportSet.h
# End Source File
# Begin Source File

SOURCE=.\RegistrationTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsEventTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsOrgSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsParticipantForSeriesSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsPostResultsSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsSet.h
# End Source File
# Begin Source File

SOURCE=.\ResultsWorldStandardSet.h
# End Source File
# Begin Source File

SOURCE=.\RosterDescriptionsSet.h
# End Source File
# Begin Source File

SOURCE=.\RosterNamesSet.h
# End Source File
# Begin Source File

SOURCE=.\RosterSet.h
# End Source File
# Begin Source File

SOURCE=.\RulesJoinSet.h
# End Source File
# Begin Source File

SOURCE=.\RulesSet.h
# End Source File
# Begin Source File

SOURCE=.\RuleSubTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\RuleTypeSet.h
# End Source File
# Begin Source File

SOURCE=.\SecurityPersonSeriesSet.h
# End Source File
# Begin Source File

SOURCE=.\SecurityPersonSet.h
# End Source File
# Begin Source File

SOURCE=.\SecurityRoleSet.h
# End Source File
# Begin Source File

SOURCE=.\SeriesPersonPFSOrgSet.h
# End Source File
# Begin Source File

SOURCE=.\SeriesSeasonSet.h
# End Source File
# Begin Source File

SOURCE=.\SeriesSet.h
# End Source File
# Begin Source File

SOURCE=.\SeriesStatisticsSet.h
# End Source File
# Begin Source File

SOURCE=.\StringSet.h
# End Source File
# Begin Source File

SOURCE=.\ValidateSet.h
# End Source File
# Begin Source File

SOURCE=.\WorldStandardSet.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Authenticator.h
# End Source File
# Begin Source File

SOURCE=.\Base64.h
# End Source File
# Begin Source File

SOURCE=.\BitMaskEnum.h
# End Source File
# Begin Source File

SOURCE=.\BulkCopy.h
# End Source File
# Begin Source File

SOURCE=.\Calculate.h
# End Source File
# Begin Source File

SOURCE=.\Convert.h
# End Source File
# Begin Source File

SOURCE=.\Crypt.h
# End Source File
# Begin Source File

SOURCE=.\CryptByteArray.h
# End Source File
# Begin Source File

SOURCE=.\CSV.h
# End Source File
# Begin Source File

SOURCE=.\DBForeignKey.h
# End Source File
# Begin Source File

SOURCE=.\DBTable.h
# End Source File
# Begin Source File

SOURCE=.\DBView.h
# End Source File
# Begin Source File

SOURCE=.\FixDuplicateOption.h
# End Source File
# Begin Source File

SOURCE=.\Format.h
# End Source File
# Begin Source File

SOURCE=.\HtmlKey.h
# End Source File
# Begin Source File

SOURCE=.\HtmlMonth.h
# End Source File
# Begin Source File

SOURCE=.\HtmlWriter.h
# End Source File
# Begin Source File

SOURCE=.\HttpServerProperties.h
# End Source File
# Begin Source File

SOURCE=.\HttpServerVariable.h
# End Source File
# Begin Source File

SOURCE=.\HttpServerVariableEx.h
# End Source File
# Begin Source File

SOURCE=.\key_intf.h
# End Source File
# Begin Source File

SOURCE=.\MaintainDatabase.h
# End Source File
# Begin Source File

SOURCE=.\MIMECode.h
# End Source File
# Begin Source File

SOURCE=.\Module.h
# End Source File
# Begin Source File

SOURCE=.\Page.h
# End Source File
# Begin Source File

SOURCE=.\PersonSearcher.h
# End Source File
# Begin Source File

SOURCE=.\Process.h
# End Source File
# Begin Source File

SOURCE=.\ProcessGroup.h
# End Source File
# Begin Source File

SOURCE=.\Processor.h
# End Source File
# Begin Source File

SOURCE=.\Properties.h
# End Source File
# Begin Source File

SOURCE=.\RecordsetEx.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\RegKey.h
# End Source File
# Begin Source File

SOURCE=.\ReportAwardsOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportClubRecordsOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportEventCalendarOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportFinancialHistoryOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportGroupsListOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportParticipantHistoryOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportPersonOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportResultsBySeriesOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportResultsOption.h
# End Source File
# Begin Source File

SOURCE=.\ReportRosterOption.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RuleSubType.h
# End Source File
# Begin Source File

SOURCE=.\RuleType.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\StringLine.h
# End Source File
# Begin Source File

SOURCE=.\StringStream.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# Begin Source File

SOURCE=.\WebAthl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\WebAthl.DEF
# End Source File
# Begin Source File

SOURCE=.\WebAthl.RC
# End Source File
# End Group
# Begin Group "HTML"

# PROP Default_Filter "html;htm"
# Begin Source File

SOURCE=.\html\AddSelectBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\CheckBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\DateBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\Default.HTM
# End Source File
# Begin Source File

SOURCE=.\html\EmptyHorizontalRule.HTM
# End Source File
# Begin Source File

SOURCE=.\html\EndRoster.HTM
# End Source File
# Begin Source File

SOURCE=.\html\EndSelectBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\GroupsTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\GroupsTableHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\HiddenText.HTM
# End Source File
# Begin Source File

SOURCE=.\html\HorizontalRule.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MenuBar.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MonthBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MulitFormCheckBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MulitFormComment.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MulitFormHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MulitFormRadioButton.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MulitFormStartSelectBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\MultiFormEditIntBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\NonEditText.HTM
# End Source File
# Begin Source File

SOURCE=.\html\PasswordBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RadioButton.HTM
# End Source File
# Begin Source File

SOURCE=.\html\ResetButton.HTM
# End Source File
# Begin Source File

SOURCE=.\html\ResultsDistTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\ResultsTableHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\ResultsTimeTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RosterTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RulesHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RuleSubmit.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RuleSubTypeSel.HTM
# End Source File
# Begin Source File

SOURCE=.\html\RuleTypeSel.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StandardDistTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StandardTableHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StandardTimeTable.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StartForm.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StartRoster.HTM
# End Source File
# Begin Source File

SOURCE=.\html\StartSelectBox.HTM
# End Source File
# Begin Source File

SOURCE=.\html\SubmitButton.HTM
# End Source File
# Begin Source File

SOURCE=.\html\TableHeader.HTM
# End Source File
# Begin Source File

SOURCE=.\html\TextArea.HTM
# End Source File
# Begin Source File

SOURCE=.\html\TimeBox.HTM
# End Source File
# End Group
# Begin Group "SQL"

# PROP Default_Filter "sql"
# Begin Group "Tables"

# PROP Default_Filter "sql"
# Begin Source File

SOURCE=.\sql\tables\crEvent.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crEventRecord.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crEventRecordTemp.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crEventType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crFinancial.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crGroups.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crLocation.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crOrganisation.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crParticipantForSeries.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crPerson.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crPersonComments.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crPostResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crPreResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRegistrationType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRoster.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRosterDescriptions.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRules.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRuleSubType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crRuleType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crSecurityPerson.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crSecurityPersonSeries.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crSecurityRole.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crSeries.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crSeriesSeason.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\tables\crWorldStandard.SQL
# End Source File
# End Group
# Begin Group "Views"

# PROP Default_Filter "sql"
# Begin Source File

SOURCE=.\sql\views\crLatestFinancial.SQL
# End Source File
# End Group
# Begin Group "SQL Scripts"

# PROP Default_Filter "sql"
# Begin Source File

SOURCE=.\sql\AgeGroupRanking.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\AgeGroups.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\Awards.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\ClubRecords.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\Consistency.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\DeleteResultsPreEventNoPostEvent.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\EventForProcessing.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\EventTally.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\FinancialHistory.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetAgeGroup.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetConsistencyAgeGroup.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetConsistencyResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetEventLength.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetEventRecord.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetEventResultsOrderByGrossPerf.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetEventTimed.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetFinancialParticipantForSeries.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetFinancialResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetFirstEventForSeason.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetListPointScores.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetPersonsLatestEvent.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetQuickPostReport.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetQuickReport.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetRosterNames.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetRules.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetRuleSubType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetRuleType.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GetWavaResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GroupForParticipant.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\GroupsReport.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertEventRecord.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertParticipantForSeries.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertPFSPointScore.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertPFSPostResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertPFSPreResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertPostResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\InsertPreResults.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\IsItWava.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\NextEvent.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\ParticipantHistory.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\PersonParticipant.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\PointScore.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\PrevEvent.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\ResultsOrg.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\SeriesStatistics.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateAgeGroups.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateEligibilityDivision.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateEligibilityGroups.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateEligibilityXMore.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateEventRecord.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateOrganisation.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdateOverAllPlace.SQL
# End Source File
# Begin Source File

SOURCE=.\sql\UpdatePointScores.SQL
# End Source File
# End Group
# Begin Group "Constraints"

# PROP Default_Filter "sql"
# Begin Source File

SOURCE=.\sql\constraints\drfkEvent.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkEventRecord.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkFinancial.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkGroups.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkParticipantForSeries.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkPerson.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkPersonComments.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkPostResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkPreResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkRoster.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkRules.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkRuleSubType.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkSecurityPerson.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkSecurityPersonSeries.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkSeriesSeason.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\drfkWorldStandard.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkEvent.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkEventRecord.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkFinancial.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkGroups.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkParticipantForSeries.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkPerson.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkPersonComments.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkPostResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkPreResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkResults.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkRoster.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkRules.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkRuleSubType.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkSecurityPerson.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkSecurityPersonSeries.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkSeriesSeason.sql
# End Source File
# Begin Source File

SOURCE=.\sql\constraints\fkWorldStandard.sql
# End Source File
# End Group
# End Group
# Begin Group "Build"

# PROP Default_Filter "txt"
# Begin Source File

SOURCE=.\build\date.txt
# End Source File
# Begin Source File

SOURCE=.\build\no.txt
# End Source File
# Begin Source File

SOURCE=.\build\release.txt
# End Source File
# End Group
# Begin Group "Javascript"

# PROP Default_Filter "JS"
# Begin Source File

SOURCE=.\html\DBConfig.JS
# End Source File
# End Group
# End Target
# End Project
