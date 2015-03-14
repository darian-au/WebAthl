CREATE TABLE Groups 
(
	SeriesID 				int 			NOT NULL ,
	EventTypeID 			int 			NOT NULL ,
	GroupID 				int 			NOT NULL ,
	GroupRate 				real 			NULL ,
	GroupStart 				real  			NULL ,

	CONSTRAINT PK_Groups PRIMARY KEY  
	(
		SeriesID,
		EventTypeID,
		GroupID
	)
)
