SELECT 	Results.PersonID,
	Person.FirstName, 
	Person.LastName, 
	Count(Results.PersonID) AS EventTally

FROM 	Person, 
	Results, 
	Event 

WHERE 	Person.PersonID = Results.PersonID AND 
	Event.EventID = Results.EventID AND 
	(
%s
	)  

GROUP BY 
	Results.PersonID, 
	Person.FirstName, 
	Person.LastName  

HAVING 	(Count(Results.PersonID)>=%s) AND
	(Count(Results.PersonID)<=%s)

ORDER BY 
	Count(Results.PersonID) DESC

