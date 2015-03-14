CREATE TABLE PersonComments 
(
	PersonID 				int 			NOT NULL ,
	CommentNo				int  			NOT NULL ,
	Type					varchar (60) 	NULL ,
	Comment 				varchar (100) 	NULL ,

	CONSTRAINT PK_PersonComments PRIMARY KEY  
	(
		PersonID,
		CommentNo
	)
)
