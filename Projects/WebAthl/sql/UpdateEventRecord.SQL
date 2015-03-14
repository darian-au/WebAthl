UPDATE	EventRecord

SET	EventRecord.EventID = Results.EventID,
	EventRecord.PersonID = Results.PersonID

FROM	Results,
	Event,
	Person,
	Series,
	EventRecord

WHERE	Results.SeriesID = Series.SeriesID
AND	Results.PersonID = Person.PersonID
AND	Event.EventID = Results.EventID
AND	Event.SeriesID = Results.SeriesID

AND	Results.SeriesID = EventRecord.SeriesID 
AND	Event.LocationID = EventRecord.LocationID
AND	Event.EventTypeID = EventRecord.EventTypeID
AND	Person.Sex = EventRecord.Sex
AND	Results.AgeGroup = EventRecord.AgeGroup
AND	Series.AgeCategory = EventRecord.AgeCategory

AND	Results.NetPerformanceHOUR = EventRecord.ClubPerformanceHOUR
AND	Results.NetPerformanceMIN = EventRecord.ClubPerformanceMIN
AND	Results.NetPerformanceSEC = EventRecord.ClubPerformanceSEC

AND	Results.SeriesID = %d
