SELECT 	ParticipantForSeries.*, 
	Person.*, 
	Groups.*, 
	Series.*, 
	Event.*, 
	EventType.*, 
	Location.*

FROM 	ParticipantForSeries, 
	Person, 
	Groups,
	Series, 
	Event, 
	EventType, 
	Location 

WHERE 	EventType.EventTypeID = Event.EventTypeID 
 AND	Groups.EventTypeID = Event.EventTypeID 
 AND	Groups.EventTypeID = EventType.EventTypeID 
 AND 	Groups.SeriesID = Event.SeriesID 
 AND 	ParticipantForSeries.SeriesID = Event.SeriesID 
 AND 	ParticipantForSeries.SeriesID = Groups.SeriesID 
 AND 	Series.SeriesID = Event.SeriesID 
 AND 	Series.SeriesID = Groups.SeriesID 
 AND 	Series.SeriesID = ParticipantForSeries.SeriesID 
 AND 	Person.PersonID = ParticipantForSeries.PersonID 
 AND 	Location.LocationID = Event.LocationID 
 AND	ParticipantForSeries.GroupIDSupposedTo = Groups.GroupID 
 AND	( ParticipantForSeries.SeriesID = %s ) 
 AND 	( Event.EventID = %s ) 
