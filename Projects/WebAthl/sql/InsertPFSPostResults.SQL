INSERT 	INTO 	

	ParticipantForSeries (
		SeriesID,
		PersonID, 
		GroupIDSupposedTo, 
		DivisionSupposedTo, 
		EligibilityForEvent 
	)

	SELECT 	PostResults.SeriesID, 
		PostResults.PersonID,
		1 AS GroupIDSupposedTo,
		1 AS DivisionSupposedTo,
		'%c' AS EligibilityForEvent

	FROM 	PostResults 

	WHERE	PostResults.PersonID NOT IN (
			SELECT 	ParticipantForSeries.PersonID 
			FROM	ParticipantForSeries
			WHERE	ParticipantForSeries.SeriesID = %d
		) AND

		PostResults.SeriesID = %d AND
		PostResults.EventID = %d

