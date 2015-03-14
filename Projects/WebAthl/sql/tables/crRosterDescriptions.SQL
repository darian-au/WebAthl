CREATE TABLE RosterDescriptions 
(
	TaskID 					int 			NOT NULL ,
	TaskDescription			varchar (60) 	NULL ,

	CONSTRAINT PK_RosterDescriptions PRIMARY KEY  
	(
		TaskID
	)
)
