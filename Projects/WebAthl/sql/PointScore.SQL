SELECT 	Series.*,
	Person.*, 
	ParticipantForSeries.*

FROM 	Series, 
	Person, 
	ParticipantForSeries

WHERE 	Person.PersonID = ParticipantForSeries.PersonID AND 
	Series.SeriesID = ParticipantForSeries.SeriesID AND 
	(ParticipantForSeries.SeriesID=%s) AND
	(ParticipantForSeries.EventsForSeason >= %s) AND
	(ParticipantForSeries.EventsForSeason > 0)

ORDER BY
