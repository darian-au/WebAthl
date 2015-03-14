# Microsoft Developer Studio Generated NMAKE File, Based on WebAthl.dsp
!IF "$(CFG)" == ""
CFG=WebAthl - Win32 Release
!MESSAGE No configuration specified. Defaulting to WebAthl - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "WebAthl - Win32 Release" && "$(CFG)" != "WebAthl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WebAthl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WebAthl.dll" ".\build\build.exe"


CLEAN :
	-@erase "$(INTDIR)\AgeGroupRankingSet.obj"
	-@erase "$(INTDIR)\AgeGroupSet.obj"
	-@erase "$(INTDIR)\Authenticator.obj"
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\BitMaskEnum.obj"
	-@erase "$(INTDIR)\BoolResultSet.obj"
	-@erase "$(INTDIR)\BulkCopy.obj"
	-@erase "$(INTDIR)\Calculate.obj"
	-@erase "$(INTDIR)\ClubRecordsSet.obj"
	-@erase "$(INTDIR)\ConsistencyAgeGroupSet.obj"
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\CountItemSet.obj"
	-@erase "$(INTDIR)\CountResultSet.obj"
	-@erase "$(INTDIR)\Crypt.obj"
	-@erase "$(INTDIR)\CryptByteArray.obj"
	-@erase "$(INTDIR)\CSV.obj"
	-@erase "$(INTDIR)\DBForeignKey.obj"
	-@erase "$(INTDIR)\DBTable.obj"
	-@erase "$(INTDIR)\DBView.obj"
	-@erase "$(INTDIR)\Default.obj"
	-@erase "$(INTDIR)\DoubleSet.obj"
	-@erase "$(INTDIR)\DupPersonSet.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\EventETypLocSet.obj"
	-@erase "$(INTDIR)\EventRecordSet.obj"
	-@erase "$(INTDIR)\EventSet.obj"
	-@erase "$(INTDIR)\EventTallySet.obj"
	-@erase "$(INTDIR)\EventType.obj"
	-@erase "$(INTDIR)\EventTypeSet.obj"
	-@erase "$(INTDIR)\Financial.obj"
	-@erase "$(INTDIR)\FinancialRegistrationSet.obj"
	-@erase "$(INTDIR)\FinancialSet.obj"
	-@erase "$(INTDIR)\FixDuplicateOption.obj"
	-@erase "$(INTDIR)\Format.obj"
	-@erase "$(INTDIR)\Groups.obj"
	-@erase "$(INTDIR)\GroupsReportSet.obj"
	-@erase "$(INTDIR)\GroupsSet.obj"
	-@erase "$(INTDIR)\HtmlKey.obj"
	-@erase "$(INTDIR)\HtmlMonth.obj"
	-@erase "$(INTDIR)\HtmlWriter.obj"
	-@erase "$(INTDIR)\HttpServerProperties.obj"
	-@erase "$(INTDIR)\HttpServerVariable.obj"
	-@erase "$(INTDIR)\HttpServerVariableEx.obj"
	-@erase "$(INTDIR)\IntegerSet.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\Location.obj"
	-@erase "$(INTDIR)\LocationSet.obj"
	-@erase "$(INTDIR)\MaintainDatabase.obj"
	-@erase "$(INTDIR)\Maintenance.obj"
	-@erase "$(INTDIR)\MIMECode.obj"
	-@erase "$(INTDIR)\Module.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Organisation.obj"
	-@erase "$(INTDIR)\OrganisationSet.obj"
	-@erase "$(INTDIR)\Page.obj"
	-@erase "$(INTDIR)\ParticipantDetailsSet.obj"
	-@erase "$(INTDIR)\ParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\ParticipantHistorySet.obj"
	-@erase "$(INTDIR)\Person.obj"
	-@erase "$(INTDIR)\PersonCommentsSet.obj"
	-@erase "$(INTDIR)\PersonFinancialCommentsSet.obj"
	-@erase "$(INTDIR)\PersonFinancialSet.obj"
	-@erase "$(INTDIR)\PersonParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\PersonSearcher.obj"
	-@erase "$(INTDIR)\PersonSet.obj"
	-@erase "$(INTDIR)\PostResultsSet.obj"
	-@erase "$(INTDIR)\PreResultsSet.obj"
	-@erase "$(INTDIR)\Process.obj"
	-@erase "$(INTDIR)\ProcessGroup.obj"
	-@erase "$(INTDIR)\Processing.obj"
	-@erase "$(INTDIR)\Processor.obj"
	-@erase "$(INTDIR)\Properties.obj"
	-@erase "$(INTDIR)\QuickReportSet.obj"
	-@erase "$(INTDIR)\RecordsetEx.obj"
	-@erase "$(INTDIR)\RegistrationType.obj"
	-@erase "$(INTDIR)\RegistrationTypeSet.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\RegKey.obj"
	-@erase "$(INTDIR)\ReportAwardsOption.obj"
	-@erase "$(INTDIR)\ReportClubRecordsOption.obj"
	-@erase "$(INTDIR)\ReportEventCalendarOption.obj"
	-@erase "$(INTDIR)\ReportFinancialHistoryOption.obj"
	-@erase "$(INTDIR)\ReportGroupsListOption.obj"
	-@erase "$(INTDIR)\ReportParticipantHistoryOption.obj"
	-@erase "$(INTDIR)\ReportPersonOption.obj"
	-@erase "$(INTDIR)\ReportResultsBySeriesOption.obj"
	-@erase "$(INTDIR)\ReportResultsOption.obj"
	-@erase "$(INTDIR)\ReportRosterOption.obj"
	-@erase "$(INTDIR)\Reports.obj"
	-@erase "$(INTDIR)\ResultsEntry.obj"
	-@erase "$(INTDIR)\ResultsEventTypeSet.obj"
	-@erase "$(INTDIR)\ResultsOrgSet.obj"
	-@erase "$(INTDIR)\ResultsParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\ResultsPostResultsSet.obj"
	-@erase "$(INTDIR)\ResultsSet.obj"
	-@erase "$(INTDIR)\ResultsWorldStandardSet.obj"
	-@erase "$(INTDIR)\Roster.obj"
	-@erase "$(INTDIR)\RosterDescriptions.obj"
	-@erase "$(INTDIR)\RosterDescriptionsSet.obj"
	-@erase "$(INTDIR)\RosterNamesSet.obj"
	-@erase "$(INTDIR)\RosterSet.obj"
	-@erase "$(INTDIR)\Rules.obj"
	-@erase "$(INTDIR)\RulesJoinSet.obj"
	-@erase "$(INTDIR)\RulesSet.obj"
	-@erase "$(INTDIR)\RuleSubType.obj"
	-@erase "$(INTDIR)\RuleSubTypeSet.obj"
	-@erase "$(INTDIR)\RuleType.obj"
	-@erase "$(INTDIR)\RuleTypeSet.obj"
	-@erase "$(INTDIR)\SearchPerson.obj"
	-@erase "$(INTDIR)\Security.obj"
	-@erase "$(INTDIR)\SecurityPersonSeriesSet.obj"
	-@erase "$(INTDIR)\SecurityPersonSet.obj"
	-@erase "$(INTDIR)\SecurityRoleSet.obj"
	-@erase "$(INTDIR)\SelectSeries.obj"
	-@erase "$(INTDIR)\Series.obj"
	-@erase "$(INTDIR)\SeriesPersonPFSOrgSet.obj"
	-@erase "$(INTDIR)\SeriesSeasonSet.obj"
	-@erase "$(INTDIR)\SeriesSet.obj"
	-@erase "$(INTDIR)\SeriesStatisticsSet.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\StringLine.obj"
	-@erase "$(INTDIR)\StringSet.obj"
	-@erase "$(INTDIR)\StringStream.obj"
	-@erase "$(INTDIR)\Util.obj"
	-@erase "$(INTDIR)\Utilities.obj"
	-@erase "$(INTDIR)\ValidateSet.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WebAthl.obj"
	-@erase "$(INTDIR)\WebAthl.res"
	-@erase "$(INTDIR)\WorldStandard.obj"
	-@erase "$(INTDIR)\WorldStandardSet.obj"
	-@erase "$(OUTDIR)\WebAthl.dll"
	-@erase "$(OUTDIR)\WebAthl.exp"
	-@erase "$(OUTDIR)\WebAthl.lib"
	-@erase "build\build.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\WebAthl.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WebAthl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WebAthl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=advapi32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\WebAthl.pdb" /machine:I386 /def:".\WebAthl.DEF" /out:"$(OUTDIR)\WebAthl.dll" /implib:"$(OUTDIR)\WebAthl.lib" 
DEF_FILE= \
	".\WebAthl.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AgeGroupRankingSet.obj" \
	"$(INTDIR)\AgeGroupSet.obj" \
	"$(INTDIR)\BoolResultSet.obj" \
	"$(INTDIR)\ClubRecordsSet.obj" \
	"$(INTDIR)\ConsistencyAgeGroupSet.obj" \
	"$(INTDIR)\CountItemSet.obj" \
	"$(INTDIR)\CountResultSet.obj" \
	"$(INTDIR)\DoubleSet.obj" \
	"$(INTDIR)\DupPersonSet.obj" \
	"$(INTDIR)\EventETypLocSet.obj" \
	"$(INTDIR)\EventRecordSet.obj" \
	"$(INTDIR)\EventSet.obj" \
	"$(INTDIR)\EventTallySet.obj" \
	"$(INTDIR)\EventTypeSet.obj" \
	"$(INTDIR)\FinancialRegistrationSet.obj" \
	"$(INTDIR)\FinancialSet.obj" \
	"$(INTDIR)\GroupsReportSet.obj" \
	"$(INTDIR)\GroupsSet.obj" \
	"$(INTDIR)\IntegerSet.obj" \
	"$(INTDIR)\LocationSet.obj" \
	"$(INTDIR)\OrganisationSet.obj" \
	"$(INTDIR)\ParticipantDetailsSet.obj" \
	"$(INTDIR)\ParticipantForSeriesSet.obj" \
	"$(INTDIR)\ParticipantHistorySet.obj" \
	"$(INTDIR)\PersonCommentsSet.obj" \
	"$(INTDIR)\PersonFinancialCommentsSet.obj" \
	"$(INTDIR)\PersonFinancialSet.obj" \
	"$(INTDIR)\PersonParticipantForSeriesSet.obj" \
	"$(INTDIR)\PersonSet.obj" \
	"$(INTDIR)\PostResultsSet.obj" \
	"$(INTDIR)\PreResultsSet.obj" \
	"$(INTDIR)\QuickReportSet.obj" \
	"$(INTDIR)\RegistrationTypeSet.obj" \
	"$(INTDIR)\ResultsEventTypeSet.obj" \
	"$(INTDIR)\ResultsOrgSet.obj" \
	"$(INTDIR)\ResultsParticipantForSeriesSet.obj" \
	"$(INTDIR)\ResultsPostResultsSet.obj" \
	"$(INTDIR)\ResultsSet.obj" \
	"$(INTDIR)\ResultsWorldStandardSet.obj" \
	"$(INTDIR)\RosterDescriptionsSet.obj" \
	"$(INTDIR)\RosterNamesSet.obj" \
	"$(INTDIR)\RosterSet.obj" \
	"$(INTDIR)\RulesJoinSet.obj" \
	"$(INTDIR)\RulesSet.obj" \
	"$(INTDIR)\RuleSubTypeSet.obj" \
	"$(INTDIR)\RuleTypeSet.obj" \
	"$(INTDIR)\SecurityPersonSeriesSet.obj" \
	"$(INTDIR)\SecurityPersonSet.obj" \
	"$(INTDIR)\SecurityRoleSet.obj" \
	"$(INTDIR)\SeriesPersonPFSOrgSet.obj" \
	"$(INTDIR)\SeriesSeasonSet.obj" \
	"$(INTDIR)\SeriesSet.obj" \
	"$(INTDIR)\SeriesStatisticsSet.obj" \
	"$(INTDIR)\StringSet.obj" \
	"$(INTDIR)\ValidateSet.obj" \
	"$(INTDIR)\WorldStandardSet.obj" \
	"$(INTDIR)\Default.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\EventType.obj" \
	"$(INTDIR)\Financial.obj" \
	"$(INTDIR)\Groups.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\Location.obj" \
	"$(INTDIR)\Maintenance.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\Organisation.obj" \
	"$(INTDIR)\Person.obj" \
	"$(INTDIR)\Processing.obj" \
	"$(INTDIR)\RegistrationType.obj" \
	"$(INTDIR)\Reports.obj" \
	"$(INTDIR)\ResultsEntry.obj" \
	"$(INTDIR)\Roster.obj" \
	"$(INTDIR)\RosterDescriptions.obj" \
	"$(INTDIR)\Rules.obj" \
	"$(INTDIR)\SearchPerson.obj" \
	"$(INTDIR)\Security.obj" \
	"$(INTDIR)\SelectSeries.obj" \
	"$(INTDIR)\Series.obj" \
	"$(INTDIR)\Utilities.obj" \
	"$(INTDIR)\WorldStandard.obj" \
	"$(INTDIR)\Authenticator.obj" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\BitMaskEnum.obj" \
	"$(INTDIR)\BulkCopy.obj" \
	"$(INTDIR)\Calculate.obj" \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Crypt.obj" \
	"$(INTDIR)\CryptByteArray.obj" \
	"$(INTDIR)\CSV.obj" \
	"$(INTDIR)\DBForeignKey.obj" \
	"$(INTDIR)\DBTable.obj" \
	"$(INTDIR)\DBView.obj" \
	"$(INTDIR)\FixDuplicateOption.obj" \
	"$(INTDIR)\Format.obj" \
	"$(INTDIR)\HtmlKey.obj" \
	"$(INTDIR)\HtmlMonth.obj" \
	"$(INTDIR)\HtmlWriter.obj" \
	"$(INTDIR)\HttpServerProperties.obj" \
	"$(INTDIR)\HttpServerVariable.obj" \
	"$(INTDIR)\HttpServerVariableEx.obj" \
	"$(INTDIR)\MaintainDatabase.obj" \
	"$(INTDIR)\MIMECode.obj" \
	"$(INTDIR)\Module.obj" \
	"$(INTDIR)\Page.obj" \
	"$(INTDIR)\PersonSearcher.obj" \
	"$(INTDIR)\Process.obj" \
	"$(INTDIR)\ProcessGroup.obj" \
	"$(INTDIR)\Processor.obj" \
	"$(INTDIR)\Properties.obj" \
	"$(INTDIR)\RecordsetEx.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RegKey.obj" \
	"$(INTDIR)\ReportAwardsOption.obj" \
	"$(INTDIR)\ReportClubRecordsOption.obj" \
	"$(INTDIR)\ReportEventCalendarOption.obj" \
	"$(INTDIR)\ReportFinancialHistoryOption.obj" \
	"$(INTDIR)\ReportGroupsListOption.obj" \
	"$(INTDIR)\ReportParticipantHistoryOption.obj" \
	"$(INTDIR)\ReportPersonOption.obj" \
	"$(INTDIR)\ReportResultsBySeriesOption.obj" \
	"$(INTDIR)\ReportResultsOption.obj" \
	"$(INTDIR)\ReportRosterOption.obj" \
	"$(INTDIR)\RuleSubType.obj" \
	"$(INTDIR)\RuleType.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\StringLine.obj" \
	"$(INTDIR)\StringStream.obj" \
	"$(INTDIR)\Util.obj" \
	"$(INTDIR)\WebAthl.obj" \
	"$(INTDIR)\WebAthl.res"

"$(OUTDIR)\WebAthl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

InputPath=.\Release\WebAthl.dll
SOURCE="$(InputPath)"

".\build\build.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	build\build.bat
<< 
	

!ELSEIF  "$(CFG)" == "WebAthl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WebAthl.dll"


CLEAN :
	-@erase "$(INTDIR)\AgeGroupRankingSet.obj"
	-@erase "$(INTDIR)\AgeGroupSet.obj"
	-@erase "$(INTDIR)\Authenticator.obj"
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\BitMaskEnum.obj"
	-@erase "$(INTDIR)\BoolResultSet.obj"
	-@erase "$(INTDIR)\BulkCopy.obj"
	-@erase "$(INTDIR)\Calculate.obj"
	-@erase "$(INTDIR)\ClubRecordsSet.obj"
	-@erase "$(INTDIR)\ConsistencyAgeGroupSet.obj"
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\CountItemSet.obj"
	-@erase "$(INTDIR)\CountResultSet.obj"
	-@erase "$(INTDIR)\Crypt.obj"
	-@erase "$(INTDIR)\CryptByteArray.obj"
	-@erase "$(INTDIR)\CSV.obj"
	-@erase "$(INTDIR)\DBForeignKey.obj"
	-@erase "$(INTDIR)\DBTable.obj"
	-@erase "$(INTDIR)\DBView.obj"
	-@erase "$(INTDIR)\Default.obj"
	-@erase "$(INTDIR)\DoubleSet.obj"
	-@erase "$(INTDIR)\DupPersonSet.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\EventETypLocSet.obj"
	-@erase "$(INTDIR)\EventRecordSet.obj"
	-@erase "$(INTDIR)\EventSet.obj"
	-@erase "$(INTDIR)\EventTallySet.obj"
	-@erase "$(INTDIR)\EventType.obj"
	-@erase "$(INTDIR)\EventTypeSet.obj"
	-@erase "$(INTDIR)\Financial.obj"
	-@erase "$(INTDIR)\FinancialRegistrationSet.obj"
	-@erase "$(INTDIR)\FinancialSet.obj"
	-@erase "$(INTDIR)\FixDuplicateOption.obj"
	-@erase "$(INTDIR)\Format.obj"
	-@erase "$(INTDIR)\Groups.obj"
	-@erase "$(INTDIR)\GroupsReportSet.obj"
	-@erase "$(INTDIR)\GroupsSet.obj"
	-@erase "$(INTDIR)\HtmlKey.obj"
	-@erase "$(INTDIR)\HtmlMonth.obj"
	-@erase "$(INTDIR)\HtmlWriter.obj"
	-@erase "$(INTDIR)\HttpServerProperties.obj"
	-@erase "$(INTDIR)\HttpServerVariable.obj"
	-@erase "$(INTDIR)\HttpServerVariableEx.obj"
	-@erase "$(INTDIR)\IntegerSet.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\Location.obj"
	-@erase "$(INTDIR)\LocationSet.obj"
	-@erase "$(INTDIR)\MaintainDatabase.obj"
	-@erase "$(INTDIR)\Maintenance.obj"
	-@erase "$(INTDIR)\MIMECode.obj"
	-@erase "$(INTDIR)\Module.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Organisation.obj"
	-@erase "$(INTDIR)\OrganisationSet.obj"
	-@erase "$(INTDIR)\Page.obj"
	-@erase "$(INTDIR)\ParticipantDetailsSet.obj"
	-@erase "$(INTDIR)\ParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\ParticipantHistorySet.obj"
	-@erase "$(INTDIR)\Person.obj"
	-@erase "$(INTDIR)\PersonCommentsSet.obj"
	-@erase "$(INTDIR)\PersonFinancialCommentsSet.obj"
	-@erase "$(INTDIR)\PersonFinancialSet.obj"
	-@erase "$(INTDIR)\PersonParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\PersonSearcher.obj"
	-@erase "$(INTDIR)\PersonSet.obj"
	-@erase "$(INTDIR)\PostResultsSet.obj"
	-@erase "$(INTDIR)\PreResultsSet.obj"
	-@erase "$(INTDIR)\Process.obj"
	-@erase "$(INTDIR)\ProcessGroup.obj"
	-@erase "$(INTDIR)\Processing.obj"
	-@erase "$(INTDIR)\Processor.obj"
	-@erase "$(INTDIR)\Properties.obj"
	-@erase "$(INTDIR)\QuickReportSet.obj"
	-@erase "$(INTDIR)\RecordsetEx.obj"
	-@erase "$(INTDIR)\RegistrationType.obj"
	-@erase "$(INTDIR)\RegistrationTypeSet.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\RegKey.obj"
	-@erase "$(INTDIR)\ReportAwardsOption.obj"
	-@erase "$(INTDIR)\ReportClubRecordsOption.obj"
	-@erase "$(INTDIR)\ReportEventCalendarOption.obj"
	-@erase "$(INTDIR)\ReportFinancialHistoryOption.obj"
	-@erase "$(INTDIR)\ReportGroupsListOption.obj"
	-@erase "$(INTDIR)\ReportParticipantHistoryOption.obj"
	-@erase "$(INTDIR)\ReportPersonOption.obj"
	-@erase "$(INTDIR)\ReportResultsBySeriesOption.obj"
	-@erase "$(INTDIR)\ReportResultsOption.obj"
	-@erase "$(INTDIR)\ReportRosterOption.obj"
	-@erase "$(INTDIR)\Reports.obj"
	-@erase "$(INTDIR)\ResultsEntry.obj"
	-@erase "$(INTDIR)\ResultsEventTypeSet.obj"
	-@erase "$(INTDIR)\ResultsOrgSet.obj"
	-@erase "$(INTDIR)\ResultsParticipantForSeriesSet.obj"
	-@erase "$(INTDIR)\ResultsPostResultsSet.obj"
	-@erase "$(INTDIR)\ResultsSet.obj"
	-@erase "$(INTDIR)\ResultsWorldStandardSet.obj"
	-@erase "$(INTDIR)\Roster.obj"
	-@erase "$(INTDIR)\RosterDescriptions.obj"
	-@erase "$(INTDIR)\RosterDescriptionsSet.obj"
	-@erase "$(INTDIR)\RosterNamesSet.obj"
	-@erase "$(INTDIR)\RosterSet.obj"
	-@erase "$(INTDIR)\Rules.obj"
	-@erase "$(INTDIR)\RulesJoinSet.obj"
	-@erase "$(INTDIR)\RulesSet.obj"
	-@erase "$(INTDIR)\RuleSubType.obj"
	-@erase "$(INTDIR)\RuleSubTypeSet.obj"
	-@erase "$(INTDIR)\RuleType.obj"
	-@erase "$(INTDIR)\RuleTypeSet.obj"
	-@erase "$(INTDIR)\SearchPerson.obj"
	-@erase "$(INTDIR)\Security.obj"
	-@erase "$(INTDIR)\SecurityPersonSeriesSet.obj"
	-@erase "$(INTDIR)\SecurityPersonSet.obj"
	-@erase "$(INTDIR)\SecurityRoleSet.obj"
	-@erase "$(INTDIR)\SelectSeries.obj"
	-@erase "$(INTDIR)\Series.obj"
	-@erase "$(INTDIR)\SeriesPersonPFSOrgSet.obj"
	-@erase "$(INTDIR)\SeriesSeasonSet.obj"
	-@erase "$(INTDIR)\SeriesSet.obj"
	-@erase "$(INTDIR)\SeriesStatisticsSet.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\StringLine.obj"
	-@erase "$(INTDIR)\StringSet.obj"
	-@erase "$(INTDIR)\StringStream.obj"
	-@erase "$(INTDIR)\Util.obj"
	-@erase "$(INTDIR)\Utilities.obj"
	-@erase "$(INTDIR)\ValidateSet.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WebAthl.obj"
	-@erase "$(INTDIR)\WebAthl.res"
	-@erase "$(INTDIR)\WorldStandard.obj"
	-@erase "$(INTDIR)\WorldStandardSet.obj"
	-@erase "$(OUTDIR)\WebAthl.dll"
	-@erase "$(OUTDIR)\WebAthl.exp"
	-@erase "$(OUTDIR)\WebAthl.ilk"
	-@erase "$(OUTDIR)\WebAthl.lib"
	-@erase "$(OUTDIR)\WebAthl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\WebAthl.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\WebAthl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WebAthl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=advapi32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\WebAthl.pdb" /debug /machine:I386 /def:".\WebAthl.DEF" /out:"$(OUTDIR)\WebAthl.dll" /implib:"$(OUTDIR)\WebAthl.lib" 
DEF_FILE= \
	".\WebAthl.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AgeGroupRankingSet.obj" \
	"$(INTDIR)\AgeGroupSet.obj" \
	"$(INTDIR)\BoolResultSet.obj" \
	"$(INTDIR)\ClubRecordsSet.obj" \
	"$(INTDIR)\ConsistencyAgeGroupSet.obj" \
	"$(INTDIR)\CountItemSet.obj" \
	"$(INTDIR)\CountResultSet.obj" \
	"$(INTDIR)\DoubleSet.obj" \
	"$(INTDIR)\DupPersonSet.obj" \
	"$(INTDIR)\EventETypLocSet.obj" \
	"$(INTDIR)\EventRecordSet.obj" \
	"$(INTDIR)\EventSet.obj" \
	"$(INTDIR)\EventTallySet.obj" \
	"$(INTDIR)\EventTypeSet.obj" \
	"$(INTDIR)\FinancialRegistrationSet.obj" \
	"$(INTDIR)\FinancialSet.obj" \
	"$(INTDIR)\GroupsReportSet.obj" \
	"$(INTDIR)\GroupsSet.obj" \
	"$(INTDIR)\IntegerSet.obj" \
	"$(INTDIR)\LocationSet.obj" \
	"$(INTDIR)\OrganisationSet.obj" \
	"$(INTDIR)\ParticipantDetailsSet.obj" \
	"$(INTDIR)\ParticipantForSeriesSet.obj" \
	"$(INTDIR)\ParticipantHistorySet.obj" \
	"$(INTDIR)\PersonCommentsSet.obj" \
	"$(INTDIR)\PersonFinancialCommentsSet.obj" \
	"$(INTDIR)\PersonFinancialSet.obj" \
	"$(INTDIR)\PersonParticipantForSeriesSet.obj" \
	"$(INTDIR)\PersonSet.obj" \
	"$(INTDIR)\PostResultsSet.obj" \
	"$(INTDIR)\PreResultsSet.obj" \
	"$(INTDIR)\QuickReportSet.obj" \
	"$(INTDIR)\RegistrationTypeSet.obj" \
	"$(INTDIR)\ResultsEventTypeSet.obj" \
	"$(INTDIR)\ResultsOrgSet.obj" \
	"$(INTDIR)\ResultsParticipantForSeriesSet.obj" \
	"$(INTDIR)\ResultsPostResultsSet.obj" \
	"$(INTDIR)\ResultsSet.obj" \
	"$(INTDIR)\ResultsWorldStandardSet.obj" \
	"$(INTDIR)\RosterDescriptionsSet.obj" \
	"$(INTDIR)\RosterNamesSet.obj" \
	"$(INTDIR)\RosterSet.obj" \
	"$(INTDIR)\RulesJoinSet.obj" \
	"$(INTDIR)\RulesSet.obj" \
	"$(INTDIR)\RuleSubTypeSet.obj" \
	"$(INTDIR)\RuleTypeSet.obj" \
	"$(INTDIR)\SecurityPersonSeriesSet.obj" \
	"$(INTDIR)\SecurityPersonSet.obj" \
	"$(INTDIR)\SecurityRoleSet.obj" \
	"$(INTDIR)\SeriesPersonPFSOrgSet.obj" \
	"$(INTDIR)\SeriesSeasonSet.obj" \
	"$(INTDIR)\SeriesSet.obj" \
	"$(INTDIR)\SeriesStatisticsSet.obj" \
	"$(INTDIR)\StringSet.obj" \
	"$(INTDIR)\ValidateSet.obj" \
	"$(INTDIR)\WorldStandardSet.obj" \
	"$(INTDIR)\Default.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\EventType.obj" \
	"$(INTDIR)\Financial.obj" \
	"$(INTDIR)\Groups.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\Location.obj" \
	"$(INTDIR)\Maintenance.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\Organisation.obj" \
	"$(INTDIR)\Person.obj" \
	"$(INTDIR)\Processing.obj" \
	"$(INTDIR)\RegistrationType.obj" \
	"$(INTDIR)\Reports.obj" \
	"$(INTDIR)\ResultsEntry.obj" \
	"$(INTDIR)\Roster.obj" \
	"$(INTDIR)\RosterDescriptions.obj" \
	"$(INTDIR)\Rules.obj" \
	"$(INTDIR)\SearchPerson.obj" \
	"$(INTDIR)\Security.obj" \
	"$(INTDIR)\SelectSeries.obj" \
	"$(INTDIR)\Series.obj" \
	"$(INTDIR)\Utilities.obj" \
	"$(INTDIR)\WorldStandard.obj" \
	"$(INTDIR)\Authenticator.obj" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\BitMaskEnum.obj" \
	"$(INTDIR)\BulkCopy.obj" \
	"$(INTDIR)\Calculate.obj" \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Crypt.obj" \
	"$(INTDIR)\CryptByteArray.obj" \
	"$(INTDIR)\CSV.obj" \
	"$(INTDIR)\DBForeignKey.obj" \
	"$(INTDIR)\DBTable.obj" \
	"$(INTDIR)\DBView.obj" \
	"$(INTDIR)\FixDuplicateOption.obj" \
	"$(INTDIR)\Format.obj" \
	"$(INTDIR)\HtmlKey.obj" \
	"$(INTDIR)\HtmlMonth.obj" \
	"$(INTDIR)\HtmlWriter.obj" \
	"$(INTDIR)\HttpServerProperties.obj" \
	"$(INTDIR)\HttpServerVariable.obj" \
	"$(INTDIR)\HttpServerVariableEx.obj" \
	"$(INTDIR)\MaintainDatabase.obj" \
	"$(INTDIR)\MIMECode.obj" \
	"$(INTDIR)\Module.obj" \
	"$(INTDIR)\Page.obj" \
	"$(INTDIR)\PersonSearcher.obj" \
	"$(INTDIR)\Process.obj" \
	"$(INTDIR)\ProcessGroup.obj" \
	"$(INTDIR)\Processor.obj" \
	"$(INTDIR)\Properties.obj" \
	"$(INTDIR)\RecordsetEx.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RegKey.obj" \
	"$(INTDIR)\ReportAwardsOption.obj" \
	"$(INTDIR)\ReportClubRecordsOption.obj" \
	"$(INTDIR)\ReportEventCalendarOption.obj" \
	"$(INTDIR)\ReportFinancialHistoryOption.obj" \
	"$(INTDIR)\ReportGroupsListOption.obj" \
	"$(INTDIR)\ReportParticipantHistoryOption.obj" \
	"$(INTDIR)\ReportPersonOption.obj" \
	"$(INTDIR)\ReportResultsBySeriesOption.obj" \
	"$(INTDIR)\ReportResultsOption.obj" \
	"$(INTDIR)\ReportRosterOption.obj" \
	"$(INTDIR)\RuleSubType.obj" \
	"$(INTDIR)\RuleType.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\StringLine.obj" \
	"$(INTDIR)\StringStream.obj" \
	"$(INTDIR)\Util.obj" \
	"$(INTDIR)\WebAthl.obj" \
	"$(INTDIR)\WebAthl.res"

"$(OUTDIR)\WebAthl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WebAthl.dep")
!INCLUDE "WebAthl.dep"
!ELSE 
!MESSAGE Warning: cannot find "WebAthl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WebAthl - Win32 Release" || "$(CFG)" == "WebAthl - Win32 Debug"
SOURCE=.\AgeGroupRankingSet.cpp

"$(INTDIR)\AgeGroupRankingSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AgeGroupSet.cpp

"$(INTDIR)\AgeGroupSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BoolResultSet.cpp

"$(INTDIR)\BoolResultSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ClubRecordsSet.cpp

"$(INTDIR)\ClubRecordsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ConsistencyAgeGroupSet.cpp

"$(INTDIR)\ConsistencyAgeGroupSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CountItemSet.cpp

"$(INTDIR)\CountItemSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CountResultSet.cpp

"$(INTDIR)\CountResultSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DoubleSet.cpp

"$(INTDIR)\DoubleSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DupPersonSet.cpp

"$(INTDIR)\DupPersonSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventETypLocSet.cpp

"$(INTDIR)\EventETypLocSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventRecordSet.cpp

"$(INTDIR)\EventRecordSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventSet.cpp

"$(INTDIR)\EventSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventTallySet.cpp

"$(INTDIR)\EventTallySet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventTypeSet.cpp

"$(INTDIR)\EventTypeSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FinancialRegistrationSet.cpp

"$(INTDIR)\FinancialRegistrationSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FinancialSet.cpp

"$(INTDIR)\FinancialSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GroupsReportSet.cpp

"$(INTDIR)\GroupsReportSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GroupsSet.cpp

"$(INTDIR)\GroupsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IntegerSet.cpp

"$(INTDIR)\IntegerSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LocationSet.cpp

"$(INTDIR)\LocationSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OrganisationSet.cpp

"$(INTDIR)\OrganisationSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParticipantDetailsSet.cpp

"$(INTDIR)\ParticipantDetailsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParticipantForSeriesSet.cpp

"$(INTDIR)\ParticipantForSeriesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParticipantHistorySet.cpp

"$(INTDIR)\ParticipantHistorySet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonCommentsSet.cpp

"$(INTDIR)\PersonCommentsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonFinancialCommentsSet.cpp

"$(INTDIR)\PersonFinancialCommentsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonFinancialSet.cpp

"$(INTDIR)\PersonFinancialSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonParticipantForSeriesSet.cpp

"$(INTDIR)\PersonParticipantForSeriesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonSet.cpp

"$(INTDIR)\PersonSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PostResultsSet.cpp

"$(INTDIR)\PostResultsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PreResultsSet.cpp

"$(INTDIR)\PreResultsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\QuickReportSet.cpp

"$(INTDIR)\QuickReportSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegistrationTypeSet.cpp

"$(INTDIR)\RegistrationTypeSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsEventTypeSet.cpp

"$(INTDIR)\ResultsEventTypeSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsOrgSet.cpp

"$(INTDIR)\ResultsOrgSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsParticipantForSeriesSet.cpp

"$(INTDIR)\ResultsParticipantForSeriesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsPostResultsSet.cpp

"$(INTDIR)\ResultsPostResultsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsSet.cpp

"$(INTDIR)\ResultsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsWorldStandardSet.cpp

"$(INTDIR)\ResultsWorldStandardSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RosterDescriptionsSet.cpp

"$(INTDIR)\RosterDescriptionsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RosterNamesSet.cpp

"$(INTDIR)\RosterNamesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RosterSet.cpp

"$(INTDIR)\RosterSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RulesJoinSet.cpp

"$(INTDIR)\RulesJoinSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RulesSet.cpp

"$(INTDIR)\RulesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RuleSubTypeSet.cpp

"$(INTDIR)\RuleSubTypeSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RuleTypeSet.cpp

"$(INTDIR)\RuleTypeSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SecurityPersonSeriesSet.cpp

"$(INTDIR)\SecurityPersonSeriesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SecurityPersonSet.cpp

"$(INTDIR)\SecurityPersonSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SecurityRoleSet.cpp

"$(INTDIR)\SecurityRoleSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SeriesPersonPFSOrgSet.cpp

"$(INTDIR)\SeriesPersonPFSOrgSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SeriesSeasonSet.cpp

"$(INTDIR)\SeriesSeasonSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SeriesSet.cpp

"$(INTDIR)\SeriesSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SeriesStatisticsSet.cpp

"$(INTDIR)\SeriesStatisticsSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StringSet.cpp

"$(INTDIR)\StringSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ValidateSet.cpp

"$(INTDIR)\ValidateSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WorldStandardSet.cpp

"$(INTDIR)\WorldStandardSet.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Default.cpp

"$(INTDIR)\Default.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Event.cpp

"$(INTDIR)\Event.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EventType.cpp

"$(INTDIR)\EventType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Financial.cpp

"$(INTDIR)\Financial.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Groups.cpp

"$(INTDIR)\Groups.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\License.cpp

"$(INTDIR)\License.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Location.cpp

"$(INTDIR)\Location.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Maintenance.cpp

"$(INTDIR)\Maintenance.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Options.cpp

"$(INTDIR)\Options.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Organisation.cpp

"$(INTDIR)\Organisation.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Person.cpp

"$(INTDIR)\Person.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Processing.cpp

"$(INTDIR)\Processing.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegistrationType.cpp

"$(INTDIR)\RegistrationType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Reports.cpp

"$(INTDIR)\Reports.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ResultsEntry.cpp

"$(INTDIR)\ResultsEntry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Roster.cpp

"$(INTDIR)\Roster.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RosterDescriptions.cpp

"$(INTDIR)\RosterDescriptions.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Rules.cpp

"$(INTDIR)\Rules.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SearchPerson.cpp

"$(INTDIR)\SearchPerson.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Security.cpp

"$(INTDIR)\Security.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SelectSeries.cpp

"$(INTDIR)\SelectSeries.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Series.cpp

"$(INTDIR)\Series.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Utilities.cpp

"$(INTDIR)\Utilities.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WorldStandard.cpp

"$(INTDIR)\WorldStandard.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Authenticator.cpp

"$(INTDIR)\Authenticator.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Base64.cpp

"$(INTDIR)\Base64.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BitMaskEnum.cpp

"$(INTDIR)\BitMaskEnum.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BulkCopy.cpp

"$(INTDIR)\BulkCopy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Calculate.cpp

"$(INTDIR)\Calculate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Convert.cpp

"$(INTDIR)\Convert.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Crypt.cpp

"$(INTDIR)\Crypt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CryptByteArray.cpp

"$(INTDIR)\CryptByteArray.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CSV.cpp

"$(INTDIR)\CSV.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DBForeignKey.cpp

"$(INTDIR)\DBForeignKey.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DBTable.cpp

"$(INTDIR)\DBTable.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DBView.cpp

"$(INTDIR)\DBView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FixDuplicateOption.cpp

"$(INTDIR)\FixDuplicateOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Format.cpp

"$(INTDIR)\Format.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HtmlKey.cpp

"$(INTDIR)\HtmlKey.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HtmlMonth.cpp

"$(INTDIR)\HtmlMonth.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HtmlWriter.cpp

"$(INTDIR)\HtmlWriter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HttpServerProperties.cpp

"$(INTDIR)\HttpServerProperties.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HttpServerVariable.cpp

"$(INTDIR)\HttpServerVariable.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HttpServerVariableEx.cpp

"$(INTDIR)\HttpServerVariableEx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MaintainDatabase.cpp

"$(INTDIR)\MaintainDatabase.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MIMECode.cpp

"$(INTDIR)\MIMECode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Module.cpp

"$(INTDIR)\Module.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Page.cpp

"$(INTDIR)\Page.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PersonSearcher.cpp

"$(INTDIR)\PersonSearcher.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Process.cpp

"$(INTDIR)\Process.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ProcessGroup.cpp

"$(INTDIR)\ProcessGroup.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Processor.cpp

"$(INTDIR)\Processor.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Properties.cpp

"$(INTDIR)\Properties.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RecordsetEx.cpp

"$(INTDIR)\RecordsetEx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Registry.cpp

"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegKey.cpp

"$(INTDIR)\RegKey.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportAwardsOption.cpp

"$(INTDIR)\ReportAwardsOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportClubRecordsOption.cpp

"$(INTDIR)\ReportClubRecordsOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportEventCalendarOption.cpp

"$(INTDIR)\ReportEventCalendarOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportFinancialHistoryOption.cpp

"$(INTDIR)\ReportFinancialHistoryOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportGroupsListOption.cpp

"$(INTDIR)\ReportGroupsListOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportParticipantHistoryOption.cpp

"$(INTDIR)\ReportParticipantHistoryOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportPersonOption.cpp

"$(INTDIR)\ReportPersonOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportResultsBySeriesOption.cpp

"$(INTDIR)\ReportResultsBySeriesOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportResultsOption.cpp

"$(INTDIR)\ReportResultsOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ReportRosterOption.cpp

"$(INTDIR)\ReportRosterOption.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RuleSubType.cpp

"$(INTDIR)\RuleSubType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RuleType.cpp

"$(INTDIR)\RuleType.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\stdafx.cpp

"$(INTDIR)\stdafx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StringLine.cpp

"$(INTDIR)\StringLine.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StringStream.cpp

"$(INTDIR)\StringStream.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Util.cpp

"$(INTDIR)\Util.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WebAthl.cpp

"$(INTDIR)\WebAthl.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WebAthl.RC

"$(INTDIR)\WebAthl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

