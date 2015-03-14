DELETE 	FROM 
	Results 

WHERE 	Results.PersonID NOT IN ( 
	SELECT 	PostResults.PersonID 
	FROM 	PostResults 
	WHERE 	PostResults.SeriesID = %d AND 
		PostResults.EventID = %d 
	) AND 
	Results.SeriesID = %d AND 
	Results.EventID = %d 
