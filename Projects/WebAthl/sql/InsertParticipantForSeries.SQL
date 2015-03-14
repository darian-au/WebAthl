INSERT INTO ParticipantForSeries(SeriesID,PersonID,GroupIDSupposedTo,DivisionSupposedTo,EligibilityForEvent,OrgID)

SELECT	
	r.SeriesID, 
	r.PersonID, 
	r.%s,
	r.DivisionSupposedTo, 
	'%c' AS EligibilityForEvent,
	LatestFinancial.OrgID

FROM	LatestFinancial RIGHT JOIN 
	(
		Results AS r INNER JOIN 
		(
			SELECT 	Results.PersonID, MAX(EventID) AS LatestEventID
			FROM 	Results 
			WHERE 	SeriesID = %d and
				PersonID IN 
				(
					SELECT	Results.PersonID

					FROM 	Results, 
						SeriesSeason,
						Event

					WHERE 	SeriesSeason.SeriesID = Results.SeriesID AND 
						Results.EventID = Event.EventID AND
						((Results.SeriesID=%d) AND
						 (Event.EventNo>=(%d-SeriesSeason.EventsInSeason))) 

					GROUP BY Results.PersonID
				)
			GROUP BY PersonID

		) AS b ON 
			r.EventID = b.LatestEventID AND r.PersonID = b.PersonID

	) ON 
		LatestFinancial.PersonID = r.PersonID	

WHERE r.SeriesID = %d AND ( %s )

