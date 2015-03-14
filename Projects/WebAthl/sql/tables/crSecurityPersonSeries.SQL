CREATE TABLE SecurityPersonSeries 
(
	PersonID 				int 			NOT NULL ,
	SeriesID 				int 			NOT NULL ,

	CONSTRAINT PK_SecurityPersonSeries PRIMARY KEY  
	(
		PersonID,
		SeriesID
	)
)
