SELECT 	Results.PersonID , 
	MIN(Results.AgeGroup) AS MinAgeGroup ,
	MAX(Results.AgeGroup) AS MaxAgeGroup ,
	COUNT(Results.AgeGroup) AS EventsForSeason , 
	NULL AS EventsForSeries 

FROM 	ParticipantForSeries ,
	SeriesSeason ,
 	Results 

WHERE 	ParticipantForSeries.SeriesID = SeriesSeason.SeriesID
AND	ParticipantForSeries.SeriesID = Results.SeriesID
AND	ParticipantForSeries.PersonID = Results.PersonID
AND	SeriesSeason.SeriesID = Results.SeriesID 
AND	Results.EventID >= SeriesSeason.FirstEventForSeason 
AND	Results.SeriesID = %d

GROUP BY
	Results.PersonID 

ORDER BY 
	Results.PersonID
