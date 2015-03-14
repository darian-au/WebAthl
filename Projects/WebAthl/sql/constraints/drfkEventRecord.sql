ALTER TABLE EventRecord DROP

	CONSTRAINT FK_EventRecord_SeriesID ,
	CONSTRAINT FK_EventRecord_EventTypeID ,
	CONSTRAINT FK_EventRecord_LocationID ,
	CONSTRAINT FK_EventRecord_PersonID ,
	CONSTRAINT FK_EventRecord_EventID 
