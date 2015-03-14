CREATE TABLE Rules 
(
	SeriesID 				int 			NOT NULL ,
	RuleTypeID 				int 			NOT NULL ,
	RuleSubTypeID 			int 			NOT NULL ,
	RuleID 					int 			NOT NULL ,
	Law 					int 			NULL ,

	CONSTRAINT PK_Rules PRIMARY KEY  
	(
		SeriesID,
		RuleTypeID,
		RuleSubTypeID,
		RuleID
	)
)
