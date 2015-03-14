CREATE TABLE Organisation 
(
	OrgID 					int 			NOT NULL ,
	OrgName 				varchar (60) 	NULL ,
	Address1 				varchar (100) 	NULL ,
	Address2 				varchar (100) 	NULL ,
	Town 					varchar (25) 	NULL ,
	State 					varchar (25) 	NULL ,
	Country 				varchar (25) 	NULL ,
	PostCode 				varchar (10) 	NULL ,
	Phone 					varchar (15) 	NULL ,
	Fax 					varchar (15) 	NULL ,
	Mobile 					varchar (15) 	NULL ,
	email 					varchar (100) 	NULL ,
	URL 					varchar (100) 	NULL ,
	RegistrarPersonID		int 			NULL ,
	AdministratorPersonID 	int 			NULL ,

	CONSTRAINT PK_Organisation PRIMARY KEY  
	(
		OrgID
	)
)
