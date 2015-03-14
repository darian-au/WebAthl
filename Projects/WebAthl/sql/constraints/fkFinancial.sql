ALTER TABLE Financial ADD

	CONSTRAINT FK_Financial_OrgID 
	FOREIGN KEY (OrgID) 
	REFERENCES Organisation (OrgID),

	CONSTRAINT FK_Financial_PersonID 
	FOREIGN KEY (PersonID) 
	REFERENCES Person (PersonID),

	CONSTRAINT FK_Financial_RegistrationTypeID 
	FOREIGN KEY (RegistrationTypeID) 
	REFERENCES RegistrationType (RegistrationTypeID)
