SELECT 	LatestFinancial.* , 
	RegistrationType.* 

FROM 	LatestFinancial , 
	RegistrationType , 
	ParticipantForSeries

WHERE 	LatestFinancial.RegistrationTypeID = RegistrationType.RegistrationTypeID
AND	ParticipantForSeries.PersonID = LatestFinancial.PersonID
AND	ParticipantForSeries.SeriesID = %d
