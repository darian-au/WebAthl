CREATE TABLE Financial 
(
	PersonID 				int 			NOT NULL ,
	DateRenewedDAY 			int  			NULL ,
	DateRenewedMONTH		int  			NULL ,
	DateRenewedYEAR			int  			NULL ,
	Year 					int				NOT NULL ,
	RegistrationID 			int				NULL ,
	RegistrationTypeID 		int				NOT NULL ,
	MailListFlag 			int				NOT NULL ,
	OrgID 					int 			NULL ,

	CONSTRAINT PK_Financial PRIMARY KEY  
	(
		PersonID,
		Year,
		RegistrationTypeID
	)
)
