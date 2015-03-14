ALTER TABLE SecurityPerson ADD

	CONSTRAINT FK_SecurityPerson_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_SecurityPerson_RoleID
	FOREIGN KEY (RoleID) 
	REFERENCES SecurityRole (RoleID)
