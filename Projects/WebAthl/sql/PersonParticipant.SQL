SELECT 	ParticipantForSeries.*,
	Person.*

FROM 	ParticipantForSeries, 
	Person

WHERE 	Person.PersonID = ParticipantForSeries.PersonID AND 
	((ParticipantForSeries.SeriesID = %s) AND 
	 (ParticipantForSeries.GroupIDSupposedTo >= %s) AND
	 (ParticipantForSeries.GroupIDSupposedTo <= %s))

ORDER BY 
	ParticipantForSeries.GroupIDSupposedTo, 
	ParticipantForSeries.NetPoints DESC

