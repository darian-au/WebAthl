ALTER TABLE Results ADD

	CONSTRAINT FK_Results_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_Results_OrgID 
	FOREIGN KEY (OrgID) 
	REFERENCES Organisation (OrgID),

	CONSTRAINT FK_Results_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_Results_EventID 
	FOREIGN KEY (EventID) 
	REFERENCES Event (EventID)
