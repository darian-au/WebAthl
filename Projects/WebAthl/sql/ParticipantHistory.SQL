SELECT 	Series.*, 
	Person.*, 
	Event.*, 
	Location.*, 
	EventType.*, 
	Results.*

FROM 	Event, 
	EventType, 
	Location, 
	Person, 
	Results, 
	Series

WHERE 	Results.PersonID = Person.PersonID AND 
	Event.EventID = Results.EventID AND 
	Event.SeriesID = Results.SeriesID AND 
	EventType.EventTypeID = Event.EventTypeID AND 
	Location.LocationID = Event.LocationID AND 
	Series.SeriesID = Event.SeriesID AND 
	Series.SeriesID = Results.SeriesID AND 
	((Results.SeriesID > 0) AND (Results.PersonID = %s)) 
