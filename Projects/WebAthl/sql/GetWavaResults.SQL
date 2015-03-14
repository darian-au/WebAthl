SELECT	Results.*, 

	WorldStandard.PerfHOUR, 
	WorldStandard.PerfMIN, 
	WorldStandard.PerfSEC

FROM 	Event, 
	Person, 
	Results, 
	WorldStandard, 
	Series 

WHERE 	    Results.EventID = Event.EventID 
	AND Results.SeriesID = Event.SeriesID 
	AND Person.PersonID = Results.PersonID 
	AND Series.SeriesID = Event.SeriesID 
	AND Series.SeriesID = Results.SeriesID 

	AND WorldStandard.AgeGroup = Results.AgeGroup 
	AND WorldStandard.EventTypeID = Event.EventTypeID 
	AND WorldStandard.Sex = Person.Sex  
	AND (WorldStandard.RecCategory = 'D' )

	AND (Results.SeriesID = %d ) 
	AND (Results.EventID = %d ) 

%s
