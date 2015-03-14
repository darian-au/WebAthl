CREATE TABLE SecurityPerson 
(
	PersonID 				int 			NOT NULL ,
	LoginName 				varchar (16)  	NULL ,
	Password 				varbinary (255) NULL ,
	RoleID					int				NULL ,

	CONSTRAINT PK_SecurityPerson PRIMARY KEY  
	(
		PersonID
	)
)
