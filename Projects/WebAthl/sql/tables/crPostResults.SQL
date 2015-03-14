CREATE TABLE PostResults 
(
	SeriesID 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	PersonID 				int 			NOT NULL ,
	GroupIDActual 			int 			NULL ,
	DivisionActual 			int 			NULL ,
	GrossPerformanceHOUR 	int 			NULL ,
	GrossPerformanceMIN 	int 			NULL ,
	GrossPerformanceSEC 	real 			NULL ,
	Place 					int 			NULL ,
	AgeGroup 				int 			NULL ,
	ChestNumber 			varchar (60) 	NULL ,
	NewGroupID 				int 			NULL ,
	NewGroupMessage 		varchar (60) 	NULL ,
	Points 					int 			NULL ,

	CONSTRAINT PK_PostResults PRIMARY KEY  
	(
		SeriesID,
		EventID,
		PersonID
	)
)
