CREATE TABLE EventRecordTemp 
(
	SeriesID 				int 			NOT NULL ,
	LocationID 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	EventTypeID				int 			NOT NULL ,
	Sex 					char (1)	 	NOT NULL ,
	AgeGroup 				int 			NOT NULL ,
	AgeCategory 			char (1)	 	NOT NULL ,
	PersonID 				int 			NOT NULL,
	ClubPerformanceHOUR 	int 			NULL ,
	ClubPerformanceMIN 		int 			NULL ,
	ClubPerformanceSEC 		real 			NULL ,

	CONSTRAINT PK_EventRecordTemp PRIMARY KEY  
	(
		SeriesID,
		LocationID,
		EventTypeID,
		Sex,
		AgeGroup,
		AgeCategory,
		PersonID
	)
)
