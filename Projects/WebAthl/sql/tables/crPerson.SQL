CREATE TABLE Person 
(
	PersonID 				int 			NOT NULL ,
	LastName 				varchar (60) 	NULL ,
	FirstName 				varchar (60) 	NULL ,
	MiddleName 				varchar (60) 	NULL ,
	dobDAY 					int  			NULL ,
	dobMONTH 				int  			NULL ,
	dobYEAR 				int  			NULL ,
	Sex 					char (1)		NULL ,
	Address1 				varchar (100) 	NULL ,
	Address2 				varchar (100) 	NULL ,
	Town 					varchar (25) 	NULL ,
	State 					varchar (25) 	NULL ,
	Country 				varchar (25) 	NULL ,
	PostCode 				varchar (10) 	NULL ,
	PhoneHm 				varchar (15) 	NULL ,
	PhoneWk 				varchar (15) 	NULL ,
	Fax 					varchar (15) 	NULL ,
	Mobile 					varchar (15) 	NULL ,
	email 					varchar (100) 	NULL ,
	ContactPersonID			int 			NULL ,

	CONSTRAINT PK_Person PRIMARY KEY  
	(
		PersonID
	)
)
