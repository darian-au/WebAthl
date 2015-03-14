INSERT 	INTO

	Results (
		SeriesID,
		EventID,
		PersonID,
		
		AgeGroup ,
		
		GroupStartActual,
		GrossPerformanceHOUR,
		GrossPerformanceMIN,
		GrossPerformanceSEC,
		
		Eligible,
		
		ChestNumber,
		GroupIDSupposedTo,
		DivisionSupposedTo,
		OrgID
	)

	SELECT 	PreResults.SeriesID, 
		PreResults.EventID, 
		PreResults.PersonID, 
		
		PreResults.AgeGroup, 
		
		Groups.GroupStart AS GroupStartActual, 
		PreResults.GrossPerformanceHOUR, 
		PreResults.GrossPerformanceMIN, 
		PreResults.GrossPerformanceSEC, 
		
		ParticipantForSeries.EligibilityForEvent AS Eligible, 
		
		PreResults.ChestNumber, 
		ParticipantForSeries.GroupIDSupposedTo, 
		ParticipantForSeries.DivisionSupposedTo, 
		LatestFinancial.OrgID
	
	FROM 	LatestFinancial RIGHT JOIN 
		(
			(
				(
					ParticipantForSeries INNER JOIN 
					(
						PreResults INNER JOIN Groups ON 
							(PreResults.GroupIDSupposedTo = Groups.GroupID) AND 
							(PreResults.SeriesID = Groups.SeriesID)
					) ON 
						(ParticipantForSeries.PersonID = PreResults.PersonID) AND 
						(ParticipantForSeries.SeriesID = PreResults.SeriesID) AND 
						(ParticipantForSeries.SeriesID = Groups.SeriesID)

				) INNER JOIN EventType ON 
					Groups.EventTypeID = EventType.EventTypeID

			) INNER JOIN Event ON 
				(PreResults.EventID = Event.EventID) AND 
				(PreResults.SeriesID = Event.SeriesID) AND 
				(EventType.EventTypeID = Event.EventTypeID)
		) ON 
			LatestFinancial.PersonID = PreResults.PersonID

	WHERE 	PreResults.SeriesID=%d AND PreResults.EventID=%d

	ORDER BY 
		PreResults.PersonID
