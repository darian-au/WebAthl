SELECT 	%s
FROM 	Rules, 
	RuleSubType, 
	RuleType 
WHERE 	RuleSubType.RuleSubTypeID = Rules.RuleSubTypeID 
AND 	RuleSubType.RuleTypeID = Rules.RuleTypeID 
AND 	RuleType.RuleTypeID = Rules.RuleTypeID 
AND 	RuleType.RuleTypeID = RuleSubType.RuleTypeID 
AND 	((Rules.SeriesID=%d) 
AND 	 (RuleType.RuleTypeDescription='%s') 
AND 	 (RuleSubType.RuleSubTypeDescription='%s')) 

