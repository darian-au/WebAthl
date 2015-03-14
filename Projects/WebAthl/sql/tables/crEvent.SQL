CREATE TABLE Event 
(
	SeriesID 				int 			NOT NULL ,
	EventNo 				int 			NOT NULL ,
	EventID 				int 			NOT NULL ,
	LocationID 				int 			NOT NULL ,
	EventTypeID				int 			NOT NULL ,
	DateDAY 				int  			NULL ,
	DateMONTH 				int  			NULL ,
	DateYEAR 				int 			NULL ,
	PreEntryOpen			int 			NULL ,
	DateAgeDAY 				int  			NULL ,
	DateAgeMONTH 			int  			NULL ,
	DateAgeYEAR 			int 			NULL ,

	CONSTRAINT UQ_Event_EventID 
	UNIQUE (EventID),

	CONSTRAINT PK_Event PRIMARY KEY  
	(
		EventID,
		SeriesID,
		EventNo
	)
)
