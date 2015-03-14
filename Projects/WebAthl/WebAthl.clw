; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFinancialSet
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WebAthl.h"
LastPage=0

ClassCount=48

ResourceCount=0
Class1=CSecurityGroupDescSet
Class2=COrganisationSet
Class3=CSecurityPermTableSet
Class4=CSecurityPersonSet
Class5=CpostResultsSet
Class6=CSecurityGroupPermSet
Class7=CEventTypeSet
Class8=CFinancialSet
Class9=CGroupsSet
Class10=CLocationSet
Class11=CqReport
Class12=CParticipantForSeriesSet
Class13=CSecurityGroupSet
Class14=CEventETypLoc
Class15=CEventRecordSet
Class16=CRosterSet
Class17=CRosterDescriptionsSet
Class18=CpreResultsSet
Class19=CEventSet
Class20=CRosterNamesSet
Class21=CCountResults
Class22=CPersonSet
Class23=CResultsSet
Class24=CSeriesSet
Class25=CBoolResult
Class26=CRulesSet
Class27=CRuleTypeSet
Class28=CRuleSubTypeSet
Class29=CLaw
Class30=CWorldStandardSet
Class31=CValidate
Class32=CCountRules
Class33=CSeriesSeasonSet
Class34=CClubRecordsSet
Class35=CSecurityPersonSeriesSet
Class36=CParticipantHistorySet
Class37=CPersonFinancialSet
Class38=CEventTallySet
Class39=CbigReportSet
Class40=CGroupsReportSet
Class41=CParticipantDetailsSet
Class42=CPersonParticipantForSeriesSet
Class43=COptionsSet
Class44=CSeriesPersonPFSSet
Class45=CPersonCommentsSet
Class46=CRegistrationTypeSet
Class47=CResultsOrg
Class48=CEventRecord

[DB:CPersonSet]
DB=1
DBType=ODBC
ColumnCount=20
Column1=[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[dobDAY], 4, 4
Column6=[dobMONTH], 4, 4
Column7=[dobYEAR], 4, 4
Column8=[Sex], 1, 1
Column9=[Address1], 12, 100
Column10=[Address2], 12, 100
Column11=[Town], 12, 25
Column12=[State], 12, 25
Column13=[Country], 12, 25
Column14=[PostCode], 12, 10
Column15=[PhoneHm], 12, 15
Column16=[PhoneWk], 12, 15
Column17=[Fax], 12, 15
Column18=[Mobile], 12, 15
Column19=[email], 12, 60
Column20=[PartnerPersonID], 4, 4
Column21=[Mobile], 12, 15
Column22=[email], 12, 60
Column23=[PartnerPersonID], 4, 4

[DB:p2]
DB=1
DBType=ODBC
ColumnCount=21
Column1=[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[DOB], 11, 16
Column6=[SEX], 1, 1
Column7=[AgeGroup], 2, 5
Column8=[Age], 2, 5
Column9=[AgeCatergory], 1, 1
Column10=[Address1], 12, 100
Column11=[Address2], 12, 100
Column12=[Town], 12, 25
Column13=[State], 12, 25
Column14=[Country], 12, 25
Column15=[PostCode], 12, 10
Column16=[PhoneHm], 12, 15
Column17=[PhoneWk], 12, 15
Column18=[Fax], 12, 15
Column19=[Mobile], 12, 15
Column20=[email], 12, 60
Column21=[PartnerPersonID], 4, 4

[DB:COrg]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[OrgID], 4, 4
Column2=[OrgName], 12, 60
Column3=[Address1], 12, 100
Column4=[Address2], 12, 100
Column5=[Town], 12, 25
Column6=[State], 12, 25
Column7=[Country], 12, 25
Column8=[PostCode], 12, 10
Column9=[Phone], 12, 15
Column10=[Fax], 12, 15
Column11=[Mobile], 12, 15
Column12=[email], 12, 60
Column13=[URL], 12, 60
Column14=[RegistrarPersonID], 4, 4
Column15=[AdministratorPersonID], 4, 4

[DB:CPerson]
DB=1
DBType=ODBC
ColumnCount=21
Column1=[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[DOB], 11, 16
Column6=[SEX], 1, 1
Column7=[AgeGroup], 2, 5
Column8=[Age], 2, 5
Column9=[AgeCatergory], 1, 1
Column10=[Address1], 12, 100
Column11=[Address2], 12, 100
Column12=[Town], 12, 25
Column13=[State], 12, 25
Column14=[Country], 12, 25
Column15=[PostCode], 12, 10
Column16=[PhoneHm], 12, 15
Column17=[PhoneWk], 12, 15
Column18=[Fax], 12, 15
Column19=[Mobile], 12, 15
Column20=[email], 12, 60
Column21=[PartnerPersonID], 4, 4

[DB:COrgSet]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[OrgID], 4, 4
Column2=[OrgName], 12, 60
Column3=[Address1], 12, 100
Column4=[Address2], 12, 100
Column5=[Town], 12, 25
Column6=[State], 12, 25
Column7=[Country], 12, 25
Column8=[PostCode], 12, 10
Column9=[Phone], 12, 15
Column10=[Fax], 12, 15
Column11=[Mobile], 12, 15
Column12=[email], 12, 60
Column13=[URL], 12, 60
Column14=[RegistrarPersonID], 4, 4
Column15=[AdministratorPersonID], 4, 4

[DB:CResultsSet]
DB=1
DBType=ODBC
ColumnCount=26
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[DivisionActual], 4, 4
Column5=[AgeGroup], 4, 4
Column6=[GroupIDActual], 4, 4
Column7=[GroupStartActual], 7, 4
Column8=[NewGroupID], 4, 4
Column9=[NewGroupMessage], 12, 60
Column10=[GrossPerformanceHOUR], 4, 4
Column11=[GrossPerformanceMIN], 4, 4
Column12=[GrossPerformanceSEC], 7, 4
Column13=[NetPerformanceHOUR], 4, 4
Column14=[NetPerformanceMIN], 4, 4
Column15=[NetPerformanceSEC], 7, 4
Column16=[Place], 4, 4
Column17=[OverallPlace], 4, 4
Column18=[Percentile], 4, 4
Column19=[Points], 4, 4
Column20=[Eligible], 1, 1
Column21=[EventRate], 7, 4
Column22=[GroupRateActual], 7, 4
Column23=[ChestNumber], 12, 10
Column24=[WorldStandard], 7, 4
Column25=[GroupIDSupposedTo], 4, 4
Column26=[DivisionSupposedTo], 4, 4

[DB:Ctest]
DB=1
DBType=ODBC
ColumnCount=23
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[DivisionActual], 4, 4
Column5=[AgeGroup], 2, 5
Column6=[GroupIDActual], 4, 4
Column7=[GroupStartActual], 2, 15
Column8=[NewGroupID], 4, 4
Column9=[NewGroupMessage], 12, 60
Column10=[GrossPerformance], 2, 15
Column11=[NetPerformance], 2, 15
Column12=[Place], 4, 4
Column13=[OverallPlace], 4, 4
Column14=[Percentile], 4, 4
Column15=[Points], 4, 4
Column16=[Eligible], 1, 1
Column17=[EventRate], 2, 15
Column18=[GroupRateActual], 2, 15
Column19=[ChestNumber], 12, 10
Column20=[WorldStandard], 2, 8
Column21=[GroupIDSupposedTo], 4, 4
Column22=[DivisionSupposedTo], 4, 4
Column23=[darian], 7, 4

[CLS:CPersonSet]
Type=0
HeaderFile=PersonSet.h
ImplementationFile=PersonSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CPersonSet

[CLS:COrganisationSet]
Type=0
HeaderFile=OrganisationSet.h
ImplementationFile=OrganisationSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=COrganisationSet

[DB:COrganisationSet]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[OrgID], 4, 4
Column2=[OrgName], 12, 60
Column3=[Address1], 12, 100
Column4=[Address2], 12, 100
Column5=[Town], 12, 25
Column6=[State], 12, 25
Column7=[Country], 12, 25
Column8=[PostCode], 12, 10
Column9=[Phone], 12, 15
Column10=[Fax], 12, 15
Column11=[Mobile], 12, 15
Column12=[email], 12, 60
Column13=[URL], 12, 60
Column14=[RegistrarPersonID], 4, 4
Column15=[AdministratorPersonID], 4, 4

[DB:CConsistencyRules]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[EventsToCount], 4, 4
Column3=[EventsNoAgeChange], 4, 4
Column4=[RuleDescID], 4, 4

[DB:CEligibilityRules]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[EventsMissed], 4, 4
Column3=[EventsNeeded], 4, 4
Column4=[RuleDescID], 4, 4

[DB:CConsistencyRulesSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[EventsToCount], 4, 4
Column3=[EventsNoAgeChange], 4, 4
Column4=[RuleDescID], 4, 4

[DB:CEligibilityRulesSet]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SeriesID], 4, 4
Column2=[EligibilityRuleID], 4, 4
Column3=[EventsMissed], 4, 4
Column4=[EventsNeeded], 4, 4
Column5=[RuleDescID], 4, 4

[CLS:CEventSet]
Type=0
HeaderFile=EventSet.h
ImplementationFile=EventSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CEventSet

[DB:CEventSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[EventID], 4, 4
Column4=[LocationID], 4, 4
Column5=[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[NumOfParticipants], 4, 4
Column10=[FirstPersonID], 4, 4
Column11=[SecondPersonID], 4, 4
Column12=[ThirdPersonID], 4, 4
Column13=[BestWomanPersonID], 4, 4
Column14=[BestManPersonID], 4, 4
Column15=[OrganiserPersonID], 4, 4

[CLS:CEventRecordSet]
Type=0
HeaderFile=EventRecordSet.h
ImplementationFile=EventRecordSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CEventRecordSet

[DB:CEventRecordSet]
DB=1
DBType=ODBC
ColumnCount=11
Column1=[SeriesID], 4, 4
Column2=[LocationID], 4, 4
Column3=[EventID], 4, 4
Column4=[EventTypeID], 4, 4
Column5=[Sex], 1, 1
Column6=[AgeGroup], 4, 4
Column7=[AgeCategory], 1, 1
Column8=[PersonID], 4, 4
Column9=[ClubPerformanceHOUR], 4, 4
Column10=[ClubPerformanceMIN], 4, 4
Column11=[ClubPerformanceSEC], 7, 4
Column12=[StatePerformanceMIN], 4, 4
Column13=[StatePerformanceSEC], 7, 4
Column14=[NationalPerformanceHOUR], 4, 4
Column15=[NationalPerformanceMIN], 4, 4
Column16=[NationalPerformanceSEC], 7, 4
Column17=[WorldPerformanceHOUR], 4, 4
Column18=[WorldPerformanceMIN], 4, 4
Column19=[WorldPerformanceSEC], 7, 4

[CLS:CEventTypeSet]
Type=0
HeaderFile=EventTypeSet.h
ImplementationFile=EventTypeSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CEventTypeSet

[DB:CEventTypeSet]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[EventTypeID], 4, 4
Column2=[EventDescription], 12, 60
Column3=[Timed], -7, 1
Column4=[EventLength], 7, 4
Column5=[Difficulty], 4, 4

[CLS:CFinancialSet]
Type=0
HeaderFile=FinancialSet.h
ImplementationFile=FinancialSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CFinancialSet

[DB:CFinancialSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[PersonID], 4, 4
Column2=[DateRenewedDAY], 4, 4
Column3=[DateRenewedMONTH], 4, 4
Column4=[DateRenewedYEAR], 4, 4
Column5=[Year], 4, 4
Column6=[RegistrationID], 4, 4
Column7=[RegistrationSeason], 1, 1
Column8=[MailListFlag], -7, 1

[CLS:CGroupsSet]
Type=0
HeaderFile=GroupsSet.h
ImplementationFile=GroupsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CGroupsSet

[DB:CGroupsSet]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SeriesID], 4, 4
Column2=[EventTypeID], 4, 4
Column3=[GroupID], 4, 4
Column4=[GroupRate], 7, 4
Column5=[GroupStart], 7, 4

[CLS:CLocationSet]
Type=0
HeaderFile=LocationSet.h
ImplementationFile=LocationSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CLocationSet

[DB:CLocationSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[LocationID], 4, 4
Column2=[LocationDescription], 12, 60

[CLS:CSeriesSet]
Type=0
HeaderFile=SeriesSet.h
ImplementationFile=SeriesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSeriesSet

[DB:CSeriesSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[SeriesDescription], 12, 60
Column3=[Handicapped], -7, 1
Column4=[AgeCategory], 1, 1

[CLS:CParticipantForSeriesSet]
Type=0
HeaderFile=ParticipantForSeriesSet.h
ImplementationFile=ParticipantForSeriesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CParticipantForSeriesSet

[DB:CParticipantForSeriesSet]
DB=1
DBType=ODBC
ColumnCount=16
Column1=[SeriesID], 4, 4
Column2=[PersonID], 4, 4
Column3=[GroupIDSupposedTo], 4, 4
Column4=[DivisionSupposedTo], 4, 4
Column5=[Gold], 4, 4
Column6=[Silver], 4, 4
Column7=[Bronze], 4, 4
Column8=[ConsistencyAgeGroup], 4, 4
Column9=[ConsistencyEventsCurrent], 4, 4
Column10=[ConsistencyEventsOlder], 4, 4
Column11=[ConsistencyEventsRate], 7, 4
Column12=[EventsForSeason], 4, 4
Column13=[GrossPoints], 4, 4
Column14=[LowPoints], 4, 4
Column15=[NetPoints], 4, 4
Column16=[EligibilityForEvent], 1, 1

[DB:CPointsScoreRulesSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[MaxPoints], 4, 4
Column3=[PointsScale], 7, 4
Column4=[EventsToCount], 4, 4

[DB:CReGroupRulesSet]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[SeriesID], 4, 4
Column2=[ReGroupRuleID], 4, 4
Column3=[RuleDescID], 4, 4
Column4=[LastNoEvents], 4, 4
Column5=[Percentile], 4, 4
Column6=[MoveUP], -7, 1

[CLS:CResultsSet]
Type=0
HeaderFile=ResultsSet.h
ImplementationFile=ResultsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CResultsSet

[CLS:CRosterSet]
Type=0
HeaderFile=RosterSet.h
ImplementationFile=RosterSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRosterSet

[DB:CRosterSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[TaskID], 4, 4

[DB:CRosterDescriptions]
DB=1
DBType=ODBC
ColumnCount=0

[CLS:CRosterDescriptionsSet]
Type=0
HeaderFile=RosterDescriptionsSet.h
ImplementationFile=RosterDescriptionsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRosterDescriptionsSet

[DB:CRosterDescriptionsSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[TaskID], 4, 4
Column2=[TaskDescription], 12, 60

[DB:CTempClassSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[GroupIDActual], 4, 4
Column5=[DivisionActual], 4, 4
Column6=[GrossPerformance], 7, 4
Column7=[Place], 4, 4
Column8=[ChestNumber], 12, 10

[DB:CTempResultsSet]
DB=1
DBType=ODBC
ColumnCount=10
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[GroupIDActual], 4, 4
Column5=[DivisionActual], 4, 4
Column6=[GrossPerformanceHOUR], 4, 4
Column7=[GrossPerformanceMIN], 4, 4
Column8=[GrossPerformanceSEC], 7, 4
Column9=[Place], 4, 4
Column10=[ChestNumber], 12, 10

[CLS:CWorldStandardSet]
Type=0
HeaderFile=WorldStandardSet.h
ImplementationFile=WorldStandardSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CWorldStandardSet

[DB:CWorldStandardSet]
DB=1
DBType=ODBC
ColumnCount=9
Column1=[EventTypeID], 4, 4
Column2=[AgeGroup], 4, 4
Column3=[Sex], 1, 1
Column4=[AgeCategory], 1, 1
Column5=[RecCategory], 1, 1
Column6=[PerfHOUR], 4, 4
Column7=[PerfMIN], 4, 4
Column8=[PerfSEC], 7, 4
Column9=[PerfFactor], 7, 4
Column10=[StatePerformanceMIN], 4, 4
Column11=[StatePerformanceSEC], 7, 4
Column12=[NationalPerformanceHOUR], 4, 4
Column13=[NationalPerformanceMIN], 4, 4
Column14=[NationalPerformanceSEC], 7, 4
Column15=[WorldPerformanceHOUR], 4, 4
Column16=[WorldPerformanceMIN], 4, 4
Column17=[WorldPerformanceSEC], 7, 4

[DB:CLastEventForSeriesSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[SeriesID], 4, 4
Column2=[LastEventNo], 4, 4

[DB:CRuleDescriptions]
DB=1
DBType=ODBC
ColumnCount=0

[DB:CRuleDescriptionsSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[RuleDescID], 4, 4
Column2=[Description], 12, 60

[CLS:CSecurityGroupSet]
Type=0
HeaderFile=SecurityGroupSet.h
ImplementationFile=SecurityGroupSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityGroupSet

[DB:CSecurityGroupSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[PersonID], 4, 4
Column2=[SecurityGroupID], 4, 4

[CLS:CSecurityGroupDescSet]
Type=0
HeaderFile=SecurityGroupDescSet.h
ImplementationFile=SecurityGroupDescSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityGroupDescSet

[DB:CSecurityGroupDescSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[SecurityGroupID], 4, 4
Column2=[SecurityGroupName], 12, 60

[CLS:CSecurityGroupPermSet]
Type=0
HeaderFile=SecurityGroupPermSet.h
ImplementationFile=SecurityGroupPermSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityGroupPermSet

[DB:CSecurityGroupPermSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[SecurityGroupID], 4, 4
Column2=[PermissionTableID], 4, 4

[CLS:CSecurityPermTableSet]
Type=0
HeaderFile=SecurityPermTableSet.h
ImplementationFile=SecurityPermTableSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityPermTableSet

[DB:CSecurityPermTableSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[PermissionTableID], 4, 4
Column2=[TableName], 12, 60

[CLS:CSecurityPersonSet]
Type=0
HeaderFile=SecurityPersonSet.h
ImplementationFile=SecurityPersonSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityPersonSet

[DB:CSecurityPersonSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[PersonID], 4, 4
Column2=[LoginName], 12, 16
Column3=[Password], -3, 128

[DB:CPointScoreRulesSet]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SeriesID], 4, 4
Column2=[RuleDescID], 4, 4
Column3=[MaxPoints], 4, 4
Column4=[PointsScale], 4, 4
Column5=[EventsToCount], 4, 4

[CLS:CEventETypLoc]
Type=0
HeaderFile=EventETypLoc.h
ImplementationFile=EventETypLoc.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CEventETypLoc

[DB:CEventETypLoc]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[LocationID], 4, 4
Column2=[LocationDescription], 12, 60

[CLS:CRosterNamesSet]
Type=0
HeaderFile=RosterNamesSet.h
ImplementationFile=RosterNamesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRosterNamesSet

[DB:CRosterNamesSet]
DB=1
DBType=ODBC
ColumnCount=24
Column1=[dbo].[Person].[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[dobDAY], 4, 4
Column6=[dobMONTH], 4, 4
Column7=[dobYEAR], 4, 4
Column8=[Sex], 1, 1
Column9=[Address1], 12, 100
Column10=[Address2], 12, 100
Column11=[Town], 12, 25
Column12=[State], 12, 25
Column13=[Country], 12, 25
Column14=[PostCode], 12, 10
Column15=[PhoneHm], 12, 15
Column16=[PhoneWk], 12, 15
Column17=[Fax], 12, 15
Column18=[Mobile], 12, 15
Column19=[email], 12, 100
Column20=[PartnerPersonID], 4, 4
Column21=[SeriesID], 4, 4
Column22=[EventID], 4, 4
Column23=[dbo].[Roster].[PersonID], 4, 4
Column24=[TaskID], 4, 4

[CLS:CCountResults]
Type=0
HeaderFile=CountResults.h
ImplementationFile=CountResults.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CCountResults

[DB:CCountResults]
DB=1
DBType=ODBC
ColumnCount=26
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[DivisionActual], 4, 4
Column5=[AgeGroup], 4, 4
Column6=[GroupIDActual], 4, 4
Column7=[GroupStartActual], 7, 4
Column8=[NewGroupID], 4, 4
Column9=[NewGroupMessage], 12, 60
Column10=[GrossPerformanceHOUR], 4, 4
Column11=[GrossPerformanceMIN], 4, 4
Column12=[GrossPerformanceSEC], 7, 4
Column13=[NetPerformanceHOUR], 4, 4
Column14=[NetPerformanceMIN], 4, 4
Column15=[NetPerformanceSEC], 7, 4
Column16=[Place], 4, 4
Column17=[OverallPlace], 4, 4
Column18=[Percentile], 4, 4
Column19=[Points], 4, 4
Column20=[Eligible], 1, 1
Column21=[EventRate], 7, 4
Column22=[GroupRateActual], 7, 4
Column23=[ChestNumber], 12, 10
Column24=[WorldStandard], 7, 4
Column25=[GroupIDSupposedTo], 4, 4
Column26=[DivisionSupposedTo], 4, 4

[CLS:CpreResultsSet]
Type=0
HeaderFile=preResultsSet.h
ImplementationFile=preResultsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CpreResultsSet

[DB:CpreResultsSet]
DB=1
DBType=ODBC
ColumnCount=11
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[GroupIDSupposedTo], 4, 4
Column5=[DivisionSupposedTo], 4, 4
Column6=[GrossPerformanceHOUR], 4, 4
Column7=[GrossPerformanceMIN], 4, 4
Column8=[GrossPerformanceSEC], 7, 4
Column9=[Place], 4, 4
Column10=[AgeGroup], 4, 4
Column11=[ChestNumber], 12, 10

[CLS:CpostResultsSet]
Type=0
HeaderFile=postResultsSet.h
ImplementationFile=postResultsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CpostResultsSet

[DB:CpostResultsSet]
DB=1
DBType=ODBC
ColumnCount=11
Column1=[SeriesID], 4, 4
Column2=[EventID], 4, 4
Column3=[PersonID], 4, 4
Column4=[GroupIDActual], 4, 4
Column5=[DivisionActual], 4, 4
Column6=[GrossPerformanceHOUR], 4, 4
Column7=[GrossPerformanceMIN], 4, 4
Column8=[GrossPerformanceSEC], 7, 4
Column9=[Place], 4, 4
Column10=[AgeGroup], 4, 4
Column11=[ChestNumber], 12, 10

[CLS:CqReport]
Type=0
HeaderFile=qReport.h
ImplementationFile=qReport.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CqReport

[DB:CqReport]
DB=1
DBType=ODBC
ColumnCount=23
Column1=[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[dobDAY], 4, 4
Column6=[dobMONTH], 4, 4
Column7=[dobYEAR], 4, 4
Column8=[Sex], 1, 1
Column9=[AgeGroup], 4, 4
Column10=[Age], 4, 4
Column11=[AgeCategory], 1, 1
Column12=[Address1], 12, 100
Column13=[Address2], 12, 100
Column14=[Town], 12, 25
Column15=[State], 12, 25
Column16=[Country], 12, 25
Column17=[PostCode], 12, 10
Column18=[PhoneHm], 12, 15
Column19=[PhoneWk], 12, 15
Column20=[Fax], 12, 15
Column21=[Mobile], 12, 15
Column22=[email], 12, 60
Column23=[PartnerPersonID], 4, 4

[CLS:CRulesSet]
Type=0
HeaderFile=RulesSet.h
ImplementationFile=RulesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRulesSet

[DB:CRulesSet]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SeriesID], 4, 4
Column2=[RuleTypeID], 4, 4
Column3=[RuleSubTypeID], 4, 4
Column4=[RuleID], 4, 4
Column5=[Law], 4, 4

[CLS:CRuleTypeSet]
Type=0
HeaderFile=RuleTypeSet.h
ImplementationFile=RuleTypeSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CRuleTypeSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[RuleTypeID], 4, 4
Column2=[RuleTypeDescription], 12, 60

[CLS:CRuleSubTypeSet]
Type=0
HeaderFile=RuleSubTypeSet.h
ImplementationFile=RuleSubTypeSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CRuleSubTypeSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[RuleTypeID], 4, 4
Column2=[RuleSubTypeID], 4, 4
Column3=[RuleSubTypeDescription], 12, 60

[CLS:CLaw]
Type=0
HeaderFile=Law.h
ImplementationFile=Law.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CLaw

[DB:CLaw]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[RuleTypeID], 4, 4
Column2=[RuleSubTypeID], 4, 4
Column3=[RuleSubTypeDescription], 12, 60

[CLS:CBoolResult]
Type=0
HeaderFile=BoolResult.h
ImplementationFile=BoolResult.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CBoolResult

[DB:CBoolResult]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[EventTypeID], 4, 4
Column2=[EventDescription], 12, 60
Column3=[Timed], -7, 1
Column4=[EventLength], 4, 4
Column5=[Difficulty], 4, 4

[CLS:CValidate]
Type=0
HeaderFile=Validate.h
ImplementationFile=Validate.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CValidate

[DB:CValidate]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[PersonID], 4, 4
Column2=[SecurityGroupID], 4, 4

[CLS:CCountRules]
Type=0
HeaderFile=CountRules.h
ImplementationFile=CountRules.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CCountRules

[DB:CCountRules]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SeriesID], 4, 4
Column2=[RuleTypeID], 4, 4
Column3=[RuleSubTypeID], 4, 4
Column4=[RuleID], 4, 4
Column5=[Law], 4, 4

[CLS:CSeriesSeasonSet]
Type=0
HeaderFile=SeriesSeasonSet.h
ImplementationFile=SeriesSeasonSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSeriesSeasonSet

[DB:CSeriesSeasonSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[FirstEventForSeason], 4, 4
Column3=[EventsInSeason], 4, 4
Column4=[NextEventForProcess], 4, 4

[CLS:CClubRecordsSet]
Type=0
HeaderFile=ClubRecordsSet.h
ImplementationFile=ClubRecordsSet.cpp
BaseClass=CRecordset
Filter=N
LastObject=CClubRecordsSet
VirtualFilter=r

[DB:CClubRecordsSet]
DB=1
DBType=ODBC
ColumnCount=49
Column1=[dbo].[Event].[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[dbo].[Event].[EventID], 4, 4
Column4=[dbo].[Event].[LocationID], 4, 4
Column5=[dbo].[Event].[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[dbo].[EventRecord].[SeriesID], 4, 4
Column10=[dbo].[EventRecord].[LocationID], 4, 4
Column11=[dbo].[EventRecord].[EventID], 4, 4
Column12=[dbo].[EventRecord].[EventTypeID], 4, 4
Column13=[dbo].[EventRecord].[Sex], 1, 1
Column14=[AgeGroup], 4, 4
Column15=[dbo].[EventRecord].[AgeCategory], 1, 1
Column16=[dbo].[EventRecord].[PersonID], 4, 4
Column17=[ClubPerformanceHOUR], 4, 4
Column18=[ClubPerformanceMIN], 4, 4
Column19=[ClubPerformanceSEC], 7, 4
Column20=[dbo].[EventType].[EventTypeID], 4, 4
Column21=[EventDescription], 12, 60
Column22=[Timed], -7, 1
Column23=[EventLength], 4, 4
Column24=[dbo].[Location].[LocationID], 4, 4
Column25=[LocationDescription], 12, 60
Column26=[dbo].[Person].[PersonID], 4, 4
Column27=[LastName], 12, 60
Column28=[FirstName], 12, 60
Column29=[MiddleName], 12, 60
Column30=[dobDAY], 4, 4
Column31=[dobMONTH], 4, 4
Column32=[dobYEAR], 4, 4
Column33=[dbo].[Person].[Sex], 1, 1
Column34=[Address1], 12, 100
Column35=[Address2], 12, 100
Column36=[Town], 12, 25
Column37=[State], 12, 25
Column38=[Country], 12, 25
Column39=[PostCode], 12, 10
Column40=[PhoneHm], 12, 15
Column41=[PhoneWk], 12, 15
Column42=[Fax], 12, 15
Column43=[Mobile], 12, 15
Column44=[email], 12, 60
Column45=[PartnerPersonID], 4, 4
Column46=[dbo].[Series].[SeriesID], 4, 4
Column47=[SeriesDescription], 12, 60
Column48=[Handicapped], -7, 1
Column49=[dbo].[Series].[AgeCategory], 1, 1

[DB:CConsistencySet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[SeriesID], 4, 4
Column2=[SeriesDescription], 12, 60
Column3=[Handicapped], -7, 1
Column4=[AgeCategory], 1, 1

[CLS:CParticipantHistorySet]
Type=0
HeaderFile=ParticipantHistorySet.h
ImplementationFile=ParticipantHistorySet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CParticipantHistorySet

[DB:CParticipantHistorySet]
DB=1
DBType=ODBC
ColumnCount=64
Column1=[dbo].[Event].[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[dbo].[Event].[EventID], 4, 4
Column4=[dbo].[Event].[LocationID], 4, 4
Column5=[dbo].[Event].[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[dbo].[EventType].[EventTypeID], 4, 4
Column10=[EventDescription], 12, 60
Column11=[Timed], -7, 1
Column12=[EventLength], 4, 4
Column13=[dbo].[Location].[LocationID], 4, 4
Column14=[LocationDescription], 12, 60
Column15=[dbo].[Person].[PersonID], 4, 4
Column16=[LastName], 12, 60
Column17=[FirstName], 12, 60
Column18=[MiddleName], 12, 60
Column19=[dobDAY], 4, 4
Column20=[dobMONTH], 4, 4
Column21=[dobYEAR], 4, 4
Column22=[Sex], 1, 1
Column23=[Address1], 12, 100
Column24=[Address2], 12, 100
Column25=[Town], 12, 25
Column26=[State], 12, 25
Column27=[Country], 12, 25
Column28=[PostCode], 12, 10
Column29=[PhoneHm], 12, 15
Column30=[PhoneWk], 12, 15
Column31=[Fax], 12, 15
Column32=[Mobile], 12, 15
Column33=[email], 12, 60
Column34=[PartnerPersonID], 4, 4
Column35=[dbo].[Results].[SeriesID], 4, 4
Column36=[dbo].[Results].[EventID], 4, 4
Column37=[dbo].[Results].[PersonID], 4, 4
Column38=[DivisionActual], 4, 4
Column39=[AgeGroup], 4, 4
Column40=[GroupIDActual], 4, 4
Column41=[GroupStartActual], 7, 4
Column42=[NewGroupID], 4, 4
Column43=[NewGroupMessage], 12, 60
Column44=[GrossPerformanceHOUR], 4, 4
Column45=[GrossPerformanceMIN], 4, 4
Column46=[GrossPerformanceSEC], 7, 4
Column47=[NetPerformanceHOUR], 4, 4
Column48=[NetPerformanceMIN], 4, 4
Column49=[NetPerformanceSEC], 7, 4
Column50=[Place], 4, 4
Column51=[OverallPlace], 4, 4
Column52=[Percentile], 4, 4
Column53=[Points], 4, 4
Column54=[Eligible], 1, 1
Column55=[EventRate], 7, 4
Column56=[GroupRateActual], 7, 4
Column57=[ChestNumber], 12, 10
Column58=[WorldStandard], 7, 4
Column59=[GroupIDSupposedTo], 4, 4
Column60=[DivisionSupposedTo], 4, 4
Column61=[dbo].[Series].[SeriesID], 4, 4
Column62=[SeriesDescription], 12, 60
Column63=[Handicapped], -7, 1
Column64=[AgeCategory], 1, 1

[DB:CPointScoreSet]
DB=1
DBType=ODBC
ColumnCount=37
Column1=[dbo].[ParticipantForSeries].[SeriesID], 4, 4
Column2=[dbo].[ParticipantForSeries].[PersonID], 4, 4
Column3=[GroupIDSupposedTo], 4, 4
Column4=[DivisionSupposedTo], 4, 4
Column5=[ConsistencyAgeGroup], 4, 4
Column6=[ConsistencyEventsCurrent], 4, 4
Column7=[ConsistencyEventsOlder], 4, 4
Column8=[ConsistencyEventsRate], 7, 4
Column9=[EventsForSeason], 4, 4
Column10=[GrossPoints], 4, 4
Column11=[LowPoints], 4, 4
Column12=[NetPoints], 4, 4
Column13=[EligibilityForEvent], 1, 1
Column14=[dbo].[Person].[PersonID], 4, 4
Column15=[LastName], 12, 60
Column16=[FirstName], 12, 60
Column17=[MiddleName], 12, 60
Column18=[dobDAY], 4, 4
Column19=[dobMONTH], 4, 4
Column20=[dobYEAR], 4, 4
Column21=[Sex], 1, 1
Column22=[Address1], 12, 100
Column23=[Address2], 12, 100
Column24=[Town], 12, 25
Column25=[State], 12, 25
Column26=[Country], 12, 25
Column27=[PostCode], 12, 10
Column28=[PhoneHm], 12, 15
Column29=[PhoneWk], 12, 15
Column30=[Fax], 12, 15
Column31=[Mobile], 12, 15
Column32=[email], 12, 100
Column33=[PartnerPersonID], 4, 4
Column34=[dbo].[Series].[SeriesID], 4, 4
Column35=[SeriesDescription], 12, 60
Column36=[Handicapped], -7, 1
Column37=[AgeCategory], 1, 1

[CLS:CEventTallySet]
Type=0
HeaderFile=EventTallySet.h
ImplementationFile=EventTallySet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CEventTallySet]
DB=1
DBType=ODBC
ColumnCount=20
Column1=[PersonID], 4, 4
Column2=[LastName], 12, 60
Column3=[FirstName], 12, 60
Column4=[MiddleName], 12, 60
Column5=[dobDAY], 4, 4
Column6=[dobMONTH], 4, 4
Column7=[dobYEAR], 4, 4
Column8=[Sex], 1, 1
Column9=[Address1], 12, 100
Column10=[Address2], 12, 100
Column11=[Town], 12, 25
Column12=[State], 12, 25
Column13=[Country], 12, 25
Column14=[PostCode], 12, 10
Column15=[PhoneHm], 12, 15
Column16=[PhoneWk], 12, 15
Column17=[Fax], 12, 15
Column18=[Mobile], 12, 15
Column19=[email], 12, 60
Column20=[PartnerPersonID], 4, 4

[CLS:CbigReportSet]
Type=0
HeaderFile=bigReportSet.h
ImplementationFile=bigReportSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CbigReportSet

[DB:CbigReportSet]
DB=1
DBType=ODBC
ColumnCount=43
Column1=[dbo].[Event].[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[EventID], 4, 4
Column4=[dbo].[Event].[LocationID], 4, 4
Column5=[dbo].[Event].[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[dbo].[EventType].[EventTypeID], 4, 4
Column10=[EventDescription], 12, 60
Column11=[Timed], -7, 1
Column12=[EventLength], 4, 4
Column13=[dbo].[Groups].[SeriesID], 4, 4
Column14=[dbo].[Groups].[EventTypeID], 4, 4
Column15=[GroupID], 4, 4
Column16=[GroupRate], 7, 4
Column17=[GroupStart], 7, 4
Column18=[dbo].[Location].[LocationID], 4, 4
Column19=[LocationDescription], 12, 60
Column20=[PersonID], 4, 4
Column21=[LastName], 12, 60
Column22=[FirstName], 12, 60
Column23=[MiddleName], 12, 60
Column24=[dobDAY], 4, 4
Column25=[dobMONTH], 4, 4
Column26=[dobYEAR], 4, 4
Column27=[Sex], 1, 1
Column28=[Address1], 12, 100
Column29=[Address2], 12, 100
Column30=[Town], 12, 25
Column31=[State], 12, 25
Column32=[Country], 12, 25
Column33=[PostCode], 12, 10
Column34=[PhoneHm], 12, 15
Column35=[PhoneWk], 12, 15
Column36=[Fax], 12, 15
Column37=[Mobile], 12, 15
Column38=[email], 12, 60
Column39=[PartnerPersonID], 4, 4
Column40=[dbo].[Series].[SeriesID], 4, 4
Column41=[SeriesDescription], 12, 60
Column42=[Handicapped], -7, 1
Column43=[AgeCategory], 1, 1

[CLS:CGroupsReportSet]
Type=0
HeaderFile=GroupsReportSet.h
ImplementationFile=GroupsReportSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CGroupsReportSet

[DB:CGroupsReportSet]
DB=1
DBType=ODBC
ColumnCount=56
Column1=[dbo].[Event].[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[EventID], 4, 4
Column4=[dbo].[Event].[LocationID], 4, 4
Column5=[dbo].[Event].[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[dbo].[EventType].[EventTypeID], 4, 4
Column10=[EventDescription], 12, 60
Column11=[Timed], -7, 1
Column12=[EventLength], 4, 4
Column13=[dbo].[Groups].[SeriesID], 4, 4
Column14=[dbo].[Groups].[EventTypeID], 4, 4
Column15=[GroupID], 4, 4
Column16=[GroupRate], 7, 4
Column17=[GroupStart], 7, 4
Column18=[dbo].[Location].[LocationID], 4, 4
Column19=[LocationDescription], 12, 60
Column20=[dbo].[ParticipantForSeries].[SeriesID], 4, 4
Column21=[dbo].[ParticipantForSeries].[PersonID], 4, 4
Column22=[GroupIDSupposedTo], 4, 4
Column23=[DivisionSupposedTo], 4, 4
Column24=[ConsistencyAgeGroup], 4, 4
Column25=[ConsistencyEventsCurrent], 4, 4
Column26=[ConsistencyEventsOlder], 4, 4
Column27=[ConsistencyEventsRate], 7, 4
Column28=[EventsForSeason], 4, 4
Column29=[GrossPoints], 4, 4
Column30=[LowPoints], 4, 4
Column31=[NetPoints], 4, 4
Column32=[EligibilityForEvent], 1, 1
Column33=[dbo].[Person].[PersonID], 4, 4
Column34=[LastName], 12, 60
Column35=[FirstName], 12, 60
Column36=[MiddleName], 12, 60
Column37=[dobDAY], 4, 4
Column38=[dobMONTH], 4, 4
Column39=[dobYEAR], 4, 4
Column40=[Sex], 1, 1
Column41=[Address1], 12, 100
Column42=[Address2], 12, 100
Column43=[Town], 12, 25
Column44=[State], 12, 25
Column45=[Country], 12, 25
Column46=[PostCode], 12, 10
Column47=[PhoneHm], 12, 15
Column48=[PhoneWk], 12, 15
Column49=[Fax], 12, 15
Column50=[Mobile], 12, 15
Column51=[email], 12, 60
Column52=[PartnerPersonID], 4, 4
Column53=[dbo].[Series].[SeriesID], 4, 4
Column54=[SeriesDescription], 12, 60
Column55=[Handicapped], -7, 1
Column56=[AgeCategory], 1, 1

[CLS:CParticipantDetailsSet]
Type=0
HeaderFile=ParticipantDetailsSet.h
ImplementationFile=ParticipantDetailsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CParticipantDetailsSet

[DB:CParticipantDetailsSet]
DB=1
DBType=ODBC
ColumnCount=37
Column1=[dbo].[ParticipantForSeries].[SeriesID], 4, 4
Column2=[dbo].[ParticipantForSeries].[PersonID], 4, 4
Column3=[GroupIDSupposedTo], 4, 4
Column4=[DivisionSupposedTo], 4, 4
Column5=[ConsistencyAgeGroup], 4, 4
Column6=[ConsistencyEventsCurrent], 4, 4
Column7=[ConsistencyEventsOlder], 4, 4
Column8=[ConsistencyEventsRate], 7, 4
Column9=[EventsForSeason], 4, 4
Column10=[GrossPoints], 4, 4
Column11=[LowPoints], 4, 4
Column12=[NetPoints], 4, 4
Column13=[EligibilityForEvent], 1, 1
Column14=[dbo].[Person].[PersonID], 4, 4
Column15=[LastName], 12, 60
Column16=[FirstName], 12, 60
Column17=[MiddleName], 12, 60
Column18=[dobDAY], 4, 4
Column19=[dobMONTH], 4, 4
Column20=[dobYEAR], 4, 4
Column21=[Sex], 1, 1
Column22=[Address1], 12, 100
Column23=[Address2], 12, 100
Column24=[Town], 12, 25
Column25=[State], 12, 25
Column26=[Country], 12, 25
Column27=[PostCode], 12, 10
Column28=[PhoneHm], 12, 15
Column29=[PhoneWk], 12, 15
Column30=[Fax], 12, 15
Column31=[Mobile], 12, 15
Column32=[email], 12, 60
Column33=[PartnerPersonID], 4, 4
Column34=[dbo].[Series].[SeriesID], 4, 4
Column35=[SeriesDescription], 12, 60
Column36=[Handicapped], -7, 1
Column37=[AgeCategory], 1, 1

[CLS:CPersonParticipantForSeriesSet]
Type=0
HeaderFile=PersonParticipantForSeriesSet.h
ImplementationFile=PersonParticipantForSeriesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CPersonParticipantForSeriesSet

[DB:CPersonParticipantForSeriesSet]
DB=1
DBType=ODBC
ColumnCount=33
Column1=[SeriesID], 4, 4
Column2=[dbo].[ParticipantForSeries].[PersonID], 4, 4
Column3=[GroupIDSupposedTo], 4, 4
Column4=[DivisionSupposedTo], 4, 4
Column5=[ConsistencyAgeGroup], 4, 4
Column6=[ConsistencyEventsCurrent], 4, 4
Column7=[ConsistencyEventsOlder], 4, 4
Column8=[ConsistencyEventsRate], 7, 4
Column9=[EventsForSeason], 4, 4
Column10=[GrossPoints], 4, 4
Column11=[LowPoints], 4, 4
Column12=[NetPoints], 4, 4
Column13=[EligibilityForEvent], 1, 1
Column14=[dbo].[Person].[PersonID], 4, 4
Column15=[LastName], 12, 60
Column16=[FirstName], 12, 60
Column17=[MiddleName], 12, 60
Column18=[dobDAY], 4, 4
Column19=[dobMONTH], 4, 4
Column20=[dobYEAR], 4, 4
Column21=[Sex], 1, 1
Column22=[Address1], 12, 100
Column23=[Address2], 12, 100
Column24=[Town], 12, 25
Column25=[State], 12, 25
Column26=[Country], 12, 25
Column27=[PostCode], 12, 10
Column28=[PhoneHm], 12, 15
Column29=[PhoneWk], 12, 15
Column30=[Fax], 12, 15
Column31=[Mobile], 12, 15
Column32=[email], 12, 60
Column33=[PartnerPersonID], 4, 4

[CLS:COptionsSet]
Type=0
HeaderFile=OptionsSet.h
ImplementationFile=OptionsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=COptionsSet

[DB:COptionsSet]
DB=1
DBType=ODBC
ColumnCount=19
Column1=[OrgID], 4, 4
Column2=[AgeGroup_MaxJunior], 4, 4
Column3=[AgeGroup_JuniorGroup], 4, 4
Column4=[AgeGroup_MinVeteran], 4, 4
Column5=[AgeGroup_VeteranGroup], 4, 4
Column6=[Season_WinterStart], 4, 4
Column7=[Season_WinterStop], 4, 4
Column8=[Season_SummerStart], 4, 4
Column9=[Season_SummerStop], 4, 4
Column10=[Season_YearLongrStart], 4, 4
Column11=[Season_YearLongStop], 4, 4
Column12=[MailList_Spacing], 4, 4
Column13=[Processing_TimeOut], 4, 4
Column14=[Appearance_Font], 12, 50
Column15=[Appearance_bgColor], 12, 50
Column16=[Appearance_menuColor], 12, 50
Column17=[Appearance_Logo], 12, 50
Column18=[Appearance_bgPic], 12, 50
Column19=[Appearance_menuPic], 12, 50

[CLS:CSecurityPersonSeriesSet]
Type=0
HeaderFile=SecurityPersonSeriesSet.h
ImplementationFile=SecurityPersonSeriesSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSecurityPersonSeriesSet

[DB:CSecurityPersonSeriesSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[PersonID], 4, 4
Column2=[SeriesID], 4, 4

[DB:CPersonFinancial]
DB=1
DBType=ODBC
ColumnCount=28
Column1=[dbo].[Financial].[PersonID], 4, 4
Column2=[DateRenewedDAY], 4, 4
Column3=[DateRenewedMONTH], 4, 4
Column4=[DateRenewedYEAR], 4, 4
Column5=[Year], 4, 4
Column6=[RegistrationID], 4, 4
Column7=[RegistrationSeason], 1, 1
Column8=[MailListFlag], -7, 1
Column9=[dbo].[Person].[PersonID], 4, 4
Column10=[LastName], 12, 60
Column11=[FirstName], 12, 60
Column12=[MiddleName], 12, 60
Column13=[dobDAY], 4, 4
Column14=[dobMONTH], 4, 4
Column15=[dobYEAR], 4, 4
Column16=[Sex], 1, 1
Column17=[Address1], 12, 100
Column18=[Address2], 12, 100
Column19=[Town], 12, 25
Column20=[State], 12, 25
Column21=[Country], 12, 25
Column22=[PostCode], 12, 10
Column23=[PhoneHm], 12, 15
Column24=[PhoneWk], 12, 15
Column25=[Fax], 12, 15
Column26=[Mobile], 12, 15
Column27=[email], 12, 100
Column28=[PartnerPersonID], 4, 4

[CLS:CPersonFinancialSet]
Type=0
HeaderFile=PersonFinancialSet.h
ImplementationFile=PersonFinancialSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CPersonFinancialSet

[DB:CPersonFinancialSet]
DB=1
DBType=ODBC
ColumnCount=28
Column1=[dbo].[Financial].[PersonID], 4, 4
Column2=[DateRenewedDAY], 4, 4
Column3=[DateRenewedMONTH], 4, 4
Column4=[DateRenewedYEAR], 4, 4
Column5=[Year], 4, 4
Column6=[RegistrationID], 4, 4
Column7=[RegistrationSeason], 1, 1
Column8=[MailListFlag], -7, 1
Column9=[dbo].[Person].[PersonID], 4, 4
Column10=[LastName], 12, 60
Column11=[FirstName], 12, 60
Column12=[MiddleName], 12, 60
Column13=[dobDAY], 4, 4
Column14=[dobMONTH], 4, 4
Column15=[dobYEAR], 4, 4
Column16=[Sex], 1, 1
Column17=[Address1], 12, 100
Column18=[Address2], 12, 100
Column19=[Town], 12, 25
Column20=[State], 12, 25
Column21=[Country], 12, 25
Column22=[PostCode], 12, 10
Column23=[PhoneHm], 12, 15
Column24=[PhoneWk], 12, 15
Column25=[Fax], 12, 15
Column26=[Mobile], 12, 15
Column27=[email], 12, 100
Column28=[PartnerPersonID], 4, 4

[CLS:CSeriesPersonPFSSet]
Type=0
HeaderFile=SeriesPersonPFSSet.h
ImplementationFile=SeriesPersonPFSSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSeriesPersonPFSSet

[DB:CSeriesPersonPFSSet]
DB=1
DBType=ODBC
ColumnCount=37
Column1=[dbo].[ParticipantForSeries].[SeriesID], 4, 4
Column2=[dbo].[ParticipantForSeries].[PersonID], 4, 4
Column3=[GroupIDSupposedTo], 4, 4
Column4=[DivisionSupposedTo], 4, 4
Column5=[ConsistencyAgeGroup], 4, 4
Column6=[ConsistencyEventsCurrent], 4, 4
Column7=[ConsistencyEventsOlder], 4, 4
Column8=[ConsistencyEventsRate], 7, 4
Column9=[EventsForSeason], 4, 4
Column10=[GrossPoints], 4, 4
Column11=[LowPoints], 4, 4
Column12=[NetPoints], 4, 4
Column13=[EligibilityForEvent], 1, 1
Column14=[dbo].[Person].[PersonID], 4, 4
Column15=[LastName], 12, 60
Column16=[FirstName], 12, 60
Column17=[MiddleName], 12, 60
Column18=[dobDAY], 4, 4
Column19=[dobMONTH], 4, 4
Column20=[dobYEAR], 4, 4
Column21=[Sex], 1, 1
Column22=[Address1], 12, 100
Column23=[Address2], 12, 100
Column24=[Town], 12, 25
Column25=[State], 12, 25
Column26=[Country], 12, 25
Column27=[PostCode], 12, 10
Column28=[PhoneHm], 12, 15
Column29=[PhoneWk], 12, 15
Column30=[Fax], 12, 15
Column31=[Mobile], 12, 15
Column32=[email], 12, 100
Column33=[PartnerPersonID], 4, 4
Column34=[dbo].[Series].[SeriesID], 4, 4
Column35=[SeriesDescription], 12, 60
Column36=[Handicapped], -7, 1
Column37=[AgeCategory], 1, 1

[CLS:CPersonCommentsSet]
Type=0
HeaderFile=PersonCommentsSet.h
ImplementationFile=PersonCommentsSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CPersonCommentsSet

[DB:CPersonCommentsSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[PersonID], 4, 4
Column2=[CommentNo], 4, 4
Column3=[Comment], 12, 100

[CLS:CRegistrationTypeSet]
Type=0
HeaderFile=RegistrationTypeSet.h
ImplementationFile=RegistrationTypeSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRegistrationTypeSet

[DB:CRegistrationTypeSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[RegistrationTypeID], 4, 4
Column2=[Description], 12, 60
Column3=[MonthStart], 4, 4
Column4=[MonthStop], 4, 4

[CLS:CResultsOrg]
Type=0
HeaderFile=ResultsOrg.h
ImplementationFile=ResultsOrg.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CResultsOrg

[DB:CResultsOrg]
DB=1
DBType=ODBC
ColumnCount=93
Column1=[dbo].[Event].[SeriesID], 4, 4
Column2=[EventNo], 4, 4
Column3=[dbo].[Event].[EventID], 4, 4
Column4=[dbo].[Event].[LocationID], 4, 4
Column5=[dbo].[Event].[EventTypeID], 4, 4
Column6=[DateDAY], 4, 4
Column7=[DateMONTH], 4, 4
Column8=[DateYEAR], 4, 4
Column9=[dbo].[EventType].[EventTypeID], 4, 4
Column10=[EventDescription], 12, 60
Column11=[Timed], 4, 4
Column12=[EventLength], 7, 4
Column13=[dbo].[Financial].[PersonID], 4, 4
Column14=[DateRenewedDAY], 4, 4
Column15=[DateRenewedMONTH], 4, 4
Column16=[DateRenewedYEAR], 4, 4
Column17=[Year], 4, 4
Column18=[RegistrationID], 4, 4
Column19=[RegistrationSeason], 4, 4
Column20=[MailListFlag], -7, 1
Column21=[dbo].[Financial].[OrgID], 4, 4
Column22=[dbo].[Groups].[SeriesID], 4, 4
Column23=[dbo].[Groups].[EventTypeID], 4, 4
Column24=[GroupID], 4, 4
Column25=[GroupRate], 7, 4
Column26=[GroupStart], 7, 4
Column27=[dbo].[Location].[LocationID], 4, 4
Column28=[LocationDescription], 12, 60
Column29=[dbo].[Organisation].[OrgID], 4, 4
Column30=[OrgName], 12, 60
Column31=[dbo].[Organisation].[Address1], 12, 100
Column32=[dbo].[Organisation].[Address2], 12, 100
Column33=[dbo].[Organisation].[Town], 12, 25
Column34=[dbo].[Organisation].[State], 12, 25
Column35=[dbo].[Organisation].[Country], 12, 25
Column36=[dbo].[Organisation].[PostCode], 12, 10
Column37=[Phone], 12, 15
Column38=[dbo].[Organisation].[Fax], 12, 15
Column39=[dbo].[Organisation].[Mobile], 12, 15
Column40=[dbo].[Organisation].[email], 12, 100
Column41=[URL], 12, 100
Column42=[RegistrarPersonID], 4, 4
Column43=[AdministratorPersonID], 4, 4
Column44=[dbo].[Person].[PersonID], 4, 4
Column45=[LastName], 12, 60
Column46=[FirstName], 12, 60
Column47=[MiddleName], 12, 60
Column48=[dobDAY], 4, 4
Column49=[dobMONTH], 4, 4
Column50=[dobYEAR], 4, 4
Column51=[Sex], 1, 1
Column52=[dbo].[Person].[Address1], 12, 100
Column53=[dbo].[Person].[Address2], 12, 100
Column54=[dbo].[Person].[Town], 12, 25
Column55=[dbo].[Person].[State], 12, 25
Column56=[dbo].[Person].[Country], 12, 25
Column57=[dbo].[Person].[PostCode], 12, 10
Column58=[PhoneHm], 12, 15
Column59=[PhoneWk], 12, 15
Column60=[dbo].[Person].[Fax], 12, 15
Column61=[dbo].[Person].[Mobile], 12, 15
Column62=[dbo].[Person].[email], 12, 100
Column63=[PartnerPersonID], 4, 4
Column64=[dbo].[Results].[SeriesID], 4, 4
Column65=[dbo].[Results].[EventID], 4, 4
Column66=[dbo].[Results].[PersonID], 4, 4
Column67=[DivisionActual], 4, 4
Column68=[AgeGroup], 4, 4
Column69=[GroupIDActual], 4, 4
Column70=[GroupStartActual], 7, 4
Column71=[NewGroupID], 4, 4
Column72=[NewGroupMessage], 12, 60
Column73=[GrossPerformanceHOUR], 4, 4
Column74=[GrossPerformanceMIN], 4, 4
Column75=[GrossPerformanceSEC], 7, 4
Column76=[NetPerformanceHOUR], 4, 4
Column77=[NetPerformanceMIN], 4, 4
Column78=[NetPerformanceSEC], 7, 4
Column79=[Place], 4, 4
Column80=[OverallPlace], 4, 4
Column81=[Percentile], 4, 4
Column82=[Points], 4, 4
Column83=[Eligible], 1, 1
Column84=[EventRate], 7, 4
Column85=[GroupRateActual], 7, 4
Column86=[ChestNumber], 12, 10
Column87=[WorldStandard], 7, 4
Column88=[GroupIDSupposedTo], 4, 4
Column89=[DivisionSupposedTo], 4, 4
Column90=[dbo].[Series].[SeriesID], 4, 4
Column91=[SeriesDescription], 12, 60
Column92=[Handicapped], -7, 1
Column93=[AgeCategory], 1, 1

[CLS:CEventRecord]
Type=0
HeaderFile=EventRecord.h
ImplementationFile=EventRecord.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CEventRecord

[DB:CEventRecord]
DB=1
DBType=ODBC
ColumnCount=11
Column1=[SeriesID], 4, 4
Column2=[LocationID], 4, 4
Column3=[EventID], 4, 4
Column4=[EventTypeID], 4, 4
Column5=[Sex], 1, 1
Column6=[AgeGroup], 4, 4
Column7=[AgeCategory], 1, 1
Column8=[PersonID], 4, 4
Column9=[ClubPerformanceHOUR], 4, 4
Column10=[ClubPerformanceMIN], 4, 4
Column11=[ClubPerformanceSEC], 7, 4

