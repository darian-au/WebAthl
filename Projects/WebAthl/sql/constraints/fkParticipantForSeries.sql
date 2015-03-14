ALTER TABLE ParticipantForSeries ADD

	CONSTRAINT FK_ParticipantForSeries_SeriesID 
	FOREIGN KEY (SeriesID) 
	REFERENCES Series (SeriesID),

	CONSTRAINT FK_ParticipantForSeries_OrgID 
	FOREIGN KEY (OrgID) 
	REFERENCES Organisation (OrgID),

	CONSTRAINT FK_ParticipantForSeries_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID)
