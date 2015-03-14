CREATE TABLE ParticipantForSeries 
(
	SeriesID 				int 			NOT NULL ,
	PersonID 				int 			NOT NULL ,
	GroupIDSupposedTo		int 			NULL ,
	DivisionSupposedTo 		int 			NULL ,
	ConsistencyAgeGroup 	int 			NULL ,
	ConsistencyEventsCurrent int 			NULL ,
	ConsistencyEventsOlder 	int 			NULL ,
	ConsistencyEventsRate 	real 			NULL ,
	EventsForSeason 		int 			NULL ,
	GrossPoints 			int 			NULL ,
	LowPoints 				int 			NULL ,
	NetPoints 				int 			NULL ,
	EligibilityForEvent 	varchar (60) 	NULL ,
	OrgID					int				NULL ,
	EventsForSeries 		int 			NULL ,
	ConsistencyAgeStandard 	real 			NULL ,

	CONSTRAINT PK_ParticipantForSeries PRIMARY KEY  
	(
		SeriesID,
		PersonID
	)
)
