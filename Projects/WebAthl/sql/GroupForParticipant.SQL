SELECT 	Series.*, 
	Person.* ,
	ParticipantForSeries.*, 
	Results.*,

	Event.*, 
	Location.*, 
	EventType.*

FROM 	ParticipantForSeries, 
	Person, 
	Series,
	Results,

	Event, 
	Location, 
	EventType

WHERE 	Results.PersonID = Person.PersonID AND 
	Event.EventID = Results.EventID AND 
	Event.SeriesID = Results.SeriesID AND 
	EventType.EventTypeID = Event.EventTypeID AND 
	Location.LocationID = Event.LocationID AND 
	Series.SeriesID = Event.SeriesID AND 
	Series.SeriesID = Results.SeriesID AND 

	Series.SeriesID = ParticipantForSeries.SeriesID AND 
	Person.PersonID = ParticipantForSeries.PersonID AND 
	Results.PersonID = ParticipantForSeries.PersonID AND 
	Results.SeriesID = ParticipantForSeries.SeriesID AND 
	((ParticipantForSeries.PersonID=%s) AND 
	 (ParticipantForSeries.SeriesID=%s)) AND

	Event.EventNo = (
	
		SELECT 	MAX(Event.EventNo)
		FROM 	Event,
			Results
		WHERE	Event.EventID = Results.EventID AND
			((Results.PersonID=%s) AND 
			 (Results.SeriesID=%s))
	)

ORDER BY Event.EventNo DESC

