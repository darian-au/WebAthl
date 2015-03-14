INSERT 	INTO 	

	ParticipantForSeries (
		SeriesID,
		PersonID, 
		GroupIDSupposedTo, 
		DivisionSupposedTo, 
		EligibilityForEvent 
	)

	SELECT 	PreResults.SeriesID, 
		PreResults.PersonID,
		1 AS GroupIDSupposedTo,
		1 AS DivisionSupposedTo,
		'%c' AS EligibilityForEvent

	FROM 	PreResults 

	WHERE	PreResults.PersonID NOT IN (
			SELECT 	ParticipantForSeries.PersonID 
			FROM	ParticipantForSeries
			WHERE	SeriesID = %d
		) AND

		PreResults.SeriesID = %d AND
		PreResults.EventID = %d
