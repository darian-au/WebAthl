CREATE TABLE Results 
(
	SeriesID 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	PersonID 				int 			NOT NULL ,
	DivisionActual 			int 			NULL ,
	AgeGroup 				int 			NULL ,
	GroupIDActual 			int 			NULL ,
	GroupStartActual		real 			NULL ,
	NewGroupID 				int 			NULL ,
	NewGroupMessage 		varchar (60) 	NULL ,
	GrossPerformanceHOUR 	int 			NULL ,
	GrossPerformanceMIN 	int 			NULL ,
	GrossPerformanceSEC 	real 			NULL ,
	NetPerformanceHOUR 		int 			NULL ,
	NetPerformanceMIN 		int 			NULL ,
	NetPerformanceSEC 		real 			NULL ,
	Place 					int 			NULL ,
	OverallPlace 			int 			NULL ,
	Percentile 				int 			NULL ,
	Points 					int 			NULL ,
	Eligible 				char (1)		NULL ,
	EventRate 				real 			NULL ,
	GroupRateActual 		real 			NULL ,
	ChestNumber 			varchar (60) 	NULL ,
	WorldStandard 			real 			NULL ,
	GroupIDSupposedTo		int 			NULL ,
	DivisionSupposedTo		int 			NULL ,
	OrgID					int				NULL ,

	CONSTRAINT PK_Results PRIMARY KEY  
	(
		SeriesID ,
		EventID ,
		PersonID
	)

)
