SELECT	PreResults.SeriesID, 
	PreResults.EventID,  
	PreResults.PersonID, 
	PreResults.GroupIDSupposedTo AS GroupID, 
	PreResults.DivisionSupposedTo AS Division, 
	PreResults.GrossPerformanceHOUR, 
	PreResults.GrossPerformanceMIN, 
	PreResults.GrossPerformanceSEC,
	PreResults.Place, 
	PreResults.AgeGroup, 
	PreResults.ChestNumber, 
	NULL AS NewGroupID, 
	NULL AS NewGroupMessage, 
	NULL AS Points, 
	Person.LastName, 
	Person.FirstName, 
	Person.MiddleName, 
	Person.Sex 

FROM 	PreResults, 
	Person 

WHERE 	PreResults.PersonID = Person.PersonID
AND	PreResults.SeriesID = %s 
AND	PreResults.EventID = %s 

ORDER BY 
	DivisionSupposedTo 
