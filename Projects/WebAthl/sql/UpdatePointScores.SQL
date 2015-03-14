UPDATE 	ParticipantForSeries

SET	ParticipantForSeries.GrossPoints = %d ,
	ParticipantForSeries.NetPoints = %d ,
	ParticipantForSeries.LowPoints = %d

WHERE 	ParticipantForSeries.SeriesID = %d AND
	ParticipantForSeries.PersonID = %d
