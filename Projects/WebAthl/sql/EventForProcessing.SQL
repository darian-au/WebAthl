SELECT 	Series.*,
	Event.*, 
	EventType.*, 
	Location.* 

FROM  	Series,
	Event,  
	EventType,  
	Location ,
	SeriesSeason

WHERE 	Series.SeriesID = %s 
AND	Series.SeriesID = Event.SeriesID 
AND	Event.SeriesID = SeriesSeason.SeriesID 
AND	EventType.EventTypeID = Event.EventTypeID 
AND	Location.LocationID = Event.LocationID 
AND	Event.EventID = SeriesSeason.NextEventForProcess

ORDER BY 
	Event.SeriesID, 
	Event.EventNo, 
	Event.EventID
