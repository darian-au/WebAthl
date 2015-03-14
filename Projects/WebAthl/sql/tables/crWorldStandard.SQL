CREATE TABLE WorldStandard 
(
	EventTypeID 			int 			NOT NULL ,
	AgeGroup 				int 			NOT NULL ,
	Sex 					char (1)		NOT NULL ,
	AgeCategory 			char (1)		NOT NULL ,
	RecCategory 			char (1)		NOT NULL ,
	PerfHOUR 				int 			NULL ,
	PerfMIN 				int 			NULL ,
	PerfSEC 				real 			NULL ,
	PerfFactor 				real 			NULL ,

	CONSTRAINT PK_WorldStandard PRIMARY KEY  
	(
		EventTypeID,
		AgeGroup,
		Sex,
		AgeCategory,
		RecCategory 
	)
)
