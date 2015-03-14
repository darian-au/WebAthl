CREATE TABLE PreResults 
(
	SeriesID 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	PersonID 				int 			NOT NULL ,
	GroupIDSupposedTo 		int 			NULL ,
	DivisionSupposedTo 		int 			NULL ,
	GrossPerformanceHOUR 	int 			NULL ,
	GrossPerformanceMIN 	int 			NULL ,
	GrossPerformanceSEC 	real 			NULL ,
	Place 					int 			NULL ,
	AgeGroup 				int 			NULL ,
	ChestNumber 			varchar (60) 	NULL ,

	CONSTRAINT PK_PreResults PRIMARY KEY  
	(
		SeriesID,
		EventID,
		PersonID
	)
)
