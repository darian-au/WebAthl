SELECT	PostResults.SeriesID, 
	PostResults.EventID,  
	PostResults.PersonID, 
	PostResults.GroupIDActual AS GroupID, 
	PostResults.DivisionActual AS Division, 
	PostResults.GrossPerformanceHOUR, 
	PostResults.GrossPerformanceMIN, 
	PostResults.GrossPerformanceSEC,
	PostResults.Place, 
	PostResults.AgeGroup, 
	PostResults.ChestNumber, 
	PostResults.NewGroupID, 
	PostResults.NewGroupMessage, 
	PostResults.Points, 
	Person.LastName, 
	Person.FirstName, 
	Person.MiddleName, 
	Person.Sex 

FROM 	PostResults, 
	Person 

WHERE 	PostResults.PersonID = Person.PersonID
AND	PostResults.SeriesID = %s 
AND	PostResults.EventID = %s 

ORDER BY 
	DivisionActual 
