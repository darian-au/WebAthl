SELECT	Results.*

FROM 	Event, 
	Results 

WHERE 	Results.EventID = Event.EventID AND 
	Results.SeriesID = Event.SeriesID AND 
	Results.Points IS NOT NULL AND
	((Event.SeriesID=%d) AND
	 (Event.EventNo>(%d-1)) ) 

ORDER BY 
	Results.PersonID, 
	Results.Points DESC
