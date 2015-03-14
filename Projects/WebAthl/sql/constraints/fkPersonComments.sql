ALTER TABLE PersonComments ADD

	CONSTRAINT FK_PersonComments_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID)
