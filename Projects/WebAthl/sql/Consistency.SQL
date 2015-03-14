SELECT 	Series.*,
	Person.*, 
	ParticipantForSeries.*

FROM 	ParticipantForSeries, 
	Person, 
	Series
WHERE 	Person.PersonID = ParticipantForSeries.PersonID AND 
	Series.SeriesID = ParticipantForSeries.SeriesID AND 
	 (ParticipantForSeries.SeriesID=%s) AND
	 (ParticipantForSeries.ConsistencyEventsCurrent >= %s ) AND 
	 (ParticipantForSeries.ConsistencyEventsCurrent > 0 )

ORDER BY 
