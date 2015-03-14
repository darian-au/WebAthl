CREATE TABLE SeriesSeason 
(
	SeriesID 				int 			NOT NULL ,
	FirstEventForSeason 	int 			NULL ,
	EventsInSeason 			int 			NULL ,
	NextEventForProcess 	int 			NULL ,

	CONSTRAINT PK_SeriesSeason PRIMARY KEY  
	(
		SeriesID
	)
)
