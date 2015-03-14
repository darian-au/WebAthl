SELECT 	COUNT(EventType.EventLength) AS Total

FROM 	Event, 
	EventType, 
	WorldStandard

WHERE 	EventType.EventTypeID = WorldStandard.EventTypeID AND 
	Event.EventTypeID = EventType.EventTypeID AND 
	Event.EventTypeID = WorldStandard.EventTypeID AND 
	((Event.SeriesID = %d ) AND
	 (Event.EventID = %d ) AND
	 (WorldStandard.RecCategory = 'D' ))
