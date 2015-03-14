SELECT	Results.SeriesID, 
	Results.EventID, 
	Results.PersonID, 
	Results.NewGroupID,
	Results.NewGroupMessage,

	Results.GroupIDSupposedTo, 

	ParticipantForSeries.GroupIDSupposedTo

FROM
	(
		(
			SELECT 	MAX(Results.EventID) AS EventID, 
				Results.SeriesID,
				Results.PersonID

			FROM 	ParticipantForSeries INNER JOIN Results ON
					(ParticipantForSeries.SeriesID = Results.SeriesID) AND
					(ParticipantForSeries.PersonID = Results.PersonID) 

			WHERE 	Results.SeriesID = %s
			GROUP BY
				Results.PersonID,
				Results.SeriesID

		) AS PersonsLatestEventID INNER JOIN Results ON
			(PersonsLatestEventID.EventID = Results.EventID) AND
			(PersonsLatestEventID.SeriesID = Results.SeriesID) AND
			(PersonsLatestEventID.PersonID = Results.PersonID) 

	) INNER JOIN ParticipantForSeries ON
		(Results.SeriesID = ParticipantForSeries.SeriesID) AND
		(Results.PersonID = ParticipantForSeries.PersonID) 
