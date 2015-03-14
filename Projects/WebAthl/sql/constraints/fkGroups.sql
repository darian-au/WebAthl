ALTER TABLE Groups ADD

	CONSTRAINT FK_Groups_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_Groups_EventTypeID 
	FOREIGN KEY (EventTypeID) 
	REFERENCES EventType (EventTypeID)
