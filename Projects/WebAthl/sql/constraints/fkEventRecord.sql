ALTER TABLE EventRecord ADD

	CONSTRAINT FK_EventRecord_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_EventRecord_EventTypeID 
	FOREIGN KEY (EventTypeID) 
	REFERENCES EventType (EventTypeID),

	CONSTRAINT FK_EventRecord_LocationID 
	FOREIGN KEY (LocationID) 
	REFERENCES Location (LocationID),

	CONSTRAINT FK_EventRecord_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_EventRecord_EventID 
	FOREIGN KEY (EventID) 
	REFERENCES Event (EventID)
