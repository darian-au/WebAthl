UPDATE 	Results
SET	OrgID = (

	SELECT 	Financial.OrgID
	FROM 	( 
			SELECT 	Financial.PersonID, 
				MAX(Financial.Year) AS Yr 
			FROM 	Financial 
			GROUP BY 
				Financial.PersonID 

		) AS LatestFinancial 

		INNER JOIN Financial ON 
			Financial.PersonID = LatestFinancial.PersonID AND
			Financial.Year = LatestFinancial.Yr
		
	WHERE
		Financial.PersonID  = Results.PersonID
)
WHERE 	Results.SeriesID = %d AND
	Results.EventID = %d
