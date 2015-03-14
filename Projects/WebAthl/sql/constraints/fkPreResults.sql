ALTER TABLE PreResults ADD

	CONSTRAINT FK_PreResults_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_PreResults_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_PreResults_EventID 
	FOREIGN KEY (EventID) 
	REFERENCES Event (EventID)
