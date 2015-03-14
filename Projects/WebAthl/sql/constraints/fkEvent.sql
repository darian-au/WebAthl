ALTER TABLE Event ADD

	CONSTRAINT FK_Event_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_Event_EventTypeID 
	FOREIGN KEY (EventTypeID) 
	REFERENCES EventType (EventTypeID),

	CONSTRAINT FK_Event_LocationID 
	FOREIGN KEY (LocationID) 
	REFERENCES Location (LocationID)
