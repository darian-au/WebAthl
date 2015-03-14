CREATE TABLE SecurityRole 
(
	RoleID					int 			NOT NULL ,
	RoleName 				varchar (60) 	NULL ,
	Permission				int 			NULL ,

	CONSTRAINT PK_SecurityRole PRIMARY KEY  
	(
		RoleID
	)
)
