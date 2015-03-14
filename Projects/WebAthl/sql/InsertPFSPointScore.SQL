INSERT 	INTO 	

	ParticipantForSeries (
		SeriesID,
		PersonID, 
		GroupIDSupposedTo, 
		DivisionSupposedTo, 
		EligibilityForEvent 
	)

	SELECT 	DISTINCT 
		Results.SeriesID, 
		Results.PersonID,
		1 AS GroupIDSupposedTo,
		1 AS DivisionSupposedTo,
		'%c' AS EligibilityForEvent

	FROM 	Event, 
		Results 

	WHERE	Results.PersonID NOT IN (
			SELECT 	ParticipantForSeries.PersonID 
			FROM	ParticipantForSeries
			WHERE	ParticipantForSeries.SeriesID = %d
		) AND

	 	Results.EventID = Event.EventID AND 
		Results.SeriesID = Event.SeriesID AND 
		Results.Points IS NOT NULL AND
		((Event.SeriesID=%d) AND
		 (Event.EventNo>(%d-1)) ) 
