SELECT 	Results.*,
	EventType.*   

FROM 	Event, 
	EventType, 
	ParticipantForSeries, 
	Results 

WHERE 	Event.SeriesID = ParticipantForSeries.SeriesID AND 
	Results.EventID = Event.EventID AND 
	Results.PersonID = ParticipantForSeries.PersonID AND 
	Results.SeriesID = Event.SeriesID AND 
	Results.SeriesID = ParticipantForSeries.SeriesID AND 
	EventType.EventTypeID = Event.EventTypeID AND 

	Results.EventRate IS NOT NULL AND 

	((Event.SeriesID = %d ) AND
	 (Event.EventNo >= %d ) ) 

ORDER BY 
	Results.PersonID
	%s
