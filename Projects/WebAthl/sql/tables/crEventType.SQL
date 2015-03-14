CREATE TABLE EventType 
(
	EventTypeID 			int 			NOT NULL ,
	EventDescription 		varchar (60) 	NULL ,
	Timed 					int 			NOT NULL ,
	EventLength 			real 			NULL ,

	CONSTRAINT PK_EventType PRIMARY KEY  
	(
		EventTypeID
	)
)
