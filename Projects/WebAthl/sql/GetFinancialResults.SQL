SELECT 	LatestFinancial.* , 
	RegistrationType.*

FROM 	LatestFinancial , 
	RegistrationType , 
	Results

WHERE 	LatestFinancial.RegistrationTypeID = RegistrationType.RegistrationTypeID
AND	Results.PersonID = LatestFinancial.PersonID
AND	Results.SeriesID = %d
AND	Results.EventID = %d
