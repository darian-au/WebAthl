CREATE VIEW LatestFinancial AS

	SELECT 	Financial.*
	FROM 	( 
			SELECT 	Financial.PersonID, 
				MAX(Financial.Year) AS Yr 
			FROM 	Financial 
			GROUP BY 
				Financial.PersonID 

		) AS f 

		INNER JOIN Financial ON 
			Financial.PersonID = f.PersonID AND
			Financial.Year = f.Yr

