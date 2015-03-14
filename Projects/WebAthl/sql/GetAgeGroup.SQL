SELECT	%s

FROM	Results,
	SeriesSeason

WHERE	SeriesSeason.SeriesID = Results.SeriesID 
AND	Results.SeriesID = %d 
AND	Results.EventID >= SeriesSeason.FirstEventForSeason 
AND	Results.PersonID = %d 
