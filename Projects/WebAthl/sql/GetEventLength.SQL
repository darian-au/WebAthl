SELECT 	EventType.EventLength AS Total

FROM 	Event, 
	EventType

WHERE 	Event.EventTypeID = EventType.EventTypeID AND 
	((Event.SeriesID = %d ) AND
	 (Event.EventID = %d ))
