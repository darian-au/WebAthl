ALTER TABLE PostResults ADD

	CONSTRAINT FK_PostResults_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_PostResults_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_PostResults_EventID 
	FOREIGN KEY (EventID) 
	REFERENCES Event (EventID)
