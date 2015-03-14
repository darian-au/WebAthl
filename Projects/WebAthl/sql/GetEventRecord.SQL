SELECT	Results.SeriesID,
	Event.LocationID,
	0 AS EventID,
	Event.EventTypeID,
	Person.Sex,
	Results.AgeGroup,
	'' AS AgeCategory,
	0 AS PersonID,
	0 AS ClubPerformanceHOUR, 
	0 AS ClubPerformanceMIN, 
	%s(	(Results.NetPerformanceHOUR * 60.0 * 60.0) + 
		(Results.NetPerformanceMIN * 60.0) +
		(Results.NetPerformanceSEC)
	) AS ClubPerformanceSEC

FROM	Results,
	Event,
	Person,
	Series,
	EventType

WHERE	Results.SeriesID = Series.SeriesID
AND	Results.PersonID = Person.PersonID
AND	Event.EventID = Results.EventID
AND	Event.SeriesID = Results.SeriesID
AND	EventType.EventTypeID = Event.EventTypeID

AND	EventType.Timed = %d
AND	Results.SeriesID = %d

GROUP BY
	Results.SeriesID,
	Event.LocationID,
	Event.EventTypeID,
	Person.Sex,
	Results.AgeGroup
