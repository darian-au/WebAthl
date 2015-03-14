UPDATE 	Results

SET	Results.Eligible = 'D'

WHERE 	Results.SeriesID = %d AND
	Results.EventID = %d AND
	Results.PersonID IN (

	SELECT 	Results.PersonID

	FROM 	Results  

	WHERE 	((Results.SeriesID = %d) AND
		 (Results.EventID = %d) AND
		 (Results.DivisionActual <> Results.DivisionSupposedTo) ) 
)
