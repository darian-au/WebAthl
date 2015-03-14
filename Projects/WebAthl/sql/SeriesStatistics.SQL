SELECT 	AgeGroup , 
	COUNT(*) AS Total , 
	Sex 

FROM 	Results , 
	Person 

WHERE 	Person.PersonId = Results.PersonID 
AND 	SeriesID = %s 
AND 	( EventID BETWEEN %s AND %s ) 

GROUP BY 
	AgeGroup , 
	Sex 

ORDER BY 
	AgeGroup , 
	Sex 
