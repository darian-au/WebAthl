SELECT 
	Series.*, 
	Person.*, 
	ParticipantForSeries.*, 
	Organisation.*

FROM 
	(
		(
			ParticipantForSeries INNER JOIN Person ON 
				ParticipantForSeries.PersonID = Person.PersonID

		) INNER JOIN Series ON 
			ParticipantForSeries.SeriesID = Series.SeriesID

	) LEFT JOIN Organisation ON 
		ParticipantForSeries.OrgID = Organisation.OrgID

WHERE
	Series.SeriesID = %s

