SELECT 	Roster.*, 
	RosterDescriptions.*, 
	Person.* 

FROM 	Roster, 
	RosterDescriptions, 
	Person 

WHERE 	EventID = %s 
AND 	Roster.PersonID = Person.PersonID 
AND 	Roster.TaskID = RosterDescriptions.TaskID 

ORDER BY 
	Person.Lastname 
