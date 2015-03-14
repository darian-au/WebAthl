ALTER TABLE Person ADD

	CONSTRAINT FK_Person_ContactPersonID 
	FOREIGN KEY (ContactPersonID) 
	REFERENCES Person (PersonID)
