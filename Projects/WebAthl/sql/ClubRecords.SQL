SELECT 	EventRecord.*, 
	Series.*, 
	Location.*, 
	EventType.*, 
	Person.*,
	Event.*

FROM 	Event,
	EventRecord, 
	EventType, 
	Location, 
	Person, 
	Series

WHERE 	Event.EventID = EventRecord.EventID 
AND		Event.SeriesID = EventRecord.SeriesID 
AND		Event.EventTypeID = EventRecord.EventTypeID 
AND		Event.LocationID = EventRecord.LocationID 
AND		EventType.EventTypeID = Event.EventTypeID 
AND		EventType.EventTypeID = EventRecord.EventTypeID 
AND		Person.PersonID = EventRecord.PersonID 
AND		Person.Sex = EventRecord.Sex 
AND		Series.SeriesID = Event.SeriesID 
AND		Series.SeriesID = EventRecord.SeriesID 
AND		Location.LocationID = Event.LocationID 
AND		Location.LocationID = EventRecord.LocationID 
