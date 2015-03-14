SELECT 	EventNo 
FROM 	Event 
WHERE	EventID = (
	SELECT 	FirstEventForSeason
	FROM 	SeriesSeason
	WHERE 	SeriesSeason.SeriesID = %d
)	
