CREATE TABLE RegistrationType 
(
	RegistrationTypeID		int 			NOT NULL ,
	RegistrationDescription varchar (60) 	NULL ,
	MonthStart				int				NULL ,
	MonthStop				int				NULL ,

	CONSTRAINT PK_RegistrationType PRIMARY KEY  
	(
		RegistrationTypeID 
	)
)
