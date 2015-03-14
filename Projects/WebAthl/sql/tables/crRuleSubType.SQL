CREATE TABLE RuleSubType 
(
	RuleTypeID 				int 			NOT NULL ,
	RuleSubTypeID 			int 			NOT NULL ,
	RuleSubTypeDescription 	varchar (60) 	NULL ,

	CONSTRAINT PK_RuleSubType PRIMARY KEY  
	(
		RuleTypeID,
		RuleSubTypeID
	)
)
