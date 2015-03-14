SELECT	Series.SeriesDescription, 
	Event.EventNo, 
	Location.LocationDescription, 
	EventType.EventDescription, 
	Event.DateDAY, 
	Event.DateMONTH, 
	Event.DateYEAR, 
	Person.FirstName, 
	Person.LastName, 
	Person.Sex, 
	Groups.GroupRate, 
	Results.SeriesID, 
	Results.EventID, 
	Results.PersonID, 
	Results.DivisionActual, 
	Results.AgeGroup, 
	Results.GroupIDActual, 
	Results.GroupStartActual, 
	Results.NewGroupID, 
	Results.NewGroupMessage, 
	Results.GrossPerformanceHOUR, 
	Results.GrossPerformanceMIN, 
	Results.GrossPerformanceSEC, 
	Results.NetPerformanceHOUR, 
	Results.NetPerformanceMIN, 
	Results.NetPerformanceSEC, 
	Results.Place, 
	Results.OverallPlace, 
	Results.Percentile, 
	Results.Points, 
	Results.Eligible, 
	Results.EventRate, 
	Results.GroupRateActual, 
	Results.ChestNumber, 
	Results.WorldStandard, 
	Results.GroupIDSupposedTo, 
	Results.DivisionSupposedTo,
	EventType.Timed
FROM	Event, 
	EventType, 
	Groups, 
	Location, 
	Person, 
	Results, 
	Series
WHERE	Results.PersonID = Person.PersonID AND 
	Results.SeriesID = Groups.SeriesID AND 
	Results.EventID = Event.EventID AND 
	Groups.SeriesID = Event.SeriesID AND 
	Results.SeriesID = Event.SeriesID AND 
	Groups.EventTypeID = Event.EventTypeID AND 
	EventType.EventTypeID = Event.EventTypeID AND 
	EventType.EventTypeID = Groups.EventTypeID AND 
	Results.GroupIDSupposedTo = Groups.GroupID AND 
	Series.SeriesID = Event.SeriesID AND 
	Series.SeriesID = Groups.SeriesID AND 
	Series.SeriesID = Results.SeriesID AND 
	Location.LocationID = Event.LocationID AND 
	((Results.SeriesID=%s) AND (Results.EventID=%s))
