ALTER TABLE Roster ADD

	CONSTRAINT FK_Roster_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_Roster_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_Roster_TaskID
	FOREIGN KEY (TaskID) 
	REFERENCES RosterDescriptions (TaskID),

	CONSTRAINT FK_Roster_EventID 
	FOREIGN KEY (EventID) 
	REFERENCES Event (EventID)
