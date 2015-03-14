UPDATE	ParticipantForSeries 
SET	ParticipantForSeries.EligibilityForEvent = '%d' 
WHERE	ParticipantForSeries.SeriesID = %d 
AND	ParticipantForSeries.PersonID IN (
				
	SELECT 	Results.PersonID 
	FROM 	ParticipantForSeries, 
		Results, 
		Event  
	WHERE 	ParticipantForSeries.PersonID = Results.PersonID AND 
		ParticipantForSeries.SeriesID = Results.SeriesID AND 
		Results.EventID = Event.EventID AND
		(Results.SeriesID = %d) AND
		(Event.EventNo BETWEEN (%d - %d) AND (%d) )
		%s
	GROUP BY Results.PersonID
	HAVING COUNT(EventNo) %s

)
