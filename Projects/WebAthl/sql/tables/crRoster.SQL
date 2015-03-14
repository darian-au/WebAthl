CREATE TABLE Roster 
(
	SeriesID 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	PersonID 				int 			NOT NULL ,
	TaskID 					int 			NOT NULL ,

	CONSTRAINT PK_Roster PRIMARY KEY  
	(
		SeriesID,
		EventID,
		PersonID
	)
)
