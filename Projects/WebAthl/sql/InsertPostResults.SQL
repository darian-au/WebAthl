INSERT 	INTO

	Results (
		SeriesID,
		EventID,
		PersonID,
		DivisionActual,
		AgeGroup ,
		GroupIDActual,
		GroupStartActual,
		GrossPerformanceHOUR,
		GrossPerformanceMIN,
		GrossPerformanceSEC,
		Place,
		Eligible,
		GroupRateActual,
		ChestNumber,
		GroupIDSupposedTo,
		DivisionSupposedTo,
		OrgID
	)

	SELECT 	PostResults.SeriesID, 
		PostResults.EventID, 
		PostResults.PersonID, 
		PostResults.DivisionActual, 
		PostResults.AgeGroup, 
		PostResults.GroupIDActual, 
		Groups.GroupStart AS GroupStartActual, 
		PostResults.GrossPerformanceHOUR, 
		PostResults.GrossPerformanceMIN, 
		PostResults.GrossPerformanceSEC, 
		PostResults.Place, 
		ParticipantForSeries.EligibilityForEvent AS Eligible, 
		Groups.GroupRate AS GroupRateActual, 
		PostResults.ChestNumber, 
		ParticipantForSeries.GroupIDSupposedTo, 
		ParticipantForSeries.DivisionSupposedTo, 
		LatestFinancial.OrgID
	
	FROM 	LatestFinancial RIGHT JOIN 
		(
			(
				(
					ParticipantForSeries INNER JOIN 
					(
						PostResults INNER JOIN Groups ON 
							(PostResults.GroupIDActual = Groups.GroupID) AND 
							(PostResults.SeriesID = Groups.SeriesID)
					) ON 
						(ParticipantForSeries.PersonID = PostResults.PersonID) AND 
						(ParticipantForSeries.SeriesID = PostResults.SeriesID) AND 
						(ParticipantForSeries.SeriesID = Groups.SeriesID)

				) INNER JOIN EventType ON 
					Groups.EventTypeID = EventType.EventTypeID

			) INNER JOIN Event ON 
				(PostResults.EventID = Event.EventID) AND 
				(PostResults.SeriesID = Event.SeriesID) AND 
				(EventType.EventTypeID = Event.EventTypeID)
		) ON 
			LatestFinancial.PersonID = PostResults.PersonID

	WHERE 	PostResults.SeriesID=%d AND PostResults.EventID=%d

	ORDER BY 
		PostResults.PersonID
