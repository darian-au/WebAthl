UPDATE 	Results

SET	Results.Eligible = 'G'

WHERE 	Results.SeriesID = %d AND
	Results.EventID = %d AND
	Results.PersonID IN (

	SELECT 	Results.PersonID

	FROM 	Results  

	WHERE 	((Results.SeriesID = %d) AND
		 (Results.EventID = %d) AND
		 (Results.GroupIDActual <> Results.GroupIDSupposedTo) ) 
)