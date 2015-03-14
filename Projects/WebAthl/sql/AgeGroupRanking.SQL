SELECT 	Series.* , 
	Location.* , 
	EventType.* , 
	Results.* , 
	Person.* , 
	Event.* 

FROM	Series , 
	Location , 
	EventType , 
	Results , 
	Person , 
	Event 

WHERE 	Results.SeriesID = Series.SeriesID 
AND 	Person.PersonID = Results.PersonID 
AND 	Event.EventID = Results.EventID 
AND 	Event.SeriesID = Results.SeriesID 
AND 	Event.SeriesID = Series.SeriesID 
AND 	Event.EventTypeID = EventType.EventTypeID 
AND 	Event.LocationID = Location.LocationID 
AND 	Series.SeriesID = %s 
AND 	Location.LocationID = %s 
AND 	EventType.EventTypeID = %s

ORDER BY 
	Person.Sex , 
	Results.AgeGroup , 
	Results.NetPerformanceHOUR , 
	Results.NetPerformanceMIN , 
	Results.NetPerformanceSEC 
