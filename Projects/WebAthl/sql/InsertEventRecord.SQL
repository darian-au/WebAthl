SELECT	EventRecordTemp.SeriesID ,
	EventRecordTemp.LocationID ,
	Results.EventID ,
	EventRecordTemp.EventTypeID ,
	EventRecordTemp.Sex ,
	EventRecordTemp.AgeGroup ,
	EventRecordTemp.AgeCategory ,
	Results.PersonID ,
	EventRecordTemp.ClubPerformanceHOUR ,
	EventRecordTemp.ClubPerformanceMIN ,
	EventRecordTemp.ClubPerformanceSEC 

FROM	Results,
	Event,
	Person,
	Series,
	EventType,
	EventRecordTemp

WHERE	Results.SeriesID = Series.SeriesID
AND	Results.PersonID = Person.PersonID
AND	Event.EventID = Results.EventID
AND	Event.SeriesID = Results.SeriesID
AND	EventType.EventTypeID = Event.EventTypeID

AND	EventType.Timed = %d
AND	Results.SeriesID = %d

AND	Results.SeriesID = EventRecordTemp.SeriesID 
AND	Event.LocationID = EventRecordTemp.LocationID
AND	Event.EventTypeID = EventRecordTemp.EventTypeID
AND	Person.Sex = EventRecordTemp.Sex
AND	Results.AgeGroup = EventRecordTemp.AgeGroup

AND	Results.NetPerformanceHOUR = EventRecordTemp.ClubPerformanceHOUR
AND	Results.NetPerformanceMIN = EventRecordTemp.ClubPerformanceMIN
AND	Results.NetPerformanceSEC = EventRecordTemp.ClubPerformanceSEC

