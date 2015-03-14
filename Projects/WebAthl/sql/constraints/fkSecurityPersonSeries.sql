ALTER TABLE SecurityPersonSeries ADD

	CONSTRAINT FK_SecurityPersonSeries_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_SecurityPersonSeries_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID)
